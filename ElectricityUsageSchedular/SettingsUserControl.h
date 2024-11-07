#pragma once

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

        CheckBox^ chkHighUsageNotif;
        CheckBox^ chkDeviceActivationNotif;
        NumericUpDown^ numEnergyRate;
        RadioButton^ rbLightTheme;
        RadioButton^ rbDarkTheme;

        void InitializeComponent(void);
    };
}
