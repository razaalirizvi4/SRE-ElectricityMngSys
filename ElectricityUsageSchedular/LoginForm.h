#pragma once

#include "MainForm.h"

namespace EUS {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class LoginForm : public System::Windows::Forms::Form
    {
    public:
        LoginForm(void);

    protected:
        ~LoginForm();

    private:
        System::ComponentModel::Container^ components;
        Button^ btnLogin;

        void InitializeComponent(void);
        void OnLoginClick(Object^ sender, EventArgs^ e);
    };
}
