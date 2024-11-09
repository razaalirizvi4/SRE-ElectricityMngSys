#include "pch.h"
#include "MainForm.h"

namespace EUS {
    MainForm::MainForm(void) {
        InitializeComponent();
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
        sidebarPanel->Height = MainPageStyles::SidebarHeight;
        sidebarPanel->BackColor = MainPageStyles::SidebarColor;
        ApplyRightRoundedCorners(sidebarPanel, MainPageStyles::CornerRadius);
    }

    void MainForm::InitializeSidebarLabel() {
        labelEUS = gcnew Label();
        labelEUS->Text = L"EUS";
        labelEUS->Size = Drawing::Size(150, 60);
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
        button->Size = Drawing::Size(size, size);
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
