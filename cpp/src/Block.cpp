// Block.cpp

#include "Block.h" 

using namespace Yosokumo;

Block::Block() : type(EMPTY), studyIdentifier("")
{
    cellSequence.clear();
    predictorSequence.clear();
    specimenSequence.clear();
}

Block::Block(std::string id) : type(EMPTY), studyIdentifier(id)
{
    cellSequence.clear();
    predictorSequence.clear();
    specimenSequence.clear();
}

Block::~Block()
{}

void Block::setType(Type t)
{
    type = t;
}

Block::Type Block::getType() const
{
    return type;
}

void Block::setStudyIdentifier(std::string id)
{
    studyIdentifier = id;
}

std::string Block::getStudyIdentifier() const
{
    return studyIdentifier;
}

std::string Block::toString()
{
    std::stringstream s;

    s <<
    "Block:"                                       << '\n' <<
    "  type            = " << getType()            << '\n' <<
    "  studyIdentifier = " << getStudyIdentifier() << '\n';

    return s.str();
}

// end Block.cpp
