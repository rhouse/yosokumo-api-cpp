// RealValue.cpp

#include <sstream>

#include "RealValue.h"

using namespace Yosokumo;


RealValue::RealValue(double value) : Value(REAL, value)
{}

double RealValue::getValue() const
{
    return double_value;
}

std::string RealValue::toString() const
{
    // See p570 of Standard C++ IOStreams and Locales:  It looks like by
    // setting the precision to 17 the conversion from double to string 
    // uses %0.17g as the format, which is what we want (or should it be 16?)
    std::stringstream s;
    s.precision(17);
    s << double_value;
    return s.str();
}

// end RealValue.cpp
