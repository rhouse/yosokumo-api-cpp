// Roster.cpp

#include <sstream>
#include <cassert>

#include "Roster.h"

using namespace Yosokumo;

// Constructors

Roster::Roster() :
    studyIdentifier(""),
    studyName(""),
    rosterLocation("")
{
}

Roster::Roster(
    const std::string &studyIdentifier, 
    const std::string &studyName) :
        studyIdentifier(studyIdentifier),
        studyName(studyName),
        rosterLocation("")
{
}

// Equality operators

bool Roster::operator==(const Roster &rhs) const
{
    if
    (!(
        studyIdentifier  == rhs.studyIdentifier  &&
        studyName        == rhs.studyName        &&
        rosterLocation   == rhs.rosterLocation &&
        size()           == rhs.size()
    ))
        return false;

    RoleConstIterator iter;
 
    for (iter = begin();  iter != end();  ++iter)
    {
        Role role = iter->second;
        const std::string userIdentifier = role.getUserIdentifier();
        Role rhsRole;

        if (!rhs.getRole(userIdentifier, rhsRole))
            return false;
        
        if (role != rhsRole)
            return false;
    }

    return true;
}

bool Roster::operator!=(const Roster &rhs) const
{
    return !(*this == rhs);
}


// Setters and getters

void Roster::setStudyIdentifier(const std::string &id)
{
    studyIdentifier = id;
}

std::string Roster::getStudyIdentifier() const
{
    return studyIdentifier;
}

void Roster::setStudyName(const std::string &name)
{
    studyName = name;
}

std::string Roster::getStudyName() const
{
    return studyName;
}

void Roster::setRosterLocation(const std::string &loc)
{
    rosterLocation = loc;
}

std::string Roster::getRosterLocation() const
{
    return rosterLocation;
}

// Access to the role collection

bool Roster::addRole(const Role &newRole, Role &oldRole)
{
    std::pair<std::string, Role> keyRole = 
        std::make_pair(newRole.getUserIdentifier(), newRole);

    std::pair<RoleIterator, bool> ret;

    ret = roleCollection.insert(keyRole);

    if (ret.second)
        return true;

    RoleIterator iter = ret.first;
    oldRole = iter->second;

    roleCollection.erase(ret.first);

    ret = roleCollection.insert(keyRole);

    assert(ret.second);

    return false;
}

bool Roster::addRole(const Role &newRole)
{
    Role oldRole;

    return addRole(newRole, oldRole);
}

bool Roster::removeRole(const std::string &userIdentifier)
{
    return (roleCollection.erase(userIdentifier) == 1);
}

void Roster::clearRoles()
{
    roleCollection.clear();
}

bool Roster::getRole(const std::string &userIdentifier, Role &foundRole) const
{
    RoleConstIterator iter;

    iter = roleCollection.find(userIdentifier);

    if (iter == roleCollection.end())
        return false;

    foundRole = iter->second;

    return true;
}

bool Roster::containsRole(std::string userIdentifier) const
{
    return (roleCollection.find(userIdentifier) != roleCollection.end());
}

int Roster::size() const
{
    return roleCollection.size();
}

bool Roster::isEmpty() const
{
    return roleCollection.empty();
}

Roster::RoleIterator Roster::begin()
{
    return roleCollection.begin();
}

Roster::RoleConstIterator Roster::begin() const
{
    return roleCollection.begin();
}

Roster::RoleIterator Roster::end()
{
    return roleCollection.end();
}

Roster::RoleConstIterator Roster::end() const
{
    return roleCollection.end();
}


// Utility

std::string Roster::toString() const
{
    return toStringInternal(false);
}

std::string Roster::toStringInternal(bool showAll) const
{
    std::stringstream s;

    s <<
        "Roster:"                                      << "\n" <<
        "  studyIdentifier = " << getStudyIdentifier() << "\n" <<
        "  studyName       = " << getStudyName()       << "\n"
    ;

    if (showAll)
        s <<
            "  rosterLocation  = " << getRosterLocation()  << "\n"
        ;

    s <<
        "  Roles:"                                     << "\n"
    ;

    RoleConstIterator iter;
 
    for (iter = begin();  iter != end();  ++iter)
    {
        Role role = iter->second;
        s << "    " << role.getUserIdentifier();
        s << "    " << role.getUserName() << "\n";
    }

    return s.str();
}

// end Roster.cpp
