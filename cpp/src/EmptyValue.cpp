// EmptyValue.cpp

#include "EmptyValue.h"

using namespace Yosokumo;


EmptyValue::EmptyValue() : Value(EMPTY, uint64_t(0))
{}

void *EmptyValue::getValue() const
{
    return NULL;
}

std::string EmptyValue::toString() const
{
    return "<empty value>";
}

// end EmptyValue.cpp
