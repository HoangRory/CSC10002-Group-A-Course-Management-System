#pragma once
#include "proto.h"

void DelAccount(Account *&accHead);
void ReadAccount(Account *&accHead);
void WriteAccount(Account *accHead);

void LoggingIn(Account *accHead, string &user, string &pass, int &role);

void ChangePass(Account *accHead, string &user, string &pass);

void Main_interface(Account *accHead, string &user, string &pass, int &role);

void AccountAlteration(Account *accHead, string &user, string &pass, int &role);

void LoggingMain(Account *&accHead, string &user, string &pass, int &role);
