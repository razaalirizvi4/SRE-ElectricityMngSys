#include "helperStructs.h"
void ShowNotification(const wchar_t* title, const wchar_t* message);
vector<schedule_appliance::Appliance> sortit(vector<schedule_appliance::Appliance> arr, int priority);
void initializeTable();
void makeTable(vector<schedule_appliance::Appliance> arr, int rowIndex, float& currentBill, float targetBill);
void traverseSlots(int& mover, int rowIndex);
void actuallyMake(vector<schedule_appliance::Appliance> arr, int rowIndex, float& currentBill, float targetBill);
