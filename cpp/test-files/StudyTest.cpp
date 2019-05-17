// StudyTest.cpp  -  Test the Study class with UnitTest++

#include "UnitTest++.h"
#include "Study.h"

#include <iostream>

using namespace Yosokumo;

static void setAllStudyMembers(Study &s)
{
    s.setBlockCount               (123456);
    s.setCellCount                (7890);
    s.setCreationTime             ("creation time");
    s.setLatestBlockTime          ("latest block time");
    s.setLatestProspectTime       ("latest prospect time");
    s.setModelLocation            ("model location");
    s.setNameControlLocation      ("name control location");
    s.setOwnerIdentifier          ("owner identifier");
    s.setOwnerName                ("owner name");
    s.setPanelLocation            ("panel location");
    s.setProspectCount            (1234567890);
    s.setRosterLocation           ("roster location");
    s.setStatus                   (Study::STOPPED);
    s.setStatusControlLocation    ("status control location");
    s.setStudyIdentifier          ("study identifier");
    s.setStudyLocation            ("study location");
    s.setStudyName                ("study name");
    s.setTableLocation            ("table location");
    s.setType                     (Study::CHANCE);
    s.setVisibility               (Study::PUBLIC);
    s.setVisibilityControlLocation("visibility control location");
}

static void checkAllStudyMembers(const Study &s)
{
    CHECK_EQUAL(s.getBlockCount                (), 123456UL);
    CHECK_EQUAL(s.getCellCount                 (), 7890UL);
    CHECK_EQUAL(s.getCreationTime              (), "creation time");
    CHECK_EQUAL(s.getLatestBlockTime           (), "latest block time");
    CHECK_EQUAL(s.getLatestProspectTime        (), "latest prospect time");
    CHECK_EQUAL(s.getModelLocation             (), "model location");
    CHECK_EQUAL(s.getNameControlLocation       (), "name control location");
    CHECK_EQUAL(s.getOwnerIdentifier           (), "owner identifier");
    CHECK_EQUAL(s.getOwnerName                 (), "owner name");
    CHECK_EQUAL(s.getPanelLocation             (), "panel location");
    CHECK_EQUAL(s.getProspectCount             (), 1234567890UL);
    CHECK_EQUAL(s.getRosterLocation            (), "roster location");
    CHECK_EQUAL(s.getStatus                    (), Study::STOPPED);
    CHECK_EQUAL(s.getStatusControlLocation     (), "status control location");
    CHECK_EQUAL(s.getStudyIdentifier           (), "study identifier");
    CHECK_EQUAL(s.getStudyLocation             (), "study location");
    CHECK_EQUAL(s.getStudyName                 (), "study name");
    CHECK_EQUAL(s.getTableLocation             (), "table location");
    CHECK_EQUAL(s.getType                      (), Study::CHANCE);
    CHECK_EQUAL(s.getVisibility                (), Study::PUBLIC);
    CHECK_EQUAL(s.getVisibilityControlLocation (), 
                                            "visibility control location");
}

static void verifyAllMembers(
    const Study       &S,
    const std::string &n,
    Study::Type        t, 
    Study::Status      s,
    Study::Visibility  v)
{
    CHECK_EQUAL(S.getStudyIdentifier           (), "");
    CHECK_EQUAL(S.getStudyName                 (),  n);
    CHECK_EQUAL(S.getStudyLocation             (), "");
    CHECK_EQUAL(S.getType                      (),  t);
    CHECK_EQUAL(S.getStatus                    (),  s);
    CHECK_EQUAL(S.getVisibility                (),  v);
    CHECK_EQUAL(S.getOwnerIdentifier           (), "");
    CHECK_EQUAL(S.getOwnerName                 (), "");
    CHECK_EQUAL(S.getTableLocation             (), "");
    CHECK_EQUAL(S.getModelLocation             (), "");
    CHECK_EQUAL(S.getPanelLocation             (), "");
    CHECK_EQUAL(S.getRosterLocation            (), "");
    CHECK_EQUAL(S.getNameControlLocation       (), "");
    CHECK_EQUAL(S.getStatusControlLocation     (), "");
    CHECK_EQUAL(S.getVisibilityControlLocation (), "");
    CHECK_EQUAL(S.getBlockCount                (),  0UL);
    CHECK_EQUAL(S.getCellCount                 (),  0UL);
    CHECK_EQUAL(S.getProspectCount             (),  0UL);
    CHECK_EQUAL(S.getCreationTime              (), "");
    CHECK_EQUAL(S.getLatestBlockTime           (), "");
    CHECK_EQUAL(S.getLatestProspectTime        (), "");
}

TEST(defaultConstructorForStudy)
{
    std::cout << "StudyTest defaultConstructorForStudy" << '\n';

    Study study;

    verifyAllMembers(
        study,
        "", 
        Study::NUMBER, 
        Study::RUNNING, 
        Study::PRIVATE);
}

TEST(usualConstructorForStudy)
{
    std::cout << "StudyTest usualConstructorForStudy" << '\n';

    Study study(
        "Study name",
        Study::RANK, 
        Study::STANDBY,
        Study::PUBLIC);

    verifyAllMembers(
        study,
        "Study name",
        Study::RANK, 
        Study::STANDBY,
        Study::PUBLIC);
}

TEST(copyConstructorForStudy)
{
    std::cout << "StudyTest usualConstructorForStudy" << '\n';

    Study study(
        "Study name",
        Study::CLASS, 
        Study::STANDBY,
        Study::PUBLIC);

    verifyAllMembers(
        study,
        "Study name",
        Study::CLASS, 
        Study::STANDBY,
        Study::PUBLIC);

    Study study2(study);

    verifyAllMembers(
        study2,
        "Study name",
        Study::CLASS, 
        Study::STANDBY,
        Study::PUBLIC);

    setAllStudyMembers(study);
    checkAllStudyMembers(study);

    Study study3(study);

    checkAllStudyMembers(study3);
}

TEST(settersAndGettersForStudy)
{
    std::cout << "StudyTest settersAndGettersForStudy" << '\n';

    Study study;

    setAllStudyMembers(study);
    checkAllStudyMembers(study);
}

TEST(assignmentOperatorForStudy)
{
    std::cout << "StudyTest assignmentOperatorForStudy" << '\n';

    Study study, study2;

    setAllStudyMembers(study);
    checkAllStudyMembers(study);

    study2 = study;
    checkAllStudyMembers(study2);
}

TEST(equalityOperatorsForStudy)
{
    std::cout << "StudyTest equalityOperatorsForStudy" << '\n';

    Study study, study2;

    setAllStudyMembers(study);
    checkAllStudyMembers(study);

    setAllStudyMembers(study2);
    checkAllStudyMembers(study2);

    CHECK(study == study2);

    study2.setLatestProspectTime("some other time");
    CHECK(study != study2);
}

TEST(toStringForStudy)
{
    std::cout << "StudyTest toStringForStudy" << '\n';

    Study study;

    setAllStudyMembers(study);
    checkAllStudyMembers(study);

    std::string expected = 
        "Study:\n"
        "  studyIdentifier          = study identifier\n"
        "  studyName                = study name\n"
        "  studyLocation            = study location\n"
        "\n"
        "  type                     = 3\n"
        "  status                   = 2\n"
        "  visibility               = 1\n"
        "\n"
        "  ownerIdentifier          = owner identifier\n"
        "  ownerName                = owner name\n"
        "  tableLocation            = table location\n"
        "  modelLocation            = model location\n"
        "  panelLocation            = panel location\n"
        "  rosterLocation           = roster location\n"
        "\n"
        "  nameControlLocation      = name control location\n"
        "  statusControlLocation    = status control location\n"
        "  visibilityControlLocation= visibility control location\n"
        "\n"
        "  blockCount               = 123456\n"
        "  cellCount                = 7890\n"
        "  prospectCount            = 1234567890\n"
        "\n"
        "  creationTime             = creation time\n"
        "  latestBlockTime          = latest block time\n"
        "  latestProspectTime       = latest prospect time\n"
    ;

    std::string actual = study.toString();

    CHECK_EQUAL(actual, expected);
}

// end StudyTest.cpp
