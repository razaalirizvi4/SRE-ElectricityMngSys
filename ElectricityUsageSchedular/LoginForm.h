#pragma once

#include "MainForm.h"
#include<string.h>

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
        Button^ btnToRegister;

        Label^ passText;
        TextBox^ passBox;

        Label^ emailText;
        TextBox^ emailBox;

        String^ getEmail;
        String^ getPassword;
        String^ getUsername;
        int getID;

        bool insideTextBox;

        void InitializeComponent(void);
        void OnLoginClick(Object^ sender, EventArgs^ e);
        void MoveToRegister(Object^ sender, EventArgs^ e);
        void LoginSuccess();
        void LoginFailure();
        bool LoginCheck();

        void OnEnterPressed(Object^ sender,KeyEventArgs^e);
        void InsideTextBox(Object^ sender, EventArgs^ e);
        void OutsideTextBox(Object^ sender, EventArgs^ e);
    };

    class UserData
    {
    public:
        static int userid;
        static string username;
        static string useremail;
        static string userpassword;
        static string userprovince;
        static string usercity;
        static string userarea;
        static string userpeakstart;
        static string userpeakend;

    };

}
