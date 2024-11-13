#include "pch.h"
#include "SchedulerUserControl.h"
#include <iostream>


namespace EUS {

    SchedulerUserControl::SchedulerUserControl(void)
    {
        InitializeComponent();
        initializeTable();
        vector<schedule_appliance::Appliance> arr;
        for (int i = 1; i <= 15; ++i) {
            string name = "name" + to_string(i);
            float kwh = 1.8f;
            int priority = (i % 3) + 1;

            // Create and push the appliance object into the vector
            arr.push_back(schedule_appliance::Appliance(name, kwh, priority));
        }
        sortit(arr, 0);

        float dailyBill = 0.0f;
        const float monthlyThreshold = 50000.0f;
        const float dailyThreshold = monthlyThreshold / 30.0f; // Calculate daily threshold

        fillScheduleWithBacktracking(arr, 0, dailyBill, dailyThreshold);

        // Project the monthly bill based on the daily calculation
        float estimatedMonthlyBill = dailyBill * 30;
        updateBillLabel(estimatedMonthlyBill);
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
    void SchedulerUserControl::setValues(vector<schedule_appliance::Appliance> arr, int rowInd) {
        if (rowInd >= arr.size()) {
            return;
        }
        if (arr[rowInd].priority == 3) {
            for (int i = 1; i < 24; i++)
            table->Rows[rowInd]->Cells[i]->Value = "+";
        }
        else if (arr[rowInd].priority == 2) {
            for (int i = 1; i < 24; i*= 2)
                table->Rows[rowInd]->Cells[i]->Value = "+";
        }
        else {
            for (int i = 1; i < 24; i *= 4)
                table->Rows[rowInd]->Cells[i]->Value = "+";
        }
        setValues(arr, rowInd + 1);
    }

    

    

    void SchedulerUserControl::fillScheduleWithBacktracking(
        vector<schedule_appliance::Appliance>& appliances,
        int rowInd,
        float& currentBill,
        const float billThreshold)
    {
        if (rowInd >= appliances.size()) return;

        float remainingBudget = billThreshold - currentBill;
        int slotsToAssign = calculateDynamicSlots(appliances[rowInd], remainingBudget);

        int slotsFilled = assignSlots(rowInd, slotsToAssign, currentBill, appliances[rowInd].kwh);

        std::cout << "After assigning slots to row " << rowInd << ", Current Bill: " << currentBill << "\n";

        if (currentBill > billThreshold) {
            std::cout << "Exceeded bill threshold. Adjusting slots...\n";
            backtrackAndAdjust(appliances, rowInd, currentBill, billThreshold);
        }

        fillScheduleWithBacktracking(appliances, rowInd + 1, currentBill, billThreshold);
    }

    int SchedulerUserControl::calculateDynamicSlots(
        const schedule_appliance::Appliance& appliance,
        float remainingBudget)
    {
        float costPerSlot = 12.5f * appliance.kwh;

        int maxPossibleSlots = static_cast<int>(remainingBudget / costPerSlot);
        int priorityMultiplier = (appliance.priority == 3) ? 1 : (appliance.priority == 2) ? 2 : 4;

        int dynamicSlots = maxPossibleSlots / priorityMultiplier;
        return max(0, dynamicSlots);
    }

    int SchedulerUserControl::assignSlots(int rowIndex, int numSlots, float& currentBill, float kwh) {
        int slotsFilled = 0;
        const float costPerSlot = 41.6f * kwh;

        for (int i = 1; i < 24 && slotsFilled < numSlots; ++i) {
            if (table->Rows[rowIndex]->Cells[i]->Value == nullptr) {
                table->Rows[rowIndex]->Cells[i]->Value = "+";
                slotsFilled++;
                currentBill += costPerSlot;
            }
        }

        std::cout << "Assigned " << slotsFilled << " slots to row " << rowIndex << ", New Bill: " << currentBill << "\n";

        return slotsFilled;
    }

    void SchedulerUserControl::backtrackAndAdjust(
        vector<schedule_appliance::Appliance>& appliances,
        int rowInd,
        float& currentBill,
        const float billThreshold)
    {
        for (int i = appliances.size() - 1; i >= 0; --i) {
            int reductionSlots = calculateReductionSlots(appliances[i]);

            for (int j = 1; j < 24 && reductionSlots > 0; ++j) {
                if (table->Rows[i]->Cells[j]->Value != nullptr) {
                    table->Rows[i]->Cells[j]->Value = nullptr;
                    currentBill -= appliances[i].kwh * 12.5f;
                    reductionSlots--;

                    std::cout << "Backtracking: Reduced slot in row " << i << ", Current Bill: " << currentBill << "\n";

                    if (currentBill <= billThreshold) return;
                }
            }
        }
    }

    int SchedulerUserControl::calculateReductionSlots(const schedule_appliance::Appliance& appliance)
    {
        return (appliance.priority == 3) ? 2 : (appliance.priority == 2) ? 4 : 6;
    }
};

