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
        this->BackColor = Color::FromArgb(212, 237, 250);

        // Use similar color, font, and alignment for labels
        int labelWidth = 200;
        int inputOffsetX = 250;
        int initialY = 30;
        int spacingY = 50;
        System::Drawing::Font^ boldFont = gcnew System::Drawing::Font("Calibri", 16, FontStyle::Bold);
        System::Drawing::Font^ regularFont = gcnew System::Drawing::Font("Calibri", 12);

        // Title Label
        Label^ lblTitle = gcnew Label();
        lblTitle->Text = L"Settings";
        lblTitle->Font = boldFont;
        lblTitle->ForeColor = Color::FromArgb(69, 160, 227);
        lblTitle->Size = System::Drawing::Size(200, 40);
        lblTitle->Location = Point((this->Width - lblTitle->Width) / 2, initialY);
        lblTitle->TextAlign = ContentAlignment::MiddleCenter;
        this->Controls->Add(lblTitle);

        initialY += spacingY + 20;

        // Notification Preferences Section
        initialY += spacingY;
        Label^ lblNotifications = gcnew Label();
        lblNotifications->Text = L"Notifications:";
        lblNotifications->Font = regularFont;
        lblNotifications->ForeColor = Color::FromArgb(69, 160, 227);
        lblNotifications->Location = Point(30, initialY);
        lblNotifications->Size = System::Drawing::Size(labelWidth, 20);
        this->Controls->Add(lblNotifications);

        chkHighUsageNotif = gcnew CheckBox();
        chkHighUsageNotif->Text = L"High Usage Alerts";
        chkHighUsageNotif->Font = regularFont;
        chkHighUsageNotif->ForeColor = Color::FromArgb(69, 160, 227);
        chkHighUsageNotif->Location = Point(inputOffsetX, initialY);
        chkHighUsageNotif->Checked = true;
        this->Controls->Add(chkHighUsageNotif);

        chkDeviceActivationNotif = gcnew CheckBox();
        chkDeviceActivationNotif->Text = L"Device Activation Alerts";
        chkDeviceActivationNotif->Font = regularFont;
        chkDeviceActivationNotif->ForeColor = Color::FromArgb(69, 160, 227);
        chkDeviceActivationNotif->Location = Point(inputOffsetX, initialY + 30);
        chkDeviceActivationNotif->Checked = true;
        this->Controls->Add(chkDeviceActivationNotif);

        // Default Energy Rates
        initialY += spacingY + 30;
        Label^ lblEnergyRate = gcnew Label();
        lblEnergyRate->Text = L"Energy Rate (per kWh):";
        lblEnergyRate->Font = regularFont;
        lblEnergyRate->ForeColor = Color::FromArgb(69, 160, 227);
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
    }
};

