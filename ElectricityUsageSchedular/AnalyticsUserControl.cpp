#include "pch.h"
#include "AnalyticsUserControl.h"

namespace EUS {

        AnalyticsUserControl::AnalyticsUserControl(void)
        {
            InitializeComponent();
            this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &AnalyticsUserControl::MakePieChart);
            this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &AnalyticsUserControl::MakeBarChart);
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

            //top text
            Label^ label = gcnew Label();
            label->Text = L"Analytics Page";
            label->Font = gcnew System::Drawing::Font("Arial", 24, FontStyle::Bold);
            label->ForeColor = Color::FromArgb(69, 160, 227);
            label->Dock = DockStyle::Top;  // Changed from Fill to Top
            label->Height = 50;            // Give it a specific height (fix bottom sharp cutoff)
            label->TextAlign = ContentAlignment::MiddleCenter;
            this->Controls->Add(label);
        }

        void AnalyticsUserControl::MakePieChart(Object^ sender, PaintEventArgs^ e)
        {

            int totalAppliances = GlobalObjects::Globals::Gtable->Rows->Count;
            int* hoursForEachAppliance = new int[totalAppliances-1];



            //get all hours in an array, each index represenitng appliance number and value representing hours run
            for (int i = 0; i < totalAppliances; i++)   //for each appliance
            {
                int count = 0;
                for (int j = 1; j < 24; j++)            //for each hour
                {
                    if (GlobalObjects::Globals::Gtable->Rows[i]->Cells[j]->Value == "+")
                    {
                        count++;
                    }
                }
                hoursForEachAppliance[i] = count;
            }

            int topFourAppliancesIndexes[4] = { 0 };
            int topFourAppliancesHours[4] = { 0 };

            for (int i = 0; i < 4; i++)                         //get top 4 appliances and their hours
            {
                int count = 0;
                int Bcount = 0;
                int index = 0;
                for (int j = 0; j < totalAppliances; j++)
                {
                    count = hoursForEachAppliance[j];
                    if (count > Bcount)
                    {
                        Bcount = count;                         //get max hours
                        index = j;                              //get index of appliance with max hours
                    }
                }
                topFourAppliancesIndexes[i] = index;
                topFourAppliancesHours[i] = Bcount;
                hoursForEachAppliance[index] = -1;              //so it wont be counted again
            }

            // Data for the pie chart
            array<float>^ values = { topFourAppliancesHours[0],topFourAppliancesHours[1],topFourAppliancesHours[2],topFourAppliancesHours[3] };
            array<String^>^ labels = { GlobalObjects::Globals::Gtable->Rows[topFourAppliancesIndexes[0]]->Cells[0]->Value->ToString(), GlobalObjects::Globals::Gtable->Rows[topFourAppliancesIndexes[1]]->Cells[0]->Value->ToString(), GlobalObjects::Globals::Gtable->Rows[topFourAppliancesIndexes[2]]->Cells[0]->Value->ToString(), GlobalObjects::Globals::Gtable->Rows[topFourAppliancesIndexes[3]]->Cells[0]->Value->ToString() };
            
            //alternating theme-matching colours
            int startR = 0, startG = 91, startB = 156;
            int endR = 99, endG = 190, endB = 255;

            int numSlices = values->Length;
            array<Color>^ colors = gcnew array<Color>(numSlices);

            for (int i = 0; i < numSlices; i++)
            {
                // Calculate intermediate color values
                int r = startR + ((endR - startR) * i / (numSlices - 1));
                int g = startG + ((endG - startG) * i / (numSlices - 1));
                int b = startB + ((endB - startB) * i / (numSlices - 1));

                colors[i] = Color::FromArgb(r, g, b);
            }            

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
            int width = 250;
            int height = 250;
            Drawing::Rectangle rect = Drawing::Rectangle(x, y, width, height);

            // Draw pie slices
            float startAngle = 0.0f;
            for (int i = 0; i < values->Length; i++)
            {
                float sweepAngle = (values[i] / total) * 360.0f;

                // Draw slice
                g->FillPie(gcnew SolidBrush(colors[i]), rect, startAngle, sweepAngle);

                // Draw border
                g->DrawPie(Pens::Black, rect, startAngle, sweepAngle);

                // Calculate legend position
                int legendX = x + width + 30;                                   //side rectangles spacing
                int legendY = y + (i * 20);

                // Draw legend box
                g->FillRectangle(gcnew SolidBrush(colors[i]),                   //side rectangle width and height
                    legendX, legendY, 10, 10);
                g->DrawRectangle(Pens::Black,
                    legendX, legendY, 10, 10);

                // Draw legend text
                g->DrawString(                                                  //side rectangle text size and spacing
                    String::Format("{0}: {1} Hours",
                    labels[i],
                    (values[i])),
                    gcnew System::Drawing::Font("Arial", 10),
                    Brushes::Black,
                    legendX + 15,
                    legendY-3
                );

                startAngle += sweepAngle;
            }

            //text under pie chart
            Label^ PieLabel = gcnew Label();
            PieLabel->Text = L"Each Appliance's energy\n\tConsumption";
            PieLabel->Font = gcnew System::Drawing::Font("Arial", 18, FontStyle::Bold);
            PieLabel->ForeColor = Color::FromArgb(69, 160, 227);
            PieLabel->AutoSize = true;
            PieLabel->Location = Point(x-15, y+280);
            PieLabel->TextAlign = ContentAlignment::MiddleCenter;
            this->Controls->Add(PieLabel);
        }

        void AnalyticsUserControl::MakeBarChart(Object^ sender, PaintEventArgs^ e)
        {

            // Data for the bar chart
            array<float>^ values = { 10.0f, 20.0f, 4.0f, 32.0f,56.0f,12.0f,69.0f,21.0f,32.5f, 10.0f, 20.0f, 4.0f, 32.0f,56.0f,12.0f,69.0f,21.0f,32.5f, 56.0f,45.6f,52.01f,34.56f,12.0f };
            array<String^>^ labels = { "00-01", "01-02", "02-03", "03-04", "04-05", "05-06", "06-07", "07-08", "08-09", "09-10", "10-11", "11-12", "12-13", "13-14", "14-15", "15-16", "16-17", "17-18", "18-19", "19-20", "20-21", "21-22", "22-23", "23-00" };

            // Calculate colors for each bar
            int numBars = values->Length;
            array<Color>^ colors = gcnew array<Color>(numBars);

            for (int i = 0; i < numBars; i++)
            {
                if (i % 2 == 0)
                {
                    colors[i] = Color::FromArgb(46, 138, 205);
                }
                else
                {
                    colors[i] = Color::FromArgb(96, 188, 255);
                }
            }

            Graphics^ g = e->Graphics;
            g->SmoothingMode = Drawing2D::SmoothingMode::AntiAlias;

            // Define chart area with more space for rotated labels         //overall graph size
            int marginLeft = 850;
            int marginRight = 125;  // Space for legend
            int marginTop = 110;
            int marginBottom = 380;  // More space for rotated labels
            int x = marginLeft;
            int y = marginTop;
            int width = this->Width - (marginLeft + marginRight);
            int height = this->Height - (marginTop + marginBottom);

            // Calculate the maximum value for scaling
            float maxValue = 0;
            for each (float value in values)
            {
                if (value > maxValue) maxValue = value;
            }

            // Calculate bar properties with thinner bars
            int barWidth = (width) / (numBars * 1);                       //width
            int barSpacing = barWidth / 8;  // Less spacing
            float scaleY = (height - 50) / maxValue;

            // Draw bars and labels
            System::Drawing::Font^ labelFont = gcnew System::Drawing::Font("Arial", 8);  // Smaller font
            System::Drawing::Font^ valueFont = gcnew System::Drawing::Font("Arial", 8);  // Smaller font

            for (int i = 0; i < numBars; i++)
            {
                // Calculate bar dimensions
                int barX = x + (i * (barWidth + barSpacing));
                int barHeight = (int)(values[i] * scaleY);                //height
                int barY = y + height - barHeight - 40;

                // Draw bar
                Drawing::Rectangle barRect = Drawing::Rectangle(barX, barY, barWidth, barHeight);
                g->FillRectangle(gcnew SolidBrush(colors[i]), barRect);
                g->DrawRectangle(Pens::Black, barRect);

                // Draw value on top of bar
                String^ valueText = values[i].ToString("F1");
                SizeF valueSize = g->MeasureString(valueText, valueFont);
                g->DrawString(valueText,
                    valueFont,
                    Brushes::Black,
                    barX + (barWidth - valueSize.Width) / 2,
                    barY - valueSize.Height - 2);

                if (i % 1 == 0)  // Adjust this number to show more or fewer labels
                {
                    SizeF labelSize = g->MeasureString(labels[i], labelFont);
                    g->TranslateTransform(
                        barX + (barWidth) / 2,
                        y + height - 25
                    );
                    g->RotateTransform(-35);  // 45-degree angle
                    g->DrawString(labels[i],
                        labelFont,
                        Brushes::Black,
                        -labelSize.Width / 2,  // Center the text
                        0);
                    g->ResetTransform();
                }
            }

            // Draw axes
            Pen^ axisPen = gcnew Pen(Color::Black, 2);
            g->DrawLine(axisPen, x, y + height - 40, x, y);
            g->DrawLine(axisPen, x, y + height - 40, x + width+50, y + height - 40);

            //text under pie chart
            Label^ BarLabel = gcnew Label();
            BarLabel->Text = L"Energy Consumed each\n\tHour";
            BarLabel->Font = gcnew System::Drawing::Font("Arial", 18, FontStyle::Bold);
            BarLabel->ForeColor = Color::FromArgb(69, 160, 227);
            BarLabel->AutoSize = true;
            BarLabel->Location = Point(x + 130, y + height + 10);
            BarLabel->TextAlign = ContentAlignment::MiddleCenter;
            this->Controls->Add(BarLabel);
        }
    };
