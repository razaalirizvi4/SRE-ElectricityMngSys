#include "pch.h"
#include "AnalyticsUserControl.h"

namespace EUS {

        AnalyticsUserControl::AnalyticsUserControl(void)
        {
            InitializeComponent();
        }

        AnalyticsUserControl::~AnalyticsUserControl()
        {
            if (components)
            {
                delete components;
            }
        }

        void AnalyticsUserControl::InitializeComponent(void)
        {
            this->components = gcnew System::ComponentModel::Container();
            this->Size = System::Drawing::Size(600, 400);
            this->BackColor = Color::FromArgb(235, 245, 235);

            Label^ label = gcnew Label();
            label->Text = L"Analytics Page";
            label->Font = gcnew System::Drawing::Font("Arial", 18, FontStyle::Bold);
            label->ForeColor = Color::FromArgb(218, 165, 32); // Gold color for highlights
            label->Dock = DockStyle::Top;
            label->TextAlign = ContentAlignment::MiddleCenter;
            this->Controls->Add(label);
        }
    };
