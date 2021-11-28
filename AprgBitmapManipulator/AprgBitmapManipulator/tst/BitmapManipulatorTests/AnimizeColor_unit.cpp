#include <BitmapManipulator/AnimizeColor.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>

#include <gtest/gtest.h>

using namespace std;

#define APRG_BITMAP_FILTERS_BITMAP_DIRECTORY APRG_DIR R"(\AprgBitmapFilters\FilesForTests\SampleBitmaps\)"

namespace alba {

namespace AprgBitmap {

TEST(AnimizeColorTest, DISABLED_GatherAndSaveStatistics) {
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);

    gatherAndSaveDataInAnimizeColor(bitmapDirectory.getDirectory() + R"(NonAnimeBitmaps\Foals.bmp)");
}

}  // namespace AprgBitmap

}  // namespace alba
