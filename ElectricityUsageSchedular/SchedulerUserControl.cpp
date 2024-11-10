#include "pch.h"
#include "SchedulerUserControl.h"
#include <iostream>


namespace EUS {

    SchedulerUserControl::SchedulerUserControl(void)
    {
        InitializeComponent();
        initializeTable();
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
    }

    void SchedulerUserControl::initializeTable() {
        DataGridView^ table = gcnew DataGridView();
        table->Location = System::Drawing::Point(00, 310);
        table->Size = System::Drawing::Size(1450, 200);
        
        table->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
        table->ColumnHeadersVisible = true;
        table->RowHeadersVisible = false;
        table->AllowUserToAddRows = false;

        std::string arr[24] = {
    "0000-0100", "0100-0200", "0200-0300", "0300-0400", "0400-0500",
    "0500-0600", "0600-0700", "0700-0800", "0800-0900", "0900-1000",
    "1000-1100", "1100-1200", "1200-1300", "1300-1400", "1400-1500",
    "1500-1600", "1600-1700", "1700-1800", "1800-1900", "1900-2000",
    "2000-2100", "2100-2200", "2200-2300", "2300-2400"
        };


        for (int i = 0; i < 24; i++) {
            table->Columns->Add(gcnew System::String(arr[i].c_str()), gcnew System::String(arr[i].c_str()));
        }


        // Add rows(num of items = num of rows)
       
        // Add the DataGridView to the form
        this->Controls->Add(table);
    }
};

