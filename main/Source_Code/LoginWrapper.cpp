// LoginWrapper.cpp
#include "../Header/LoginWrapper.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace LoginWrapper
{
    bool LoggingInWrapper(Account* accHead, System::String^% user, System::String^% pass, int& role)
    {
        // Convert managed System::String to std::string
        std::string user_std = msclr::interop::marshal_as<std::string>(user);
        std::string pass_std = msclr::interop::marshal_as<std::string>(pass);

        bool result = LoggingIn(accHead, user_std, pass_std, role);

        // Convert std::string back to managed System::String
        user = gcnew System::String(user_std.c_str());
        pass = gcnew System::String(pass_std.c_str());

        return result;
    }
}
