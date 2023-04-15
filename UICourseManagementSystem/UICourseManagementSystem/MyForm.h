#pragma once

namespace UICourseManagementSystem {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^ box;
	protected:
	private: System::Windows::Forms::TextBox^ Sysname;
	private: System::Windows::Forms::TextBox^ username;
	private: System::Windows::Forms::TextBox^ password;
	private: System::Windows::Forms::CheckBox^ checkBox1;
	private: System::Windows::Forms::Button^ button1;

	protected:



	protected:

	protected:

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->box = (gcnew System::Windows::Forms::PictureBox());
			this->Sysname = (gcnew System::Windows::Forms::TextBox());
			this->username = (gcnew System::Windows::Forms::TextBox());
			this->password = (gcnew System::Windows::Forms::TextBox());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
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
			this->Sysname->BackColor = System::Drawing::Color::White;
			this->Sysname->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->Sysname->Cursor = System::Windows::Forms::Cursors::Default;
			this->Sysname->Font = (gcnew System::Drawing::Font(L"Google Sans", 16.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(163)));
			this->Sysname->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->Sysname->Location = System::Drawing::Point(290, 153);
			this->Sysname->Name = L"Sysname";
			this->Sysname->Size = System::Drawing::Size(300, 27);
			this->Sysname->TabIndex = 1;
			this->Sysname->Text = L"School Management System";
			// 
			// username
			// 
			this->username->Cursor = System::Windows::Forms::Cursors::IBeam;
			this->username->Font = (gcnew System::Drawing::Font(L"Google Sans", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(163)));
			this->username->ForeColor = System::Drawing::Color::DimGray;
			this->username->Location = System::Drawing::Point(333, 222);
			this->username->Name = L"username";
			this->username->Size = System::Drawing::Size(225, 24);
			this->username->TabIndex = 2;
			this->username->Text = L"Username";
			// 
			// password
			// 
			this->password->Cursor = System::Windows::Forms::Cursors::IBeam;
			this->password->Font = (gcnew System::Drawing::Font(L"Google Sans", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(163)));
			this->password->ForeColor = System::Drawing::Color::DimGray;
			this->password->Location = System::Drawing::Point(333, 278);
			this->password->Name = L"password";
			this->password->Size = System::Drawing::Size(225, 24);
			this->password->TabIndex = 3;
			this->password->Text = L"Password";
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->BackColor = System::Drawing::Color::White;
			this->checkBox1->Font = (gcnew System::Drawing::Font(L"Google Sans", 6, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(163)));
			this->checkBox1->ForeColor = System::Drawing::Color::Gray;
			this->checkBox1->Location = System::Drawing::Point(333, 325);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(77, 14);
			this->checkBox1->TabIndex = 4;
			this->checkBox1->Text = L"I\'m not a robot";
			this->checkBox1->UseVisualStyleBackColor = false;
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::Color::MidnightBlue;
			this->button1->FlatAppearance->BorderSize = 0;
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->Font = (gcnew System::Drawing::Font(L"Google Sans", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(163)));
			this->button1->ForeColor = System::Drawing::Color::White;
			this->button1->Location = System::Drawing::Point(391, 365);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(109, 32);
			this->button1->TabIndex = 5;
			this->button1->Text = L"Log in";
			this->button1->UseVisualStyleBackColor = false;
			// 
			// MyForm
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->ClientSize = System::Drawing::Size(882, 533);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->checkBox1);
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
	private: System::Void checkBox1_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void pictureBox1_Click(System::Object^ sender, System::EventArgs^ e) {
	}

	};
}
