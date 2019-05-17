// CellBlock.cpp

#include "CellBlock.h"

using namespace Yosokumo;

// Constructors and destructor

CellBlock::CellBlock() : Block()
{
    setType(CELL);
}

CellBlock::CellBlock(std::string id) : Block(id)
{
    setType(CELL);
}

CellBlock::CellBlock(
    std::vector<Cell>::iterator begin, 
    std::vector<Cell>::iterator end) : Block()
{
    setType(CELL);
    addCells(begin, end);
}

CellBlock::CellBlock(
    std::list<Cell>::iterator begin, 
    std::list<Cell>::iterator end) : Block()
{
    setType(CELL);
    addCells(begin, end);
}

CellBlock::CellBlock(
    std::string id, 
    std::vector<Cell>::iterator begin, 
    std::vector<Cell>::iterator end) : Block(id)
{
    setType(CELL);
    addCells(begin, end);
}

CellBlock::CellBlock(
    std::string id, 
    std::list<Cell>::iterator begin, 
    std::list<Cell>::iterator end) : Block(id)
{
    setType(CELL);
    addCells(begin, end);
}

CellBlock::~CellBlock()
{}


// Access to the cell sequence

void CellBlock::addCell(const Cell &cell)
{
    cellSequence.push_back(cell);
}

bool CellBlock::addCells(
    std::vector<Cell>::iterator begin, 
    std::vector<Cell>::iterator end)
{
    unsigned old_size = cellSequence.size();
    cellSequence.insert(cellSequence.end(), begin, end);
    return cellSequence.size() != old_size;
}

bool CellBlock::addCells(
    std::list<Cell>::iterator begin, 
    std::list<Cell>::iterator end)
{
    unsigned old_size = cellSequence.size();
    cellSequence.insert(cellSequence.end(), begin, end);
    return cellSequence.size() != old_size;
}

bool CellBlock::removeCells(uint64_t numCellsToRemove)
{
    if (numCellsToRemove == 0 || isEmpty())
        return false;

    if (numCellsToRemove >= size())
        clearCells();
    else
        cellSequence.erase(
            cellSequence.end()-numCellsToRemove, 
            cellSequence.end());

    return true;
}


Cell CellBlock::getCell(uint64_t index) const
{
    return cellSequence.at(index);
}


void CellBlock::clearCells()
{
    cellSequence.clear();
}

uint64_t CellBlock::size() const
{
    return cellSequence.size();
}

bool CellBlock::isEmpty() const
{
    return cellSequence.empty();
}


std::string CellBlock::toString()
{
    std::stringstream s;

    s <<
    "CellBlock:"                                   << '\n' <<
    "  type            = " << getType()            << '\n' <<
    "  studyIdentifier = " << getStudyIdentifier() << '\n';

    for (uint64_t i = 0;  i < size();  ++i)
    {
        Cell c = getCell(i);

        s << "\n" << "  " << c.toString();
    }

    return s.str();
}

std::ostream &operator<<(std::ostream &os, CellBlock &p)
{
    os << p.toString();
    return os;
}

std::stringstream &operator<<(std::stringstream &s, CellBlock &p)
{
    s << p.toString();
    return s;
}

// end CellBlock.cpp
