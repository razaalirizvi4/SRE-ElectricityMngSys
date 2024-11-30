#include "pch.h"
#include "AnalyticsUserControl.h"
#include"week.h"

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

            Week::Tables^ week1 = GlobalObjects::Globals::monthlyTables[0];
            Week::Tables^ week2 = GlobalObjects::Globals::monthlyTables[1];
            Week::Tables^ week3 = GlobalObjects::Globals::monthlyTables[2];
            Week::Tables^ week4 = GlobalObjects::Globals::monthlyTables[3];

            int totalAppliances = week1->Gtable1->Rows->Count;
            int* hoursForEachAppliance = new int[totalAppliances - 1];
            for (int i = 0; i < totalAppliances; i++)
            {
                hoursForEachAppliance[i] = 0;
            }

            array<DataGridView^>^ ArrayW1 = gcnew array<DataGridView^>(7);
            ArrayW1[0] = week1->Gtable1;
            ArrayW1[1] = week1->Gtable2;
            ArrayW1[2] = week1->Gtable3;
            ArrayW1[3] = week1->Gtable4;
            ArrayW1[4] = week1->Gtable5;
            ArrayW1[5] = week1->Gtable6;
            ArrayW1[6] = week1->GTable7;

            array<DataGridView^>^ ArrayW2 = gcnew array<DataGridView^>(7);
            ArrayW2[0] = week2->Gtable1;
            ArrayW2[1] = week2->Gtable2;
            ArrayW2[2] = week2->Gtable3;
            ArrayW2[3] = week2->Gtable4;
            ArrayW2[4] = week2->Gtable5;
            ArrayW2[5] = week2->Gtable6;
            ArrayW2[6] = week2->GTable7;

            array<DataGridView^>^ ArrayW3 = gcnew array<DataGridView^>(7);
            ArrayW3[0] = week3->Gtable1;
            ArrayW3[1] = week3->Gtable2;
            ArrayW3[2] = week3->Gtable3;
            ArrayW3[3] = week3->Gtable4;
            ArrayW3[4] = week3->Gtable5;
            ArrayW3[5] = week3->Gtable6;
            ArrayW3[6] = week3->GTable7;

            array<DataGridView^>^ ArrayW4 = gcnew array<DataGridView^>(7);
            ArrayW4[0] = week4->Gtable1;
            ArrayW4[1] = week4->Gtable2;
            ArrayW4[2] = week4->Gtable3;
            ArrayW4[3] = week4->Gtable4;
            ArrayW4[4] = week4->Gtable5;
            ArrayW4[5] = week4->Gtable6;
            ArrayW4[6] = week4->GTable7;
            

            
            for (int k = 0; k < 7; k++)         //for each day in week1
            {
                for (int i = 0; i < totalAppliances; i++)   //for each appliance
                {
                    int count = 0;
                    for (int j = 1; j < 24; j++)            //for each hour of the day
                    {
                        if (ArrayW1[k]->Rows[i]->Cells[j]->Value == "+")
                        {
                            count++;
                        }
                    }
                    hoursForEachAppliance[i] += count;
                }
            }

            for (int k = 0; k < 7; k++)         //for each day in week2
            {
                for (int i = 0; i < totalAppliances; i++)   //for each appliance
                {
                    int count = 0;
                    for (int j = 1; j < 24; j++)            //for each hour of the day
                    {
                        if (ArrayW2[k]->Rows[i]->Cells[j]->Value == "+")
                        {
                            count++;
                        }
                    }
                    hoursForEachAppliance[i] += count;
                }
            }

            for (int k = 0; k < 7; k++)         //for each day in week3
            {
                for (int i = 0; i < totalAppliances; i++)   //for each appliance
                {
                    int count = 0;
                    for (int j = 1; j < 24; j++)            //for each hour of the day
                    {
                        if (ArrayW3[k]->Rows[i]->Cells[j]->Value == "+")
                        {
                            count++;
                        }
                    }
                    hoursForEachAppliance[i] += count;
                }
            }

            for (int k = 0; k < 7; k++)         //for each day in week4
            {
                for (int i = 0; i < totalAppliances; i++)   //for each appliance
                {
                    int count = 0;
                    for (int j = 1; j < 24; j++)            //for each hour of the day
                    {
                        if (ArrayW4[k]->Rows[i]->Cells[j]->Value == "+")
                        {
                            count++;
                        }
                    }
                    hoursForEachAppliance[i] += count;
                }
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
            array<String^>^ labels = { week1->Gtable1->Rows[topFourAppliancesIndexes[0]]->Cells[0]->Value->ToString(), week1->Gtable1->Rows[topFourAppliancesIndexes[1]]->Cells[0]->Value->ToString(), week1->Gtable1->Rows[topFourAppliancesIndexes[2]]->Cells[0]->Value->ToString(), week1->Gtable1->Rows[topFourAppliancesIndexes[3]]->Cells[0]->Value->ToString() };
            
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

            Week::Tables^ week1 = GlobalObjects::Globals::monthlyTables[0];
            Week::Tables^ week2 = GlobalObjects::Globals::monthlyTables[1];
            Week::Tables^ week3 = GlobalObjects::Globals::monthlyTables[2];
            Week::Tables^ week4 = GlobalObjects::Globals::monthlyTables[3];

            int totalAppliances = week1->Gtable1->Rows->Count;
            int week1H = 0;
            int week2H = 0;
            int week3H = 0;
            int week4H = 0;

            array<DataGridView^>^ ArrayW1 = gcnew array<DataGridView^>(7);
            ArrayW1[0] = week1->Gtable1;
            ArrayW1[1] = week1->Gtable2;
            ArrayW1[2] = week1->Gtable3;
            ArrayW1[3] = week1->Gtable4;
            ArrayW1[4] = week1->Gtable5;
            ArrayW1[5] = week1->Gtable6;
            ArrayW1[6] = week1->GTable7;

            array<DataGridView^>^ ArrayW2 = gcnew array<DataGridView^>(7);
            ArrayW2[0] = week2->Gtable1;
            ArrayW2[1] = week2->Gtable2;
            ArrayW2[2] = week2->Gtable3;
            ArrayW2[3] = week2->Gtable4;
            ArrayW2[4] = week2->Gtable5;
            ArrayW2[5] = week2->Gtable6;
            ArrayW2[6] = week2->GTable7;

            array<DataGridView^>^ ArrayW3 = gcnew array<DataGridView^>(7);
            ArrayW3[0] = week3->Gtable1;
            ArrayW3[1] = week3->Gtable2;
            ArrayW3[2] = week3->Gtable3;
            ArrayW3[3] = week3->Gtable4;
            ArrayW3[4] = week3->Gtable5;
            ArrayW3[5] = week3->Gtable6;
            ArrayW3[6] = week3->GTable7;

            array<DataGridView^>^ ArrayW4 = gcnew array<DataGridView^>(7);
            ArrayW4[0] = week4->Gtable1;
            ArrayW4[1] = week4->Gtable2;
            ArrayW4[2] = week4->Gtable3;
            ArrayW4[3] = week4->Gtable4;
            ArrayW4[4] = week4->Gtable5;
            ArrayW4[5] = week4->Gtable6;
            ArrayW4[6] = week4->GTable7;

            int count = 0;
            for (int k = 0; k < 7; k++)         //for each day in week1
            {
                for (int i = 0; i < totalAppliances; i++)   //for each appliance
                {
                    count = 0;
                    for (int j = 1; j < 24; j++)            //for each hour of the day
                    {
                        if (ArrayW1[k]->Rows[i]->Cells[j]->Value == "+")
                        {
                            count++;
                        }
                    }
                }
            }
            week1H = count;

            count = 0;
            for (int k = 0; k < 7; k++)         //for each day in week1
            {
                for (int i = 0; i < totalAppliances; i++)   //for each appliance
                {
                    count = 0;
                    for (int j = 1; j < 24; j++)            //for each hour of the day
                    {
                        if (ArrayW2[k]->Rows[i]->Cells[j]->Value == "+")
                        {
                            count++;
                        }
                    }
                }
            }
            week2H = count;

            count = 0;
            for (int k = 0; k < 7; k++)         //for each day in week1
            {
                for (int i = 0; i < totalAppliances; i++)   //for each appliance
                {
                    count = 0;
                    for (int j = 1; j < 24; j++)            //for each hour of the day
                    {
                        if (ArrayW3[k]->Rows[i]->Cells[j]->Value == "+")
                        {
                            count++;
                        }
                    }
                }
            }
            week3H = count;

            count = 0;
            for (int k = 0; k < 7; k++)         //for each day in week1
            {
                for (int i = 0; i < totalAppliances; i++)   //for each appliance
                {
                    count = 0;
                    for (int j = 1; j < 24; j++)            //for each hour of the day
                    {
                        if (ArrayW4[k]->Rows[i]->Cells[j]->Value == "+")
                        {
                            count++;
                        }
                    }
                }
            }
            week4H = count;

            // Data for the bar chart
            array<float>^ values = { week1H, week2H, week3H, week4H};
            array<String^>^ labels = { "Week 1", "Week 2", "Week 3", "Week 4"};

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
            int marginRight = 250;  // Space for legend
            int marginTop = 130;
            int marginBottom = 360;  // More space for rotated labels
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
            int barWidth = (width) / (numBars * 1.1);                       //width
            int barSpacing = barWidth / 4;  // Less spacing
            float scaleY = (height - 50) / maxValue;

            // Draw bars and labels
            System::Drawing::Font^ labelFont = gcnew System::Drawing::Font("Arial", 12);  // Bottom text
            System::Drawing::Font^ valueFont = gcnew System::Drawing::Font("Arial", 10);  // top text

            for (int i = 0; i < numBars; i++)
            {
                // Calculate bar dimensions
                int barX = x + (i * (barWidth + barSpacing))+25;
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
                    g->RotateTransform(-25);  // 45-degree angle
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
            g->DrawLine(axisPen, x, y + height - 40, x + width+80, y + height - 40);

            //text under bar chart
            Label^ BarLabel = gcnew Label();
            BarLabel->Text = L"Energy Consumed each\n\tHour";
            BarLabel->Font = gcnew System::Drawing::Font("Arial", 18, FontStyle::Bold);
            BarLabel->ForeColor = Color::FromArgb(69, 160, 227);
            BarLabel->AutoSize = true;
            BarLabel->Location = Point(x + 85, y + height + 10);
            BarLabel->TextAlign = ContentAlignment::MiddleCenter;
            this->Controls->Add(BarLabel);
        }
    };
