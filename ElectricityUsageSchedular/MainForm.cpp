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
        this->BackColor = Color::FromArgb(212, 237, 250);

        this->WindowState = System::Windows::Forms::FormWindowState::Maximized;

        // Sidebar settings
        sidebarPanel = gcnew Panel();
        sidebarPanel->Dock = DockStyle::Left;
        sidebarPanel->Width = 70;
        sidebarPanel->Height = 1055;
        sidebarPanel->BackColor = Color::FromArgb(69, 160, 227);

        // Apply rounded corners to the sidebar
        ApplyRightRoundedCorners(sidebarPanel, 15);

        // Content panel settings
        contentPanel = gcnew Panel();
        contentPanel->Dock = DockStyle::Fill;
        contentPanel->BackColor = Color::FromArgb(69, 160, 227);

        // "EUS" label settings
        labelEUS = gcnew Label();
        labelEUS->Text = L"EUS";
        labelEUS->Size = System::Drawing::Size(150, 60);
        labelEUS->Font = gcnew System::Drawing::Font(L"Calibri", 16, FontStyle::Bold);
        labelEUS->Dock = DockStyle::Top;
        labelEUS->TextAlign = ContentAlignment::MiddleCenter;
        labelEUS->ForeColor = Color::FromArgb(225, 240, 250);
        labelEUS->BackColor = Color::FromArgb(69, 160, 227);

        // Update button sizes for full screen
        btnDashboard = CreateIconButton("icon_dashboard.png", 70);
        btnScheduler = CreateIconButton("icon_scheduler.png", 70);
        btnDevices = CreateIconButton("icon_devices.png", 70);
        btnAnalytics = CreateIconButton("icon_analytics.png", 70);
        btnSettings = CreateIconButton("icon_settings.png", 70);
        btnSettings->Dock = DockStyle::Bottom;

        btnDashboard->Dock = DockStyle::Top;
        btnScheduler->Dock = DockStyle::Top;
        btnDevices->Dock = DockStyle::Top;
        btnAnalytics->Dock = DockStyle::Top;

        sidebarPanel->Controls->Add(btnSettings);
        sidebarPanel->Controls->Add(btnAnalytics);
        sidebarPanel->Controls->Add(btnDevices);
        sidebarPanel->Controls->Add(btnScheduler);
        sidebarPanel->Controls->Add(btnDashboard);
        sidebarPanel->Controls->Add(labelEUS);

        this->Controls->Add(contentPanel);
        this->Controls->Add(sidebarPanel);

        this->FormClosing += gcnew FormClosingEventHandler(this, &MainForm::OnFormClosing);
        this->OnSidebarButtonClick(btnDashboard, nullptr);
    }

    // Update CreateIconButton to accept size parameters
    Button^ MainForm::CreateIconButton(System::String^ iconPath, int size)
    {
        auto button = gcnew System::Windows::Forms::Button();
        button->Size = System::Drawing::Size(size, size);
        button->BackColor = Color::FromArgb(69, 160, 227);
        button->FlatStyle = FlatStyle::Flat;
        button->FlatAppearance->BorderSize = 0;
        button->Image = Image::FromFile(iconPath);
        button->ImageAlign = ContentAlignment::MiddleCenter;
        button->Click += gcnew EventHandler(this, &MainForm::OnSidebarButtonClick);

        button->MouseEnter += gcnew EventHandler(this, &MainForm::OnButtonMouseEnter);
        button->MouseLeave += gcnew EventHandler(this, &MainForm::OnButtonMouseLeave);

        return button;
    }

    void MainForm::ApplyRoundedRectangleToPanel(Panel^ panel, int radius, RoundedRectangles::RoundedRectangle::RectangleCorners corners)
    {
        System::Drawing::Drawing2D::GraphicsPath^ path = RoundedRectangles::RoundedRectangle::Create(
            0, 0, panel->Width, panel->Height, radius, corners
        );
        panel->Region = gcnew System::Drawing::Region(path);
    }

    void MainForm::ApplyRightRoundedCorners(Panel^ panel, int radius)
    {
        GraphicsPath^ path = RoundedRectangles::RoundedRectangle::Create(0, 0, panel->Width, panel->Height, radius,
            RoundedRectangles::RoundedRectangle::RectangleCorners::TopRight |
            RoundedRectangles::RoundedRectangle::RectangleCorners::BottomRight);
        panel->Region = gcnew System::Drawing::Region(path);
    }

    void MainForm::OnButtonMouseEnter(Object^ sender, EventArgs^ e)
    {
        Button^ btn = dynamic_cast<Button^>(sender);
        if (btn != nullptr)
        {
            btn->BackColor = Color::FromArgb(115, 178, 243);
        }
    }

    void MainForm::OnButtonMouseLeave(Object^ sender, EventArgs^ e)
    {
        Button^ btn = dynamic_cast<Button^>(sender);
        if (btn != nullptr && btn != activeButton)
        {
            btn->BackColor = Color::FromArgb(69, 160, 227);
        }
    }

    void MainForm::OnSidebarButtonClick(Object^ sender, EventArgs^ e)
    {
        Button^ clickedButton = dynamic_cast<Button^>(sender);
        if (clickedButton == nullptr) return;

        // Reset previous active button's background
        if (activeButton != nullptr) {
            activeButton->BackColor = Color::FromArgb(69, 160, 227);
        }

        // Highlight the clicked button
        clickedButton->BackColor = Color::FromArgb(115, 178, 243);
        activeButton = clickedButton;

        this->contentPanel->Controls->Clear();

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
