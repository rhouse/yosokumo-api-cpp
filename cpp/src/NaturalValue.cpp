// NaturalValue.cpp

#include <sstream>

#include "NaturalValue.h"

using namespace Yosokumo;


NaturalValue::NaturalValue(uint64_t value) : Value(NATURAL, value)
{}

uint64_t NaturalValue::getValue() const
{
    return uint_value;
}

std::string NaturalValue::toString() const
{
    std::stringstream s;
    s << uint_value;
    return s.str();
}

// end NaturalValue.cpp
