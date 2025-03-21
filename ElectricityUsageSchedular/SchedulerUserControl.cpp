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
        InitializeComponent();
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
        label->Location = Point(610, 20);
        label->Height = 1;
        label->AutoSize = true;
        this->Controls->Add(label);

        lable = gcnew Label();
        lable->Text = L"Bill";
        lable->Font = gcnew System::Drawing::Font("Arial", 18, FontStyle::Bold);
        lable->ForeColor = Color::FromArgb(106, 210, 255); // Gold color for highlights
        lable->Location = Point(550, 50);
        lable->Height = 1;
        lable->AutoSize = true;
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
        l->ForeColor = Color::FromArgb(106, 210, 255); // Gold color for highlights
        l->Location = System::Drawing::Point(47, 60); // Set position
        l->AutoSize = true;
        this->Controls->Add(l);

        // Add items to the ComboBox
        comboBox->Items->Add("Sunday");
        comboBox->Items->Add("Monday");
        comboBox->Items->Add("Tuesday");
        comboBox->Items->Add("Wednesday");
        comboBox->Items->Add("Thursday");
        comboBox->Items->Add("Friday");
        comboBox->Items->Add("Saturday");
        //comboBox->Items->Add("Option 3");

        comboBoxWeek->Items->Add("Week 1");
        comboBoxWeek->Items->Add("Week 2");
        comboBoxWeek->Items->Add("Week 3");
        comboBoxWeek->Items->Add("Week 4");

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

        if (selectedValue == "Sunday") selectedTable = GlobalObjects::Globals::monthlyTables[selectedweek]->Gtable1;
        else if (selectedValue == "Monday") selectedTable = GlobalObjects::Globals::monthlyTables[selectedweek]->Gtable2;
        else if (selectedValue == "Tuesday") selectedTable = GlobalObjects::Globals::monthlyTables[selectedweek]->Gtable3;
        else if (selectedValue == "Wednesday") selectedTable = GlobalObjects::Globals::monthlyTables[selectedweek]->Gtable4;
        else if (selectedValue == "Thursday") selectedTable = GlobalObjects::Globals::monthlyTables[selectedweek]->Gtable5;
        else if (selectedValue == "Friday") selectedTable = GlobalObjects::Globals::monthlyTables[selectedweek]->Gtable6;
        else if (selectedValue == "Saturday") selectedTable = GlobalObjects::Globals::monthlyTables[selectedweek]->GTable7;

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

