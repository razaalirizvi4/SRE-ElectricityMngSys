#include "pch.h"
#include "SettingsUserControl.h"

namespace EUS {

    SettingsUserControl::SettingsUserControl(void)
    {
        InitializeComponent();
    }

    SettingsUserControl::~SettingsUserControl()
    {
        if (components)
        {
            delete components;
        }
    }

    void SettingsUserControl::InitializeComponent(void)
    {
        this->components = gcnew System::ComponentModel::Container();
        this->Size = System::Drawing::Size(1200, 720);
        this->BackColor = Color::FromArgb(235, 245, 235);

        // Label width and alignment settings
        int labelWidth = 150;
        int inputOffsetX = 200;
        int initialY = 30;
        int spacingY = 50;

        // Title Label for Settings Page
        Label^ lblTitle = gcnew Label();
        lblTitle->Text = L"Settings";
        lblTitle->Font = gcnew System::Drawing::Font("Arial", 18, FontStyle::Bold);
        lblTitle->ForeColor = Color::FromArgb(85, 107, 47);
        lblTitle->Size = System::Drawing::Size(200, 40);
        lblTitle->Location = Point((this->Width - lblTitle->Width) / 2, initialY);
        this->Controls->Add(lblTitle);

        initialY += spacingY + 20;

        // Notification Preferences
        initialY += spacingY;
        Label^ lblNotifications = gcnew Label();
        lblNotifications->Text = L"Notifications:";
        lblNotifications->Location = Point(30, initialY);
        lblNotifications->Size = System::Drawing::Size(labelWidth, 20);
        this->Controls->Add(lblNotifications);

        chkHighUsageNotif = gcnew CheckBox();
        chkHighUsageNotif->Text = L"High Usage Alerts";
        chkHighUsageNotif->Location = Point(inputOffsetX, initialY);
        chkHighUsageNotif->Checked = true;
        this->Controls->Add(chkHighUsageNotif);

        chkDeviceActivationNotif = gcnew CheckBox();
        chkDeviceActivationNotif->Text = L"Device Activation Alerts";
        chkDeviceActivationNotif->Location = Point(inputOffsetX, initialY + 30);
        chkDeviceActivationNotif->Checked = true;
        this->Controls->Add(chkDeviceActivationNotif);

        // Default Energy Rates
        initialY += spacingY + 30;
        Label^ lblEnergyRate = gcnew Label();
        lblEnergyRate->Text = L"Energy Rate (per kWh):";
        lblEnergyRate->Location = Point(30, initialY);
        lblEnergyRate->Size = System::Drawing::Size(labelWidth, 20);
        this->Controls->Add(lblEnergyRate);

        numEnergyRate = gcnew NumericUpDown();
        numEnergyRate->Location = Point(inputOffsetX, initialY);
        numEnergyRate->Width = 100;
        numEnergyRate->DecimalPlaces = 2;
        numEnergyRate->Minimum = Decimal(0.01);
        numEnergyRate->Maximum = Decimal(10.00);
        numEnergyRate->Value = Decimal(0.12);
        this->Controls->Add(numEnergyRate);

        // Theme Selector
        initialY += spacingY;
        Label^ lblTheme = gcnew Label();
        lblTheme->Text = L"App Theme:";
        lblTheme->Location = Point(30, initialY);
        lblTheme->Size = System::Drawing::Size(labelWidth, 20);
        this->Controls->Add(lblTheme);

        rbLightTheme = gcnew RadioButton();
        rbLightTheme->Text = L"Light";
        rbLightTheme->Location = Point(inputOffsetX, initialY);
        rbLightTheme->Checked = true;
        this->Controls->Add(rbLightTheme);

        rbDarkTheme = gcnew RadioButton();
        rbDarkTheme->Text = L"Dark";
        rbDarkTheme->Location = Point(inputOffsetX + 80, initialY);
        this->Controls->Add(rbDarkTheme);
    }
};

