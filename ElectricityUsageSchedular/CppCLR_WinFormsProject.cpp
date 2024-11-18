#include "pch.h"
#include "LoginForm.h"
#include"GlobalObjects.h"
using namespace System;
using namespace System::ComponentModel;
using namespace System::Windows::Forms;
using namespace System::Drawing;
#include <thread>
#include <chrono>
#include <ctime>

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

vector<schedule_appliance::Appliance> sortit(vector<schedule_appliance::Appliance> appliances, int priorityLevel) {
    vector<schedule_appliance::Appliance> sorted;
    
    int j = 0;
    for (int i = 0; i < appliances.size(); i++) {
        if (appliances[i].priority == 3) {
            sorted.push_back(appliances[i]);
        }
    }
    for (int i = 0; i < appliances.size(); i++) {
        if (appliances[i].priority == 2) {
            sorted.push_back(appliances[i]);
        }
    }
    for (int i = 0; i < appliances.size(); i++) {
        if (appliances[i].priority == 1) {
            sorted.push_back(appliances[i]);
        }
    }
    return sorted;
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

    GlobalObjects::Globals::Gtable->Rows->Add(15);


    for (int i = 0; i < GlobalObjects::Globals::Gtable->Rows->Count; i++) {
        GlobalObjects::Globals::Gtable->Rows[i]->Cells[0]->Value = gcnew System::String(arrr[i].name.c_str());
    }

     //Add the DataGridView to the form
    //this->Controls->Add(GlobalObjects::Globals::Gtable);
}


void traverseSlots(int& mover, int rowIndex) {
    // Ensure rowIndex and mover are within valid bounds before accessing table
    if (rowIndex - 1 < 0 || rowIndex - 1 >= GlobalObjects::Globals::Gtable->Rows->Count || mover >= 23 || mover < 0) {
        return;
    }

    // Check if the current cell is within bounds and is empty
    if (GlobalObjects::Globals::Gtable->Rows[rowIndex - 1]->Cells->Count > mover && GlobalObjects::Globals::Gtable->Rows[rowIndex - 1]->Cells[mover] &&
        GlobalObjects::Globals::Gtable->Rows[rowIndex - 1]->Cells[mover]->Value == nullptr) {
        // Stop here as we found an empty cell
        return;
    }

    // Move to the next cell and continue searching
    ++mover;
    traverseSlots(mover, rowIndex);
}


void makeTable(vector<schedule_appliance::Appliance> arr, int rowIndex, float& currentBill, float targetBill) {
    // Initial pass to assign slots to each appliance based on priority
    for (int i = 0; i < arr.size(); ++i) {
        if (currentBill >= targetBill) {
            return;
        }

        if (arr[i].priority == 3) {
            // Priority 3: Assign all available slots (1 per hour)
            for (int j = 1; j < 24; ++j) {
                if (i < GlobalObjects::Globals::Gtable->Rows->Count && j < GlobalObjects::Globals::Gtable->Rows[i]->Cells->Count) {
                    GlobalObjects::Globals::Gtable->Rows[i]->Cells[j]->Value = "+";
                    currentBill += arr[i].kwh * 41.6;
                    if (currentBill >= targetBill) {
                        return;
                    }
                }
            }
        }
        else if (arr[i].priority == 2) {
            // Priority 2: Assign 2 slots with a 1-cell gap between them
            int col = 1;
            traverseSlots(col, i);
            if (i < GlobalObjects::Globals::Gtable->Rows->Count && col < GlobalObjects::Globals::Gtable->Rows[i]->Cells->Count) {
                GlobalObjects::Globals::Gtable->Rows[i]->Cells[col]->Value = "+";
                if (col + 2 < GlobalObjects::Globals::Gtable->Rows[i]->Cells->Count) {
                    GlobalObjects::Globals::Gtable->Rows[i]->Cells[col + 2]->Value = "+";
                }
                currentBill += arr[i].kwh * 41.6;
            }
        }
        else if (arr[i].priority == 1) {
            // Priority 1: Assign only 1 slot
            int col = 1;
            traverseSlots(col, i);
            if (i < GlobalObjects::Globals::Gtable->Rows->Count && col < GlobalObjects::Globals::Gtable->Rows[i]->Cells->Count) {
                GlobalObjects::Globals::Gtable->Rows[i]->Cells[col]->Value = "+";
                currentBill += arr[i].kwh * 41.6;
            }
        }
    }

    // Secondary pass to revisit priority 2 and 1 appliances and assign additional slots
    bool slotsAssigned = false; // Track if any slots were assigned during this pass
    for (int i = 0; i < arr.size(); ++i) {
        if (currentBill >= targetBill) {
            return;
        }

        if (arr[i].priority == 2) {
            int col = 1;
            while (currentBill < targetBill) {
                traverseSlots(col, i);
                if (i < GlobalObjects::Globals::Gtable->Rows->Count && col < GlobalObjects::Globals::Gtable->Rows[i]->Cells->Count) {
                    GlobalObjects::Globals::Gtable->Rows[i]->Cells[col]->Value = "+";
                    if (col + 2 < GlobalObjects::Globals::Gtable->Rows[i]->Cells->Count) {
                        GlobalObjects::Globals::Gtable->Rows[i]->Cells[col + 2]->Value = "+";
                    }
                    currentBill += arr[i].kwh * 41.6;
                    slotsAssigned = true;
                }
                col += 4;
                if (col >= 24) break;
            }
        }
        else if (arr[i].priority == 1) {
            int col = 1;
            while (currentBill < targetBill) {
                traverseSlots(col, i);
                if (i < GlobalObjects::Globals::Gtable->Rows->Count && col < GlobalObjects::Globals::Gtable->Rows[i]->Cells->Count) {
                    GlobalObjects::Globals::Gtable->Rows[i]->Cells[col]->Value = "+";
                    currentBill += arr[i].kwh * 41.6;
                    slotsAssigned = true;
                }
                col += 2;
                if (col >= 24) break;
            }
        }
    }

    // If we assigned any slots during this pass and haven't reached the target bill, make another call
    if (slotsAssigned && currentBill < targetBill) {
        makeTable(arr, rowIndex, currentBill, targetBill);
    }
}

void actuallyMake(vector<schedule_appliance::Appliance> arr, int rowIndex, float& currentBill, float targetBill) {
    initializeTable();
    arr = sortit(arr, 0);

    float dailyBill = 0.0f;
    const float monthlyThreshold = 50000.0f;

    const float dailyThreshold = monthlyThreshold / 30.0f; // Calculate daily threshold

    makeTable(arr, 0, dailyBill, dailyThreshold);
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