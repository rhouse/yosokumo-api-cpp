// SpecialValue.cpp

#include <sstream>

#include "SpecialValue.h"

using namespace Yosokumo;


SpecialValue::SpecialValue(uint64_t value) : Value(SPECIAL, value)
{}

uint64_t SpecialValue::getValue() const
{
    return uint_value;
}

std::string SpecialValue::toString() const
{
    std::stringstream s;
    s << uint_value;
    return s.str();
}

// end SpecialValue.cpp
