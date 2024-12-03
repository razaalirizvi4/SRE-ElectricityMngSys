#include "pch.h"
#include "DashboardUserControl.h"
#include"week.h"

namespace EUS
{

    DashboardUserControl::DashboardUserControl(void)
    {
        InitializeComponent();
        this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &DashboardUserControl::MakePieChart);
        this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &DashboardUserControl::MakeLineChart);
        this->DoubleBuffered = true;  // Add this line for smoother rendering
    }

    DashboardUserControl::~DashboardUserControl() {
        if (components) {
            delete components;
        }
    }

    Button^ DashboardUserControl::CreateRoundedButton(String^ iconPath, int size, Point location) {
        Button^ button = gcnew Button();
        button->Size = System::Drawing::Size(size, size);
        button->Location = location;
        button->BackColor = DashboardStyles::PanelBackColor;
        button->FlatStyle = FlatStyle::Flat;
        button->FlatAppearance->BorderSize = 0;

        // Set the icon
        button->Image = Image::FromFile(iconPath);
        button->ImageAlign = ContentAlignment::MiddleCenter;

        // Apply rounded corners
        System::Drawing::Drawing2D::GraphicsPath^ path = RoundedRectangles::RoundedRectangle::Create(
            0, 0, size, size, size / 2,
            RoundedRectangles::RoundedRectangle::RectangleCorners::All
        );
        button->Region = gcnew System::Drawing::Region(path);

        return button;
    }

    Label^ DashboardUserControl::CreateLabel(String^ text, System::Drawing::Font^ font, Color color, int width, int height, Point location) {
        Label^ label = gcnew Label();
        label->Text = text;
        label->Font = font;
        label->ForeColor = color;
        label->Size = System::Drawing::Size(width, height);
        label->Location = location;
        label->TextAlign = ContentAlignment::MiddleCenter; // Center-align text
        return label;
    }

    Panel^ DashboardUserControl::CreatePanel(PanelConfig config) {
        Panel^ panel = gcnew Panel();
        panel->Size = System::Drawing::Size(config.Width, config.Height);
        panel->Location = config.Location;
        panel->BackColor = config.BackColor;

        // Title
        if (!String::IsNullOrEmpty(config.Title)) {
            Label^ titleLabel = CreateLabel(config.Title,
                DashboardStyles::TitleFont,
                Color::White,
                panel->Width,
                30,
                Point(0, 10)); // Offset for title
            panel->Controls->Add(titleLabel);
        }

        // Content
        if (!String::IsNullOrEmpty(config.Content)) {
            cli::array<String^>^ contentLines = config.Content->Split('\n');
            int yOffset = config.ContentYOffset;

            for each (String ^ line in contentLines) {
                Label^ lineLabel = CreateLabel(line,
                    DashboardStyles::ContentFont,
                    Color::White,
                    panel->Width - 20,
                    25, // Set the height of each line label
                    Point(10, yOffset));
                lineLabel->AutoSize = false;
                panel->Controls->Add(lineLabel);
                yOffset += 25 + config.LineSpacing;
            }
        }

        ApplyRoundedRectangleToPanel(panel, DashboardStyles::DefaultCornerRadius);
        return panel;
    }

    void DashboardUserControl::ApplyRoundedRectangleToPanel(Panel^ panel, int radius) {
        System::Drawing::Drawing2D::GraphicsPath^ path = RoundedRectangles::RoundedRectangle::Create(
            0, 0, panel->Width, panel->Height, radius,
            RoundedRectangles::RoundedRectangle::RectangleCorners::All
        );
        panel->Region = gcnew System::Drawing::Region(path);
    }

    Panel^ DashboardUserControl::CreateTopSection() {
        // Create a container for the top section
        Panel^ topSectionPanel = gcnew Panel();
        topSectionPanel->Size = System::Drawing::Size(1420, this->Height / 3);
        topSectionPanel->Location = Point(DashboardStyles::DefaultMargin, DashboardStyles::DefaultMargin - 30);
        topSectionPanel->BackColor = DashboardStyles::MainBackColor;

        ApplyRoundedRectangleToPanel(topSectionPanel, DashboardStyles::DefaultCornerRadius);

        int boxWidth = (topSectionPanel->Width - DashboardStyles::DefaultSpacing - 90) / 2;
        int boxHeight = topSectionPanel->Height - DashboardStyles::DefaultSpacing2 - 50;

        // Determine current time and whether it's within peak hours
        DateTime now = DateTime::Now;
        int currentHour = now.Hour;
        int startHour = timetoInt(UserData::userpeakstart);
        int endHour = timetoInt(UserData::userpeakend);

        double currentRate = (currentHour >= startHour && currentHour < endHour)
            ? UserData::peakrate
            : UserData::offpeakrate;

        // vars
        int bill = static_cast<int>(GlobalObjectsRaza::Globals::unmanagedGlobals->bill);
        int units = bill / currentRate;

        // First Box Configuration
        PanelConfig box1Config;
        box1Config.Width = boxWidth;
        box1Config.Height = boxHeight;
        box1Config.Location = Point(0, 0);
        box1Config.BackColor = DashboardStyles::PanelBackColor;
        box1Config.LineSpacing = 3;
        box1Config.ContentYOffset = 50;
        box1Config.Title = "Energy Consumption Overview";
        box1Config.Content = gcnew String(
            ("Daily Usage: " + std::to_string(units) + " kWh\n" +
                "Todays Units: " + std::to_string(units) + "\n" +
                "Peak Today: " + UserData::userpeakstart + "\n").c_str());

        // Second Box Configuration
        PanelConfig box2Config = box1Config;
        box2Config.Location = Point(boxWidth + DashboardStyles::DefaultSpacing + 10, 0);
        box2Config.Title = "Current Rate Info";

        box2Config.Content = gcnew String(
            ("Current Rate: Pkr " + std::to_string(static_cast<int>(UserData::offpeakrate)) + "/kWh\nPeak Hours: " + UserData::userpeakstart + " - " + UserData::userpeakend + "\n" +
                "Today's Est. Cost: Pkr " + std::to_string(bill)).c_str());

        topSectionPanel->Controls->Add(CreatePanel(box1Config));
        topSectionPanel->Controls->Add(CreatePanel(box2Config));

        return topSectionPanel;
    }

    Panel^ DashboardUserControl::CreateBottomSection() {
        energySavingTips = gcnew cli::array<String^> {
            "Schedule laundry for off-peak hours.",
                "Turn off lights when not in use.",
                "Unplug devices that are not being used.",
                "Use a programmable thermostat to save energy.",
                "Seal windows and doors to reduce energy waste.",
                "Set your water heater to 50°C for efficiency.",
                "Use energy-efficient LED light bulbs.",
                "Clean or replace air filters regularly."
        };
        currentTipIndex = 4;

        // Create a container for the bottom section
        Panel^ bottomSectionPanel = gcnew Panel();
        bottomSectionPanel->Size = System::Drawing::Size(1430, this->Height / 5);
        bottomSectionPanel->Location = Point(DashboardStyles::DefaultMargin, 685);
        bottomSectionPanel->BackColor = DashboardStyles::MainBackColor;

        ApplyRoundedRectangleToPanel(bottomSectionPanel, DashboardStyles::DefaultCornerRadius);

        // Add rounded buttons
        Button^ prevButton = CreateRoundedButton("icon_left.png", 75, Point(0, bottomSectionPanel->Height / 2 - 40));
        Button^ nextButton = CreateRoundedButton("icon_right.png", 75, Point(bottomSectionPanel->Width - 160, bottomSectionPanel->Height / 2 - 40));

        // Add central rounded box
        tipsPanelConfig;
        tipsPanelConfig.Width = bottomSectionPanel->Width - 450;
        tipsPanelConfig.Height = bottomSectionPanel->Height - 20;
        tipsPanelConfig.Location = Point(180, 10);
        tipsPanelConfig.BackColor = DashboardStyles::PanelBackColor;
        tipsPanelConfig.LineSpacing = 5;
        tipsPanelConfig.ContentYOffset = 55;
        tipsPanelConfig.Title = "Energy Saving Tips";
        tipsPanelConfig.Content = energySavingTips[currentTipIndex];

        Panel^ tipsPanel = CreatePanel(tipsPanelConfig);

        // Add cycling logic
        prevButton->Click += gcnew EventHandler(this, &DashboardUserControl::ShowPreviousTip);
        nextButton->Click += gcnew EventHandler(this, &DashboardUserControl::ShowNextTip);

        bottomSectionPanel->Controls->Add(prevButton);
        bottomSectionPanel->Controls->Add(nextButton);
        bottomSectionPanel->Controls->Add(tipsPanel);

        return bottomSectionPanel;
    }

    void DashboardUserControl::InitializeComponent(void) {
        this->components = gcnew System::ComponentModel::Container();
        this->Size = System::Drawing::Size(1480, 685);

        this->Dock = DockStyle::Fill;
        this->BackColor = DashboardStyles::MainBackColor;

        // Create and add the top section
        Panel^ topSectionPanel = CreateTopSection();
        this->Controls->Add(topSectionPanel);

        // Create and add the bottom section
        Panel^ bottomSectionPanel = CreateBottomSection();
        this->Controls->Add(bottomSectionPanel);
    }

    // Tip cycling logic
    void DashboardUserControl::ShowPreviousTip(Object^ sender, EventArgs^ e) {
        if (energySavingTips->Length == 0) return;

        currentTipIndex = (currentTipIndex - 1 + energySavingTips->Length) % energySavingTips->Length;
        UpdateTipContent();
    }

    void DashboardUserControl::ShowNextTip(Object^ sender, EventArgs^ e) {
        if (energySavingTips->Length == 0) return;

        currentTipIndex = (currentTipIndex + 1) % energySavingTips->Length;
        UpdateTipContent();
    }

    void DashboardUserControl::UpdateTipContent() {
        // Find the central panel and update its content
        Panel^ bottomSectionPanel = dynamic_cast<Panel^>(this->Controls[1]);
        if (bottomSectionPanel) {
            Panel^ tipsPanel = dynamic_cast<Panel^>(bottomSectionPanel->Controls[2]);
            if (tipsPanel && tipsPanel->Controls->Count > 0) {
                Label^ contentLabel = dynamic_cast<Label^>(tipsPanel->Controls[1]);
                if (contentLabel) {
                    contentLabel->Text = energySavingTips[currentTipIndex];
                }
                return;
            }
        }
    }

    void DashboardUserControl::MakePieChart(Object^ sender, PaintEventArgs^ e)
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

        cli::array<DataGridView^>^ ArrayW1 = gcnew cli::array<DataGridView^>(7);
        ArrayW1[0] = week1->Gtable1;
        ArrayW1[1] = week1->Gtable2;
        ArrayW1[2] = week1->Gtable3;
        ArrayW1[3] = week1->Gtable4;
        ArrayW1[4] = week1->Gtable5;
        ArrayW1[5] = week1->Gtable6;
        ArrayW1[6] = week1->GTable7;

        cli::array<DataGridView^>^ ArrayW2 = gcnew cli::array<DataGridView^>(7);
        ArrayW2[0] = week2->Gtable1;
        ArrayW2[1] = week2->Gtable2;
        ArrayW2[2] = week2->Gtable3;
        ArrayW2[3] = week2->Gtable4;
        ArrayW2[4] = week2->Gtable5;
        ArrayW2[5] = week2->Gtable6;
        ArrayW2[6] = week2->GTable7;

        cli::array<DataGridView^>^ ArrayW3 = gcnew cli::array<DataGridView^>(7);
        ArrayW3[0] = week3->Gtable1;
        ArrayW3[1] = week3->Gtable2;
        ArrayW3[2] = week3->Gtable3;
        ArrayW3[3] = week3->Gtable4;
        ArrayW3[4] = week3->Gtable5;
        ArrayW3[5] = week3->Gtable6;
        ArrayW3[6] = week3->GTable7;

        cli::array<DataGridView^>^ ArrayW4 = gcnew cli::array<DataGridView^>(7);
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
        cli::array<float>^ values = { topFourAppliancesHours[0],topFourAppliancesHours[1],topFourAppliancesHours[2],topFourAppliancesHours[3] };
        cli::array<String^>^ labels = { week1->Gtable1->Rows[topFourAppliancesIndexes[0]]->Cells[0]->Value->ToString(), week1->Gtable1->Rows[topFourAppliancesIndexes[1]]->Cells[0]->Value->ToString(), week1->Gtable1->Rows[topFourAppliancesIndexes[2]]->Cells[0]->Value->ToString(), week1->Gtable1->Rows[topFourAppliancesIndexes[3]]->Cells[0]->Value->ToString() };

        //alternating theme-matching colours
        int startR = 0, startG = 91, startB = 156;
        int endR = 99, endG = 190, endB = 255;

        int numSlices = values->Length;
        cli::array<Color>^ colors = gcnew cli::array<Color>(numSlices);

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
        int x = 215;
        int y = 275;
        int width = 300;
        int height = 300;
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
                legendY - 3
            );

            startAngle += sweepAngle;
        }

        //text under pie chart
        Label^ PieLabel = gcnew Label();
        PieLabel->Text = L"Top Most Energy Consuming\n\tAppliances";
        PieLabel->Font = gcnew System::Drawing::Font("Arial", 18, FontStyle::Bold);
        PieLabel->ForeColor = Color::FromArgb(69, 160, 227);
        PieLabel->AutoSize = true;
        PieLabel->Location = Point(x - 50, y + 280);
        PieLabel->TextAlign = ContentAlignment::MiddleCenter;
        this->Controls->Add(PieLabel);
    }

    void DashboardUserControl::MakeLineChart(Object^ sender, PaintEventArgs^ e)
    {

        Week::Tables^ week1 = GlobalObjects::Globals::monthlyTables[0];

        int totalAppliances = week1->Gtable1->Rows->Count;

        DataGridView^ ArrayW1 = gcnew DataGridView;

        ArrayW1 = week1->Gtable1;
        int* eachHourEnergy = new int[24];

        // Calculation logic
        int count = 0;
        for (int j = 1; j < 24; j++)    //each hour
        {
            count = 0;
            for (int i = 0; i < totalAppliances; i++)       //each appliance
            {
                if (ArrayW1->Rows[i]->Cells[j]->Value == "+")
                {
                    count++;
                }
            }
            eachHourEnergy[j-1] = count;
        }

        // (previous code blocks omitted for brevity, would be similar to W1 calculation)

            // Sample data with four lines
            cli::array<float>^ val1 = { eachHourEnergy[0], eachHourEnergy[1],eachHourEnergy[2], eachHourEnergy[3],eachHourEnergy[4],eachHourEnergy[5],eachHourEnergy[6],eachHourEnergy[7],eachHourEnergy[8],eachHourEnergy[9],eachHourEnergy[10],eachHourEnergy[11],eachHourEnergy[12],eachHourEnergy[13],eachHourEnergy[14],eachHourEnergy[15],eachHourEnergy[16],eachHourEnergy[17],eachHourEnergy[18],eachHourEnergy[19],eachHourEnergy[20],eachHourEnergy[21],eachHourEnergy[22] };
            cli::array<String^>^ labels = { "00","01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22","23"};

            // Calculate colors for the lines
            cli::array<Color>^ colorArray = {
                Color::FromArgb(46, 138, 205),   // Blue
            };

            // Set up graphics
            Graphics^ g = e->Graphics;
            g->SmoothingMode = Drawing2D::SmoothingMode::AntiAlias;

            // Define chart area (same as before)
            int marginLeft = 775;
            int marginRight = 100;
            int marginTop = 220;
            int marginBottom = 200;
            int x = marginLeft;
            int y = marginTop;
            int width = this->Width - (marginLeft + marginRight);
            int height = this->Height - (marginTop + marginBottom);

            // Calculate the maximum value for scaling
            float maxValue = 0;
            for each (float value in val1) if (value > maxValue) maxValue = value;

            // Calculate line properties
            int lineWidth = 3;
            float scaleY = (height - 50) / maxValue;

            // Draw lines and labels
            System::Drawing::Font^ labelFont = gcnew System::Drawing::Font("Arial", 12);

            // Draw four lines
            cli::array<cli::array<PointF>^>^ linesPoints = gcnew cli::array<cli::array<PointF>^>(1);
            cli::array<cli::array<float>^>^ valArrays = { val1 };

            for (int lineIndex = 0; lineIndex < 1; lineIndex++)
            {
                linesPoints[lineIndex] = gcnew cli::array<PointF>(valArrays[lineIndex]->Length);
                for (int i = 0; i < valArrays[lineIndex]->Length; i++)
                {
                    linesPoints[lineIndex][i] = PointF(
                        x + (i * (width / (valArrays[lineIndex]->Length - 1))),
                        y + height - (valArrays[lineIndex][i] * scaleY)
                    );
                }
                g->DrawLines(gcnew Pen(colorArray[lineIndex], lineWidth), linesPoints[lineIndex]);
            }

            // Draw axes and labels (same as before)
            Pen^ axisPen = gcnew Pen(Color::Black, 2);
            g->DrawLine(axisPen, x, y + height, x + width, y + height);
            g->DrawLine(axisPen, x, y, x, y + height);

            for (int i = 0; i < labels->Length; i++) {
                SizeF labelSize = g->MeasureString(labels[i], labelFont);
                g->DrawString(labels[i],
                    labelFont,
                    Brushes::Black,
                    x + (i * (width / (labels->Length - 1))) - (labelSize.Width / 2),
                    y + height + 10);
            }
    }
    
}
