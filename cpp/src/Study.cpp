// Study.cpp

#include <sstream>

#include "Study.h"

using namespace Yosokumo;

// Constructors

Study::Study()
{
    initStudy();
}

Study::Study
    (
        const std::string &studyName, 
        Type               type, 
        Status             status,
        Visibility         visibility
    )
{
    initStudy();

    this->studyName   = studyName;
    this->type        = type;
    this->status      = status;
    this->visibility  = visibility;
}

Study::Study(const Study &rhs)
{
    operator=(rhs);
}

Study::~Study()
{}

Study &Study::operator=(const Study& rhs)
{
    if (this == &rhs)
        return *this;

    copyStudy(*this, rhs);

    return *this;
}


// Equality operators

bool Study::operator==(const Study &rhs) const 
{
    return
    (
        studyIdentifier           == rhs.studyIdentifier           &&
        studyName                 == rhs.studyName                 &&
        studyLocation             == rhs.studyLocation             &&

        type                      == rhs.type                      &&
        status                    == rhs.status                    &&
        visibility                == rhs.visibility                &&

        ownerIdentifier           == rhs.ownerIdentifier           &&
        ownerName                 == rhs.ownerName                 &&

        tableLocation             == rhs.tableLocation             &&
        modelLocation             == rhs.modelLocation             &&
        panelLocation             == rhs.panelLocation             &&
        rosterLocation            == rhs.rosterLocation            &&

        // Panel info

        nameControlLocation       == rhs.nameControlLocation       &&
        statusControlLocation     == rhs.statusControlLocation     &&
        visibilityControlLocation == rhs.visibilityControlLocation &&

        blockCount                == rhs.blockCount                &&
        cellCount                 == rhs.cellCount                 &&
        prospectCount             == rhs.prospectCount             &&

        creationTime              == rhs.creationTime              &&
        latestBlockTime           == rhs.latestBlockTime           &&
        latestProspectTime        == rhs.latestProspectTime
    );
}

bool Study::operator!=(const Study &rhs) const
{
    return !(*this == rhs);
}


void Study::initStudy()
{
    studyIdentifier           = "";
    studyName                 = "";
    studyLocation             = "";
    type                      = NUMBER;
    status                    = RUNNING;
    visibility                = PRIVATE;
    ownerIdentifier           = "";
    ownerName                 = "";
    tableLocation             = "";
    modelLocation             = "";
    panelLocation             = "";
    rosterLocation            = "";
    nameControlLocation       = "";
    statusControlLocation     = "";
    visibilityControlLocation = "";
    blockCount                = 0;
    cellCount                 = 0;
    prospectCount             = 0;
    creationTime              = "";
    latestBlockTime           = "";
    latestProspectTime        = "";
}

// Copy one study to another

void Study::copyStudy(Study &t, const Study &s)
{
    t.setStudyIdentifier(s.getStudyIdentifier());
    t.setStudyName      (s.getStudyName()      );
    t.setStudyLocation  (s.getStudyLocation()  );
    t.setType           (s.getType()           );
    t.setStatus         (s.getStatus()         );
    t.setVisibility     (s.getVisibility()     );
    t.setOwnerIdentifier(s.getOwnerIdentifier());
    t.setOwnerName      (s.getOwnerName()      );
    t.setTableLocation  (s.getTableLocation()  );
    t.setModelLocation  (s.getModelLocation()  );
    t.setPanelLocation  (s.getPanelLocation()  );
    t.setRosterLocation (s.getRosterLocation() );

    // Panel info

    t.setNameControlLocation      (s.getNameControlLocation()      );
    t.setStatusControlLocation    (s.getStatusControlLocation()    );
    t.setVisibilityControlLocation(s.getVisibilityControlLocation());
    t.setBlockCount               (s.getBlockCount()               );
    t.setCellCount                (s.getCellCount()                );
    t.setProspectCount            (s.getProspectCount()            );
    t.setCreationTime             (s.getCreationTime()             );
    t.setLatestBlockTime          (s.getLatestBlockTime()          );
    t.setLatestProspectTime       (s.getLatestProspectTime()       );

}   //  end copyStudy

// Setters and getters

void Study::setStudyIdentifier(const std::string &id)
{
    studyIdentifier = id;
}

std::string Study::getStudyIdentifier() const
{
    return studyIdentifier;
}

void Study::setStudyName(const std::string &name)
{
    studyName = name;
}

std::string Study::getStudyName() const
{
    return studyName;
}

void Study::setStudyLocation(const std::string &loc)
{
    studyLocation = loc;
}

std::string Study::getStudyLocation() const
{
    return studyLocation;
}

void Study::setType(Type t)
{
    type = t;
}

Study::Type Study::getType() const
{
    return type;
}

void Study::setStatus(Status s)
{
    status = s;
}

Study::Status Study::getStatus() const
{
    return status;
}

void Study::setVisibility(Visibility v)
{
    visibility = v;
}

Study::Visibility Study::getVisibility() const
{
    return visibility;
}

void Study::setOwnerIdentifier(const std::string &id)
{
    ownerIdentifier = id;
}

std::string Study::getOwnerIdentifier() const
{
    return ownerIdentifier;
}

void Study::setOwnerName(const std::string &name)
{
    ownerName = name;
}

std::string Study::getOwnerName() const
{
    return ownerName;
}

void Study::setTableLocation(const std::string &loc)
{
    tableLocation = loc;
}

std::string Study::getTableLocation() const
{
    return tableLocation;
}

void Study::setModelLocation(const std::string &loc)
{
    modelLocation = loc;
}

std::string Study::getModelLocation() const
{
    return modelLocation;
}

void Study::setPanelLocation(const std::string &loc)
{
    panelLocation = loc;
}

std::string Study::getPanelLocation() const
{
    return panelLocation;
}

void Study::setRosterLocation(const std::string &loc)
{
    rosterLocation = loc;
}

std::string Study::getRosterLocation() const
{
    return rosterLocation;
}

// Panel setters and getters

void Study::setNameControlLocation(const std::string &nameControlLocation)
{
    this->nameControlLocation = nameControlLocation;
}

std::string Study::getNameControlLocation() const
{
    return nameControlLocation;
}

void Study::setStatusControlLocation(const std::string &statusControlLocation)
{
    this->statusControlLocation = statusControlLocation;
}

std::string Study::getStatusControlLocation() const
{
    return statusControlLocation;
}

void Study::setVisibilityControlLocation(const std::string &visibilityControlLocation)
{
    this->visibilityControlLocation = visibilityControlLocation;
}

std::string Study::getVisibilityControlLocation() const
{
    return visibilityControlLocation;
}

void Study::setBlockCount(uint64_t blockCount)
{
    this->blockCount = blockCount;
}

uint64_t Study::getBlockCount() const
{
    return blockCount;
}

void Study::setCellCount(uint64_t cellCount)
{
    this->cellCount = cellCount;
}

uint64_t Study::getCellCount() const
{
    return cellCount;
}

void Study::setProspectCount(uint64_t prospectCount)
{
    this->prospectCount = prospectCount;
}

uint64_t Study::getProspectCount() const
{
    return prospectCount;
}

void Study::setCreationTime(const std::string &creationTime)
{
    this->creationTime = creationTime;
}

std::string Study::getCreationTime() const
{
    return creationTime;
}

void Study::setLatestBlockTime(const std::string &latestBlockTime)
{
    this->latestBlockTime = latestBlockTime;
}

std::string Study::getLatestBlockTime() const
{
    return latestBlockTime;
}

void Study::setLatestProspectTime(const std::string &latestProspectTime)
{
    this->latestProspectTime = latestProspectTime;
}

std::string Study::getLatestProspectTime() const
{
    return latestProspectTime;
}

// Utility

std::string Study::toString()
{
    std::stringstream s;

    s << 
    "Study:"                                                   << '\n' <<
    "  studyIdentifier          = " << getStudyIdentifier()    << '\n' <<
    "  studyName                = " << getStudyName()          << '\n' <<
    "  studyLocation            = " << getStudyLocation()      << '\n' <<
                                                                  '\n' <<
    "  type                     = " << getType()               << '\n' <<
    "  status                   = " << getStatus()             << '\n' <<
    "  visibility               = " << getVisibility()         << '\n' <<
                                                                  '\n' <<
    "  ownerIdentifier          = " << getOwnerIdentifier()    << '\n' <<
    "  ownerName                = " << getOwnerName()          << '\n' <<
    "  tableLocation            = " << getTableLocation()      << '\n' <<
    "  modelLocation            = " << getModelLocation()      << '\n' <<
    "  panelLocation            = " << getPanelLocation()      << '\n' <<
    "  rosterLocation           = " << getRosterLocation()     << '\n' <<
                                                                  '\n' <<
    "  nameControlLocation      = " << getNameControlLocation()<< '\n' <<
    "  statusControlLocation    = " 
                            << getStatusControlLocation()      << '\n' <<
    "  visibilityControlLocation= " 
                            << getVisibilityControlLocation()  << '\n' <<
                                                                  '\n' <<
    "  blockCount               = " << getBlockCount()         << '\n' <<
    "  cellCount                = " << getCellCount()          << '\n' <<
    "  prospectCount            = " << getProspectCount()      << '\n' <<
                                                                  '\n' <<
    "  creationTime             = " << getCreationTime()       << '\n' <<
    "  latestBlockTime          = " << getLatestBlockTime()    << '\n' <<
    "  latestProspectTime       = " << getLatestProspectTime() << '\n'
    ;

    return s.str();

}   // end toString

// end Study.cpp
