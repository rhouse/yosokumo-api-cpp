// PredictorBlock.cpp

#include "PredictorBlock.h"

using namespace Yosokumo;

// Constructors and destructor

PredictorBlock::PredictorBlock() : Block()
{
    setType(PREDICTOR);
}

PredictorBlock::PredictorBlock(std::string id) : Block(id)
{
    setType(PREDICTOR);
}

PredictorBlock::PredictorBlock(
    std::vector<Predictor>::iterator begin, 
    std::vector<Predictor>::iterator end) : Block()
{
    setType(PREDICTOR);
    addPredictors(begin, end);
}

PredictorBlock::PredictorBlock(
    std::list<Predictor>::iterator begin, 
    std::list<Predictor>::iterator end) : Block()
{
    setType(PREDICTOR);
    addPredictors(begin, end);
}

PredictorBlock::PredictorBlock(
    std::string id, 
    std::vector<Predictor>::iterator begin, 
    std::vector<Predictor>::iterator end) : Block(id)
{
    setType(PREDICTOR);
    addPredictors(begin, end);
}

PredictorBlock::PredictorBlock(
    std::string id, 
    std::list<Predictor>::iterator begin, 
    std::list<Predictor>::iterator end) : Block(id)
{
    setType(PREDICTOR);
    addPredictors(begin, end);
}

PredictorBlock::~PredictorBlock()
{}

// Access to the predictor sequence

void PredictorBlock::addPredictor(const Predictor &predictor)
{
    predictorSequence.push_back(predictor);
}

bool PredictorBlock::addPredictors(
    std::vector<Predictor>::iterator begin, 
    std::vector<Predictor>::iterator end)
{
    unsigned old_size = predictorSequence.size();
    predictorSequence.insert(predictorSequence.end(), begin, end);
    return predictorSequence.size() != old_size;
}

bool PredictorBlock::addPredictors(
    std::list<Predictor>::iterator begin, 
    std::list<Predictor>::iterator end)
{
    unsigned old_size = predictorSequence.size();
    predictorSequence.insert(predictorSequence.end(), begin, end);
    return predictorSequence.size() != old_size;
}

bool PredictorBlock::removePredictors(uint64_t numPredictorsToRemove)
{
    if (numPredictorsToRemove == 0 || isEmpty())
        return false;

    if (numPredictorsToRemove >= size())
        clearPredictors();
    else
        predictorSequence.erase(
            predictorSequence.end()-numPredictorsToRemove, 
            predictorSequence.end());

    return true;
}


Predictor PredictorBlock::getPredictor(uint64_t index) const
{
    return predictorSequence.at(index);
}


void PredictorBlock::clearPredictors()
{
    predictorSequence.clear();
}

uint64_t PredictorBlock::size() const
{
    return predictorSequence.size();
}

bool PredictorBlock::isEmpty() const
{
    return predictorSequence.empty();
}


std::string PredictorBlock::toString()
{
    std::stringstream s;

    s <<
    "PredictorBlock:"                              << '\n' <<
    "  type            = " << getType()            << '\n' <<
    "  studyIdentifier = " << getStudyIdentifier() << '\n';

    for (uint64_t i = 0;  i < size();  ++i)
    {
        Predictor p = getPredictor(i);

        s << "\n" << "  " << p;
    }

    return s.str();
}

std::ostream &operator<<(std::ostream &os, PredictorBlock &p)
{
    os << p.toString();
    return os;
}

std::stringstream &operator<<(std::stringstream &s, PredictorBlock &p)
{
    s << p.toString();
    return s;
}

// end PredictorBlock.cpp
