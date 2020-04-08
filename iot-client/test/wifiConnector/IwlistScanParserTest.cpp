//
// Created by julian on 19.07.18.
//

#include "IwlistScanParserTest.h"
#include "IwListScannData.h"

TEST_F(IwlistScanParserTest , parseEmpty) {
    std::vector<std::string> lines { "" };

    auto erg = parser.parse(lines);

    ASSERT_EQ(erg.size(), 0);
}

/**
 * This test case uses a wifif scann from the university. There's only one valid Hotspot.
 */
TEST_F(IwlistScanParserTest , parseOnlyOneValid) {
    auto lines = IwListScannData::parseOnlyOneValid();

    auto erg = parser.parse(lines);

    ASSERT_EQ(erg.size(), 1);
}