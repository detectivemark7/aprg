#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <FileExtractor/AprgFileExtractor.hpp>

#include <gtest/gtest.h>

#ifndef PATH_OF_7Z_TEMP_FILE
    static_assert(false, "PATH_OF_7Z_TEMP_FILE is not set in cmake");
#endif

#define PATH_OF_SAMPLE_ZIP_1 APRG_DIR R"(\AprgFileExtractor\FilesForTests\DirectoryTest.zip)"
#define PATH_OF_SAMPLE_ZIP_2 APRG_DIR R"(\AprgFileExtractor\FilesForTests\DirectoryTest2.zip)"

using namespace std;

namespace alba
{

namespace
{

void deleteAllFilesOnDirectory(string const& directoryPath)
{
    AlbaLocalPathHandler topDirectoryPathHandler(directoryPath);
    set<string> files;
    set<string> directories;
    topDirectoryPathHandler.findFilesAndDirectoriesUnlimitedDepth("*.*", files, directories);
    for(string const& file: files)
    {
        AlbaLocalPathHandler filePathHandler(file);
        filePathHandler.deleteFile();
        filePathHandler.reInput();
        ASSERT_FALSE(filePathHandler.isFoundInLocalSystem());
    }
}

}

namespace ProgressCounters
{
int numberOfFilesToBeAnalyzedForExtraction;
int numberOfFilesAnalyzedForExtraction;
}

TEST(AprgFileExtractorTest, DISABLED_ActualTest)
{
    AprgFileExtractor fileExtractor(R"([LRM] || [alarm] || [UDP] || [CPU] || [syslog] || [ccns] || [tcom] || [startup] || [runtime] || [system] || [radparam] || ([bts]&&([.log]||[.zip]||[.tar])) || [snapshot] || ([tech]&&[report]) || [BTSLogFiles])");
    fileExtractor.extractAllRelevantFiles(R"(D:\W\ZZZ_Useless_Logs\PR103380\New folder\)");
}

TEST(AprgFileExtractorTest, ListOfFilesFromZipFileAreCorrectlyRetrieved)
{
    AprgFileExtractor fileExtractor;
    set<string> files;
    fileExtractor.copyRelativeFilePathsFromCompressedFile(PATH_OF_SAMPLE_ZIP_1, files);

    ASSERT_EQ(11U, files.size());
    auto fileIterator = files.begin();
    EXPECT_EQ(R"(DirectoryTest\DIR1\File1.log)", *fileIterator++);
    EXPECT_EQ(R"(DirectoryTest\DIR2\File2.txt)", *fileIterator++);
    EXPECT_EQ(R"(DirectoryTest\DIR3\File3)", *fileIterator++);
    EXPECT_EQ(R"(DirectoryTest\DIR4\File4.mp3)", *fileIterator++);
    EXPECT_EQ(R"(DirectoryTest\DIR5\File5.avi)", *fileIterator++);
    EXPECT_EQ(R"(DirectoryTest\DIR6\SUBDIR1\File6.jpg)", *fileIterator++);
    EXPECT_EQ(R"(DirectoryTest\File1.log)", *fileIterator++);
    EXPECT_EQ(R"(DirectoryTest\File2.txt)", *fileIterator++);
    EXPECT_EQ(R"(DirectoryTest\File3)", *fileIterator++);
    EXPECT_EQ(R"(DirectoryTest\File4.mp3)", *fileIterator++);
    EXPECT_EQ(R"(DirectoryTest\File5.avi)", *fileIterator++);
}

TEST(AprgFileExtractorTest, OneFileIsExtractedSuccessfully)
{
    AprgFileExtractor fileExtractor;
    AlbaLocalPathHandler directoryPathHandler(APRG_DIR R"(\AprgFileExtractor\FilesForTests\DirectoryTest\)");
    deleteAllFilesOnDirectory(directoryPathHandler.getFullPath());

    string outputFilePath = fileExtractor.extractOneFile(PATH_OF_SAMPLE_ZIP_1, R"(DirectoryTest\DIR1\File1.log)");

    AlbaLocalPathHandler filePathHandler(APRG_DIR R"(\AprgFileExtractor\FilesForTests\DirectoryTest\DirectoryTest\DIR1\File1.log)");
    EXPECT_EQ(filePathHandler.getFullPath(), outputFilePath);
    filePathHandler.reInput();
    EXPECT_TRUE(filePathHandler.isFoundInLocalSystem());
    deleteAllFilesOnDirectory(directoryPathHandler.getFullPath());
}

TEST(AprgFileExtractorTest, AllFilesAreExtractedSuccessfully)
{
    AprgFileExtractor fileExtractor;
    AlbaLocalPathHandler directoryPathHandler(APRG_DIR R"(\AprgFileExtractor\FilesForTests\DirectoryTest\)");
    deleteAllFilesOnDirectory(directoryPathHandler.getFullPath());

    string outputDirectoryPath = fileExtractor.extractOnceForAllFiles(PATH_OF_SAMPLE_ZIP_1);

    EXPECT_EQ(directoryPathHandler.getFullPath(), outputDirectoryPath);
    AlbaLocalPathHandler outputFilePathHandler(APRG_DIR R"(\AprgFileExtractor\FilesForTests\DirectoryTest\File1.log)");
    EXPECT_TRUE(outputFilePathHandler.isFoundInLocalSystem());
    outputFilePathHandler.input(APRG_DIR R"(\AprgFileExtractor\FilesForTests\DirectoryTest\File2.txt)");
    EXPECT_TRUE(outputFilePathHandler.isFoundInLocalSystem());
    outputFilePathHandler.input(APRG_DIR R"(\AprgFileExtractor\FilesForTests\DirectoryTest\File3)");
    EXPECT_TRUE(outputFilePathHandler.isFoundInLocalSystem());
    outputFilePathHandler.input(APRG_DIR R"(\AprgFileExtractor\FilesForTests\DirectoryTest\File4.mp3)");
    EXPECT_TRUE(outputFilePathHandler.isFoundInLocalSystem());
    outputFilePathHandler.input(APRG_DIR R"(\AprgFileExtractor\FilesForTests\DirectoryTest\File5.avi)");
    EXPECT_TRUE(outputFilePathHandler.isFoundInLocalSystem());
    deleteAllFilesOnDirectory(directoryPathHandler.getFullPath());
}

TEST(AprgFileExtractorTest, FilesAreExtractedSuccessfullyWithACondition)
{
    AprgFileExtractor fileExtractor("[.log]");
    AlbaLocalPathHandler directoryPathHandler(APRG_DIR R"(\AprgFileExtractor\FilesForTests\DirectoryTest\)");
    deleteAllFilesOnDirectory(directoryPathHandler.getFullPath());

    fileExtractor.extractAllRelevantFiles(PATH_OF_SAMPLE_ZIP_1);

    AlbaLocalPathHandler filePathHandler(APRG_DIR R"(\AprgFileExtractor\FilesForTests\DirectoryTest\DirectoryTest\DIR1\File1.log)");
    EXPECT_TRUE(filePathHandler.isFoundInLocalSystem());
    filePathHandler.input(APRG_DIR R"(\AprgFileExtractor\FilesForTests\DirectoryTest\DirectoryTest\File1.log)");
    EXPECT_TRUE(filePathHandler.isFoundInLocalSystem());
    deleteAllFilesOnDirectory(directoryPathHandler.getFullPath());
}

TEST(AprgFileExtractorTest, FilesAreExtractedSuccessfullyWithAConditionWhen7zPathHasSpaces)
{
    AprgFileExtractor fileExtractor("[.log]", APRG_DIR R"(\AprgFileExtractor\7z32 With Space\7z. With Space.exe)", APRG_DIR R"(\AprgFileExtractor\7z32 With Space\tempFile.txt)");
    AlbaLocalPathHandler directoryPathHandler(APRG_DIR R"(\AprgFileExtractor\FilesForTests\DirectoryTest\)");
    deleteAllFilesOnDirectory(directoryPathHandler.getFullPath());

    fileExtractor.extractAllRelevantFiles(PATH_OF_SAMPLE_ZIP_1);

    AlbaLocalPathHandler filePathHandler(APRG_DIR R"(\AprgFileExtractor\FilesForTests\DirectoryTest\DirectoryTest\DIR1\File1.log)");
    EXPECT_TRUE(filePathHandler.isFoundInLocalSystem());
    filePathHandler.input(APRG_DIR R"(\AprgFileExtractor\FilesForTests\DirectoryTest\DirectoryTest\File1.log)");
    EXPECT_TRUE(filePathHandler.isFoundInLocalSystem());
    deleteAllFilesOnDirectory(directoryPathHandler.getFullPath());
}

TEST(AprgFileExtractorTest, FilesAreExtractedRecursivelyWithACondition)
{
    AprgFileExtractor fileExtractor("[DirectoryTest]");
    AlbaLocalPathHandler directoryPathHandler(APRG_DIR R"(\AprgFileExtractor\FilesForTests\DirectoryTest2\)");
    deleteAllFilesOnDirectory(directoryPathHandler.getFullPath());

    fileExtractor.extractAllRelevantFiles(PATH_OF_SAMPLE_ZIP_2);

    AlbaLocalPathHandler filePathHandler(APRG_DIR R"(\AprgFileExtractor\FilesForTests\DirectoryTest2\DirectoryTest2\DirectoryTest2\DirectoryTest2.txt)");
    EXPECT_TRUE(filePathHandler.isFoundInLocalSystem());
    deleteAllFilesOnDirectory(directoryPathHandler.getFullPath());
}

}
