#include <string>
#include "call.h"
#include <sstream> //Jas ja dodadov zaradi testiranjeto
#pragma once



namespace GUICPP {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices; //Jas go dodadov ova zaradi Marshal, konverzija od System::String vo char[]

	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
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
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  CheckB;
	private: System::Windows::Forms::Button^  ExitB;
	private: System::Windows::Forms::Button^  BrowseProgramB;
	protected: 

	protected: 




	private: System::Windows::Forms::TextBox^  ProgramPathTB;

	private: System::Windows::Forms::GroupBox^  formulasGB;





	private: System::Windows::Forms::Button^  BrowseFormulaB;
	private: System::Windows::Forms::TextBox^  formulaPathTB;


	private: System::Windows::Forms::RadioButton^  manuallyRB;

	private: System::Windows::Forms::RadioButton^  fromFileRB;
	private: System::Windows::Forms::ListBox^  formulasLB;








	private: System::Windows::Forms::Button^  RemoveFormulaB;
	private: System::Windows::Forms::TextBox^  OutputTB;


	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog2;
	private: System::Windows::Forms::Button^  AddFormulaB;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  formulaTB;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;





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
			this->CheckB = (gcnew System::Windows::Forms::Button());
			this->ExitB = (gcnew System::Windows::Forms::Button());
			this->BrowseProgramB = (gcnew System::Windows::Forms::Button());
			this->ProgramPathTB = (gcnew System::Windows::Forms::TextBox());
			this->formulasGB = (gcnew System::Windows::Forms::GroupBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->AddFormulaB = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->formulaTB = (gcnew System::Windows::Forms::TextBox());
			this->RemoveFormulaB = (gcnew System::Windows::Forms::Button());
			this->formulasLB = (gcnew System::Windows::Forms::ListBox());
			this->BrowseFormulaB = (gcnew System::Windows::Forms::Button());
			this->formulaPathTB = (gcnew System::Windows::Forms::TextBox());
			this->manuallyRB = (gcnew System::Windows::Forms::RadioButton());
			this->fromFileRB = (gcnew System::Windows::Forms::RadioButton());
			this->OutputTB = (gcnew System::Windows::Forms::TextBox());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->openFileDialog2 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->formulasGB->SuspendLayout();
			this->SuspendLayout();
			// 
			// CheckB
			// 
			this->CheckB->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->CheckB->Location = System::Drawing::Point(12, 273);
			this->CheckB->Name = L"CheckB";
			this->CheckB->Size = System::Drawing::Size(97, 27);
			this->CheckB->TabIndex = 0;
			this->CheckB->TabStop = false;
			this->CheckB->Text = L"Check";
			this->CheckB->UseVisualStyleBackColor = true;
			this->CheckB->Click += gcnew System::EventHandler(this, &Form1::CheckB_Click);
			// 
			// ExitB
			// 
			this->ExitB->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->ExitB->Location = System::Drawing::Point(322, 273);
			this->ExitB->Name = L"ExitB";
			this->ExitB->Size = System::Drawing::Size(97, 27);
			this->ExitB->TabIndex = 1;
			this->ExitB->Text = L"Exit";
			this->ExitB->UseVisualStyleBackColor = true;
			this->ExitB->Click += gcnew System::EventHandler(this, &Form1::ExitB_Click);
			// 
			// BrowseProgramB
			// 
			this->BrowseProgramB->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->BrowseProgramB->Location = System::Drawing::Point(288, 7);
			this->BrowseProgramB->Name = L"BrowseProgramB";
			this->BrowseProgramB->Size = System::Drawing::Size(131, 36);
			this->BrowseProgramB->TabIndex = 0;
			this->BrowseProgramB->Text = L"Browse MIPS Program";
			this->BrowseProgramB->UseVisualStyleBackColor = true;
			this->BrowseProgramB->Click += gcnew System::EventHandler(this, &Form1::BrowseProgramB_Click);
			// 
			// ProgramPathTB
			// 
			this->ProgramPathTB->BackColor = System::Drawing::SystemColors::Window;
			this->ProgramPathTB->Location = System::Drawing::Point(12, 23);
			this->ProgramPathTB->Name = L"ProgramPathTB";
			this->ProgramPathTB->Size = System::Drawing::Size(270, 20);
			this->ProgramPathTB->TabIndex = 5;
			// 
			// formulasGB
			// 
			this->formulasGB->Controls->Add(this->label3);
			this->formulasGB->Controls->Add(this->AddFormulaB);
			this->formulasGB->Controls->Add(this->label1);
			this->formulasGB->Controls->Add(this->formulaTB);
			this->formulasGB->Controls->Add(this->RemoveFormulaB);
			this->formulasGB->Controls->Add(this->formulasLB);
			this->formulasGB->Controls->Add(this->BrowseFormulaB);
			this->formulasGB->Controls->Add(this->formulaPathTB);
			this->formulasGB->Controls->Add(this->manuallyRB);
			this->formulasGB->Controls->Add(this->fromFileRB);
			this->formulasGB->Location = System::Drawing::Point(12, 58);
			this->formulasGB->Name = L"formulasGB";
			this->formulasGB->Size = System::Drawing::Size(407, 181);
			this->formulasGB->TabIndex = 7;
			this->formulasGB->TabStop = false;
			this->formulasGB->Text = L"Formulas";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(6, 128);
			this->label3->Name = L"label3";
			this->label3->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->label3->Size = System::Drawing::Size(44, 26);
			this->label3->TabIndex = 14;
			this->label3->Text = L"Formula\r\nList:";
			// 
			// AddFormulaB
			// 
			this->AddFormulaB->Enabled = false;
			this->AddFormulaB->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->AddFormulaB->Location = System::Drawing::Point(304, 94);
			this->AddFormulaB->Name = L"AddFormulaB";
			this->AddFormulaB->Size = System::Drawing::Size(97, 20);
			this->AddFormulaB->TabIndex = 13;
			this->AddFormulaB->Text = L"Add";
			this->AddFormulaB->UseVisualStyleBackColor = true;
			this->AddFormulaB->Click += gcnew System::EventHandler(this, &Form1::AddFormulaB_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(6, 97);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(47, 13);
			this->label1->TabIndex = 12;
			this->label1->Text = L"Formula:";
			// 
			// formulaTB
			// 
			this->formulaTB->Enabled = false;
			this->formulaTB->Location = System::Drawing::Point(59, 94);
			this->formulaTB->Name = L"formulaTB";
			this->formulaTB->Size = System::Drawing::Size(239, 20);
			this->formulaTB->TabIndex = 11;
			// 
			// RemoveFormulaB
			// 
			this->RemoveFormulaB->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->RemoveFormulaB->Location = System::Drawing::Point(304, 128);
			this->RemoveFormulaB->Name = L"RemoveFormulaB";
			this->RemoveFormulaB->Size = System::Drawing::Size(97, 43);
			this->RemoveFormulaB->TabIndex = 10;
			this->RemoveFormulaB->Text = L"Remove\r\nFormula";
			this->RemoveFormulaB->UseVisualStyleBackColor = true;
			this->RemoveFormulaB->Click += gcnew System::EventHandler(this, &Form1::RemoveFormulaB_Click);
			// 
			// formulasLB
			// 
			this->formulasLB->FormattingEnabled = true;
			this->formulasLB->Location = System::Drawing::Point(59, 128);
			this->formulasLB->Name = L"formulasLB";
			this->formulasLB->Size = System::Drawing::Size(239, 43);
			this->formulasLB->TabIndex = 9;
			// 
			// BrowseFormulaB
			// 
			this->BrowseFormulaB->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->BrowseFormulaB->Location = System::Drawing::Point(304, 42);
			this->BrowseFormulaB->Name = L"BrowseFormulaB";
			this->BrowseFormulaB->Size = System::Drawing::Size(97, 20);
			this->BrowseFormulaB->TabIndex = 7;
			this->BrowseFormulaB->Text = L"Browse Formula";
			this->BrowseFormulaB->UseVisualStyleBackColor = true;
			this->BrowseFormulaB->Click += gcnew System::EventHandler(this, &Form1::BrowseFormulaB_Click);
			// 
			// formulaPathTB
			// 
			this->formulaPathTB->Location = System::Drawing::Point(9, 42);
			this->formulaPathTB->Name = L"formulaPathTB";
			this->formulaPathTB->Size = System::Drawing::Size(289, 20);
			this->formulaPathTB->TabIndex = 6;
			// 
			// manuallyRB
			// 
			this->manuallyRB->AutoSize = true;
			this->manuallyRB->Location = System::Drawing::Point(6, 68);
			this->manuallyRB->Name = L"manuallyRB";
			this->manuallyRB->Size = System::Drawing::Size(67, 17);
			this->manuallyRB->TabIndex = 1;
			this->manuallyRB->Text = L"Manually";
			this->manuallyRB->UseVisualStyleBackColor = true;
			this->manuallyRB->CheckedChanged += gcnew System::EventHandler(this, &Form1::manuallyRB_CheckedChanged);
			// 
			// fromFileRB
			// 
			this->fromFileRB->AutoSize = true;
			this->fromFileRB->Checked = true;
			this->fromFileRB->Location = System::Drawing::Point(6, 19);
			this->fromFileRB->Name = L"fromFileRB";
			this->fromFileRB->Size = System::Drawing::Size(67, 17);
			this->fromFileRB->TabIndex = 0;
			this->fromFileRB->TabStop = true;
			this->fromFileRB->Text = L"From File";
			this->fromFileRB->UseVisualStyleBackColor = true;
			this->fromFileRB->CheckedChanged += gcnew System::EventHandler(this, &Form1::fromFileRB_CheckedChanged);
			// 
			// OutputTB
			// 
			this->OutputTB->BackColor = System::Drawing::SystemColors::Window;
			this->OutputTB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->OutputTB->ForeColor = System::Drawing::SystemColors::WindowText;
			this->OutputTB->Location = System::Drawing::Point(12, 306);
			this->OutputTB->Multiline = true;
			this->OutputTB->Name = L"OutputTB";
			this->OutputTB->ReadOnly = true;
			this->OutputTB->Size = System::Drawing::Size(407, 220);
			this->OutputTB->TabIndex = 8;
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->Filter = L"Assembly Files(*.s; *.asm; *.txt)|*.s;*.asm;*.txt|All Files|*.*";
			this->openFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &Form1::openFileDialog1_FileOk);
			// 
			// openFileDialog2
			// 
			this->openFileDialog2->Filter = L"Text Files(*.txt)|*.txt|All Files|*.*";
			this->openFileDialog2->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &Form1::openFileDialog2_FileOk);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(12, 7);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(51, 13);
			this->label2->TabIndex = 9;
			this->label2->Text = L"File Path:";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(429, 538);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->OutputTB);
			this->Controls->Add(this->formulasGB);
			this->Controls->Add(this->ProgramPathTB);
			this->Controls->Add(this->BrowseProgramB);
			this->Controls->Add(this->ExitB);
			this->Controls->Add(this->CheckB);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"Form1";
			this->ShowIcon = false;
			this->Text = L"MIPS Checker";
			this->formulasGB->ResumeLayout(false);
			this->formulasGB->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

private: System::Void BrowseProgramB_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->openFileDialog1->ShowDialog();
		 }
private: System::Void ExitB_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->Close();
		 }
private: System::Void openFileDialog1_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
			 this->ProgramPathTB->Text = openFileDialog1->FileName;
		 }
private: System::Void openFileDialog2_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
			 this->formulaPathTB->Text = openFileDialog2->FileName;
			 System::IO::StreamReader ^ sr = gcnew System::IO::StreamReader(openFileDialog2->FileName);
			 String ^ temp;
			 while(temp = sr->ReadLine())
				 formulasLB->Items->Add(temp);

		 }
private: System::Void fromFileRB_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if(fromFileRB->Checked == true){
				 formulaPathTB->Enabled = true;
				 BrowseFormulaB->Enabled = true;
				 formulaTB->Enabled = false;
				 AddFormulaB->Enabled = false;
			 }
			 else {
				 formulaPathTB->Enabled = false;
				 BrowseFormulaB->Enabled = false;
				 formulaTB->Enabled = true;
				 AddFormulaB->Enabled = true;
			 }
		 }
private: System::Void manuallyRB_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if(manuallyRB->Checked == true){
				 formulaPathTB->Enabled = false;
				 BrowseFormulaB->Enabled = false;
				 formulaTB->Enabled = true;
				 AddFormulaB->Enabled = true;
			 }
			 else{
				 formulaPathTB->Enabled = true;
				 BrowseFormulaB->Enabled = true;
				 formulaTB->Enabled = false;
				 AddFormulaB->Enabled = false;
			 }


		 }
private: System::Void AddFormulaB_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(formulaTB->Text != ""){
				formulasLB->Items->Add(formulaTB->Text);
			 }
		 }
private: System::Void RemoveFormulaB_Click(System::Object^  sender, System::EventArgs^  e) {
			 formulasLB->Items->Remove(formulasLB->SelectedItem);
		 }
private: System::Void BrowseFormulaB_Click(System::Object^  sender, System::EventArgs^  e) {
			 openFileDialog2->ShowDialog();
		 }

private: System::Void CheckB_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->OutputTB->Text = "";
			 //char* programPath = (char*)(void*)Marshal::StringToHGlobalAnsi(this->ProgramPathTB->Text).ToPointer();
			 int counter;
			 std::string callOutput = "";
			 std::string tempString = "";

			 for(counter = 0; counter < this->formulasLB->Items->Count; counter++){
				// char* eachFormula = (char*)(void*)Marshal::StringToHGlobalAnsi(this->formulasLB->Items[counter]->ToString()).ToPointer();
				 tempString = func(this->ProgramPathTB->Text, this->formulasLB->Items[counter]->ToString());
				 callOutput = callOutput + tempString;
				 callOutput = callOutput + "\r\n";
				 //Marshal::FreeHGlobal((IntPtr)eachFormula);
			 }
			 String^ outputAsSystemString = gcnew String(callOutput.c_str()); //conversion
			 this->OutputTB->Text = outputAsSystemString;
			 //Marshal::FreeHGlobal((IntPtr)programPath);
		 }
};
}

