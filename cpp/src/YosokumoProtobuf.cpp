// YosokumoProtobuf.cpp

#include "StringUtil.h"
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


using namespace Yosokumo;


std::string YosokumoProtobuf::getContentType()
{
    return "application/yosokumo+protobuf";
}

//***********************   protobuf -> Catalog   *************************

bool YosokumoProtobuf::makeCatalogFromBytes(
    const std::vector<uint8_t> &catalogAsBytes,
    Catalog &catalog)
{
    ProtoBuf::Catalog protoCatalog;

    if (!makeProtobufCatalogFromBytes(catalogAsBytes, protoCatalog))
        return false;

    return makeCatalogFromProtobufCatalog(protoCatalog, catalog);
}

bool YosokumoProtobuf::makeProtobufCatalogFromBytes(
    const std::vector<uint8_t> &catalogAsBytes,
    ProtoBuf::Catalog &protoCatalog)
{
    int n = int(catalogAsBytes.size());

    if (n == 0)
    {
        exception = ServiceException(
            "input vector of bytes is empty",
            "makeProtobufCatalogFromBytes");
        return false;
    }

    if (!protoCatalog.ParseFromArray(&catalogAsBytes[0], n))
    {
        exception = ServiceException(
            "ProtoBuf::Catalog::ParseFromArray failed",
            "makeProtobufCatalogFromBytes");
        return false;
    }

    return true;

}   //  end makeProtobufCatalogFromBytes


bool YosokumoProtobuf::makeCatalogFromProtobufCatalog(
    const ProtoBuf::Catalog &protoCatalog, 
    Catalog &catalog)
{
    // Create a Yosokumo Catalog from a Protobuf catalog

    catalog.setUserIdentifier (protoCatalog.user_identifier());
    catalog.setUserName       (protoCatalog.user_name()      );
    catalog.setCatalogLocation(protoCatalog.location()       );

    catalog.clearStudies();

    for (int i = 0;  i < protoCatalog.study_size();  ++i)
    {
        const ProtoBuf::Study &protoStudy = protoCatalog.study(i);

        Study study;

        if (!makeStudyFromProtobufStudy(protoStudy, study))
            return false;

        if (!catalog.addStudy(study))
        {
            exception = ServiceException(
                "catalog contains two studies with the same identifier",
                "makeCatalogFromProtobufCatalog");

            return false;
        }
    }

    return true;

}   //  end makeCatalogFromProtobufCatalog

//***********************   Catalog -> protobuf   *************************

bool YosokumoProtobuf::makeBytesFromCatalog(
    const Catalog &catalog,
    std::vector<uint8_t> &catalogAsBytes)
{
    ProtoBuf::Catalog protoCatalog;

    if (!makeProtobufCatalogFromCatalog(catalog, protoCatalog))
        return false;

    return makeBytesFromProtobufCatalog(protoCatalog, catalogAsBytes);
}


bool YosokumoProtobuf::makeProtobufCatalogFromCatalog(
    const Catalog &catalog,
    ProtoBuf::Catalog &protoCatalog)
{
    protoCatalog.set_user_identifier (catalog.getUserIdentifier());
    protoCatalog.set_user_name       (catalog.getUserName());
    protoCatalog.set_location        (catalog.getCatalogLocation());

    Catalog::StudyConstIterator iter;
 
    for (iter = catalog.begin();  iter != catalog.end();  ++iter)
    {
        const Study &study = iter->second;

        ProtoBuf::Study *pProtoStudy = protoCatalog.add_study();

        if (!makeProtobufStudyFromStudy(study, *pProtoStudy))
            return false;
    }

    return true;
}

bool YosokumoProtobuf::makeBytesFromProtobufCatalog(
    const ProtoBuf::Catalog &protoCatalog,
    std::vector<uint8_t> &catalogAsBytes)
{
    int numBytes = protoCatalog.ByteSize();

    catalogAsBytes.assign(numBytes, 0);

    return protoCatalog.SerializeToArray(&catalogAsBytes[0], numBytes);
}


//************************   protobuf -> Study   **************************

bool YosokumoProtobuf::makeStudyFromBytes(
    const std::vector<uint8_t> &studyAsBytes,
    Study &study)
{
    ProtoBuf::Study protoStudy;

    if (!makeProtobufStudyFromBytes(studyAsBytes, protoStudy))
        return false;

    return makeStudyFromProtobufStudy(protoStudy, study);

}   //  end makeStudyFromBytes

bool YosokumoProtobuf::makeProtobufStudyFromBytes(
    const std::vector<uint8_t> &studyAsBytes,
    ProtoBuf::Study &protoStudy)
{
    int n = int(studyAsBytes.size());

    if (n == 0)
    {
        exception = ServiceException(
            "input vector of bytes is empty",
            "makeProtobufStudyFromBytes");
        return false;
    }

    if (!protoStudy.ParseFromArray(&studyAsBytes[0], n))
    {
        exception = ServiceException(
            "ProtoBuf::Study::ParseFromArray failed",
            "makeProtobufStudyFromBytes");
        return false;
    }

    return true;

}   //  end makeProtobufStudyFromBytes


bool YosokumoProtobuf::makeStudyFromProtobufStudy(
    const ProtoBuf::Study &protoStudy,
    Study &study)
{
    study.setStudyIdentifier(protoStudy.study_identifier());
    study.setStudyName      (protoStudy.study_name()      );
    study.setStudyLocation  (protoStudy.location()        );

    Study::Type type;
    if (!protoTypeToType(protoStudy.type(), type))
        return false;
    study.setType(type);

    Study::Status status;
    if (!protoStatusToStatus(protoStudy.status(), status))
        return false;
    study.setStatus(status);

    Study::Visibility visibility;
    if (!protoVisibilityToVisibility(protoStudy.visibility(), visibility)) 
        return false;
    study.setVisibility(visibility);

    study.setOwnerIdentifier(protoStudy.owner().user_identifier());
    study.setOwnerName      (protoStudy.owner().user_name());
    study.setTableLocation  (protoStudy.table().location());
    study.setModelLocation  (protoStudy.model().location());
    study.setPanelLocation  (protoStudy.panel().location());
    study.setRosterLocation (protoStudy.roster().location());

    return true;

}   //  end makeStudyFromProtobufStudy


//************************   Study -> protobuf   **************************

bool YosokumoProtobuf::makeBytesFromStudy(
    const Study &study,
    std::vector<uint8_t> &studyAsBytes)
{
    ProtoBuf::Study protoStudy;

    if (!makeProtobufStudyFromStudy(study, protoStudy))
        return false;

    return makeBytesFromProtobufStudy(protoStudy, studyAsBytes);
}


bool YosokumoProtobuf::makeProtobufStudyFromStudy(
    const Study &study,
    ProtoBuf::Study &protoStudy)
{
    protoStudy.set_study_identifier (study.getStudyIdentifier());
    protoStudy.set_study_name       (study.getStudyName());

    ProtoBuf::Study_Type type;
    if (!typeToProtobufType(study.getType(), type))
        return false;
    protoStudy.set_type(type);

    ProtoBuf::Study_Status status;
    if (!statusToProtobufStatus(study.getStatus(), status))
        return false;
    protoStudy.set_status(status);

    ProtoBuf::Study_Visibility visibility;
    if (!visibilityToProtobufVisibility(study.getVisibility(), visibility))
        return false;
    protoStudy.set_visibility(visibility);

    return true;
}

bool YosokumoProtobuf::makeBytesFromProtobufStudy(
    const ProtoBuf::Study &protoStudy,
    std::vector<uint8_t> &studyAsBytes)
{
    int numBytes = protoStudy.ByteSize();

    studyAsBytes.assign(numBytes, 0);

    return protoStudy.SerializeToArray(&studyAsBytes[0], numBytes);
}

//*********************   protobuf -> Study name   ************************

bool YosokumoProtobuf::makeStudyNameFromBytes(
    const std::vector<uint8_t> &studyNameAsBytes,
    std::string &name)
{
    ProtoBuf::Panel_StudyNameControl protoNameControl;

    if (!makeProtobufStudyNameControlFromBytes(
                                    studyNameAsBytes, protoNameControl))
        return false;

    return makeStudyNameFromProtobufStudyNameControl(protoNameControl, name);
}

bool YosokumoProtobuf::makeProtobufStudyNameControlFromBytes(
    const std::vector<uint8_t> &studyNameAsBytes,
    ProtoBuf::Panel_StudyNameControl &protoNameControl)
{
    int numBytes = int(studyNameAsBytes.size());

    if (numBytes == 0)
    {
        exception = ServiceException(
            "input vector of bytes is empty",
            "makeProtobufStudyNameControlFromBytes");
        return false;
    }

    if (!protoNameControl.ParseFromArray(&studyNameAsBytes[0], numBytes))
    {
        exception = ServiceException(
            "ProtoBuf::Panel_StudyNameControl::ParseFromArray failed",
            "makeProtobufStudyNameControlFromBytes");
        return false;
    }

    return true;
}

bool YosokumoProtobuf::makeStudyNameFromProtobufStudyNameControl(
    const ProtoBuf::Panel_StudyNameControl &protoNameControl,
    std::string &name)
{
    name = protoNameControl.study_name();
    return true;
}

//*********************   Study name -> protobuf   ************************

bool YosokumoProtobuf::makeBytesFromStudyName(
    const std::string &name,
    std::vector<uint8_t> &studyNameAsBytes)
{
    ProtoBuf::Panel_StudyNameControl protoNameControl;

    if (!makeProtobufStudyNameControlFromName(name, protoNameControl))
        return false;

    return makeBytesFromProtobufStudyNameControl(protoNameControl,studyNameAsBytes);
}

bool YosokumoProtobuf::makeProtobufStudyNameControlFromName(
    const std::string &name,
    ProtoBuf::Panel_StudyNameControl &protoNameControl)
{
    protoNameControl.set_study_name(name);
    return true;
}

bool YosokumoProtobuf::makeBytesFromProtobufStudyNameControl(
    const ProtoBuf::Panel_StudyNameControl &protoNameControl,
    std::vector<uint8_t> &studyNameAsBytes)
{
    int numBytes = protoNameControl.ByteSize();
    studyNameAsBytes.assign(numBytes, 0);
    return protoNameControl.SerializeToArray(&studyNameAsBytes[0], numBytes);
}

//********************   protobuf -> Study status   ***********************

bool YosokumoProtobuf::makeStudyStatusFromBytes(
    const std::vector<uint8_t> &studyStatusAsBytes,
    Study::Status &status)
{
    ProtoBuf::Panel_StatusControl protoStatusControl;

    if (!makeProtobufStudyStatusControlFromBytes(
                                    studyStatusAsBytes, protoStatusControl))
        return false;

    return makeStudyStatusFromProtobufStudyStatusControl(
        protoStatusControl, status);
}

bool YosokumoProtobuf::makeProtobufStudyStatusControlFromBytes(
    const std::vector<uint8_t> &studyStatusAsBytes,
    ProtoBuf::Panel_StatusControl &protoStatusControl)
{
    int numBytes = int(studyStatusAsBytes.size());

    if (numBytes == 0)
    {
        exception = ServiceException(
            "input vector of bytes is empty",
            "makeProtobufStudyStatusControlFromBytes");
        return false;
    }

    if (!protoStatusControl.ParseFromArray(&studyStatusAsBytes[0], numBytes))
    {
        exception = ServiceException(
            "ProtoBuf::Panel_StatusControl::ParseFromArray failed",
            "makeProtobufStudyStatusControlFromBytes");
        return false;
    }

    return true;
}

bool YosokumoProtobuf::makeStudyStatusFromProtobufStudyStatusControl(
    const ProtoBuf::Panel_StatusControl &protoStatusControl,
    Study::Status &status)
{
    return protoStatusToStatus(protoStatusControl.status(), status);
}


//*********************   Study status -> protobuf   ************************

bool YosokumoProtobuf::makeBytesFromStudyStatus(
    const Study::Status status,
    std::vector<uint8_t> &studyStatusAsBytes)
{
    ProtoBuf::Panel_StatusControl protoStatusControl;

    if (!makeProtobufStudyStatusControlFromStatus(status, protoStatusControl))
        return false;

    return makeBytesFromProtobufStudyStatusControl(
        protoStatusControl, studyStatusAsBytes);
}

bool YosokumoProtobuf::makeProtobufStudyStatusControlFromStatus(
    const Study::Status status,
    ProtoBuf::Panel_StatusControl &protoStatusControl)
{
    ProtoBuf::Study_Status protoStatus;

    if (!statusToProtobufStatus(status, protoStatus))
        return false;

    protoStatusControl.set_status(protoStatus);

    return true;
}

bool YosokumoProtobuf::makeBytesFromProtobufStudyStatusControl(
    const ProtoBuf::Panel_StatusControl &protoStatusControl,
    std::vector<uint8_t> &studyStatusAsBytes)
{
    int numBytes = protoStatusControl.ByteSize();
    studyStatusAsBytes.assign(numBytes, 0);
    return protoStatusControl.SerializeToArray(&studyStatusAsBytes[0], numBytes);
}

//*******************   protobuf -> Study visibility   ********************

bool YosokumoProtobuf::makeStudyVisibilityFromBytes(
    const std::vector<uint8_t> &studyVisibilityAsBytes,
    Study::Visibility &visibility)
{
    ProtoBuf::Panel_VisibilityControl protoVisibilityControl;

    if (!makeProtobufStudyVisibilityControlFromBytes(
                            studyVisibilityAsBytes, protoVisibilityControl))
        return false;

    return makeStudyVisibilityFromProtobufStudyVisibilityControl(
        protoVisibilityControl, visibility);
}

bool YosokumoProtobuf::makeProtobufStudyVisibilityControlFromBytes(
    const std::vector<uint8_t> &studyVisibilityAsBytes,
    ProtoBuf::Panel_VisibilityControl &protoVisibilityControl)
{
    int numBytes = int(studyVisibilityAsBytes.size());

    if (numBytes == 0)
    {
        exception = ServiceException(
            "input vector of bytes is empty",
            "makeProtobufStudyVisibilityControlFromBytes");
        return false;
    }

    if (!protoVisibilityControl.ParseFromArray(&studyVisibilityAsBytes[0], 
                                                                numBytes))
    {
        exception = ServiceException(
            "ProtoBuf::Panel_VisibilityControl::ParseFromArray failed",
            "makeProtobufStudyVisibilityControlFromBytes");
        return false;
    }

    return true;
}

bool YosokumoProtobuf::makeStudyVisibilityFromProtobufStudyVisibilityControl(
    const ProtoBuf::Panel_VisibilityControl &protoVisibilityControl,
    Study::Visibility &visibility)
{
    return protoVisibilityToVisibility(protoVisibilityControl.visibility(), 
                                                              visibility);
}


//*******************   Study visibility -> protobuf   ********************

bool YosokumoProtobuf::makeBytesFromStudyVisibility(
    const Study::Visibility visibility,
    std::vector<uint8_t> &studyVisibilityAsBytes)
{
    ProtoBuf::Panel_VisibilityControl protoVisibilityControl;

    if (!makeProtobufStudyVisibilityControlFromVisibility(visibility, 
                                                protoVisibilityControl))
        return false;

    return makeBytesFromProtobufStudyVisibilityControl(
        protoVisibilityControl, studyVisibilityAsBytes);
}

bool YosokumoProtobuf::makeProtobufStudyVisibilityControlFromVisibility(
    const Study::Visibility visibility,
    ProtoBuf::Panel_VisibilityControl &protoVisibilityControl)
{
    ProtoBuf::Study_Visibility protoVisibility;

    if (!visibilityToProtobufVisibility(visibility, protoVisibility))
        return false;

    protoVisibilityControl.set_visibility(protoVisibility);

    return true;
}

bool YosokumoProtobuf::makeBytesFromProtobufStudyVisibilityControl(
    const ProtoBuf::Panel_VisibilityControl &protoVisibilityControl,
    std::vector<uint8_t> &studyVisibilityAsBytes)
{
    int numBytes = protoVisibilityControl.ByteSize();
    studyVisibilityAsBytes.assign(numBytes, 0);
    return protoVisibilityControl.SerializeToArray(&studyVisibilityAsBytes[0], 
                                                                numBytes);
}

//************************   protobuf -> Panel   **************************

bool YosokumoProtobuf::makePanelFromBytes(
    const std::vector<uint8_t> &panelAsBytes,
    Panel &panel)
{
    ProtoBuf::Panel protoPanel;

    if (!makeProtobufPanelFromBytes(panelAsBytes, protoPanel))
        return false;

    return makePanelFromProtobufPanel(protoPanel, panel);

}   //  end makePanelFromBytes

bool YosokumoProtobuf::makeProtobufPanelFromBytes(
    const std::vector<uint8_t> &panelAsBytes,
    ProtoBuf::Panel &protoPanel)
{
    int n = int(panelAsBytes.size());

    if (n == 0)
    {
        exception = ServiceException(
            "input vector of bytes is empty",
            "makeProtobufPanelFromBytes");
        return false;
    }

    if (!protoPanel.ParseFromArray(&panelAsBytes[0], n))
    {
        exception = ServiceException(
            "ProtoBuf::Panel::ParseFromArray failed",
            "makeProtobufPanelFromBytes");
        return false;
    }

    return true;

}   //  end makeProtobufPanelFromBytes


bool YosokumoProtobuf::makePanelFromProtobufPanel(
    const ProtoBuf::Panel &protoPanel,
    Panel &panel)
{
    panel.setNameControlLocation(
                protoPanel.study_name_control().location());
    panel.setStatusControlLocation(
                protoPanel.status_control().location());
    panel.setVisibilityControlLocation(
                protoPanel.visibility_control().location());

    panel.setBlockCount(
                protoPanel.block_count_control().block_count());
    panel.setCellCount(
                protoPanel.cell_count_control().cell_count());
    panel.setProspectCount(
                protoPanel.prospect_count_control().prospect_count());

    panel.setCreationTime(
        protoPanel.creation_time_control().creation_time()      );
    panel.setLatestBlockTime(
        protoPanel.latest_block_time_control().latest_block_time()   );
    panel.setLatestProspectTime(
        protoPanel.latest_prospect_time_control().latest_prospect_time());

    return true;

}   //  end makePanelFromProtobufPanel


//************************   Panel -> protobuf   **************************

bool YosokumoProtobuf::makeBytesFromPanel(
    const Panel &panel,
    std::vector<uint8_t> &panelAsBytes)
{
    ProtoBuf::Panel protoPanel;

    if (!makeProtobufPanelFromPanel(panel, protoPanel))
        return false;

    return makeBytesFromProtobufPanel(protoPanel, panelAsBytes);
}


bool YosokumoProtobuf::makeProtobufPanelFromPanel(
    const Panel &panel,
    ProtoBuf::Panel &protoPanel)
{
    // makeProtobufPanelFromPanel only exists for testing makePanelFromBytes,
    // which means that the four fields following are not really relevant, 
    // but in order to create a valid ProtoBuf::Panel, they must be present.

    protoPanel.set_study_identifier("study identifier");
    protoPanel.mutable_study_name_control()->set_study_name("study name");
    protoPanel.mutable_status_control()    ->set_status(
                                        ProtoBuf::Study_Status_Stopped);
    protoPanel.mutable_visibility_control()->set_visibility(
                                        ProtoBuf::Study_Visibility_Private);

    // The following fields are the "real" Panel fields

    protoPanel.mutable_study_name_control()->set_location(
                                        panel.getNameControlLocation());
    protoPanel.mutable_status_control()    ->set_location(
                                        panel.getStatusControlLocation());
    protoPanel.mutable_visibility_control()->set_location(
                                        panel.getVisibilityControlLocation());

    protoPanel.mutable_block_count_control()   ->set_block_count(
                                        panel.getBlockCount());
    protoPanel.mutable_cell_count_control()    ->set_cell_count(
                                        panel.getCellCount());
    protoPanel.mutable_prospect_count_control()->set_prospect_count(
                                        panel.getProspectCount());

    protoPanel.mutable_creation_time_control()       ->set_creation_time(
                                                panel.getCreationTime());
    protoPanel.mutable_latest_block_time_control()   ->set_latest_block_time(
                                                panel.getLatestBlockTime());
    protoPanel.mutable_latest_prospect_time_control()->set_latest_prospect_time(
                                                panel.getLatestProspectTime());

    return true;
}

bool YosokumoProtobuf::makeBytesFromProtobufPanel(
    const ProtoBuf::Panel &protoPanel,
    std::vector<uint8_t> &panelAsBytes)
{
    int numBytes = protoPanel.ByteSize();

    panelAsBytes.assign(numBytes, 0);

    return protoPanel.SerializeToArray(&panelAsBytes[0], numBytes);
}


//************************   protobuf -> Role   ***************************

bool YosokumoProtobuf::makeRoleFromBytes(
    const std::vector<uint8_t> &roleAsBytes,
    Role &role)
{
    ProtoBuf::Role protoRole;

    if (!makeProtobufRoleFromBytes(roleAsBytes, protoRole))
        return false;

    return makeRoleFromProtobufRole(protoRole, role);

}   //  end makeRoleFromBytes

bool YosokumoProtobuf::makeProtobufRoleFromBytes(
    const std::vector<uint8_t> &roleAsBytes,
    ProtoBuf::Role &protoRole)
{
    int n = int(roleAsBytes.size());

    if (n == 0)
    {
        exception = ServiceException(
            "input vector of bytes is empty",
            "makeProtobufRoleFromBytes");
        return false;
    }

    if (!protoRole.ParseFromArray(&roleAsBytes[0], n))
    {
        exception = ServiceException(
            "ProtoBuf::Role::ParseFromArray failed",
            "makeProtobufRoleFromBytes");
        return false;
    }

    return true;

}   //  end makeProtobufRoleFromBytes


bool YosokumoProtobuf::makeRoleFromProtobufRole(
    const ProtoBuf::Role &protoRole,
    Role &role)
{
    role.setUserIdentifier (protoRole.roleholder().user_identifier());
    role.setStudyIdentifier(protoRole.study().study_identifier());

    role.setRoleLocation(protoRole.location());
    role.setUserName    (protoRole.roleholder().user_name());
    role.setStudyName   (protoRole.study().study_name());

    ProtoBuf::Role_Privileges p = protoRole.privileges();

    if (p.get_study())    role.addPrivilege(Privilege(Privilege::GET_STUDY   ));
    if (p.delete_study()) role.addPrivilege(Privilege(Privilege::DELETE_STUDY));
    if (p.get_roster())   role.addPrivilege(Privilege(Privilege::GET_ROSTER  ));
    if (p.post_roster())  role.addPrivilege(Privilege(Privilege::POST_ROSTER ));
    if (p.get_role())     role.addPrivilege(Privilege(Privilege::GET_ROLE    ));
    if (p.put_role())     role.addPrivilege(Privilege(Privilege::PUT_ROLE    ));
    if (p.delete_role())  role.addPrivilege(Privilege(Privilege::DELETE_ROLE ));
    if (p.get_panel())    role.addPrivilege(Privilege(Privilege::GET_PANEL   ));
    if (p.get_control())  role.addPrivilege(Privilege(Privilege::GET_CONTROL ));
    if (p.put_control())  role.addPrivilege(Privilege(Privilege::PUT_CONTROL ));
    if (p.post_table())   role.addPrivilege(Privilege(Privilege::POST_TABLE  ));
    if (p.get_model())    role.addPrivilege(Privilege(Privilege::GET_MODEL   ));
    if (p.post_model())   role.addPrivilege(Privilege(Privilege::POST_MODEL  ));

    return true;

}   //  end makeRoleFromProtobufRole


//************************   Role -> protobuf   ***************************

bool YosokumoProtobuf::makeBytesFromRole(
    const Role &role,
    std::vector<uint8_t> &roleAsBytes)
{
    ProtoBuf::Role protoRole;

    if (!makeProtobufRoleFromRole(role, protoRole))
        return false;

    return makeBytesFromProtobufRole(protoRole, roleAsBytes);
}


bool YosokumoProtobuf::makeProtobufRoleFromRole(
    const Role &role,
    ProtoBuf::Role &protoRole)
{
    ProtoBuf::Role_Roleholder roleholder;
    roleholder.set_user_identifier(role.getUserIdentifier());
    roleholder.set_user_name      (role.getUserName()      );

    ProtoBuf::Role_Study study;
    study.set_study_identifier(role.getStudyIdentifier());
    study.set_study_name      (role.getStudyName()      );

    ProtoBuf::Role_Privileges p;
    p.set_get_study   (role.getPrivilege(Privilege::GET_STUDY   ));
    p.set_delete_study(role.getPrivilege(Privilege::DELETE_STUDY));
    p.set_get_roster  (role.getPrivilege(Privilege::GET_ROSTER  ));
    p.set_post_roster (role.getPrivilege(Privilege::POST_ROSTER ));
    p.set_get_role    (role.getPrivilege(Privilege::GET_ROLE    ));
    p.set_put_role    (role.getPrivilege(Privilege::PUT_ROLE    ));
    p.set_delete_role (role.getPrivilege(Privilege::DELETE_ROLE ));
    p.set_get_panel   (role.getPrivilege(Privilege::GET_PANEL   ));
    p.set_get_control (role.getPrivilege(Privilege::GET_CONTROL ));
    p.set_put_control (role.getPrivilege(Privilege::PUT_CONTROL ));
    p.set_post_table  (role.getPrivilege(Privilege::POST_TABLE  ));
    p.set_get_model   (role.getPrivilege(Privilege::GET_MODEL   ));
    p.set_post_model  (role.getPrivilege(Privilege::POST_MODEL  ));

    protoRole.set_location(role.getRoleLocation());
    *protoRole.mutable_roleholder() = roleholder;
    *protoRole.mutable_study()      = study;
    *protoRole.mutable_privileges() = p;

    return true;
}

bool YosokumoProtobuf::makeBytesFromProtobufRole(
    const ProtoBuf::Role &protoRole,
    std::vector<uint8_t> &roleAsBytes)
{
    int numBytes = protoRole.ByteSize();

    roleAsBytes.assign(numBytes, 0);

    return protoRole.SerializeToArray(&roleAsBytes[0], numBytes);
}

//************************   protobuf -> Roster   ***************************

bool YosokumoProtobuf::makeRosterFromBytes(
    const std::vector<uint8_t> &rosterAsBytes,
    Roster &roster)
{
    ProtoBuf::Roster protoRoster;

    if (!makeProtobufRosterFromBytes(rosterAsBytes, protoRoster))
        return false;

    return makeRosterFromProtobufRoster(protoRoster, roster);

}   //  end makeRosterFromBytes

bool YosokumoProtobuf::makeProtobufRosterFromBytes(
    const std::vector<uint8_t> &rosterAsBytes,
    ProtoBuf::Roster &protoRoster)
{
    int n = int(rosterAsBytes.size());

    if (n == 0)
    {
        exception = ServiceException(
            "input vector of bytes is empty",
            "makeProtobufRosterFromBytes");
        return false;
    }

    if (!protoRoster.ParseFromArray(&rosterAsBytes[0], n))
    {
        exception = ServiceException(
            "ProtoBuf::Roster::ParseFromArray failed",
            "makeProtobufRosterFromBytes");
        return false;
    }

    return true;

}   //  end makeProtobufRosterFromBytes


bool YosokumoProtobuf::makeRosterFromProtobufRoster(
    const ProtoBuf::Roster &protoRoster,
    Roster &roster)
{
    roster.setStudyIdentifier(protoRoster.study_identifier());
    roster.setStudyName      (protoRoster.study_name()      );
    roster.setRosterLocation (protoRoster.location()        );

    for (int i = 0;  i < protoRoster.role_size();  ++i)
    {
        const ProtoBuf::Role &protoRole = protoRoster.role(i);

        Role role;

        if (!makeRoleFromProtobufRole(protoRole, role))
            return false;

        if (!roster.addRole(role))
        {
            exception = ServiceException(
                "roster contains two roles with the same identifier",
                "makeRosterFromProtobufRoster");

            return false;
        }
    }

    return true;

}   //  end makeRosterFromProtobufRoster


//************************   Roster -> protobuf   ***************************

bool YosokumoProtobuf::makeBytesFromRoster(
    const Roster &roster,
    std::vector<uint8_t> &rosterAsBytes)
{
    ProtoBuf::Roster protoRoster;

    if (!makeProtobufRosterFromRoster(roster, protoRoster))
        return false;

    return makeBytesFromProtobufRoster(protoRoster, rosterAsBytes);
}


bool YosokumoProtobuf::makeProtobufRosterFromRoster(
    const Roster &roster,
    ProtoBuf::Roster &protoRoster)
{
    protoRoster.set_study_identifier(roster.getStudyIdentifier());
    protoRoster.set_study_name      (roster.getStudyName()      );
    protoRoster.set_location        (roster.getRosterLocation() );

    Roster::RoleConstIterator iter;
 
    for (iter = roster.begin();  iter != roster.end();  ++iter)
    {
        const Role &role = iter->second;

        ProtoBuf::Role *pProtoRole = protoRoster.add_role();

        if (!makeProtobufRoleFromRole(role, *pProtoRole))
            return false;
    }

    return true;
}

bool YosokumoProtobuf::makeBytesFromProtobufRoster(
    const ProtoBuf::Roster &protoRoster,
    std::vector<uint8_t> &rosterAsBytes)
{
    int numBytes = protoRoster.ByteSize();

    rosterAsBytes.assign(numBytes, 0);

    return protoRoster.SerializeToArray(&rosterAsBytes[0], numBytes);
}

//**********************   protobuf -> Predictor   ************************

bool YosokumoProtobuf::makePredictorFromBytes(
    const std::vector<uint8_t> &predictorAsBytes,
    Predictor &predictor)
{
    ProtoBuf::Predictor protoPredictor;

    if (!makeProtobufPredictorFromBytes(predictorAsBytes, protoPredictor))
        return false;

    return makePredictorFromProtobufPredictor(protoPredictor, predictor);

}   //  end makePredictorFromBytes

bool YosokumoProtobuf::makeProtobufPredictorFromBytes(
    const std::vector<uint8_t> &predictorAsBytes,
    ProtoBuf::Predictor &protoPredictor)
{
    int n = int(predictorAsBytes.size());

    if (n == 0)
    {
        exception = ServiceException(
            "input vector of bytes is empty",
            "makeProtobufPredictorFromBytes");
        return false;
    }

    if (!protoPredictor.ParseFromArray(&predictorAsBytes[0], n))
    {
        exception = ServiceException(
            "ProtoBuf::Predictor::ParseFromArray failed",
            "makeProtobufPredictorFromBytes");
        return false;
    }

    return true;

}   //  end makeProtobufPredictorFromBytes


bool YosokumoProtobuf::makePredictorFromProtobufPredictor(
    const ProtoBuf::Predictor &protoPredictor,
    Predictor &predictor)
{
    predictor.setPredictorName (protoPredictor.name());

    Predictor::Type type;
    if (!protoTypeToType(protoPredictor.type(), type))
        return false;
    predictor.setType(type);

    Predictor::Status status;
    if (!protoStatusToStatus(protoPredictor.status(), status))
        return false;
    predictor.setStatus(status);

    Predictor::Level level;
    if (!protoLevelToLevel(protoPredictor.level(), level)) 
        return false;
    predictor.setLevel(level);

    return true;

}   //  end makePredictorFromProtobufPredictor


//**********************   Predictor -> protobuf   ************************

bool YosokumoProtobuf::makeBytesFromPredictor(
    const Predictor &predictor,
    std::vector<uint8_t> &predictorAsBytes)
{
    ProtoBuf::Predictor protoPredictor;

    if (!makeProtobufPredictorFromPredictor(predictor, protoPredictor))
        return false;

    return makeBytesFromProtobufPredictor(protoPredictor, predictorAsBytes);
}


bool YosokumoProtobuf::makeProtobufPredictorFromPredictor(
    const Predictor &predictor,
    ProtoBuf::Predictor &protoPredictor)
{
    protoPredictor.set_name(predictor.getPredictorName());

    ProtoBuf::Predictor_Type type;
    if (!typeToProtobufType(predictor.getType(), type))
        return false;
    protoPredictor.set_type(type);

    ProtoBuf::Predictor_Status status;
    if (!statusToProtobufStatus(predictor.getStatus(), status))
        return false;
    protoPredictor.set_status(status);

    ProtoBuf::Predictor_Level level;
    if (!levelToProtobufLevel(predictor.getLevel(), level))
        return false;
    protoPredictor.set_level(level);

    return true;
}

bool YosokumoProtobuf::makeBytesFromProtobufPredictor(
    const ProtoBuf::Predictor &protoPredictor,
    std::vector<uint8_t> &predictorAsBytes)
{
    int numBytes = protoPredictor.ByteSize();

    predictorAsBytes.assign(numBytes, 0);

    return protoPredictor.SerializeToArray(&predictorAsBytes[0], numBytes);
}

//**********************   protobuf -> Cell   ************************

bool YosokumoProtobuf::makeCellFromBytes(
    const std::vector<uint8_t> &cellAsBytes,
    Cell &cell)
{
    ProtoBuf::Cell protoCell;

    if (!makeProtobufCellFromBytes(cellAsBytes, protoCell))
        return false;

    return makeCellFromProtobufCell(protoCell, cell);

}   //  end makeCellFromBytes

bool YosokumoProtobuf::makeProtobufCellFromBytes(
    const std::vector<uint8_t> &cellAsBytes,
    ProtoBuf::Cell &protoCell)
{
    int n = int(cellAsBytes.size());

    if (n == 0)
    {
        exception = ServiceException(
            "input vector of bytes is empty",
            "makeProtobufCellFromBytes");
        return false;
    }

    if (!protoCell.ParseFromArray(&cellAsBytes[0], n))
    {
        exception = ServiceException(
            "ProtoBuf::Cell::ParseFromArray failed",
            "makeProtobufCellFromBytes");
        return false;
    }

    return true;

}   //  end makeProtobufCellFromBytes


bool YosokumoProtobuf::makeCellFromProtobufCell(
    const ProtoBuf::Cell &protoCell,
    Cell &cell)
{
    uint64_t nameOrKey;

    if      (protoCell.has_key() )  nameOrKey = protoCell.key();
    else if (protoCell.has_name())  nameOrKey = protoCell.name();
    else
    {
        exception = ServiceException(
            "ProtoBuf::Cell has neither name nor key",
            "makeCellFromProtobufCell");
        return false;
    }

    Value value;
    if (protoCell.has_empty()  )  
                value = EmptyValue();
    else if (protoCell.has_natural())
                value = NaturalValue(protoCell.natural());
    else if (protoCell.has_integer())
                value = IntegerValue(protoCell.integer());
    else if (protoCell.has_real())
                value = RealValue(protoCell.real());
    else if (protoCell.has_special())
                value = SpecialValue(protoCell.special());
    else
    {
        exception = ServiceException(
            "ProtoBuf::Cell has no value",
            "makeCellFromProtobufCell");
        return false;
    }

    cell.setName(nameOrKey);
    cell.setValue(value);

    return true;

}   //  end makeCellFromProtobufCell


//**********************   Cell -> protobuf   ************************

bool YosokumoProtobuf::makeBytesFromCell(
    const Cell &cell,
    std::vector<uint8_t> &cellAsBytes)
{
    ProtoBuf::Cell protoCell;

    if (!makeProtobufCellFromCell(cell, protoCell))
        return false;

    return makeBytesFromProtobufCell(protoCell, cellAsBytes);
}

bool YosokumoProtobuf::makeProtobufCellFromCell(
    const Cell &cell,
    ProtoBuf::Cell &protoCell)
{
    protoCell.set_name(cell.getName());

    Value v = cell.getValue();

    switch (v.getType())
    {
    case Value::EMPTY:    protoCell.set_empty(true);                   break;
    case Value::NATURAL:  protoCell.set_natural(v.getNaturalValue());  break;
    case Value::INTEGER:  protoCell.set_integer(v.getIntegerValue());  break;
    case Value::REAL:     protoCell.set_real   (v.getRealValue()   );  break;
    case Value::SPECIAL:  protoCell.set_special(v.getSpecialValue());  break;
    default:
        protoCell.set_empty(true);
        exception = ServiceException(
            "Yosokumo Cell value has unknown type",
            "makeProtobufCellFromCell");
        return false;
    }

    return true;
}

bool YosokumoProtobuf::makeBytesFromProtobufCell(
    const ProtoBuf::Cell &protoCell,
    std::vector<uint8_t> &cellAsBytes)
{
    int numBytes = protoCell.ByteSize();

    cellAsBytes.assign(numBytes, 0);

    return protoCell.SerializeToArray(&cellAsBytes[0], numBytes);
}


//**********************   protobuf -> Specimen   ************************

bool YosokumoProtobuf::makeSpecimenFromBytes(
    const std::vector<uint8_t> &specimenAsBytes,
    Specimen &specimen)
{
    ProtoBuf::Specimen protoSpecimen;

    if (!makeProtobufSpecimenFromBytes(specimenAsBytes, protoSpecimen))
        return false;

    return makeSpecimenFromProtobufSpecimen(protoSpecimen, specimen);

}   //  end makeSpecimenFromBytes

bool YosokumoProtobuf::makeProtobufSpecimenFromBytes(
    const std::vector<uint8_t> &specimenAsBytes,
    ProtoBuf::Specimen &protoSpecimen)
{
    int n = int(specimenAsBytes.size());

    if (n == 0)
    {
        exception = ServiceException(
            "input vector of bytes is empty",
            "makeProtobufSpecimenFromBytes");
        return false;
    }

    if (!protoSpecimen.ParseFromArray(&specimenAsBytes[0], n))
    {
        exception = ServiceException(
            "ProtoBuf::Specimen::ParseFromArray failed",
            "makeProtobufSpecimenFromBytes");
        return false;
    }

    return true;

}   //  end makeProtobufSpecimenFromBytes


bool YosokumoProtobuf::makeSpecimenFromProtobufSpecimen(
    const ProtoBuf::Specimen &protoSpecimen,
    Specimen &specimen)
{
    specimen.setSpecimenKey(protoSpecimen.key());

    Specimen::Status status;
    if (!protoStatusToStatus(protoSpecimen.status(), status))
        return false;
    specimen.setStatus(status);

    specimen.setWeight(protoSpecimen.weight());

    Value value;
    if (protoSpecimen.has_empty()  )
                value = EmptyValue();
    else if (protoSpecimen.has_natural())
                value = NaturalValue(protoSpecimen.natural());
    else if (protoSpecimen.has_integer())
                value = IntegerValue(protoSpecimen.integer());
    else if (protoSpecimen.has_real()   )
                value = RealValue(protoSpecimen.real());
    else
    {
        exception = ServiceException(
            "ProtoBuf::Specimen has no value",
            "makeSpecimenFromProtobufSpecimen");
        return false;
    }

    specimen.setPredictand(value);

    for (int i = 0;  i < protoSpecimen.cell_size();  ++i)
    {
        const ProtoBuf::Cell &protoCell = protoSpecimen.cell(i);

        Cell cell;

        if (!makeCellFromProtobufCell(protoCell, cell))
            return false;

        specimen.addCell(cell);
    }

    return true;

}   //  end makeSpecimenFromProtobufSpecimen


//**********************   Specimen -> protobuf   ************************

bool YosokumoProtobuf::makeBytesFromSpecimen(
    const Specimen &specimen,
    std::vector<uint8_t> &specimenAsBytes)
{
    ProtoBuf::Specimen protoSpecimen;

    if (!makeProtobufSpecimenFromSpecimen(specimen, protoSpecimen))
        return false;

    return makeBytesFromProtobufSpecimen(protoSpecimen, specimenAsBytes);
}

bool YosokumoProtobuf::makeProtobufSpecimenFromSpecimen(
    const Specimen &specimen,
    ProtoBuf::Specimen &protoSpecimen)
{
    protoSpecimen.set_key(specimen.getSpecimenKey());

    ProtoBuf::Specimen_Status protoStatus;
    if (!statusToProtobufStatus(specimen.getStatus(), protoStatus))
        return false;
    protoSpecimen.set_status(protoStatus);

    protoSpecimen.set_weight(specimen.getWeight());

    Value v = specimen.getPredictand();

    switch (v.getType())
    {
    case Value::EMPTY:    protoSpecimen.set_empty(true);                   break;
    case Value::NATURAL:  protoSpecimen.set_natural(v.getNaturalValue());  break;
    case Value::INTEGER:  protoSpecimen.set_integer(v.getIntegerValue());  break;
    case Value::REAL:     protoSpecimen.set_real   (v.getRealValue());     break;
    default:
        protoSpecimen.set_empty(true);
        exception = ServiceException(
            "Yosokumo Specimen predictand value has unknown type",
            "makeProtobufSpecimenFromSpecimen");
    }
 
    for (unsigned i = 0;  i < specimen.size();  ++i)
    {
        const Cell &cell = specimen.getCell(i);

        ProtoBuf::Cell *pProtoCell = protoSpecimen.add_cell();

        if (!makeProtobufCellFromCell(cell, *pProtoCell))
            return false;
    }

    return true;
}


bool YosokumoProtobuf::makeBytesFromProtobufSpecimen(
    const ProtoBuf::Specimen &protoSpecimen,
    std::vector<uint8_t> &specimenAsBytes)
{
    int numBytes = protoSpecimen.ByteSize();

    specimenAsBytes.assign(numBytes, 0);

    return protoSpecimen.SerializeToArray(&specimenAsBytes[0], numBytes);
}


//************************   protobuf -> Block   **************************

bool YosokumoProtobuf::makeBlockFromBytes(
    const std::vector<uint8_t> &blockAsBytes,
    Block &block)
{
    ProtoBuf::Block protoBlock;

    if (!makeProtobufBlockFromBytes(blockAsBytes, protoBlock))
        return false;

    return makeBlockFromProtobufBlock(protoBlock, block);

}   //  end makeBlockFromBytes

bool YosokumoProtobuf::makeProtobufBlockFromBytes(
    const std::vector<uint8_t> &blockAsBytes,
    ProtoBuf::Block &protoBlock)
{
    int n = int(blockAsBytes.size());

    if (n == 0)
    {
        exception = ServiceException(
            "input vector of bytes is empty",
            "makeProtobufBlockFromBytes");
        return false;
    }

    if (!protoBlock.ParseFromArray(&blockAsBytes[0], n))
    {
        exception = ServiceException(
            "ProtoBuf::Block::ParseFromArray failed",
            "makeProtobufBlockFromBytes");
        return false;
    }

    return true;

}   //  end makeProtobufBlockFromBytes


bool YosokumoProtobuf::makeBlockFromProtobufBlock(
    const ProtoBuf::Block &protoBlock,
    Block &block)
{
    std::string id = protoBlock.study_identifier();

    Block::Type blockType;
    if (protoBlock.has_empty() && protoBlock.empty())
        blockType = Block::EMPTY;
    else if (protoBlock.predictor_size() > 0)
            blockType = Block::PREDICTOR;
    else
            blockType = Block::CELL;

    // The alert reader might expect that the statement just above should 
    // set blockType to Block::SPECIMEN.  Indeed, the protoBlock contains a
    // SpecimenBlock.  However, to avoid waste of time and space, the input 
    // SpecimenBlock is transformed to a CellBlock.

    switch (blockType)
    {
    case Block::EMPTY:
        block = EmptyBlock(id);
        break;

    case Block::PREDICTOR:
    {
        block = PredictorBlock(id);
        PredictorBlock &pblock = (PredictorBlock&)block;
        for (int i = 0;  i < protoBlock.predictor_size();  ++i)
        {
            const ProtoBuf::Predictor &protoPredictor = protoBlock.predictor(i);

            Predictor predictor;

            if (!makePredictorFromProtobufPredictor(protoPredictor, predictor))
                return false;

            pblock.addPredictor(predictor);
        }
        break;
    }

    case Block::CELL:
    {
        block = CellBlock(id);
        CellBlock &cblock = (CellBlock&)block;
        for (int i = 0;  i < protoBlock.specimen_size();  ++i)
        {
            const ProtoBuf::Specimen &protoSpecimen = protoBlock.specimen(i);

            Specimen specimen;

            if (!makeSpecimenFromProtobufSpecimen(protoSpecimen, specimen))
                return false;

            Cell cell(specimen.getSpecimenKey(), specimen.getPredictand());

            cblock.addCell(cell);
        }
        break;
    }

    default:
        assert(false);
        break;
    }
    return true;

}   //  end makeBlockFromProtobufBlock


//************************   Block -> protobuf   **************************

bool YosokumoProtobuf::makeBytesFromBlock(
    const Block &block,
    std::vector<uint8_t> &blockAsBytes)
{
    ProtoBuf::Block protoBlock;

    if (!makeProtobufBlockFromBlock(block, protoBlock))
        return false;

    return makeBytesFromProtobufBlock(protoBlock, blockAsBytes);
}

bool YosokumoProtobuf::makeProtobufBlockFromBlock(
    const Block &block,
    ProtoBuf::Block &protoBlock)
{
    protoBlock.set_study_identifier(block.getStudyIdentifier());

    switch (block.getType())
    {
    case Block::EMPTY:
        protoBlock.set_empty(true);
        break;

    case Block::PREDICTOR:
    {
        protoBlock.clear_empty();
        PredictorBlock &pblock = (PredictorBlock&)block;
        for (unsigned i = 0;  i < pblock.size();  ++i)
        {
            const Predictor &p = pblock.getPredictor(i);
            ProtoBuf::Predictor *pProtoPredictor = protoBlock.add_predictor();
            if (!makeProtobufPredictorFromPredictor(p, *pProtoPredictor))
                return false;
        }
        break;
    }

    case Block::SPECIMEN:
    {
        protoBlock.clear_empty();
        SpecimenBlock &sblock = (SpecimenBlock&)block;
        for (unsigned i = 0;  i < sblock.size();  ++i)
        {
            const Specimen *ps = sblock.getSpecimen(i);
            ProtoBuf::Specimen *pProtoSpecimen = protoBlock.add_specimen();
            if (!makeProtobufSpecimenFromSpecimen(*ps, *pProtoSpecimen))
                return false;
        }
        break;
    }

    default:
        protoBlock.set_empty(true);
        exception = ServiceException(
            "Yosokumo::Block has unknown type",
             "makeProtobufBlockFromBlock");
        return false;
    }

    return true;
}

bool YosokumoProtobuf::makeBytesFromProtobufBlock(
    const ProtoBuf::Block &protoBlock,
    std::vector<uint8_t> &blockAsBytes)
{
    int numBytes = protoBlock.ByteSize();

    blockAsBytes.assign(numBytes, 0);

    return protoBlock.SerializeToArray(&blockAsBytes[0], numBytes);
}


//***********************   protobuf -> Message   *************************


bool YosokumoProtobuf::makeMessageFromBytes(
    const std::vector<uint8_t> &messageAsBytes,
    Message &message)
{
    ProtoBuf::Message protoMessage;

    if (!makeProtobufMessageFromBytes(messageAsBytes, protoMessage))
        return false;

    return makeMessageFromProtobufMessage(protoMessage, message);
}

bool YosokumoProtobuf::makeProtobufMessageFromBytes(
    const std::vector<uint8_t> &messageAsBytes,
    ProtoBuf::Message &protoMessage)
{
    int n = int(messageAsBytes.size());

    if (n == 0)
    {
        exception = ServiceException(
            "input vector of bytes is empty",
            "makeProtobufMessageFromBytes");
        return false;
    }

    if (!protoMessage.ParseFromArray(&messageAsBytes[0], n))
    {
        exception = ServiceException(
            "ProtoBuf::Message::ParseFromArray failed",
            "makeProtobufMessageFromBytes");
        return false;
    }

    return true;

}   //  end makeProtobufMessageFromBytes

bool YosokumoProtobuf::makeMessageFromProtobufMessage(
    const ProtoBuf::Message &protoMessage,
    Message &m)
{
    m.setType(Message::INFORMATION);
    m.setText("");

    Message::Type type;

    if (!protoTypeToType(protoMessage.type(), type))
        return false;

    std::string text = protoMessage.text();
    text = trim(text);

    // It is a bit unclear why we ignore Message objects with a text 
    // consisting solely of whitespace, but this is what the Java API does.
    // It may be that on occasion such objects are sent over by the Yosokumo
    // server and there is nothing to do but ignore them.

    if (text.empty())
        return false;

    m.setType(type);
    m.setText(text);

    return true;

}   //  end makeMessageFromProtobufMessage

//***********************   Message -> protobuf   *************************

bool YosokumoProtobuf::makeBytesFromMessage(
    const Message &message,
    std::vector<uint8_t> &messageAsBytes)
{
    ProtoBuf::Message protoMessage;

    if (!makeProtobufMessageFromMessage(message, protoMessage))
        return false;

    return makeBytesFromProtobufMessage(protoMessage, messageAsBytes);
}


bool YosokumoProtobuf::makeProtobufMessageFromMessage(
    const Message &message,
    ProtoBuf::Message &protoMessage)
{
    protoMessage.set_text(message.getText());

    ProtoBuf::Message_Type type;
    if (!typeToProtobufType(message.getType(), type))
        return false;
    protoMessage.set_type(type);

    return true;
}

bool YosokumoProtobuf::makeBytesFromProtobufMessage(
    const ProtoBuf::Message &protoMessage,
    std::vector<uint8_t> &messageAsBytes)
{
    int numBytes = protoMessage.ByteSize();

    messageAsBytes.assign(numBytes, 0);

    return protoMessage.SerializeToArray(&messageAsBytes[0], numBytes);
}

//*************************   enums -> enums   ****************************

//*********************   protobuf -> Study::Type   ***********************

bool YosokumoProtobuf::protoTypeToType(
    ProtoBuf::Study_Type protoType,
    Study::Type &type)
{
    bool ok = true;

    switch (protoType)
    {
    case ProtoBuf::Study_Type_Class:   type = Study::CLASS;   break;
    case ProtoBuf::Study_Type_Rank:    type = Study::RANK;    break;
    case ProtoBuf::Study_Type_Number:  type = Study::NUMBER;  break;
    case ProtoBuf::Study_Type_Chance:  type = Study::CHANCE;  break;
    default:                           ok = false;            break;
    }

    if (!ok)
    {
        exception = ServiceException(
            "ProtoBuf::Study_Type is invalid",
            "protoTypeToType:  ProtoBuf::Study_Type -> Study::Type");

    } 

    return ok;

}   //  end protoTypeToType:  ProtoBuf::Study_Type -> Study::Type

//*********************   Study::Type -> protobuf   ***********************

bool YosokumoProtobuf::typeToProtobufType(
    Study::Type type,
    ProtoBuf::Study_Type &protoType)
{
    bool ok = true;

    switch (type)
    {
    case Study::CLASS :  protoType = ProtoBuf::Study_Type_Class ;  break;
    case Study::RANK  :  protoType = ProtoBuf::Study_Type_Rank  ;  break;
    case Study::NUMBER:  protoType = ProtoBuf::Study_Type_Number;  break;
    case Study::CHANCE:  protoType = ProtoBuf::Study_Type_Chance;  break;
    default:             ok = false;                               break;
    }

    if (!ok)
    {
        exception = ServiceException(
            "Study::Type is invalid",
            "typeToProtobufType:  Study::Type -> ProtoBuf::Study_Type");

    } 

    return ok;

}   //  end typeToProtobufType:  Study::Type -> ProtoBuf::Study_Type

//********************   protobuf -> Study::Status   **********************

bool YosokumoProtobuf::protoStatusToStatus(
    ProtoBuf::Study_Status protoStatus,
    Study::Status &status)
{
    bool ok = true;

    switch (protoStatus)
    {
    case ProtoBuf::Study_Status_Running:  status = Study::RUNNING;  break;
    case ProtoBuf::Study_Status_Standby:  status = Study::STANDBY;  break;
    case ProtoBuf::Study_Status_Stopped:  status = Study::STOPPED;  break;
    default:                              ok = false;               break;
    }

    if (!ok)
    {
        exception = ServiceException(
            "ProtoBuf::Study_Status is invalid",
            "protoStatusToStatus:  ProtoBuf::Study_Status -> Study::Status");

    } 

    return ok;

}   //  end protoStatusToStatus:  ProtoBuf::Study_Status -> Study::Status

//********************   Study::Status -> protobuf   **********************

bool YosokumoProtobuf::statusToProtobufStatus(
    Study::Status status,
    ProtoBuf::Study_Status &protoStatus)
{
    bool ok = true;

    switch (status)
    {
    case Study::RUNNING:  protoStatus = ProtoBuf::Study_Status_Running;  break;
    case Study::STANDBY:  protoStatus = ProtoBuf::Study_Status_Standby;  break;
    case Study::STOPPED:  protoStatus = ProtoBuf::Study_Status_Stopped;  break;
    default:              ok = false;                                    break;
    }

    if (!ok)
    {
        exception = ServiceException(
            "Study::Status is invalid",
            "statusToProtobufStatus:  Study::Status -> ProtoBuf::Study_Status");

    } 

    return ok;

}   //  end statusToProtobufStatus:  Study::Status -> ProtoBuf::Study_Status


//******************   protobuf -> Study::Visibility   ********************

bool YosokumoProtobuf::protoVisibilityToVisibility(
    ProtoBuf::Study_Visibility protoVisibility,
    Study::Visibility &visibility)
{
    bool ok = true;

    switch (protoVisibility)
    {
    case ProtoBuf::Study_Visibility_Private:  visibility = Study::PRIVATE; break;
    case ProtoBuf::Study_Visibility_Public:   visibility = Study::PUBLIC;  break;
    default:                                  ok = false;                  break;
    }

    if (!ok)
    {
        exception = ServiceException(
            "ProtoBuf::Study_Visibility is invalid",
            "protoVisibilityToVisibility:  ProtoBuf::Study_Visibility -> "
                                                    "Study::Visibility");

    } 

    return ok;

}   //  end protoVisibilityToVisibility:  ProtoBuf::Study_Visibility -> Study::Visibility

//******************   Study::Visibility -> protobuf   ********************

bool YosokumoProtobuf::visibilityToProtobufVisibility(
    Study::Visibility visibility,
    ProtoBuf::Study_Visibility &protoVisibility)
{
    bool ok = true;

    switch (visibility)
    {
    case Study::PRIVATE:  protoVisibility = ProtoBuf::Study_Visibility_Private;  break;
    case Study::PUBLIC :  protoVisibility = ProtoBuf::Study_Visibility_Public ;  break;
    default:              ok = false;                                            break;
    }

    if (!ok)
    {
        exception = ServiceException(
            "Study::Visibility is invalid",
            "visibilityToProtobufVisibility:  Study::Visibility -> ProtoBuf::Study_Visibility");

    } 

    return ok;

}   //  end visibilityToProtobufVisibility:  Study::Visibility -> ProtoBuf::Study_Visibility


//********************   protobuf -> Message::Type   **********************

bool YosokumoProtobuf::protoTypeToType(
    ProtoBuf::Message_Type protoType,
    Message::Type &type)
{
    bool ok = true;

    switch (protoType)
    {
    case ProtoBuf::Message_Type_Information:  type = Message::INFORMATION;  break;
    case ProtoBuf::Message_Type_Error:        type = Message::ERROR;        break;
    default:                                  ok = false;                   break;
    }

    if (!ok)
    {
        exception = ServiceException(
            "ProtoBuf::Message_Type is invalid",
            "protoTypeToType:  ProtoBuf::Message_Type -> Message::Type");
    }

    return ok;

}   //  end protoTypeToType:  ProtoBuf::Message_Type -> Message::Type


//********************   Message::Type -> protobuf   **********************

bool YosokumoProtobuf::typeToProtobufType(
    Message::Type type,
    ProtoBuf::Message_Type &protoType)
{
    bool ok = true;

    switch (type)
    {
    case Message::INFORMATION:  protoType = ProtoBuf::Message_Type_Information; break;
    case Message::ERROR:        protoType = ProtoBuf::Message_Type_Error;       break;
    default:                    ok = false;                                     break;
    }

    if (!ok)
    {
        exception = ServiceException(
            "Message::Type is invalid",
            "typeToProtobufType:  Message::Type -> ProtoBuf::Message_Type");
    }

    return ok;

}   //  end typeToProtobufType:  Message::Type -> ProtoBuf::Message_Type


//******************   protobuf -> Predictor::Status   ********************

bool YosokumoProtobuf::protoStatusToStatus(
    ProtoBuf::Predictor_Status protoStatus,
    Predictor::Status &status)
{
    bool ok = true;

    switch (protoStatus)
    {
    case ProtoBuf::Predictor_Status_Active:    status = Predictor::ACTIVE;    break;
    case ProtoBuf::Predictor_Status_Inactive:  status = Predictor::INACTIVE;  break;
    default:                                   ok = false;                    break;
    }

    if (!ok)
    {
        exception = ServiceException(
            "ProtoBuf::Predictor_Status is invalid",
            "protoStatusToStatus:  ProtoBuf::Predictor_Status -> Predictor::Status");

    } 

    return ok;

}   //  end protoStatusToStatus:  ProtoBuf::Predictor_Status -> Predictor::Status


//******************   Predictor::Status -> protobuf   ********************

bool YosokumoProtobuf::statusToProtobufStatus(
    Predictor::Status status,
    ProtoBuf::Predictor_Status &protoStatus)
{
    bool ok = true;

    switch (status)
    {
    case Predictor::ACTIVE:    protoStatus = ProtoBuf::Predictor_Status_Active;    break;
    case Predictor::INACTIVE:  protoStatus = ProtoBuf::Predictor_Status_Inactive;  break;
    default:                   ok = false;                                         break;
    }

    if (!ok)
    {
        exception = ServiceException(
            "Predictor::Status is invalid",
            "statusToProtobufStatus:  Predictor::Status -> ProtoBuf::Predictor_Status");

    } 

    return ok;

}   //  end statusToProtobufStatus:  Predictor::Status -> ProtoBuf::Predictor_Status

//*******************   protobuf -> Predictor::Type   *********************

bool YosokumoProtobuf::protoTypeToType(
    ProtoBuf::Predictor_Type protoType,
    Predictor::Type &type)
{
    bool ok = true;

    switch (protoType)
    {
    case ProtoBuf::Predictor_Type_Categorical:  type = Predictor::CATEGORICAL;  break;
    case ProtoBuf::Predictor_Type_Continuous:   type = Predictor::CONTINUOUS;   break;
    default:                                    ok = false;                     break;
    }

    if (!ok)
    {
        exception = ServiceException(
            "ProtoBuf::Predictor_Type is invalid",
            "protoTypeToType:  ProtoBuf::Predictor_Type -> Predictor::Type");
    }

    return ok;

}   //  end protoTypeToType:  ProtoBuf::Predictor_Type -> Predictor::Type


//*******************   Predictor::Type -> protobuf   *********************

bool YosokumoProtobuf::typeToProtobufType(
    Predictor::Type type,
    ProtoBuf::Predictor_Type &protoType)
{
    bool ok = true;

    switch (type)
    {
    case Predictor::CATEGORICAL:  protoType = ProtoBuf::Predictor_Type_Categorical; break;
    case Predictor::CONTINUOUS:   protoType = ProtoBuf::Predictor_Type_Continuous;  break;
    default:                      ok = false;                                       break;
    }

    if (!ok)
    {
        exception = ServiceException(
            "Predictor::Type is invalid",
            "typeToProtobufType:  Predictor::Type -> ProtoBuf::Predictor_Type");
    }

    return ok;

}   //  end typeToProtobufType:  Predictor::Type -> ProtoBuf::Predictor_Type


//******************   protobuf -> Predictor::Level   *********************

bool YosokumoProtobuf::protoLevelToLevel(
    ProtoBuf::Predictor_Level protoLevel,
    Predictor::Level &level)
{
    bool ok = true;

    switch (protoLevel)
    {
    case ProtoBuf::Predictor_Level_Nominal:   level = Predictor::NOMINAL;   break;
    case ProtoBuf::Predictor_Level_Ordinal:   level = Predictor::ORDINAL;   break;
    case ProtoBuf::Predictor_Level_Interval:  level = Predictor::INTERVAL;  break;
    case ProtoBuf::Predictor_Level_Ratio:     level = Predictor::RATIO;     break;
    default:                                  ok = false;                   break;
    }

    if (!ok)
    {
        exception = ServiceException(
            "ProtoBuf::Predictor_Level is invalid",
            "protoLevelToLevel:  ProtoBuf::Predictor_Level -> Predictor::Level");
    }

    return ok;

}   //  end protoLevelToLevel:  ProtoBuf::Predictor_Level -> Predictor::Level


//*******************   Predictor::Level -> protobuf   ********************

bool YosokumoProtobuf::levelToProtobufLevel(
    Predictor::Level level,
    ProtoBuf::Predictor_Level &protoLevel)
{
    bool ok = true;

    switch (level)
    {
    case Predictor::NOMINAL:   protoLevel = ProtoBuf::Predictor_Level_Nominal;  break;
    case Predictor::ORDINAL:   protoLevel = ProtoBuf::Predictor_Level_Ordinal;  break;
    case Predictor::INTERVAL:  protoLevel = ProtoBuf::Predictor_Level_Interval; break;
    case Predictor::RATIO:     protoLevel = ProtoBuf::Predictor_Level_Ratio;    break;
    default:                   ok = false;                                      break;
    }

    if (!ok)
    {
        exception = ServiceException(
            "Predictor::Level is invalid",
            "levelToProtobufLevel:  Predictor::Level -> ProtoBuf::Predictor_Level");
    }

    return ok;

}   //  end levelToProtobufLevel:  Predictor::Level -> ProtoBuf::Predictor_Level


//******************   protobuf -> Specimen::Status   *********************

bool YosokumoProtobuf::protoStatusToStatus(
    ProtoBuf::Specimen_Status protoStatus,
    Specimen::Status &status)
{
    bool ok = true;

    switch (protoStatus)
    {
    case ProtoBuf::Specimen_Status_Active:    status = Specimen::ACTIVE;    break;
    case ProtoBuf::Specimen_Status_Inactive:  status = Specimen::INACTIVE;  break;
    default:                                  ok = false;                   break;
    }

    if (!ok)
    {
        exception = ServiceException(
            "ProtoBuf::Specimen_Status is invalid",
            "protoStatusToStatus:  ProtoBuf::Specimen_Status -> Specimen::Status");
    } 

    return ok;

}   //  end protoStatusToStatus:  ProtoBuf::Specimen_Status -> Specimen::Status

//*******************   Specimen::Status -> protobuf   ********************

bool YosokumoProtobuf::statusToProtobufStatus(
    Specimen::Status status,
    ProtoBuf::Specimen_Status &protoStatus)
{
    bool ok = true;

    switch (status)
    {
    case Specimen::ACTIVE:    protoStatus = ProtoBuf::Specimen_Status_Active;    break;
    case Specimen::INACTIVE:  protoStatus = ProtoBuf::Specimen_Status_Inactive;  break;
    default:                  ok = false;                                        break;
    }

    if (!ok)
    {
        exception = ServiceException(
            "Specimen::Status is invalid",
            "statusToProtobufStatus:  Specimen::Status -> ProtoBuf::Specimen_Status");
    } 

    return ok;

}   //  end statusToProtobufStatus:  Specimen::Status -> ProtoBuf::Specimen_Status


// end YosokumoProtobuf.cpp
