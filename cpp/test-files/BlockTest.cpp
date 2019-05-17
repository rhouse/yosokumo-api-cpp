// BlockTest.cpp  -  Test the Block class and its subclasses with UnitTest++

#include "UnitTest++.h"

#include "EmptyBlock.h"
#include "PredictorBlock.h"
#include "SpecimenBlock.h"
#include "CellBlock.h"

#include "EmptyValue.h"
#include "IntegerValue.h"
#include "NaturalValue.h"
#include "RealValue.h"

#include <list>
#include <vector>
#include <iostream>

using namespace Yosokumo;

//***** NOTE:  Some of the helper functions below (e.g., makePredictorList)
//*****        are called from other files (e.g., YosokumoProtobufTest.cpp)
//*****        which is why they are not static.

void makePredictorList(std::list<Predictor> &predictorList)
{
    predictorList.clear();

    Predictor p1(
        11111, 
        Predictor::ACTIVE, 
        Predictor::CATEGORICAL,
        Predictor::INTERVAL);
    predictorList.push_back(p1);

    Predictor p2(
        22222, 
        Predictor::INACTIVE, 
        Predictor::CONTINUOUS,
        Predictor::NOMINAL);
    predictorList.push_back(p2);

    Predictor p3(
        33333, 
        Predictor::ACTIVE, 
        Predictor::CATEGORICAL,
        Predictor::ORDINAL);
    predictorList.push_back(p3);

    Predictor p4(
        44444, 
        Predictor::INACTIVE, 
        Predictor::CONTINUOUS,
        Predictor::RATIO);
    predictorList.push_back(p4);

}   //  end makePredictorList

static void makePredictorVector(std::vector<Predictor> &predictorVector)
{
    predictorVector.clear();

    Predictor p1(
        11111, 
        Predictor::ACTIVE, 
        Predictor::CATEGORICAL,
        Predictor::INTERVAL);
    predictorVector.push_back(p1);

    Predictor p2(
        22222, 
        Predictor::INACTIVE, 
        Predictor::CONTINUOUS,
        Predictor::NOMINAL);
    predictorVector.push_back(p2);

    Predictor p3(
        33333, 
        Predictor::ACTIVE, 
        Predictor::CATEGORICAL,
        Predictor::ORDINAL);
    predictorVector.push_back(p3);

    Predictor p4(
        44444, 
        Predictor::INACTIVE, 
        Predictor::CONTINUOUS,
        Predictor::RATIO);
    predictorVector.push_back(p4);

}   //  end makePredictorVector


static void verifyPredictor(const Predictor &p, int i)
{
    switch (i)
    {
    case 1:  CHECK_EQUAL(p.getPredictorName(), 11111);
             CHECK_EQUAL(p.getStatus(), Predictor::ACTIVE);
             CHECK_EQUAL(p.getType()  , Predictor::CATEGORICAL);
             CHECK_EQUAL(p.getLevel() , Predictor::INTERVAL);
             break;

    case 2:  CHECK_EQUAL(p.getPredictorName(), 22222);
             CHECK_EQUAL(p.getStatus(), Predictor::INACTIVE);
             CHECK_EQUAL(p.getType()  , Predictor::CONTINUOUS);
             CHECK_EQUAL(p.getLevel() , Predictor::NOMINAL);
             break;

    case 3:  CHECK_EQUAL(p.getPredictorName(), 33333);
             CHECK_EQUAL(p.getStatus(), Predictor::ACTIVE);
             CHECK_EQUAL(p.getType()  , Predictor::CATEGORICAL);
             CHECK_EQUAL(p.getLevel() , Predictor::ORDINAL);
             break;

    case 4:  CHECK_EQUAL(p.getPredictorName(), 44444);
             CHECK_EQUAL(p.getStatus(), Predictor::INACTIVE);
             CHECK_EQUAL(p.getType()  , Predictor::CONTINUOUS);
             CHECK_EQUAL(p.getLevel() , Predictor::RATIO);
             break;

    default: CHECK(false);
    }
}

void checkPredictorSequence(const PredictorBlock &block)
{
    CHECK(block.size() == 4);
    CHECK(!block.isEmpty());

    // test getPredictorSequence -- use a for-loop with indices

    uint64_t i;

    for (i = 0;  i < block.size();  ++i)
    {
        Predictor p = block.getPredictor(i);
        verifyPredictor(p, i+1);
    }

    CHECK(i == 4);

}   //  end checkPredictorSequence


static void makeCellList(std::list<Cell> &cellList)
{
    cellList.push_back(Cell(11111, RealValue(99.999)));
    cellList.push_back(Cell(22222, IntegerValue(88888)));
    cellList.push_back(Cell(33333, EmptyValue()));
    cellList.push_back(Cell(44444, NaturalValue(7777777777)));
}

static void verifyCell(const Cell &c, int i)
{
    switch (i)
    {
    case 1:  CHECK_EQUAL(c.getKey(), 11111UL);
             CHECK_EQUAL(c.getValue().getType(), Value::REAL);
             CHECK_EQUAL(c.getValue().getRealValue(), 99.999);
             break;

    case 2:  CHECK_EQUAL(c.getKey(), 22222UL);
             CHECK_EQUAL(c.getValue().getType(), Value::INTEGER);
             CHECK_EQUAL(c.getValue().getIntegerValue(), 88888);
             break;

    case 3:  CHECK_EQUAL(c.getKey(), 33333UL);
             CHECK_EQUAL(c.getValue().getType(), Value::EMPTY);
             break;

    case 4:  CHECK_EQUAL(c.getKey(), 44444UL);
             CHECK_EQUAL(c.getValue().getType(), Value::NATURAL);
             CHECK_EQUAL(c.getValue().getNaturalValue(), 7777777777UL);
             break;

    default: CHECK(false);
    }
}

static void checkCellSequence(const CellBlock &cellBlock)
{
    CHECK_EQUAL(cellBlock.size(), 4UL);
    CHECK(!cellBlock.isEmpty());

    // test getCellSequence -- use a for-loop with indices

    uint64_t i;

    for (i = 0;  i < cellBlock.size();  ++i)
    {
        Cell c = cellBlock.getCell(i);
        verifyCell(c, i+1);
    }

    CHECK_EQUAL(i, 4UL);

}   //  end checkCellSequence


void makeSpecimenList(std::list<Specimen> &specimenList)
{
    std::list<Cell> cellList;
    makeCellList(cellList);

    specimenList.clear();

    Specimen p1(11111, NaturalValue(217), cellList.begin(), cellList.end());
    specimenList.push_back(p1);

    Specimen p2(22222, IntegerValue(-314), cellList.begin(), cellList.end());
    p2.setStatus(Specimen::INACTIVE);
    specimenList.push_back(p2);

    Specimen p3(33333, RealValue(9.87654321), cellList.begin(), cellList.end());
    specimenList.push_back(p3);

    Specimen p4(44444, RealValue(1.414), cellList.begin(), cellList.end());
    p4.setStatus(Specimen::INACTIVE);
    specimenList.push_back(p4);

}   //  end makeSpecimenList



static void checkSpecimenCells(const Specimen &specimen)
{
    CHECK_EQUAL(specimen.size(), 4UL);

    for (unsigned i = 0;  i < specimen.size();  ++i)
    {
        Cell c = specimen.getCell(i);
        verifyCell(c, i+1);
    }
}


static void verifySpecimen(const Specimen &p, int i)
{
    switch (i)
    {
    case 1:  CHECK_EQUAL(p.getSpecimenKey(), 11111UL);
             CHECK_EQUAL(p.getStatus(), Specimen::ACTIVE);
             CHECK(p.getPredictand() == NaturalValue(217));
             checkSpecimenCells(p);
             break;

    case 2:  CHECK_EQUAL(p.getSpecimenKey(), 22222UL);
             CHECK_EQUAL(p.getStatus(), Specimen::INACTIVE);
             CHECK(p.getPredictand() == IntegerValue(-314));
             checkSpecimenCells(p);
             break;

    case 3:  CHECK_EQUAL(p.getSpecimenKey(), 33333UL);
             CHECK_EQUAL(p.getStatus(), Specimen::ACTIVE);
             CHECK(p.getPredictand() == RealValue(9.87654321));
             checkSpecimenCells(p);
             break;

    case 4:  CHECK_EQUAL(p.getSpecimenKey(), 44444UL);
             CHECK_EQUAL(p.getStatus(), Specimen::INACTIVE);
             CHECK(p.getPredictand() == RealValue(1.414));
             checkSpecimenCells(p);
             break;

    default: CHECK(false);
    }
}

void checkSpecimenSequence(const SpecimenBlock &block)
{
    CHECK_EQUAL(block.size(), 4UL);
    CHECK(!block.isEmpty());

    // test getSpecimenSequence -- use a for-loop with indices

    uint64_t i;

    for (i = 0;  i < block.size();  ++i)
    {
        Specimen* s = block.getSpecimen(i);
        verifySpecimen(*s, i+1);
    }

    CHECK_EQUAL(i, 4UL);

}   //  end checkSpecimenSequence


TEST(minimalConstructorForBlock)
{
    std::cout << "BlockTest minimalConstructorForBlock" << '\n';

    EmptyBlock block;
    CHECK_EQUAL(block.getStudyIdentifier(), "");
    CHECK_EQUAL(block.getType(), Block::EMPTY);

    PredictorBlock pblock;
    CHECK_EQUAL(pblock.getStudyIdentifier(), "");
    CHECK_EQUAL(pblock.getType(), Block::PREDICTOR);
    CHECK_EQUAL(pblock.size(), 0UL);
    CHECK(pblock.isEmpty());

    SpecimenBlock sblock;
    CHECK_EQUAL(sblock.getStudyIdentifier(), "");
    CHECK_EQUAL(sblock.getType(), Block::SPECIMEN);
    CHECK_EQUAL(sblock.size(), 0UL);
    CHECK(sblock.isEmpty());

    CellBlock cblock;
    CHECK_EQUAL(cblock.getStudyIdentifier(), "");
    CHECK_EQUAL(cblock.getType(), Block::CELL);
    CHECK_EQUAL(cblock.size(), 0UL);
    CHECK(cblock.isEmpty());
}

TEST(usualConstructorForBlock)
{
    std::cout << "BlockTest usualConstructorForBlock" << '\n';

    std::string id = "predictor id 123";

    EmptyBlock block(id);
    CHECK_EQUAL(block.getStudyIdentifier(), id);

    PredictorBlock pblock(id);
    CHECK_EQUAL(pblock.getStudyIdentifier(), id);
    CHECK_EQUAL(pblock.getType(), Block::PREDICTOR);
    CHECK_EQUAL(pblock.size(), 0UL);
    CHECK(pblock.isEmpty());

    std::list<Predictor> predictorList;
    makePredictorList(predictorList);

    PredictorBlock pblock2(predictorList.begin(), predictorList.end());
    CHECK_EQUAL(pblock2.getStudyIdentifier(), "");
    CHECK_EQUAL(pblock2.getType(), Block::PREDICTOR);
    checkPredictorSequence(pblock2);

    PredictorBlock pblock3(id, predictorList.begin(), predictorList.end());
    CHECK_EQUAL(pblock3.getStudyIdentifier(), id);
    CHECK_EQUAL(pblock3.getType(), Block::PREDICTOR);
    checkPredictorSequence(pblock3);

    SpecimenBlock sblock(id);
    CHECK_EQUAL(sblock.getStudyIdentifier(), id);
    CHECK_EQUAL(sblock.getType(), Block::SPECIMEN);
    CHECK_EQUAL(sblock.size(), 0UL);
    CHECK(sblock.isEmpty());

    std::list<Specimen> specimenList;
    makeSpecimenList(specimenList);
    SpecimenBlock sblock2(specimenList.begin(), specimenList.end());
    CHECK_EQUAL(sblock2.getStudyIdentifier(), "");
    CHECK_EQUAL(sblock2.getType(), Block::SPECIMEN);
    checkSpecimenSequence(sblock2);

    SpecimenBlock sblock3(id, specimenList.begin(), specimenList.end());
    CHECK_EQUAL(sblock3.getStudyIdentifier(), id);
    CHECK_EQUAL(sblock3.getType(), Block::SPECIMEN);
    checkSpecimenSequence(sblock3);

    std::list<Cell> cellList;
    makeCellList(cellList);
    CellBlock cblock(cellList.begin(), cellList.end());
    CHECK_EQUAL(cblock.getStudyIdentifier(), "");
    CHECK_EQUAL(cblock.getType(), Block::CELL);
    checkCellSequence(cblock);

}


TEST(settersAndGettersForBlock)
{
    std::cout << "BlockTest settersAndGettersForBlock" << '\n';

    std::string id1 = "1234567890abcdef";
    std::string id2 = "fedcba0987654321";

    EmptyBlock block(id1);
    CHECK_EQUAL(block.getStudyIdentifier(), id1);
    block.setStudyIdentifier(id2);
    CHECK_EQUAL(block.getStudyIdentifier(), id2);

    PredictorBlock pblock(id1);
    CHECK_EQUAL(pblock.getStudyIdentifier(), id1);
    pblock.setStudyIdentifier(id2);
    CHECK_EQUAL(pblock.getStudyIdentifier(), id2);

    SpecimenBlock sblock(id1);
    CHECK_EQUAL(sblock.getStudyIdentifier(), id1);
    sblock.setStudyIdentifier(id2);
    CHECK_EQUAL(sblock.getStudyIdentifier(), id2);

    CellBlock cblock(id1);
    CHECK_EQUAL(cblock.getStudyIdentifier(), id1);
    cblock.setStudyIdentifier(id2);
    CHECK_EQUAL(cblock.getStudyIdentifier(), id2);
}

TEST(basicAccessToSequencesForBlock)
{
    std::cout << "BlockTest basicAccessToSequencesForBlock" << '\n';

    Predictor predictor1(
        11111, 
        Predictor::ACTIVE, 
        Predictor::CATEGORICAL,
        Predictor::INTERVAL);

    Predictor predictor2(
        22222, 
        Predictor::INACTIVE, 
        Predictor::CONTINUOUS,
        Predictor::NOMINAL);

    Predictor predictor3(
        33333, 
        Predictor::ACTIVE, 
        Predictor::CATEGORICAL,
        Predictor::ORDINAL);

// PredictorBlock tests

    PredictorBlock pblock("454567");

    // test addPredictor, getPredictor, size, and isEmpty

    CHECK(pblock.isEmpty());

    pblock.addPredictor(predictor1);
    CHECK_EQUAL(pblock.size(), 1UL);
    CHECK(!pblock.isEmpty());
    CHECK(pblock.getPredictor(0) == predictor1);

    pblock.addPredictor(predictor2);
    CHECK_EQUAL(pblock.size(), 2UL);
    CHECK(!pblock.isEmpty());
    CHECK(pblock.getPredictor(1) == predictor2);

    pblock.addPredictor(predictor3);
    CHECK_EQUAL(pblock.size(), 3UL);
    CHECK(!pblock.isEmpty());
    CHECK(pblock.getPredictor(2) == predictor3);

    pblock.addPredictor(predictor3);
    CHECK_EQUAL(pblock.size(), 4UL);
    CHECK(!pblock.isEmpty());
    CHECK(pblock.getPredictor(3) == predictor3);

    // test removePredictors

    bool b;

    b = pblock.removePredictors(0);
    CHECK(!b);
    CHECK_EQUAL(pblock.size(), 4UL);

    b = pblock.removePredictors(2);
    CHECK(b);
    CHECK_EQUAL(pblock.size(), 2UL);
    CHECK(!pblock.isEmpty());
    CHECK(pblock.getPredictor(0) == predictor1);
    CHECK(pblock.getPredictor(1) == predictor2);

    b = pblock.removePredictors(5);
    CHECK(b);
    CHECK_EQUAL(pblock.size(), 0UL);
    CHECK(pblock.isEmpty());

    b = pblock.removePredictors(5);
    CHECK(!b);
    CHECK_EQUAL(pblock.size(), 0UL);
    CHECK(pblock.isEmpty());

    // test clearPredictors

    pblock.addPredictor(predictor1);
    pblock.addPredictor(predictor2);
    pblock.addPredictor(predictor3);
    CHECK_EQUAL(pblock.size(), 3UL);

    pblock.clearPredictors();
    CHECK_EQUAL(pblock.size(), 0UL);
    CHECK(pblock.isEmpty());

// SpecimenBlock tests

    std::list<Cell> list1;

    Specimen specimen1(11111, list1.begin(), list1.end());
    Specimen specimen2(22222, list1.begin(), list1.end());
    specimen2.setStatus(Specimen::INACTIVE);
    Specimen specimen3(33333, list1.begin(), list1.end());

    SpecimenBlock sblock("765454");

    // test addSpecimen, getSpecimen, size, and isEmpty

    CHECK(sblock.isEmpty());

    sblock.addSpecimen(&specimen1);
    CHECK_EQUAL(sblock.size(), 1UL);
    CHECK(!sblock.isEmpty());
    CHECK_EQUAL(sblock.getSpecimen(0), &specimen1);

    sblock.addSpecimen(&specimen2);
    CHECK_EQUAL(sblock.size(), 2UL);
    CHECK(!sblock.isEmpty());
    CHECK_EQUAL(sblock.getSpecimen(1), &specimen2);

    sblock.addSpecimen(&specimen3);
    CHECK_EQUAL(sblock.size(), 3UL);
    CHECK(!sblock.isEmpty());
    CHECK_EQUAL(sblock.getSpecimen(2), &specimen3);

    sblock.addSpecimen(&specimen3);
    CHECK_EQUAL(sblock.size(), 4UL);
    CHECK(!sblock.isEmpty());
    CHECK_EQUAL(sblock.getSpecimen(3), &specimen3);

    // test removeSpecimens

    b = sblock.removeSpecimens(0);
    CHECK(!b);
    CHECK_EQUAL(sblock.size(), 4UL);

    b = sblock.removeSpecimens(2);
    CHECK(b);
    CHECK_EQUAL(sblock.size(), 2UL);
    CHECK(!sblock.isEmpty());
    CHECK_EQUAL(sblock.getSpecimen(0), &specimen1);
    CHECK_EQUAL(sblock.getSpecimen(1), &specimen2);

    b = sblock.removeSpecimens(5);
    CHECK(b);
    CHECK_EQUAL(sblock.size(), 0UL);
    CHECK(sblock.isEmpty());

    b = sblock.removeSpecimens(5);
    CHECK(!b);
    CHECK_EQUAL(sblock.size(), 0UL);
    CHECK(sblock.isEmpty());

    // test clearSpecimens

    sblock.addSpecimen(&specimen1);
    sblock.addSpecimen(&specimen2);
    sblock.addSpecimen(&specimen3);
    CHECK_EQUAL(sblock.size(), 3UL);

    sblock.clearSpecimens();
    CHECK_EQUAL(sblock.size(), 0UL);
    CHECK(sblock.isEmpty());

// CellBlock tests

    Cell cell1(11111, RealValue(99.999));
    Cell cell2(22222, RealValue(88.888));
    Cell cell3(33333, RealValue(77.777));

    CellBlock cblock("765454");

    // test addCell, getCell, size, and isEmpty

    CHECK(cblock.isEmpty());

    cblock.addCell(cell1);
    CHECK_EQUAL(cblock.size(), 1UL);
    CHECK(!cblock.isEmpty());
    CHECK(cblock.getCell(0) == cell1);

    cblock.addCell(cell2);
    CHECK_EQUAL(cblock.size(), 2UL);
    CHECK(!cblock.isEmpty());
    CHECK(cblock.getCell(1) == cell2);

    cblock.addCell(cell3);
    CHECK_EQUAL(cblock.size(), 3UL);
    CHECK(!cblock.isEmpty());
    CHECK(cblock.getCell(2) == cell3);

    cblock.addCell(cell3);
    CHECK_EQUAL(cblock.size(), 4UL);
    CHECK(!cblock.isEmpty());
    CHECK(cblock.getCell(3) == cell3);

    // test removeCells

    b = cblock.removeCells(0);
    CHECK(!b);
    CHECK_EQUAL(cblock.size(), 4UL);

    b = cblock.removeCells(2);
    CHECK(b);
    CHECK_EQUAL(cblock.size(), 2UL);
    CHECK(!cblock.isEmpty());
    CHECK(cblock.getCell(0) == cell1);
    CHECK(cblock.getCell(1) == cell2);

    b = cblock.removeCells(5);
    CHECK(b);
    CHECK_EQUAL(cblock.size(), 0UL);
    CHECK(cblock.isEmpty());

    b = cblock.removeCells(5);
    CHECK(!b);
    CHECK_EQUAL(cblock.size(), 0UL);
    CHECK(cblock.isEmpty());

    // test clearCells

    cblock.addCell(cell1);
    cblock.addCell(cell2);
    cblock.addCell(cell3);
    CHECK_EQUAL(cblock.size(), 3UL);

    cblock.clearCells();
    CHECK_EQUAL(cblock.size(), 0UL);
    CHECK(cblock.isEmpty());

}   //  end basicAccessToSequences()


TEST(addPredictorsForPredictorBlock)
{
    std::cout << "BlockTest addPredictorsForPredictorBlock" << '\n';

    PredictorBlock pblock;

    std::list<Predictor> predictorList;
    makePredictorList(predictorList);
    pblock.addPredictors(predictorList.begin(), predictorList.end());
    checkPredictorSequence(pblock);
    pblock.clearPredictors();

    std::vector<Predictor> predictorVector;
    makePredictorVector(predictorVector);
    pblock.addPredictors(predictorVector.begin(), predictorVector.end());
    checkPredictorSequence(pblock);
    pblock.clearPredictors();

}   //  end addPredictorsForPredictorBlock

TEST(stringStreamInsertionOperatorForPredictorBlock)
{
    std::cout << "BlockTest stringStreamInsertionOperatorForPredictorBlock" << '\n';

    std::stringstream s;

    PredictorBlock pblock("First block");

    std::string expect = 
        "PredictorBlock:\n"
        "  type            = 1\n"
        "  studyIdentifier = First block\n";
    s << pblock;
    CHECK_EQUAL(expect, s.str());
    s.str("");

    std::list<Predictor> predictorList;
    makePredictorList(predictorList);
    pblock.addPredictors(predictorList.begin(), predictorList.end());
    pblock.setStudyIdentifier("Second block");
    checkPredictorSequence(pblock);

    expect = 
        "PredictorBlock:\n"
        "  type            = 1\n"
        "  studyIdentifier = Second block\n"
        "\n"
        "  Predictor:\n"
        "  name   = 11111\n"
        "  status = 0\n"
        "  type   = 0\n"
        "  level  = 2\n"
        "\n"
        "  Predictor:\n"
        "  name   = 22222\n"
        "  status = 1\n"
        "  type   = 1\n"
        "  level  = 0\n"
        "\n"
        "  Predictor:\n"
        "  name   = 33333\n"
        "  status = 0\n"
        "  type   = 0\n"
        "  level  = 1\n"
        "\n"
        "  Predictor:\n"
        "  name   = 44444\n"
        "  status = 1\n"
        "  type   = 1\n"
        "  level  = 3\n";
    s << pblock;
    CHECK_EQUAL(expect, s.str());
    s.str("");

}   //  end stringStreamInsertionOperatorForPredictorBlock


// end BlockTest.cpp
