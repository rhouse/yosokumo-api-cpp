// PredictorTest.cpp  -  Test the Predictor class with UnitTest++

#include "UnitTest++.h"
#include "Predictor.h"

#include <string>
#include <iostream>

using namespace Yosokumo;

TEST(defaultConstructorForPredictor)
{
    std::cout << "PredictorTest defaultConstructorForPredictor" << '\n';

    Predictor predictor;

    CHECK_EQUAL(predictor.getPredictorName(), 1);
    CHECK_EQUAL(predictor.getStatus()       , Predictor::ACTIVE);
    CHECK_EQUAL(predictor.getType()         , Predictor::CONTINUOUS);
    CHECK_EQUAL(predictor.getLevel()        , Predictor::RATIO);
}

TEST(minimalConstructorForPredictor)
{
    std::cout << "PredictorTest minimalConstructorForPredictor" << '\n';

    Predictor predictor(123456789);

    CHECK_EQUAL(predictor.getPredictorName(), 123456789);
    CHECK_EQUAL(predictor.getStatus()       , Predictor::ACTIVE);
    CHECK_EQUAL(predictor.getType()         , Predictor::CONTINUOUS);
    CHECK_EQUAL(predictor.getLevel()        , Predictor::RATIO);
}

TEST(usualConstructorForPredictor)
{
    std::cout << "PredictorTest usualConstructorForPredictor" << '\n';

    Predictor predictor(
        987654321, 
        Predictor::INACTIVE,
        Predictor::CATEGORICAL,
        Predictor::NOMINAL);
    CHECK_EQUAL(predictor.getPredictorName(), 987654321);
    CHECK_EQUAL(predictor.getStatus()       , Predictor::INACTIVE);
    CHECK_EQUAL(predictor.getType()         , Predictor::CATEGORICAL);
    CHECK_EQUAL(predictor.getLevel()        , Predictor::NOMINAL);
}

TEST(copyConstructorForPredictor)
{
    std::cout << "PredictorTest copyConstructorForPredictor" << '\n';

    Predictor predictor(
        987654321, 
        Predictor::INACTIVE,
        Predictor::CATEGORICAL,
        Predictor::NOMINAL);
    Predictor predictor2(predictor);

    CHECK_EQUAL(predictor2.getPredictorName(), 987654321);
    CHECK_EQUAL(predictor2.getStatus()       , Predictor::INACTIVE);
    CHECK_EQUAL(predictor2.getType()         , Predictor::CATEGORICAL);
    CHECK_EQUAL(predictor2.getLevel()        , Predictor::NOMINAL);
}

TEST(assignmentOperatorForPredictor)
{
    std::cout << "PredictorTest assignmentOperatorForPredictor" << '\n';

    Predictor predictor(
        987654321, 
        Predictor::INACTIVE,
        Predictor::CATEGORICAL,
        Predictor::NOMINAL);

    Predictor predictor2;
    predictor2 = predictor;

    CHECK_EQUAL(predictor2.getPredictorName(), 987654321);
    CHECK_EQUAL(predictor2.getStatus()       , Predictor::INACTIVE);
    CHECK_EQUAL(predictor2.getType()         , Predictor::CATEGORICAL);
    CHECK_EQUAL(predictor2.getLevel()        , Predictor::NOMINAL);
}

TEST(equalityOperatorsForPredictor)
{
    std::cout << "PredictorTest equalityOperatorsForPredictor" << '\n';

    Predictor predictor(
        987654321, 
        Predictor::INACTIVE,
        Predictor::CATEGORICAL,
        Predictor::NOMINAL);

    Predictor predictor2(predictor);

    CHECK(  predictor == predictor2 );
    CHECK(!(predictor != predictor2));

    predictor2.setPredictorName(314159);
    CHECK(!(predictor == predictor2));
    CHECK(  predictor != predictor2 );
    predictor2.setPredictorName(987654321);

    predictor2.setStatus(Predictor::ACTIVE);
    CHECK(!(predictor == predictor2));
    CHECK(  predictor != predictor2 );
    predictor2.setStatus(Predictor::INACTIVE);

    predictor2.setType(Predictor::CONTINUOUS);
    CHECK(!(predictor == predictor2));
    CHECK(  predictor != predictor2 );
    predictor2.setType(Predictor::CATEGORICAL);

    predictor2.setLevel(Predictor::RATIO);
    CHECK(!(predictor == predictor2));
    CHECK(  predictor != predictor2 );
    predictor2.setLevel(Predictor::NOMINAL);

    CHECK(  predictor == predictor2 );
    CHECK(!(predictor != predictor2));
}

TEST(settersAndGettersForPredictor)
{
    std::cout << "PredictorTest settersAndGettersForPredictor" << '\n';

    Predictor predictor(314159);

    predictor.setPredictorName(951413);
    predictor.setStatus(Predictor::INACTIVE);
    predictor.setType  (Predictor::CATEGORICAL);
    predictor.setLevel (Predictor::ORDINAL);

    CHECK_EQUAL(predictor.getPredictorName(), 951413);
    CHECK_EQUAL(predictor.getStatus()       , Predictor::INACTIVE);
    CHECK_EQUAL(predictor.getType()         , Predictor::CATEGORICAL);
    CHECK_EQUAL(predictor.getLevel()        , Predictor::ORDINAL);
}

TEST(stringStreamInsertionOperatorForPredictor)
{
    std::cout << "PredictorTest stringStreamInsertionOperatorForPredictor" << '\n';

    std::stringstream s;

    Predictor predictor;
    std::string expect = 
        "Predictor:\n"
        "  name   = 1\n"
        "  status = 0\n"
        "  type   = 1\n"
        "  level  = 3\n";
    s << predictor;
    CHECK_EQUAL(expect, s.str());
    s.str("");

    Predictor predictor2(
        123456789012345,
        Predictor::INACTIVE,
        Predictor::CATEGORICAL,
        Predictor::INTERVAL);
    expect = 
        "Predictor:\n"
        "  name   = 123456789012345\n"
        "  status = 1\n"
        "  type   = 0\n"
        "  level  = 2\n";
    s << predictor2;
    CHECK_EQUAL(expect, s.str());
}

// end PredictorTest.cpp
