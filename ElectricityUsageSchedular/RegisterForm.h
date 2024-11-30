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
        Button^ btntoLogin;
        Button^ btnRegister;

        Label^ userName;
        Label^ userEmail;
        Label^ userPassword;
        Label^ userProvince;
        Label^ userCity;
        Label^ userArea;

        TextBox^ nameBox;
        TextBox^ emailBox;
        TextBox^ passwordBox;
        ComboBox^ provinceBox;
        ComboBox^ cityBox;
        ComboBox^ areaBox;
  

        void InitializeComponent(void);
        void MoveToLogin(Object^ sender, EventArgs^ e);
        void OnFormClosed(Object^ sender, FormClosedEventArgs^ e);

        void OnRegisterClick(Object^ sender, EventArgs^ e);
        bool RegisterCheck();
        bool RegisterDBCheck();
        void RegisterSuccess();
        void RegisterFailure();

        bool ValidPassword(String^p);
        bool ValidEmail(String^e);
        bool ValidName(String^n);
        bool ValidProvince(String^p);
        bool ValidCity(String^ c);
        bool ValidArea(String^ a);

        void LoadCitiesForProvince(String^ province);
        void OnProvinceSelected(Object^ sender, EventArgs^ e);
        void OnCitySelected(Object^ sender, EventArgs^ e);
        void LoadAreasForCity(String^ city);


    };
}
