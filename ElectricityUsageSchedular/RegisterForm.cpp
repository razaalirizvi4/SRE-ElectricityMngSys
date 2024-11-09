#include "pch.h"
#include "RegisterForm.h"
#include "MainForm.h"

namespace EUS {

    RegisterForm::RegisterForm(void)
    {
        InitializeComponent();
    }

    RegisterForm::~RegisterForm()
    {
        if (components)
        {
            delete components;
        }
    }

    void RegisterForm::InitializeComponent(void)
    {
        //Initialize containter
        this->components = gcnew System::ComponentModel::Container();
        this->Size = System::Drawing::Size(1200, 720);
    }

}
