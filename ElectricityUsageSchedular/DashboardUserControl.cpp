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
        this->Size = System::Drawing::Size(1130, 720);
        this->BackColor = Color::FromArgb(240, 255, 240);

        int sectionMargin = 10;
        int sectionSpacing = 20;
        int cornerRadius = 15;

        // Define font for labels
        System::Drawing::Font^ boldFont = gcnew System::Drawing::Font("Arial", 14, FontStyle::Bold);
        System::Drawing::Font^ regularFont = gcnew System::Drawing::Font("Arial", 12);

        // ---- Section 1 ----
        section1Panel = gcnew Panel();
        section1Panel->Size = System::Drawing::Size(this->Width - 2 * sectionMargin, 180);
        section1Panel->Location = Point(sectionMargin, sectionMargin);
        section1Panel->BackColor = Color::FromArgb(245, 250, 245);

        // Sub-panels for Section 1
        Panel^ subPanel1 = gcnew Panel();
        subPanel1->Size = System::Drawing::Size(300, 180);
        subPanel1->Location = Point(0, 0);
        subPanel1->BackColor = Color::FromArgb(40, 100, 50); // Darker green
        subPanel1->Controls->Add(CreateLabel("Summary of Usage", boldFont, Color::FromArgb(255, 215, 0), 300, 30, Point(0, 0)));
        subPanel1->Controls->Add(CreateLabel("Current Usage: 15 kWh", regularFont, Color::White, 300, 25, Point(0, 40)));

        Panel^ subPanel2 = gcnew Panel();
        subPanel2->Size = System::Drawing::Size(300, 180);
        subPanel2->Location = Point(310, 0);
        subPanel2->BackColor = Color::FromArgb(40, 100, 50);
        subPanel2->Controls->Add(CreateLabel("Total Cost: $3.50", regularFont, Color::White, 300, 25, Point(0, 0)));
        subPanel2->Controls->Add(CreateLabel("Peak Time: 6 PM - 9 PM", regularFont, Color::White, 300, 25, Point(0, 40)));

        Panel^ subPanel3 = gcnew Panel();
        subPanel3->Size = System::Drawing::Size(500, 180);
        subPanel3->Location = Point(620, 0);
        subPanel3->BackColor = Color::FromArgb(40, 100, 50);
        subPanel3->Controls->Add(CreateLabel("Placeholder Info (More data here)", regularFont, Color::White, 500, 25, Point(0, 0)));
        subPanel3->Controls->Add(CreateLabel("Additional Data Placeholder", regularFont, Color::White, 500, 25, Point(0, 40)));

        section1Panel->Controls->Add(subPanel1);
        section1Panel->Controls->Add(subPanel2);
        section1Panel->Controls->Add(subPanel3);
        this->Controls->Add(section1Panel);

        // ---- Section 2 ----
        section2Panel = gcnew Panel();
        section2Panel->Size = System::Drawing::Size(this->Width - 2 * sectionMargin, 250);
        section2Panel->Location = Point(sectionMargin, section1Panel->Bottom + sectionSpacing);
        section2Panel->BackColor = Color::WhiteSmoke;

        // Sub-panels for Section 2
        Panel^ subPanel4 = gcnew Panel();
        subPanel4->Size = System::Drawing::Size(550, 250);
        subPanel4->Location = Point(0, 0);
        subPanel4->BackColor = Color::FromArgb(34, 49, 36);
        subPanel4->Controls->Add(CreateLabel("Recent Activity Timeline", boldFont, Color::FromArgb(255, 215, 0), 300, 30, Point(0, 0)));
        subPanel4->Controls->Add(CreateLabel("Timeline Placeholder", regularFont, Color::White, 300, 25, Point(0, 40)));

        Panel^ subPanel5 = gcnew Panel();
        subPanel5->Size = System::Drawing::Size(550, 250);
        subPanel5->Location = Point(560, 0);
        subPanel5->BackColor = Color::FromArgb(34, 49, 36);
        subPanel5->Controls->Add(CreateLabel("Energy Consumption Graph (Placeholder)", regularFont, Color::White, 500, 25, Point(0, 0)));

        section2Panel->Controls->Add(subPanel4);
        section2Panel->Controls->Add(subPanel5);
        this->Controls->Add(section2Panel);

        // ---- Section 3 ----
        section3Panel = gcnew Panel();
        section3Panel->Size = System::Drawing::Size(this->Width - 2 * sectionMargin, 180);
        section3Panel->Location = Point(sectionMargin, section2Panel->Bottom + sectionSpacing);
        section3Panel->BackColor = Color::WhiteSmoke;

        // Sub-panel for Section 3
        Panel^ subPanel6 = gcnew Panel();
        subPanel6->Size = System::Drawing::Size(1120, 180);
        subPanel6->Location = Point(0, 0);
        subPanel6->BackColor = Color::FromArgb(47, 68, 53);
        subPanel6->Controls->Add(CreateLabel("Energy Saving Tips", boldFont, Color::FromArgb(255, 215, 0), 1120, 30, Point(0, 0)));
        subPanel6->Controls->Add(CreateLabel("Turn off unused devices when not in use.", regularFont, Color::White, 1120, 25, Point(0, 40)));

        section3Panel->Controls->Add(subPanel6);
        this->Controls->Add(section3Panel);
    }
}

