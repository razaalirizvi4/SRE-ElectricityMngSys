#include "pch.h"
#include "RegisterForm.h"
#include "MainForm.h"
#include"LoginForm.h"
#include<sqlite3.h>
using namespace System::Text::RegularExpressions;
#include<vector>
#include <msclr/marshal_cppstd.h>

namespace EUS {

    RegisterForm::RegisterForm(void)
    {
        InitializeComponent();
    }

    RegisterForm::~RegisterForm()
    {
        if (components)
        {
            delete components;
        }
    }

    void RegisterForm::InitializeComponent(void)
    {
        //Initialize container
        this->components = gcnew System::ComponentModel::Container();
        this->Size = System::Drawing::Size(1200, 720);
        this->Text = L"Register";

        // Set the form's background color to a light blue
        this->BackColor = Color::FromArgb(240, 248, 255); // Light blue background

        // Create the login button 
        btntoLogin = gcnew Button();
        btntoLogin->Text = L"Login";
        btntoLogin->Size = System::Drawing::Size(100, 50);
        btntoLogin->Location = System::Drawing::Point(620, 560);
        btntoLogin->BackColor = Color::FromArgb(0, 122, 204);
        btntoLogin->ForeColor = Color::White;
        btntoLogin->Font = gcnew System::Drawing::Font(L"Arial", 12);
        btntoLogin->Click += gcnew EventHandler(this, &RegisterForm::MoveToLogin);

        this->Controls->Add(btntoLogin);

        // Create the button to move to register page
        btnRegister = gcnew Button();
        btnRegister->Text = L"Register";
        btnRegister->Size = System::Drawing::Size(100, 50);
        btnRegister->Location = System::Drawing::Point(500, 560);
        btnRegister->BackColor = Color::FromArgb(0, 204, 122);
        btnRegister->ForeColor = Color::White;
        btnRegister->Font = gcnew System::Drawing::Font(L"Arial", 12);
        btnRegister->Click += gcnew EventHandler(this, &RegisterForm::OnRegisterClick);

        this->Controls->Add(btnRegister);

        // Create Labels for User Details with adjusted font and position
        userName = gcnew Label();
        userName->Text = L"Username:";
        userName->Location = System::Drawing::Point(500, 100);
        userName->Font = gcnew System::Drawing::Font("Courier New", 18, System::Drawing::FontStyle::Bold);
        userName->AutoSize = true;
        this->Controls->Add(userName);

        userEmail = gcnew Label();
        userEmail->Text = L"Email:";
        userEmail->Location = System::Drawing::Point(500, 180);
        userEmail->Font = gcnew System::Drawing::Font("Courier New", 18, System::Drawing::FontStyle::Bold);
        userEmail->AutoSize = true;
        this->Controls->Add(userEmail);

        userPassword = gcnew Label();
        userPassword->Text = L"Password:";
        userPassword->Location = System::Drawing::Point(500, 260);
        userPassword->Font = gcnew System::Drawing::Font("Courier New", 18, System::Drawing::FontStyle::Bold);
        userPassword->AutoSize = true;
        this->Controls->Add(userPassword);

        userProvince = gcnew Label();
        userProvince->Text = L"Province:";
        userProvince->Location = System::Drawing::Point(500, 340);
        userProvince->Font = gcnew System::Drawing::Font("Courier New", 18, System::Drawing::FontStyle::Bold);
        userProvince->AutoSize = true;
        this->Controls->Add(userProvince);

        userCity = gcnew Label();
        userCity->Text = L"City:";
        userCity->Location = System::Drawing::Point(500, 420);
        userCity->Font = gcnew System::Drawing::Font("Courier New", 18, System::Drawing::FontStyle::Bold);
        userCity->AutoSize = true;
        this->Controls->Add(userCity);

        // Create Textboxes for User Inputs with improved layout
        nameBox = gcnew TextBox();
        nameBox->Location = System::Drawing::Point(500, 130);
        nameBox->Size = System::Drawing::Size(250, 30);
        nameBox->Font = gcnew System::Drawing::Font(L"Arial", 10);
        this->Controls->Add(nameBox);

        emailBox = gcnew TextBox();
        emailBox->Location = System::Drawing::Point(500, 210);
        emailBox->Size = System::Drawing::Size(250, 30);
        emailBox->Font = gcnew System::Drawing::Font(L"Arial", 10);
        this->Controls->Add(emailBox);

        passwordBox = gcnew TextBox();
        passwordBox->Location = System::Drawing::Point(500, 290);
        passwordBox->Size = System::Drawing::Size(250, 30);
        passwordBox->PasswordChar = '*';  // Mask the password
        passwordBox->Font = gcnew System::Drawing::Font(L"Arial", 10);
        this->Controls->Add(passwordBox);

        // Create province and city selection boxes
        provinceBox = gcnew ComboBox();
        provinceBox->Location = System::Drawing::Point(500, 370);
        provinceBox->Size = System::Drawing::Size(250, 30);
        provinceBox->Font = gcnew System::Drawing::Font(L"Arial", 10);

        cityBox = gcnew ComboBox();
        cityBox->Location = System::Drawing::Point(500, 450);
        cityBox->Size = System::Drawing::Size(250, 30);
        cityBox->Font = gcnew System::Drawing::Font(L"Arial", 10);
        this->Controls->Add(cityBox);

        // Add the list of provinces
        std::vector<std::string> provinces = { "Sindh","Punjab","Khyber Pakhtunkhwa","Balochistan","Other" };
        for (int i = 0; i < 5; ++i)
        {
            // Convert std::string to managed System::String^ and add to ComboBox
            provinceBox->Items->Add(gcnew String(provinces[i].c_str()));
        }

        this->Controls->Add(provinceBox);
        provinceBox->SelectedIndexChanged += gcnew EventHandler(this, &RegisterForm::OnProvinceSelected);

        // Form closure event
        this->FormClosed += gcnew FormClosedEventHandler(this, &RegisterForm::OnFormClosed);


        userArea = gcnew Label();
        userArea->Text = L"Area:";
        userArea->Location = System::Drawing::Point(500, 500);
        userArea->Font = gcnew System::Drawing::Font("Courier New", 18, System::Drawing::FontStyle::Bold);
        userArea->AutoSize = true;
        this->Controls->Add(userArea);

        areaBox = gcnew ComboBox();
        areaBox->Location = System::Drawing::Point(500, 530);
        areaBox->Size = System::Drawing::Size(250, 30);
        areaBox->Font = gcnew System::Drawing::Font(L"Arial", 10);
        this->Controls->Add(areaBox);

        cityBox->SelectedIndexChanged += gcnew EventHandler(this, &RegisterForm::OnCitySelected);


    }

    void RegisterForm::MoveToLogin(Object^ sender, EventArgs^ e)
    {
        // Hide login screen and show registration screen
        this->Hide();
        LoginForm^ logForm = gcnew LoginForm();
        logForm->Show();

    }

    void RegisterForm::OnFormClosed(Object^ sender, FormClosedEventArgs^ e)
    {
        Application::Exit();
    }

    bool RegisterForm::ValidPassword(String^p)
    {
        if (p->Length >= 8 && p->Length <= 12)
        {
            return true;
        }
        else
        {
            MessageBox::Show(L"Password must be between 8 and 12 characters.", L"Invalid Password", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return false;
        }
    }

    bool RegisterForm::ValidName(String^ n)
    {
        if (n->Length >= 2)
        {
            return true;
        }
        else
        {
            MessageBox::Show(L"Please enter your full name.", L"Invalid Password", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return false;
        }
    }

    bool RegisterForm::ValidEmail(String^ e)
    {
        // Define the regex pattern for a valid email
        String^ pattern = L"^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$";
        Regex^ regex = gcnew Regex(pattern);

        // Match the email with the regex pattern
        if (regex->IsMatch(e))
        {
            return true;
        }
        else
        {
            MessageBox::Show(L"Please enter a valid email address.", L"Invalid Email", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return false;
        }
    }

    bool RegisterForm::ValidProvince(String^ province)
    {
        // Check if the province is empty or not selected
        if (province == nullptr || province->Length == 0)
        {
            MessageBox::Show(L"Please select a province.", L"Invalid Province", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return false;
        }
        return true;
    }

    bool RegisterForm::ValidCity(String^ city)
    {
        // Check if the province is empty or not selected
        if (city == nullptr || city->Length == 0)
        {
            MessageBox::Show(L"Please select a city.", L"Invalid City", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return false;
        }
        return true;
    }

    bool RegisterForm::RegisterCheck()
    {
        String^ password = passwordBox->Text;
        String^ name = nameBox->Text;
        String^ email = emailBox->Text;
        String^ province = provinceBox->Text;
        String^ city = cityBox->Text;
        String^ area = areaBox->Text;

        if (ValidPassword(password) && ValidName(name) && ValidEmail(email) && ValidProvince(province) && ValidCity(city) && ValidArea(area))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void RegisterForm::OnRegisterClick(Object^ sender, EventArgs^ e)
    {
        if (RegisterCheck() && RegisterDBCheck())
        {
            RegisterSuccess();
            return;
        }

        RegisterFailure();
    }

    void RegisterForm::RegisterSuccess()
    {
        MessageBox::Show("Register Successfull, redirecting to login!", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
        this->Hide();
        LoginForm^ logForm = gcnew LoginForm();
        logForm->Show();
    }

    void RegisterForm::RegisterFailure()
    {
        MessageBox::Show("Recheck your information!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
    }

    bool RegisterForm::RegisterDBCheck()
    {
        // Retrieve the email, password, province, and name from textboxes
        String^ enteredEmail = emailBox->Text;
        String^ enteredPassword = passwordBox->Text;
        String^ enteredProvince = provinceBox->Text; 
        String^ enteredCity = cityBox->Text;
        String^ enteredName = nameBox->Text;  
        String^ enteredArea = areaBox->Text;

        // Convert managed String^ to std::string for SQLite
        msclr::interop::marshal_context context;
        std::string email = context.marshal_as<std::string>(enteredEmail);
        std::string password = context.marshal_as<std::string>(enteredPassword);
        std::string province = context.marshal_as<std::string>(enteredProvince);
        std::string city = context.marshal_as<std::string>(enteredCity);
        std::string name = context.marshal_as<std::string>(enteredName);
        std::string area = context.marshal_as<std::string>(enteredArea);

        sqlite3* db;
        sqlite3_stmt* stmt;
        int rc = sqlite3_open("user_management.db", &db);  // Open the database

        if (rc != SQLITE_OK)
        {
            MessageBox::Show("Failed to open database!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return false;
        }

        // Check if the email already exists
        std::string checkEmailQuery = "SELECT COUNT(*) FROM Users WHERE User_Email = ?";
        rc = sqlite3_prepare_v2(db, checkEmailQuery.c_str(), -1, &stmt, nullptr);

        if (rc != SQLITE_OK)
        {
            MessageBox::Show("Failed to prepare query! Error: " + gcnew String(sqlite3_errmsg(db)), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            sqlite3_close(db);
            return false;
        }

        // Bind the email to the query
        sqlite3_bind_text(stmt, 1, email.c_str(), -1, SQLITE_STATIC);

        bool emailExists = false;
        if (sqlite3_step(stmt) == SQLITE_ROW)
        {
            int count = sqlite3_column_int(stmt, 0);
            if (count > 0)
            {
                emailExists = true;  // Email already exists
            }
        }
        sqlite3_finalize(stmt);

        if (emailExists)
        {
            MessageBox::Show("Email already exists!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            sqlite3_close(db);
            return false;  // Email exists, cannot register
        }

        // Step 2: If email doesn't exist, insert new user into the database
        std::string insertQuery = "INSERT INTO Users (User_Email, User_Name, User_Password, User_Province, User_City, User_Area) VALUES (?, ?, ?, ?, ?, ?)";
        rc = sqlite3_prepare_v2(db, insertQuery.c_str(), -1, &stmt, nullptr);

        if (rc != SQLITE_OK)
        {
            MessageBox::Show("Failed to prepare insert query! Error: " + gcnew String(sqlite3_errmsg(db)), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            sqlite3_close(db);
            return false;
        }

        // Bind the email, password, province, and name to the insert query
        sqlite3_bind_text(stmt, 1, email.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, name.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, password.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 4, province.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 5, city.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 6, area.c_str(), -1, SQLITE_STATIC);

        // Execute the insert statement
        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE)
        {
            MessageBox::Show("Failed to insert user! Error: " + gcnew String(sqlite3_errmsg(db)), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return false;
        }

        // Clean up
        sqlite3_finalize(stmt);
        sqlite3_close(db);

        return true;  // Registration successful
    }


        void RegisterForm::LoadCitiesForProvince(String^ province)
        {
        cityBox->Items->Clear(); // Clear existing cities

        // Convert the province to std::string for SQLite query
        msclr::interop::marshal_context context;
        std::string provinceStr = context.marshal_as<std::string>(province);

        sqlite3* db;
        sqlite3_stmt* stmt;
        int rc = sqlite3_open("user_management.db", &db);  // Open the database

        if (rc != SQLITE_OK)
        {
            MessageBox::Show("Failed to open database!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        // Query to get cities for the selected province
        std::string query = "SELECT City FROM Cities WHERE Province = ?";
        rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);

        if (rc != SQLITE_OK)
        {
            MessageBox::Show("Failed to prepare query! Error: " + gcnew String(sqlite3_errmsg(db)), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            sqlite3_close(db);
            return;
        }

        // Bind the province to the query
        sqlite3_bind_text(stmt, 1, provinceStr.c_str(), -1, SQLITE_STATIC);

        // Step through the result set and add cities to the cityBox
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            const char* city = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            cityBox->Items->Add(gcnew String(city));
        }

        sqlite3_finalize(stmt);
        sqlite3_close(db);

        }


        void RegisterForm::OnProvinceSelected(Object^ sender, EventArgs^ e)
        {
            String^ selectedProvince = provinceBox->SelectedItem->ToString();
           
            //Reset city and areabox
            cityBox->Items->Clear();
            areaBox->Items->Clear();
            this->Controls->Remove(cityBox);
            cityBox = gcnew ComboBox();
            cityBox->Location = System::Drawing::Point(500, 450);
            cityBox->Size = System::Drawing::Size(250, 30);
            cityBox->Font = gcnew System::Drawing::Font(L"Arial", 10);
            cityBox->SelectedIndexChanged += gcnew EventHandler(this, &RegisterForm::OnCitySelected);
            this->Controls->Add(cityBox);

            areaBox->Items->Clear();
            this->Controls->Remove(areaBox);
            areaBox = gcnew ComboBox();
            areaBox = gcnew ComboBox();
            areaBox->Location = System::Drawing::Point(500, 530);
            areaBox->Size = System::Drawing::Size(250, 30);
            areaBox->Font = gcnew System::Drawing::Font(L"Arial", 10);
            this->Controls->Add(areaBox);

            cityBox->SelectedIndexChanged += gcnew EventHandler(this, &RegisterForm::OnCitySelected);

            LoadCitiesForProvince(selectedProvince);



        }

        void RegisterForm::OnCitySelected(Object^ sender, EventArgs^ e)
        {
            String^ selectedCity = cityBox->SelectedItem->ToString();

            areaBox->Items->Clear();
            this->Controls->Remove(areaBox);
            areaBox = gcnew ComboBox();
            areaBox = gcnew ComboBox();
            areaBox->Location = System::Drawing::Point(500, 530);
            areaBox->Size = System::Drawing::Size(250, 30);
            areaBox->Font = gcnew System::Drawing::Font(L"Arial", 10);
            this->Controls->Add(areaBox);

            LoadAreasForCity(selectedCity);

        }

        void RegisterForm::LoadAreasForCity(String^ city)
        {

            areaBox->Items->Clear(); // Clear existing cities

            // Convert the province to std::string for SQLite query
            msclr::interop::marshal_context context;
            std::string cityStr = context.marshal_as<std::string>(city);

            sqlite3* db;
            sqlite3_stmt* stmt;
            int rc = sqlite3_open("user_management.db", &db);  // Open the database

            if (rc != SQLITE_OK)
            {
                MessageBox::Show("Failed to open database!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            // Query to get cities for the selected province
            std::string query = "SELECT Area FROM Areas WHERE City = ?";
            rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);

            if (rc != SQLITE_OK)
            {
                MessageBox::Show("Failed to prepare query! Error: " + gcnew String(sqlite3_errmsg(db)), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                sqlite3_close(db);
                return;
            }

            // Bind the province to the query
            sqlite3_bind_text(stmt, 1, cityStr.c_str(), -1, SQLITE_STATIC);

            // Step through the result set and add cities to the cityBox
            while (sqlite3_step(stmt) == SQLITE_ROW)
            {
                const char* city = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
                areaBox->Items->Add(gcnew String(city));
            }

            sqlite3_finalize(stmt);
            sqlite3_close(db);

        }

        bool RegisterForm::ValidArea(String^ area)
        {
            // Check if the province is empty or not selected
            if (area == nullptr || area->Length == 0)
            {
                MessageBox::Show(L"Please select a area.", L"Invalid City", MessageBoxButtons::OK, MessageBoxIcon::Error);
                return false;
            }
            return true;
        }

}

