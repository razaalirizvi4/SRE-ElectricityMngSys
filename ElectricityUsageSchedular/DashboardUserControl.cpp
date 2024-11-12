#include "pch.h"
#include "DashboardUserControl.h"
#include "RoundedRectangle.h"

namespace EUS {

    DashboardUserControl::DashboardUserControl(void) {
        InitializeComponent();
    }

    DashboardUserControl::~DashboardUserControl() {
        if (components) {
            delete components;
        }
    }

    Label^ DashboardUserControl::CreateLabel(String^ text, System::Drawing::Font^ font, Color color, int width, int height, Point location) {
        Label^ label = gcnew Label();
        label->Text = text;
        label->Font = font;
        label->ForeColor = color;
        label->Size = System::Drawing::Size(width, height);
        label->Location = location;
        label->TextAlign = ContentAlignment::MiddleLeft;
        label->Padding = System::Windows::Forms::Padding(10, 0, 0, 0);
        return label;
    }

    Panel^ DashboardUserControl::CreatePanel(PanelConfig config) {
        // Adjusting size and location to simulate padding
        int padding = 15;
        Panel^ panel = gcnew Panel();
        panel->Size = System::Drawing::Size(config.Width - 2 * padding, config.Height - 2 * padding);
        panel->Location = Point(config.Location.X + padding, config.Location.Y + padding);
        panel->BackColor = config.BackColor;

        // Title
        if (!String::IsNullOrEmpty(config.Title)) {
            Label^ titleLabel = CreateLabel(config.Title,
                DashboardStyles::TitleFont,
                Color::White,
                panel->Width,
                30,
                Point(10, 10)); // Offset for title
            panel->Controls->Add(titleLabel);
        }

        // Content
        if (!String::IsNullOrEmpty(config.Content)) {
            Label^ contentLabel = CreateLabel(config.Content,
                DashboardStyles::ContentFont,
                Color::White,
                panel->Width - 20,
                panel->Height - 50,
                Point(10, 50)); // Offset for content
            contentLabel->AutoSize = false;
            panel->Controls->Add(contentLabel);
        }

        ApplyRoundedRectangleToPanel(panel, DashboardStyles::DefaultCornerRadius);
        return panel;
    }

    void DashboardUserControl::ApplyRoundedRectangleToPanel(Panel^ panel, int radius) {
        System::Drawing::Drawing2D::GraphicsPath^ path = RoundedRectangles::RoundedRectangle::Create(
            0, 0, panel->Width, panel->Height, radius,
            RoundedRectangles::RoundedRectangle::RectangleCorners::All
        );
        panel->Region = gcnew System::Drawing::Region(path);
    }

    Panel^ DashboardUserControl::CreateTopLeftSection() {
        int padding = DashboardStyles::DefaultMargin / 2; // Add extra padding to top-left
        PanelConfig config;
        config.Width = this->Width - DashboardStyles::DefaultMargin;
        config.Height = this->Height / 2 - DashboardStyles::DefaultMargin;
        config.Location = Point(DashboardStyles::DefaultMargin + padding, DashboardStyles::DefaultMargin + padding);
        config.BackColor = DashboardStyles::PanelBackColor;
        config.Title = "Energy Consumption Overview";
        config.Content = "Daily Usage: 28.5 kWh\n"
            "Current Power: 2.4 kW\n"
            "Peak Today: 3.8 kW at 18:30\n"
            "Week-over-Week Change: -5.2%";

        return CreatePanel(config);
    }

    Panel^ DashboardUserControl::CreateBottomLeftSection(Point location) {
        Panel^ containerPanel = gcnew Panel();
        containerPanel->Size = System::Drawing::Size(
            this->Width - DashboardStyles::DefaultMargin,
            this->Height / 2 - DashboardStyles::DefaultMargin + DashboardStyles::MiniBoxHeight
        );
        containerPanel->Location = location;
        containerPanel->BackColor = DashboardStyles::MainBackColor;

        ApplyRoundedRectangleToPanel(containerPanel, DashboardStyles::DefaultCornerRadius);

        int boxHeight = (containerPanel->Height - DashboardStyles::DefaultSpacing - 100);

        // Device Management Box
        PanelConfig box1Config;
        box1Config.Width = containerPanel->Width / 2 - DashboardStyles::DefaultSpacing + 70;
        box1Config.Height = boxHeight - 110;
        box1Config.Location = Point(0, 0);
        box1Config.BackColor = DashboardStyles::PanelBackColor;
        box1Config.Title = "Current Rate Info";
        box1Config.Content = "Current Rate: $0.14/kWh\n"
            "Peak Hours: 14:00 - 19:00\n"
            "Next Rate Change: 2hrs 15min\n"
            "Today's Est. Cost: $8.45";

        containerPanel->Controls->Add(CreatePanel(box1Config));

        // Performance Metrics Box
        PanelConfig box2Config;
        box2Config.Width = containerPanel->Width / 2 - DashboardStyles::DefaultSpacing + 75;
        box2Config.Height = boxHeight - 110;
        box2Config.Location = Point(containerPanel->Width / 2 - 25, boxHeight - 90);
        box2Config.BackColor = DashboardStyles::PanelBackColor; 
        box2Config.Title = "Energy Saving Tips";
        box2Config.Content = "• Schedule laundry for off-peak hours\n"
            "• HVAC efficiency decreasing (check filter)\n"
            "• Smart scheduling could save $25/month\n"
            "• Consider upgrading to LED bulbs";

        containerPanel->Controls->Add(CreatePanel(box2Config));

        return containerPanel;
    }

    Panel^ DashboardUserControl::CreateRightSection(Point location) {
        Panel^ containerPanel = gcnew Panel();
        containerPanel->Size = System::Drawing::Size(
            this->Width - 520 - 5,
            this->Height - DashboardStyles::DefaultMargin + 100
        );
        containerPanel->Location = location;
        containerPanel->BackColor = DashboardStyles::MainBackColor;

        ApplyRoundedRectangleToPanel(containerPanel, DashboardStyles::DefaultCornerRadius);

        // Rate Information Box
        PanelConfig box1Config;
        box1Config.Width = containerPanel->Width;
        box1Config.Height = containerPanel->Height / 2 - DashboardStyles::DefaultSpacing + 40;
        box1Config.Location = Point(0, 0);
        box1Config.BackColor = DashboardStyles::PanelBackColor;
        box1Config.Title = "Device Management";
        box1Config.Content = "Active Devices:\n"
            "• HVAC System: ON (2.1 kW)\n"
            "• Water Heater: Standby (0.1 kW)\n"
            "• Washing Machine: OFF\n"
            "• Dishwasher: Scheduled (21:00)";

        containerPanel->Controls->Add(CreatePanel(box1Config));

        // Energy Tips Box
        PanelConfig box2Config;
        box2Config.Width = containerPanel->Width;
        box2Config.Height = containerPanel->Height / 2 - DashboardStyles::DefaultSpacing + 45;
        box2Config.Location = Point(0, box1Config.Height + DashboardStyles::DefaultSpacing2);
        box2Config.BackColor = DashboardStyles::PanelBackColor;
        box2Config.Title = "Performance Metrics";
        box2Config.Content = "Energy Efficiency Score: 85/100\n"
            "Weekly Goal Progress: 68%\n"
            "Monthly Savings: $42.30\n"
            "Carbon Footprint: -15% vs. Last Month";

        containerPanel->Controls->Add(CreatePanel(box2Config));

        return containerPanel;
    }

    void DashboardUserControl::InitializeComponent(void) {
        this->components = gcnew System::ComponentModel::Container();

        int screenWidth = Screen::PrimaryScreen->Bounds.Width;
        if (screenWidth == 1920) {
            this->Size = System::Drawing::Size(1140, 900);
        }
        else {
            this->Size = System::Drawing::Size(940, 685);
            DashboardStyles::MiniBoxHeight = 165;
        }

        this->BackColor = DashboardStyles::MainBackColor;

        // Create and add top-left section
        Panel^ topLeftPanel = CreateTopLeftSection();
        this->Controls->Add(topLeftPanel);

        // Create and add bottom-left section
        Panel^ bottomLeftPanel = CreateBottomLeftSection(
            Point(DashboardStyles::DefaultMargin,
                topLeftPanel->Bottom + DashboardStyles::DefaultSpacing)
        );
        this->Controls->Add(bottomLeftPanel);

        // Create and add right section
        Panel^ rightPanel = CreateRightSection(
            Point(topLeftPanel->Right + DashboardStyles::DefaultSpacing,
                DashboardStyles::DefaultMargin)
        );
        this->Controls->Add(rightPanel);
    }
}
