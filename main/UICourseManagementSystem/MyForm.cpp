#include "MyForm.h"
#include "../Header/AccReader.h"
#include "../Header/proto.h"
#include "../Header/Utility.h"
#include "../Header/Year.h"
#include "../Header/Semester.h"
#include <msclr/marshal_cppstd.h>

using namespace System;
using namespace System::Windows::Forms;
[STAThreadAttribute]

int main(/*array<System::String^>^ args*/) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	UICourseManagementSystem::MyForm frm;
	Application::Run(% frm);
}