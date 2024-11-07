#include "pch.h"
#include "LoginForm.h"
#include "MainForm.h"

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
    }

    void LoginForm::OnLoginClick(Object^ sender, EventArgs^ e)
    {
        // Hide login screen and show the main app with sidebar
        this->Hide();
        MainForm^ mainForm = gcnew MainForm();
        mainForm->Show();
    }
}
