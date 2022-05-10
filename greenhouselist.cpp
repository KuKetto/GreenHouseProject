#include "greenhouselist.h"

const std::vector<Greenhouse> &GreenHouseList::getGreenhouseList() const
{
    return greenhouseList;
}

void GreenHouseList::setGreenhouseList(const std::vector<Greenhouse> &newGreenhouseList)
{
    greenhouseList = newGreenhouseList;
}
