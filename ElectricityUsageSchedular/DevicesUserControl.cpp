#include "pch.h"
#include "GlobalFunctions.h"
#include "DevicesUserControl.h"
#include <sqlite3.h>
#include <vector>
#include<cstring>
#include<string>
#include <iostream>
#include <msclr/marshal_cppstd.h>
#include<cliext/vector>
#include "globals2.h"
using namespace System;
using namespace System::Drawing;
using namespace System::Drawing::Drawing2D;
using namespace System::Windows::Forms;
using namespace std;
int priority = 0;
string brand;
char* errmsg = nullptr;
vector <string> appliances;
string selectappliance;
string prompt4 = "runs thrice a week";
string prompt1 = "runs every day : seldom";
string prompt3 = "runs every day : critical";
string prompt2 = "runs every day : most of the day";
string prompt5 = "runs once a week";
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
        this->BackColor = Color::FromArgb(234, 237, 244);

        Label^ label = gcnew Label();

        label->Text = L"Devices Page";
        label->Font = gcnew System::Drawing::Font("Arial", 18, FontStyle::Bold);
        label->ForeColor = Color::FromArgb(67, 24, 255);
        label->Dock = DockStyle::Top;
        label->TextAlign = ContentAlignment::MiddleCenter;
        this->Controls->Add(label);
        AddButton1(50+30, 50);
        AddButton2(500+30, 50);
        AddButton3(990+30, 50);
        AddButton4(50+30, 450);
        AddButton5(500+30, 450);
        AddButton6(990+30, 450);
       
        open_dbconnection();
    }
    
     int delcallback(void* data, int argc, char** argv, char** azColName) 
     {
        for (int i = 0; i < argc; i++) {
            std::cout << azColName[i] << ": " << (argv[i] ? argv[i] : "NULL") << std::endl;
        }
        std::cout << std::endl;
        return 0;
    }
    void MyDialogForm:: push_app()
    {
        get_appliances();
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
        Image^ buttonimage = Image::FromFile("pel.png");

        // Set button properties
        myButton->Size = System::Drawing::Size(250, 250);
        myButton->Location = System::Drawing::Point(xpos, ypos);
        myButton->BackColor = Color::FromArgb(255, 255, 255); // Set button background to white
        myButton->Image = buttonimage;

        // Remove borders completely
        myButton->FlatAppearance->BorderSize = 0;
        myButton->FlatAppearance->MouseDownBackColor = Color::Transparent;
        myButton->FlatAppearance->MouseOverBackColor = Color::Transparent;

        // Set rounded corners
        int cornerRadius = 50;
        GraphicsPath^ path = gcnew GraphicsPath();
        path->AddArc(0, 0, cornerRadius, cornerRadius, 180, 90); // Top-left
        path->AddArc(myButton->Width - cornerRadius, 0, cornerRadius, cornerRadius, 270, 90); // Top-right
        path->AddArc(myButton->Width - cornerRadius, myButton->Height - cornerRadius, cornerRadius, cornerRadius, 0, 90); // Bottom-right
        path->AddArc(0, myButton->Height - cornerRadius, cornerRadius, cornerRadius, 90, 90); // Bottom-left
        path->CloseFigure();
        myButton->Region = gcnew System::Drawing::Region(path);

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
        MyDialogForm^ dialog = gcnew MyDialogForm();
        dialog->ShowDialog();
    }
    void DevicesUserControl::AddButton2(int xpos, int ypos)
    {
        Button^ myButton = gcnew Button();
        Image^ buttonimage = Image::FromFile("dawlance.png");

        // Set button properties
        myButton->Size = System::Drawing::Size(250, 250);
        myButton->Location = System::Drawing::Point(xpos, ypos);
        myButton->BackColor = Color::FromArgb(255, 255, 255); // Set button background to white
        myButton->Image = buttonimage;

        // Remove borders completely
        myButton->FlatAppearance->BorderSize = 0;
        myButton->FlatAppearance->MouseDownBackColor = Color::Transparent;
        myButton->FlatAppearance->MouseOverBackColor = Color::Transparent;

        // Set rounded corners
        int cornerRadius = 50;
        GraphicsPath^ path = gcnew GraphicsPath();
        path->AddArc(0, 0, cornerRadius, cornerRadius, 180, 90); // Top-left
        path->AddArc(myButton->Width - cornerRadius, 0, cornerRadius, cornerRadius, 270, 90); // Top-right
        path->AddArc(myButton->Width - cornerRadius, myButton->Height - cornerRadius, cornerRadius, cornerRadius, 0, 90); // Bottom-right
        path->AddArc(0, myButton->Height - cornerRadius, cornerRadius, cornerRadius, 90, 90); // Bottom-left
        path->CloseFigure();
        myButton->Region = gcnew System::Drawing::Region(path);

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
        MyDialogForm^ dialog = gcnew MyDialogForm();
        dialog->ShowDialog();
    }
    void DevicesUserControl::AddButton3(int xpos, int ypos)
    {
        // Create a new button
        Button^ myButton = gcnew Button();
        Image^ buttonimage = Image::FromFile("haier.png");

        // Set button properties
        myButton->Size = System::Drawing::Size(250, 250);
        myButton->Location = System::Drawing::Point(xpos, ypos);
        myButton->BackColor = Color::FromArgb(255, 255, 255); // Set button background to white
        myButton->Image = buttonimage;

        // Remove borders completely
        myButton->FlatAppearance->BorderSize = 0;
        myButton->FlatAppearance->MouseDownBackColor = Color::Transparent;
        myButton->FlatAppearance->MouseOverBackColor = Color::Transparent;

        // Set rounded corners
        int cornerRadius = 50;
        GraphicsPath^ path = gcnew GraphicsPath();
        path->AddArc(0, 0, cornerRadius, cornerRadius, 180, 90); // Top-left
        path->AddArc(myButton->Width - cornerRadius, 0, cornerRadius, cornerRadius, 270, 90); // Top-right
        path->AddArc(myButton->Width - cornerRadius, myButton->Height - cornerRadius, cornerRadius, cornerRadius, 0, 90); // Bottom-right
        path->AddArc(0, myButton->Height - cornerRadius, cornerRadius, cornerRadius, 90, 90); // Bottom-left
        path->CloseFigure();
        myButton->Region = gcnew System::Drawing::Region(path);
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
        MyDialogForm^ dialog = gcnew MyDialogForm();
        dialog->ShowDialog();
    }
    void DevicesUserControl::AddButton4(int xpos, int ypos)
    {
        Button^ myButton = gcnew Button();
        Image^ buttonimage = Image::FromFile("lg.png");

        // Set button properties
        myButton->Size = System::Drawing::Size(250, 250);
        myButton->Location = System::Drawing::Point(xpos, ypos);
        myButton->BackColor = Color::FromArgb(255, 255, 255); // Set button background to white
        myButton->Image = buttonimage;

        // Remove borders completely
        myButton->FlatAppearance->BorderSize = 0;
        myButton->FlatAppearance->MouseDownBackColor = Color::Transparent;
        myButton->FlatAppearance->MouseOverBackColor = Color::Transparent;

        // Set rounded corners
        int cornerRadius = 50;
        GraphicsPath^ path = gcnew GraphicsPath();
        path->AddArc(0, 0, cornerRadius, cornerRadius, 180, 90); // Top-left
        path->AddArc(myButton->Width - cornerRadius, 0, cornerRadius, cornerRadius, 270, 90); // Top-right
        path->AddArc(myButton->Width - cornerRadius, myButton->Height - cornerRadius, cornerRadius, cornerRadius, 0, 90); // Bottom-right
        path->AddArc(0, myButton->Height - cornerRadius, cornerRadius, cornerRadius, 90, 90); // Bottom-left
        path->CloseFigure();
        myButton->Region = gcnew System::Drawing::Region(path);

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
        MyDialogForm^ dialog = gcnew MyDialogForm();
        dialog->ShowDialog();
    }
    void DevicesUserControl::AddButton5(int xpos, int ypos)
    {
        Button^ myButton = gcnew Button();
        Image^ buttonimage = Image::FromFile("samsung.png");

        // Set button properties
        myButton->Size = System::Drawing::Size(250, 250);
        myButton->Location = System::Drawing::Point(xpos, ypos);
        myButton->BackColor = Color::FromArgb(255, 255, 255); // Set button background to white
        myButton->Image = buttonimage;

        // Remove borders completely
        myButton->FlatAppearance->BorderSize = 0;
        myButton->FlatAppearance->MouseDownBackColor = Color::Transparent;
        myButton->FlatAppearance->MouseOverBackColor = Color::Transparent;

        // Set rounded corners
        int cornerRadius = 50;
        GraphicsPath^ path = gcnew GraphicsPath();
        path->AddArc(0, 0, cornerRadius, cornerRadius, 180, 90); // Top-left
        path->AddArc(myButton->Width - cornerRadius, 0, cornerRadius, cornerRadius, 270, 90); // Top-right
        path->AddArc(myButton->Width - cornerRadius, myButton->Height - cornerRadius, cornerRadius, cornerRadius, 0, 90); // Bottom-right
        path->AddArc(0, myButton->Height - cornerRadius, cornerRadius, cornerRadius, 90, 90); // Bottom-left
        path->CloseFigure();
        myButton->Region = gcnew System::Drawing::Region(path);
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
        MyDialogForm^ dialog = gcnew MyDialogForm();
        dialog->ShowDialog();
    }
    void DevicesUserControl::AddButton6(int xpos, int ypos)
    {
        // Create a new button
        Button^ myButton = gcnew Button();
        Image^ buttonimage = Image::FromFile("orient.png");

        // Set button properties
        myButton->Size = System::Drawing::Size(250, 250);
        myButton->Location = System::Drawing::Point(xpos, ypos);
        myButton->BackColor = Color::FromArgb(255, 255, 255); // Set button background to white
        myButton->Image = buttonimage;

        // Remove borders completely
        myButton->FlatAppearance->BorderSize = 0;
        myButton->FlatAppearance->MouseDownBackColor = Color::Transparent;
        myButton->FlatAppearance->MouseOverBackColor = Color::Transparent;

        // Set rounded corners
        int cornerRadius = 50;
        GraphicsPath^ path = gcnew GraphicsPath();
        path->AddArc(0, 0, cornerRadius, cornerRadius, 180, 90); // Top-left
        path->AddArc(myButton->Width - cornerRadius, 0, cornerRadius, cornerRadius, 270, 90); // Top-right
        path->AddArc(myButton->Width - cornerRadius, myButton->Height - cornerRadius, cornerRadius, cornerRadius, 0, 90); // Bottom-right
        path->AddArc(0, myButton->Height - cornerRadius, cornerRadius, cornerRadius, 90, 90); // Bottom-left
        path->CloseFigure();
        myButton->Region = gcnew System::Drawing::Region(path);
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
        MyDialogForm^ dialog = gcnew MyDialogForm();
        dialog->ShowDialog();
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
        MyDialogForm^ dialog = gcnew MyDialogForm();
        dialog->ShowDialog();
    }
    void MyDialogForm::Add_addbutton(int xpos, int ypos)
    {
        Button^ myButton = gcnew Button();

        // Set button properties
        myButton->Text = "Add Appliance";
        myButton->Size = System::Drawing::Size(100, 30);
        myButton->Location = System::Drawing::Point(xpos, ypos);
        myButton->BackColor = Color::FromArgb(69, 160, 227);

        // Add click event handler
        myButton->Click += gcnew EventHandler(this, &MyDialogForm::addbuttonclick);

        // Add the button to the form
        this->Controls->Add(myButton);
    }
    void add_priority()
    {
        string sqlquery = "INSERT INTO USERS_APPLIANCE (priority) VALUES ('" + to_string(priority) + "');";
        const char* q = sqlquery.c_str();
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

        MessageBox::Show("Priority Added !");
        // push_app();
    }
    void MyDialogForm::addbuttonclick(Object^ sender, EventArgs^ e)
    {
        string sqlquery = "INSERT INTO USERS_APPLIANCE (userid, productname, priority) VALUES ("+ to_string(1) + ", '" + selectappliance + "', " + to_string(priority) + ");";
        const char* q = sqlquery.c_str();
        string result;
        // Execute the query and pass the result variable to the callback
        /*if (priority != 0) {*/

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
                MessageBox::Show("Query Ran Successfully" + gcnew String(result.c_str()));
            }
        //}
       /* else{
            MessageBox::Show("error set priority");
        }*/
        
       // push_app();
    }
    void MyDialogForm::Add_deletebutton(int xpos, int ypos)
    {
        Button^ myButton = gcnew Button();

        // Set button properties
        myButton->Text = "Delete Appliance";
        myButton->Size = System::Drawing::Size(100, 30);
        myButton->Location = System::Drawing::Point(xpos, ypos);
        myButton->BackColor = Color::FromArgb(69, 160, 227);

        // Add click event handler
        myButton->Click += gcnew EventHandler(this, &MyDialogForm::delbuttonclick);

        // Add the button to the form
        this->Controls->Add(myButton);
    }
    void MyDialogForm::delbuttonclick(Object^ sender, EventArgs^ e)
    {
        
        string sql = "DELETE FROM USERS_APPLIANCE WHERE productname = '" + selectappliance + "';";
       
        // Execute the SQL statement
        

        if (sqlite3_exec(db, sql.c_str(), delcallback, 0, &errmsg) != SQLITE_OK) {
            String^ errorMsg = gcnew String(sqlite3_errmsg(db));
            String^ detailedMsg = gcnew String(errmsg ? errmsg : "No detailed error message");

            // Show error in a message box
            MessageBox::Show("Error executing query: " + errorMsg + "\nDetails: " + detailedMsg,
                "Query Execution Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
        else {
            MessageBox::Show("Appliance deleted !");
        }
        
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
    void MyDialogForm::UpdateComboBox1()
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
    
    void MyDialogForm :: comboBox_SelectedIndexChanged1(Object^ sender, EventArgs^ e) 
    {
        ComboBox^ comboBox = dynamic_cast<ComboBox^>(sender);
        if (comboBox->SelectedIndex != 0)
        {
            selectappliance = msclr::interop::marshal_as<std::string>(comboBox->SelectedItem->ToString());
            String^ selectedItem = comboBox->SelectedItem->ToString();
            
        }
    }
    void MyDialogForm::comboBox_SelectedIndexChanged2(Object^ sender, EventArgs^ e)
    {
        ComboBox^ comboBox2 = dynamic_cast<ComboBox^>(sender);
        
        if (comboBox2->SelectedIndex != 0)
        {
            String^ pri = comboBox2->SelectedItem->ToString();
            if (pri == gcnew String(prompt1.c_str()))
            {
                priority = 1;
            }
            else if (pri == gcnew String(prompt2.c_str()))
            {
                priority = 2;
            }
            else if (pri == gcnew String(prompt3.c_str()))
            {
                priority = 3;
            }
            else if (pri == gcnew String(prompt4.c_str()))
            {
                priority = 4;
            }
            else if (pri == gcnew String(prompt5.c_str()))
            {
                priority = 5;
            }
            
        }
        MessageBox::Show(gcnew String(to_string(priority).c_str()));
    }
   
    
    MyDialogForm::MyDialogForm()
    {
        // Set the title and size of the dialog
        this->Text = "APPLIANCE SELECTION";
        this->Size = System::Drawing::Size(700, 300);

        // Add a label
        
     
        comboBox->Location = System::Drawing::Point(10, 50);
        comboBox->Size = System::Drawing::Size(500, 30);

        // Add items to the ComboBox
        comboBox->Items->Add("Select your appliance to add or delete");
        // Set a default selected item
        comboBox->SelectedIndex = 0;
        // Add event handler for selection change
        comboBox->SelectedIndexChanged += gcnew EventHandler(this, &MyDialogForm::comboBox_SelectedIndexChanged1);
        // Add the ComboBox to the form
        this->Controls->Add(comboBox);
        UpdateComboBox1();
        prioritycombo->Location = System::Drawing::Point(10, 100);
        prioritycombo->Size = System::Drawing::Size(500, 30);

        // Add items to the ComboBox
        prioritycombo->Items->Add("Select priority");
        // Set a default selected item
        prioritycombo->SelectedIndex = 0;
        // Add event handler for selection change
        prioritycombo->Items->Add(gcnew String(prompt1.c_str()));
        prioritycombo->Items->Add(gcnew String(prompt2.c_str()));
        prioritycombo->Items->Add(gcnew String(prompt3.c_str()));
        prioritycombo->Items->Add(gcnew String(prompt4.c_str()));
        prioritycombo->Items->Add(gcnew String(prompt5.c_str()));
        
        prioritycombo->SelectedIndexChanged += gcnew EventHandler(this, &MyDialogForm::comboBox_SelectedIndexChanged2);
        // Add the ComboBox to the form
        
        this->Controls->Add(prioritycombo);
       
        Add_addbutton(150, 150);
        Add_deletebutton(250, 150);
         //Add an OK button
        Button^ okButton = gcnew Button();
        okButton->Text = "OK";
        okButton->Location = System::Drawing::Point(450, 200);
        okButton->Click += gcnew EventHandler(this, &MyDialogForm::OnOkButtonClick);
        this->Controls->Add(okButton);
    }
};


