#include "pch.h"
#include "DashboardUserControl.h"

namespace EUS {

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
        this->BackColor = Color::FromArgb(235, 245, 235);

        int sectionMargin = 10;
        int sectionSpacing = 20;

        // ---- Section 1 (Top Section with 3 panels) ----
        section1Panel = gcnew Panel();
        section1Panel->Size = System::Drawing::Size(this->Width - 2 * sectionMargin, 180);
        section1Panel->Location = Point(sectionMargin, sectionMargin);
        section1Panel->BackColor = Color::WhiteSmoke;

        // Sub-panel 1 of Section 1: Title & Usage Info
        Panel^ subPanel1 = gcnew Panel();
        subPanel1->Size = System::Drawing::Size(300, 180);
        subPanel1->Location = Point(0, 0);
        subPanel1->BackColor = Color::FromArgb(47, 68, 53);
        Label^ lblSummary = gcnew Label();
        lblSummary->Text = L"Summary of Usage";
        lblSummary->Font = gcnew System::Drawing::Font("Arial", 14, FontStyle::Bold);
        lblSummary->ForeColor = Color::FromArgb(255, 215, 0);
        lblSummary->Location = Point(0, 0);
        lblSummary->Size = System::Drawing::Size(300, 30);
        lblSummary->TextAlign = ContentAlignment::MiddleCenter;
        subPanel1->Controls->Add(lblSummary);

        Label^ lblUsage = gcnew Label();
        lblUsage->Text = L"Current Usage: 15 kWh";
        lblUsage->Font = gcnew System::Drawing::Font("Arial", 12);
        lblUsage->ForeColor = Color::FromArgb(255, 255, 255);
        lblUsage->Location = Point(0, 40);
        lblUsage->Size = System::Drawing::Size(300, 25);
        lblUsage->TextAlign = ContentAlignment::MiddleCenter;
        subPanel1->Controls->Add(lblUsage);

        section1Panel->Controls->Add(subPanel1);

        // Sub-panel 2 of Section 1: Cost & Time Info
        Panel^ subPanel2 = gcnew Panel();
        subPanel2->Size = System::Drawing::Size(300, 180);
        subPanel2->Location = Point(310, 0);
        subPanel2->BackColor = Color::FromArgb(47, 68, 53);
        Label^ lblCost = gcnew Label();
        lblCost->Text = L"Total Cost: $3.50";
        lblCost->Font = gcnew System::Drawing::Font("Arial", 12);
        lblCost->ForeColor = Color::FromArgb(255, 255, 255);
        lblCost->Location = Point(0, 0);
        lblCost->Size = System::Drawing::Size(300, 25);
        lblCost->TextAlign = ContentAlignment::MiddleCenter;
        subPanel2->Controls->Add(lblCost);

        Label^ lblTime = gcnew Label();
        lblTime->Text = L"Peak Time: 6 PM - 9 PM";
        lblTime->Font = gcnew System::Drawing::Font("Arial", 12);
        lblTime->ForeColor = Color::FromArgb(255, 255, 255);
        lblTime->Location = Point(0, 40);
        lblTime->Size = System::Drawing::Size(300, 25);
        lblTime->TextAlign = ContentAlignment::MiddleCenter;
        subPanel2->Controls->Add(lblTime);

        section1Panel->Controls->Add(subPanel2);

        // Sub-panel 3 of Section 1: Placeholder Info
        Panel^ subPanel3 = gcnew Panel();
        subPanel3->Size = System::Drawing::Size(500, 180);
        subPanel3->Location = Point(620, 0);
        subPanel3->BackColor = Color::FromArgb(47, 68, 53);
        Label^ lblPlaceholder = gcnew Label();
        lblPlaceholder->Text = L"Placeholder Info (More data here)";
        lblPlaceholder->Font = gcnew System::Drawing::Font("Arial", 12);
        lblPlaceholder->ForeColor = Color::FromArgb(255, 255, 255);
        lblPlaceholder->Location = Point(0, 0);
        lblPlaceholder->Size = System::Drawing::Size(500, 25);
        lblPlaceholder->TextAlign = ContentAlignment::MiddleCenter;
        subPanel3->Controls->Add(lblPlaceholder);

        Label^ lblAdditionalInfo = gcnew Label();
        lblAdditionalInfo->Text = L"Additional Data Placeholder";
        lblAdditionalInfo->Font = gcnew System::Drawing::Font("Arial", 12);
        lblAdditionalInfo->ForeColor = Color::FromArgb(255, 255, 255);
        lblAdditionalInfo->Location = Point(0, 40);
        lblAdditionalInfo->Size = System::Drawing::Size(500, 25);
        lblAdditionalInfo->TextAlign = ContentAlignment::MiddleCenter;
        subPanel3->Controls->Add(lblAdditionalInfo);

        section1Panel->Controls->Add(subPanel3);

        this->Controls->Add(section1Panel);

        // ---- Section 2 (Middle Section with 2 panels) ----
        section2Panel = gcnew Panel();
        section2Panel->Size = System::Drawing::Size(this->Width - 2 * sectionMargin, 250);
        section2Panel->Location = Point(sectionMargin, section1Panel->Bottom + sectionSpacing);
        section2Panel->BackColor = Color::WhiteSmoke;

        // Sub-panel 1 of Section 2
        Panel^ subPanel4 = gcnew Panel();
        subPanel4->Size = System::Drawing::Size(550, 250);
        subPanel4->Location = Point(0, 0);
        subPanel4->BackColor = Color::FromArgb(34, 49, 36);
        Label^ lblRecentActivity = gcnew Label();
        lblRecentActivity->Text = L"Recent Activity Timeline";
        lblRecentActivity->Font = gcnew System::Drawing::Font("Arial", 14, FontStyle::Bold);
        lblRecentActivity->ForeColor = Color::FromArgb(255, 215, 0);
        lblRecentActivity->Location = Point(0, 0);
        lblRecentActivity->Size = System::Drawing::Size(300, 30);
        lblRecentActivity->TextAlign = ContentAlignment::MiddleCenter;
        subPanel4->Controls->Add(lblRecentActivity);

        Label^ lblTimeline = gcnew Label();
        lblTimeline->Text = L"Timeline Placeholder";
        lblTimeline->Font = gcnew System::Drawing::Font("Arial", 12);
        lblTimeline->ForeColor = Color::FromArgb(255, 255, 255);
        lblTimeline->Location = Point(0, 40);
        lblTimeline->Size = System::Drawing::Size(300, 25);
        lblTimeline->TextAlign = ContentAlignment::MiddleCenter;
        subPanel4->Controls->Add(lblTimeline);

        section2Panel->Controls->Add(subPanel4);

        // Sub-panel 2 of Section 2: Energy Consumption Graph
        Panel^ subPanel5 = gcnew Panel();
        subPanel5->Size = System::Drawing::Size(550, 250);
        subPanel5->Location = Point(560, 0);
        subPanel5->BackColor = Color::FromArgb(34, 49, 36);
        Label^ lblEnergyGraph = gcnew Label();
        lblEnergyGraph->Text = L"Energy Consumption Graph (Placeholder)";
        lblEnergyGraph->Font = gcnew System::Drawing::Font("Arial", 12);
        lblEnergyGraph->ForeColor = Color::FromArgb(255, 255, 255);
        lblEnergyGraph->Location = Point(0, 0);
        lblEnergyGraph->Size = System::Drawing::Size(500, 25);
        lblEnergyGraph->TextAlign = ContentAlignment::MiddleCenter;
        subPanel5->Controls->Add(lblEnergyGraph);

        section2Panel->Controls->Add(subPanel5);

        this->Controls->Add(section2Panel);

        // ---- Section 3 (Bottom Section with 2 panels) ----
        section3Panel = gcnew Panel();
        section3Panel->Size = System::Drawing::Size(this->Width - 2 * sectionMargin, 180);
        section3Panel->Location = Point(sectionMargin, section2Panel->Bottom + sectionSpacing);
        section3Panel->BackColor = Color::WhiteSmoke;

        // Sub-panel 1 of Section 3: Energy Saving Tips
        Panel^ subPanel6 = gcnew Panel();
        subPanel6->Size = System::Drawing::Size(1120, 180);
        subPanel6->Location = Point(0, 0);
        subPanel6->BackColor = Color::FromArgb(47, 68, 53);
        Label^ lblEnergySavingTips = gcnew Label();
        lblEnergySavingTips->Text = L"Energy Saving Tips";
        lblEnergySavingTips->Font = gcnew System::Drawing::Font("Arial", 14, FontStyle::Bold);
        lblEnergySavingTips->ForeColor = Color::FromArgb(255, 215, 0);
        lblEnergySavingTips->Location = Point(0, 0);
        lblEnergySavingTips->Size = System::Drawing::Size(1120, 30);
        lblEnergySavingTips->TextAlign = ContentAlignment::MiddleCenter;
        subPanel6->Controls->Add(lblEnergySavingTips);

        Label^ lblTips = gcnew Label();
        lblTips->Text = L"Turn off unused devices when not in use.";
        lblTips->Font = gcnew System::Drawing::Font("Arial", 12);
        lblTips->ForeColor = Color::FromArgb(255, 255, 255);
        lblTips->Location = Point(0, 40);
        lblTips->Size = System::Drawing::Size(1120, 25);
        lblTips->TextAlign = ContentAlignment::MiddleCenter;
        subPanel6->Controls->Add(lblTips);

        section3Panel->Controls->Add(subPanel6);

        this->Controls->Add(section3Panel);
    }
}

