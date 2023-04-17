#pragma once
#include "../Header/Login.h"
//#include "../Header/LoginWrapper.h"
///adding library
#include <string>
#include "../Header/proto.h"
#include "../Header/Utility.h"
#include "../Header/Year.h"
#include "../Header/Semester.h"
#include "../Header/AccReader.h"
#include <msclr/marshal_cppstd.h>

// <newfunc>
namespace UICourseManagementSystem {


	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System;

	public ref struct WinFormAccount
	{
		String^ username;
		String^ password;
		String^ firstName;
		String^ lastName;
		String^ Gender;
		String^ SocialID;
		String^ birth;
		int role;
		WinFormAccount^ next;
		WinFormAccount^ prev;
	};


	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void) 
		{
			InitializeComponent();

		}

	protected:
		~MyForm() {
			if (components) {
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^ box;
	protected:
	private: System::Windows::Forms::TextBox^ Sysname;
	private: System::Windows::Forms::TextBox^ username;
	private: System::Windows::Forms::TextBox^ password;
	private: System::Windows::Forms::CheckBox^ checkbox;

	private: System::Windows::Forms::Button^ login;
	private: System::Windows::Forms::Button^ exit;
	private: System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		   void InitializeComponent(void)
		   {
			   System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			   this->box = (gcnew System::Windows::Forms::PictureBox());
			   this->Sysname = (gcnew System::Windows::Forms::TextBox());
			   this->username = (gcnew System::Windows::Forms::TextBox());
			   this->password = (gcnew System::Windows::Forms::TextBox());
			   this->checkbox = (gcnew System::Windows::Forms::CheckBox());
			   this->login = (gcnew System::Windows::Forms::Button());
			   this->exit = (gcnew System::Windows::Forms::Button());
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->box))->BeginInit();
			   this->SuspendLayout();
			   // 
			   // box
			   // 
			   this->box->BackColor = System::Drawing::Color::White;
			   this->box->Location = System::Drawing::Point(134, 134);
			   this->box->Name = L"box";
			   this->box->Size = System::Drawing::Size(616, 285);
			   this->box->TabIndex = 0;
			   this->box->TabStop = false;
			   // 
			   // Sysname
			   // 
			   this->Sysname->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				   | System::Windows::Forms::AnchorStyles::Left)
				   | System::Windows::Forms::AnchorStyles::Right));
			   this->Sysname->BackColor = System::Drawing::Color::White;
			   this->Sysname->BorderStyle = System::Windows::Forms::BorderStyle::None;
			   this->Sysname->Cursor = System::Windows::Forms::Cursors::Default;
			   this->Sysname->Font = (gcnew System::Drawing::Font(L"Google Sans", 16.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(163)));
			   this->Sysname->ForeColor = System::Drawing::Color::MidnightBlue;
			   this->Sysname->Location = System::Drawing::Point(293, 160);
			   this->Sysname->Name = L"Sysname";
			   this->Sysname->ReadOnly = true;
			   this->Sysname->Size = System::Drawing::Size(364, 34);
			   this->Sysname->TabIndex = 1;
			   this->Sysname->Text = L"School Management System";
			   //this->Sysname->TextChanged += gcnew System::EventHandler(this, &MyForm::Sysname_TextChanged);
			   // 
			   // username
			   // 
			   this->username->Cursor = System::Windows::Forms::Cursors::IBeam;
			   this->username->Font = (gcnew System::Drawing::Font(L"Google Sans", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(163)));
			   this->username->ForeColor = System::Drawing::Color::DimGray;
			   this->username->Location = System::Drawing::Point(333, 222);
			   this->username->Name = L"username";
			   this->username->Size = System::Drawing::Size(225, 29);
			   this->username->TabIndex = 2;
			   this->username->Text = L"Username";
			   this->username->Enter += gcnew System::EventHandler(this, &MyForm::username_Enter);
			   this->username->Leave += gcnew System::EventHandler(this, &MyForm::username_Leave);
			   // 
			   // password
			   // 
			   this->password->Cursor = System::Windows::Forms::Cursors::IBeam;
			   this->password->Font = (gcnew System::Drawing::Font(L"Google Sans", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(163)));
			   this->password->ForeColor = System::Drawing::Color::DimGray;
			   this->password->Location = System::Drawing::Point(333, 278);
			   this->password->Name = L"password";
			   this->password->Size = System::Drawing::Size(225, 29);
			   this->password->TabIndex = 3;
			   this->password->Text = L"Password";
			   this->password->UseSystemPasswordChar = true;
			   this->password->Enter += gcnew System::EventHandler(this, &MyForm::password_Enter);
			   this->password->Leave += gcnew System::EventHandler(this, &MyForm::password_Leave);
			   // 
			   // checkbox
			   // 
			   this->checkbox->AutoSize = true;
			   this->checkbox->BackColor = System::Drawing::Color::White;
			   this->checkbox->Checked = true;
			   this->checkbox->CheckState = System::Windows::Forms::CheckState::Checked;
			   this->checkbox->Font = (gcnew System::Drawing::Font(L"Google Sans", 6, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(163)));
			   this->checkbox->ForeColor = System::Drawing::Color::Gray;
			   this->checkbox->Location = System::Drawing::Point(333, 325);
			   this->checkbox->Name = L"checkbox";
			   this->checkbox->Size = System::Drawing::Size(95, 17);
			   this->checkbox->TabIndex = 4;
			   this->checkbox->Text = L"I\'m not a robot";
			   this->checkbox->UseVisualStyleBackColor = false;
			   this->checkbox->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkbox_CheckedChanged);
			   // 
			   // login
			   // 
			   this->login->BackColor = System::Drawing::Color::MidnightBlue;
			   this->login->FlatAppearance->BorderSize = 0;
			   this->login->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			   this->login->Font = (gcnew System::Drawing::Font(L"Google Sans", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(163)));
			   this->login->ForeColor = System::Drawing::Color::White;
			   this->login->Location = System::Drawing::Point(333, 367);
			   this->login->Name = L"login";
			   this->login->Size = System::Drawing::Size(95, 32);
			   this->login->TabIndex = 5;
			   this->login->Text = L"Log in";
			   this->login->UseVisualStyleBackColor = false;
			   this->login->Click += gcnew System::EventHandler(this, &MyForm::login_Click);
			   // 
			   // exit
			   // 
			   this->exit->BackColor = System::Drawing::Color::White;
			   this->exit->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			   this->exit->Font = (gcnew System::Drawing::Font(L"Google Sans", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(163)));
			   this->exit->ForeColor = System::Drawing::Color::Silver;
			   this->exit->Location = System::Drawing::Point(463, 367);
			   this->exit->Name = L"exit";
			   this->exit->Size = System::Drawing::Size(95, 32);
			   this->exit->TabIndex = 6;
			   this->exit->Text = L"Exit";
			   this->exit->UseVisualStyleBackColor = false;
			   this->exit->Click += gcnew System::EventHandler(this, &MyForm::exit_Click);
			   // 
			   // MyForm
			   // 
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			   this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			   this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			   this->ClientSize = System::Drawing::Size(882, 533);
			   this->Controls->Add(this->exit);
			   this->Controls->Add(this->login);
			   this->Controls->Add(this->checkbox);
			   this->Controls->Add(this->password);
			   this->Controls->Add(this->username);
			   this->Controls->Add(this->Sysname);
			   this->Controls->Add(this->box);
			   this->Font = (gcnew System::Drawing::Font(L"Google Sans", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(163)));
			   this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			   this->Name = L"MyForm";
			   this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			   this->Text = L"MyForm";
			   this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->box))->EndInit();
			   this->ResumeLayout(false);
			   this->PerformLayout();
		   }
#pragma endregion

	private:
		System::Void username_Enter(System::Object^ sender, System::EventArgs^ e) {
			// Clear placeholder text when username text box is focused
			if (username->Text == L"Username") {
				username->Text = L"";
				username->ForeColor = System::Drawing::Color::Black;
			}
		}

		System::Void username_Leave(System::Object^ sender, System::EventArgs^ e) {
			// Restore placeholder text when username text box loses focus and is empty
			if (username->Text == L"") {
				username->Text = L"Username";
				username->ForeColor = System::Drawing::Color::Gray;
			}
		}

		System::Void password_Enter(System::Object^ sender, System::EventArgs^ e) {
			// Clear placeholder text and set password char when password text box is focused
			if (password->Text == L"Password") {
				password->Text = L"";
				password->UseSystemPasswordChar = true;
				password->ForeColor = System::Drawing::Color::Black;
			}
		}

		System::Void password_Leave(System::Object^ sender, System::EventArgs^ e) {
			// Restore placeholder text and hide password char when password text box loses focus and is empty
			if (password->Text == L"") {
				password->Text = L"Password";
				password->UseSystemPasswordChar = false;
				password->ForeColor = System::Drawing::Color::Gray;
			}
		}
		//toi day ne =0

	private: System::Void checkbox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		//////////////////////////////////////////////////////////
		if (checkbox->Checked) {
			login->Enabled = true;
		}
		else {
			login->Enabled = false;
		}
		//////////////////////////////////////////////////////////
	}

	private: System::Void exit_Click(System::Object^ sender, System::EventArgs^ e) {
		Application::Exit();
	}

	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}

	private: System::Void login_Click(System::Object^ sender, System::EventArgs^ e) {
			msclr::interop::marshal_context context;
			string user = context.marshal_as<string>(username->Text);
			string pass = context.marshal_as<string>(password->Text);

			int role = 0;
			Account* accHead = nullptr;
			ReadAccount(accHead);

			Account* cur = accHead;
			bool loggedIn = false;
			while (cur) {
				if (cur->username == user && cur->password == pass) {
					loggedIn = true;
					break;
				}
				cur = cur->next;
			}

			if (loggedIn) {
				role = cur->role;
				String^ message = "Logged in successfully!!\nHello, " + gcnew String(cur->lastName.c_str()) + " " + gcnew String(cur->firstName.c_str()) + "!";
				String^ title = "Login Success";
				MessageBox::Show(message, title, MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
			else {
				String^ message = "Wrong username or password!!!\nRetry!";
				String^ title = "Login Failed";
				MessageBox::Show(message, title, MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	};
}

// </newfunc>
//namespace UICourseManagementSystem {
//
//	using namespace System;
//	using namespace System::ComponentModel;
//	using namespace System::Collections;
//	using namespace System::Windows::Forms;
//	using namespace System::Data;
//	using namespace System::Drawing;
//
//	/// <summary>
//	/// This MyForm handle the login page for the Course Management System
//	/// </summary>
//	public ref class MyForm : public System::Windows::Forms::Form
//	{
//	public:
//		//MyForm(void)
//		MyForm(void)
//		{
//			// Initialize your form here
//			InitializeComponent();
//		}
//
//		MyForm(Account* accHead, std::string& user, std::string& pass, int& role)
//		{
//			InitializeComponent();
//			this->accHead = accHead;
//			System::String^ managedUsername = gcnew System::String(user.c_str());
//			this->username->Text = managedUsername;
//			//this->username = user;
//			System::String^ managedPassword = gcnew System::String(pass.c_str());
//			this->password->Text = managedPassword;
//			//this->password = pass;
//			this->SetUserRole(role);
//		}
//
//	protected:
//		/// <summary>
//		/// Clean up any resources being used.
//		/// </summary>
//		~MyForm()
//		{
//			if (components)
//			{
//				delete components;
//			}
//		}
//	private:
//		Account* accHead;
//		std::string* user;
//		std::string* pass;
//		int* role;
//
//	private: int userRole;
//
//	public: void SetUserRole(int role) {
//		userRole = role;
//	}
//	private: System::Windows::Forms::PictureBox^ box;
//	protected:
//	private: System::Windows::Forms::TextBox^ Sysname;
//	private: System::Windows::Forms::TextBox^ username;
//	private: System::Windows::Forms::TextBox^ password;
//	private: System::Windows::Forms::CheckBox^ checkbox;
//
//	private: System::Windows::Forms::Button^ login;
//	private: System::Windows::Forms::Button^ exit;
//
//
//
//
//
//
//	protected:
//
//
//
//	protected:
//
//	protected:
//
//	protected:
//
//	private:
//		/// <summary>
//		/// Required designer variable.
//		/// </summary>
//		System::ComponentModel::Container ^components;
//
//#pragma region Windows Form Designer generated code
//		/// <summary>
//		/// Required method for Designer support - do not modify
//		/// the contents of this method with the code editor.
//		/// </summary>
//		void InitializeComponent(void)
//		{
//			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
//			this->box = (gcnew System::Windows::Forms::PictureBox());
//			this->Sysname = (gcnew System::Windows::Forms::TextBox());
//			this->username = (gcnew System::Windows::Forms::TextBox());
//			this->password = (gcnew System::Windows::Forms::TextBox());
//			this->checkbox = (gcnew System::Windows::Forms::CheckBox());
//			this->login = (gcnew System::Windows::Forms::Button());
//			this->exit = (gcnew System::Windows::Forms::Button());
//			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->box))->BeginInit();
//			this->SuspendLayout();
//			// 
//			// box
//			// 
//			this->box->BackColor = System::Drawing::Color::White;
//			this->box->Location = System::Drawing::Point(134, 134);
//			this->box->Name = L"box";
//			this->box->Size = System::Drawing::Size(616, 285);
//			this->box->TabIndex = 0;
//			this->box->TabStop = false;
//			// 
//			// Sysname
//			// 
//			this->Sysname->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
//				| System::Windows::Forms::AnchorStyles::Left)
//				| System::Windows::Forms::AnchorStyles::Right));
//			this->Sysname->BackColor = System::Drawing::Color::White;
//			this->Sysname->BorderStyle = System::Windows::Forms::BorderStyle::None;
//			this->Sysname->Cursor = System::Windows::Forms::Cursors::Default;
//			this->Sysname->Font = (gcnew System::Drawing::Font(L"Google Sans", 16.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
//				static_cast<System::Byte>(163)));
//			this->Sysname->ForeColor = System::Drawing::Color::MidnightBlue;
//			this->Sysname->Location = System::Drawing::Point(293, 160);
//			this->Sysname->Name = L"Sysname";
//			this->Sysname->ReadOnly = true;
//			this->Sysname->Size = System::Drawing::Size(364, 34);
//			this->Sysname->TabIndex = 1;
//			this->Sysname->Text = L"School Management System";
//			this->Sysname->TextChanged += gcnew System::EventHandler(this, &MyForm::Sysname_TextChanged);
//			// 
//			// username
//			// 
//			this->username->Cursor = System::Windows::Forms::Cursors::IBeam;
//			this->username->Font = (gcnew System::Drawing::Font(L"Google Sans", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
//				static_cast<System::Byte>(163)));
//			this->username->ForeColor = System::Drawing::Color::DimGray;
//			this->username->Location = System::Drawing::Point(333, 222);
//			this->username->Name = L"username";
//			this->username->Size = System::Drawing::Size(225, 29);
//			this->username->TabIndex = 2;
//			this->username->Text = L"Username";
//			this->username->Enter += gcnew System::EventHandler(this, &MyForm::username_Enter);
//			this->username->Leave += gcnew System::EventHandler(this, &MyForm::username_Leave);
//			// 
//			// password
//			// 
//			this->password->Cursor = System::Windows::Forms::Cursors::IBeam;
//			this->password->Font = (gcnew System::Drawing::Font(L"Google Sans", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
//				static_cast<System::Byte>(163)));
//			this->password->ForeColor = System::Drawing::Color::DimGray;
//			this->password->Location = System::Drawing::Point(333, 278);
//			this->password->Name = L"password";
//			this->password->Size = System::Drawing::Size(225, 29);
//			this->password->TabIndex = 3;
//			this->password->Text = L"Password";
//			this->password->UseSystemPasswordChar = true;
//			this->password->Enter += gcnew System::EventHandler(this, &MyForm::password_Enter);
//			this->password->Leave += gcnew System::EventHandler(this, &MyForm::password_Leave);
//			// 
//			// checkbox
//			// 
//			this->checkbox->AutoSize = true;
//			this->checkbox->BackColor = System::Drawing::Color::White;
//			this->checkbox->Checked = true;
//			this->checkbox->CheckState = System::Windows::Forms::CheckState::Checked;
//			this->checkbox->Font = (gcnew System::Drawing::Font(L"Google Sans", 6, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
//				static_cast<System::Byte>(163)));
//			this->checkbox->ForeColor = System::Drawing::Color::Gray;
//			this->checkbox->Location = System::Drawing::Point(333, 325);
//			this->checkbox->Name = L"checkbox";
//			this->checkbox->Size = System::Drawing::Size(95, 17);
//			this->checkbox->TabIndex = 4;
//			this->checkbox->Text = L"I\'m not a robot";
//			this->checkbox->UseVisualStyleBackColor = false;
//			this->checkbox->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBox1_CheckedChanged);
//			// 
//			// login
//			// 
//			this->login->BackColor = System::Drawing::Color::MidnightBlue;
//			this->login->FlatAppearance->BorderSize = 0;
//			this->login->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
//			this->login->Font = (gcnew System::Drawing::Font(L"Google Sans", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
//				static_cast<System::Byte>(163)));
//			this->login->ForeColor = System::Drawing::Color::White;
//			this->login->Location = System::Drawing::Point(333, 367);
//			this->login->Name = L"login";
//			this->login->Size = System::Drawing::Size(95, 32);
//			this->login->TabIndex = 5;
//			this->login->Text = L"Log in";
//			this->login->UseVisualStyleBackColor = false;
//			this->login->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
//			// 
//			// exit
//			// 
//			this->exit->BackColor = System::Drawing::Color::White;
//			this->exit->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
//			this->exit->Font = (gcnew System::Drawing::Font(L"Google Sans", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
//				static_cast<System::Byte>(163)));
//			this->exit->ForeColor = System::Drawing::Color::Silver;
//			this->exit->Location = System::Drawing::Point(463, 367);
//			this->exit->Name = L"exit";
//			this->exit->Size = System::Drawing::Size(95, 32);
//			this->exit->TabIndex = 6;
//			this->exit->Text = L"Exit";
//			this->exit->UseVisualStyleBackColor = false;
//			this->exit->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
//			// 
//			// MyForm
//			// 
//			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
//			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
//			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
//			this->ClientSize = System::Drawing::Size(882, 533);
//			this->Controls->Add(this->exit);
//			this->Controls->Add(this->login);
//			this->Controls->Add(this->checkbox);
//			this->Controls->Add(this->password);
//			this->Controls->Add(this->username);
//			this->Controls->Add(this->Sysname);
//			this->Controls->Add(this->box);
//			this->Font = (gcnew System::Drawing::Font(L"Google Sans", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
//				static_cast<System::Byte>(163)));
//			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
//			this->Name = L"MyForm";
//			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
//			this->Text = L"MyForm";
//			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
//			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->box))->EndInit();
//			this->ResumeLayout(false);
//			this->PerformLayout();
//
//		}
//#pragma endregion
//	//private: System::Void checkBox1_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
//	//}
//	//khuc nay la de nhap cai password voi username thoi do :))
//	private:
//		System::Void username_Enter(System::Object^ sender, System::EventArgs^ e) {
//			// Clear placeholder text when username text box is focused
//			if (username->Text == L"Username") {
//				username->Text = L"";
//				username->ForeColor = System::Drawing::Color::Black;
//			}
//		}
//
//		System::Void username_Leave(System::Object^ sender, System::EventArgs^ e) {
//			// Restore placeholder text when username text box loses focus and is empty
//			if (username->Text == L"") {
//				username->Text = L"Username";
//				username->ForeColor = System::Drawing::Color::Gray;
//			}
//		}
//
//		System::Void password_Enter(System::Object^ sender, System::EventArgs^ e) {
//			// Clear placeholder text and set password char when password text box is focused
//			if (password->Text == L"Password") {
//				password->Text = L"";
//				password->UseSystemPasswordChar = true;
//				password->ForeColor = System::Drawing::Color::Black;
//			}
//		}
//
//		System::Void password_Leave(System::Object^ sender, System::EventArgs^ e) {
//			// Restore placeholder text and hide password char when password text box loses focus and is empty
//			if (password->Text == L"") {
//				password->Text = L"Password";
//				password->UseSystemPasswordChar = false;
//				password->ForeColor = System::Drawing::Color::Gray;
//			}
//		}
//	//toi day ne =0
//
//	private: System::Void checkbox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
//		//////////////////////////////////////////////////////////
//		if (checkbox->Checked) {
//			login->Enabled = true;
//		}
//		else {
//			login->Enabled = false;
//		}
//		//////////////////////////////////////////////////////////
//	}
//	private: System::Void exit_Click(System::Object^ sender, System::EventArgs^ e) {
//		Application::Exit();
//	}
//	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
//	}
//	private: System::Void pictureBox1_Click(System::Object^ sender, System::EventArgs^ e) {
//	}
//	private: System::Void Sysname_TextChanged(System::Object^ sender, System::EventArgs^ e) {
//	}
//	private: System::Void username_TextChanged(System::Object^ sender, System::EventArgs^ e) {
//	}
//	private: System::Void password_TextChanged(System::Object^ sender, System::EventArgs^ e) {
//	}
//	private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
//	}
//	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
//		////////////////////////////////////////////////////////
//		if (username->Text == "admin") {
//			if (password->Text == "admin") {
//				MessageBox::Show("Login Sucessfully!", "System", MessageBoxButtons::OK, MessageBoxIcon::Asterisk);
//				Application::Exit();
//			}
//			else {
//				MessageBox::Show("Incorrect Password\nPlease retry.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
//			}
//		}
//		else {
//			MessageBox::Show("Incorrect Username\nPlease retry.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
//		}
//		//////////////////////////////////////////////////////////
//	}
//
//	};
//}
