#include "PasswordGenerator.h"


void PasswordGenerator::SetLength() {
	printf("Choose the length of your desired passowrd: ");
	int length;
	length = this->CheckLength();
	this->length = length;

	this->PrintNewline();
}

void PasswordGenerator::IncludeUppercaseLetter() {
	bool answer;
	printf("Include uppercase letters in your password? [y/n]: ");
	answer = this->ReadAndCheckAnswer();
	answers["Uppercase"] = answer;
	if (answer) {
		strings.push_back("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	}
	this->PrintNewline();
}

void PasswordGenerator::IncludeLowercaseLetter() {
	bool answer;
	printf("Include lowercase letters in your password? [y/n]: ");
	answer = this->ReadAndCheckAnswer();
	answers["Lowercase"] = answer;
	if (answer) {
		strings.push_back("abcdefghijklmnopqrstuvwxyz");
	}
	this->PrintNewline();
}

void PasswordGenerator::IncludeNumbers() {
	bool answer; 
	printf("Include numbers in your password? [y/n]: ");
	answer = this->ReadAndCheckAnswer();
	answers["Numbers"] = answer;
	if (answer) {
		strings.push_back("0123456789");
	}
	this->PrintNewline();
}

void PasswordGenerator::IncludeSymbols() {
	bool answer;
	printf("Include symbols in your password? [y/n]: ");
	answer = this->ReadAndCheckAnswer();
	answers["Symbols"] = answer;
	if (answer) {
		strings.push_back("!@#$%^&*()_+{}[];:,./<>?");
	}
	this->PrintNewline();
}

std::string PasswordGenerator::GeneratePassowrd() {
	srand(static_cast<int>(time(nullptr)));

	password.clear();

	std::string charList = "";
	int count = 0;

	for (auto& it : answers) {
		if (it.second) {
			charList += strings[count];
			count++;
		}
	}

	for (int i = 0; i < length; i++) {
		int randomIndex = rand() % charList.length();
		password += charList[randomIndex];
	}

	this->CheckPassword();
	return password;
}

void PasswordGenerator::CheckPassword() {
	for (auto& it : answers) {
		if (it.first == "Uppercase" && it.second) {
			if (password.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ") == std::string::npos) {
				cout << "1" << endl;
				int randIndex = rand() % password.length();
				password[randIndex] = 'A' + rand() % 26;
			}
		}
		if (it.first == "Lowercase" && it.second) {
			if (password.find_first_of("abcdefghijklmnopqrstuvwxyz") == std::string::npos) {
				cout << "2" << endl;
				int randIndex = rand() % password.length();
				password[randIndex] = 'a' + rand() % 26;
			}
		}
		if (it.first == "Numbers" && it.second) {
			if (password.find_first_of("0123456789") == std::string::npos) {
				cout << "3" << endl;
				int randIndex = rand() % password.length();
				password[randIndex] = '0' + rand() % 10;
			}
		}
		if (it.first == "Symbols" && it.second) {
			if (password.find_first_of("!@#$ea%^&*()_+{}[];:,./<>?") == std::string::npos) {
				cout << "4" << endl;
				int randIndex = rand() % password.length();
				password[randIndex] = '!' + rand() % 15;
			}
		}
	}
}

void PasswordGenerator::RegeneratePassword() {
	bool answer;
	do {
		printf("\nGenerating...\n");
		Sleep(2000);
		printf("\nYour generated password is: %s\n", this->GeneratePassowrd().c_str());
		printf("\n");
		printf("Regenerate password? [y/n] ");
		answer = this->ReadAndCheckAnswer();
	} while (answer);
}

void PasswordGenerator::PrintNewline() {
	printf("\n");
	printf("\n");
}

void PasswordGenerator::CopyToClipboard() {
	const char* passwordCString = password.c_str();
	const size_t len = strlen(passwordCString) + 1;
	HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
	memcpy(GlobalLock(hMem), passwordCString, len);
	GlobalUnlock(hMem);
	OpenClipboard(0);
	EmptyClipboard();
	SetClipboardData(CF_TEXT, hMem);
	CloseClipboard();
}

void PasswordGenerator::SavePassword() {
	std::string answer;
	printf("\nWhat do you wish to use this password for?\n");
	printf("Your answer -> ");
	std::cin >> answer;
	std::string filename = "C:\\Users\\sorin\\OneDrive\\Desktop\\passwords.txt";

	std::fstream file;
	
	if (std::filesystem::exists(filename)) {
		file.open(filename, std::ios::in | std::ios::out);
	}
	else {
		file.open(filename, std::ios::out);
	}

	vector<string> text;
	std::string line;
	while (std::getline(file, line)) {
		text.push_back(line);
	}

	file.close();

	file.open(filename, std::ios::out | std::ios::trunc);
	bool found = false;

	for (auto& it : text) {
		if (it.find(answer) != std::string::npos) {
			it = answer + ":" + " " + password;
			found = true;
		} 
		file << it << endl;
	}
	if (!found) {
		file << answer + ":" + " " + password << endl;
	}
}


void PasswordGenerator::UserDisplay() {
	printf("Welcome to password generator!\n");
	this->SetLength();
	this->IncludeUppercaseLetter();
	this->IncludeLowercaseLetter();
	this->IncludeNumbers();
	this->IncludeSymbols();

	this->RegeneratePassword();

	this->PrintNewline();
	printf("Copy password to clipboard? [y/n] ");
	bool answer = this->ReadAndCheckAnswer();
	if (answer) {
		this->CopyToClipboard();
	}

	this->PrintNewline();
	printf("Save this password in <passwords.txt> ? [y/n] ");
	answer = this->ReadAndCheckAnswer();
	if (answer) {
		this->SavePassword();
	}
}


bool PasswordGenerator::ReadAndCheckAnswer() {
	exception1 WrongAnswerFormat;
	std::string answer;
	do {
		printf("\nYour answer -> ");
		std::cin >> answer;
		try {
			if (answer != "y" && answer != "n" && answer != "Y" && answer != "N") {
				throw WrongAnswerFormat;
			}
		}
		catch (exception& e) {
			std::cout << e.what() << std::endl;
		}
	} while (answer != "y" && answer != "n" && answer != "Y" && answer != "N");

	if (answer == "y" || answer == "Y") {
		return true;
	} 
	return false;
}

int PasswordGenerator::CheckLength() {
	bool check = true;
	string length;
	exception2 WrongLengthFormat;
	exception3 LengthTooShort;
	do {
		printf("\nYour answer -> ");
		std::cin >> length;
		check = false;
		try {
			for (auto it : length) {
				if (!isdigit(it)) {
					check = true;
					throw WrongLengthFormat;
				}
			}
			if (stoi(length) <= 4) {
				check = true;
				throw LengthTooShort;
			}
		}
		catch (exception& e) {
			std::cout << e.what() << std::endl;
		}
	} while (check);
	
	return stoi(length);
}