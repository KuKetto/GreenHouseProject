#ifndef ILOADER_H
#define ILOADER_H

#include "greenhouselist.h"

class ILoader {
public:
    virtual GreenHouseList loadGreenHouses() = 0;
};

#endif // ILOADER_H
