// PanelTest.cpp  -  Test the Panel class

#include "UnitTest++.h"

#include "Panel.h"

#include <iostream>

using namespace Yosokumo;

TEST(allMethodsForPanel)
{
    std::cout << "Panel allMethodsForPanel" << '\n';

    std::string nameControlLocation       = "name control location";
    std::string statusControlLocation     = "status control location";
    std::string visibilityControlLocation = "visibility control location";

    uint64_t blockCount    = 16449;
    uint64_t cellCount     = 271;
    uint64_t prospectCount = 314159;

    std::string creationTime       = "creation time";
    std::string latestBlockTime    = "latest block time";
    std::string latestProspectTime = "latest prospect time";

    Panel panel;

    panel.setNameControlLocation      (nameControlLocation      );
    panel.setStatusControlLocation    (statusControlLocation    );
    panel.setVisibilityControlLocation(visibilityControlLocation);
    panel.setBlockCount               (blockCount               );
    panel.setCellCount                (cellCount                );
    panel.setProspectCount            (prospectCount            );
    panel.setCreationTime             (creationTime             );
    panel.setLatestBlockTime          (latestBlockTime          );
    panel.setLatestProspectTime       (latestProspectTime       );

    CHECK_EQUAL(panel.getNameControlLocation      (), nameControlLocation      );
    CHECK_EQUAL(panel.getStatusControlLocation    (), statusControlLocation    );
    CHECK_EQUAL(panel.getVisibilityControlLocation(), visibilityControlLocation);
    CHECK_EQUAL(panel.getBlockCount               (), blockCount               );
    CHECK_EQUAL(panel.getCellCount                (), cellCount                );
    CHECK_EQUAL(panel.getProspectCount            (), prospectCount            );
    CHECK_EQUAL(panel.getCreationTime             (), creationTime             );
    CHECK_EQUAL(panel.getLatestBlockTime          (), latestBlockTime          );
    CHECK_EQUAL(panel.getLatestProspectTime       (), latestProspectTime       );
}

// end PanelTest.cpp
