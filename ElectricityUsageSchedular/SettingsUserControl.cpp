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
        this->BackColor = Color::FromArgb(234, 237, 244);

        int labelWidth = 200;
        int inputOffsetX = 250;
        int initialY = 70;
        int spacingY = 50;
        int aestheticOffset = 50;
        System::Drawing::Font^ boldFont = gcnew System::Drawing::Font("Calibri", 16, FontStyle::Bold);
        System::Drawing::Font^ regularFont = gcnew System::Drawing::Font("Calibri", 12);

        // Email Section
        Label^ lblEmail = gcnew Label();
        lblEmail->Text = L"Email:";
        lblEmail->Font = regularFont;
        lblEmail->ForeColor = Color::FromArgb(67, 24, 255);
        lblEmail->Location = Point(30, initialY);
        lblEmail->Size = System::Drawing::Size(labelWidth, 20);
        this->Controls->Add(lblEmail);

        txtEmail = gcnew TextBox();
        txtEmail->Location = Point(inputOffsetX, initialY);
        txtEmail->Width = 250;
        this->Controls->Add(txtEmail);

        initialY += spacingY;

        // Peak Hours Section
        Label^ lblPeakHours = gcnew Label();
        lblPeakHours->Text = L"Peak Hours:";
        lblPeakHours->Font = regularFont;
        lblPeakHours->ForeColor = Color::FromArgb(67, 24, 255);
        lblPeakHours->Location = Point(30, initialY);
        lblPeakHours->Size = System::Drawing::Size(labelWidth, 20);
        this->Controls->Add(lblPeakHours);

        Label^ lblStart = gcnew Label();
        lblStart->Text = L"Start Time (HH:MM):";
        lblStart->Font = regularFont;
        lblStart->ForeColor = Color::FromArgb(67, 24, 255);
        lblStart->Location = Point(30 + aestheticOffset, initialY + spacingY);
        this->Controls->Add(lblStart);

        txtStartTime = gcnew TextBox();
        txtStartTime->Location = Point(inputOffsetX + aestheticOffset, initialY + spacingY);
        txtStartTime->Width = 100;
        txtStartTime->Text = gcnew String(UserData::userpeakstart.c_str());  // Populate with current peak hours
        this->Controls->Add(txtStartTime);

        Label^ lblEnd = gcnew Label();
        lblEnd->Text = L"End Time (HH:MM):";
        lblEnd->Font = regularFont;
        lblEnd->ForeColor = Color::FromArgb(67, 24, 255);
        lblEnd->Location = Point(30 + aestheticOffset, initialY + 2 * spacingY);
        this->Controls->Add(lblEnd);

        txtEndTime = gcnew TextBox();
        txtEndTime->Location = Point(inputOffsetX + aestheticOffset, initialY + 2 * spacingY);
        txtEndTime->Width = 100;
        txtEndTime->Text = gcnew String(UserData::userpeakend.c_str());  // Populate with current peak hours
        this->Controls->Add(txtEndTime);

        initialY += 3 * spacingY;

        // Budget Section
        Label^ lblBudget = gcnew Label();
        lblBudget->Text = L"Budget (per month):";
        lblBudget->Font = regularFont;
        lblBudget->ForeColor = Color::FromArgb(67, 24, 255);
        lblBudget->Location = Point(30, initialY);
        lblBudget->Size = System::Drawing::Size(labelWidth, 20);
        this->Controls->Add(lblBudget);

        numBudget = gcnew NumericUpDown();
        numBudget->Location = Point(inputOffsetX, initialY);
        numBudget->Width = 100;
        numBudget->Minimum = Decimal(5000);
        numBudget->Maximum = Decimal(999999999);
        numBudget->Value = Decimal(UserData::userbudget);
        this->Controls->Add(numBudget);

        // Save Button
        Button^ btnSave = gcnew Button();
        btnSave->Text = L"Save";
        btnSave->Font = boldFont;
        btnSave->Size = System::Drawing::Size(100, 40);
        btnSave->Location = Point((this->Width - btnSave->Width) / 2, initialY + spacingY + 20);
        btnSave->BackColor = Color::FromArgb(234, 237, 244);
        btnSave->ForeColor = Color::FromArgb(255, 255, 255);
        btnSave->FlatStyle = FlatStyle::Flat;
        btnSave->FlatAppearance->BorderSize = 0;
        btnSave->TextAlign = ContentAlignment::MiddleCenter;
        btnSave->Click += gcnew EventHandler(this, &SettingsUserControl::SaveSettings);
        this->Controls->Add(btnSave);
    }

    void SettingsUserControl::SaveSettings(System::Object^ sender, System::EventArgs^ e)
    {
        // Validate Email
        if (txtEmail->Text->Trim()->Length == 0)
        {
            MessageBox::Show("Email is mandatory.", "Validation Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return;
        }

        bool isBudgetChanged = Decimal::ToInt32(numBudget->Value) != UserData::userbudget;
        bool isHoursChanged = txtStartTime->Text != gcnew String(UserData::userpeakstart.c_str()) || txtEndTime->Text != gcnew String(UserData::userpeakend.c_str());

        if (!isBudgetChanged && !isHoursChanged)
        {
            MessageBox::Show("No changes detected. Please modify the budget or peak hours.", "No Change", MessageBoxButtons::OK, MessageBoxIcon::Information);
            return;
        }

        // Update Budget if changed
        if (isBudgetChanged)
        {
            int User_Budget = Decimal::ToInt32(numBudget->Value);
            UpdateUserBudget(User_Budget, UserData::userid);
        }

        // Update Peak Hours if changed
        if (isHoursChanged)
        {
            std::string Peak_Start = msclr::interop::marshal_as<std::string>(txtStartTime->Text);
            std::string Peak_End = msclr::interop::marshal_as<std::string>(txtEndTime->Text);

            // Avoid updating with empty values
            if (Peak_Start.empty()) Peak_Start = UserData::userpeakstart;
            if (Peak_End.empty()) Peak_End = UserData::userpeakend;

            UpdatePeakHours(Peak_Start, Peak_End, UserData::usercity, UserData::userarea);
        }

        MessageBox::Show("Settings updated successfully!", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);

        // Force close the app after saving
        Application::Exit();
    }

    void SettingsUserControl::UpdateUserBudget(int User_Budget, int User_ID)
    {
        sqlite3* db;
        if (sqlite3_open("user_management.db", &db) != SQLITE_OK)
        {
            MessageBox::Show("Error opening database", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        std::string query = "UPDATE Users SET User_Budget = ? WHERE User_ID = ?";

        sqlite3_stmt* stmt;
        if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
        {
            MessageBox::Show("Error preparing statement", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            sqlite3_close(db);
            return;
        }

        sqlite3_bind_int(stmt, 1, User_Budget);
        sqlite3_bind_int(stmt, 2, User_ID);

        if (sqlite3_step(stmt) != SQLITE_DONE)
        {
            MessageBox::Show("Error executing query", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }

        sqlite3_finalize(stmt);
        sqlite3_close(db);
    }

    void SettingsUserControl::UpdatePeakHours(const std::string& Peak_Start, const std::string& Peak_End, const std::string& City, const std::string& Area)
    {
        sqlite3* db;
        if (sqlite3_open("user_management.db", &db) != SQLITE_OK)
        {
            MessageBox::Show("Error opening database", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        std::string query = "UPDATE User_Settings SET Peak_Hours_Start = ?, Peak_Hours_End = ? WHERE City = ? AND Area = ?";

        sqlite3_stmt* stmt;
        if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
        {
            MessageBox::Show("Error preparing statement", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            sqlite3_close(db);
            return;
        }

        sqlite3_bind_text(stmt, 1, Peak_Start.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, Peak_End.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, City.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 4, Area.c_str(), -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) != SQLITE_DONE)
        {
            MessageBox::Show("Error executing query", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }

        sqlite3_finalize(stmt);
        sqlite3_close(db);
    }
}

