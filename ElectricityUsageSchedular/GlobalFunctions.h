#include "helperStructs.h"

void ShowNotification(const wchar_t* title, const wchar_t* message);
vector<schedule_appliance::Appliance> sortit(vector<schedule_appliance::Appliance> arr, int priority);
void makeTable(float& daily, float threshold, const vector<schedule_appliance::Appliance>& arr);
int traverseCols(int row);
//void actuallyMake(vector<schedule_appliance::Appliance> arr, int rowIndex, float& currentBill, float targetBill);
void initializeTable();
void actuallyMake(vector<schedule_appliance::Appliance> arr, int rowIndex, float& currentBill, float targetBill);
int aplcallback(void* data, int argc, char** argv, char** colNames);
int callback(void* data, int argc, char** argv, char** azColName);
void retrive_appliance_names();
void get_appliances();
void RandomizeTable(System::Windows::Forms::DataGridView^ tbl);
void CheckConditionInBackground();
