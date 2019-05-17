// EmptyBlock.cpp

#include "EmptyBlock.h"

using namespace Yosokumo;

EmptyBlock::EmptyBlock()
{}

EmptyBlock::EmptyBlock(std::string id) : Block(id)
{}

EmptyBlock::~EmptyBlock()
{}

Block::Type EmptyBlock::getType() const
{
    return EMPTY;
}

std::string EmptyBlock::toString()
{
    return "<empty block>";
}

// end EmptyBlock.cpp
