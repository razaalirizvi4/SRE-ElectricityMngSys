#include "pch.h"
#include "SchedulerUserControl.h"
#include <iostream>


namespace EUS {

    SchedulerUserControl::SchedulerUserControl(void)
    {
        GlobalObjects::Globals::Gtable->Location = System::Drawing::Point(00, 310);
        GlobalObjects::Globals::Gtable->Size = System::Drawing::Size(1450, 500);
        this->Controls->Add(GlobalObjects::Globals::Gtable);
        InitializeComponent();
        //updateBillLabel(dailyBill * 30.0f);
        //make the table accesible globally
       // setGlobalTable();
    }

    void SchedulerUserControl::setGlobalTable()
    {
       // GlobalObjects::Globals::Gtable = table;
    }


    void SchedulerUserControl::updateBillLabel(float finalBill) {
        lable->Text = "Final Bill: " + System::Convert::ToString(finalBill);
    }

    SchedulerUserControl::~SchedulerUserControl()
    {
        if (components)
        {
            delete components;
        }
    }

    void SchedulerUserControl::InitializeComponent(void)
    {
        this->components = gcnew System::ComponentModel::Container();
        this->Size = System::Drawing::Size(600, 400);
        this->BackColor = Color::FromArgb(235, 245, 235); // Light greenish-white for easy readability

        Label^ label = gcnew Label();
        label->Text = L"Scheduler Page";
        label->Font = gcnew System::Drawing::Font("Arial", 18, FontStyle::Bold);
        label->ForeColor = Color::FromArgb(218, 165, 32); // Gold color for highlights
        label->Dock = DockStyle::Top;
        label->TextAlign = ContentAlignment::MiddleCenter;
        this->Controls->Add(label);

        lable = gcnew Label();
        lable->Text = L"Bill";
        lable->Font = gcnew System::Drawing::Font("Arial", 18, FontStyle::Bold);
        lable->ForeColor = Color::FromArgb(218, 165, 32); // Gold color for highlights
        lable->Dock = DockStyle::Top;
        lable->TextAlign = ContentAlignment::MiddleCenter;
        this->Controls->Add(lable);

        comboBox = gcnew ComboBox();
        comboBox->Location = System::Drawing::Point(50, 50); // Set position
        comboBox->Size = System::Drawing::Size(150, 30);    // Set size

        // Add items to the ComboBox
        comboBox->Items->Add("Day");
        comboBox->Items->Add("Night");
        //comboBox->Items->Add("Option 3");

        // Set default selected item
        comboBox->SelectedIndex = 0;

        // Add an event handler for selected item changes
        comboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &EUS::SchedulerUserControl::OnColumnDropdownChanged);


        // Add the ComboBox to the form
        this->Controls->Add(comboBox);
        GlobalObjects::Globals::Gtable->Location = System::Drawing::Point(00, 310);
        GlobalObjects::Globals::Gtable->Size = System::Drawing::Size(1450, 500);
        this->Controls->Add(GlobalObjects::Globals::Gtable);
        
    }

    

    void SchedulerUserControl::OnColumnDropdownChanged(System::Object^ sender, System::EventArgs^ e) {
        
    }

};

