// Panel.cpp

#include "Panel.h"

using namespace Yosokumo;


// Panel setters and getters

void Panel::setNameControlLocation(const std::string &nameControlLocation)
{
    this->nameControlLocation = nameControlLocation;
}

std::string Panel::getNameControlLocation() const
{
    return nameControlLocation;
}

void Panel::setStatusControlLocation(const std::string &statusControlLocation)
{
    this->statusControlLocation = statusControlLocation;
}

std::string Panel::getStatusControlLocation() const
{
    return statusControlLocation;
}


void Panel::setVisibilityControlLocation(
    const std::string &visibilityControlLocation)
{
    this->visibilityControlLocation = visibilityControlLocation;
}

std::string Panel::getVisibilityControlLocation() const
{
    return visibilityControlLocation;
}


void Panel::setBlockCount(uint64_t blockCount)
{
    this->blockCount = blockCount;
}

uint64_t Panel::getBlockCount() const
{
    return blockCount;
}

void Panel::setCellCount(uint64_t cellCount)
{
    this->cellCount = cellCount;
}

uint64_t Panel::getCellCount() const
{
    return cellCount;
}

void Panel::setProspectCount(uint64_t prospectCount)
{
    this->prospectCount = prospectCount;
}

uint64_t Panel::getProspectCount() const
{
    return prospectCount;
}

void Panel::setCreationTime(const std::string &creationTime)
{
    this->creationTime = creationTime;
}

std::string Panel::getCreationTime() const 
{
    return creationTime;
}

void Panel::setLatestBlockTime(const std::string &latestBlockTime)
{
    this->latestBlockTime = latestBlockTime;
}

std::string Panel::getLatestBlockTime() const
{
    return latestBlockTime;
}

void Panel::setLatestProspectTime(const std::string &latestProspectTime)
{
    this->latestProspectTime = latestProspectTime;
}

std::string Panel::getLatestProspectTime() const
{
    return latestProspectTime;
}

// end Panel.cpp
