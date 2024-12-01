#include "pch.h"
#include "LoginForm.h"
#include "MainForm.h"
#include "RegisterForm.h"
#include"CustomMessageForm.h"
#include<sqlite3.h>
#include <msclr/marshal_cppstd.h>
#include "globals2.h"
#include"RoundedRectangle.h"

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



namespace EUS 
{


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
        //Initialize
        insideTextBox = false;

        //Initialize containter
        this->components = gcnew System::ComponentModel::Container();
        this->Size = System::Drawing::Size(1200, 720);
        this->Text = L"Login";
        this->BackgroundImage = System::Drawing::Image::FromFile("backdrop.jpg");
        this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;

        //Initialize panel (rounded)(bg1)
        Panel^ backpanel1 = gcnew Panel();
        backpanel1->Size = System::Drawing::Size(400,640);
        backpanel1->Location = System::Drawing::Point(440, 30);
        backpanel1->BackColor = Color::FromArgb(30, 30, 30);
        ApplyRoundedRectangleToPanel(backpanel1, 20);

        //Initialize panel (rounded)(bg2)
        Panel^ backpanel2 = gcnew Panel();
        backpanel2->Size = System::Drawing::Size(400, 640);
        backpanel2->Location = System::Drawing::Point(435, 35);
        backpanel2->BackColor = Color::FromArgb(0, 122, 204);
        ApplyRoundedRectangleToPanel(backpanel2, 20);

        //Initialize to register label text
        Label^ rl1 = gcnew Label();
        rl1->AutoSize = true;
        rl1->Location = System::Drawing::Point(500, 380);
        rl1->BackColor = Color::FromArgb(30,30,30);
        rl1->ForeColor = Color::FromArgb(69, 160, 227);
        rl1->Text = L"Do not have an account?";
        rl1->Font = gcnew System::Drawing::Font("Helvetica", 12);


        
        //Initialize login button
        btnLogin = gcnew Button();
        btnLogin->Text = L"Login";
        btnLogin->Size = System::Drawing::Size(150, 50);
        btnLogin->Location = System::Drawing::Point(560, 280);
        btnLogin->BackColor = Color::FromArgb(0, 122, 204);
        btnLogin->ForeColor = Color::White;
        btnLogin->FlatStyle = FlatStyle::Flat;
        btnLogin->FlatAppearance->BorderSize = 0;
        btnLogin->Click += gcnew EventHandler(this, &LoginForm::OnLoginClick);

        

        //Initialize to register button
        btnToRegister = gcnew Button();
        btnToRegister->Text = L"Register";
        btnToRegister->Size = System::Drawing::Size(100, 50);
        btnToRegister->Location = System::Drawing::Point(675, 365);
        btnToRegister->BackColor = Color::FromArgb(30, 30, 30);
        btnToRegister->ForeColor = Color::White;
        btnToRegister->FlatStyle = FlatStyle::Flat;
        btnToRegister->FlatAppearance->BorderSize = 0;
        btnToRegister->Click += gcnew EventHandler(this, &LoginForm::MoveToRegister);



        //Email label and textbox
        emailText = gcnew Label();
        emailText->Text = "Email";
        emailText->AutoSize = true;
        emailText->Location = System::Drawing::Point(530, 100);
        emailText->Font = gcnew System::Drawing::Font("Helvetica", 18, System::Drawing::FontStyle::Bold);
        emailText->BackColor = Color::FromArgb(30, 30, 30);
        emailText->ForeColor = Color::FromArgb(80, 116, 174);


        emailBox = gcnew TextBox();
        emailBox->Size = System::Drawing::Size(200, 30);
        emailBox->Location = System::Drawing::Point(530, 130);
        emailBox->GotFocus += gcnew EventHandler(this, &LoginForm::InsideTextBox);
        emailBox->LostFocus += gcnew EventHandler(this, &LoginForm::OutsideTextBox);
        emailBox->KeyDown += gcnew KeyEventHandler(this, &LoginForm::OnEnterPressed);
        emailBox->BackColor = Color::FromArgb(30, 30, 30);
        emailBox->BorderStyle= BorderStyle::FixedSingle;
        emailBox->ForeColor = Color::FromArgb(212, 237, 250);


        // Password label and textbox
        passText = gcnew Label();
        passText->Text = "Password";
        passText->AutoSize = true;
        passText->Location = System::Drawing::Point(530, 180);
        passText->Font = gcnew System::Drawing::Font("Helvetica", 18, System::Drawing::FontStyle::Bold);
        passText->BackColor = Color::FromArgb(30, 30, 30);
        passText->ForeColor = Color::FromArgb(80, 116, 174);


        passBox = gcnew TextBox();
        passBox->Size = System::Drawing::Size(200, 30);
        passBox->Location = System::Drawing::Point(530, 210);
        passBox->GotFocus += gcnew EventHandler(this, &LoginForm::InsideTextBox);
        passBox->LostFocus += gcnew EventHandler(this, &LoginForm::OutsideTextBox);
        passBox->KeyDown += gcnew KeyEventHandler(this, &LoginForm::OnEnterPressed);
        passBox->PasswordChar = '*';
        passBox->BackColor = Color::FromArgb(30, 30, 30);
        passBox->BorderStyle= BorderStyle::FixedSingle;
        passBox->ForeColor = Color::FromArgb(212, 237, 250);


        //Add to controls order for display
        this->Controls->Add(passBox);
        this->Controls->Add(passText);
        this->Controls->Add(emailBox);
        this->Controls->Add(emailText);
        this->Controls->Add(btnToRegister);
        this->Controls->Add(btnLogin);
        this->Controls->Add(rl1);
        this->Controls->Add(backpanel1);
        this->Controls->Add(backpanel2);
        

    }

    void LoginForm::OnLoginClick(Object^ sender, EventArgs^ e)
    {
        if (LoginCheck())
        {
            FetchDetailsOnLogin();
            LoginSuccess();
            return;
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
        CustomMessageForm^ msg = gcnew CustomMessageForm("Please try again!", "Login Status", true);
        msg->Show();
    }

    bool LoginForm::LoginCheck()
    {
        // Retrieve email and password from textboxes
        String^ enteredEmail = emailBox->Text;
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
            MessageBox::Show("Failed to open database!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return false;
        }

        // Prepare the SQL query to check for a matching email and password
        std::string sql = "SELECT COUNT(*) FROM Users WHERE User_Email = ? AND User_Password = ?";
        rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

        if (rc != SQLITE_OK)
        {
            MessageBox::Show("Failed to prepare SQL query! Error: " + gcnew String(sqlite3_errmsg(db)), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            sqlite3_close(db);
            return false; // Return immediately after a failure
        }

        // Bind email and password to the prepared statement
        sqlite3_bind_text(stmt, 1, email.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

        // Execute the query and check if we have a match
        bool loginSuccessful = false;
        if (sqlite3_step(stmt) == SQLITE_ROW)
        {
            int count = sqlite3_column_int(stmt, 0);
            if (count > 0) 
            {
                loginSuccessful = true; // Match found
            }
        }
        else
        {
            MessageBox::Show("Failed to execute query. Error: " + gcnew String(sqlite3_errmsg(db)), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }

        // Final cleanup
        sqlite3_finalize(stmt);
        sqlite3_close(db);

        return loginSuccessful; // Return whether login was successful
    }



    void LoginForm::OnEnterPressed(Object^ sender, KeyEventArgs^ e)
    {
        if (e->KeyCode == Keys::Enter && insideTextBox)
        {
            if (LoginCheck())
            {
                FetchDetailsOnLogin();
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


    UserData::UserData()
    {
        userid = -1;
        username = "";
        useremail = "";
        userpassword = "";
        userprovince = "";
        usercity = "";
        userarea = "";
        userpeakstart = "";
        userpeakend = "";
    }

    // Initialize static variables
    int EUS::UserData::userid = 0;                        // Set to some initial value
    std::string EUS::UserData::username = "default_user";  // Set to some initial value
    std::string EUS::UserData::useremail = "example@email.com";  // Set to some initial value
    std::string EUS::UserData::userpassword = "default_password"; // Set to some initial value
    std::string EUS::UserData::userprovince = "default_province"; // Set to some initial value
    std::string EUS::UserData::usercity = "default_city";        // Set to some initial value
    std::string EUS::UserData::userarea = "default_area";        // Set to some initial value
    std::string EUS::UserData::userpeakstart = "some initial value"; // Set to some initial value
    std::string EUS::UserData::userpeakend = "some initial value";   // Set to some initial value

    void LoginForm::FetchDetailsOnLogin()
    {
        String^ enteredEmail = emailBox->Text;
        String^ enteredPassword = passBox->Text;

        // Convert managed String^ to std::string for SQLite
        msclr::interop::marshal_context context;
        std::string email = context.marshal_as<std::string>(enteredEmail);
        std::string password = context.marshal_as<std::string>(enteredPassword);

        sqlite3* db;
        sqlite3_stmt* stmt;
        int rc = sqlite3_open("user_management.db", &db);

        if (rc != SQLITE_OK) {
            MessageBox::Show("Failed to open database!");
            return;
        }

        // Prepare SQL for login query
        std::string sql = "SELECT User_ID, User_Email, User_Name, User_Password, User_Province, User_City, User_Area FROM Users WHERE User_Email = ? AND User_Password = ?";
        rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            MessageBox::Show("Failed to prepare SQL statement!");
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return;
        }

        sqlite3_bind_text(stmt, 1, email.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

        rc = sqlite3_step(stmt);
        if (rc == SQLITE_ROW) {
            int userID = sqlite3_column_int(stmt, 0);
            const unsigned char* userEmail = sqlite3_column_text(stmt, 1);
            const unsigned char* userName = sqlite3_column_text(stmt, 2);
            const unsigned char* userPassword = sqlite3_column_text(stmt, 3);
            const unsigned char* userProvince = sqlite3_column_text(stmt, 4);
            const unsigned char* userCity = sqlite3_column_text(stmt, 5);
            const unsigned char* userArea = sqlite3_column_text(stmt, 6);

            std::string userEmailStr(reinterpret_cast<const char*>(userEmail));
            std::string userNameStr(reinterpret_cast<const char*>(userName));
            std::string userPasswordStr(reinterpret_cast<const char*>(userPassword));
            std::string userProvinceStr(reinterpret_cast<const char*>(userProvince));
            std::string userCityStr(reinterpret_cast<const char*>(userCity));
            std::string userAreaStr(reinterpret_cast<const char*>(userArea));

            // Store static data in UserData class
            UserData::userid = userID;
            UserData::username = userNameStr;
            UserData::useremail = userEmailStr;
            UserData::userpassword = userPasswordStr;
            UserData::userprovince = userProvinceStr;
            UserData::usercity = userCityStr;
            UserData::userarea = userAreaStr;
        }
        sqlite3_finalize(stmt);

        // Fetch additional area details (PeakStart, PeakEnd)
        std::string uarea = UserData::userarea;

        sql = "SELECT Peak_Start, Peak_End FROM Areas WHERE Area = ?";

        rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

        if (rc != SQLITE_OK) 
        {
            MessageBox::Show("Failed to prepare area query!");
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return;
        }
        sqlite3_bind_text(stmt, 1, uarea.c_str(), -1, SQLITE_STATIC);

        rc = sqlite3_step(stmt);
        if (rc == SQLITE_ROW) 
        {
            const unsigned char* pstart = sqlite3_column_text(stmt, 0);
            const unsigned char* pend = sqlite3_column_text(stmt, 1);

            std::string pstarti(reinterpret_cast<const char*>(pstart));
            std::string pendi(reinterpret_cast<const char*>(pend));

            UserData::userpeakstart = pstarti;
            UserData::userpeakend = pendi;
        }
        sqlite3_finalize(stmt);
        sqlite3_close(db);
    }


   void LoginForm::ApplyRoundedRectangleToPanel(Panel^ panel, int radius) {
        System::Drawing::Drawing2D::GraphicsPath^ path = RoundedRectangles::RoundedRectangle::Create(
            0, 0, panel->Width, panel->Height, radius,
            RoundedRectangles::RoundedRectangle::RectangleCorners::All
        );
        panel->Region = gcnew System::Drawing::Region(path);
    }


}
