#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sqlite3.h>
#include "helperStructs.h"

class UnmanagedGlobals
{
public:
    std::vector<std::string> appliances1;
    std::vector<schedule_appliance::Appliance> apl;
    int exiter;
    sqlite3* dbr;
    char* errmsgr;
    float bill;
    UnmanagedGlobals() {
        errmsgr = nullptr;
    }
};
