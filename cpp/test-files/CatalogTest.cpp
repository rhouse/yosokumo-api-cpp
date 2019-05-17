// CatalogTest.cpp  -  Test the Catalog class with UnitTest++

#include "UnitTest++.h"

#include "Catalog.h"

#include <iostream>
#include <sstream>
#include <algorithm>
#include <iomanip>

using namespace Yosokumo;


TEST(defaultConstructorForCatalog)
{
    std::cout << "Catalog defaultConstructorForCatalog" << '\n';

    Catalog catalog;
    CHECK(catalog.getUserIdentifier()  == "ABCDEF0123456789");
    CHECK(catalog.getUserName()        == "");
    CHECK(catalog.getCatalogLocation() == "");
    CHECK(catalog.size()               == 0);
}

TEST(usualConstructorForCatalog)
{
    std::cout << "Catalog usualConstructorForCatalog" << '\n';

    Catalog catalog("1234567890abcdef", "User name");
    CHECK(catalog.getUserIdentifier()  == "1234567890abcdef");
    CHECK(catalog.getUserName()        == "User name");
    CHECK(catalog.getCatalogLocation() == "");
    CHECK(catalog.size()               == 0);
}

TEST(settersAndGettersForCatalog)
{
    std::cout << "Catalog settersAndGettersForCatalog" << '\n';

    Catalog catalog;

    catalog.setUserIdentifier ("user8Identifier9");
    catalog.setUserName       ("user name");
    catalog.setCatalogLocation("catalog location");

    CHECK(catalog.getUserIdentifier()  == "user8Identifier9");
    CHECK(catalog.getUserName()        == "user name");
    CHECK(catalog.getCatalogLocation() == "catalog location");
}


TEST(basicAccessToStudyCollectionForCatalog)
{
    std::cout << "Catalog basicAccessToStudyCollectionForCatalog" << '\n';

    Study study1(
        "Study1 name", 
        Study::RANK, 
        Study::STANDBY,
        Study::PUBLIC);
    study1.setStudyIdentifier("9999999999999991");

    Study study2(
        "Study2 name", 
        Study::NUMBER, 
        Study::STOPPED,
        Study::PRIVATE);
    study2.setStudyIdentifier("9999999999999992");

    Study study3(
        "Study3 name", 
        Study::CHANCE, 
        Study::RUNNING,
        Study::PUBLIC);
    study3.setStudyIdentifier("9999999999999993");

    Catalog catalog("userIdentifier", "user name");
    Study s;

    // test addStudy, getStudy, containsStudy, size, and isEmpty

    CHECK(catalog.isEmpty());

    CHECK(catalog.addStudy(study1));
    CHECK(catalog.size() == 1);
    CHECK(!catalog.isEmpty());
    CHECK(catalog.getStudy("9999999999999991", s));
    CHECK(s == study1);
    CHECK(catalog.containsStudy("9999999999999991"));

    CHECK(catalog.addStudy(study2));
    CHECK(catalog.size() == 2);
    CHECK(!catalog.isEmpty());
    CHECK(catalog.getStudy("9999999999999992", s));
    CHECK(s == study2);
    CHECK(catalog.containsStudy("9999999999999992"));

    CHECK(catalog.addStudy(study3));
    CHECK(catalog.size() == 3);
    CHECK(!catalog.isEmpty());
    CHECK(catalog.getStudy("9999999999999993", s));
    CHECK(s == study3);
    CHECK(catalog.containsStudy("9999999999999993"));

    CHECK(!catalog.addStudy(study3, s));
    CHECK(s == study3);
    CHECK(catalog.size() == 3);
    CHECK(!catalog.isEmpty());
    CHECK(catalog.getStudy("9999999999999993", s));
    CHECK(s == study3);

    // test removeStudy and clear

    CHECK(catalog.removeStudy("9999999999999993"));
    CHECK(catalog.size() == 2);
    CHECK(!catalog.isEmpty());
    CHECK(!catalog.getStudy("9999999999999993", s));
    CHECK(!catalog.containsStudy("9999999999999993"));

    CHECK(!catalog.removeStudy("9999999999999993"));
    CHECK(catalog.size() == 2);
    CHECK(!catalog.isEmpty());
    CHECK(!catalog.getStudy("9999999999999993", s));

    catalog.clearStudies();
    CHECK(catalog.size() == 0);
    CHECK(catalog.isEmpty());
    CHECK(!catalog.getStudy("9999999999999993", s));

}   //  end basicAccessToStudyCollection()


TEST(advancedAccessToStudyCollectionForCatalog)
{
    std::cout << "Catalog advancedAccessToStudyCollectionForCatalog" << '\n';

    std::string studyIdentifier1 = "9999999999999991";
    std::string studyIdentifier2 = "9999999999999992";
    std::string studyIdentifier3 = "9999999999999993";

    Study study1(
        "Study1 name", 
        Study::RANK, 
        Study::STANDBY,
        Study::PUBLIC);
    study1.setStudyIdentifier(studyIdentifier1);

    Study study2(
        "Study2 name", 
        Study::NUMBER, 
        Study::STOPPED,
        Study::PRIVATE);
    study2.setStudyIdentifier(studyIdentifier2);

    Study study3(
        "Study3 name", 
        Study::CHANCE, 
        Study::RUNNING,
        Study::PUBLIC);
    study3.setStudyIdentifier(studyIdentifier3);

    Catalog catalog("userIdentifier", "user name");
    Study s;

    CHECK(catalog.addStudy(study1));
    CHECK(catalog.addStudy(study2));
    CHECK(catalog.addStudy(study3));

    // test StudyIterator, begin(), and end()

    Catalog::StudyIterator iter;

    int i = 0;
 
    for (iter = catalog.begin();  iter != catalog.end();  ++iter)
    {
        Study study = iter->second;

        std::string t = study.getStudyIdentifier();

        switch (++i)
        {
        case 1:  CHECK(t == studyIdentifier1);  break;
        case 2:  CHECK(t == studyIdentifier2);  break;
        case 3:  CHECK(t == studyIdentifier3);  break;
        default: CHECK(false);
        }
    }

    CHECK(i == 3);

}   //  end advancedAccessToStudyCollection


static std::string makeStudyId(int n)
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


TEST(stressTestAccessToStudyCollectionForCatalog)
{
    std::cout << "Catalog stressTestAccessToStudyCollectionForCatalog" << '\n';

    int numStudies = 2000;

    Catalog catalog;

    // Create a bunch of studies and put them in a catalog

    for (int i = 1;  i <= numStudies;  i++)
    {
        Study study(
            "study name", 
            Study::RANK, 
            Study::STANDBY,
            Study::PUBLIC);
        study.setStudyIdentifier(makeStudyId(i));

        CHECK(catalog.addStudy(study));
    }

    CHECK(catalog.size() == numStudies);

    // Make sure all the studies can be found

    for (int i = numStudies;  i > 0 ;  i--)
    {
        std::string studyId = makeStudyId(i);
        Study study;
        CHECK(catalog.getStudy(studyId, study));
        CHECK(study.getStudyIdentifier() == studyId);
    }

    // Remove each study from the catalog

    for (int i = 1;  i <= numStudies;  i++)
    {
        std::string studyId = makeStudyId(i);
        CHECK(catalog.removeStudy(studyId));
        Study study;
        CHECK(!catalog.getStudy(studyId, study));
    }

    CHECK(catalog.isEmpty());

}   //  end stressTestAccessToStudyCollection


// end CatalogTest.cpp
