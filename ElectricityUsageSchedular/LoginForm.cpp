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
        //Initialize variables
        insideTextBox = false;

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

        // Create the label
        passText = gcnew Label();
        passText->Text = "Passcode";
        passText->AutoSize = true;
        passText->Location = System::Drawing::Point(530,200);
        passText->Font = gcnew System::Drawing::Font("Courier New", 18, System::Drawing::FontStyle::Bold);

        this->Controls->Add(passText);

        //Create the textbox
        passBox = gcnew TextBox();
        passBox->Size = System::Drawing::Size(150, 50);
        passBox->Location = System::Drawing::Point(520, 250);
        passBox->GotFocus += gcnew EventHandler(this, &LoginForm::InsideTextBox);
        passBox->LostFocus += gcnew EventHandler(this, &LoginForm::OutsideTextBox);
        passBox->KeyDown += gcnew KeyEventHandler(this, &LoginForm::OnEnterPressed);

        this->Controls->Add(passBox);


    }

    void LoginForm::OnLoginClick(Object^ sender, EventArgs^ e)
    {
        LoginSuccess();
    }

    void LoginForm::MoveToRegister(Object^ sender, EventArgs^ e)
    {
        // Hide login screen and show registration screen
        this->Hide();
        RegisterForm^ regForm = gcnew RegisterForm();
        regForm->Show();

    }

    void LoginForm::LoginSuccess()
    {
        this->Hide();
        MainForm^ mainForm = gcnew MainForm();
        mainForm->Show();

        //CustomMessageForm^ msg = gcnew CustomMessageForm("Login success!", "Login Status", true);
        // msg->Show();
    }

    void LoginForm::LoginFailure()
    {
        CustomMessageForm^ msg = gcnew CustomMessageForm("Please try again!", "Login Status", true);
        msg->Show();
    }

    bool LoginForm::LoginCheck()
    {
        return true;
    }

    void LoginForm::OnEnterPressed(Object^ sender, KeyEventArgs^ e)
    {
        if (e->KeyCode == Keys::Enter && insideTextBox)
        {
            LoginSuccess();
        }
    }

    void LoginForm::InsideTextBox(Object^ sender, EventArgs^ e)
    {
        insideTextBox = true;
    }

    void LoginForm::OutsideTextBox(Object^ sender, EventArgs^ e)
    {
        insideTextBox = false;
    }


}
