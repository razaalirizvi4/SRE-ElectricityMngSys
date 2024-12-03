#include "pch.h"
#include "MainForm.h"
#include"GlobalFunctions.h"
#include <sstream>
#include <sqlite3.h>
#include <string>
#include <msclr/marshal_cppstd.h>
#include <chrono>
#include "LoginForm.h"
#include <thread>
#include "Userclass.h"


void InitializeTable1(System::Windows::Forms::DataGridView^ targetTable) {
    // Clear the target table
    targetTable->Rows->Clear();
    targetTable->Columns->Clear();

    targetTable->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
    targetTable->ColumnHeadersVisible = true;
    targetTable->RowHeadersVisible = false;
    targetTable->AllowUserToAddRows = false;

    // Copy column structure from Gtable
    for (int i = 0; i < GlobalObjects::Globals::Gtable->ColumnCount; ++i) {
        auto newColumn = gcnew System::Windows::Forms::DataGridViewTextBoxColumn();
        newColumn->HeaderText = GlobalObjects::Globals::Gtable->Columns[i]->HeaderText;
        newColumn->Width = GlobalObjects::Globals::Gtable->Columns[i]->Width;
        targetTable->Columns->Add(newColumn);
    }

    // Copy row data from Gtable
    for (int i = 0; i < GlobalObjects::Globals::Gtable->RowCount; ++i) {
        // Create a new row for the target table
        System::Windows::Forms::DataGridViewRow^ newRow = gcnew System::Windows::Forms::DataGridViewRow();

        // Copy each cell's value from Gtable to the new row
        for (int j = 0; j < GlobalObjects::Globals::Gtable->ColumnCount; ++j) {
            System::Windows::Forms::DataGridViewCell^ newCell = gcnew System::Windows::Forms::DataGridViewTextBoxCell();
            newCell->Value = GlobalObjects::Globals::Gtable->Rows[i]->Cells[j]->Value;
            newRow->Cells->Add(newCell);
        }

        // Add the newly created row to the target table
        targetTable->Rows->Add(newRow);
    }
}

int p4 = 0;//3 times a week
int p5 = 0;//1 time a week

void getWrongP() {
    for (int i = 0; i < GlobalObjectsRaza::Globals::unmanagedGlobals->apl.size(); i++) {
        if (GlobalObjectsRaza::Globals::unmanagedGlobals->apl[i].priority == 4) {
            p4++;
        }
        else if (GlobalObjectsRaza::Globals::unmanagedGlobals->apl[i].priority == 5) {
            p5++;
        }
    }
}

void populateP4(System::Windows::Forms::DataGridView^ targetTable) {
    vector<schedule_appliance::Appliance> arr = sortit(GlobalObjectsRaza::Globals::unmanagedGlobals->apl, 0);
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i].priority == 4) {
            targetTable->Rows[i]->Cells[3]->Value = "+";
            GlobalObjectsRaza::Globals::unmanagedGlobals->bill += (EUS::UserData::offpeakrate * arr[i].kwh) / 3;
            GlobalObjectsRaza::Globals::unmanagedGlobals->dailyunits += arr[i].kwh / 3;
        }
    }
}

void populateP5(System::Windows::Forms::DataGridView^ targetTable) {
    vector<schedule_appliance::Appliance> arr = sortit(GlobalObjectsRaza::Globals::unmanagedGlobals->apl, 0);
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i].priority == 5) {
            targetTable->Rows[i]->Cells[3]->Value = "+";
            GlobalObjectsRaza::Globals::unmanagedGlobals->bill += (EUS::UserData::offpeakrate * arr[i].kwh) / 3;
            GlobalObjectsRaza::Globals::unmanagedGlobals->dailyunits += arr[i].kwh / 3;
        }
    }
}

namespace EUS
{
    MainForm::MainForm(void)
    {
        InitializeComponent();

        sqlite3* db;
        int rc = sqlite3_open("user_management.db", &db);
        if (rc != SQLITE_OK)
        {
            System::Windows::Forms::MessageBox::Show("Failed to open database!");
            return;
        }

        string loggedInEmail = UserData::useremail; // Replace this with the logged-in user's email
        string city = "";  // Variable to store the fetched city
        string area = "";
        int start = -1;
        int end = -1;

        // Step 1: Fetch User_City and User_Area from the Users table
        string query = "SELECT User_City, User_Area FROM Users WHERE User_Email = ?";
        sqlite3_stmt* stmt;

        if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK)
        {
            // Bind the logged-in user's email to the placeholder
            sqlite3_bind_text(stmt, 1, loggedInEmail.c_str(), -1, SQLITE_STATIC);

            if (sqlite3_step(stmt) == SQLITE_ROW)
            {
                const char* userCity = (const char*)sqlite3_column_text(stmt, 0);
                const char* userArea = (const char*)sqlite3_column_text(stmt, 1);

                if (userCity != nullptr) city = userCity; // Store the city
                if (userArea != nullptr) area = userArea; // Store the area
            }
            else
            {
                System::Windows::Forms::MessageBox::Show("No data found for the specified user.");
            }

            sqlite3_finalize(stmt);
        }
        else
        {
            System::Windows::Forms::MessageBox::Show("Failed to prepare SQL statement.");
        }

        sqlite3_close(db);

        
        sqlite3* db1;
        int rc1 = sqlite3_open("user_management.db", &db1);
        if (rc1 != SQLITE_OK)
        {
            System::Windows::Forms::MessageBox::Show("Failed to open database!");
            return;
        }

        // Step 2: Fetch Peak_Start and Peak_End from the Areas table
        string query1 = "SELECT Peak_Start, Peak_End FROM Areas WHERE City = ? AND Area = ?";
        sqlite3_stmt* stmt1;

        if (sqlite3_prepare_v2(db1, query1.c_str(), -1, &stmt1, nullptr) == SQLITE_OK)
        {
            // Bind city and area to the placeholders
            sqlite3_bind_text(stmt1, 1, city.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt1, 2, area.c_str(), -1, SQLITE_STATIC);

            if (sqlite3_step(stmt1) == SQLITE_ROW)
            {
                const char* peakStart = (const char*)sqlite3_column_text(stmt1, 0);
                const char* peakEnd = (const char*)sqlite3_column_text(stmt1, 1);

                if (peakStart != nullptr && peakEnd != nullptr)
                {
                    // Convert "HH:MM" format to integer hours
                    start = stoi(string(peakStart).substr(0, 2));
                    end = stoi(string(peakEnd).substr(0, 2));
                }
            }
            else
            {
                System::Windows::Forms::MessageBox::Show("No data found for the specified city and area.");
            }

            sqlite3_finalize(stmt1);
        }
        else
        {
            System::Windows::Forms::MessageBox::Show("Failed to prepare SQL statement.");
        }

        sqlite3_close(db1);

        //-------------------------------------------------------------------------------------------------//

        // Get the current time
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);

        // Convert time to tm structure
        struct tm* localTime = localtime(&time);

        // Get hours and minutes (24-hour format)
        int h = localTime->tm_hour;
        int m = localTime->tm_min;

        if (h > end)
        {
            ShowNotification(L"Reminder", L"Today's Peak Hour has ended");
        }
        else if (h < start)
        {
            wostringstream oss;
            start = start - h;

            if (m != 0)
            {
                start -= 1;
                m = 60 - m;
            }

            oss << L"Next Peak Hour in " << start << " Hours " << m << " Minutes";
            wstring message = oss.str();
            ShowNotification(L"Reminder", message.c_str());
        }
        else if (h >= start && h <= end)
        {
            ShowNotification(L"Reminder", L"Peak Hour in Progress Right Now");
        }
        //----------------------------------------------------------------------------------------------------------------------------------------//


    }

    MainForm::~MainForm() {
        if (components) {
            delete components;
        }
    }

    void MainForm::InitializeComponent(void) {
        //----------------------------------------------------------------------------------------------------//




        retrive_appliance_names();
        get_appliances();

        for (int i = 0; i < GlobalObjectsRaza::Globals::unmanagedGlobals->apl.size(); i++) {
            int p = (i % 2) + 1;
            if (i == 7)
                p = 4;
            GlobalObjectsRaza::Globals::unmanagedGlobals->apl[i].priority = p;
        }
        vector<schedule_appliance::Appliance> arr = sortit(GlobalObjectsRaza::Globals::unmanagedGlobals->apl, 0);

        float dailyBill = 0.0f;
        const float monthlyThreshold = EUS::UserData::userbudget;
        getWrongP();
        const float dailyThreshold = monthlyThreshold / 30.0f; // Calculate daily threshold
        initializeTable();
        makeTable(GlobalObjectsRaza::Globals::unmanagedGlobals->bill, dailyThreshold, arr);
        //GlobalObjectsRaza::Globals::unmanagedGlobals->bill = dailyBill;

        for (int i = 0; i < 4; i++) {
            Week::Tables^ weekTables = gcnew Week::Tables(); // Create an instance of Tables for each week

            // Initialize and randomize each DataGridView
            DataGridView^ day1 = gcnew DataGridView();
            DataGridView^ day2 = gcnew DataGridView();
            DataGridView^ day3 = gcnew DataGridView();
            DataGridView^ day4 = gcnew DataGridView();
            DataGridView^ day5 = gcnew DataGridView();
            DataGridView^ day6 = gcnew DataGridView();
            DataGridView^ day7 = gcnew DataGridView();

            InitializeTable1(day1);

            RandomizeTable(day1);
            populateP4(day1);
            populateP5(day1);
            InitializeTable1(day2);
            RandomizeTable(day2);
            InitializeTable1(day3);
            //setP4(day3);
            populateP4(day3);
            RandomizeTable(day3);
            InitializeTable1(day4);
            RandomizeTable(day4);
            InitializeTable1(day5);
            RandomizeTable(day5);
            InitializeTable1(day6);
            //setP4(day6);
            populateP4(day6);
            RandomizeTable(day6);
            InitializeTable1(day7);
            RandomizeTable(day7);

            // Assign to instance members of Tables
            weekTables->Gtable1 = day1;
            weekTables->Gtable2 = day2;
            weekTables->Gtable3 = day3;
            weekTables->Gtable4 = day4;
            weekTables->Gtable5 = day5;
            weekTables->Gtable6 = day6;
            weekTables->GTable7 = day7;

            GlobalObjects::Globals::monthlyTables->Add(weekTables);
        }

        sqlite3_close(GlobalObjectsRaza::Globals::unmanagedGlobals->dbr);









        //=============================================================================================================//

        InitializeFormProperties();
        InitializeSidebar();
        InitializeContentPanel();
        SetupEventHandlers();

        thread backgroundThread(CheckConditionInBackground);
        backgroundThread.detach();


    }

    void MainForm::InitializeFormProperties() {
        this->components = gcnew System::ComponentModel::Container();
        this->BackColor = MainPageStyles::BackgroundColor;
        this->WindowState = FormWindowState::Maximized;
    }

    void MainForm::InitializeSidebar() {
        // Initialize sidebar panel
        sidebarPanel = gcnew Panel();
        ConfigureSidebarPanel();

        // Initialize and add controls to sidebar
        InitializeSidebarLabel();
        InitializeSidebarButtons();
        AddControlsToSidebar();
    }

    void MainForm::ConfigureSidebarPanel() {
        sidebarPanel->Dock = DockStyle::Left;
        sidebarPanel->Width = MainPageStyles::SidebarWidth;

        int screenWidth = Screen::PrimaryScreen->Bounds.Width;
        if (screenWidth == 1920) {
            sidebarPanel->Height = MainPageStyles::SidebarHeight;
        }
        else {
            sidebarPanel->Height = 840;
        }

        sidebarPanel->BackColor = MainPageStyles::SidebarColor;
        ApplyRightRoundedCorners(sidebarPanel, MainPageStyles::CornerRadius);
    }

    void MainForm::InitializeSidebarLabel() {
        labelEUS = gcnew Label();
        labelEUS->Text = L"EUS";
        labelEUS->Size = Drawing::Size(150, 65);
        labelEUS->Font = MainPageStyles::TitleFont;
        labelEUS->Dock = DockStyle::Top;
        labelEUS->TextAlign = ContentAlignment::MiddleCenter;
        labelEUS->ForeColor = MainPageStyles::TextColor;
        labelEUS->BackColor = MainPageStyles::SidebarColor;
    }

    void MainForm::InitializeSidebarButtons() {
        btnDashboard = CreateIconButton("icon_dashboard.png", MainPageStyles::ButtonSize);
        btnScheduler = CreateIconButton("icon_scheduler.png", MainPageStyles::ButtonSize);
        btnDevices = CreateIconButton("icon_devices.png", MainPageStyles::ButtonSize);
        btnSettings = CreateIconButton("icon_settings.png", MainPageStyles::ButtonSize);

        ConfigureButtonDocking();
    }

    void MainForm::ConfigureButtonDocking() {
        btnDashboard->Dock = DockStyle::Top;
        btnScheduler->Dock = DockStyle::Top;
        btnDevices->Dock = DockStyle::Top;
        btnSettings->Dock = DockStyle::Top;
    }

    void MainForm::AddControlsToSidebar() {
        sidebarPanel->Controls->Add(btnSettings);
        sidebarPanel->Controls->Add(btnDevices);
        sidebarPanel->Controls->Add(btnScheduler);
        sidebarPanel->Controls->Add(btnDashboard);
        sidebarPanel->Controls->Add(labelEUS);
    }

    void MainForm::InitializeContentPanel() {
        contentPanel = gcnew Panel();
        contentPanel->Dock = DockStyle::Fill;
        contentPanel->BackColor = MainPageStyles::SidebarColor;
    }

    Button^ MainForm::CreateIconButton(String^ iconPath, int size) {
        auto button = gcnew Button();
        button->Size = Drawing::Size(size, size + 5);
        button->BackColor = MainPageStyles::SidebarColor;
        button->FlatStyle = FlatStyle::Flat;
        button->FlatAppearance->BorderSize = 0;
        button->Image = Image::FromFile(iconPath);
        button->ImageAlign = ContentAlignment::MiddleCenter;

        // Add event handlers
        button->Click += gcnew EventHandler(this, &MainForm::OnSidebarButtonClick);
        button->MouseEnter += gcnew EventHandler(this, &MainForm::OnButtonMouseEnter);
        button->MouseLeave += gcnew EventHandler(this, &MainForm::OnButtonMouseLeave);

        return button;
    }

    void MainForm::SetupEventHandlers() {
        this->Controls->Add(contentPanel);
        this->Controls->Add(sidebarPanel);
        this->FormClosing += gcnew FormClosingEventHandler(this, &MainForm::OnFormClosing);
        this->OnSidebarButtonClick(btnDashboard, nullptr);
    }

    void MainForm::ApplyRoundedRectangleToPanel(Panel^ panel, int radius,
        RoundedRectangles::RoundedRectangle::RectangleCorners corners) {
        auto path = RoundedRectangles::RoundedRectangle::Create(0, 0,
            panel->Width, panel->Height, radius, corners);
        panel->Region = gcnew Drawing::Region(path);
    }

    void MainForm::ApplyRightRoundedCorners(Panel^ panel, int radius) {
        auto corners = RoundedRectangles::RoundedRectangle::RectangleCorners::TopRight |
            RoundedRectangles::RoundedRectangle::RectangleCorners::BottomRight;
        ApplyRoundedRectangleToPanel(panel, radius, corners);
    }

    void MainForm::OnButtonMouseEnter(Object^ sender, EventArgs^ e) {
        Button^ btn = dynamic_cast<Button^>(sender);
        if (btn != nullptr) {
            btn->BackColor = MainPageStyles::ButtonHoverColor;
        }
    }

    void MainForm::OnButtonMouseLeave(Object^ sender, EventArgs^ e) {
        Button^ btn = dynamic_cast<Button^>(sender);
        if (btn != nullptr && btn != activeButton) {
            btn->BackColor = MainPageStyles::SidebarColor;
        }
    }

    void MainForm::OnSidebarButtonClick(Object^ sender, EventArgs^ e) {
        Button^ clickedButton = dynamic_cast<Button^>(sender);
        if (clickedButton == nullptr) return;

        UpdateButtonStates(clickedButton);
        UpdateContentPanel(clickedButton);
    }

    void MainForm::UpdateButtonStates(Button^ clickedButton) {
        if (activeButton != nullptr) {
            activeButton->BackColor = MainPageStyles::SidebarColor;
        }
        clickedButton->BackColor = MainPageStyles::ButtonHoverColor;
        activeButton = clickedButton;
    }

    void MainForm::UpdateContentPanel(Button^ clickedButton) {
        contentPanel->Controls->Clear();
        UserControl^ newPage = CreateAppropriateUserControl(clickedButton);

        if (newPage != nullptr) {
            newPage->Dock = DockStyle::Fill;
            contentPanel->Controls->Add(newPage);
        }
    }

    UserControl^ MainForm::CreateAppropriateUserControl(Button^ button) {
        if (button == btnDashboard) return gcnew DashboardUserControl();
        if (button == btnScheduler) return gcnew SchedulerUserControl();
        if (button == btnDevices) return gcnew DevicesUserControl();
        if (button == btnSettings) return gcnew SettingsUserControl();
        return nullptr;
    }

    void MainForm::OnFormClosing(Object^ sender, FormClosingEventArgs^ e) {
        Application::Exit();
    }
}
