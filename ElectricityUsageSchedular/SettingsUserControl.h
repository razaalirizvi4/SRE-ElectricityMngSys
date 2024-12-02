#pragma once
#include "Userclass.h"
#include <string>
#include <sqlite3.h>
#include <msclr/marshal_cppstd.h>

namespace EUS {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class SettingsUserControl : public System::Windows::Forms::UserControl
    {
    public:
        SettingsUserControl(void);

    protected:
        ~SettingsUserControl();

    private:
        System::ComponentModel::Container^ components;

        System::Windows::Forms::CheckBox^ chkHighUsageNotif;
        System::Windows::Forms::CheckBox^ chkDeviceActivationNotif;
        System::Windows::Forms::NumericUpDown^ numEnergyRate;
        System::Windows::Forms::TextBox^ txtStartTime;
        System::Windows::Forms::TextBox^ txtEndTime;
        System::Windows::Forms::TextBox^ txtEmail;
        System::Windows::Forms::NumericUpDown^ numBudget;

        void InitializeComponent(void);
        void SaveSettings(Object^ sender, EventArgs^ e);
        void UpdateUserBudget(int User_Budget, int User_ID);
        void UpdatePeakHours(const std::string& Peak_Start, const std::string& Peak_End, const std::string& City, const std::string& Area);
    };
}
