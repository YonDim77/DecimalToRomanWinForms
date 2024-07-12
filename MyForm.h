#pragma once

#include<string>
#include<map>
#include <msclr\marshal_cppstd.h>
#include <atlstr.h>
#include <stdio.h>
#using <mscorlib.dll>

namespace DecimalToRomanWF {

	using namespace System;
	using namespace System::ComponentModel;
	//using namespace System::Runtime::InteropServices;
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
	private: System::Windows::Forms::TextBox^  txtDecimalBox;
	protected:
	private: System::Windows::Forms::TextBox^  txtRomanBox;
	private: System::Windows::Forms::Label^  label1;

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
			this->txtDecimalBox = (gcnew System::Windows::Forms::TextBox());
			this->txtRomanBox = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// txtDecimalBox
			// 
			this->txtDecimalBox->Location = System::Drawing::Point(32, 115);
			this->txtDecimalBox->Name = L"txtDecimalBox";
			this->txtDecimalBox->Size = System::Drawing::Size(59, 20);
			this->txtDecimalBox->TabIndex = 0;
			this->txtDecimalBox->TextChanged += gcnew System::EventHandler(this, &MyForm::txtDecimalBox_TextChanged);
			// 
			// txtRomanBox
			// 
			this->txtRomanBox->Location = System::Drawing::Point(141, 115);
			this->txtRomanBox->Name = L"txtRomanBox";
			this->txtRomanBox->Size = System::Drawing::Size(101, 20);
			this->txtRomanBox->TabIndex = 1;
			this->txtRomanBox->TextChanged += gcnew System::EventHandler(this, &MyForm::txtRomanBox_TextChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(38, 86);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(166, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Decimal       <----->             Roman";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->ClientSize = System::Drawing::Size(284, 261);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->txtRomanBox);
			this->Controls->Add(this->txtDecimalBox);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->MaximizeBox = false;
			this->Name = L"MyForm";
			this->Text = L"Decimal <--> Roman";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: std::string IntToRoman(int num) {
		std::string strRoman;
		std::string M[] = { "","M","MM","MMM" };
		std::string C[] = { "","C","CC","CCC","CD","D","DC","DCC","DCCC","CM" };
		std::string X[] = { "","X","XX","XXX","XL","L","LX","LXX","LXXX","XC" };
		std::string I[] = { "","I","II","III","IV","V","VI","VII","VIII","IX" };
		strRoman = M[num / 1000] + C[(num % 1000) / 100] + X[(num % 100) / 10] + I[(num % 10)];
		return strRoman;
	}

	private: int RomanToInt(std::string s) {
		std::map<char, int> roman;
		roman['M'] = 1000;
		roman['D'] = 500;
		roman['C'] = 100;
		roman['L'] = 50;
		roman['X'] = 10;
		roman['V'] = 5;
		roman['I'] = 1;

		int res = 0;
		for (unsigned int i = 0; i < s.size() - 1; i++)
		{
			if (roman[s[i]] < roman[s[i + 1]])
				res -= roman[s[i]];
			else
				res += roman[s[i]];
		}
		res += roman[s[s.size() - 1]];
		return res;
	}

	private: System::Void txtDecimalBox_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		if (txtDecimalBox->Text == "")
		{
			txtRomanBox->Text = "";
		}
		else
		{
			System::String^ inputString = txtDecimalBox->Text;
			CString inputValue(inputString);
			bool isValid = true;
	
			for (int i = 0; i < inputValue.GetLength(); i++)
			{
				if (inputValue[i] < '0' || inputValue[i] > '9')
				{
					txtDecimalBox->Text = "";
					String^ msg = "Please enter a whole number between 1 and 3000";
					MessageBox::Show(msg);					
					isValid = false;
					break;
				}
			}

			//System::String ^ str1 = txtDecimalBox->Text;
			//pin_ptr<const wchar_t> str2 = PtrToStringChars(str1);
			if (isValid)
			{
				int number = System::Convert::ToInt32(txtDecimalBox->Text);
				if (number >= 1 && number <= 3000)
				{
					std::string roman = IntToRoman(number);
					txtRomanBox->Text = gcnew String(roman.c_str());
				}
				else
				{
					txtDecimalBox->Text = "";
					String^ msg = "Please enter a whole number between 1 and 3000";
					MessageBox::Show(msg);					
				}
			}

		}
	}
	private: System::Void txtRomanBox_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		if (txtRomanBox->Text == "")
		{
			txtDecimalBox->Text = "";
		}
		else
		{
			CString inputValue = txtRomanBox->Text;
			bool isValid = true;
		
			for (int i = 0; i < inputValue.GetLength(); i++)
			{
				if (inputValue[i] != 'M' && inputValue[i] != 'D' && inputValue[i] != 'C' && inputValue[i] != 'L' &&
					inputValue[i] != 'X' && inputValue[i] != 'V' && inputValue[i] != 'I')
				{
					txtRomanBox->Text = "";
					String^ msg = "Please enter a roman number between 1 and 3000";
					MessageBox::Show(msg);
					isValid = false;
					break;
				}
			}

			{
				if (isValid)
				{
					int countM = 0;
					for (int i = 0; i < inputValue.GetLength(); i++)
					{
						if (inputValue[i] == 'M')
						{
							countM++;
						}
					}
					if (countM >= 3 && inputValue.GetLength() == 4)
					{
						txtRomanBox->Text = "";
						String^ msg = "Please enter a roman number less than 3001";
						MessageBox::Show(msg);											
					}
					else
					{
						std::string romanNumber = msclr::interop::marshal_as<std::string>(txtRomanBox->Text);
						unsigned int number = RomanToInt(romanNumber);
						txtDecimalBox->Text = number.ToString();
					}
				}
			}
		}
	}
};
}
