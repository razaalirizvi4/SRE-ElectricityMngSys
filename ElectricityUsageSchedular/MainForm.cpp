#include "pch.h"
#include "MainForm.h"
#include"GlobalFunctions.h"
#include <sstream>
#include <sqlite3.h>
#include <string>
#include <msclr/marshal_cppstd.h>
#include <chrono>

namespace EUS {
    MainForm::MainForm(void) {
        InitializeComponent();

        sqlite3* db;
        int rc = sqlite3_open("user_management.db", &db);
        if (rc != SQLITE_OK)
        {
            System::Windows::Forms::MessageBox::Show("Failed to open database!");
            return;
        }

        string loggedInEmail = "a@a.com"; // Replace this with the logged-in user's email
        string prov = ""; // Variable to store the fetched province
        string city = "";
        int start = -1;                 // To store the starting hour
        int end = -1;                   // To store the ending hour

        string query = "SELECT User_Province, User_City FROM Users WHERE User_Email = ?";
        sqlite3_stmt* stmt;

        if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK)
        {
            // Bind the logged-in user's username to the placeholder
            sqlite3_bind_text(stmt, 1, loggedInEmail.c_str(), -1, SQLITE_STATIC);

            if (sqlite3_step(stmt) == SQLITE_ROW)
            {
                const char* province = (const char*)sqlite3_column_text(stmt, 0);
                const char* userCity = (const char*)sqlite3_column_text(stmt, 1);

                if (province != nullptr)
                {
                    prov = province; // Store the province
                }
                if (userCity != nullptr)
                {
                    city = userCity; // Store the city
                }
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
        //----------------------------------------------------------------------------------------------------//

        sqlite3* db1;
        int rc1 = sqlite3_open("user_management.db", &db1);
        if (rc1 != SQLITE_OK)
        {
            System::Windows::Forms::MessageBox::Show("Failed to open database!");
            return;
        }

        string query1 = "SELECT PeakStart, PeakEnd FROM Peak_Hours WHERE Province = ? AND City = ?";
        sqlite3_stmt* stmt1;

        if (sqlite3_prepare_v2(db1, query1.c_str(), -1, &stmt1, nullptr) == SQLITE_OK)
        {
            // Bind province and city to the placeholders
            sqlite3_bind_text(stmt1, 1, prov.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt1, 2, city.c_str(), -1, SQLITE_STATIC);

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
                System::Windows::Forms::MessageBox::Show("No data found for the specified province and city.");
            }

            sqlite3_finalize(stmt);
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
                start - 1;
                m = 60 - m;
            }

            oss << L"Next Peak Hour in " << start << " Hours " << m << " Minutes";
            wstring message = oss.str();
            ShowNotification(L"Reminder", message.c_str());
        }
        else if (h > start && h < end)
        {
            ShowNotification(L"Reminder", L"Peak Hour in Progress Right Now");
        }
    }

    MainForm::~MainForm() {
        if (components) {
            delete components;
        }
    }

    void MainForm::InitializeComponent(void) {
        InitializeFormProperties();
        InitializeSidebar();
        InitializeContentPanel();
        SetupEventHandlers();
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
        btnAnalytics = CreateIconButton("icon_analytics.png", MainPageStyles::ButtonSize);
        btnSettings = CreateIconButton("icon_settings.png", MainPageStyles::ButtonSize);

        ConfigureButtonDocking();
    }

    void MainForm::ConfigureButtonDocking() {
        btnSettings->Dock = DockStyle::Bottom;
        btnDashboard->Dock = DockStyle::Top;
        btnScheduler->Dock = DockStyle::Top;
        btnDevices->Dock = DockStyle::Top;
        btnAnalytics->Dock = DockStyle::Top;
    }

    void MainForm::AddControlsToSidebar() {
        sidebarPanel->Controls->Add(btnSettings);
        sidebarPanel->Controls->Add(btnAnalytics);
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
        if (button == btnAnalytics) return gcnew AnalyticsUserControl();
        if (button == btnSettings) return gcnew SettingsUserControl();
        return nullptr;
    }

    void MainForm::OnFormClosing(Object^ sender, FormClosingEventArgs^ e) {
        Application::Exit();
    }
}
