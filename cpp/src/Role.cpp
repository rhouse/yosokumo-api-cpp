// Role.cpp

#include "Role.h"

#include <sstream>

using namespace Yosokumo;

// Constructors

Role::Role() :
    userIdentifier(""), 
    userName(""), 
    studyIdentifier(""), 
    studyName(""), 
    roleLocation("")
{
    privilegeSet.reset();   // Turn off all privileges
}

Role::Role(
    const std::string &userIdentifier, 
    const std::string &studyIdentifier) :
        userIdentifier(userIdentifier), 
        userName(""), 
        studyIdentifier(studyIdentifier), 
        studyName(""), 
        roleLocation("")
{
    privilegeSet.reset();   // Turn off all privileges
}

Role::Role(const Role &rhs)
{
    operator=(rhs);
}

Role::~Role()
{}

Role &Role::operator=(const Role& rhs)
{
    if (this == &rhs)
        return *this;

    userIdentifier  = rhs.userIdentifier ;
    userName        = rhs.userName       ;
    studyIdentifier = rhs.studyIdentifier;
    studyName       = rhs.studyName      ;
    roleLocation    = rhs.roleLocation   ;

    privilegeSet    = rhs.privilegeSet;

    return *this;
}


// Equality operators

bool Role::operator==(const Role &rhs) const 
{
    return
    (
        userIdentifier  == rhs.userIdentifier &&
        userName        == rhs.userName       &&
        studyIdentifier == rhs.studyIdentifier&&
        studyName       == rhs.studyName      &&
        roleLocation    == rhs.roleLocation   &&
        privilegeSet    == rhs.privilegeSet
    );
}

bool Role::operator!=(const Role &rhs) const
{
    return !(*this == rhs);
}


// Setters and getters

Role &Role::setRoleLocation(const std::string &loc)
{
    roleLocation = loc;
    return *this;
}

std::string Role::getRoleLocation() const
{
    return roleLocation;
}

Role &Role::setUserIdentifier(const std::string &userIdentifier)
{
    this->userIdentifier = userIdentifier;
    return *this;
}

std::string Role::getUserIdentifier() const
{
    return userIdentifier;
}

Role &Role::setUserName(const std::string &name)
{
    userName = name;
    return *this;
}

std::string Role::getUserName() const
{
    return userName;
}

Role &Role::setStudyIdentifier(const std::string &studyIdentifier)
{
    this->studyIdentifier = studyIdentifier;
    return *this;
}

std::string Role::getStudyIdentifier() const
{
    return studyIdentifier;
}

Role &Role::setStudyName(const std::string &name)
{
    studyName = name;
    return *this;
}

std::string Role::getStudyName() const
{
    return studyName;
}


// Get and set privileges

Role &Role::addPrivilege(Privilege privilege)
{
    privilegeSet.set(privilege.getNumber()-1, true);

    return *this;
}

Role &Role::removePrivilege(Privilege privilege)
{
    privilegeSet.reset(privilege.getNumber()-1);

    return *this;
}

Role &Role::addAllPrivileges()
{
    privilegeSet.set();

    return *this;
}

Role &Role::removeAllPrivileges()
{
    privilegeSet.reset();

    return *this;
}

bool Role::getPrivilege(Privilege privilege) const
{
    return privilegeSet.test(privilege.getNumber()-1);
}


// Utility

std::string Role::toString() const
{
    return toStringInternal(false);
}

std::string Role::toStringInternal(bool showAll) const
{
    std::stringstream s;

    s <<
        "Role:"                                           << "\n" <<
        "  userIdentifier  = " << getUserIdentifier()     << "\n" <<
        "  userName        = " << getUserName()           << "\n" <<
                                                             "\n" <<
        "  studyIdentifier = " << getStudyIdentifier()    << "\n" <<
        "  studyName       = " << getStudyName()          << "\n"
    ;

    if (showAll)
        s <<
                                                             "\n" <<
        "  roleLocation    = " << getRoleLocation()       << "\n"
        ;

    s <<
                                                            "\n" <<
        "  privilegeSet"                                 << "\n" 
    ;

    for (int i = 1;  i <= Privilege::NUMBER_OF_PRIVILEGES;  ++i)
    {
        Privilege privilege = Privilege::valueOf(i);

        s << "    ";
        s << (getPrivilege(privilege) ? "yes " : "no  ");
        s << privilege.getName();
        s << "\n";
    }

    return s.str();
}

// end Role.cpp
