#include "pch.h"
#include "DevicesUserControl.h"

namespace EUS {

    DevicesUserControl::DevicesUserControl(void)
    {
        InitializeComponent();
    }

    DevicesUserControl::~DevicesUserControl()
    {
        if (components)
        {
            delete components;
        }
    }

    void DevicesUserControl::InitializeComponent(void)
    {
        this->components = gcnew System::ComponentModel::Container();
        this->Size = System::Drawing::Size(600, 400);
        this->BackColor = Color::FromArgb(235, 245, 235);

        Label^ label = gcnew Label();
        label->Text = L"Devices Page";
        label->Font = gcnew System::Drawing::Font("Arial", 18, FontStyle::Bold);
        label->ForeColor = Color::FromArgb(218, 165, 32);
        label->Dock = DockStyle::Top;
        label->TextAlign = ContentAlignment::MiddleCenter;
        this->Controls->Add(label);
    }
};

