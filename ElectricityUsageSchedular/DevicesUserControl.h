#pragma once

namespace EUS {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class DevicesUserControl : public System::Windows::Forms::UserControl
    {
    public:
        DevicesUserControl(void);
        Panel^ topLeftPanel;

    protected:
        ~DevicesUserControl();

    private:
        System::ComponentModel::Container^ components;

        void InitializeComponent(void);
    };
}
