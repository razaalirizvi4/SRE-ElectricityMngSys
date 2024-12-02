#pragma once
#include<string>

namespace EUS 
{

    class UserData
    {
    public:
        static int userid;
        static std::string username;
        static std::string useremail;
        static std::string userpassword;
        static std::string userprovince;
        static std::string usercity;
        static std::string userarea;
        static std::string userpeakstart;
        static std::string userpeakend;

        UserData()
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

    };

}