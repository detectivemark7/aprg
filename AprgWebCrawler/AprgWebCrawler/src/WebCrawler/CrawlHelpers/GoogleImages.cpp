#include <Common/File/AlbaFileReader.hpp>
#include <Common/String/AlbaStringHelper.hpp>
#include <WebCrawler/WebCrawler.hpp>

#include <deque>
#include <fstream>
#include <iostream>
#include <unordered_set>

using namespace alba;
using namespace std;

using alba::stringHelper::getStringInBetweenTwoStrings;
using alba::stringHelper::isStringFoundInsideTheOtherStringCaseSensitive;

/*
namespace aprgWebCrawler
{

void WebCrawler::saveImageListFromGoogleImages()
{
    AlbaLocalPathHandler downloadPathHandler(m_downloadDirectoryPathHandler.getDirectory() + R"(\temp.html)");
    AlbaLocalPathHandler listPathHandler(m_downloadDirectoryPathHandler.getDirectory() + R"(\ListOfImages.txt)");
    ifstream htmlFileStream(downloadPathHandler.getFullPath());
    if(!htmlFileStream.is_open())
    {
        cout << "Cannot open html file." << endl;
        cout << "File to read:" << downloadPathHandler.getFullPath() << endl;
        return;
    }
    ofstream listFileStream(listPathHandler.getFullPath());
    if(!listFileStream.is_open())
    {
        cout << "Cannot open list file." << endl;
        cout << "File to write:" << listPathHandler.getFullPath() << endl;
        return;
    }
    AlbaFileReader htmlFileReader(htmlFileStream);
    unordered_set<string> listOfImages;
    while (htmlFileReader.isNotFinished())
    {
        string lineInHtmlFile(htmlFileReader.getLine());
        if(isStringFoundInsideTheOtherStringCaseSensitive(lineInHtmlFile, "http://www.google.com/imgres?imgurl="))
        {
            int indexOfImgres = lineInHtmlFile.find("http://www.google.com/imgres?");
            while(stringHelper::isNotNpos(indexOfImgres))
            {
                listOfImages.emplace(getStringInBetweenTwoStrings(lineInHtmlFile, "imgurl=", "&", indexOfImgres));
                indexOfImgres = lineInHtmlFile.find("http://www.google.com/imgres?", indexOfImgres);
            }
        }
    }
    for(string const imageLink:listOfImages)
    {
        listFileStream<<imageLink<<endl;
    }
}

void WebCrawler::downloadGoogleImages() const
{
    AlbaLocalPathHandler listPathHandler(m_downloadDirectoryPathHandler.getDirectory() + R"(\ListOfImages.txt)");
    ifstream listFileStream(listPathHandler.getFullPath());
    if(!listFileStream.is_open())
    {
        cout << "Cannot open html file." << endl;
        cout << "File to read:" << listPathHandler.getFullPath() << endl;
        return;
    }
    AlbaFileReader listFileReader(listFileStream);
    deque<string> listOfImages;
    while (listFileReader.isNotFinished())
    {
        listOfImages.emplace_back(listFileReader.getLine());
    }
    listFileStream.close();


    while(!listOfImages.empty())
    {
        AlbaWebPathHandler imageWebPathHandler(listOfImages.front());
        if(!imageWebPathHandler.isFile())
        {
            cout << "Image link is not to a file." << endl;
            cout << "ImageLinkWebPath : " << imageWebPathHandler.getFullPath() << endl;
            return;
        }
        //downloadBinaryFileUntilSuccessful(imageWebPathHandler, AlbaLocalPathHandler(m_workingPathHandler.getDirectory() + imageWebPathHandler.getFile()));
        listOfImages.pop_front();
        ofstream outListFileStream(listPathHandler.getFullPath());
        if(!outListFileStream.is_open())
        {
            cout << "Cannot open list file." << endl;
            cout << "File to write:" << listPathHandler.getFullPath() << endl;
            return;
        }
        for(string const imageLink:listOfImages)
        {
            outListFileStream<<imageLink<<endl;
        }
    }
}

}
*/
