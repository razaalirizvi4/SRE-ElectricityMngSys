#pragma once
#include <iostream>
#include <string>

using namespace std;

struct Appliance {
    string name;
    float kwh;
    bool priority;

    static Appliance* appliances;
    static int applianceCount;
    static int maxAppliances;

    Appliance(const string& name = "", float kwh = 0.0f, bool priority = false)
        : name(name), kwh(kwh), priority(priority) {
    }

    static void initializeArray(int capacity) {
        maxAppliances = capacity;
        applianceCount = 0;
        appliances = new Appliance[capacity];
    }

    static void cleanupArray() {
        delete[] appliances;
    }

    static void addItem(const string& name, float kwh, bool priority) {
        if (applianceCount < maxAppliances) {
            appliances[applianceCount++] = Appliance(name, kwh, priority);
        }
    }

    static void deleteItem(const string& name) {
        int index = -1;
        for (int i = 0; i < applianceCount; ++i) {
            if (appliances[i].name == name) {
                index = i;
                break;
            }
        }

        if (index != -1) {
            for (int i = index; i < applianceCount - 1; ++i) {
                appliances[i] = appliances[i + 1];
            }
            --applianceCount;
        }
    }

    static void sortItemsByPriority() {
        Appliance* sortedArr = new Appliance[applianceCount];
        int sortedIndex = 0;

        for (int i = 0; i < applianceCount; ++i) {
            if (appliances[i].priority) {
                sortedArr[sortedIndex++] = appliances[i];
            }
        }

        for (int i = 0; i < applianceCount; ++i) {
            if (!appliances[i].priority) {
                sortedArr[sortedIndex++] = appliances[i];
            }
        }

        for (int i = 0; i < applianceCount; ++i) {
            appliances[i] = sortedArr[i];
        }

        delete[] sortedArr;
    }
};

Appliance* Appliance::appliances = nullptr;
int Appliance::applianceCount = 0;
int Appliance::maxAppliances = 0;
