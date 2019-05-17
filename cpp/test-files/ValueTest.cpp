// ValueTest.cpp  -  Test the Value class and its subclasses with UnitTest++

#include <cmath>

#include "UnitTest++.h"
#include "EmptyValue.h"
#include "IntegerValue.h"
#include "NaturalValue.h"
#include "RealValue.h"
#include "SpecialValue.h"

#include <iostream>

using namespace Yosokumo;


TEST(integerValue)
{
    std::cout << "ValueTest integerValue" << '\n';

    IntegerValue intval(314159);
    CHECK_EQUAL(intval.getType()   , Value::INTEGER);
    CHECK_EQUAL(intval.getValue()  , 314159);
    CHECK_EQUAL(intval.toString()  , "314159");
    CHECK(intval.getValue() != 314158);
    IntegerValue intval1(314159);
    CHECK(intval == intval1);
    IntegerValue intval2(314159+2);
    CHECK(intval != intval2);

    int64_t big = 9223372036854775807;

    IntegerValue maxint(big);
    CHECK_EQUAL(maxint.getType()   , Value::INTEGER);
    CHECK_EQUAL(maxint.getValue()  , big);
    CHECK_EQUAL(maxint.toString()  , "9223372036854775807");

    int64_t small = -9223372036854775807;

    IntegerValue minint(small);
    CHECK_EQUAL(minint.getType()   , Value::INTEGER);
    CHECK_EQUAL(minint.getValue()  , small);
    CHECK_EQUAL(minint.toString()  , "-9223372036854775807");
}

TEST(naturalValue)
{
    std::cout << "ValueTest naturalValue" << '\n';

    NaturalValue natval(314159);
    CHECK_EQUAL(natval.getType()   , Value::NATURAL);
    CHECK_EQUAL(natval.getValue()  , 314159U);
    CHECK_EQUAL(natval.toString()  , "314159");
    CHECK(natval.getValue() != 314158);
    NaturalValue natval1(314159);
    CHECK(natval == natval1);
    NaturalValue natval2(314159+2);
    CHECK(natval != natval2);

    uint64_t big = 18446744073709551615UL;

    NaturalValue maxnat(big);
    CHECK_EQUAL(maxnat.getType()   , Value::NATURAL);
    CHECK_EQUAL(maxnat.getValue()  , big);
    CHECK_EQUAL(maxnat.toString()  , "18446744073709551615");

    uint64_t small = 0;

    NaturalValue minnat(small);
    CHECK_EQUAL(minnat.getType()   , Value::NATURAL);
    CHECK_EQUAL(minnat.getValue()  , small);
    CHECK_EQUAL(minnat.toString()  , "0");
}

TEST(specialValue)
{
    std::cout << "ValueTest specialValue" << '\n';

    SpecialValue specval(314159);
    CHECK_EQUAL(specval.getType()   , Value::SPECIAL);
    CHECK_EQUAL(specval.getValue()  , 314159U);
    CHECK_EQUAL(specval.toString()  , "314159");
    CHECK(specval.getValue() != 314158);
    SpecialValue specval1(314159);
    CHECK(specval == specval1);
    SpecialValue specval2(314159+2);
    CHECK(specval != specval2);

    uint64_t big = 18446744073709551615UL;

    SpecialValue maxspec(big);
    CHECK_EQUAL(maxspec.getType()   , Value::SPECIAL);
    CHECK_EQUAL(maxspec.getValue()  , big);
    CHECK_EQUAL(maxspec.toString()  , "18446744073709551615");

    uint64_t small = 0;

    SpecialValue minspec(small);
    CHECK_EQUAL(minspec.getType()   , Value::SPECIAL);
    CHECK_EQUAL(minspec.getValue()  , small);
    CHECK_EQUAL(minspec.toString()  , "0");
}

TEST(emptyValue)
{
    std::cout << "ValueTest emptyValue" << '\n';

    EmptyValue emptyval;
    CHECK_EQUAL(emptyval.getType()   , Value::EMPTY);
    CHECK_EQUAL(emptyval.getValue()  , (void*)0);
    CHECK_EQUAL(emptyval.toString()  , "<empty value>");
    EmptyValue emptyval1;
    CHECK(emptyval == emptyval1);
    IntegerValue intval(103);
    CHECK(emptyval != intval);
}

TEST(realValue)
{
    std::cout << "ValueTest realValue" << '\n';

    RealValue realval(314159);
    CHECK_EQUAL(realval.getType()   , Value::REAL);
    CHECK_EQUAL(realval.getValue()  , 314159);
    CHECK_EQUAL(realval.toString()  , "314159");
    CHECK(realval.getValue() != 314158);
    RealValue realval1(314159);
    CHECK(realval == realval1);
    RealValue realval2(314159+2);
    CHECK(realval != realval2);

    double sqrt2 = sqrt(2);

    RealValue x(sqrt2);
    CHECK_EQUAL(x.getType()   , Value::REAL);
    CHECK_EQUAL(x.getValue()  , sqrt2);
    CHECK_EQUAL(x.toString()  , "1.4142135623730951");

    RealValue x1(3.14);
    CHECK_EQUAL(x1.toString() , "3.1400000000000001");

    RealValue x2(0.75);
    CHECK_EQUAL(x2.toString()  , "0.75");

    RealValue x3(1234567890.1234567);
    CHECK_EQUAL(x3.toString()  , "1234567890.1234567");

    RealValue x4(-1234567890.1234567);
    CHECK_EQUAL(x4.toString()  , "-1234567890.1234567");

    RealValue x5(1e100);
    CHECK_EQUAL(x5.toString()  , "1e+100");

    RealValue x6(-1e-100);
    CHECK_EQUAL(x6.toString()  , "-1e-100");

    RealValue x7(12345678901234567890.12345678901234567890);
    CHECK_EQUAL(x7.toString()  , "1.2345678901234567e+19");
}

// end ValueTest.cpp
