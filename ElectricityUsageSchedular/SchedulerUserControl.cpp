#include "pch.h"
#include "SchedulerUserControl.h"
#include <iostream>


namespace EUS {

    SchedulerUserControl::SchedulerUserControl(void)
    {
        InitializeComponent();
        initializeTable();
        vector<schedule_appliance::Appliance> arrr;
        for (int i = 0; i <= 15; ++i) {
            string name = "name" + to_string(i);
            float kwh = 0.8f;
            int priority = (i % 2) + 1;
            if (i == 14) priority = 3;

            // Create and push the appliance object into the vector
            arrr.push_back(schedule_appliance::Appliance(name, kwh, priority));
        }
        vector<schedule_appliance::Appliance> arr = sortit(arrr, 0);

        float dailyBill = 0.0f;
        const float monthlyThreshold = 60000.0f;

        const float dailyThreshold = monthlyThreshold / 30.0f; // Calculate daily threshold

        makeTable(arr, 0, dailyBill, dailyThreshold);
        updateBillLabel(dailyBill * 30.0f);
        //make the table accesible globally
        setGlobalTable();
    }

    void SchedulerUserControl::setGlobalTable()
    {
        GlobalObjects::Globals::Gtable = table;
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
        
    }

    void SchedulerUserControl::initializeTable() {
        table = gcnew DataGridView();
        table->Location = System::Drawing::Point(00, 310);
        table->Size = System::Drawing::Size(1450, 500);

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

        vector<schedule_appliance::Appliance> arrr;
        for (int i = 1; i <= 15; ++i) {
            string name = "name" + to_string(i);
            float kwh = 1.8f;
            int priority = (i % 3) + 1;  // Cycle through 1, 2, 3 for priority

            // Create and push the appliance object into the vector
            arrr.push_back(schedule_appliance::Appliance(name, kwh, priority));
        }
        sortit(arrr, 0);


        table->Columns->Add("Name", "Name");
        for (int i = 0; i < 23; i++) {
            table->Columns->Add(gcnew System::String(arr[i].c_str()), gcnew System::String(arr[i].c_str()));
        }


        // Add rows(num of items = num of rows)
       
        table->Rows->Add(15);
        
        
        for (int i = 0; i < table->Rows->Count; i++) {
            table->Rows[i]->Cells[0]->Value = gcnew System::String(arrr[i].name.c_str());
        }
        
        // Add the DataGridView to the form
        this->Controls->Add(table);
    }
    

    void SchedulerUserControl::traverseSlots(int& mover, int rowIndex) {
        // Ensure rowIndex and mover are within valid bounds before accessing table
        if (rowIndex - 1 < 0 || rowIndex - 1 >= table->Rows->Count || mover >= 23 || mover < 0) {
            return;
        }

        // Check if the current cell is within bounds and is empty
        if (table->Rows[rowIndex - 1]->Cells->Count > mover && table->Rows[rowIndex - 1]->Cells[mover] &&
            table->Rows[rowIndex - 1]->Cells[mover]->Value == nullptr) {
            // Stop here as we found an empty cell
            return;
        }

        // Move to the next cell and continue searching
        ++mover;
        traverseSlots(mover, rowIndex);
    }


    void SchedulerUserControl::makeTable(vector<schedule_appliance::Appliance> arr, int rowIndex, float& currentBill, float targetBill) {
        // Initial pass to assign slots to each appliance based on priority
        for (int i = 0; i < arr.size(); ++i) {
            if (currentBill >= targetBill) {
                return;
            }

            if (arr[i].priority == 3) {
                // Priority 3: Assign all available slots (1 per hour)
                for (int j = 1; j < 24; ++j) {
                    if (i < table->Rows->Count && j < table->Rows[i]->Cells->Count) {
                        table->Rows[i]->Cells[j]->Value = "+";
                        currentBill += arr[i].kwh * 41.6;
                        if (currentBill >= targetBill) {
                            return;
                        }
                    }
                }
            }
            else if (arr[i].priority == 2) {
                // Priority 2: Assign 2 slots with a 1-cell gap between them
                int col = 1;
                traverseSlots(col, i);
                if (i < table->Rows->Count && col < table->Rows[i]->Cells->Count) {
                    table->Rows[i]->Cells[col]->Value = "+";
                    if (col + 2 < table->Rows[i]->Cells->Count) {
                        table->Rows[i]->Cells[col + 2]->Value = "+";
                    }
                    currentBill += arr[i].kwh * 41.6;
                }
            }
            else if (arr[i].priority == 1) {
                // Priority 1: Assign only 1 slot
                int col = 1;
                traverseSlots(col, i);
                if (i < table->Rows->Count && col < table->Rows[i]->Cells->Count) {
                    table->Rows[i]->Cells[col]->Value = "+";
                    currentBill += arr[i].kwh * 41.6;
                }
            }
        }

        // Secondary pass to revisit priority 2 and 1 appliances and assign additional slots
        bool slotsAssigned = false; // Track if any slots were assigned during this pass
        for (int i = 0; i < arr.size(); ++i) {
            if (currentBill >= targetBill) {
                return;
            }

            if (arr[i].priority == 2) {
                int col = 1;
                while (currentBill < targetBill) {
                    traverseSlots(col, i);
                    if (i < table->Rows->Count && col < table->Rows[i]->Cells->Count) {
                        table->Rows[i]->Cells[col]->Value = "+";
                        if (col + 2 < table->Rows[i]->Cells->Count) {
                            table->Rows[i]->Cells[col + 2]->Value = "+";
                        }
                        currentBill += arr[i].kwh * 41.6;
                        slotsAssigned = true;
                    }
                    col += 4;
                    if (col >= 24) break;
                }
            }
            else if (arr[i].priority == 1) {
                int col = 1;
                while (currentBill < targetBill) {
                    traverseSlots(col, i);
                    if (i < table->Rows->Count && col < table->Rows[i]->Cells->Count) {
                        table->Rows[i]->Cells[col]->Value = "+";
                        currentBill += arr[i].kwh * 41.6;
                        slotsAssigned = true;
                    }
                    col += 2;
                    if (col >= 24) break;
                }
            }
        }

        // If we assigned any slots during this pass and haven't reached the target bill, make another call
        if (slotsAssigned && currentBill < targetBill) {
            makeTable(arr, rowIndex, currentBill, targetBill);
        }
    }

    void SchedulerUserControl::OnColumnDropdownChanged(System::Object^ sender, System::EventArgs^ e) {
        if (comboBox->SelectedIndex == 0) {
            for (int i = 1; i < 12; i++) {
                table->Columns[i]->Visible = true;
            }
            for (int i = 12; i < 24; i++) {
                table->Columns[i]->Visible = false;
            }
        }
        else if (comboBox->SelectedIndex == 1) {
            for (int i = 12; i < 24; i++) {
                table->Columns[i]->Visible = true;
            }
            for (int i = 1; i < 12; i++) {
                table->Columns[i]->Visible = false;
            }
        }
    }

};

