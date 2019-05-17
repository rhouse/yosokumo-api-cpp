// RoleTest.cpp  -  Test the Role class with UnitTest++

#include "UnitTest++.h"

#include "Role.h"

#include <iostream>

using namespace Yosokumo;

bool allPrivileges(const Role &role)
{
    CHECK(role.getPrivilege(Privilege::GET_STUDY   ));
    CHECK(role.getPrivilege(Privilege::DELETE_STUDY));
    CHECK(role.getPrivilege(Privilege::GET_ROSTER  ));
    CHECK(role.getPrivilege(Privilege::POST_ROSTER ));
    CHECK(role.getPrivilege(Privilege::GET_ROLE    ));
    CHECK(role.getPrivilege(Privilege::PUT_ROLE    ));
    CHECK(role.getPrivilege(Privilege::DELETE_ROLE ));
    CHECK(role.getPrivilege(Privilege::GET_PANEL   ));
    CHECK(role.getPrivilege(Privilege::GET_CONTROL ));
    CHECK(role.getPrivilege(Privilege::PUT_CONTROL ));
    CHECK(role.getPrivilege(Privilege::POST_TABLE  ));
    CHECK(role.getPrivilege(Privilege::GET_MODEL   ));
    CHECK(role.getPrivilege(Privilege::POST_MODEL  ));

    return true;
}

bool noPrivileges(const Role &role)
{
    CHECK(!role.getPrivilege(Privilege::GET_STUDY   ));
    CHECK(!role.getPrivilege(Privilege::DELETE_STUDY));
    CHECK(!role.getPrivilege(Privilege::GET_ROSTER  ));
    CHECK(!role.getPrivilege(Privilege::POST_ROSTER ));
    CHECK(!role.getPrivilege(Privilege::GET_ROLE    ));
    CHECK(!role.getPrivilege(Privilege::PUT_ROLE    ));
    CHECK(!role.getPrivilege(Privilege::DELETE_ROLE ));
    CHECK(!role.getPrivilege(Privilege::GET_PANEL   ));
    CHECK(!role.getPrivilege(Privilege::GET_CONTROL ));
    CHECK(!role.getPrivilege(Privilege::PUT_CONTROL ));
    CHECK(!role.getPrivilege(Privilege::POST_TABLE  ));
    CHECK(!role.getPrivilege(Privilege::GET_MODEL   ));
    CHECK(!role.getPrivilege(Privilege::POST_MODEL  ));

    return true;
}

TEST(defaultConstructorForRole)
{
    std::cout << "Role defaultConstructorForRole" << '\n';

    Role role("", "");

    CHECK(role.getRoleLocation()    == "");
    CHECK(role.getUserIdentifier()  == "");
    CHECK(role.getUserName()        == "");
    CHECK(role.getStudyIdentifier() == "");
    CHECK(role.getStudyName()       == "");

    CHECK(noPrivileges(role));
}

TEST(userIdentifierConstructorForRole)
{
    std::cout << "Role userIdentifierConstructorForRole" << '\n';

    std::string userId = "user identifier 1";

    Role role(userId, "");

    CHECK(role.getRoleLocation()    == "");
    CHECK(role.getUserIdentifier()  == userId);
    CHECK(role.getUserName()        == "");
    CHECK(role.getStudyIdentifier() == "");
    CHECK(role.getStudyName()       == "");

    CHECK(noPrivileges(role));
}

TEST(userAndStudyIdentifierConstructorForRole)
{
    std::cout << "Role userAndStudyIdentifierConstructorForRole" << '\n';

    std::string userId   = "user identifier 2";
    std::string studyId  = "study identifier 2";

    Role role(userId, studyId);

    CHECK(role.getRoleLocation()    == "");
    CHECK(role.getUserIdentifier()  == userId);
    CHECK(role.getUserName()        == "");
    CHECK(role.getStudyIdentifier() == studyId);
    CHECK(role.getStudyName()       == "");

    CHECK(noPrivileges(role));
}

TEST(settersAndGettersForRole)
{
    std::cout << "Role settersAndGettersForRole" << '\n';

    std::string location = "location 2";
    std::string userId   = "user identifier 2";
    std::string userName = "user name 2";
    std::string studyId  = "study identifier 2";
    std::string studyName= "study name 2";

    Role role("", "");

    role.setRoleLocation   (location );
    role.setUserIdentifier (userId   );
    role.setUserName       (userName );
    role.setStudyIdentifier(studyId  );
    role.setStudyName      (studyName);

    CHECK(role.getRoleLocation()    == location );
    CHECK(role.getUserIdentifier()  == userId   );
    CHECK(role.getUserName()        == userName );
    CHECK(role.getStudyIdentifier() == studyId  );
    CHECK(role.getStudyName()       == studyName);
}

TEST(addAndRemovePrivilegesForRole)
{
    std::cout << "Role addAndRemovePrivilegesForRole" << '\n';

    Role role("my user", "my study");

    role.addPrivilege        (Privilege::GET_STUDY );
    CHECK(role.getPrivilege  (Privilege::GET_STUDY));
    role.removePrivilege     (Privilege::GET_STUDY );
    CHECK(!role.getPrivilege (Privilege::GET_STUDY));

    role.addPrivilege        (Privilege::DELETE_STUDY );
    CHECK(role.getPrivilege  (Privilege::DELETE_STUDY));
    role.removePrivilege     (Privilege::DELETE_STUDY );
    CHECK(!role.getPrivilege (Privilege::DELETE_STUDY));

    role.addPrivilege        (Privilege::GET_ROSTER );
    CHECK(role.getPrivilege  (Privilege::GET_ROSTER));
    role.removePrivilege     (Privilege::GET_ROSTER );
    CHECK(!role.getPrivilege (Privilege::GET_ROSTER));

    role.addPrivilege        (Privilege::POST_ROSTER );
    CHECK(role.getPrivilege  (Privilege::POST_ROSTER));
    role.removePrivilege     (Privilege::POST_ROSTER );
    CHECK(!role.getPrivilege (Privilege::POST_ROSTER));

    role.addPrivilege        (Privilege::GET_ROLE );
    CHECK(role.getPrivilege  (Privilege::GET_ROLE));
    role.removePrivilege     (Privilege::GET_ROLE );
    CHECK(!role.getPrivilege (Privilege::GET_ROLE));

    role.addPrivilege        (Privilege::PUT_ROLE );
    CHECK(role.getPrivilege  (Privilege::PUT_ROLE));
    role.removePrivilege     (Privilege::PUT_ROLE );
    CHECK(!role.getPrivilege (Privilege::PUT_ROLE));

    role.addPrivilege        (Privilege::DELETE_ROLE );
    CHECK(role.getPrivilege  (Privilege::DELETE_ROLE));
    role.removePrivilege     (Privilege::DELETE_ROLE );
    CHECK(!role.getPrivilege (Privilege::DELETE_ROLE));

    role.addPrivilege        (Privilege::GET_PANEL );
    CHECK(role.getPrivilege  (Privilege::GET_PANEL));
    role.removePrivilege     (Privilege::GET_PANEL );
    CHECK(!role.getPrivilege (Privilege::GET_PANEL));

    role.addPrivilege        (Privilege::GET_CONTROL );
    CHECK(role.getPrivilege  (Privilege::GET_CONTROL));
    role.removePrivilege     (Privilege::GET_CONTROL );
    CHECK(!role.getPrivilege (Privilege::GET_CONTROL));

    role.addPrivilege        (Privilege::PUT_CONTROL );
    CHECK(role.getPrivilege  (Privilege::PUT_CONTROL));
    role.removePrivilege     (Privilege::PUT_CONTROL );
    CHECK(!role.getPrivilege (Privilege::PUT_CONTROL));

    role.addPrivilege        (Privilege::POST_TABLE );
    CHECK(role.getPrivilege  (Privilege::POST_TABLE));
    role.removePrivilege     (Privilege::POST_TABLE );
    CHECK(!role.getPrivilege (Privilege::POST_TABLE));

    role.addPrivilege        (Privilege::GET_MODEL );
    CHECK(role.getPrivilege  (Privilege::GET_MODEL));
    role.removePrivilege     (Privilege::GET_MODEL );
    CHECK(!role.getPrivilege (Privilege::GET_MODEL));

    role.addPrivilege        (Privilege::POST_MODEL );
    CHECK(role.getPrivilege  (Privilege::POST_MODEL));
    role.removePrivilege     (Privilege::POST_MODEL );
    CHECK(!role.getPrivilege (Privilege::POST_MODEL));

    CHECK(noPrivileges(role));
}

TEST(allAndNoPrivilegesForRole)
{
    std::cout << "Role allAndNoPrivilegesForRole" << '\n';

    Role role("my user", "my study");

    CHECK(noPrivileges(role));

    role.addAllPrivileges();
    CHECK(allPrivileges(role));

    role.removeAllPrivileges();
    CHECK(noPrivileges(role));
}

TEST(toStringForRole)
{
    std::cout << "Role toStringForRole" << '\n';

    std::string location = "location 2";
    std::string userId   = "user identifier 2";
    std::string userName = "user name 2";
    std::string studyId  = "study identifier 2";
    std::string studyName= "study name 2";

    Role role(userId, studyId);

    role.setRoleLocation   (location );
    role.setUserName       (userName );
    role.setStudyName      (studyName);

    role.addPrivilege        (Privilege::GET_STUDY );
    role.addPrivilege        (Privilege::GET_ROSTER );
    role.addPrivilege        (Privilege::GET_ROLE );
    role.addPrivilege        (Privilege::DELETE_ROLE );
    role.addPrivilege        (Privilege::GET_CONTROL );
    role.addPrivilege        (Privilege::POST_TABLE );
    role.addPrivilege        (Privilege::POST_MODEL );

    std::string expected = 
        "Role:\n"
        "  userIdentifier  = user identifier 2\n"
        "  userName        = user name 2\n"
        "\n"
        "  studyIdentifier = study identifier 2\n"
        "  studyName       = study name 2\n"
        "\n"
        "  privilegeSet\n"
        "    yes GET_STUDY\n"
        "    no  DELETE_STUDY\n"
        "    yes GET_ROSTER\n"
        "    no  POST_ROSTER\n"
        "    yes GET_ROLE\n"
        "    no  PUT_ROLE\n"
        "    yes DELETE_ROLE\n"
        "    no  GET_PANEL\n"
        "    yes GET_CONTROL\n"
        "    no  PUT_CONTROL\n"
        "    yes POST_TABLE\n"
        "    no  GET_MODEL\n"
        "    yes POST_MODEL\n"
    ;

    std::string actual = role.toString();

    CHECK_EQUAL(actual, expected);

    expected = 
        "Role:\n"
        "  userIdentifier  = user identifier 2\n"
        "  userName        = user name 2\n"
        "\n"
        "  studyIdentifier = study identifier 2\n"
        "  studyName       = study name 2\n"
        "\n"
        "  roleLocation    = location 2\n"
        "\n"
        "  privilegeSet\n"
        "    yes GET_STUDY\n"
        "    no  DELETE_STUDY\n"
        "    yes GET_ROSTER\n"
        "    no  POST_ROSTER\n"
        "    yes GET_ROLE\n"
        "    no  PUT_ROLE\n"
        "    yes DELETE_ROLE\n"
        "    no  GET_PANEL\n"
        "    yes GET_CONTROL\n"
        "    no  PUT_CONTROL\n"
        "    yes POST_TABLE\n"
        "    no  GET_MODEL\n"
        "    yes POST_MODEL\n"
    ;

    actual = role.toStringInternal(true);

    CHECK_EQUAL(actual, expected);
}

//  end RoleTest.cpp
