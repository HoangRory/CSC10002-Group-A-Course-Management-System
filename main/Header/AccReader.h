#pragma once
#include "proto.h" // Assuming this is the header file containing your Account structure
#include "../UICourseManagementSystem/MyForm.h" // The header file containing the WinFormAccount structure

WinFormAccount^ ConvertToWinFormAccount(Account* account);
void ReadAccount(WinFormAccount^% accHead);