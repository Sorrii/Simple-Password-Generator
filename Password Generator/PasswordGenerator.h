#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <ctime>
#include <cstdlib>
#include <cctype>
#include <fstream>
#include <filesystem>
#include <Windows.h>
#include "Exceptii.h"

class PasswordGenerator {
private:
	int length;
	std::string password;
	std::map<string,bool>answers;
	std::vector<std::string> strings;
public:
	void SetLength();
	void IncludeUppercaseLetter();
	void IncludeLowercaseLetter();
	void IncludeNumbers();
	void IncludeSymbols();

	std::string GeneratePassowrd();
	void RegeneratePassword();
	void CheckPassword();

	void UserDisplay();
	void CopyToClipboard();
	void SavePassword();

	bool ReadAndCheckAnswer();
	int CheckLength();

	void PrintNewline();
};

