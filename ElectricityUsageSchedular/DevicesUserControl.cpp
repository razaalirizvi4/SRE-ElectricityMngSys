#include "pch.h"
#include "DevicesUserControl.h"
#include "sqlite3.h"
#include <iostream>
namespace EUS {
    sqlite3* db;
    int exit;
    
    DevicesUserControl::DevicesUserControl(void)
    {
        InitializeComponent();
    }

    DevicesUserControl::~DevicesUserControl()
    {
        if (components)
        {
            delete components;
        }
    }

    void DevicesUserControl::InitializeComponent(void)
    {
        this->components = gcnew System::ComponentModel::Container();
        this->Size = System::Drawing::Size(600, 400);
        this->BackColor = Color::FromArgb(235, 245, 235);

        Label^ label = gcnew Label();
        label->Text = L"Devices Page";
        label->Font = gcnew System::Drawing::Font("Arial", 18, FontStyle::Bold);
        label->ForeColor = Color::FromArgb(218, 165, 32);
        label->Dock = DockStyle::Top;
        label->TextAlign = ContentAlignment::MiddleCenter;
        this->Controls->Add(label);
        AddButton1(10, 50);
        AddButton2(500, 50);
        AddButton3(990, 50);
        AddButton4(10, 150);
        AddButton5(500, 150);
        AddButton6(990, 150);
        AddButton7(500, 250);
        Add_addbutton(1090, 350);
        AddComboBox();
        Add_deletebutton(1190, 350);
        open_dbconnection();
    }
    void DevicesUserControl::open_dbconnection()
    {
        exit = sqlite3_open("bill management.db", &db);
        if (exit) {
            MessageBox::Show("Connection Failed");
        }
        else {
            MessageBox::Show("DB connected successfully");
        }
    }
    void DevicesUserControl::AddButton1(int xpos, int ypos)
    {
        // Create a new button
        Button^ myButton = gcnew Button();

        // Set button properties
        myButton->Text = "PEL";
        myButton->Size = System::Drawing::Size(400, 50);
        myButton->Location = System::Drawing::Point(xpos, ypos);
        myButton->BackColor = Color::FromArgb(69, 160, 227);

        // Add click event handler
        myButton->Click += gcnew EventHandler(this, &DevicesUserControl::OnButtonClick1);

        // Add the button to the form
        this->Controls->Add(myButton);
    }
    void DevicesUserControl::OnButtonClick1(Object^ sender, EventArgs^ e)
    {
        MessageBox::Show("Button clicked!");
    }
    void DevicesUserControl::AddButton2(int xpos, int ypos)
    {
        // Create a new button
        Button^ myButton = gcnew Button();

        // Set button properties
        myButton->Text = "DAWLANCE";
        myButton->Size = System::Drawing::Size(400, 50);
        myButton->Location = System::Drawing::Point(xpos, ypos);
        myButton->BackColor = Color::FromArgb(69, 160, 227);

        // Add click event handler
        myButton->Click += gcnew EventHandler(this, &DevicesUserControl::OnButtonClick2);

        // Add the button to the form
        this->Controls->Add(myButton);
    }
    void DevicesUserControl::OnButtonClick2(Object^ sender, EventArgs^ e)
    {
        MessageBox::Show("Button clicked!");
    }
    void DevicesUserControl::AddButton3(int xpos, int ypos)
    {
        // Create a new button
        Button^ myButton = gcnew Button();

        // Set button properties
        myButton->Text = "HAIER";
        myButton->Size = System::Drawing::Size(400, 50);
        myButton->Location = System::Drawing::Point(xpos, ypos);
        myButton->BackColor = Color::FromArgb(69, 160, 227);

        // Add click event handler
        myButton->Click += gcnew EventHandler(this, &DevicesUserControl::OnButtonClick3);

        // Add the button to the form
        this->Controls->Add(myButton);
    }
    void DevicesUserControl::OnButtonClick3(Object^ sender, EventArgs^ e)
    {
        MessageBox::Show("Button clicked!");
    }
    void DevicesUserControl::AddButton4(int xpos, int ypos)
    {
        // Create a new button
        Button^ myButton = gcnew Button();

        // Set button properties
        myButton->Text = "LG";
        myButton->Size = System::Drawing::Size(400, 50);
        myButton->Location = System::Drawing::Point(xpos, ypos);
        myButton->BackColor = Color::FromArgb(69, 160, 227);

        // Add click event handler
        myButton->Click += gcnew EventHandler(this, &DevicesUserControl::OnButtonClick4);

        // Add the button to the form
        this->Controls->Add(myButton);
    }
    void DevicesUserControl::OnButtonClick4(Object^ sender, EventArgs^ e)
    {
        MessageBox::Show("Button clicked!");
    }
    void DevicesUserControl::AddButton5(int xpos, int ypos)
    {
        // Create a new button
        Button^ myButton = gcnew Button();

        // Set button properties
        myButton->Text = "Samsung";
        myButton->Size = System::Drawing::Size(400, 50);
        myButton->Location = System::Drawing::Point(xpos, ypos);
        myButton->BackColor = Color::FromArgb(69, 160, 227);

        // Add click event handler
        myButton->Click += gcnew EventHandler(this, &DevicesUserControl::OnButtonClick5);

        // Add the button to the form
        this->Controls->Add(myButton);
    }
    void DevicesUserControl::OnButtonClick5(Object^ sender, EventArgs^ e)
    {
        MessageBox::Show("Button clicked!");
    }
    void DevicesUserControl::AddButton6(int xpos, int ypos)
    {
        // Create a new button
        Button^ myButton = gcnew Button();

        // Set button properties
        myButton->Text = "Orient";
        myButton->Size = System::Drawing::Size(400, 50);
        myButton->Location = System::Drawing::Point(xpos, ypos);
        myButton->BackColor = Color::FromArgb(69, 160, 227);

        // Add click event handler
        myButton->Click += gcnew EventHandler(this, &DevicesUserControl::OnButtonClick6);

        // Add the button to the form
        this->Controls->Add(myButton);
    }
    void DevicesUserControl::OnButtonClick6(Object^ sender, EventArgs^ e)
    {
        MessageBox::Show("Button clicked!");
    }
    void DevicesUserControl::AddButton7(int xpos, int ypos)
    {
        // Create a new button
        Button^ myButton = gcnew Button();

        // Set button properties
        myButton->Text = "Other";
        myButton->Size = System::Drawing::Size(400, 50);
        myButton->Location = System::Drawing::Point(xpos, ypos);
        myButton->BackColor = Color::FromArgb(69, 160, 227);

        // Add click event handler
        myButton->Click += gcnew EventHandler(this, &DevicesUserControl::OnButtonClick7);

        // Add the button to the form
        this->Controls->Add(myButton);
    }
    void DevicesUserControl::OnButtonClick7(Object^ sender, EventArgs^ e)
    {
        MessageBox::Show("Button clicked!");
    }
    void DevicesUserControl::Add_addbutton(int xpos, int ypos)
    {
        Button^ myButton = gcnew Button();

        // Set button properties
        myButton->Text = "Add Appliance";
        myButton->Size = System::Drawing::Size(100, 30);
        myButton->Location = System::Drawing::Point(xpos, ypos);
        myButton->BackColor = Color::FromArgb(69, 160, 227);

        // Add click event handler
        myButton->Click += gcnew EventHandler(this, &DevicesUserControl::addbuttonclick);

        // Add the button to the form
        this->Controls->Add(myButton);
    }
    void DevicesUserControl::addbuttonclick(Object^ sender, EventArgs^ e)
    {
        MessageBox::Show("Appliance Added !");
    }
    void DevicesUserControl::Add_deletebutton(int xpos, int ypos)
    {
        Button^ myButton = gcnew Button();

        // Set button properties
        myButton->Text = "Delete Appliance";
        myButton->Size = System::Drawing::Size(100, 30);
        myButton->Location = System::Drawing::Point(xpos, ypos);
        myButton->BackColor = Color::FromArgb(69, 160, 227);

        // Add click event handler
        myButton->Click += gcnew EventHandler(this, &DevicesUserControl::delbuttonclick);

        // Add the button to the form
        this->Controls->Add(myButton);
    }
    void DevicesUserControl::delbuttonclick(Object^ sender, EventArgs^ e)
    {
        MessageBox::Show("Appliance deleted !");
    }
    void DevicesUserControl::AddComboBox()
    {
        ComboBox^ comboBox = gcnew ComboBox();

        // Set ComboBox properties
        comboBox->Location = System::Drawing::Point(50, 350);
        comboBox->Size = System::Drawing::Size(1000, 30);

        // Add items to the ComboBox
        comboBox->Items->Add("Press on the brand of your appliance,then select your appliance to add or delete,click other to add a different appliance.");
        comboBox->Items->Add("Option 1");
        comboBox->Items->Add("Option 2");
        comboBox->Items->Add("Option 3");

        // Set a default selected item
        comboBox->SelectedIndex = 0;

        // Add event handler for selection change
        comboBox->SelectedIndexChanged += gcnew EventHandler(this, &DevicesUserControl::comboBox_SelectedIndexChanged);

        // Add the ComboBox to the form
        this->Controls->Add(comboBox);
    }
    
    void DevicesUserControl :: comboBox_SelectedIndexChanged(Object^ sender, EventArgs^ e) 
    {
        ComboBox^ comboBox = dynamic_cast<ComboBox^>(sender);
        if (comboBox->SelectedIndex != 0)
        {
            String^ selectedItem = comboBox->SelectedItem->ToString();
            MessageBox::Show("Selected Item: " + selectedItem);
        }
    }
};


