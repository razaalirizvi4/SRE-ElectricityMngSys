#include "pch.h"
#include "SchedulerUserControl.h"
#include <iostream>
#include "globals2.h"




void InitializeTable1(System::Windows::Forms::DataGridView^ targetTable) {
    // Clear the target table
    targetTable->Rows->Clear();
    targetTable->Columns->Clear();

    targetTable->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
    targetTable ->ColumnHeadersVisible = true;
    targetTable->RowHeadersVisible = false;
    targetTable->AllowUserToAddRows = false;

    // Copy column structure from Gtable
    for (int i = 0; i < GlobalObjects::Globals::Gtable->ColumnCount; ++i) {
        auto newColumn = gcnew System::Windows::Forms::DataGridViewTextBoxColumn();
        newColumn->HeaderText = GlobalObjects::Globals::Gtable->Columns[i]->HeaderText;
        newColumn->Width = GlobalObjects::Globals::Gtable->Columns[i]->Width;
        targetTable->Columns->Add(newColumn);
    }

    // Copy row data from Gtable
    for (int i = 0; i < GlobalObjects::Globals::Gtable->RowCount; ++i) {
        // Create a new row for the target table
        System::Windows::Forms::DataGridViewRow^ newRow = gcnew System::Windows::Forms::DataGridViewRow();

        // Copy each cell's value from Gtable to the new row
        for (int j = 0; j < GlobalObjects::Globals::Gtable->ColumnCount; ++j) {
            System::Windows::Forms::DataGridViewCell^ newCell = gcnew System::Windows::Forms::DataGridViewTextBoxCell();
            newCell->Value = GlobalObjects::Globals::Gtable->Rows[i]->Cells[j]->Value;
            newRow->Cells->Add(newCell);
        }

        // Add the newly created row to the target table
        targetTable->Rows->Add(newRow);
    }
}




namespace EUS {

    SchedulerUserControl::SchedulerUserControl(void)
    {
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
        const float monthlyThreshold = 50000.0f;

        const float dailyThreshold = monthlyThreshold / 30.0f; // Calculate daily threshold
        initializeTable();
        makeTable(dailyBill, dailyThreshold, arr);
        GlobalObjectsRaza::Globals::unmanagedGlobals->bill = dailyBill;
        sqlite3_close(GlobalObjectsRaza::Globals::unmanagedGlobals->dbr);
        updateBillLabel(GlobalObjectsRaza::Globals::unmanagedGlobals->bill * 30);
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
        comboBox->Items->Add("1");
        comboBox->Items->Add("2");
        comboBox->Items->Add("3");
        comboBox->Items->Add("4");
        comboBox->Items->Add("5");
        comboBox->Items->Add("6");
        comboBox->Items->Add("7");
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
        
        InitializeTable1(GlobalObjects::Globals::Gtable2);
        RandomizeTable(GlobalObjects::Globals::Gtable2);
        InitializeTable1(GlobalObjects::Globals::Gtable3);
        RandomizeTable(GlobalObjects::Globals::Gtable3);
        InitializeTable1(GlobalObjects::Globals::Gtable4);
        RandomizeTable(GlobalObjects::Globals::Gtable4);
        InitializeTable1(GlobalObjects::Globals::Gtable5);
        RandomizeTable(GlobalObjects::Globals::Gtable5);
        InitializeTable1(GlobalObjects::Globals::Gtable6);
        RandomizeTable(GlobalObjects::Globals::Gtable6);
        InitializeTable1(GlobalObjects::Globals::Gtable7);
        RandomizeTable(GlobalObjects::Globals::Gtable7);
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

        if (selectedValue == "1") selectedTable = GlobalObjects::Globals::Gtable;
        else if (selectedValue == "2") selectedTable = GlobalObjects::Globals::Gtable2;
        else if (selectedValue == "3") selectedTable = GlobalObjects::Globals::Gtable3;
        else if (selectedValue == "4") selectedTable = GlobalObjects::Globals::Gtable4;
        else if (selectedValue == "5") selectedTable = GlobalObjects::Globals::Gtable5;
        else if (selectedValue == "6") selectedTable = GlobalObjects::Globals::Gtable6;
        else if (selectedValue == "7") selectedTable = GlobalObjects::Globals::Gtable7;

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



};

