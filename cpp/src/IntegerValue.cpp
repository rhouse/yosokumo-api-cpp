// IntegerValue.cpp

#include <sstream>

#include "IntegerValue.h"

using namespace Yosokumo;


IntegerValue::IntegerValue(int64_t value) : Value(INTEGER, value)
{}

int64_t IntegerValue::getValue() const
{
    return int_value;
}

std::string IntegerValue::toString() const
{
    std::stringstream s;
    s << int_value;
    return s.str();
}

// end IntegerValue.cpp
