
// Specimen.cpp

#include <sstream>

#include "Specimen.h"
#include "EmptyValue.h"

using namespace Yosokumo;

// Constructors

Specimen::Specimen()
{
    setSpecimenKey(0);
    setStatus     (Specimen::ACTIVE);
    setWeight     (1);
    setPredictand (EmptyValue());
}

Specimen::Specimen(uint64_t key)
{
    setSpecimenKey(key);
    setStatus     (Specimen::ACTIVE);
    setWeight     (1);
    setPredictand (EmptyValue());
}

Specimen::Specimen
(
    uint64_t key, 
    std::vector<Cell>::iterator begin,
    std::vector<Cell>::iterator end
)
{
    addCells(begin, end);
    setSpecimenKey(key);
    setStatus     (Specimen::ACTIVE);
    setWeight     (1);
    setPredictand (EmptyValue());
}

Specimen::Specimen
(
    uint64_t key, 
    std::list<Cell>::iterator begin,
    std::list<Cell>::iterator end
)
{
    addCells(begin, end);
    setSpecimenKey(key);
    setStatus     (Specimen::ACTIVE);
    setWeight     (1);
    setPredictand (EmptyValue());
}

Specimen::Specimen
(
    uint64_t    key,
    Value       predictand,
    std::vector<Cell>::iterator begin,
    std::vector<Cell>::iterator end
)
{
    addCells(begin, end);
    setSpecimenKey(key);
    setStatus     (Specimen::ACTIVE);
    setWeight     (1);
    setPredictand (predictand);
}

Specimen::Specimen
(
    uint64_t    key,
    Value       predictand,
    std::list<Cell>::iterator begin,
    std::list<Cell>::iterator end
)
{
    addCells(begin, end);
    setSpecimenKey(key);
    setStatus     (Specimen::ACTIVE);
    setWeight     (1);
    setPredictand (predictand);
}

Specimen::Specimen
(
    uint64_t    key,
    Status      status,
    uint64_t    weight,
    Value       predictand,
    std::vector<Cell>::iterator begin,
    std::vector<Cell>::iterator end
)
{
    addCells(begin, end);
    setSpecimenKey(key);
    setStatus     (status);
    setWeight     (weight);
    setPredictand (predictand);
}

Specimen::Specimen
(
    uint64_t    key,
    Status      status,
    uint64_t    weight,
    Value       predictand,
    std::list<Cell>::iterator begin,
    std::list<Cell>::iterator end
)
{
    addCells(begin, end);
    setSpecimenKey(key);
    setStatus     (status);
    setWeight     (weight);
    setPredictand (predictand);
}

Specimen::Specimen(const Specimen &rhs)
{
    operator=(rhs);
}

Specimen::~Specimen()
{}

Specimen &Specimen::operator=(const Specimen &rhs)
{
    if (this == &rhs)
        return *this;

    key        = rhs.key       ;
    status     = rhs.status    ;
    weight     = rhs.weight    ;
    predictand = rhs.predictand;

    Specimen &r = const_cast<Specimen &>(rhs);

    addCells(r.cellSequence.begin(), r.cellSequence.end());

    return *this;
}


// Setters and getters

void Specimen::setSpecimenKey(uint64_t key)
{
    this->key = key;
}

uint64_t Specimen::getSpecimenKey() const
{
    return key;
}


void Specimen::setStatus(Status s)
{
    status = s;
}

Specimen::Status Specimen::getStatus() const
{
    return status;
}


void Specimen::setWeight(uint64_t w)
{
    weight = w;
}

uint64_t Specimen::getWeight() const
{
    return weight;
}


void Specimen::setPredictand(Value v)
{
    predictand = v;
}

Value Specimen::getPredictand() const
{
    return predictand;
}


// Access to the cell sequence

void Specimen::addCell(const Cell &cell)
{
    cellSequence.push_back(cell);
}


bool Specimen::addCells
(
    std::vector<Cell>::iterator begin, 
    std::vector<Cell>::iterator end
)
{
    unsigned old_size = cellSequence.size();
    cellSequence.insert(cellSequence.end(), begin, end);
    return cellSequence.size() != old_size;
}

bool  Specimen::addCells
(
    std::list<Cell>::iterator begin, 
    std::list<Cell>::iterator end
)
{
    unsigned old_size = cellSequence.size();
    cellSequence.insert(cellSequence.end(), begin, end);
    return cellSequence.size() != old_size;
}

bool  Specimen::removeCells(uint64_t numCellsToRemove)
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


Cell  Specimen::getCell(int index) const
{
    return cellSequence.at(index);
}

void  Specimen::clearCells()
{
    cellSequence.clear();
}

uint64_t  Specimen::size() const
{
    return cellSequence.size();
}

bool Specimen::isEmpty() const
{
    return cellSequence.empty();
}


// Utility

std::string Specimen::toString() const
{
    std::stringstream s;
    s <<
        "Specimen:"                           << "\n" <<
        "  key        = " << getSpecimenKey() << "\n" <<
                                                 "\n" <<
        "  status     = " << getStatus()      << "\n" <<
        "  weight     = " << getWeight()      << "\n" <<
        "  predictand = " << predictand.toString() << "\n";

    for (uint64_t i = 0;  i < size();  ++i)
    {
        Cell c = getCell(i);

        s << "  " << c.toString();
    }

    return s.str();
}

// end Specimen.cpp
