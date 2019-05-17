// PrivilegeTest.cpp  -  Test the Privilege class

#include "UnitTest++.h"

#include "Privilege.h"

#include <iostream>

using namespace Yosokumo;

TEST(allMethodsForPrivilege)
{
    std::cout << "Privilege allMethodsForPrivilege" << '\n';

    Privilege p01(Privilege::GET_STUDY   );
    Privilege p02(Privilege::DELETE_STUDY);
    Privilege p03(Privilege::GET_ROSTER  );
    Privilege p04(Privilege::POST_ROSTER );
    Privilege p05(Privilege::GET_ROLE    );
    Privilege p06(Privilege::PUT_ROLE    );
    Privilege p07(Privilege::DELETE_ROLE );
    Privilege p08(Privilege::GET_PANEL   );
    Privilege p09(Privilege::GET_CONTROL );
    Privilege p10(Privilege::PUT_CONTROL );
    Privilege p11(Privilege::POST_TABLE  );
    Privilege p12(Privilege::GET_MODEL   );
    Privilege p13(Privilege::POST_MODEL  );

    CHECK_EQUAL(Privilege::valueOf(Privilege::GET_STUDY   ), p01.getNumber());
    CHECK_EQUAL(Privilege::valueOf(Privilege::DELETE_STUDY), p02.getNumber());
    CHECK_EQUAL(Privilege::valueOf(Privilege::GET_ROSTER  ), p03.getNumber());
    CHECK_EQUAL(Privilege::valueOf(Privilege::POST_ROSTER ), p04.getNumber());
    CHECK_EQUAL(Privilege::valueOf(Privilege::GET_ROLE    ), p05.getNumber());
    CHECK_EQUAL(Privilege::valueOf(Privilege::PUT_ROLE    ), p06.getNumber());
    CHECK_EQUAL(Privilege::valueOf(Privilege::DELETE_ROLE ), p07.getNumber());
    CHECK_EQUAL(Privilege::valueOf(Privilege::GET_PANEL   ), p08.getNumber());
    CHECK_EQUAL(Privilege::valueOf(Privilege::GET_CONTROL ), p09.getNumber());
    CHECK_EQUAL(Privilege::valueOf(Privilege::PUT_CONTROL ), p10.getNumber());
    CHECK_EQUAL(Privilege::valueOf(Privilege::POST_TABLE  ), p11.getNumber());
    CHECK_EQUAL(Privilege::valueOf(Privilege::GET_MODEL   ), p12.getNumber());
    CHECK_EQUAL(Privilege::valueOf(Privilege::POST_MODEL  ), p13.getNumber());

    CHECK(Privilege::NUMBER_OF_PRIVILEGES == 13);
}

// end PrivilegeTest.cpp
