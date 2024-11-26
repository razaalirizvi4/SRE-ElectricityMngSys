#include "pch.h"
#include "LoginForm.h"
#include"GlobalObjects.h"
#include "globals2.h"
using namespace System;
using namespace System::ComponentModel;
using namespace System::Windows::Forms;
using namespace System::Drawing;
#include <thread>
#include <chrono>
#include <ctime>
#include <sqlite3.h>

//---------------------------Functions Definition-------------------------------------
#include "GlobalFunctions.h"
#include <Shellapi.h>
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "Shell32.lib")



void ShowNotification(const wchar_t* title, const wchar_t* message)
{
    NOTIFYICONDATA nid = {};
    nid.cbSize = sizeof(NOTIFYICONDATA);
    nid.uFlags = NIF_INFO;
    wcsncpy_s(nid.szInfoTitle, title, _TRUNCATE);
    wcsncpy_s(nid.szInfo, message, _TRUNCATE);

    Shell_NotifyIcon(NIM_ADD, &nid);
    Shell_NotifyIcon(NIM_MODIFY, &nid); // Show the notification
    Shell_NotifyIcon(NIM_DELETE, &nid); // Remove it
}




vector<schedule_appliance::Appliance> sortit(vector<schedule_appliance::Appliance> app, int priorityLevel) {
    vector<schedule_appliance::Appliance> sorted;

    int j = 0;
    for (int i = 0; i < app.size(); i++) {
        if (app[i].priority == 3) {
            sorted.push_back(app[i]);
        }
    }
    for (int i = 0; i < app.size(); i++) {
        if (app[i].priority == 2) {
            sorted.push_back(app[i]);
        }
    }
    for (int i = 0; i < app.size(); i++) {
        if (app[i].priority == 1) {
            sorted.push_back(app[i]);
        }
    }
    return sorted;
}




int traverseCols(int row) {
    for (int i = 1; i < 24; i++) {
        if (GlobalObjects::Globals::Gtable->Rows[row]->Cells[i]->Value == nullptr) {
            return i;  // Found an empty column
        }
    }
    return -1;  // No empty column found
}

void makeTable(float& daily, float threshold, const vector<schedule_appliance::Appliance>& arr) {
    // If daily exceeds threshold, stop
    if (daily >= threshold) {
        return;
    }

    // Loop through appliances and fill table accordingly
    for (int i = 0; i < arr.size(); i++) {
        int empty;

        if (arr[i].priority == 3) {
            // Priority 3 appliances: fill up any column in that row
            for (int j = 1; j < 24; j++) {
                if (GlobalObjects::Globals::Gtable->Rows[i]->Cells[j]->Value == nullptr) {  // Find empty column
                    GlobalObjects::Globals::Gtable->Rows[i]->Cells[j]->Value = "+";  // Mark as used
                    daily += arr[i].kwh * 41.6;  // Add kWh to daily usage
                }
            }
        }
        if (arr[i].priority == 2) {
            // Priority 2 appliances: fill two columns if possible
            empty = traverseCols(i);
            if (empty != -1) {
                GlobalObjects::Globals::Gtable->Rows[i]->Cells[empty]->Value = "+";
                daily += arr[i].kwh * 41.6;
            }

            empty = traverseCols( i);  // Look for another empty spot
            if (empty != -1) {
                GlobalObjects::Globals::Gtable->Rows[i]->Cells[empty]->Value = "+";
                daily += arr[i].kwh * 41.6;
            }
        }
        if (arr[i].priority == 1) {
            // Priority 1 appliances: fill one column
            empty = traverseCols(i);
            if (empty != -1) {
                GlobalObjects::Globals::Gtable->Rows[i]->Cells[empty]->Value = "+";
                daily += arr[i].kwh * 41.6;
            }
        }
    }
    makeTable(daily, threshold, arr);

}

void initializeTable() {
    GlobalObjects::Globals::Gtable = gcnew DataGridView();


    GlobalObjects::Globals::Gtable->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
    GlobalObjects::Globals::Gtable->ColumnHeadersVisible = true;
    GlobalObjects::Globals::Gtable->RowHeadersVisible = false;
    GlobalObjects::Globals::Gtable->AllowUserToAddRows = false;

    std::string arr[24] = {
"0000-0100", "0100-0200", "0200-0300", "0300-0400", "0400-0500",
"0500-0600", "0600-0700", "0700-0800", "0800-0900", "0900-1000",
"1000-1100", "1100-1200", "1200-1300", "1300-1400", "1400-1500",
"1500-1600", "1600-1700", "1700-1800", "1800-1900", "1900-2000",
"2000-2100", "2100-2200", "2200-2300", "2300-2400"
    };

    vector<schedule_appliance::Appliance> arrr;
    for (int i = 0; i <= 15; ++i) {
        string name = "name" + to_string(i);
        float kwh = 0.8f;
        int priority = (i % 2) + 1;
        if (i == 15) priority = 3;

        // Create and push the appliance object into the vector
        arrr.push_back(schedule_appliance::Appliance(name, kwh, priority));
    }
    arrr = sortit(arrr, 0);


    GlobalObjects::Globals::Gtable->Columns->Add("Name", "Name");
    for (int i = 0; i < 23; i++) {
        GlobalObjects::Globals::Gtable->Columns->Add(gcnew System::String(arr[i].c_str()), gcnew System::String(arr[i].c_str()));
    }


    // Add rows(num of items = num of rows)
    

    GlobalObjects::Globals::Gtable->Rows->Add(GlobalObjectsRaza::Globals::unmanagedGlobals->apl.size());
    vector<schedule_appliance::Appliance> a;
    a = sortit(GlobalObjectsRaza::Globals::unmanagedGlobals->apl, 0);

    for (int i = 0; i < GlobalObjects::Globals::Gtable->Rows->Count; i++) {
        GlobalObjects::Globals::Gtable->Rows[i]->Cells[0]->Value = gcnew System::String(a[i].name.c_str());
    }

    //Add the DataGridView to the form
   //this->Controls->Add(GlobalObjects::Globals::Gtable);
}

void actuallyMake(vector<schedule_appliance::Appliance> arr, int rowIndex, float& currentBill, float targetBill) {
    initializeTable();
    arr = sortit(arr, 0);

    float dailyBill = 0.0f;
    const float monthlyThreshold = 50000.0f;

    const float dailyThreshold = monthlyThreshold / 30.0f; // Calculate daily threshold

    makeTable(dailyBill, dailyThreshold, arr);
}

int aplcallback(void* data, int argc, char** argv, char** colNames) {


    // Create a new Record struct
    schedule_appliance::Appliance record;

    // Populate the struct fields from the database columns
             // First column: id (integer)
    record.name = argv[2] ? argv[2] : "";   // Second column: name (string)
    record.kwh = (argv[4] ? std::stof(argv[4]) : 0.0f) / 1000; // Third column: value (float)

    // Add the record to the global vector apl
    GlobalObjectsRaza::Globals::unmanagedGlobals->apl.push_back(record);

    return 0; // Success
}

int callback(void* data, int argc, char** argv, char** azColName) {
    // Extract the value of the first column (assuming one column is selected)
    if (argv[0]) {
        GlobalObjectsRaza::Globals::unmanagedGlobals->appliances1.push_back(argv[0]); // Add the value to the global vector
    }
    else {
        GlobalObjectsRaza::Globals::unmanagedGlobals->appliances1.push_back("NULL"); // Handle NULL values
    }

    return 0; // Returning 0 tells SQLite to continue processing
}

void retrive_appliance_names()
{
    GlobalObjectsRaza::Globals::unmanagedGlobals->exiter = sqlite3_open("billmanagement.db", &GlobalObjectsRaza::Globals::unmanagedGlobals->dbr);

    string sqlquery = "SELECT productname FROM USERS_APPLIANCE ";
    const char* q = sqlquery.c_str();

    if (sqlite3_exec(GlobalObjectsRaza::Globals::unmanagedGlobals->dbr, q, callback, nullptr, &GlobalObjectsRaza::Globals::unmanagedGlobals->errmsgr) != SQLITE_OK) {
        String^ errorMsg = gcnew String(sqlite3_errmsg(GlobalObjectsRaza::Globals::unmanagedGlobals->dbr));
        String^ detailedMsg = gcnew String(GlobalObjectsRaza::Globals::unmanagedGlobals->errmsgr ? GlobalObjectsRaza::Globals::unmanagedGlobals->errmsgr : "No detailed error message");

        // Show error in a message box
        MessageBox::Show("Error executing query: " + errorMsg + "\nDetails: " + detailedMsg,
            "Query Execution Error", MessageBoxButtons::OK, MessageBoxIcon::Error);

        // Free error message if allocated
        if (GlobalObjectsRaza::Globals::unmanagedGlobals->errmsgr) {
            sqlite3_free(GlobalObjectsRaza::Globals::unmanagedGlobals->errmsgr);
        }
    }
    else
    {
        MessageBox::Show("Query Ran Successfully");
    }
}

void get_appliances()
{
    for (auto it = GlobalObjectsRaza::Globals::unmanagedGlobals->appliances1.begin(); it != GlobalObjectsRaza::Globals::unmanagedGlobals->appliances1.end(); ++it)
    {
        /*String^ t = gcnew String(it->c_str());
        MessageBox::Show(t);*/

        int rc;
        string sql = "SELECT * FROM Electrical_Appliances WHERE product_name = '" + *it + "';";
        const char* q = sql.c_str();
        // Execute the query with the renamed callback
        rc = sqlite3_exec(GlobalObjectsRaza::Globals::unmanagedGlobals->dbr, q, aplcallback, nullptr, &GlobalObjectsRaza::Globals::unmanagedGlobals->errmsgr);
        if (rc != SQLITE_OK) {
            std::cerr << "SQL error: " << GlobalObjectsRaza::Globals::unmanagedGlobals->errmsgr << std::endl;
            sqlite3_free(GlobalObjectsRaza::Globals::unmanagedGlobals->errmsgr);
        }
        else {
            std::cout << "Query executed successfully.\n";
        }
    }
}

void RandomizeTable(System::Windows::Forms::DataGridView^ tbl) {
    // Assign to global table
    GlobalObjects::Globals::Gtable = tbl;

    // Random number generator
    std::random_device rd;
    std::mt19937 gen(rd());

    // Iterate through each row in the DataGridView
    for (int i = 0; i < tbl->RowCount; ++i) {
        // Extract time slot values (ignore first column)
        std::vector<int> rowValues;

        for (int j = 1; j < tbl->ColumnCount; ++j) {
            System::Object^ cellValue = tbl->Rows[i]->Cells[j]->Value;

            // Handle '+' (which represents 1) and nullptr (which represents 0)
            if (cellValue == nullptr) {
                rowValues.push_back(0);  // nullptr represents 0
            }
            else if (cellValue->ToString() == "+") {
                rowValues.push_back(1);  // '+' represents 1
            }
            else {
                // Handle any unexpected format (in case of non-numeric values)
                rowValues.push_back(0);  // Default to 0 if the format is unexpected
            }
        }

        // Shuffle the time slot values
        std::shuffle(rowValues.begin(), rowValues.end(), gen);

        // Assign shuffled values back to the time slots
        for (int j = 0; j < rowValues.size(); ++j) {
            // Assign "+" if the value is 1, or nullptr if the value is 0
            tbl->Rows[i]->Cells[j + 1]->Value = (rowValues[j] == 1) ? gcnew System::String("+") : nullptr;
        }
    }
}





void CheckConditionInBackground()
{
    while (true)
    {
        // Get current time
        time_t now = time(nullptr);
        struct tm localTime;
        localtime_s(&localTime, &now);

        // Check if the time is 3:37 AM
        if (localTime.tm_hour == 6 && localTime.tm_min == 52)
        {
            ShowNotification(L"Alert !", L"Peak Hour Reached");
            // Wait a minute to avoid multiple notifications at the same time
            this_thread::sleep_for(chrono::minutes(1));
        }

        // Sleep for 30 seconds to check the condition periodically
        this_thread::sleep_for(chrono::seconds(30));
    }
}

//--------------------------------Main stuff--------------------------------------------
using namespace System;
using namespace System::Windows::Forms;

[STAThread]
int main()
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    thread backgroundThread(CheckConditionInBackground);
    backgroundThread.detach();

    EUS::LoginForm form;
    Application::Run(% form);
    Application::Exit();

    return 0;
}