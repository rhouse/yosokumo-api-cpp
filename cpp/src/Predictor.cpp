// Predictor.cpp

#include <cassert>
#include "Predictor.h"

using namespace Yosokumo;

Predictor::Predictor()
{
    initPredictor(1, ACTIVE, CONTINUOUS, RATIO);
}

Predictor::Predictor(int64_t name)
{
    initPredictor(name, ACTIVE, CONTINUOUS, RATIO);
}

Predictor::Predictor
(
    int64_t name,
    Status  status,
    Type    type, 
    Level   level
)
{
    initPredictor(name, status, type, level);
}

Predictor::Predictor(const Predictor &rhs)
{
    initPredictor(rhs.name, rhs.status, rhs.type, rhs.level);
}

Predictor::~Predictor()
{}

Predictor &Predictor::operator=(const Predictor& rhs)
{
    if (this != &rhs)
        initPredictor(rhs.name, rhs.status, rhs.type, rhs.level);

    return *this;
}

void Predictor::initPredictor
(
    int64_t name,
    Status  status,
    Type    type, 
    Level   level
)
{
    setPredictorName(name  );
    setStatus       (status);
    setType         (type  );
    setLevel        (level );
}

// Equality operators

bool Predictor::operator==(const Predictor &rhs) const 
{
    return
    (
        name   == rhs.name   &&
        status == rhs.status &&
        type   == rhs.type   &&
        level  == rhs.level  
    );
}

bool Predictor::operator!=(const Predictor &rhs) const
{
    return !(*this == rhs);
}


// Setters and getters

void Predictor::setPredictorName(int64_t name)
{
    assert(name > 0);
    this->name = name;
}

int64_t Predictor::getPredictorName() const
{
    return name;
}


void Predictor::setStatus(Status s)
{
    status = s;
}

Predictor::Status Predictor::getStatus() const
{
    return status;
}


void Predictor::setType(Type t)
{
    type = t;
}

Predictor::Type Predictor::getType() const
{
    return type;
}


void Predictor::setLevel(Level L)
{
    level = L;
}

Predictor::Level Predictor::getLevel() const
{
    return level;
}


// Utility

std::string Predictor::toString()
{
    std::stringstream s;

    s <<
    "Predictor:"                        << '\n' <<
    "  name   = " << getPredictorName() << '\n' <<
    "  status = " << getStatus()        << '\n' <<
    "  type   = " << getType()          << '\n' <<
    "  level  = " << getLevel()         << '\n'
    ;

    return s.str();
}

std::ostream &Yosokumo::operator<<(std::ostream &os, Predictor &p)
{
    os << p.toString();
    return os;
}

std::stringstream &Yosokumo::operator<<(std::stringstream &s, Predictor &p)
{
    s << p.toString();
    return s;
}

// end Predictor.cpp
