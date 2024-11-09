#pragma once

#include "MainForm.h"

namespace EUS {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class RegisterForm : public System::Windows::Forms::Form
    {
    public:
        RegisterForm(void);

    protected:
        ~RegisterForm();

    private:
        System::ComponentModel::Container^ components;
        Button^ btnLogin;

        void InitializeComponent(void);

    };
}
