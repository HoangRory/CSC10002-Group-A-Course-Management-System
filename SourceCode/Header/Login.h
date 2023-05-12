#pragma once
#include "proto.h"

void DelAccount(Account *&accHead);
void ReadAccount(Account *&accHead);
void WriteAccount(Account *accHead);

void LoggingIn(Account *accHead, string &user, string &pass, int &role);

void ChangePass(Account *accHead, string &user, string &pass);

bool Main_interface(Account *accHead, string &user, string &pass, int &role);

bool AccountAlteration(Year *yearHead, Account *accHead, string &user, string &pass, int &role);

bool LoggingMain(Year *yearHead, Account *&accHead, string &user, string &pass, int &role);
