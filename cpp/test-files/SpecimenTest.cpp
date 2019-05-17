// SpecimenTest.cpp  -  Test the Specimen class with UnitTest++

#include "UnitTest++.h"
#include "Specimen.h"
#include "RealValue.h"
#include "IntegerValue.h"
#include "NaturalValue.h"

#include <iostream>

using namespace Yosokumo;

static void makeList(std::list<Cell> &cellList)
{
    cellList.push_back(Cell(11111, RealValue(99.999)));
    cellList.push_back(Cell(22222, RealValue(88.888)));
    cellList.push_back(Cell(33333, RealValue(77.777)));
}

static void verifyCell(const Cell &c, int i)
{
    switch (i)
    {
    case 1:  CHECK_EQUAL(c.getKey(), 11111UL);
             CHECK_EQUAL(c.getValue().getRealValue(), 99.999);
             break;

    case 2:  CHECK_EQUAL(c.getKey(), 22222UL);
             CHECK_EQUAL(c.getValue().getRealValue(), 88.888);
             break;

    case 3:  CHECK_EQUAL(c.getKey(), 33333UL);
             CHECK_EQUAL(c.getValue().getRealValue(), 77.777);
             break;

    default: CHECK(false);
    }
}

static void checkCellSequence(const Specimen &specimen)
{
    CHECK_EQUAL(specimen.size(), 3UL);
    CHECK(!specimen.isEmpty());

    // test getCellSequence -- use a for-loop with indices

    uint64_t i;

    for (i = 0;  i < specimen.size();  ++i)
    {
        Cell c = specimen.getCell(i);
        verifyCell(c, i+1);
    }

    CHECK_EQUAL(i, 3UL);

}   //  end checkCellSequence

TEST(minimalConstructorForSpecimen)
{
    std::cout << "SpecimenTest minimalConstructorForSpecimen" << '\n';

    std::list<Cell> cellList;
    makeList(cellList);

    Specimen specimen(123456789, cellList.begin(), cellList.end());

    CHECK_EQUAL(specimen.getSpecimenKey()         , 123456789UL);
    CHECK_EQUAL(specimen.getStatus()              , Specimen::ACTIVE);
    CHECK_EQUAL(specimen.getWeight()              , 1UL);
    CHECK_EQUAL(specimen.getPredictand().getType(), Value::EMPTY);
    checkCellSequence(specimen);
}


TEST(anotherConstructorForSpecimen)
{
    std::cout << "SpecimenTest anotherConstructorForSpecimen" << '\n';

    std::list<Cell> cellList;
    makeList(cellList);

    Specimen specimen(
        987654321UL, 
        RealValue(31.4159),
        cellList.begin(), cellList.end());

    CHECK_EQUAL(specimen.getSpecimenKey()         , 987654321UL);
    CHECK_EQUAL(specimen.getStatus()              , Specimen::ACTIVE);
    CHECK_EQUAL(specimen.getWeight()              , 1UL);
    CHECK_EQUAL(specimen.getPredictand().getRealValue(),31.4159);

    checkCellSequence(specimen);
}

TEST(usualConstructorForSpecimen)
{
    std::cout << "SpecimenTest usualConstructorForSpecimen" << '\n';

    std::list<Cell> cellList;
    makeList(cellList);

    Specimen specimen(
        123456789UL,
        Specimen::INACTIVE,
        101010,
        IntegerValue(314159),
        cellList.begin(), cellList.end());

    CHECK_EQUAL(specimen.getSpecimenKey()       , 123456789UL);
    CHECK_EQUAL(specimen.getStatus()            , Specimen::INACTIVE);
    CHECK_EQUAL(specimen.getWeight()            , 101010UL);
    CHECK_EQUAL(specimen.getPredictand().getIntegerValue(), 314159);

    checkCellSequence(specimen);
}

TEST(copyConstructorForSpecimen)
{
    std::cout << "SpecimenTest copyConstructorForSpecimen" << '\n';

    std::list<Cell> cellList;
    makeList(cellList);

    Specimen specimen(
        123456789UL,
        Specimen::INACTIVE,
        101010,
        IntegerValue(314159),
        cellList.begin(), cellList.end());

    Specimen specimen2(specimen);

    specimen.clearCells();

    CHECK_EQUAL(specimen2.getSpecimenKey()       , 123456789UL);
    CHECK_EQUAL(specimen2.getStatus()            , Specimen::INACTIVE);
    CHECK_EQUAL(specimen2.getWeight()            , 101010UL);
    CHECK_EQUAL(specimen2.getPredictand().getIntegerValue(), 314159);

    checkCellSequence(specimen2);
}

TEST(assignmentOperatorForSpecimen)
{
    std::cout << "SpecimenTest assignmentOperatorForSpecimen" << '\n';

    std::list<Cell> cellList;
    makeList(cellList);

    Specimen specimen(
        123456789UL,
        Specimen::INACTIVE,
        101010,
        IntegerValue(314159),
        cellList.begin(), cellList.end());

    Specimen specimen2(987654321, cellList.begin(), cellList.end());
    specimen2.clearCells();

    specimen2 = specimen;
    specimen.clearCells();

    CHECK_EQUAL(specimen2.getSpecimenKey()       , 123456789UL);
    CHECK_EQUAL(specimen2.getStatus()            , Specimen::INACTIVE);
    CHECK_EQUAL(specimen2.getWeight()            , 101010UL);
    CHECK_EQUAL(specimen2.getPredictand().getIntegerValue(), 314159);

    checkCellSequence(specimen2);
}


TEST(settersAndGettersForSpecimen)
{
    std::cout << "SpecimenTest settersAndGettersForSpecimen" << '\n';

    std::list<Cell> cellList;
    makeList(cellList);

    Specimen specimen(314159UL, cellList.begin(), cellList.end());

    specimen.setSpecimenKey(951413UL);
    specimen.setStatus(Specimen::INACTIVE);
    specimen.setWeight(1000000UL);
    specimen.setPredictand(NaturalValue(999999999UL));

    CHECK_EQUAL(specimen.getSpecimenKey() , 951413UL);
    CHECK_EQUAL(specimen.getStatus()      , Specimen::INACTIVE);
    CHECK_EQUAL(specimen.getWeight()      , 1000000UL);
    CHECK_EQUAL(specimen.getPredictand().getNaturalValue(), 999999999UL);
}

TEST(basicAccessToCellSequenceForSpecimen)
{
    std::cout << "SpecimenTest basicAccessToCellSequenceForSpecimen" << '\n';

    Cell cell1(111111UL, IntegerValue(99999));
    Cell cell2(222222UL, IntegerValue(88888));
    Cell cell3(333333UL, IntegerValue(77777));

    std::list<Cell> cellList;
    makeList(cellList);

    Specimen specimen(454567UL, cellList.begin(), cellList.end());
    specimen.clearCells();

    // test addCell, getCell, size, and isEmpty

    CHECK(specimen.isEmpty());

    specimen.addCell(cell1);
    CHECK_EQUAL(specimen.size(), 1UL);
    CHECK(!specimen.isEmpty());
    CHECK_EQUAL(specimen.getCell(0).getName(), 111111UL);
    CHECK_EQUAL(specimen.getCell(0).getValue().getIntegerValue(), 99999);

    specimen.addCell(cell2);
    CHECK_EQUAL(specimen.size(), 2UL);
    CHECK(!specimen.isEmpty());
    CHECK_EQUAL(specimen.getCell(1).getName(), 222222UL);
    CHECK_EQUAL(specimen.getCell(1).getValue().getIntegerValue(), 88888);

    specimen.addCell(cell3);
    CHECK_EQUAL(specimen.size(), 3UL);
    CHECK(!specimen.isEmpty());
    CHECK_EQUAL(specimen.getCell(2).getName(), 333333UL);
    CHECK_EQUAL(specimen.getCell(2).getValue().getIntegerValue(), 77777);

    specimen.addCell(cell3);
    CHECK_EQUAL(specimen.size(), 4UL);
    CHECK(!specimen.isEmpty());
    CHECK_EQUAL(specimen.getCell(3).getName(), 333333UL);
    CHECK_EQUAL(specimen.getCell(3).getValue().getIntegerValue(), 77777);

    // test removeCells

    bool b;

    b = specimen.removeCells(0);
    CHECK(!b);
    CHECK_EQUAL(specimen.size(), 4UL);

    b = specimen.removeCells(2);
    CHECK(b);
    CHECK_EQUAL(specimen.size(), 2UL);
    CHECK(!specimen.isEmpty());
    CHECK_EQUAL(specimen.getCell(0).getName(), 111111UL);
    CHECK_EQUAL(specimen.getCell(0).getValue().getIntegerValue(), 99999);
    CHECK_EQUAL(specimen.getCell(1).getName(), 222222UL);
    CHECK_EQUAL(specimen.getCell(1).getValue().getIntegerValue(), 88888);

    b = specimen.removeCells(5);
    CHECK(b);
    CHECK_EQUAL(specimen.size(), 0UL);
    CHECK(specimen.isEmpty());

    b = specimen.removeCells(5);
    CHECK(!b);
    CHECK_EQUAL(specimen.size(), 0UL);
    CHECK(specimen.isEmpty());

    // test clearCells

    specimen.addCell(cell1);
    specimen.addCell(cell2);
    specimen.addCell(cell3);
    CHECK_EQUAL(specimen.size(), 3UL);

    specimen.clearCells();
    CHECK_EQUAL(specimen.size(), 0UL);
    CHECK(specimen.isEmpty());

}   //  end basicAccessToCellSequence()


TEST(advancedAccessToCellSequenceForSpecimen)
{
    std::cout << "SpecimenTest advancedAccessToCellSequenceForSpecimen" << '\n';

    std::list<Cell> cellList;
    makeList(cellList);

    Specimen specimen(765454UL, cellList.begin(), cellList.end());
    checkCellSequence(specimen);
}

TEST(stressTestAccessToCellSequenceForSpecimen)
{
    std::cout << "SpecimenTest stressTestAccessToCellSequenceForSpecimen" << '\n';

    uint64_t numCells = 100000;

    std::list<Cell> cellList;
    makeList(cellList);

    Specimen specimen(1234567890UL, cellList.begin(), cellList.end());
    specimen.clearCells();

    // Create a bunch of cells and put them in a specimen

    for (uint64_t i = 1;  i <= numCells;  i++)
        specimen.addCell(Cell(i, NaturalValue(i)));

    CHECK_EQUAL(specimen.size(), numCells);

    // Remove each cell from the specimen

    for (uint64_t i = numCells;  i >= 1;  i--)
    {
        Cell c = specimen.getCell(i-1);
        CHECK_EQUAL(c.getKey(),  i);
        CHECK_EQUAL(c.getValue().getNaturalValue(), i);
        specimen.removeCells(1);
    }

    CHECK(specimen.isEmpty());

}   //  end stressTestAccessToCellSequence

//  end SpecimenTest.cpp
