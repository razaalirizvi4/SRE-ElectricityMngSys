#include "pch.h"
#include "DevicesUserControl.h"
#include "sqlite3.h"
#include <vector>
#include<cstring>
#include<string>
#include <iostream>
#include <msclr/marshal_cppstd.h>
using namespace std;
string brand;
char* errmsg = nullptr;
vector <string> appliances;
string selectappliance;
namespace EUS {
    sqlite3* db;
    int exit;
    
    DevicesUserControl::DevicesUserControl(void)
    {
        InitializeComponent();

        // Set ComboBox properties
        comboBox->Location = System::Drawing::Point(50, 350);
        comboBox->Size = System::Drawing::Size(1000, 30);

        // Add items to the ComboBox
        comboBox->Items->Add("Press on the brand of your appliance,then select your appliance to add or delete,click other to add a different appliance.");
        // Set a default selected item
        comboBox->SelectedIndex = 0;
        // Add event handler for selection change
        comboBox->SelectedIndexChanged += gcnew EventHandler(this, &DevicesUserControl::comboBox_SelectedIndexChanged);
        // Add the ComboBox to the form
        this->Controls->Add(comboBox);
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
        Add_deletebutton(1190, 350);
        open_dbconnection();
    }
    int callback(void* data, int argc, char** argv, char** azColName) {
        // Extract the value of the first column (assuming one column is selected)
        if (argv[0]) {
            appliances.push_back(argv[0]); // Add the value to the global vector
        }
        else {
            appliances.push_back("NULL"); // Handle NULL values
        }

        return 0; // Returning 0 tells SQLite to continue processing
    }
    int brandcallback(void* data, int argc, char** argv, char** azColName) {
        // Extract the first value (assuming the query returns only one column)
        if (argc > 0 && argv[0]) {
            std::string* result = static_cast<std::string*>(data);
            *result = argv[0];  // Store the value in the passed string
        }
        return 0;  // Return 0 to indicate success
    }

    void DevicesUserControl::open_dbconnection()
    {
        exit = sqlite3_open("billmanagement.db", &db);
        if (exit != SQLITE_OK) {
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
        brand = "PEL";
        String^ brandptr = gcnew String(brand.c_str());
        MessageBox::Show(brandptr);
        UpdateComboBox();
        
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
        brand = "Dawlance";
        String^ brandptr = gcnew String(brand.c_str());
        MessageBox::Show(brandptr);
        UpdateComboBox();
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
        brand = "Haier";
        String^ brandptr = gcnew String(brand.c_str());
        MessageBox::Show(brandptr);
        UpdateComboBox();
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
        brand = "Lg";
        String^ brandptr = gcnew String(brand.c_str());
        MessageBox::Show(brandptr);
        UpdateComboBox();
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
        brand = "Samsung";
        String^ brandptr = gcnew String(brand.c_str());
        MessageBox::Show(brandptr);
        UpdateComboBox();
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
        brand = "Orient";
        String^ brandptr = gcnew String(brand.c_str());
        MessageBox::Show(brandptr);
        UpdateComboBox();
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
        brand = "Other";
        String^ brandptr = gcnew String(brand.c_str());
        MessageBox::Show(brandptr);
        UpdateComboBox();
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
        string sqlquery = "INSERT INTO USERS_APPLIANCE (userid, productname) VALUES (" + to_string(1) + ", '" + selectappliance + "');";
        const char* q = sqlquery.c_str();
        MessageBox::Show(gcnew String(q));
        string result;
        // Execute the query and pass the result variable to the callback
        if (sqlite3_exec(db, q, nullptr, nullptr, &errmsg) != SQLITE_OK) {
            String^ errorMsg = gcnew String(sqlite3_errmsg(db));
            String^ detailedMsg = gcnew String(errmsg ? errmsg : "No detailed error message");

            // Show error in a message box
            MessageBox::Show("Error executing query: " + errorMsg + "\nDetails: " + detailedMsg,
                "Query Execution Error", MessageBoxButtons::OK, MessageBoxIcon::Error);

            // Free error message if allocated
            if (errmsg) {
                sqlite3_free(errmsg);
            }
        }
        else
        {
            //MessageBox::Show("Query Ran Successfully" + gcnew String(result.c_str()));
        }

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
    string getbrandid()
    {
        string sqlquery = "SELECT brand_id FROM Brands WHERE brand_name = ' " + brand + " ' ;";
        const char* q = sqlquery.c_str();
       
        string result;
        // Execute the query and pass the result variable to the callback
        if (sqlite3_exec(db, q, brandcallback, &result, &errmsg) != SQLITE_OK) {
            String^ errorMsg = gcnew String(sqlite3_errmsg(db));
            String^ detailedMsg = gcnew String(errmsg ? errmsg : "No detailed error message");

            // Show error in a message box
            MessageBox::Show("Error executing query: " + errorMsg + "\nDetails: " + detailedMsg,
                "Query Execution Error", MessageBoxButtons::OK, MessageBoxIcon::Error);

            // Free error message if allocated
            if (errmsg) {
                sqlite3_free(errmsg);
            }
        }
        else
        {
           // MessageBox::Show("Query Ran Successfully" + gcnew String(result.c_str()));
        }
        return result;

    }
    void extractappliances()
    {
        string temp = getbrandid();
        string sqlquery = "SELECT product_name FROM Electrical_Appliances";
        const char* q = sqlquery.c_str();
        
        if (sqlite3_exec(db, q, callback, nullptr, &errmsg) != SQLITE_OK) {
            String^ errorMsg = gcnew String(sqlite3_errmsg(db));
            String^ detailedMsg = gcnew String(errmsg ? errmsg : "No detailed error message");

            // Show error in a message box
            MessageBox::Show("Error executing query: " + errorMsg + "\nDetails: " + detailedMsg,
                "Query Execution Error", MessageBoxButtons::OK, MessageBoxIcon::Error);

            // Free error message if allocated
            if (errmsg) {
                sqlite3_free(errmsg);
            }
        }
        else
        {
            MessageBox::Show("Query Ran Successfully");
        }
    }
    void DevicesUserControl::UpdateComboBox()
    {
        extractappliances();
        comboBox->Items->Clear();
        for (auto it = appliances.begin(); it != appliances.end(); ++it) {
            /*String^ t = gcnew String(it->c_str());
            MessageBox::Show(t);*/
            comboBox->Items->Add(gcnew System::String(it->c_str()));
        }
        MessageBox::Show("Combo Box Options set");
    }
    
    void DevicesUserControl :: comboBox_SelectedIndexChanged(Object^ sender, EventArgs^ e) 
    {
        ComboBox^ comboBox = dynamic_cast<ComboBox^>(sender);
        if (comboBox->SelectedIndex != 0)
        {
            selectappliance = msclr::interop::marshal_as<std::string>(comboBox->SelectedItem->ToString());
            String^ selectedItem = comboBox->SelectedItem->ToString();
            MessageBox::Show("Selected Item: " + selectedItem);
        }
    }

};


