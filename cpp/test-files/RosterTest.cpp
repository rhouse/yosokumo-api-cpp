// RosterTest.cpp  -  Test the Roster class with UnitTest++

#include "UnitTest++.h"

#include "Roster.h"

#include <iostream>
#include <sstream>
#include <algorithm>
#include <iomanip>

using namespace Yosokumo;

TEST(defaultConstructorForRoster)
{
    std::cout << "Roster defaultConstructorForRoster" << '\n';

    Roster roster;

    CHECK(roster.getStudyIdentifier() == "");
    CHECK(roster.getStudyName()       == "");
    CHECK(roster.getRosterLocation()  == "");
    CHECK(roster.size()               == 0);
}

TEST(usualConstructorForRoster)
{
    std::cout << "Roster usualConstructorForRoster" << '\n';

    std::string studyIdentifier = "my study identifier";
    std::string studyName       = "my study name";

    Roster roster(studyIdentifier, studyName);

    CHECK(roster.getStudyIdentifier() == studyIdentifier);
    CHECK(roster.getStudyName()       == studyName);
    CHECK(roster.getRosterLocation()  == "");
    CHECK(roster.size()               == 0);
}

TEST(settersAndGettersForRoster)
{
    std::cout << "Roster settersAndGettersForRoster" << '\n';

    std::string studyIdentifier = "my study identifier 2";
    std::string studyName       = "my study name 2";
    std::string studyLocation   = "my study location 2";

    Roster roster;

    roster.setStudyIdentifier (studyIdentifier);
    roster.setStudyName       (studyName);
    roster.setRosterLocation  (studyLocation);

    CHECK(roster.getStudyIdentifier() == studyIdentifier);
    CHECK(roster.getStudyName()       == studyName);
    CHECK(roster.getRosterLocation()  == studyLocation);
}

TEST(basicAccessToRoleCollectionForRoster)
{
    std::cout << "Roster basicAccessToRoleCollectionForRoster" << '\n';

    std::string userIdentifier1  = "user identifier 1";
    std::string studyIdentifier1 = "study identifier 1";

    std::string userIdentifier2  = "user identifier 2";
    std::string studyIdentifier2 = "study identifier 2";

    std::string userIdentifier3  = "user identifier 3";
    std::string studyIdentifier3 = "study identifier 3";

    Role role1(userIdentifier1, studyIdentifier1);
    Role role2(userIdentifier2, studyIdentifier2);
    Role role3(userIdentifier3, studyIdentifier3);

    std::string rosterStudyIdentifier = "roster study identifier";
    std::string rosterStudyName       = "roster study name";

    Roster roster(rosterStudyIdentifier, rosterStudyName);

    Role r;

    // test addRole, getRole, containsRole, size, and isEmpty

    CHECK(roster.isEmpty());

    CHECK(roster.addRole(role1));
    CHECK(roster.size() == 1);
    CHECK(!roster.isEmpty());
    CHECK(roster.getRole(userIdentifier1, r));
    CHECK(r == role1);
    CHECK(roster.containsRole(userIdentifier1));

    CHECK(roster.addRole(role2));
    CHECK(roster.size() == 2);
    CHECK(!roster.isEmpty());
    CHECK(roster.getRole(userIdentifier2, r));
    CHECK(r == role2);
    CHECK(roster.containsRole(userIdentifier2));

    CHECK(roster.addRole(role3));
    CHECK(roster.size() == 3);
    CHECK(!roster.isEmpty());
    CHECK(roster.getRole(userIdentifier3, r));
    CHECK(r == role3);
    CHECK(roster.containsRole(userIdentifier3));

    CHECK(!roster.addRole(role3));
    CHECK(roster.size() == 3);
    CHECK(!roster.isEmpty());
    CHECK(roster.getRole(userIdentifier3, r));
    CHECK(r == role3);

    CHECK(!roster.addRole(role3, r));
    CHECK(r == role3);
    CHECK(roster.size() == 3);
    CHECK(!roster.isEmpty());
    CHECK(roster.getRole(userIdentifier3, r));
    CHECK(r == role3);

    // test removeRole and clear

    CHECK(roster.removeRole(userIdentifier3));
    CHECK(roster.size() == 2);
    CHECK(!roster.isEmpty());
    CHECK(!roster.getRole(userIdentifier3, r));
    CHECK(!roster.containsRole(userIdentifier3));

    CHECK(!roster.removeRole(userIdentifier3));
    CHECK(roster.size() == 2);
    CHECK(!roster.isEmpty());
    CHECK(!roster.getRole(userIdentifier3, r));

    roster.clearRoles();
    CHECK(roster.size() == 0);
    CHECK(roster.isEmpty());
    CHECK(!roster.getRole(userIdentifier3, r));

}   //  end basicAccessToRoleCollection()


TEST(advancedAccessToRoleCollectionForRoster)
{
    std::cout << "Roster advancedAccessToRoleCollectionForRoster" << '\n';

    std::string userIdentifier1  = "user identifier 1";
    std::string studyIdentifier1 = "study identifier 1";

    std::string userIdentifier2  = "user identifier 2";
    std::string studyIdentifier2 = "study identifier 2";

    std::string userIdentifier3  = "user identifier 3";
    std::string studyIdentifier3 = "study identifier 3";

    Role role1(userIdentifier1, studyIdentifier1);
    Role role2(userIdentifier2, studyIdentifier2);
    Role role3(userIdentifier3, studyIdentifier3);

    std::string rosterStudyIdentifier = "roster study identifier";
    std::string rosterStudyName       = "roster study name";

    Roster roster(rosterStudyIdentifier, rosterStudyName);

    CHECK(roster.addRole(role1));
    CHECK(roster.addRole(role2));
    CHECK(roster.addRole(role3));

    // test RoleIterator, begin(), and end()

    Roster::RoleIterator iter;

    int i = 0;
 
    for (iter = roster.begin();  iter != roster.end();  ++iter)
    {
        Role role = iter->second;

        std::string t = role.getUserIdentifier();

        switch (++i)
        {
        case 1:  CHECK(t == userIdentifier1);  break;
        case 2:  CHECK(t == userIdentifier2);  break;
        case 3:  CHECK(t == userIdentifier3);  break;
        default: CHECK(false);
        }
    }

    CHECK(i == 3);

}   //  end advancedAccessToRoleCollection


static std::string makeUserId(int n)
{
    // Return a 16-character string of the form 9Zd, where 9 is a 
    // sequence of 9's and d is n as digits:

    std::stringstream s;

    s << std::setw(16) << -n;

    std::string t = s.str();
    std::replace( t.begin(), t.end(), '-', 'Z');
    std::replace( t.begin(), t.end(), ' ', '9');

    return t;
}


TEST(stressTestAccessToRoleCollectionForRoster)
{
    std::cout << "Roster stressTestAccessToRoleCollectionForRoster" << '\n';

    int numRoles = 2000;

    Roster roster;

    // Create a bunch of roles and put them in a roster

    for (int i = 1;  i <= numRoles;  i++)
    {
        Role role(makeUserId(i), "study id");
        Role s;
        CHECK(roster.addRole(role, s));
    }

    CHECK(roster.size() == numRoles);

    // Make sure all the roles can be found

    for (int i = numRoles;  i > 0 ;  i--)
    {
        std::string userId = makeUserId(i);
        Role role;
        CHECK(roster.getRole(userId, role));
        CHECK(role.getUserIdentifier() == userId);
    }

    // Remove each role from the roster

    for (int i = 1;  i <= numRoles;  i++)
    {
        std::string userId = makeUserId(i);
        CHECK(roster.removeRole(userId));
        Role role;
        CHECK(!roster.getRole(userId, role));
    }

    CHECK(roster.isEmpty());

}   //  end stressTestAccessToRoleCollection

//  end RosterTest.cpp
