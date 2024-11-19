#pragma once
#include "sqlite3.h"

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
        ComboBox^ comboBox = gcnew ComboBox();
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
        void Add_addbutton(int xpos, int ypos);
        void addbuttonclick(Object^ sender, EventArgs^ e);
        void Add_deletebutton(int xpos, int ypos);
        void delbuttonclick(Object^ sender, EventArgs^ e);
        void UpdateComboBox();
        void comboBox_SelectedIndexChanged(Object^ sender, EventArgs^ e);
    };
}
