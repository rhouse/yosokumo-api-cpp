// YosokumoProtobufTest.cpp  -  Test the YosokumoProtobuf class

#include "UnitTest++.h"

#include "YosokumoProtobuf.h"

#include "EmptyValue.h"
#include "IntegerValue.h"
#include "NaturalValue.h"
#include "RealValue.h"
#include "SpecialValue.h"

#include "EmptyBlock.h"
#include "CellBlock.h"
#include "PredictorBlock.h"
#include "SpecimenBlock.h"

#include <iostream>

using namespace Yosokumo;

// The following functions are defined in BlockTest.cpp

void makePredictorList(std::list<Predictor> &predictorList);
void checkPredictorSequence(const PredictorBlock &block);
void makeSpecimenList(std::list<Specimen> &specimenList);
void checkSpecimenSequence(const SpecimenBlock &block);

TEST(blockMethodsForYosokumoProtobuf)
{
    std::cout << "YosokumoProtobuf blockMethodsForYosokumoProtobuf" << '\n';

    YosokumoProtobuf gpb;

  // EmptyBlock

    std::string study_id = "empty block study identifier";

    Block in_block(study_id);

    CHECK_EQUAL(in_block.getStudyIdentifier(), study_id    );
    CHECK_EQUAL(in_block.getType(),            Block::EMPTY);

    // EmptyBlock <-> protobuf conversion

    std::vector<uint8_t>blockAsBytes;

    CHECK(gpb.makeBytesFromBlock(in_block, blockAsBytes));
        
    Block out_block;

    CHECK(gpb.makeBlockFromBytes(blockAsBytes, out_block));

    CHECK_EQUAL(out_block.getStudyIdentifier(), study_id    );
    CHECK_EQUAL(out_block.getType(),            Block::EMPTY);

  // PredictorBlock

    study_id = "predictor block study identifier";

    PredictorBlock in_pblock(study_id);

    CHECK_EQUAL(in_pblock.getStudyIdentifier(), study_id        );
    CHECK_EQUAL(in_pblock.getType(),            Block::PREDICTOR);

    std::list<Predictor> predictorList;
    makePredictorList(predictorList);

    in_pblock.addPredictors(predictorList.begin(), predictorList.end());
    checkPredictorSequence(in_pblock);

    // PredictorBlock <-> protobuf conversion

    CHECK(gpb.makeBytesFromBlock(in_pblock, blockAsBytes));
    CHECK(gpb.makeBlockFromBytes(blockAsBytes, out_block));

    CHECK_EQUAL(out_block.getStudyIdentifier(), study_id    );
    CHECK_EQUAL(out_block.getType(),            Block::PREDICTOR);
    checkPredictorSequence((PredictorBlock&)out_block);

  // SpecimenBlock

    study_id = "specimen block study identifier";

    SpecimenBlock in_sblock(study_id);

    CHECK_EQUAL(in_sblock.getStudyIdentifier(), study_id        );
    CHECK_EQUAL(in_sblock.getType(),            Block::SPECIMEN);

    std::list<Specimen> specimenList;
    makeSpecimenList(specimenList);

    in_sblock.addSpecimens(specimenList.begin(), specimenList.end());
    checkSpecimenSequence(in_sblock);

    // SpecimenBlock <-> protobuf conversion

    CHECK(gpb.makeBytesFromBlock(in_sblock, blockAsBytes));
    CHECK(gpb.makeBlockFromBytes(blockAsBytes, out_block));

    CellBlock &out_cblock = (CellBlock&)out_block;

    CHECK_EQUAL(out_cblock.getStudyIdentifier(), study_id   );
    CHECK_EQUAL(out_cblock.getType(),            Block::CELL);

    CHECK_EQUAL(out_cblock.size(), in_sblock.size());

    // Check that each cell in the output block is equal to the predictand
    // of the corresponding specimen in the input block:

    for (unsigned i = 0;  i < out_cblock.size();  ++i)
    {
        Specimen *pSpecimen = in_sblock.getSpecimen(i);

        uint64_t key   = pSpecimen->getSpecimenKey();
        Value    value = pSpecimen->getPredictand();

        Cell cell = out_cblock.getCell(i);

        CHECK_EQUAL(cell.getKey(),   key);
        CHECK(cell.getValue() == value);
    }

}   //  end blockMethodsForYosokumoProtobuf


TEST(catalogMethodsForYosokumoProtobuf)
{
    std::cout << "YosokumoProtobuf catalogMethodsForYosokumoProtobuf" << '\n';

    YosokumoProtobuf gpb;

    // Define a Catalog

    std::string user_id   = "the catalog user identifier";
    std::string user_name = "the catalog user name";
    std::string loc       = "the catalog location";

    Catalog in_catalog(user_id, user_name);
    in_catalog.setCatalogLocation(loc);

    CHECK_EQUAL(in_catalog.getUserIdentifier(),  user_id  );
    CHECK_EQUAL(in_catalog.getUserName(),        user_name);
    CHECK_EQUAL(in_catalog.getCatalogLocation(), loc      );
    CHECK_EQUAL(in_catalog.size(),               0        );

    // Catalog <-> protobuf conversion

    std::vector<uint8_t>catalogAsBytes;

    CHECK(gpb.makeBytesFromCatalog(in_catalog, catalogAsBytes));
        
    Catalog out_catalog;

    CHECK(gpb.makeCatalogFromBytes(catalogAsBytes, out_catalog));

    CHECK_EQUAL(out_catalog.getUserIdentifier(),  user_id  );
    CHECK_EQUAL(out_catalog.getUserName(),        user_name);
    CHECK_EQUAL(out_catalog.getCatalogLocation(), loc      );
    CHECK_EQUAL(out_catalog.size(),               0        );

    // Define Study's and add to the catalog

    std::string name1             = "the first study name";
    std::string id1               = "the first study identifier";
    Study::Type type1             = Study::CLASS;
    Study::Status status1         = Study::RUNNING;
    Study::Visibility visibility1 = Study::PRIVATE;

    Study study1(name1, type1, status1, visibility1);
    study1.setStudyIdentifier(id1);

    CHECK(in_catalog.addStudy(study1));

    std::string name2             = "the second study name";
    std::string id2               = "the second study identifier";
    Study::Type type2             = Study::RANK;
    Study::Status status2         = Study::STANDBY;
    Study::Visibility visibility2 = Study::PUBLIC;

    Study study2(name2, type2, status2, visibility2);
    study2.setStudyIdentifier(id2);

    CHECK(in_catalog.addStudy(study2));

    CHECK_EQUAL(in_catalog.size(), 2);

    // Catalog <-> protobuf conversion

    CHECK(gpb.makeBytesFromCatalog(in_catalog, catalogAsBytes));

    CHECK(gpb.makeCatalogFromBytes(catalogAsBytes, out_catalog));

    CHECK(in_catalog == out_catalog);

}   //  end catalogMethodsForYosokumoProtobuf


TEST(cellMethodsForYosokumoProtobuf)
{
    std::cout << "YosokumoProtobuf cellMethodsForYosokumoProtobuf" << '\n';

    YosokumoProtobuf gpb;

    // Define a Cell

    uint64_t name = 1234;
    IntegerValue intval(314159);

    Cell in_cell(name, intval);

    CHECK(in_cell.getName()  ==  name);
    CHECK(in_cell.getValue() == intval);

    // Cell <-> protobuf conversion

    std::vector<uint8_t>cellAsBytes;

    CHECK(gpb.makeBytesFromCell(in_cell, cellAsBytes));
        
    Cell out_cell(987654321, EmptyValue());

    CHECK(gpb.makeCellFromBytes(cellAsBytes, out_cell));

    CHECK(in_cell == out_cell);

    // Try all value types

    NaturalValue natval(314158);
    in_cell.setValue(natval);
    CHECK(gpb.makeBytesFromCell(in_cell, cellAsBytes));
    CHECK(gpb.makeCellFromBytes(cellAsBytes, out_cell));
    CHECK(in_cell == out_cell);

    SpecialValue specval(314157);
    in_cell.setValue(specval);
    CHECK(gpb.makeBytesFromCell(in_cell, cellAsBytes));
    CHECK(gpb.makeCellFromBytes(cellAsBytes, out_cell));
    CHECK(in_cell == out_cell);

    RealValue realval(3.14159);
    in_cell.setValue(realval);
    CHECK(gpb.makeBytesFromCell(in_cell, cellAsBytes));
    CHECK(gpb.makeCellFromBytes(cellAsBytes, out_cell));
    CHECK(in_cell == out_cell);

    EmptyValue emptyval;
    in_cell.setValue(emptyval);
    CHECK(gpb.makeBytesFromCell(in_cell, cellAsBytes));
    CHECK(gpb.makeCellFromBytes(cellAsBytes, out_cell));
    CHECK(in_cell == out_cell);

}   //  end cellMethodsForYosokumoProtobuf


TEST(messageMethodsForYosokumoProtobuf)
{
    std::cout << "YosokumoProtobuf messageMethodsForYosokumoProtobuf" << '\n';

    YosokumoProtobuf gpb;

    // Define a Message

    std::string text   = "the message text";
    Message::Type type = Message::INFORMATION;

    Message in_message(type, text);

    CHECK_EQUAL(in_message.getText(), text);
    CHECK_EQUAL(in_message.getType(), type);

    // Message <-> protobuf conversion

    std::vector<uint8_t>messageAsBytes;

    CHECK(gpb.makeBytesFromMessage(in_message, messageAsBytes));
        
    Message out_message;

    CHECK(gpb.makeMessageFromBytes(messageAsBytes, out_message));

    CHECK_EQUAL(out_message.getText(), text);
    CHECK_EQUAL(out_message.getType(), type);

    // Try all enum values

    type = Message::ERROR;

    in_message.setType(type);

    CHECK(gpb.makeBytesFromMessage(in_message, messageAsBytes));
    CHECK(gpb.makeMessageFromBytes(messageAsBytes, out_message));

    CHECK_EQUAL(out_message.getType(), type);

    // Provoke an error

    type = Message::Type(100);

    in_message.setType(type);

    CHECK(!gpb.isException());

    bool ok = gpb.makeBytesFromMessage(in_message, messageAsBytes);

    if (ok)
    {
        CHECK(false);
    }
    else
    {
        CHECK(gpb.isException());
        ServiceException e;
        CHECK(gpb.getException(e));
        CHECK(e.getStatusCode() == 0);
        CHECK(strcmp(e.what(), "Message::Type is invalid") == 0);
        CHECK_EQUAL(e.getFailedMethodName(), 
            "typeToProtobufType:  Message::Type -> ProtoBuf::Message_Type");
        gpb.clearException();
        CHECK(!gpb.isException());
        CHECK(!gpb.getException(e));
    }

}   //  end messageMethodsForYosokumoProtobuf


TEST(panelMethodsForYosokumoProtobuf)
{
    std::cout << "YosokumoProtobuf panelMethodsForYosokumoProtobuf" << '\n';

    YosokumoProtobuf gpb;

    // Define a Panel

    std::string nameControlLocation       = "name location";
    std::string statusControlLocation     = "status location";
    std::string visibilityControlLocation = "visibility location";

    uint64_t blockCount    =  123;
    uint64_t cellCount     =  456;
    uint64_t prospectCount = 7890;

    std::string creationTime       = "creation time";
    std::string latestBlockTime    = "latest block time";
    std::string latestProspectTime = "latest prospect time";

    Panel in_panel;

    in_panel.setNameControlLocation(      nameControlLocation      );
    in_panel.setStatusControlLocation(    statusControlLocation    );
    in_panel.setVisibilityControlLocation(visibilityControlLocation);

    in_panel.setBlockCount(   blockCount   );
    in_panel.setCellCount(    cellCount    );
    in_panel.setProspectCount(prospectCount);

    in_panel.setCreationTime(      creationTime      );
    in_panel.setLatestBlockTime(   latestBlockTime   );
    in_panel.setLatestProspectTime(latestProspectTime);

    // Check in_panel

    CHECK_EQUAL(in_panel.getNameControlLocation(),       nameControlLocation      );
    CHECK_EQUAL(in_panel.getStatusControlLocation(),     statusControlLocation    );
    CHECK_EQUAL(in_panel.getVisibilityControlLocation(), visibilityControlLocation);

    CHECK_EQUAL(in_panel.getBlockCount(),    blockCount   );
    CHECK_EQUAL(in_panel.getCellCount(),     cellCount    );
    CHECK_EQUAL(in_panel.getProspectCount(), prospectCount);

    CHECK_EQUAL(in_panel.getCreationTime(),       creationTime      );
    CHECK_EQUAL(in_panel.getLatestBlockTime(),    latestBlockTime   );
    CHECK_EQUAL(in_panel.getLatestProspectTime(), latestProspectTime);

    // Panel <-> protobuf conversion

    std::vector<uint8_t>panelAsBytes;

    CHECK(gpb.makeBytesFromPanel(in_panel, panelAsBytes));
        
    Panel out_panel;

    out_panel.setNameControlLocation(      "old name"      );
    out_panel.setStatusControlLocation(    "old status"    );
    out_panel.setVisibilityControlLocation("old visibility");

    out_panel.setBlockCount(   111111111);
    out_panel.setCellCount(    222222222);
    out_panel.setProspectCount(333333333);

    out_panel.setCreationTime(      "old creation"       );
    out_panel.setLatestBlockTime(   "old latest block"   );
    out_panel.setLatestProspectTime("old latest prospect");

    CHECK(gpb.makePanelFromBytes(panelAsBytes, out_panel));

    // Compare in_panel and out_panel

    CHECK_EQUAL(out_panel.getNameControlLocation(),       nameControlLocation      );
    CHECK_EQUAL(out_panel.getStatusControlLocation(),     statusControlLocation    );
    CHECK_EQUAL(out_panel.getVisibilityControlLocation(), visibilityControlLocation);

    CHECK_EQUAL(out_panel.getBlockCount(),    blockCount   );
    CHECK_EQUAL(out_panel.getCellCount(),     cellCount    );
    CHECK_EQUAL(out_panel.getProspectCount(), prospectCount);

    CHECK_EQUAL(out_panel.getCreationTime(),       creationTime      );
    CHECK_EQUAL(out_panel.getLatestBlockTime(),    latestBlockTime   );
    CHECK_EQUAL(out_panel.getLatestProspectTime(), latestProspectTime);

}   //  end panelMethodsForYosokumoProtobuf


TEST(predictorMethodsForYosokumoProtobuf)
{
    std::cout << "YosokumoProtobuf predictorMethodsForYosokumoProtobuf" << '\n';

    YosokumoProtobuf gpb;

    // Define a Predictor

    Predictor in_predictor(
        987654321, 
        Predictor::ACTIVE,
        Predictor::CATEGORICAL,
        Predictor::NOMINAL);

    CHECK_EQUAL(in_predictor.getPredictorName(), 987654321);
    CHECK_EQUAL(in_predictor.getStatus()       , Predictor::ACTIVE);
    CHECK_EQUAL(in_predictor.getType()         , Predictor::CATEGORICAL);
    CHECK_EQUAL(in_predictor.getLevel()        , Predictor::NOMINAL);
                                                                  
    // Predictor <-> protobuf conversion                          

    std::vector<uint8_t>predictorAsBytes;

    CHECK(gpb.makeBytesFromPredictor(in_predictor, predictorAsBytes));
        
    Predictor out_predictor;

    CHECK(gpb.makePredictorFromBytes(predictorAsBytes, out_predictor));

    CHECK(in_predictor == out_predictor);

    // Try all enum values

    in_predictor.setStatus(Predictor::INACTIVE); 
    in_predictor.setType  (Predictor::CONTINUOUS);
    in_predictor.setLevel (Predictor::ORDINAL);
    CHECK(gpb.makeBytesFromPredictor(in_predictor, predictorAsBytes));
    CHECK(gpb.makePredictorFromBytes(predictorAsBytes, out_predictor));
    CHECK(in_predictor == out_predictor);

    in_predictor.setLevel (Predictor::INTERVAL);
    CHECK(gpb.makeBytesFromPredictor(in_predictor, predictorAsBytes));
    CHECK(gpb.makePredictorFromBytes(predictorAsBytes, out_predictor));
    CHECK(in_predictor == out_predictor);

    in_predictor.setLevel (Predictor::RATIO);
    CHECK(gpb.makeBytesFromPredictor(in_predictor, predictorAsBytes));
    CHECK(gpb.makePredictorFromBytes(predictorAsBytes, out_predictor));
    CHECK(in_predictor == out_predictor);

}   //  end predictorMethodsForYosokumoProtobuf

TEST(roleMethodsForYosokumoProtobuf)
{
    std::cout << "YosokumoProtobuf roleMethodsForYosokumoProtobuf" << '\n';

    YosokumoProtobuf gpb;

    // Define a Role

    std::string location = "location";
    std::string userId   = "user identifier";
    std::string userName = "user name";
    std::string studyId  = "study identifier";
    std::string studyName= "study name";

    Role in_role("", "");

    in_role.setRoleLocation   (location );
    in_role.setUserIdentifier (userId   );
    in_role.setUserName       (userName );
    in_role.setStudyIdentifier(studyId  );
    in_role.setStudyName      (studyName);

    in_role.addPrivilege(Privilege::GET_STUDY  );
    in_role.addPrivilege(Privilege::GET_ROSTER );
    in_role.addPrivilege(Privilege::GET_ROLE   );
    in_role.addPrivilege(Privilege::DELETE_ROLE);
    in_role.addPrivilege(Privilege::GET_CONTROL);
    in_role.addPrivilege(Privilege::POST_TABLE );
    in_role.addPrivilege(Privilege::POST_MODEL );

    // Check role fields

    CHECK(in_role.getRoleLocation()    == location );
    CHECK(in_role.getUserIdentifier()  == userId   );
    CHECK(in_role.getUserName()        == userName );
    CHECK(in_role.getStudyIdentifier() == studyId  );
    CHECK(in_role.getStudyName()       == studyName);

    CHECK( in_role.getPrivilege(Privilege::GET_STUDY   ));
    CHECK(!in_role.getPrivilege(Privilege::DELETE_STUDY));
    CHECK( in_role.getPrivilege(Privilege::GET_ROSTER  ));
    CHECK(!in_role.getPrivilege(Privilege::POST_ROSTER ));
    CHECK( in_role.getPrivilege(Privilege::GET_ROLE    ));
    CHECK(!in_role.getPrivilege(Privilege::PUT_ROLE    ));
    CHECK( in_role.getPrivilege(Privilege::DELETE_ROLE ));
    CHECK(!in_role.getPrivilege(Privilege::GET_PANEL   ));
    CHECK( in_role.getPrivilege(Privilege::GET_CONTROL ));
    CHECK(!in_role.getPrivilege(Privilege::PUT_CONTROL ));
    CHECK( in_role.getPrivilege(Privilege::POST_TABLE  ));
    CHECK(!in_role.getPrivilege(Privilege::GET_MODEL   ));
    CHECK( in_role.getPrivilege(Privilege::POST_MODEL  ));

    // Role <-> protobuf conversion

    std::vector<uint8_t>roleAsBytes;

    CHECK(gpb.makeBytesFromRole(in_role, roleAsBytes));
        
    Role out_role("", "");

    CHECK(gpb.makeRoleFromBytes(roleAsBytes, out_role));

    // Compare in_role and out_role

    CHECK(out_role.getRoleLocation()    == location );
    CHECK(out_role.getUserIdentifier()  == userId   );
    CHECK(out_role.getUserName()        == userName );
    CHECK(out_role.getStudyIdentifier() == studyId  );
    CHECK(out_role.getStudyName()       == studyName);

    CHECK( out_role.getPrivilege(Privilege::GET_STUDY   ));
    CHECK(!out_role.getPrivilege(Privilege::DELETE_STUDY));
    CHECK( out_role.getPrivilege(Privilege::GET_ROSTER  ));
    CHECK(!out_role.getPrivilege(Privilege::POST_ROSTER ));
    CHECK( out_role.getPrivilege(Privilege::GET_ROLE    ));
    CHECK(!out_role.getPrivilege(Privilege::PUT_ROLE    ));
    CHECK( out_role.getPrivilege(Privilege::DELETE_ROLE ));
    CHECK(!out_role.getPrivilege(Privilege::GET_PANEL   ));
    CHECK( out_role.getPrivilege(Privilege::GET_CONTROL ));
    CHECK(!out_role.getPrivilege(Privilege::PUT_CONTROL ));
    CHECK( out_role.getPrivilege(Privilege::POST_TABLE  ));
    CHECK(!out_role.getPrivilege(Privilege::GET_MODEL   ));
    CHECK( out_role.getPrivilege(Privilege::POST_MODEL  ));

}   //  end roleMethodsForYosokumoProtobuf

TEST(rosterMethodsForYosokumoProtobuf)
{
    std::cout << "YosokumoProtobuf rosterMethodsForYosokumoProtobuf" << '\n';

    YosokumoProtobuf gpb;

    // Define a Roster

    std::string study_id   = "the roster study identifier";
    std::string study_name = "the roster study name";
    std::string loc        = "the roster location";

    Roster in_roster(study_id, study_name);
    in_roster.setRosterLocation(loc);

    CHECK_EQUAL(in_roster.getStudyIdentifier(), study_id  );
    CHECK_EQUAL(in_roster.getStudyName(),       study_name);
    CHECK_EQUAL(in_roster.getRosterLocation(),  loc       );
    CHECK_EQUAL(in_roster.size(),               0         );

    // Roster <-> protobuf conversion

    std::vector<uint8_t>rosterAsBytes;

    CHECK(gpb.makeBytesFromRoster(in_roster, rosterAsBytes));
        
    Roster out_roster;

    CHECK(gpb.makeRosterFromBytes(rosterAsBytes, out_roster));

    CHECK_EQUAL(out_roster.getStudyIdentifier(), study_id  );
    CHECK_EQUAL(out_roster.getStudyName(),       study_name);
    CHECK_EQUAL(out_roster.getRosterLocation(),  loc       );
    CHECK_EQUAL(out_roster.size(),               0         );

    // Define Role's and add to the roster

    std::string role_location  = "role location 1";
    std::string role_userId    = "user identifier 1";
    std::string role_userName  = "user name 1";
    std::string role_studyId   = "study identifier 1";
    std::string role_studyName = "study name 1";

    Role role1("", "");

    role1.setRoleLocation   (role_location );
    role1.setUserIdentifier (role_userId   );
    role1.setUserName       (role_userName );
    role1.setStudyIdentifier(role_studyId  );
    role1.setStudyName      (role_studyName);

    role1.addPrivilege(Privilege::GET_STUDY  );
    role1.addPrivilege(Privilege::GET_ROSTER );
    role1.addPrivilege(Privilege::GET_ROLE   );
    role1.addPrivilege(Privilege::DELETE_ROLE);
    role1.addPrivilege(Privilege::GET_CONTROL);
    role1.addPrivilege(Privilege::POST_TABLE );
    role1.addPrivilege(Privilege::POST_MODEL );

    CHECK(in_roster.addRole(role1));

    role_location  = "role location 2";
    role_userId    = "user identifier 2";
    role_userName  = "user name 2";
    role_studyId   = "study identifier 2";
    role_studyName = "study name 2";

    Role role2("", "");

    role2.setRoleLocation   (role_location );
    role2.setUserIdentifier (role_userId   );
    role2.setUserName       (role_userName );
    role2.setStudyIdentifier(role_studyId  );
    role2.setStudyName      (role_studyName);

    role2.addPrivilege(Privilege::GET_STUDY   );
    role2.addPrivilege(Privilege::DELETE_STUDY);
    role2.addPrivilege(Privilege::POST_ROSTER );
    role2.addPrivilege(Privilege::PUT_ROLE    );
    role2.addPrivilege(Privilege::GET_PANEL   );
    role2.addPrivilege(Privilege::PUT_CONTROL );
    role2.addPrivilege(Privilege::GET_MODEL   );
    role2.addPrivilege(Privilege::POST_MODEL  );

    CHECK(in_roster.addRole(role2));

    CHECK_EQUAL(in_roster.size(), 2);

    // Roster <-> protobuf conversion

    CHECK(gpb.makeBytesFromRoster(in_roster, rosterAsBytes));

    CHECK(gpb.makeRosterFromBytes(rosterAsBytes, out_roster));

    CHECK(in_roster == out_roster);

}   //  end rosterMethodsForYosokumoProtobuf

TEST(specimenMethodsForYosokumoProtobuf)
{
    std::cout << "YosokumoProtobuf specimenMethodsForYosokumoProtobuf" << '\n';

    YosokumoProtobuf gpb;

    // Define a Specimen

    uint64_t         key    = 2468;
    Specimen::Status status = Specimen::ACTIVE;
    uint64_t         weight = 81726354;
    Value            value  = RealValue(2.71);

    Specimen in_specimen;

    in_specimen.setSpecimenKey(key);
    in_specimen.setStatus     (status);
    in_specimen.setWeight     (weight);
    in_specimen.setPredictand (value);

    CHECK(in_specimen.getSpecimenKey() == key   );
    CHECK(in_specimen.getStatus     () == status);
    CHECK(in_specimen.getWeight     () == weight);
    CHECK(in_specimen.getPredictand () == value );
    CHECK(in_specimen.size()           == 0     );

    // Specimen <-> protobuf conversion

    std::vector<uint8_t>specimenAsBytes;

    CHECK(gpb.makeBytesFromSpecimen(in_specimen, specimenAsBytes));
        
    Specimen out_specimen;

    CHECK(gpb.makeSpecimenFromBytes(specimenAsBytes, out_specimen));

    CHECK(out_specimen.getSpecimenKey() == key   );
    CHECK(out_specimen.getStatus     () == status);
    CHECK(out_specimen.getWeight     () == weight);
    CHECK(out_specimen.getPredictand () == value );
    CHECK(out_specimen.size()           == 0     );

    // Define Cell's and add to the specimen

    std::vector<Cell> cells;

    cells.push_back(Cell(12345678, IntegerValue(314158 )));
    cells.push_back(Cell(12345679, NaturalValue(314159 )));
    cells.push_back(Cell(12345670, RealValue   (3.14159)));
    cells.push_back(Cell(12345670, EmptyValue  (       )));
//    cell.push_back(Cell(12345671, SpecialValue(314157 )));

    std::vector<Cell>::iterator iter;

    for (iter = cells.begin();  iter != cells.end();  ++iter)
    {
        in_specimen.addCell(*iter);
    }

    CHECK(in_specimen.size() == cells.size());

    // Specimen <-> protobuf conversion

    CHECK(gpb.makeBytesFromSpecimen(in_specimen, specimenAsBytes));
    CHECK(gpb.makeSpecimenFromBytes(specimenAsBytes, out_specimen));

    CHECK(out_specimen.getSpecimenKey() == key         );
    CHECK(out_specimen.getStatus     () == status      );
    CHECK(out_specimen.getWeight     () == weight      );
    CHECK(out_specimen.getPredictand () == value       );
    CHECK(out_specimen.size()           == cells.size());

    for (unsigned i = 0;  i < in_specimen.size();  ++i)
    {
        CHECK(in_specimen.getCell(i) == out_specimen.getCell(i));
    }

}   //  end specimenMethodsForYosokumoProtobuf


TEST(studyMethodsForYosokumoProtobuf)
{
    std::cout << "YosokumoProtobuf studyMethodsForYosokumoProtobuf" << '\n';

    YosokumoProtobuf gpb;

    // Define a Study

    std::string name             = "the study name";
    std::string id               = "the study identifier";
    Study::Type type             = Study::CLASS;
    Study::Status status         = Study::RUNNING;
    Study::Visibility visibility = Study::PRIVATE;

    Study in_study(name, type, status, visibility);
    in_study.setStudyIdentifier(id);

    CHECK_EQUAL(in_study.getStudyName(),       name      );
    CHECK_EQUAL(in_study.getStudyIdentifier(), id        );
    CHECK_EQUAL(in_study.getType(),            type      );
    CHECK_EQUAL(in_study.getStatus(),          status    );
    CHECK_EQUAL(in_study.getVisibility(),      visibility);

    // Study <-> protobuf conversion

    std::vector<uint8_t>studyAsBytes;

    CHECK(gpb.makeBytesFromStudy(in_study, studyAsBytes));
        
    Study out_study;

    CHECK(gpb.makeStudyFromBytes(studyAsBytes, out_study));

    CHECK_EQUAL(out_study.getStudyName(),       name      );
    CHECK_EQUAL(out_study.getStudyIdentifier(), id        );
    CHECK_EQUAL(out_study.getType(),            type      );
    CHECK_EQUAL(out_study.getStatus(),          status    );
    CHECK_EQUAL(out_study.getVisibility(),      visibility);

    // Try all enum values

    type       = Study::RANK;
    status     = Study::STANDBY;
    visibility = Study::PUBLIC;

    in_study.setType(type);
    in_study.setStatus(status);
    in_study.setVisibility(visibility);

    CHECK(gpb.makeBytesFromStudy(in_study, studyAsBytes));
    CHECK(gpb.makeStudyFromBytes(studyAsBytes, out_study));

    CHECK_EQUAL(out_study.getType(),       type      );
    CHECK_EQUAL(out_study.getStatus(),     status    );
    CHECK_EQUAL(out_study.getVisibility(), visibility);

    type   = Study::NUMBER;
    status = Study::STOPPED;

    in_study.setType(type);
    in_study.setStatus(status);

    CHECK(gpb.makeBytesFromStudy(in_study, studyAsBytes));
    CHECK(gpb.makeStudyFromBytes(studyAsBytes, out_study));

    CHECK_EQUAL(out_study.getType(),       type      );
    CHECK_EQUAL(out_study.getStatus(),     status    );
    CHECK_EQUAL(out_study.getVisibility(), visibility);

    type = Study::CHANCE;

    in_study.setType(type);

    CHECK(gpb.makeBytesFromStudy(in_study, studyAsBytes));
    CHECK(gpb.makeStudyFromBytes(studyAsBytes, out_study));

    CHECK_EQUAL(out_study.getType(),       type      );
    CHECK_EQUAL(out_study.getStatus(),     status    );
    CHECK_EQUAL(out_study.getVisibility(), visibility);

    // Provoke an error

    type = Study::Type(100);

    in_study.setType(type);

    CHECK(!gpb.isException());

    bool ok = gpb.makeBytesFromStudy(in_study, studyAsBytes);

    if (ok)
    {
        CHECK(false);
    }
    else
    {
        CHECK(gpb.isException());
        ServiceException e;
        CHECK(gpb.getException(e));
        CHECK(e.getStatusCode() == 0);
        CHECK(strcmp(e.what(), "Study::Type is invalid") == 0);
        CHECK_EQUAL(e.getFailedMethodName(), 
            "typeToProtobufType:  Study::Type -> ProtoBuf::Study_Type");
        gpb.clearException();
        CHECK(!gpb.isException());
        CHECK(!gpb.getException(e));
    }

}   //  end studyMethodsForYosokumoProtobuf


TEST(studyNameMethodsForYosokumoProtobuf)
{
    std::cout << "YosokumoProtobuf studyNameMethodsForYosokumoProtobuf" << '\n';

    YosokumoProtobuf gpb;

    // Define a study name

    std::string in_studyName = "the study name";

    // Study name <-> protobuf conversion

    std::vector<uint8_t>studyNameAsBytes;

    CHECK(gpb.makeBytesFromStudyName(in_studyName, studyNameAsBytes));
        
    std::string out_studyName;

    CHECK(gpb.makeStudyNameFromBytes(studyNameAsBytes, out_studyName));

    CHECK_EQUAL(out_studyName, in_studyName);

}   //  end studyNameMethodsForYosokumoProtobuf


TEST(studyStatusMethodsForYosokumoProtobuf)
{
    std::cout << "YosokumoProtobuf studyStatusMethodsForYosokumoProtobuf" << '\n';

    YosokumoProtobuf gpb;

    // Define a study status

    Study::Status in_studyStatus = Study::RUNNING;

    // Study status <-> protobuf conversion

    std::vector<uint8_t>studyStatusAsBytes;

    CHECK(gpb.makeBytesFromStudyStatus(in_studyStatus, studyStatusAsBytes));
        
    Study::Status out_studyStatus;

    CHECK(gpb.makeStudyStatusFromBytes(studyStatusAsBytes, out_studyStatus));

    CHECK_EQUAL(out_studyStatus, in_studyStatus);

    // Test other enum values

    in_studyStatus = Study::STANDBY;
    CHECK(gpb.makeBytesFromStudyStatus(in_studyStatus, studyStatusAsBytes));
    CHECK(gpb.makeStudyStatusFromBytes(studyStatusAsBytes, out_studyStatus));
    CHECK_EQUAL(out_studyStatus, in_studyStatus);

    in_studyStatus = Study::STOPPED;
    CHECK(gpb.makeBytesFromStudyStatus(in_studyStatus, studyStatusAsBytes));
    CHECK(gpb.makeStudyStatusFromBytes(studyStatusAsBytes, out_studyStatus));
    CHECK_EQUAL(out_studyStatus, in_studyStatus);

}   //  end studyStatusMethodsForYosokumoProtobuf


TEST(studyVisibilityMethodsForYosokumoProtobuf)
{
    std::cout << "YosokumoProtobuf studyVisibilityMethodsForYosokumoProtobuf" << '\n';

    YosokumoProtobuf gpb;

    // Define a study visibility

    Study::Visibility in_studyVisibility = Study::PRIVATE;

    // Study visibility <-> protobuf conversion

    std::vector<uint8_t>studyVisibilityAsBytes;

    CHECK(gpb.makeBytesFromStudyVisibility(in_studyVisibility, studyVisibilityAsBytes));
        
    Study::Visibility out_studyVisibility;

    CHECK(gpb.makeStudyVisibilityFromBytes(studyVisibilityAsBytes, out_studyVisibility));

    CHECK_EQUAL(out_studyVisibility, in_studyVisibility);

    // Test other enum values

    in_studyVisibility = Study::PUBLIC;
    CHECK(gpb.makeBytesFromStudyVisibility(in_studyVisibility, studyVisibilityAsBytes));
    CHECK(gpb.makeStudyVisibilityFromBytes(studyVisibilityAsBytes, out_studyVisibility));
    CHECK_EQUAL(out_studyVisibility, in_studyVisibility);

}   //  end studyVisibilityMethodsForYosokumoProtobuf


// end YosokumoProtobufTest.cpp
