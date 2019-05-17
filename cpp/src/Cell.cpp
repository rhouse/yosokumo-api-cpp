// Cell.cpp


#include <cassert>
#include <sstream>

#include "Cell.h"
#include "EmptyValue.h"

using namespace Yosokumo;


Cell::Cell()
{
    nameOrKey = 0;
    value = EmptyValue();
}

Cell::Cell(uint64_t nameOrKey, const Value &value)
{
    assert(nameOrKey >= 0);

    this->nameOrKey = nameOrKey;
    this->value     = value;
}

// Setters and getters

void Cell::setName(uint64_t name)
{
    nameOrKey = name;
}

uint64_t Cell::getName() const
{
    return nameOrKey;
}

void Cell::setKey(uint64_t key)
{
    nameOrKey = key;
}

uint64_t Cell::getKey() const
{
    return nameOrKey;
}

void Cell::setValue(const Value &value)
{
    this->value = value;
}

Value Cell::getValue() const
{
    return value;
}

// Equality operators

bool Cell::operator==(const Cell &rhs) const 
{
    return
    (
        nameOrKey == rhs.nameOrKey &&
        value     == rhs.value
    );
}

bool Cell::operator!=(const Cell &rhs) const
{
    return !(*this == rhs);
}

std::string Cell::toString() const
{
    std::stringstream s;
    s << 
    "Cell: nameOrKey=" << nameOrKey << " value=" << value.toString() << "\n";
    return s.str();
}

// end Cell.cpp
