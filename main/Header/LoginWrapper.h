// LoginWrapper.h
#pragma once

#include "Login.h"

namespace LoginWrapper
{
    bool LoggingInWrapper(Account* accHead, System::String^% user, System::String^% pass, int& role);
}
