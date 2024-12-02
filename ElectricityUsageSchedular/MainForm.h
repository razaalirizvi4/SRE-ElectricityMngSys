#pragma once
#include "DashboardUserControl.h"
#include "SchedulerUserControl.h"
#include "DevicesUserControl.h"
#include "AnalyticsUserControl.h"
#include "SettingsUserControl.h"
#include "RoundedRectangle.h"


namespace EUS {
    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class MainPageStyles {
    public:
        // Colors
        static initonly Color BackgroundColor = Color::FromArgb(212, 237, 250);
        static initonly Color SidebarColor = Color::FromArgb(69, 160, 227);
        static initonly Color ButtonHoverColor = Color::FromArgb(115, 178, 243);
        static initonly Color TextColor = Color::FromArgb(225, 240, 250);

        // Fonts
        static initonly System::Drawing::Font^ TitleFont = gcnew System::Drawing::Font("Segoe UI", 18, FontStyle::Bold);
        static initonly System::Drawing::Font^ ContentFont = gcnew System::Drawing::Font("Calibri", 12);

        // Sizing and Layout
        static const int SidebarWidth = 70;
        static const int SidebarHeight = 1055;
        static const int CornerRadius = 20;
        static const int ButtonSize = 70;
        static const int DefaultMargin = 60;
        static const int DefaultSpacing = 50;
        static const int AlternativeSpacing = 20;
    };

    public ref class MainForm : public System::Windows::Forms::Form {
    public:
        MainForm(void);
    protected:
        ~MainForm();
    private:
        // Components
        System::ComponentModel::Container^ components;
        Panel^ sidebarPanel;
        Panel^ contentPanel;
        Label^ labelEUS;
        Button^ btnDashboard;
        Button^ btnScheduler;
        Button^ btnDevices;
        Button^ btnAnalytics;
        Button^ btnSettings;
        Button^ activeButton;

        // Initialization methods
        void InitializeComponent(void);
        void InitializeFormProperties();
        void InitializeSidebar();
        void InitializeContentPanel();
        void ConfigureSidebarPanel();
        void InitializeSidebarLabel();
        void InitializeSidebarButtons();
        void ConfigureButtonDocking();
        void AddControlsToSidebar();
        void SetupEventHandlers();

        // Helper methods
        Button^ CreateIconButton(String^ iconPath, int size);
        void ApplyRoundedRectangleToPanel(Panel^ panel, int radius,
            RoundedRectangles::RoundedRectangle::RectangleCorners corners);
        void ApplyRightRoundedCorners(Panel^ panel, int radius);
        UserControl^ CreateAppropriateUserControl(Button^ button);
        void UpdateButtonStates(Button^ clickedButton);
        void UpdateContentPanel(Button^ clickedButton);

        // Event handlers
        void OnButtonMouseEnter(Object^ sender, EventArgs^ e);
        void OnButtonMouseLeave(Object^ sender, EventArgs^ e);
        void OnSidebarButtonClick(Object^ sender, EventArgs^ e);
        void OnFormClosing(Object^ sender, FormClosingEventArgs^ e);
    };
}
