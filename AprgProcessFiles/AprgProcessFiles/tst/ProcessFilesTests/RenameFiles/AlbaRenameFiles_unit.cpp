#include <ProcessFiles/RenameFiles/AlbaRenameFiles.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(AlbaRenameFilesTest, DISABLED_RealExample) {
    AlbaRenameFiles renameFiles(
        R"(N:\Branches\APRG\AprgBitmapFilters\SampleBitmaps\AnimizeMultipleFilesTest\output2test)");
    renameFiles.renameWithIncreasingNumbers("JohnMayer", 0, 6);
}

}  // namespace alba
