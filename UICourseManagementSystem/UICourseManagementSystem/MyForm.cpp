#include "MyForm.h"
#include <msclr/marshal_cppstd.h> //for password and username change

using namespace System;
using namespace System::Windows::Forms;
[STAThreadAttribute]

void main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	UICourseManagementSystem::MyForm frm;
	Application::Run(% frm);
}

