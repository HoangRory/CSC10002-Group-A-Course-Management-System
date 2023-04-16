#include "MyForm.h"
#include <msclr/marshal_cppstd.h> //for password and username change
////////////////cop tu main
#include "../Header/Semester.h"
#include "../Header/Login.h"
#include "../Header/Year.h"

using namespace System;
using namespace System::Windows::Forms;
[STAThreadAttribute]

int main(/*array<System::String^>^ args*/) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	UICourseManagementSystem::MyForm frm;
	Application::Run(% frm);
}

//void EradicateLL(Account*& accHead, Year*& yearHead)
//{
//    DelAccount(accHead);
//    DeleteYear(yearHead);
//}
//void Merge_year_sem(Account*& accHead, Year*& yearHead)
//{
//    yearHead = RecoverFile();
//    string user = "", pass = "";
//    int role;
//    if (LoggingMain(accHead, user, pass, role))
//        return;
//    SyncFullName(yearHead, accHead);
//    NewYearMain(yearHead, accHead, role);
//}
//
//
//int main()
//{
//    Account* accHead = nullptr;
//    Year* yearHead = nullptr;
//    Merge_year_sem(accHead, yearHead);
//
//    EradicateLL(accHead, yearHead);
//    return 0;
//}