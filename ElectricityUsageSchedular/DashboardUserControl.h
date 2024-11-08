#pragma once

namespace EUS {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;
    using namespace System::Drawing::Drawing2D;

    public ref class DashboardUserControl : public System::Windows::Forms::UserControl
    {
    public:
        DashboardUserControl(void);
        Label^ CreateLabel(String^ text, System::Drawing::Font^ font, Color color, int width, int height, Point location);

    protected:
        ~DashboardUserControl();

    private:
        System::ComponentModel::Container^ components;

        Panel^ section1Panel;
        Panel^ section2Panel;
        Panel^ section3Panel;

        void InitializeComponent(void);
    };
}

