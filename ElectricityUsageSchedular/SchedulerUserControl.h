
#include "GlobalFunctions.h"
#include"GlobalObjects.h"

namespace EUS {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class SchedulerUserControl : public System::Windows::Forms::UserControl
    {
    public:
        SchedulerUserControl(void);
        DataGridView^ table;

    protected:
        ~SchedulerUserControl();

    private:
        System::ComponentModel::Container^ components;
        ComboBox^ comboBox;
        ComboBox^ comboBoxWeek;
        Label^ lable;
        void InitializeComponent(void);
        void SchedulerUserControl::updateBillLabel(float finalBill);
        void OnColumnDropdownChanged(System::Object^ sender, System::EventArgs^ e);
        void OnWeekDropdownChanged(System::Object^ sender, System::EventArgs^ e);
        /*void initializeTable();
        void makeTable(vector<schedule_appliance::Appliance> arr, int rowIndex, float& currentBill, float targetBill);
        void traverseSlots(int& mover, int rowIndex);*/
        void setGlobalTable();
        int selectedweek;
    };
}