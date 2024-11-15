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