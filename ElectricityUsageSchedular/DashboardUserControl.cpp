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
        label->TextAlign = ContentAlignment::MiddleCenter; // Center-align text
        return label;
    }

    Panel^ DashboardUserControl::CreatePanel(PanelConfig config) {
        Panel^ panel = gcnew Panel();
        panel->Size = System::Drawing::Size(config.Width, config.Height);
        panel->Location = config.Location;
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
            array<String^>^ contentLines = config.Content->Split('\n');
            int yOffset = config.ContentYOffset;

            for each (String ^ line in contentLines) {
                Label^ lineLabel = CreateLabel(line,
                    DashboardStyles::ContentFont,
                    Color::White,
                    panel->Width - 20,
                    25, // Set the height of each line label
                    Point(10, yOffset));
                lineLabel->AutoSize = false;
                panel->Controls->Add(lineLabel);
                yOffset += 25 + config.LineSpacing;
            }
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
        PanelConfig config;
        config.Width = this->Width - DashboardStyles::DefaultMargin;
        config.Height = this->Height / 2 - DashboardStyles::DefaultMargin;
        config.Location = Point(DashboardStyles::DefaultMargin, DashboardStyles::DefaultMargin);
        config.BackColor = DashboardStyles::PanelBackColor;
        config.LineSpacing = 70;
        config.ContentYOffset = 90;
        config.Title = "Energy Consumption Overview";
        config.Content =
            "Daily Usage: 28.5 kWh                                Current Power: 2.4 kW\n"
            "Peak Today: 3.8 kW at 18:30                          Week-over-Week Change: -5.2%\n";

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
        box1Config.LineSpacing = 3;
        box1Config.ContentYOffset = 60;
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
        box2Config.LineSpacing = 3;
        box2Config.ContentYOffset = 60;
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
        box1Config.LineSpacing = 15;
        box1Config.ContentYOffset = 110;
        box1Config.Title = "Device Management";
        box1Config.Content = "• HVAC System: ON (2.1 kW)\n"
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
        box2Config.LineSpacing = 15;
        box2Config.ContentYOffset = 110;
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
