#pragma once
#include <string>
#include <sstream>  // Include this header for stringstream
#include <cmath>

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
        static int userbudget;

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
            userbudget = -1;
        }

        // Convert time (HH:MM) to integer (round to nearest hour)
        int timetoInt(const std::string& time) 
        {
            // Split the time string into hours and minutes
            int hours, minutes;
            char colon;
            std::stringstream ss(time);  // Use std::stringstream here
            ss >> hours >> colon >> minutes;

            // Round up if minutes >= 30, else round down
            if (minutes >= 30) 
            {
                return hours + 1; // Round up to next hour
            }
            else 
            {
                return hours; // Round down to current hour
            }
        }

        // Convert time (HH:MM) to float (percentage of hour passed)
        float timetoFloat(const std::string& time) 
        {
            // Split the time string into hours and minutes
            int hours, minutes;
            char colon;
            std::stringstream ss(time);  // Use std::stringstream here
            ss >> hours >> colon >> minutes;

            // Convert minutes to float (percentage of hour)
            return hours + (minutes / 60.0f); // Fractional part of hour
        }
    };
}
