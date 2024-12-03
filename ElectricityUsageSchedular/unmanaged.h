#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sqlite3.h>
#include "helperStructs.h"
#include "week.h"

class UnmanagedGlobals
{
public:
    std::vector<std::string> appliances1;
    std::vector<schedule_appliance::Appliance> apl;
    std::vector<std :: string> t1;
    int exiter;
    sqlite3* dbr;
    char* errmsgr;
    float bill;
    float dailyunits;
    
    UnmanagedGlobals() {
        errmsgr = nullptr;
        dailyunits = 0;
        bill = 0;
    }
};
