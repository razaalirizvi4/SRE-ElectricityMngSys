#include "pch.h"
#include "LoginForm.h"
#include"GlobalObjects.h"
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