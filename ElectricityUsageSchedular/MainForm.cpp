#include "pch.h"
#include "MainForm.h"

namespace EUS {

    MainForm::MainForm(void)
    {
        InitializeComponent();
    }

    MainForm::~MainForm()
    {
        if (components)
        {
            delete components;
        }
    }

    void MainForm::InitializeComponent(void)
    {
        this->components = gcnew System::ComponentModel::Container();
        this->Size = System::Drawing::Size(1240, 730);
        this->Text = L"Electricity Usage Scheduler";

        // Light green accent for sidebar
        sidebarPanel = gcnew Panel();
        sidebarPanel->Dock = DockStyle::Left;
        sidebarPanel->Width = 80;  // Slightly wider for better readability
        sidebarPanel->BackColor = Color::FromArgb(60, 80, 60);  // Lightened green

        // Content panel setup
        contentPanel = gcnew Panel();
        contentPanel->Dock = DockStyle::Fill;
        contentPanel->BackColor = Color::FromArgb(235, 245, 235);

        // Add "EUS" label first item on the sidebar
        labelEUS = gcnew Label();
        labelEUS->Text = L"EUS";
        labelEUS->Size = System::Drawing::Size(50, 50);
        labelEUS->Font = gcnew System::Drawing::Font(L"Arial", 16, FontStyle::Bold);
        labelEUS->Dock = DockStyle::Top;
        labelEUS->TextAlign = ContentAlignment::MiddleCenter;
        labelEUS->ForeColor = Color::FromArgb(255, 223, 0);  // Muted yellow for text color
        labelEUS->BackColor = Color::FromArgb(34, 50, 34); // Darker background for label

        // Create buttons with icons only, docked at the top
        btnDashboard = CreateIconButton("icon_dashboard.png");
        btnScheduler = CreateIconButton("icon_scheduler.png");
        btnDevices = CreateIconButton("icon_devices.png");
        btnAnalytics = CreateIconButton("icon_analytics.png");

        // Settings button at the bottom
        btnSettings = CreateIconButton("icon_settings.png");
        btnSettings->Dock = DockStyle::Bottom;

        // Dock each button to the top
        btnDashboard->Dock = DockStyle::Top;
        btnScheduler->Dock = DockStyle::Top;
        btnDevices->Dock = DockStyle::Top;
        btnAnalytics->Dock = DockStyle::Top;

        // Add buttons to sidebar
        sidebarPanel->Controls->Add(btnSettings);
        sidebarPanel->Controls->Add(btnAnalytics);
        sidebarPanel->Controls->Add(btnDevices);
        sidebarPanel->Controls->Add(btnScheduler);
        sidebarPanel->Controls->Add(btnDashboard);
        sidebarPanel->Controls->Add(labelEUS);

        // Add sidebar and content panel to the main form
        this->Controls->Add(contentPanel);
        this->Controls->Add(sidebarPanel);

        // Register the FormClosing event handler
        this->FormClosing += gcnew FormClosingEventHandler(this, &MainForm::OnFormClosing);

        // Set Dashboard as the default open page
        this->OnSidebarButtonClick(btnDashboard, nullptr);
    }

    Button^ MainForm::CreateIconButton(System::String^ iconPath)
    {
        auto button = gcnew System::Windows::Forms::Button();
        button->Size = System::Drawing::Size(50, 50);
        button->BackColor = Color::FromArgb(60, 80, 60);  // Lighter green for button background
        button->FlatStyle = FlatStyle::Flat;
        button->FlatAppearance->BorderSize = 0;
        button->Image = Image::FromFile(iconPath);
        button->ImageAlign = ContentAlignment::MiddleCenter;
        button->Click += gcnew EventHandler(this, &MainForm::OnSidebarButtonClick);

        // Hover effect: Lighten button background when hovered
        button->MouseEnter += gcnew EventHandler(this, &MainForm::OnButtonMouseEnter);
        button->MouseLeave += gcnew EventHandler(this, &MainForm::OnButtonMouseLeave);

        return button;
    }

    void MainForm::OnButtonMouseEnter(Object^ sender, EventArgs^ e)
    {
        Button^ btn = dynamic_cast<Button^>(sender);
        if (btn != nullptr)
        {
            btn->BackColor = Color::FromArgb(85, 107, 47);  // Lighter green on hover
        }
    }

    void MainForm::OnButtonMouseLeave(Object^ sender, EventArgs^ e)
    {
        Button^ btn = dynamic_cast<Button^>(sender);
        if (btn != nullptr && btn != activeButton)
        {
            btn->BackColor = Color::FromArgb(60, 80, 60);  // Reset to original color
        }
    }

    void MainForm::OnSidebarButtonClick(Object^ sender, EventArgs^ e)
    {
        Button^ clickedButton = dynamic_cast<Button^>(sender);
        if (clickedButton == nullptr) return;

        // Reset previous active button's background
        if (activeButton != nullptr) {
            activeButton->BackColor = Color::FromArgb(60, 80, 60);  // Lightened green
        }

        // Highlight the clicked button
        clickedButton->BackColor = Color::FromArgb(85, 107, 47);  // Yellow accent for active button
        activeButton = clickedButton;

        this->contentPanel->Controls->Clear();  // Clear existing content

        UserControl^ newPage = nullptr;
        if (clickedButton == btnDashboard)
            newPage = gcnew DashboardUserControl();
        else if (clickedButton == btnScheduler)
            newPage = gcnew SchedulerUserControl();
        else if (clickedButton == btnDevices)
            newPage = gcnew DevicesUserControl();
        else if (clickedButton == btnAnalytics)
            newPage = gcnew AnalyticsUserControl();
        else if (clickedButton == btnSettings)
            newPage = gcnew SettingsUserControl();

        if (newPage != nullptr)
        {
            newPage->Dock = DockStyle::Fill;
            this->contentPanel->Controls->Add(newPage);
        }
    }

    void MainForm::OnFormClosing(Object^ sender, FormClosingEventArgs^ e)
    {
        Application::Exit();
    }
}

