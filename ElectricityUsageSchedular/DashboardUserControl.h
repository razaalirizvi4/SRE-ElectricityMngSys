#pragma once
#include "RoundedRectangle.h"
#include"Userclass.h"
namespace EUS {
    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;
    using namespace System::Drawing::Drawing2D;

    // Structure to hold panel configuration
    public value struct PanelConfig {
        int Width;
        int Height;
        Point Location;
        Color BackColor;
        String^ Title;
        String^ Content;
        int LineSpacing;
        int ContentYOffset;
    };

    // Constants for visual styling
    public ref class DashboardStyles {
    public:
        static initonly Color MainBackColor = Color::FromArgb(212, 237, 250);
        static initonly Color PanelBackColor = Color::FromArgb(69, 160, 227);
        static initonly System::Drawing::Font^ TitleFont = gcnew System::Drawing::Font("Calibri", 16, FontStyle::Bold);
        static initonly System::Drawing::Font^ ContentFont = gcnew System::Drawing::Font("Calibri", 12);
        static const int DefaultCornerRadius = 40;
        static const int DefaultMargin = 60;
        static const int DefaultSpacing = 50;
        static const int DefaultSpacing2 = 20;
        static int MiniBoxHeight = 165;
    };

    public ref class DashboardUserControl : public System::Windows::Forms::UserControl {
    public:
        DashboardUserControl(void);

    protected:
        ~DashboardUserControl();

        Button^ CreateRoundedButton(String^ iconPath, int size, Point location);

    private:
        System::ComponentModel::Container^ components;
        int screenWidth = Screen::PrimaryScreen->Bounds.Width;

        Label^ CreateLabel(String^ text, System::Drawing::Font^ font, Color color, int width, int height, Point location);
        Panel^ CreatePanel(PanelConfig config);
        void ApplyRoundedRectangleToPanel(Panel^ panel, int radius);

        // Section creation methods
        Panel^ CreateTopSection();
        void InitializeComponent(void);
    };
}
