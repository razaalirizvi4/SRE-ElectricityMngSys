#include "pch.h"
#include "MainForm.h"
#include"CustomMessageForm.h"

namespace EUS {

    CustomMessageForm::CustomMessageForm(String^ message, String^ title, bool isSuccess)
    {
        this->Message = message;
        this->Title = title;
        this->IsSuccess = isSuccess;
        InitializeComponent();
    }

    CustomMessageForm::~CustomMessageForm()
    {
        if (components)
        {
            delete components;
        }
    }

    void CustomMessageForm::btnOK_Click(Object^ sender, EventArgs^ e)
    {
        this->Close();
    }

    void CustomMessageForm::InitializeComponent(void)
    {
        this->components = gcnew System::ComponentModel::Container();
        this->btnOK = gcnew Button();
        this->lblMessage = gcnew Label();

        // Form settings
        this->Size = System::Drawing::Size(400, 200);
        this->Text = Title;
        this->BackColor = Color::FromArgb(174, 224, 216);
        this->ForeColor = Color::White;
        this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
        this->StartPosition = FormStartPosition::CenterScreen;
        this->MaximizeBox = false;
        this->MinimizeBox = false;

        // Label settings (for displaying the message)
        this->lblMessage->Text = Message;
        this->lblMessage->Size = System::Drawing::Size(350, 100);
        this->lblMessage->Location = System::Drawing::Point(25, 0);
        this->lblMessage->TextAlign = ContentAlignment::MiddleCenter;
        this->lblMessage->Font = gcnew System::Drawing::Font("Arial", 14);
        this->lblMessage->ForeColor = Color::Black;

        // Button settings (for closing the message box)
        this->btnOK->Text = "OK";
        this->btnOK->Size = System::Drawing::Size(100, 40);
        this->btnOK->Location = System::Drawing::Point(150, 100);
        this->btnOK->BackColor = Color::FromArgb(0, 122, 204);
        this->btnOK->ForeColor = Color::White;
        this->btnOK->Click += gcnew EventHandler(this, &CustomMessageForm::btnOK_Click);

        // Add controls to form
        this->Controls->Add(this->lblMessage);
        this->Controls->Add(this->btnOK);
    }


}