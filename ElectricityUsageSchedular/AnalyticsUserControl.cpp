#include "pch.h"
#include "AnalyticsUserControl.h"

namespace EUS {

        AnalyticsUserControl::AnalyticsUserControl(void)
        {
            InitializeComponent();
            this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &AnalyticsUserControl::MakePieChart);
            this->DoubleBuffered = true;  // Add this line for smoother rendering
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
            this->BackColor = Color::FromArgb(212, 237, 250);

            Label^ label = gcnew Label();
            label->Text = L"Analytics Page";
            label->Font = gcnew System::Drawing::Font("Arial", 24, FontStyle::Bold);
            label->ForeColor = Color::FromArgb(69, 160, 227);
            label->Dock = DockStyle::Top;  // Changed from Fill to Top
            label->Height = 50;            // Give it a specific height
            label->TextAlign = ContentAlignment::MiddleCenter;
            this->Controls->Add(label);
        }

        void AnalyticsUserControl::MakePieChart(Object^ sender, PaintEventArgs^ e)
        {
            // Sample data for the pie chart
            array<float>^ values = { 20.0f, 20.0f, 15.0f, 45.0f };
            array<String^>^ labels = { "Fridge", "Oven", "Television", "Sega Genesis" };
            array<Color>^ colors = {Color::Red, Color::Blue, Color::Green, Color::Yellow};

            // Calculate total for percentages
            float total = 0;
            for each (float value in values)                //what the fuck kind of loop is this ???
            {
                total += value;
            }

            // Set up graphics
            Graphics^ g = e->Graphics;
            g->SmoothingMode = Drawing2D::SmoothingMode::AntiAlias;

            // Define chart area
            int x = 100;
            int y = 125;
            int width = 300;
            int height = 300;
            Drawing::Rectangle rect = Drawing::Rectangle(x, y, width, height);

            // Draw pie slices
            float startAngle = 0.0f;
            for (int i = 0; i < values->Length; i++) {
                float sweepAngle = (values[i] / total) * 360.0f;

                // Draw slice
                g->FillPie(gcnew SolidBrush(colors[i]), rect, startAngle, sweepAngle);

                // Draw border
                g->DrawPie(Pens::Black, rect, startAngle, sweepAngle);

                // Calculate legend position
                int legendX = x + width + 50;
                int legendY = y + (i * 30);

                // Draw legend box
                g->FillRectangle(gcnew SolidBrush(colors[i]),
                    legendX, legendY, 20, 20);
                g->DrawRectangle(Pens::Black,
                    legendX, legendY, 20, 20);

                // Draw legend text
                g->DrawString(
                    String::Format("{0}: {1:F1}%",
                    labels[i],
                    (values[i] / total) * 100),
                    gcnew System::Drawing::Font("Arial", 10),
                    Brushes::Black,
                    legendX + 30,
                    legendY
                );

                startAngle += sweepAngle;
            }
        }
    };
