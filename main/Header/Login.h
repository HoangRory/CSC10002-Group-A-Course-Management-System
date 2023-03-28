#pragma once
#include "proto.h"

void DelAccount(Account *&accHead);
void ReadAccount(Account *&accHead);
void WriteAccount(Account *accHead);

void LoggingIn(Account *accHead, std::string &user, std::string &pass, int &role);
void ChangePass(Account *accHead, std::string &user, std::string &pass);
void Main_interface(Account *accHead, std::string &user, std::string &pass, int &role);