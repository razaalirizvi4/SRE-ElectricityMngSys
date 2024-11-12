#pragma once
#include<vector>

namespace EUS
{
    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class AnalyticsUserControl : public System::Windows::Forms::UserControl
    {

        public:
            AnalyticsUserControl(void);

        protected:
            ~AnalyticsUserControl();

        private:
            System::ComponentModel::Container^ components;
            void MakePieChart(Object^ sender, PaintEventArgs^ e);
            void InitializeComponent(void);
    };
}
