#include "MyForm.h"
#include <msclr/marshal_cppstd.h>

using namespace System;
using namespace System::Windows::Forms;
[STAThreadAttribute]

int main(cli::array<System::String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	UICourseManagementSystem::MyForm frm;
	Application::Run(% frm);

	return 0;
}
