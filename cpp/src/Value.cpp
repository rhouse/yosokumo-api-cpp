// Value.cpp

#include <cassert>

#include "Value.h"

using namespace Yosokumo;


Value::Value(Type type, int64_t ival) : valueType(type), int_value(ival)
{}

Value::Value(Type type, uint64_t uval) : valueType(type), uint_value(uval)
{}

Value::Value(Type type, double dval) : valueType(type), double_value(dval)
{}

Value::Value() : valueType(EMPTY), uint_value(0)
{}

Value::Type Value::getType() const
{
    return valueType;
}

void *Value::getEmptyValue() const
{
    assert(getType() == EMPTY);
    return NULL;
}

uint64_t Value::getNaturalValue() const
{
    assert(getType() == NATURAL);
    return uint_value;
}

uint64_t Value::getSpecialValue() const
{
    assert(getType() == SPECIAL);
    return uint_value;
}

int64_t Value::getIntegerValue() const
{
    assert(getType() == INTEGER);
    return int_value;
}

double Value::getRealValue() const
{
    assert(getType() == REAL);
    return double_value;
}

// Equality operators

bool Value::operator==(const Value &rhs) const 
{
    if (getType() != rhs.getType())
        return false;

    bool equal;

    switch (getType())
    {
    case EMPTY:   equal = (getEmptyValue()   == rhs.getEmptyValue());    break;
    case NATURAL: equal = (getNaturalValue() == rhs.getNaturalValue());  break;
    case INTEGER: equal = (getIntegerValue() == rhs.getIntegerValue());  break;
    case REAL:    equal = (getRealValue()    == rhs.getRealValue());     break;
    case SPECIAL: equal = (getSpecialValue() == rhs.getSpecialValue());  break;
    default:      assert(false);  break;
    }

    return equal;
}

bool Value::operator!=(const Value &rhs) const
{
    return !(*this == rhs);
}

std::string Value::toString() const
{
    return "Value::toString was called, and it probably should not have been";
}

// end Value.cpp
