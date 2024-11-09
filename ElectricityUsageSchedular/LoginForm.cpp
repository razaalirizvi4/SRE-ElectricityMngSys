#include "pch.h"
#include "LoginForm.h"
#include "MainForm.h"
#include "RegisterForm.h"
#include"CustomMessageForm.h"

namespace EUS {

    LoginForm::LoginForm(void)
    {
        InitializeComponent();
    }

    LoginForm::~LoginForm()
    {
        if (components)
        {
            delete components;
        }
    }

    void LoginForm::InitializeComponent(void)
    {
        //Initialize containter
        this->components = gcnew System::ComponentModel::Container();
        this->Size = System::Drawing::Size(1200, 720);
        this->Text = L"Login";

        // Create the login button and make it smaller
        btnLogin = gcnew Button();
        btnLogin->Text = L"Login";
        btnLogin->Size = System::Drawing::Size(100, 50);
        btnLogin->Location = System::Drawing::Point(500, 310);
        btnLogin->BackColor = Color::FromArgb(0, 122, 204);
        btnLogin->ForeColor = Color::White;
        btnLogin->Click += gcnew EventHandler(this, &LoginForm::OnLoginClick);

        this->Controls->Add(btnLogin);

        // Create the button to move to register page
        btnToRegister = gcnew Button();
        btnToRegister->Text = L"Register";
        btnToRegister->Size = System::Drawing::Size(100, 50);
        btnToRegister->Location = System::Drawing::Point(600, 310);
        btnToRegister->BackColor = Color::FromArgb(0, 204, 122);
        btnToRegister->ForeColor = Color::White;
        btnToRegister->Click += gcnew EventHandler(this, &LoginForm::MoveToRegister);

        this->Controls->Add(btnToRegister);
    }

    void LoginForm::OnLoginClick(Object^ sender, EventArgs^ e)
    {
        // Hide login screen and show the main app with sidebar
        this->Hide();
        MainForm^ mainForm = gcnew MainForm();
        mainForm->Show();

        CustomMessageForm^ msg = gcnew CustomMessageForm("Login success!","Login Status",true);
        msg->Show();
    }

    void LoginForm::MoveToRegister(Object^ sender, EventArgs^ e)
    {
        // Hide login screen and show registration screen
        this->Hide();
        RegisterForm^ regForm = gcnew RegisterForm();
        regForm->Show();

    }
}
