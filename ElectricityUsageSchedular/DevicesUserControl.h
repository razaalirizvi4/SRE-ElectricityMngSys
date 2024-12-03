#pragma once
#include <sqlite3.h>

namespace EUS {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class DevicesUserControl : public System::Windows::Forms::UserControl
    {
    public:
        DevicesUserControl(void);
        Panel^ topLeftPanel;
        
    protected:
        ~DevicesUserControl();

    private:
        System::ComponentModel::Container^ components;
        void InitializeComponent(void);
        void open_dbconnection();
        void AddButton1(int xpos, int ypos);
        void OnButtonClick1(Object^ sender, EventArgs^ e);
        void AddButton2(int xpos, int ypos);
        void OnButtonClick2(Object^ sender, EventArgs^ e);
        void AddButton3(int xpos, int ypos);
        void OnButtonClick3(Object^ sender, EventArgs^ e);
        void AddButton4(int xpos, int ypos);
        void OnButtonClick4(Object^ sender, EventArgs^ e);
        void AddButton5(int xpos, int ypos);
        void OnButtonClick5(Object^ sender, EventArgs^ e);
        void AddButton6(int xpos, int ypos);
        void OnButtonClick6(Object^ sender, EventArgs^ e);
        void AddButton7(int xpos, int ypos);
        void OnButtonClick7(Object^ sender, EventArgs^ e);
        
       
    };
    using namespace System;
    using namespace System::Windows::Forms;

    public ref class MyDialogForm : public Form
    {
    public:
        ComboBox^ comboBox = gcnew ComboBox();
        ComboBox^ prioritycombo = gcnew ComboBox();
        MyDialogForm();

    private:
        void UpdateComboBox1();
        
        void comboBox_SelectedIndexChanged1(Object^ sender, EventArgs^ e);
        void comboBox_SelectedIndexChanged2(Object^ sender, EventArgs^ e);
        void OnOkButtonClick(Object^ sender, EventArgs^ e)
        {
            // Close the dialog when the button is clicked
            this->Close();
        }
        void Add_addbutton(int xpos, int ypos);
        void addbuttonclick(Object^ sender, EventArgs^ e);
        void Add_deletebutton(int xpos, int ypos);
        void delbuttonclick(Object^ sender, EventArgs^ e);
        void push_app();
        
       
    };

}
