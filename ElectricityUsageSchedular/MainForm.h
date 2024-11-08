#pragma once

#include "DashboardUserControl.h"
#include "SchedulerUserControl.h"
#include "DevicesUserControl.h"
#include "AnalyticsUserControl.h"
#include "SettingsUserControl.h"

namespace EUS {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class MainForm : public System::Windows::Forms::Form
    {
    public:
        MainForm(void);

    protected:
        ~MainForm();

    private:
        System::ComponentModel::Container^ components;
        Panel^ sidebarPanel;
        Panel^ contentPanel;
        Label^ labelEUS;

        Button^ btnDashboard;
        Button^ btnScheduler;
        Button^ btnDevices;
        Button^ btnAnalytics;
        Button^ btnSettings;
        Button^ activeButton;

        void InitializeComponent(void);
        Button^ CreateIconButton(System::String^ iconPath, int size);
        void MainForm::OnButtonMouseEnter(Object^ sender, EventArgs^ e);
        void MainForm::OnButtonMouseLeave(Object^ sender, EventArgs^ e);
        void OnSidebarButtonClick(Object^ sender, EventArgs^ e);
        void OnFormClosing(Object^ sender, FormClosingEventArgs^ e);
    };
}
