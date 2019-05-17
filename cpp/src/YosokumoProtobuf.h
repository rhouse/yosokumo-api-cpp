// YosokumoProtobuf.h

#ifndef YOSOKUMOPROTOBUF_H
#define YOSOKUMOPROTOBUF_H

#include "YosokumoDIF.h"
#include "yosokumo.pb.h"

namespace Yosokumo
{
/**
 * Implements all functionality for transforming HTTP entity bytes in Google 
 * Protocol Buffer form into Yosokumo C++ objects (e.g., <code>Catalog</code> 
 * and <code>Study</code>) and vice versa.  In general there are six functions
 * for each Yosokumo class, illustrated here for <code>Study</code>:
 * <p>
 * Converting from HTTP entity bytes to Study:
 * <pre>
 *   public  bool makeStudyFromBytes(
 *                    const std::vector<uint8_t> &studyAsBytes, 
 *                    Study &study)
 *   private bool makeProtobufStudyFromBytes(
 *                    const std::vector<uint8_t> &studyAsBytes,
 *                    ProtoBuf::Study &protoStudy);
 *   private bool makeStudyFromProtobufStudy(
 *                    const ProtoBuf::Study &protoStudy,
 *                    Study &study);
 * </pre>
 * Converting from Study to HTTP entity bytes:
 * <pre>
 *   public  bool makeBytesFromStudy(
 *                    const Study &study,
 *                    std::vector<uint8_t> &studyAsBytes)
 *   private bool makeProtobufStudyFromStudy(
 *                    const Study &study,
 *                    ProtoBuf::Study &protoStudy)
 *   private bool makeBytesFromProtobufStudy(
 *                    const ProtoBuf::Study &protoStudy,
 *                    std::vector<uint8_t> &studyAsBytes)
 * </pre>
 * Note how Google Protocol Buffer objects are used as the intermediaries 
 * between HTTP entity bytes and Yosokumo objects.  Here is another view of the
 * transformations done by the functions shown above:
 * <pre>
 *    makeStudyFromBytes:
 *      vector<uint8_t> -> makeProtobufStudyFromBytes -> ProtoBuf.Study
 *      ProtoBuf.Study  -> makeStudyFromProtobufStudy -> Study
 *
 *    makeBytesFromStudy:
 *      Study          -> makeProtobufStudyFromStudy -> ProtoBuf.Study
 *      ProtoBuf.Study -> makeBytesFromProtobufStudy -> vector<uint8_t>
 * </pre>
 */
class YosokumoProtobuf : public YosokumoDIF
{
public:

    std::string getContentType();


//***********************   protobuf -> Catalog   *************************

public:

    bool makeCatalogFromBytes(
        const std::vector<uint8_t> &catalogAsBytes,
        Catalog &catalog);

private:

    bool makeProtobufCatalogFromBytes(
        const std::vector<uint8_t> &catalogAsBytes,
        ProtoBuf::Catalog &protoCatalog);

    bool makeCatalogFromProtobufCatalog(
        const ProtoBuf::Catalog &protoCatalog, 
        Catalog &catalog);


//***********************   Catalog -> protobuf   *************************
public:

    bool makeBytesFromCatalog(
        const Catalog &catalog,
        std::vector<uint8_t> &catalogAsBytes);

private:

    bool makeProtobufCatalogFromCatalog(
        const Catalog &catalog,
        ProtoBuf::Catalog &protoCatalog);

    bool makeBytesFromProtobufCatalog(
        const ProtoBuf::Catalog &protoCatalog,
        std::vector<uint8_t> &catalogAsBytes);


//************************   protobuf -> Study   **************************
public:

    bool makeStudyFromBytes(
        const std::vector<uint8_t> &studyAsBytes,
        Study &study);

private:

    bool makeProtobufStudyFromBytes(
        const std::vector<uint8_t> &studyAsBytes,
        ProtoBuf::Study &protoStudy);

    bool makeStudyFromProtobufStudy(
        const ProtoBuf::Study &protoStudy,
        Study &study);


//************************   Study -> protobuf   **************************
public:

    bool makeBytesFromStudy(
        const Study &study,
        std::vector<uint8_t> &studyAsBytes);

private:

    bool makeProtobufStudyFromStudy(
        const Study &study,
        ProtoBuf::Study &protoStudy);

    bool makeBytesFromProtobufStudy(
        const ProtoBuf::Study &protoStudy,
        std::vector<uint8_t> &studyAsBytes);


//*********************   protobuf -> Study name   ************************
public:

    bool makeStudyNameFromBytes(
        const std::vector<uint8_t> &studyNameAsBytes,
        std::string &name);

private:

    bool makeProtobufStudyNameControlFromBytes(
        const std::vector<uint8_t> &studyNameAsBytes,
        ProtoBuf::Panel_StudyNameControl &protoNameControl);

    bool makeStudyNameFromProtobufStudyNameControl(
        const ProtoBuf::Panel_StudyNameControl &protoNameControl,
        std::string &name);


//*********************   Study name -> protobuf   ************************
public:

    bool makeBytesFromStudyName(
        const std::string &name,
        std::vector<uint8_t> &studyNameAsBytes);

private:

    bool makeProtobufStudyNameControlFromName(
        const std::string &name,
        ProtoBuf::Panel_StudyNameControl &protoNameControl);

    bool makeBytesFromProtobufStudyNameControl(
        const ProtoBuf::Panel_StudyNameControl &protoNameControl,
        std::vector<uint8_t> &studyNameAsBytes);


//********************   protobuf -> Study status   ***********************
public:

    bool makeStudyStatusFromBytes(
        const std::vector<uint8_t> &studyStatusAsBytes,
        Study::Status &status);

private:

    bool makeProtobufStudyStatusControlFromBytes(
        const std::vector<uint8_t> &studyStatusAsBytes,
        ProtoBuf::Panel_StatusControl &protoStatusControl);

    bool makeStudyStatusFromProtobufStudyStatusControl(
        const ProtoBuf::Panel_StatusControl &protoStatusControl,
        Study::Status &status);


//********************   Study status -> protobuf   ***********************
public:

    bool makeBytesFromStudyStatus(
        const Study::Status status,
        std::vector<uint8_t> &studyStatusAsBytes);

private:

    bool makeProtobufStudyStatusControlFromStatus(
        const Study::Status status,
        ProtoBuf::Panel_StatusControl &protoStatusControl);

    bool makeBytesFromProtobufStudyStatusControl(
        const ProtoBuf::Panel_StatusControl &protoStatusControl,
        std::vector<uint8_t> &studyStatusAsBytes);

//******************   protobuf -> Study visibility   *********************
public:

    bool makeStudyVisibilityFromBytes(
        const std::vector<uint8_t> &studyVisibilityAsBytes,
        Study::Visibility &visibility);

private:

    bool makeProtobufStudyVisibilityControlFromBytes(
        const std::vector<uint8_t> &studyVisibilityAsBytes,
        ProtoBuf::Panel_VisibilityControl &protoVisibilityControl);

    bool makeStudyVisibilityFromProtobufStudyVisibilityControl(
        const ProtoBuf::Panel_VisibilityControl &protoVisibilityControl,
        Study::Visibility &visibility);


//******************   Study visibility -> protobuf   *********************
public:

    bool makeBytesFromStudyVisibility(
        const Study::Visibility visibility,
        std::vector<uint8_t> &studyVisibilityBytes);

private:

    bool makeProtobufStudyVisibilityControlFromVisibility(
        const Study::Visibility visibility,
        ProtoBuf::Panel_VisibilityControl &protoVisibilityControl);

    bool makeBytesFromProtobufStudyVisibilityControl(
        const ProtoBuf::Panel_VisibilityControl &protoVisibilityControl,
        std::vector<uint8_t> &studyVisibilityBytes);

//************************   protobuf -> Panel   **************************
public:

    bool makePanelFromBytes(
        const std::vector<uint8_t> &panelAsBytes,
        Panel &panel);

private:

    bool makeProtobufPanelFromBytes(
        const std::vector<uint8_t> &panelAsBytes,
        ProtoBuf::Panel &protoPanel);

    bool makePanelFromProtobufPanel(
        const ProtoBuf::Panel &protoPanel,
        Panel &panel);

//************************   Panel -> protobuf   **************************
public:

    bool makeBytesFromPanel(
        const Panel &panel,
        std::vector<uint8_t> &panelAsBytes);

private:

    bool makeProtobufPanelFromPanel(
        const Panel &panel,
        ProtoBuf::Panel &protoPanel);

    bool makeBytesFromProtobufPanel(
        const ProtoBuf::Panel &protoPanel,
        std::vector<uint8_t> &panelAsBytes);


//************************   protobuf -> Role   ***************************
public:

    bool makeRoleFromBytes(
        const std::vector<uint8_t> &roleAsBytes,
        Role &role);

private:

    bool makeProtobufRoleFromBytes(
        const std::vector<uint8_t> &roleAsBytes,
        ProtoBuf::Role &protoRole);

    bool makeRoleFromProtobufRole(
        const ProtoBuf::Role &protoRole,
        Role &role);


//************************   Role -> protobuf   ***************************
public:

    bool makeBytesFromRole(
        const Role &role,
        std::vector<uint8_t> &roleAsBytes);

private:

    bool makeProtobufRoleFromRole(
        const Role &role,
        ProtoBuf::Role &protoRole);

    bool makeBytesFromProtobufRole(
        const ProtoBuf::Role &protoRole,
        std::vector<uint8_t> &roleAsBytes);


//***********************   protobuf -> Roster   **************************
public:

    bool makeRosterFromBytes(
        const std::vector<uint8_t> &rosterAsBytes,
        Roster &roster);

private:

    bool makeProtobufRosterFromBytes(
        const std::vector<uint8_t> &rosterAsBytes,
        ProtoBuf::Roster &protoRoster);

    bool makeRosterFromProtobufRoster(
        const ProtoBuf::Roster &protoRoster,
        Roster &roster);


//***********************   Roster -> protobuf   **************************
public:

    bool makeBytesFromRoster(
        const Roster &roster,
        std::vector<uint8_t> &rosterAsBytes);

private:

    bool makeProtobufRosterFromRoster(
        const Roster &roster,
        ProtoBuf::Roster &protoRoster);

    bool makeBytesFromProtobufRoster(
        const ProtoBuf::Roster &protoRoster,
        std::vector<uint8_t> &rosterAsBytes);


//**********************   protobuf -> Predictor   ************************
public:

    bool makePredictorFromBytes(
        const std::vector<uint8_t> &predictorAsBytes,
        Predictor &predictor);

private:

    bool makeProtobufPredictorFromBytes(
        const std::vector<uint8_t> &predictorAsBytes,
        ProtoBuf::Predictor &protoPredictor);

    bool makePredictorFromProtobufPredictor(
        const ProtoBuf::Predictor &protoPredictor,
        Predictor &predictor);


//**********************   Predictor -> protobuf   ************************
public:

    bool makeBytesFromPredictor(
        const Predictor &predictor,
        std::vector<uint8_t> &predictorAsBytes);

private:

    bool makeProtobufPredictorFromPredictor(
        const Predictor &predictor,
        ProtoBuf::Predictor &protoPredictor);

    bool makeBytesFromProtobufPredictor(
        const ProtoBuf::Predictor &protoPredictor,
        std::vector<uint8_t> &predictorAsBytes);

//************************   protobuf -> Cell   ***************************
public:

    bool makeCellFromBytes(
        const std::vector<uint8_t> &cellAsBytes,
        Cell &cell);

private:

    bool makeProtobufCellFromBytes(
        const std::vector<uint8_t> &cellAsBytes,
        ProtoBuf::Cell &protoCell);

    bool makeCellFromProtobufCell(
        const ProtoBuf::Cell &protoCell,
        Cell &cell);


//************************   Cell -> protobuf   ***************************
public:

    bool makeBytesFromCell(
        const Cell &cell,
        std::vector<uint8_t> &cellAsBytes);

private:

    bool makeProtobufCellFromCell(
        const Cell &cell,
        ProtoBuf::Cell &protoCell);

    bool makeBytesFromProtobufCell(
        const ProtoBuf::Cell &protoCell,
        std::vector<uint8_t> &cellAsBytes);

//**********************   protobuf -> Specimen   *************************
public:

    bool makeSpecimenFromBytes(
        const std::vector<uint8_t> &specimenAsBytes,
        Specimen &specimen);

private:

    bool makeProtobufSpecimenFromBytes(
        const std::vector<uint8_t> &specimenAsBytes,
        ProtoBuf::Specimen &protoSpecimen);

    bool makeSpecimenFromProtobufSpecimen(
        const ProtoBuf::Specimen &protoSpecimen,
        Specimen &specimen);


//**********************   Specimen -> protobuf   *************************
public:

    bool makeBytesFromSpecimen(
        const Specimen &specimen,
        std::vector<uint8_t> &specimenAsBytes);

private:

    bool makeProtobufSpecimenFromSpecimen(
        const Specimen &specimen,
        ProtoBuf::Specimen &protoSpecimen);

    bool makeBytesFromProtobufSpecimen(
        const ProtoBuf::Specimen &protoSpecimen,
        std::vector<uint8_t> &specimenAsBytes);


//************************   protobuf -> Block   **************************
public:

    bool makeBlockFromBytes(
        const std::vector<uint8_t> &blockAsBytes,
        Block &block);

private:

    bool makeProtobufBlockFromBytes(
        const std::vector<uint8_t> &blockAsBytes,
        ProtoBuf::Block &protoBlock);

    bool makeBlockFromProtobufBlock(
        const ProtoBuf::Block &protoBlock,
        Block &block);


//************************   Block -> protobuf   **************************
public:

    bool makeBytesFromBlock(
        const Block &block,
        std::vector<uint8_t> &blockAsBytes);

private:

    bool makeProtobufBlockFromBlock(
        const Block &block,
        ProtoBuf::Block &protoBlock);

    bool makeBytesFromProtobufBlock(
        const ProtoBuf::Block &protoBlock,
        std::vector<uint8_t> &blockAsBytes);


//***********************   protobuf -> Message   *************************
public:

    bool makeMessageFromBytes(
        const std::vector<uint8_t> &messageAsBytes,
        Message &message);

private:

    bool makeProtobufMessageFromBytes(
        const std::vector<uint8_t> &messageAsBytes,
        ProtoBuf::Message &protoMessage);

    bool makeMessageFromProtobufMessage(
        const ProtoBuf::Message &protoMessage,
        Message &m);


//***********************   Message -> protobuf   *************************
public:

    bool makeBytesFromMessage(
        const Message &message,
        std::vector<uint8_t> &messageAsBytes);

private:

    bool makeProtobufMessageFromMessage(
        const Message &message,
        ProtoBuf::Message &protoMessage);

    bool makeBytesFromProtobufMessage(
        const ProtoBuf::Message &protoMessage,
        std::vector<uint8_t> &messageAsBytes);


//*************************   enums -> enums   ****************************
private:

    bool protoTypeToType(               //***** protobuf -> Study::Type
        ProtoBuf::Study_Type protoType,
        Study::Type &type);

    bool typeToProtobufType(            //***** Study::Type -> protobuf
        Study::Type type,
        ProtoBuf::Study_Type &protoType);

    bool protoStatusToStatus(           //***** protobuf -> Study::Status
        ProtoBuf::Study_Status protoStatus,
        Study::Status &status);

    bool statusToProtobufStatus(        //***** Study::Status -> protobuf
        Study::Status status,
        ProtoBuf::Study_Status &protoStatus);

    bool protoVisibilityToVisibility(   //***** protobuf -> Study::Visibility
        ProtoBuf::Study_Visibility protoVisibility,
        Study::Visibility &visibility);

    bool visibilityToProtobufVisibility(//***** Study::Visibility -> protobuf
        Study::Visibility visibility,
        ProtoBuf::Study_Visibility &protoVisibility);

    bool protoTypeToType(               //***** protobuf -> Message::Type
        ProtoBuf::Message_Type protoType,
        Message::Type &type);

    bool typeToProtobufType(            //***** Message::Type -> protobuf
        Message::Type type,
        ProtoBuf::Message_Type &protoType);

    bool protoStatusToStatus(           //***** protobuf -> Preditor::Status
        ProtoBuf::Predictor_Status protoStatus,
        Predictor::Status &status);

    bool statusToProtobufStatus(        //***** Predictor::Status -> protobuf
        Predictor::Status status,
        ProtoBuf::Predictor_Status &protoStatus);

    bool protoTypeToType(               //***** protobuf -> Predictor::Type
        ProtoBuf::Predictor_Type protoType,
        Predictor::Type &type);

    bool typeToProtobufType(            //***** Predictor::Type -> protobuf
        Predictor::Type type,
        ProtoBuf::Predictor_Type &protoType);

    bool protoLevelToLevel(             //***** protobuf -> Predictor::Level
        ProtoBuf::Predictor_Level protoLevel,
        Predictor::Level &level);
    
    bool levelToProtobufLevel(          //***** Predictor::Level -> protobuf
        Predictor::Level level,
        ProtoBuf::Predictor_Level &protoLevel);

   bool protoStatusToStatus(            //***** protobuf -> Specimen::Status
       ProtoBuf::Specimen_Status protoStatus,
       Specimen::Status &status);

   bool statusToProtobufStatus(         //***** Specimen::Status -> protobuf
       Specimen::Status status,
       ProtoBuf::Specimen_Status &protoStatus);

};  //  end class YosokumoProtobuf 

}   //  end namespace Yosokumo

#endif  // YOSOKUMOPROTOBUF_H

// end YosokumoProtobuf.h
