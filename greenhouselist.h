#ifndef GREENHOUSELIST_H
#define GREENHOUSELIST_H

#include <vector>
#include "greenhouse.h"

class GreenHouseList
{
public:
    const std::vector<Greenhouse> &getGreenhouseList() const;
    void setGreenhouseList(const std::vector<Greenhouse> &newGreenhouseList);
private:
    std::vector<Greenhouse> greenhouseList;
};

#endif // GREENHOUSELIST_H
