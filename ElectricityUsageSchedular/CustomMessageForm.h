#pragma once
using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;

#include "MainForm.h"

namespace EUS {
    public ref class CustomMessageForm : public Form
    {
    public:
        CustomMessageForm(String^ message, String^ title, bool isSuccess);

    protected:
        ~CustomMessageForm();

    private:
        String^ Message;
        String^ Title;
        bool IsSuccess;
        System::ComponentModel::Container^ components;

        Button^ btnOK;
        Label^ lblMessage;

        void InitializeComponent(void); //Basic Message Function
        void btnOK_Click(Object^ sender, EventArgs^ e);
    };
}
