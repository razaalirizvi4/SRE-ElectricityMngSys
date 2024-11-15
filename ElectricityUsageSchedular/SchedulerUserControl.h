
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
        ComboBox^ comboBox;
        Label^ lable;
        void InitializeComponent(void);
        void initializeTable();
        
        void SchedulerUserControl::updateBillLabel(float finalBill);
        void OnColumnDropdownChanged(System::Object^ sender, System::EventArgs^ e);
        void makeTable(vector<schedule_appliance::Appliance> arr, int rowIndex, float& currentBill, float targetBill);
        void traverseSlots(int& mover, int rowIndex);
    };
}
