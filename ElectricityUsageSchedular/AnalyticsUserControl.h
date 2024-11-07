#pragma once

namespace EUS {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class AnalyticsUserControl : public System::Windows::Forms::UserControl
    {
    public:
        AnalyticsUserControl(void);

    protected:
        ~AnalyticsUserControl();

    private:
        System::ComponentModel::Container^ components;

        void InitializeComponent(void);
    };
}
