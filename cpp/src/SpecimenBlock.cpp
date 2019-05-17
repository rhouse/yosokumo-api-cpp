// SpecimenBlock.h

#include "SpecimenBlock.h"

using namespace Yosokumo;

// Constructors

SpecimenBlock::SpecimenBlock() : Block()
{
    setType(SPECIMEN);
}

SpecimenBlock::SpecimenBlock(std::string id) : Block(id)
{
    setType(SPECIMEN);
}

SpecimenBlock::SpecimenBlock(
    std::vector<Specimen>::iterator begin, 
    std::vector<Specimen>::iterator end) : Block()
{
    setType(SPECIMEN);
    addSpecimens(begin, end);
}

SpecimenBlock::SpecimenBlock(
    std::list<Specimen>::iterator begin, 
    std::list<Specimen>::iterator end) : Block()
{
    setType(SPECIMEN);
    addSpecimens(begin, end);
}

SpecimenBlock::SpecimenBlock(
    std::string id,
    std::vector<Specimen>::iterator begin, 
    std::vector<Specimen>::iterator end) : Block(id)
{
    setType(SPECIMEN);
    addSpecimens(begin, end);
}

SpecimenBlock::SpecimenBlock(
    std::string id,
    std::list<Specimen>::iterator begin, 
    std::list<Specimen>::iterator end) : Block(id)
{
    setType(SPECIMEN);
    addSpecimens(begin, end);
}

SpecimenBlock::~SpecimenBlock()
{}


// Access to the specimen sequence

void SpecimenBlock::addSpecimen(Specimen* specimen)
{
    specimenSequence.push_back(specimen);
}

bool SpecimenBlock::addSpecimens(
    std::vector<Specimen>::iterator begin, 
    std::vector<Specimen>::iterator end)
{
    bool changed = false;

    for (std::vector<Specimen>::iterator i = begin;  i != end;  ++i)
    {
        addSpecimen(&(*i));
        changed = true;
    }

    return changed;
}

bool SpecimenBlock::addSpecimens(
    std::list<Specimen>::iterator begin, 
    std::list<Specimen>::iterator end)
{
    bool changed = false;

    for (std::list<Specimen>::iterator i = begin;  i != end;  ++i)
    {
        addSpecimen(&(*i));
        changed = true;
    }

    return changed;
}

bool SpecimenBlock::removeSpecimens(uint64_t numSpecimensToRemove)
{
    if (numSpecimensToRemove == 0 || isEmpty())
        return false;

    if (numSpecimensToRemove >= size())
        clearSpecimens();
    else
        specimenSequence.erase(
            specimenSequence.end()-numSpecimensToRemove,
            specimenSequence.end());

    return true;
}

Specimen *SpecimenBlock::getSpecimen(uint64_t index) const
{
    return specimenSequence[index];
}


void SpecimenBlock::clearSpecimens()
{
    specimenSequence.clear();
}

uint64_t SpecimenBlock::size() const
{
    return specimenSequence.size();
}

bool SpecimenBlock::isEmpty() const
{
    return specimenSequence.empty();
}


// Utility

std::string SpecimenBlock::toString()
{
    std::stringstream s;

    s <<
    "SpecimenBlock:"                               << '\n' <<
    "  type            = " << getType()            << '\n' <<
    "  studyIdentifier = " << getStudyIdentifier() << '\n';

    for (uint64_t i = 0;  i < size();  ++i)
    {
        Specimen* sp = getSpecimen(i);

        s << "\n" << "  " << sp->toString();
    }

    return s.str();
}


/** Output stream insertion operator.
 *
 * @param  os  the output stream.
 * @param  sb  the <code>SpecimenBlock</code> to insert in the stream.
 *
 * @return the output stream.
 */
std::ostream &operator<<(std::ostream &os, SpecimenBlock &sb)
{
    os << sb.toString();
    return os;
}

/** String stream insertion operator.
 *
 * @param  s   the string stream.
 * @param  sb  the <code>SpecimenBlock</code> to insert in the stream.
 *
 * @return the string stream.
 */
std::stringstream &operator<<(std::stringstream &s, SpecimenBlock &sb)
{
    s << sb.toString();
    return s;
}

// end SpecimenBlock.h
