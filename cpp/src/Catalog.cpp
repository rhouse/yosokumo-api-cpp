// Catalog.h

#include <cassert>
#include <sstream>

#include "Catalog.h"

using namespace Yosokumo;

Catalog::Catalog() :
    userIdentifier ("ABCDEF0123456789"),
    userName       (""),
    catalogLocation("")
{}

Catalog::Catalog(
    const std::string &userIdentifier, 
    const std::string &userName) :
        userIdentifier (userIdentifier),
        userName       (userName),
        catalogLocation("")
{}

Catalog::Catalog(const Catalog &rhs)
{
    operator=(rhs);
}

Catalog::~Catalog()
{}

Catalog &Catalog::operator=(const Catalog& rhs)
{
    if (this == &rhs)
        return *this;

     copyCatalog(*this, rhs);

    return *this;
}

// Equality operators

bool Catalog::operator==(const Catalog &rhs) const
{
    if
    (!(
        userIdentifier  == rhs.userIdentifier  &&
        userName        == rhs.userName        &&
        catalogLocation == rhs.catalogLocation &&
        size()          == rhs.size()
    ))
        return false;

    StudyConstIterator iter;
 
    for (iter = begin();  iter != end();  ++iter)
    {
        Study study = iter->second;
        const std::string studyIdentifier = study.getStudyIdentifier();
        Study rhsStudy;

        if (!rhs.getStudy(studyIdentifier, rhsStudy))
            return false;
        
        if (study != rhsStudy)
            return false;
    }

    return true;
}

bool Catalog::operator!=(const Catalog &rhs) const
{
    return !(*this == rhs);
}

// Copy catalog

void Catalog::copyCatalog(Catalog &t, const Catalog &s)
{
    t.setUserIdentifier (s.getUserIdentifier() );
    t.setUserName       (s.getUserName()       );
    t.setCatalogLocation(s.getCatalogLocation());

    StudyConstIterator iter;
 
    for (iter = s.begin();  iter != s.end();  ++iter)
        t.addStudy(iter->second);
}


// Setters and getters

void Catalog::setUserIdentifier(const std::string &id)
{
    userIdentifier = id;
}

std::string Catalog::getUserIdentifier() const
{
    return userIdentifier;
}

void Catalog::setUserName(const std::string &name)
{
    userName = name;
}

std::string Catalog::getUserName() const
{
    return userName;
}

void Catalog::setCatalogLocation(const std::string &loc)
{
    catalogLocation = loc;
}

std::string Catalog::getCatalogLocation() const
{
    return catalogLocation;
}

// Access to the study collection

bool Catalog::addStudy(const Study &newStudy, Study &oldStudy)
{
    std::pair<std::string, Study> keyStudy = 
        std::make_pair(newStudy.getStudyIdentifier(), newStudy);

    std::pair<StudyIterator, bool> ret;

    ret = studyCollection.insert(keyStudy);

    if (ret.second)
        return true;

    StudyIterator iter = ret.first;
    oldStudy = iter->second;

    studyCollection.erase(ret.first);

    ret = studyCollection.insert(keyStudy);

    assert(ret.second);

    return false;
}

bool Catalog::addStudy(const Study &newStudy)
 {
     Study oldStudy;

     return addStudy(newStudy, oldStudy);
 }

bool Catalog::removeStudy(const std::string &studyIdentifier)
{
    return (studyCollection.erase(studyIdentifier) == 1);
}

void Catalog::clearStudies()
{
    studyCollection.clear();
}

bool Catalog::getStudy(const std::string &studyIdentifier, Study &foundStudy) const
{
    StudyConstIterator iter;

    iter = studyCollection.find(studyIdentifier);

    if (iter == studyCollection.end())
        return false;

    foundStudy = iter->second;

    return true;
}

bool Catalog::containsStudy(const std::string &studyIdentifier) const
{
    return (studyCollection.find(studyIdentifier) != studyCollection.end());
}

int Catalog::size() const
{
    return studyCollection.size();
}

bool Catalog::isEmpty() const
{
    return studyCollection.empty();
}

Catalog::StudyIterator Catalog::begin()
{
    return studyCollection.begin();
}

Catalog::StudyConstIterator Catalog::begin() const
{
    return studyCollection.begin();
}

Catalog::StudyIterator Catalog::end()
{
    return studyCollection.end();
}

Catalog::StudyConstIterator Catalog::end() const
{
    return studyCollection.end();
}


// Utility

std::string Catalog::toString() const
{
    return toStringInternal(false);
}

std::string Catalog::toStringInternal(bool showAll) const
{
    std::stringstream s;

    s <<
        "Catalog:"                                     << "\n" <<
        "  userIdentifier  = " << getUserIdentifier()  << "\n" <<
        "  userName        = " << getUserName()        << "\n"
    ;

    if (showAll)
        s <<
            "  catalogLocation = " << getCatalogLocation() << "\n"
        ;

    s <<
        "  Studies:" << "\n"
    ;

    StudyConstIterator iter;

    for (iter = begin();  iter != end();  ++iter)
    {
        Study study = iter->second;
        s << "    " << study.getStudyIdentifier();
        s << "    " << study.getStudyName() << "\n";
    }

    return s.str();
}

// end Catalog.h
