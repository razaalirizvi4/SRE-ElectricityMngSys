#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

namespace schedule_appliance {
    struct Appliance {
        string name;
        float kwh;
        int priority; // 1: Low, 2: High, 3: Very High

        Appliance(const string& name = "", float kwh = 0.0f, int priority = 1)
            : name(name), kwh(kwh), priority(priority) {
        }

    
    };
};
