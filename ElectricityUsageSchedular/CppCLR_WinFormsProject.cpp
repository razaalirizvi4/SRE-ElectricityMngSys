#include "pch.h"
#include "LoginForm.h"


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

void sortit(vector<schedule_appliance::Appliance> appliances, int priorityLevel) {
    // Priority is handled where higher priority levels come first.
    // Sort primarily by priority, then by kwh in ascending order.
    std::sort(appliances.begin(), appliances.end(), [=](const schedule_appliance::Appliance& a, const schedule_appliance::Appliance& b) {
        if (a.priority != b.priority) {
            return a.priority > b.priority;
        }
        return a.kwh < b.kwh;
        });

    // Optional: Filter appliances to only show the specified priority level
    appliances.erase(std::remove_if(appliances.begin(), appliances.end(),
        [priorityLevel](const schedule_appliance::Appliance& appliance) {
            return appliance.priority != priorityLevel;
        }),
        appliances.end());
}

//--------------------------------Main stuff--------------------------------------------
using namespace System;
using namespace System::Windows::Forms;

[STAThread]
int main()
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    EUS::LoginForm form;
    ShowNotification(L"I am Hatsune Miku", L"I'm thinking miku miku moo ee oo");
    Application::Run(% form);
    Application::Exit();

    return 0;
}