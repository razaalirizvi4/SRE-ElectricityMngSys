#include "pch.h"
#include "DashboardUserControl.h"

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
                Point(0, 10)); // Offset for title
            panel->Controls->Add(titleLabel);
        }

        // Content
        if (!String::IsNullOrEmpty(config.Content)) {
            cli::array<String^>^ contentLines = config.Content->Split('\n');
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
		topSectionPanel->Size = System::Drawing::Size(1420, this->Height / 3);
        topSectionPanel->Location = Point(DashboardStyles::DefaultMargin, DashboardStyles::DefaultMargin - 30);
        topSectionPanel->BackColor = DashboardStyles::MainBackColor;

        ApplyRoundedRectangleToPanel(topSectionPanel, DashboardStyles::DefaultCornerRadius);

        int boxWidth = (topSectionPanel->Width - DashboardStyles::DefaultSpacing - 90) / 2;
        int boxHeight = topSectionPanel->Height - DashboardStyles::DefaultSpacing2 - 50;

        // Determine current time and whether it's within peak hours
        DateTime now = DateTime::Now;
        int currentHour = now.Hour;
        int startHour = timetoInt(UserData::userpeakstart);
        int endHour = timetoInt(UserData::userpeakend);

        double currentRate = (currentHour >= startHour && currentHour < endHour)
            ? UserData::peakrate
            : UserData::offpeakrate;

        // vars
        int bill = static_cast<int>(GlobalObjectsRaza::Globals::unmanagedGlobals->bill);
        int units = bill / currentRate;

        // First Box Configuration
        PanelConfig box1Config;
        box1Config.Width = boxWidth;
        box1Config.Height = boxHeight;
        box1Config.Location = Point(0, 0);
        box1Config.BackColor = DashboardStyles::PanelBackColor;
        box1Config.LineSpacing = 3;
        box1Config.ContentYOffset = 50;
        box1Config.Title = "Energy Consumption Overview";
        box1Config.Content = gcnew String(
            ("Daily Usage: " + std::to_string(units) + " kWh\n" +
                "Todays Units: " + std::to_string(units) + "\n" +
                "Peak Today: " + UserData::userpeakstart + "\n").c_str());

        // Second Box Configuration
        PanelConfig box2Config = box1Config;
        box2Config.Location = Point(boxWidth + DashboardStyles::DefaultSpacing + 10, 0);
        box2Config.Title = "Current Rate Info";

        box2Config.Content = gcnew String(
            ("Current Rate: Pkr " + std::to_string(static_cast<int>(UserData::offpeakrate)) + "/kWh\nPeak Hours: " + UserData::userpeakstart + " - " + UserData::userpeakend + "\n" +
                "Today's Est. Cost: Pkr " + std::to_string(bill)).c_str());

        topSectionPanel->Controls->Add(CreatePanel(box1Config));
        topSectionPanel->Controls->Add(CreatePanel(box2Config));

        return topSectionPanel;
    }

    Panel^ DashboardUserControl::CreateBottomSection() {
        energySavingTips = gcnew cli::array<String^> {
            "Schedule laundry for off-peak hours.",
                "Turn off lights when not in use.",
                "Unplug devices that are not being used.",
                "Use a programmable thermostat to save energy.",
                "Seal windows and doors to reduce energy waste.",
                "Set your water heater to 50°C for efficiency.",
                "Use energy-efficient LED light bulbs.",
                "Clean or replace air filters regularly."
        };
        currentTipIndex = 4;

        // Create a container for the bottom section
        Panel^ bottomSectionPanel = gcnew Panel();
        bottomSectionPanel->Size = System::Drawing::Size(1430, this->Height / 5);
        bottomSectionPanel->Location = Point(DashboardStyles::DefaultMargin, 685);
        bottomSectionPanel->BackColor = DashboardStyles::MainBackColor;

        ApplyRoundedRectangleToPanel(bottomSectionPanel, DashboardStyles::DefaultCornerRadius);

        // Add rounded buttons
        Button^ prevButton = CreateRoundedButton("icon_left.png", 75, Point(0, bottomSectionPanel->Height / 2 - 40));
        Button^ nextButton = CreateRoundedButton("icon_right.png", 75, Point(bottomSectionPanel->Width - 160, bottomSectionPanel->Height / 2 - 40));

        // Add central rounded box
        tipsPanelConfig;
        tipsPanelConfig.Width = bottomSectionPanel->Width - 450;
        tipsPanelConfig.Height = bottomSectionPanel->Height - 20;
        tipsPanelConfig.Location = Point(180, 10);
        tipsPanelConfig.BackColor = DashboardStyles::PanelBackColor;
        tipsPanelConfig.LineSpacing = 5;
        tipsPanelConfig.ContentYOffset = 55;
        tipsPanelConfig.Title = "Energy Saving Tips";
        tipsPanelConfig.Content = energySavingTips[currentTipIndex];

        Panel^ tipsPanel = CreatePanel(tipsPanelConfig);

        // Add cycling logic
        prevButton->Click += gcnew EventHandler(this, &DashboardUserControl::ShowPreviousTip);
        nextButton->Click += gcnew EventHandler(this, &DashboardUserControl::ShowNextTip);

        bottomSectionPanel->Controls->Add(prevButton);
        bottomSectionPanel->Controls->Add(nextButton);
        bottomSectionPanel->Controls->Add(tipsPanel);

        return bottomSectionPanel;
    }

    void DashboardUserControl::InitializeComponent(void) {
        this->components = gcnew System::ComponentModel::Container();
        this->Size = System::Drawing::Size(1480, 685);

        this->Dock = DockStyle::Fill;
        this->BackColor = DashboardStyles::MainBackColor;

        // Create and add the top section
        Panel^ topSectionPanel = CreateTopSection();
        this->Controls->Add(topSectionPanel);

        // Create and add the bottom section
        Panel^ bottomSectionPanel = CreateBottomSection();
        this->Controls->Add(bottomSectionPanel);
    }

    // Tip cycling logic
    void DashboardUserControl::ShowPreviousTip(Object^ sender, EventArgs^ e) {
        if (energySavingTips->Length == 0) return;

        currentTipIndex = (currentTipIndex - 1 + energySavingTips->Length) % energySavingTips->Length;
        UpdateTipContent();
    }

    void DashboardUserControl::ShowNextTip(Object^ sender, EventArgs^ e) {
        if (energySavingTips->Length == 0) return;

        currentTipIndex = (currentTipIndex + 1) % energySavingTips->Length;
        UpdateTipContent();
    }

    void DashboardUserControl::UpdateTipContent() {
        // Find the central panel and update its content
        Panel^ bottomSectionPanel = dynamic_cast<Panel^>(this->Controls[1]);
        if (bottomSectionPanel) {
            Panel^ tipsPanel = dynamic_cast<Panel^>(bottomSectionPanel->Controls[2]);
            if (tipsPanel && tipsPanel->Controls->Count > 0) {
                Label^ contentLabel = dynamic_cast<Label^>(tipsPanel->Controls[1]);
                if (contentLabel) {
                    contentLabel->Text = energySavingTips[currentTipIndex];
                }
                return;
            }
        }
    }
}
