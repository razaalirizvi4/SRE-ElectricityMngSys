#include "pch.h"
#include "DashboardUserControl.h"

namespace EUS {

    // Helper function to create a label with common properties
    Label^ DashboardUserControl::CreateLabel(String^ text, System::Drawing::Font^ font, Color color, int width, int height, Point location)
    {
        Label^ label = gcnew Label();
        label->Text = text;
        label->Font = font;
        label->ForeColor = color;
        label->Size = System::Drawing::Size(width, height);
        label->Location = location;
        label->TextAlign = ContentAlignment::MiddleCenter;
        return label;
    }
    DashboardUserControl::DashboardUserControl(void)
    {
        InitializeComponent();
    }

    DashboardUserControl::~DashboardUserControl()
    {
        if (components)
        {
            delete components;
        }
    }

    void DashboardUserControl::InitializeComponent(void)
    {
        this->components = gcnew System::ComponentModel::Container();
        this->Size = System::Drawing::Size(1140, 900);
        this->BackColor = Color::FromArgb(212, 237, 250);

        int sectionMargin = 60;
        int sectionMargin2 = 5;
        int sectionSpacing = 50;
        int sectionSpacing2 = 13;

        System::Drawing::Font^ boldFont = gcnew System::Drawing::Font("Segoe UI", 16, FontStyle::Bold);
        System::Drawing::Font^ regularFont = gcnew System::Drawing::Font("Segoe UI", 12);

        // Top-left Section
        Panel^ topLeftPanel = gcnew Panel();
        topLeftPanel->Size = System::Drawing::Size(this->Width - sectionMargin, this->Height / 2 - sectionMargin);
        topLeftPanel->Location = Point(sectionMargin, sectionMargin);
        topLeftPanel->BackColor = Color::FromArgb(69, 160, 227);
        ApplyRoundedRectangleToPanel(topLeftPanel, 30, RoundedRectangles::RoundedRectangle::RectangleCorners::All);

        topLeftPanel->Controls->Add(CreateLabel("Top-left Section", boldFont, Color::White, topLeftPanel->Width, 30, Point(0, 0)));
        topLeftPanel->Controls->Add(CreateLabel("Content for top-left box.", regularFont, Color::White, topLeftPanel->Width, 50, Point(0, 40)));

        this->Controls->Add(topLeftPanel);

        // Bottom-left Section (Two Boxes)
        Panel^ bottomLeftPanel = gcnew Panel();
        bottomLeftPanel->Size = System::Drawing::Size(this->Width - sectionMargin, this->Height / 2 - sectionMargin + 110);
        bottomLeftPanel->Location = Point(sectionMargin, topLeftPanel->Bottom + sectionSpacing);
        bottomLeftPanel->BackColor = Color::FromArgb(212, 237, 250);
        ApplyRoundedRectangleToPanel(bottomLeftPanel, 30, RoundedRectangles::RoundedRectangle::RectangleCorners::All);

        int boxHeight = (bottomLeftPanel->Height - sectionSpacing - 100);

        Panel^ bottomLeftBox1 = gcnew Panel();
        bottomLeftBox1->Size = System::Drawing::Size(bottomLeftPanel->Width / 2 - sectionSpacing + 70, boxHeight - 110);
        bottomLeftBox1->BackColor = Color::FromArgb(69, 160, 227);
        ApplyRoundedRectangleToPanel(bottomLeftBox1, 30, RoundedRectangles::RoundedRectangle::RectangleCorners::All);

        bottomLeftBox1->Controls->Add(CreateLabel("Bottom-left Box 1", boldFont, Color::White, bottomLeftBox1->Width, 30, Point(0, 0)));
        bottomLeftBox1->Controls->Add(CreateLabel("Content for box 1.", regularFont, Color::White, bottomLeftBox1->Width, 50, Point(0, 40)));

        Panel^ bottomLeftBox2 = gcnew Panel();
        bottomLeftBox2->Size = System::Drawing::Size(bottomLeftPanel->Width / 2 - sectionSpacing + 75, boxHeight - 110);
        bottomLeftBox2->Location = Point(bottomLeftPanel->Width / 2 - 25, bottomLeftBox1->Bottom + 20);
        bottomLeftBox2->BackColor = Color::FromArgb(69, 160, 227);
        ApplyRoundedRectangleToPanel(bottomLeftBox2, 30, RoundedRectangles::RoundedRectangle::RectangleCorners::All);

        bottomLeftBox2->Controls->Add(CreateLabel("Bottom-left Box 2", boldFont, Color::White, bottomLeftBox2->Width, 30, Point(0, 0)));
        bottomLeftBox2->Controls->Add(CreateLabel("Content for box 2.", regularFont, Color::White, bottomLeftBox2->Width, 50, Point(0, 40)));

        bottomLeftPanel->Controls->Add(bottomLeftBox1);
        bottomLeftPanel->Controls->Add(bottomLeftBox2);
        this->Controls->Add(bottomLeftPanel);

        // Right-side Section (Two Large Boxes)
        Panel^ rightPanel = gcnew Panel();
        rightPanel->Size = System::Drawing::Size(this->Width - 520 - sectionMargin2, this->Height - sectionMargin + 100);
        rightPanel->Location = Point(topLeftPanel->Right + sectionSpacing, sectionMargin);
        rightPanel->BackColor = Color::FromArgb(212, 237, 250);
        ApplyRoundedRectangleToPanel(rightPanel, 30, RoundedRectangles::RoundedRectangle::RectangleCorners::All);

        Panel^ rightBox1 = gcnew Panel();
        rightBox1->Size = System::Drawing::Size(rightPanel->Width, rightPanel->Height / 2 - sectionSpacing + 40);
        rightBox1->BackColor = Color::FromArgb(69, 160, 227);
        ApplyRoundedRectangleToPanel(rightBox1, 30, RoundedRectangles::RoundedRectangle::RectangleCorners::All);

        rightBox1->Controls->Add(CreateLabel("Right-side Box 1", boldFont, Color::White, rightBox1->Width, 30, Point(0, 0)));
        rightBox1->Controls->Add(CreateLabel("Content for right-side box 1.", regularFont, Color::White, rightBox1->Width, 50, Point(0, 40)));

        Panel^ rightBox2 = gcnew Panel();
        rightBox2->Size = System::Drawing::Size(rightPanel->Width, rightPanel->Height / 2 - sectionSpacing + 45);
        rightBox2->Location = Point(0, rightBox1->Bottom + sectionSpacing2);
        rightBox2->BackColor = Color::FromArgb(69, 160, 227);
        ApplyRoundedRectangleToPanel(rightBox2, 30, RoundedRectangles::RoundedRectangle::RectangleCorners::All);

        rightBox2->Controls->Add(CreateLabel("Right-side Box 2", boldFont, Color::White, rightBox2->Width, 30, Point(0, 0)));
        rightBox2->Controls->Add(CreateLabel("Content for right-side box 2.", regularFont, Color::White, rightBox2->Width, 50, Point(0, 40)));

        rightPanel->Controls->Add(rightBox1);
        rightPanel->Controls->Add(rightBox2);
        this->Controls->Add(rightPanel);
    }

    void DashboardUserControl::ApplyRoundedRectangleToPanel(Panel^ panel, int radius, RoundedRectangles::RoundedRectangle::RectangleCorners corners)
    {
        System::Drawing::Drawing2D::GraphicsPath^ path = RoundedRectangles::RoundedRectangle::Create(
            0, 0, panel->Width, panel->Height, radius, corners
        );
        panel->Region = gcnew System::Drawing::Region(path);
    }
}

