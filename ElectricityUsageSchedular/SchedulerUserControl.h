#pragma once

namespace EUS {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class SchedulerUserControl : public System::Windows::Forms::UserControl
    {
    public:
        SchedulerUserControl(void);

    protected:
        ~SchedulerUserControl();

    private:
        System::ComponentModel::Container^ components;

        void InitializeComponent(void);
        void initializeTable();
    };
}
