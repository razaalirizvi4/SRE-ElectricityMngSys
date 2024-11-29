#include "pch.h"
#include "LoginForm.h"
#include "MainForm.h"
#include "RegisterForm.h"
#include"CustomMessageForm.h"
#include<sqlite3.h>
#include <msclr/marshal_cppstd.h>
#include "globals2.h"

void InitializeTable1(System::Windows::Forms::DataGridView^ targetTable) {
    // Clear the target table
    targetTable->Rows->Clear();
    targetTable->Columns->Clear();

    targetTable->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
    targetTable->ColumnHeadersVisible = true;
    targetTable->RowHeadersVisible = false;
    targetTable->AllowUserToAddRows = false;

    // Copy column structure from Gtable
    for (int i = 0; i < GlobalObjects::Globals::Gtable->ColumnCount; ++i) {
        auto newColumn = gcnew System::Windows::Forms::DataGridViewTextBoxColumn();
        newColumn->HeaderText = GlobalObjects::Globals::Gtable->Columns[i]->HeaderText;
        newColumn->Width = GlobalObjects::Globals::Gtable->Columns[i]->Width;
        targetTable->Columns->Add(newColumn);
    }

    // Copy row data from Gtable
    for (int i = 0; i < GlobalObjects::Globals::Gtable->RowCount; ++i) {
        // Create a new row for the target table
        System::Windows::Forms::DataGridViewRow^ newRow = gcnew System::Windows::Forms::DataGridViewRow();

        // Copy each cell's value from Gtable to the new row
        for (int j = 0; j < GlobalObjects::Globals::Gtable->ColumnCount; ++j) {
            System::Windows::Forms::DataGridViewCell^ newCell = gcnew System::Windows::Forms::DataGridViewTextBoxCell();
            newCell->Value = GlobalObjects::Globals::Gtable->Rows[i]->Cells[j]->Value;
            newRow->Cells->Add(newCell);
        }

        // Add the newly created row to the target table
        targetTable->Rows->Add(newRow);
    }
}

namespace EUS {


    LoginForm::LoginForm(void)
    {
        InitializeComponent();
    }

    LoginForm::~LoginForm()
    {
        if (components)
        {
            delete components;
        }
    }

    void LoginForm::InitializeComponent(void)
    {
        //Initialize variables
        insideTextBox = false;

        //Initialize containter
        this->components = gcnew System::ComponentModel::Container();
        this->Size = System::Drawing::Size(1200, 720);
        this->Text = L"Login";

        this->BackColor = Color::FromArgb(240, 248, 255);

        // Create the login button and make it smaller
        btnLogin = gcnew Button();
        btnLogin->Text = L"Login";
        btnLogin->Size = System::Drawing::Size(100, 50);
        btnLogin->Location = System::Drawing::Point(500, 270);
        btnLogin->BackColor = Color::FromArgb(0, 122, 204);
        btnLogin->ForeColor = Color::White;
        btnLogin->Click += gcnew EventHandler(this, &LoginForm::OnLoginClick);

        this->Controls->Add(btnLogin);

        // Create the button to move to register page
        btnToRegister = gcnew Button();
        btnToRegister->Text = L"Register";
        btnToRegister->Size = System::Drawing::Size(100, 50);
        btnToRegister->Location = System::Drawing::Point(620, 270);
        btnToRegister->BackColor = Color::FromArgb(0, 204, 122);
        btnToRegister->ForeColor = Color::White;
        btnToRegister->Click += gcnew EventHandler(this, &LoginForm::MoveToRegister);

        this->Controls->Add(btnToRegister);

        //Email label and textbox
        emailText = gcnew Label();
        emailText->Text = "Email";
        emailText->AutoSize = true;
        emailText->Location = System::Drawing::Point(500, 100);
        emailText->Font = gcnew System::Drawing::Font("Courier New", 18, System::Drawing::FontStyle::Bold);
        this->Controls->Add(emailText);

        emailBox = gcnew TextBox();
        emailBox->Size = System::Drawing::Size(200, 30);
        emailBox->Location = System::Drawing::Point(500, 130);
        emailBox->GotFocus += gcnew EventHandler(this, &LoginForm::InsideTextBox);
        emailBox->LostFocus += gcnew EventHandler(this, &LoginForm::OutsideTextBox);
        emailBox->KeyDown += gcnew KeyEventHandler(this, &LoginForm::OnEnterPressed);
        this->Controls->Add(emailBox);

        // Password label and textbox
        passText = gcnew Label();
        passText->Text = "Passcode";
        passText->AutoSize = true;
        passText->Location = System::Drawing::Point(500, 180);
        passText->Font = gcnew System::Drawing::Font("Courier New", 18, System::Drawing::FontStyle::Bold);
        this->Controls->Add(passText);

        passBox = gcnew TextBox();
        passBox->Size = System::Drawing::Size(200, 30);
        passBox->Location = System::Drawing::Point(500, 210);
        passBox->GotFocus += gcnew EventHandler(this, &LoginForm::InsideTextBox);
        passBox->LostFocus += gcnew EventHandler(this, &LoginForm::OutsideTextBox);
        passBox->KeyDown += gcnew KeyEventHandler(this, &LoginForm::OnEnterPressed);
        passBox->PasswordChar = '*';
        this->Controls->Add(passBox);


    }

    void LoginForm::OnLoginClick(Object^ sender, EventArgs^ e)
    {
        if (LoginCheck())
        {
            LoginSuccess();
        }

        LoginFailure();
    }

    void LoginForm::MoveToRegister(Object^ sender, EventArgs^ e)
    {
        // Hide login screen and show registration screen
        this->Hide();
        RegisterForm^ regForm = gcnew RegisterForm();
        regForm->Show();

    }

    void LoginForm::LoginSuccess()
    {
        
        this->Hide();
        MainForm^ mainForm = gcnew MainForm();
        mainForm->Show();

        //initialize table here so that evth can be called
        retrive_appliance_names();
        get_appliances();
        
        for (int i = 0; i < GlobalObjectsRaza::Globals::unmanagedGlobals->apl.size(); i++) {
            int p = (i % 2) + 1;
            if (i == 7)
                p = 3;
            GlobalObjectsRaza::Globals::unmanagedGlobals->apl[i].priority = p;
        }
        vector<schedule_appliance::Appliance> arr = sortit(GlobalObjectsRaza::Globals::unmanagedGlobals->apl, 0);

        float dailyBill = 0.0f;
        const float monthlyThreshold = 60000.0f;

        const float dailyThreshold = monthlyThreshold / 30.0f; // Calculate daily threshold
        initializeTable();
        makeTable(dailyBill, dailyThreshold, arr);
        GlobalObjectsRaza::Globals::unmanagedGlobals->bill = dailyBill;
        InitializeTable1(GlobalObjects::Globals::Gtable2);
        RandomizeTable(GlobalObjects::Globals::Gtable2);
        InitializeTable1(GlobalObjects::Globals::Gtable3);
        RandomizeTable(GlobalObjects::Globals::Gtable3);
        InitializeTable1(GlobalObjects::Globals::Gtable4);
        RandomizeTable(GlobalObjects::Globals::Gtable4);
        InitializeTable1(GlobalObjects::Globals::Gtable5);
        RandomizeTable(GlobalObjects::Globals::Gtable5);
        InitializeTable1(GlobalObjects::Globals::Gtable6);
        RandomizeTable(GlobalObjects::Globals::Gtable6);
        InitializeTable1(GlobalObjects::Globals::Gtable7);
        RandomizeTable(GlobalObjects::Globals::Gtable7);
        InitializeTable1(GlobalObjects::Globals::GTable8);
        RandomizeTable(GlobalObjects::Globals::GTable8);
        for (int i = 0; i < 4; i++) {
            Week::Tables^ weekTables = gcnew Week::Tables(); // Create an instance of Tables for each week

            // Initialize and randomize each DataGridView
            DataGridView^ day1 = gcnew DataGridView();
            DataGridView^ day2 = gcnew DataGridView();
            DataGridView^ day3 = gcnew DataGridView();
            DataGridView^ day4 = gcnew DataGridView();
            DataGridView^ day5 = gcnew DataGridView();
            DataGridView^ day6 = gcnew DataGridView();
            DataGridView^ day7 = gcnew DataGridView();

            InitializeTable1(day1);
            RandomizeTable(day1);
            InitializeTable1(day2);
            RandomizeTable(day2);
            InitializeTable1(day3);
            RandomizeTable(day3);
            InitializeTable1(day4);
            RandomizeTable(day4);
            InitializeTable1(day5);
            RandomizeTable(day5);
            InitializeTable1(day6);
            RandomizeTable(day6);
            InitializeTable1(day7);
            RandomizeTable(day7);

            // Assign to instance members of Tables
            weekTables->Gtable1 = day1;
            weekTables->Gtable2 = day2;
            weekTables->Gtable3 = day3;
            weekTables->Gtable4 = day4;
            weekTables->Gtable5 = day5;
            weekTables->Gtable6 = day6;
            weekTables->GTable7 = day7;

            GlobalObjects::Globals::monthlyTables->Add(weekTables);
        }

        sqlite3_close(GlobalObjectsRaza::Globals::unmanagedGlobals->dbr);
        
        //CustomMessageForm^ msg = gcnew CustomMessageForm("Login success!", "Login Status", true);
        // msg->Show();
    }

    void LoginForm::LoginFailure()
    {
        //CustomMessageForm^ msg = gcnew CustomMessageForm("Please try again!", "Login Status", true);
        //msg->Show();
    }

    bool LoginForm::LoginCheck()
    {
        // Retrieve email and password from textboxes
        String^ enteredEmail = emailBox->Text;
        //big_boi = msclr::interop::marshal_as<string>(enteredEmail);
        String^ enteredPassword = passBox->Text;

        // Convert managed String^ to std::string for SQLite
        msclr::interop::marshal_context context;
        std::string email = context.marshal_as<std::string>(enteredEmail);
        std::string password = context.marshal_as<std::string>(enteredPassword);

        // SQLite database connection and query
        sqlite3* db;
        sqlite3_stmt* stmt;
        int rc = sqlite3_open("user_management.db", &db);  // Use filename only

        if (rc != SQLITE_OK) 
        {
            // If opening the database failed, display an error and return false
            MessageBox::Show("Failed to open database!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return false;
        }

        // Prepare the SQL query to check for a matching email and password
        std::string sql = "SELECT COUNT(*) FROM Users WHERE User_Email = ? AND User_Password = ?";
        rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

        if (rc != SQLITE_OK) 
        {
            // Display the error message returned by SQLite
            MessageBox::Show("Failed to prepare SQL query! Error: " + gcnew String(sqlite3_errmsg(db)), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            sqlite3_close(db);
            return false;
        }

        // Debugging: Output the email and password to check if they are correct
        MessageBox::Show("Email: " + gcnew String(email.c_str()) + "\nPassword: " + gcnew String(password.c_str()));

        // Bind email and password to the prepared statement
        sqlite3_bind_text(stmt, 1, email.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

        // Execute the query and check if we have a match
        bool loginSuccessful = false;
        if (sqlite3_step(stmt) == SQLITE_ROW) 
        {
            int count = sqlite3_column_int(stmt, 0);
            if (count > 0) {
                loginSuccessful = true; // Match found
            }
        }
        else 
        {
            // Debugging: Output if sqlite3_step fails
            MessageBox::Show("SQLite Step failed! Error: " + gcnew String(sqlite3_errmsg(db)));
        }

        // Clean up
        sqlite3_finalize(stmt);
        sqlite3_close(db);

        return loginSuccessful;
    }


    void LoginForm::OnEnterPressed(Object^ sender, KeyEventArgs^ e)
    {
        if (e->KeyCode == Keys::Enter && insideTextBox)
        {
            if (LoginCheck())
            {
                LoginSuccess();
                return;
            }

            LoginFailure();
        }
    }

    void LoginForm::InsideTextBox(Object^ sender, EventArgs^ e)
    {
        insideTextBox = true;
    }

    void LoginForm::OutsideTextBox(Object^ sender, EventArgs^ e)
    {
        insideTextBox = false;
    }


}
