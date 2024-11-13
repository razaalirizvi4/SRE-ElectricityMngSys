
#include "GlobalFunctions.h"

namespace EUS {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class SchedulerUserControl : public System::Windows::Forms::UserControl
    {
    public:
        SchedulerUserControl(void);

    protected:
        ~SchedulerUserControl();

    private:
        System::ComponentModel::Container^ components;
        DataGridView^ table;
        Label^ lable;
        void InitializeComponent(void);
        void initializeTable();
        void setValues(vector<schedule_appliance::Appliance> arr, int rowInd);
        void fillScheduleWithBacktracking(
            vector<schedule_appliance::Appliance>& appliances,
            int rowInd,
            float& currentBill,
            const float billThreshold);
        void backtrackAndAdjust(
            vector<schedule_appliance::Appliance>& appliances,
            int rowInd,
            float& currentBill,
            const float billThreshold);
        int assignSlots(int rowIndex, int numSlots, float& currentBill, float kwh);
        void SchedulerUserControl::updateBillLabel(float finalBill);
        int calculateReductionSlots(const schedule_appliance::Appliance& appliance);
        int calculateDynamicSlots(
            const schedule_appliance::Appliance& appliance,
            float remainingBudget);
    };
}
