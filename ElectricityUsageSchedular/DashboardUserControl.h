#pragma once

#include "RoundedRectangle.h"

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

        void InitializeComponent(void);
        void ApplyRoundedRectangleToPanel(Panel^ panel, int radius, RoundedRectangles::RoundedRectangle::RectangleCorners corners);
    };
}

