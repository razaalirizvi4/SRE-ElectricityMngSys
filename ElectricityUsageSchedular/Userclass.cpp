#include "pch.h"
#include"Userclass.h"


namespace EUS
{


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
    int EUS::UserData::userbudget = -1;

}