#include "pch.h"
#include "SchedulerUserControl.h"
#include <iostream>
#include "globals2.h"





namespace EUS {

    SchedulerUserControl::SchedulerUserControl(void)
    {
        selectedweek = 0;
        GlobalObjects::Globals::Gtable->Location = System::Drawing::Point(00, 310);
        GlobalObjects::Globals::Gtable->Size = System::Drawing::Size(1450, 500);
        
        this->Controls->Add(GlobalObjects::Globals::Gtable);
        InitializeComponent();
        //retrive_appliance_names();
       // get_appliances();

        for (int i = 0; i < GlobalObjectsRaza::Globals::unmanagedGlobals->apl.size(); i++) {
            int p = (i % 2) + 1;
            if (i == 7)
                p = 3;
            GlobalObjectsRaza::Globals::unmanagedGlobals->apl[i].priority = p;
        }
        vector<schedule_appliance::Appliance> arr = sortit(GlobalObjectsRaza::Globals::unmanagedGlobals->apl, 0);

        float dailyBill = 0.0f;
        const float monthlyThreshold = 60000.0f;

        const float dailyThreshold = monthlyThreshold / 30.0f; // Calculate daily threshold
        //initializeTable();
        //makeTable(GlobalObjectsRaza::Globals::unmanagedGlobals->bill, dailyThreshold, arr);
        //GlobalObjectsRaza::Globals::unmanagedGlobals->bill = dailyBill;
        sqlite3_close(GlobalObjectsRaza::Globals::unmanagedGlobals->dbr);
        updateBillLabel(GlobalObjectsRaza::Globals::unmanagedGlobals->bill * 30);
    }

    void SchedulerUserControl::setGlobalTable()
    {
       // GlobalObjects::Globals::Gtable = table;
    }


    void SchedulerUserControl::updateBillLabel(float finalBill) {
        lable->Text = "Final Monthly Bill: " + System::Convert::ToString(finalBill);
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
        this->BackColor = Color::FromArgb(234, 237, 244); // Light greenish-white for easy readability

        Label^ label = gcnew Label();
        label->Text = L"Weekly Schedule";
        label->Font = gcnew System::Drawing::Font("Arial", 18, FontStyle::Bold);
        label->ForeColor = Color::FromArgb(67, 24, 255); // Gold color for highlights
        label->Dock = DockStyle::Top;
        label->TextAlign = ContentAlignment::MiddleCenter;
        this->Controls->Add(label);

        lable = gcnew Label();
        lable->Text = L"Bill";
        lable->Font = gcnew System::Drawing::Font("Arial", 18, FontStyle::Bold);
        lable->ForeColor = Color::FromArgb(106, 210, 255); // Gold color for highlights
        lable->Dock = DockStyle::Top;
        lable->TextAlign = ContentAlignment::MiddleCenter;
        this->Controls->Add(lable);

        comboBox = gcnew ComboBox();
        comboBox->Location = System::Drawing::Point(50, 100); // Set position
        comboBox->Size = System::Drawing::Size(150, 30);    // Set size

        comboBoxWeek = gcnew ComboBox();
        comboBoxWeek->Location = System::Drawing::Point(50, 150); // Set position
        comboBoxWeek->Size = System::Drawing::Size(150, 30);

        Label^ l = gcnew Label();
        l = gcnew Label();
        l->Text = L"Day of the week";
        l->Font = gcnew System::Drawing::Font("Arial", 15, FontStyle::Bold);
        l->ForeColor = Color::FromArgb(123, 130, 165); // Gold color for highlights
        l->Location = System::Drawing::Point(47, 60); // Set position
        l->AutoSize = true;
        this->Controls->Add(l);

        // Add items to the ComboBox
        comboBox->Items->Add("1");
        comboBox->Items->Add("2");
        comboBox->Items->Add("3");
        comboBox->Items->Add("4");
        comboBox->Items->Add("5");
        comboBox->Items->Add("6");
        comboBox->Items->Add("7");
        //comboBox->Items->Add("Option 3");

        comboBoxWeek->Items->Add("1");
        comboBoxWeek->Items->Add("2");
        comboBoxWeek->Items->Add("3");
        comboBoxWeek->Items->Add("4");

        // Set default selected item
        comboBox->SelectedIndex = 0;
        comboBoxWeek->SelectedIndex = 0;

        // Add an event handler for selected item changes
        comboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &EUS::SchedulerUserControl::OnColumnDropdownChanged);
        comboBoxWeek->SelectedIndexChanged += gcnew System::EventHandler(this, &EUS::SchedulerUserControl::OnWeekDropdownChanged);


        // Add the ComboBox to the form
        this->Controls->Add(comboBox);
        this->Controls->Add(comboBoxWeek);
        GlobalObjects::Globals::Gtable->Location = System::Drawing::Point(00, 310);
        GlobalObjects::Globals::Gtable->Size = System::Drawing::Size(1450, 500);
        RandomizeTable(GlobalObjects::Globals::Gtable);
        this->Controls->Add(GlobalObjects::Globals::Gtable);
        OnColumnDropdownChanged(comboBox, EventArgs::Empty);
        
    }

    

    void SchedulerUserControl::OnColumnDropdownChanged(System::Object^ sender, System::EventArgs^ e) {
        // Define positions and sizes for components
        System::Drawing::Point tablePosition = System::Drawing::Point(0, 310);
        System::Drawing::Size tableSize = System::Drawing::Size(1450, 500);

        // Retrieve the selected value
        System::String^ selectedValue = comboBox->SelectedItem->ToString();

        // Remove only the current table, keep other controls intact
        for (int i = 0; i < this->Controls->Count; i++) {
            if (this->Controls[i]->GetType() == DataGridView::typeid) {
                this->Controls->RemoveAt(i);
                break;
            }
        }

        // Determine which table to show and add it to the Controls
        DataGridView^ selectedTable = nullptr;

        if (selectedValue == "1") selectedTable = GlobalObjects::Globals::monthlyTables[selectedweek]->Gtable1;
        else if (selectedValue == "2") selectedTable = GlobalObjects::Globals::monthlyTables[selectedweek]->Gtable2;
        else if (selectedValue == "3") selectedTable = GlobalObjects::Globals::monthlyTables[selectedweek]->Gtable3;
        else if (selectedValue == "4") selectedTable = GlobalObjects::Globals::monthlyTables[selectedweek]->Gtable4;
        else if (selectedValue == "5") selectedTable = GlobalObjects::Globals::monthlyTables[selectedweek]->Gtable5;
        else if (selectedValue == "6") selectedTable = GlobalObjects::Globals::monthlyTables[selectedweek]->Gtable6;
        else if (selectedValue == "7") selectedTable = GlobalObjects::Globals::monthlyTables[selectedweek]->GTable7;

        if (selectedTable != nullptr) {
            // Set table position and size
            selectedTable->Location = tablePosition;
            selectedTable->Size = tableSize;

            // Add table to controls
            this->Controls->Add(selectedTable);
        }

        // Ensure layout is refreshed
        this->Refresh();
    }

    void SchedulerUserControl::OnWeekDropdownChanged(System::Object^ sender, System::EventArgs^ e) {
        if (comboBoxWeek->SelectedIndex != -1) { // Ensure an item is selected
            // Set the global variable based on the selected index
            selectedweek = comboBoxWeek->SelectedIndex;

            // Update the comboBox value to "1"
            comboBox->SelectedIndex = 0; // 0 corresponds to "1" in the comboBox

            // Manually trigger the OnColumnDropdownChanged handler to refresh the table
            OnColumnDropdownChanged(comboBox, EventArgs::Empty);
        }
    }




};

