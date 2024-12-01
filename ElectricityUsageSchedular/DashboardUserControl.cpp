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

    Button^ DashboardUserControl::CreateRoundedButton(String^ iconPath, int size, Point location) {
        Button^ button = gcnew Button();
        button->Size = System::Drawing::Size(size, size);
        button->Location = location;
        button->BackColor = DashboardStyles::PanelBackColor;
        button->FlatStyle = FlatStyle::Flat;
        button->FlatAppearance->BorderSize = 0;

        // Set the icon
        button->Image = Image::FromFile(iconPath);
        button->ImageAlign = ContentAlignment::MiddleCenter;

        // Apply rounded corners
        System::Drawing::Drawing2D::GraphicsPath^ path = RoundedRectangles::RoundedRectangle::Create(
            0, 0, size, size, size / 2,
            RoundedRectangles::RoundedRectangle::RectangleCorners::All
        );
        button->Region = gcnew System::Drawing::Region(path);

        return button;
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

    Panel^ DashboardUserControl::CreateTopSection() {
        // Create a container for the top section
        Panel^ topSectionPanel = gcnew Panel();
			topSectionPanel->Size = System::Drawing::Size(1400, this->Height / 3);
        topSectionPanel->Location = Point(DashboardStyles::DefaultMargin, DashboardStyles::DefaultMargin);
        topSectionPanel->BackColor = DashboardStyles::MainBackColor;

        ApplyRoundedRectangleToPanel(topSectionPanel, DashboardStyles::DefaultCornerRadius);

        int boxWidth = (topSectionPanel->Width - DashboardStyles::DefaultSpacing - 100) / 3;
        int boxHeight = topSectionPanel->Height - DashboardStyles::DefaultSpacing2;

        // First Box Configuration
        PanelConfig box1Config;
        box1Config.Width = boxWidth;
        box1Config.Height = boxHeight;
        box1Config.Location = Point(0, 0);
        box1Config.BackColor = DashboardStyles::PanelBackColor;
        box1Config.LineSpacing = 3;
        box1Config.ContentYOffset = 60;
        box1Config.Title = "Energy Consumption Overview";
        box1Config.Content =
            "Daily Usage: 28.5 kWh\n"
            "Current Power: 2.4 kW\n"
            "Peak Today: 3.8 kW at 18:30\n"
            "Week-over-Week Change: -5.2%";

        // Second Box Configuration
        PanelConfig box2Config = box1Config;
        box2Config.Location = Point(boxWidth + DashboardStyles::DefaultSpacing, 0);
        box2Config.Title = "Current Rate Info";
        box2Config.Content =
            "Current Rate: $0.14/kWh\n"
            "Peak Hours: 14:00 - 19:00\n"
            "Next Rate Change: 2hrs 15min\n"
            "Today's Est. Cost: $8.45";

        // Third Box Configuration
        PanelConfig box3Config = box1Config;
        box3Config.Location = Point(2 * (boxWidth + DashboardStyles::DefaultSpacing), 0);
        box3Config.Title = "Energy Saving Tips";
        box3Config.Content =
            "• Schedule laundry for off-peak hours\n"
            "• HVAC efficiency decreasing (check filter)\n"
            "• Smart scheduling could save $25/month\n"
            "• Consider upgrading to LED bulbs";

        topSectionPanel->Controls->Add(CreatePanel(box1Config));
        topSectionPanel->Controls->Add(CreatePanel(box2Config));

        Button^ roundedButton = CreateRoundedButton("icon_settings.png", 100, Point(2 * (boxWidth + DashboardStyles::DefaultSpacing) + 310, 52));
        topSectionPanel->Controls->Add(roundedButton);

        return topSectionPanel;
    }

    void DashboardUserControl::InitializeComponent(void) {
        this->components = gcnew System::ComponentModel::Container();
        this->Size = System::Drawing::Size(1400, 685);

        this->Dock = DockStyle::Fill;
        this->BackColor = DashboardStyles::MainBackColor;

        // Create and add the top section
        Panel^ topSectionPanel = CreateTopSection();
        this->Controls->Add(topSectionPanel);
    }
}
