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

    Label^ DashboardUserControl::CreateLabel(String^ text, System::Drawing::Font^ font, Color color, int width, int height, Point location) {
        Label^ label = gcnew Label();
        label->Text = text;
        label->Font = font;
        label->ForeColor = color;
        label->Size = System::Drawing::Size(width, height);
        label->Location = location;
        label->TextAlign = ContentAlignment::MiddleCenter;
        return label;
    }

    Panel^ DashboardUserControl::CreatePanel(PanelConfig config) {
        Panel^ panel = gcnew Panel();
        panel->Size = System::Drawing::Size(config.Width, config.Height);
        panel->Location = config.Location;
        panel->BackColor = config.BackColor;

        if (!String::IsNullOrEmpty(config.Title)) {
            panel->Controls->Add(CreateLabel(config.Title,
                DashboardStyles::TitleFont,
                Color::White,
                panel->Width,
                30,
                Point(0, 0)));
        }

        if (!String::IsNullOrEmpty(config.Content)) {
            panel->Controls->Add(CreateLabel(config.Content,
                DashboardStyles::ContentFont,
                Color::White,
                panel->Width,
                50,
                Point(0, 40)));
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
        config.Title = "Top-left Section";
        config.Content = "Content for top-left box.";

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

        // Add Box 1
        PanelConfig box1Config;
        box1Config.Width = containerPanel->Width / 2 - DashboardStyles::DefaultSpacing + 70;
        box1Config.Height = boxHeight - 110;
        box1Config.Location = Point(0, 0);
        box1Config.BackColor = DashboardStyles::PanelBackColor;
        box1Config.Title = "Bottom-left Box 1";
        box1Config.Content = "Content for box 1.";

        containerPanel->Controls->Add(CreatePanel(box1Config));

        // Add Box 2
        PanelConfig box2Config;
        box2Config.Width = containerPanel->Width / 2 - DashboardStyles::DefaultSpacing + 75;
        box2Config.Height = boxHeight - 110;
        box2Config.Location = Point(containerPanel->Width / 2 - 25, boxHeight - 90);
        box2Config.BackColor = DashboardStyles::PanelBackColor;
        box2Config.Title = "Bottom-left Box 2";
        box2Config.Content = "Content for box 2.";

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

        // Add Box 1
        PanelConfig box1Config;
        box1Config.Width = containerPanel->Width;
        box1Config.Height = containerPanel->Height / 2 - DashboardStyles::DefaultSpacing + 40;
        box1Config.Location = Point(0, 0);
        box1Config.BackColor = DashboardStyles::PanelBackColor;
        box1Config.Title = "Right-side Box 1";
        box1Config.Content = "Content for right-side box 1.";

        containerPanel->Controls->Add(CreatePanel(box1Config));

        // Add Box 2
        PanelConfig box2Config;
        box2Config.Width = containerPanel->Width;
        box2Config.Height = containerPanel->Height / 2 - DashboardStyles::DefaultSpacing + 45;
        box2Config.Location = Point(0, box1Config.Height + DashboardStyles::DefaultSpacing2);
        box2Config.BackColor = DashboardStyles::PanelBackColor;
        box2Config.Title = "Right-side Box 2";
        box2Config.Content = "Content for right-side box 2.";

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
