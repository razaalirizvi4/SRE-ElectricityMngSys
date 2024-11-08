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
        this->BackColor = Color::FromArgb(235, 245, 235);

        int sectionMargin = 15;
        int sectionSpacing = 25;

        System::Drawing::Font^ boldFont = gcnew System::Drawing::Font("Segoe UI", 16, FontStyle::Bold);
        System::Drawing::Font^ regularFont = gcnew System::Drawing::Font("Segoe UI", 12);

        // ---- Section 1: Usage Overview ----
        section1Panel = gcnew Panel();
        section1Panel->Size = System::Drawing::Size(this->Width - 2 * sectionMargin, 180);
        section1Panel->Location = Point(sectionMargin, sectionMargin);
        section1Panel->BackColor = Color::FromArgb(245, 250, 245);

        FlowLayoutPanel^ section1Flow = gcnew FlowLayoutPanel();
        section1Flow->FlowDirection = FlowDirection::LeftToRight;
        section1Flow->Size = section1Panel->Size;
        section1Flow->Padding.All = 20;
        section1Flow->AutoSize = true;

        // Sub-panels for Section 1
        Panel^ subPanel1 = gcnew Panel();
        subPanel1->Size = System::Drawing::Size(300, 180);
        subPanel1->BackColor = Color::FromArgb(40, 100, 50);
        subPanel1->Controls->Add(CreateLabel("Summary of Usage", boldFont, Color::FromArgb(255, 215, 0), 300, 30, Point(0, 0)));
        subPanel1->Controls->Add(CreateLabel("Current Usage: 15 kWh", regularFont, Color::White, 300, 25, Point(0, 40)));
        subPanel1->Controls->Add(CreateLabel("Usage Forecast: 20 kWh", regularFont, Color::White, 300, 25, Point(0, 70)));

        Panel^ subPanel2 = gcnew Panel();
        subPanel2->Size = System::Drawing::Size(300, 180);
        subPanel2->BackColor = Color::FromArgb(40, 100, 50);
        subPanel2->Controls->Add(CreateLabel("City Rates", boldFont, Color::FromArgb(255, 215, 0), 300, 30, Point(0, 0)));
        subPanel2->Controls->Add(CreateLabel("Total Cost: $3.50", regularFont, Color::White, 300, 25, Point(0, 40)));
        subPanel2->Controls->Add(CreateLabel("Peak Time: 6 PM - 9 PM", regularFont, Color::White, 300, 25, Point(0, 70)));
        subPanel2->Controls->Add(CreateLabel("Off-Peak Rate: $0.10/kWh", regularFont, Color::White, 300, 25, Point(0, 100)));

        Panel^ subPanel3 = gcnew Panel();
        subPanel3->Size = System::Drawing::Size(500, 180);
        subPanel3->BackColor = Color::FromArgb(40, 100, 50);
        subPanel3->Controls->Add(CreateLabel("Additional Data Placeholder", boldFont, Color::FromArgb(255, 215, 0), 500, 30, Point(0, 0)));
        subPanel3->Controls->Add(CreateLabel("Total Usage Last Week: 100 kWh", regularFont, Color::White, 500, 25, Point(0, 40)));
        subPanel3->Controls->Add(CreateLabel("Average Daily Usage: 15 kWh", regularFont, Color::White, 500, 25, Point(0, 70)));

        section1Flow->Controls->Add(subPanel1);
        section1Flow->Controls->Add(subPanel2);
        section1Flow->Controls->Add(subPanel3);
        section1Panel->Controls->Add(section1Flow);
        this->Controls->Add(section1Panel);

        // ---- Section 2: Activity and Trends (empty space) ----
        section2Panel = gcnew Panel();
        section2Panel->Size = System::Drawing::Size(this->Width - 2 * sectionMargin, 300);  // Smaller size for empty space
        section2Panel->Location = Point(sectionMargin, section1Panel->Bottom + sectionSpacing);
        section2Panel->BackColor = Color::White; // This will remain empty as requested
        this->Controls->Add(section2Panel);

        // ---- Section 3: Energy Saving Tips and Timeline ----
        section3Panel = gcnew Panel();
        section3Panel->Size = System::Drawing::Size(this->Width - 2 * sectionMargin + 100, 130);  // Adjusted size
        section3Panel->Location = Point(sectionMargin, section2Panel->Bottom + sectionSpacing);
        section3Panel->BackColor = Color::WhiteSmoke;

        FlowLayoutPanel^ section3Flow = gcnew FlowLayoutPanel();
        section3Flow->FlowDirection = FlowDirection::LeftToRight;
        section3Flow->Size = section3Panel->Size;
        section3Flow->Padding.All = 10;

        // Sub-panels for Section 3
        Panel^ subPanel6 = gcnew Panel();
        subPanel6->Size = System::Drawing::Size(550, 130);
        subPanel6->BackColor = Color::FromArgb(47, 68, 53);
        subPanel6->Controls->Add(CreateLabel("Energy Saving Tips", boldFont, Color::FromArgb(255, 215, 0), 550, 30, Point(0, 0)));
        subPanel6->Controls->Add(CreateLabel("Turn off unused devices when not in use.", regularFont, Color::White, 550, 25, Point(0, 40)));
        subPanel6->Controls->Add(CreateLabel("Install energy-efficient appliances.", regularFont, Color::White, 550, 25, Point(0, 70)));

        Panel^ subPanel4 = gcnew Panel();
        subPanel4->Size = System::Drawing::Size(550, 130);
        subPanel4->BackColor = Color::FromArgb(34, 49, 36);
        subPanel4->Controls->Add(CreateLabel("Recent Activity Timeline", boldFont, Color::FromArgb(255, 215, 0), 500, 30, Point(0, 0)));
        subPanel4->Controls->Add(CreateLabel("Today: Usage increased by 5 kWh", regularFont, Color::White, 550, 25, Point(0, 40)));
        subPanel4->Controls->Add(CreateLabel("Yesterday: Peak time observed at 7 PM", regularFont, Color::White, 550, 25, Point(0, 70)));

        section3Flow->Controls->Add(subPanel4);  // Timeline on the left
        section3Flow->Controls->Add(subPanel6);  // Energy Saving Tips on the right
        section3Panel->Controls->Add(section3Flow);
        this->Controls->Add(section3Panel);
    }
}

