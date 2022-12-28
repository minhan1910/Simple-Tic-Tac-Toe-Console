
#include <iostream>
#include <cctype>
#include "Utils.h"


const int IGNORE_CHARS = 256;

int GetInt(const char* prompt, const char* error) {
	bool failure;
	int input;

	do {
		failure = false;
		std::cout << prompt;
		std::cin >> input;

		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(IGNORE_CHARS, '\n');
			std::cout << error << std::endl;
			failure = true;
		}
	} while (failure);

	return input;
}

char GetCharacter(const char* prompt, const char* error) {
	bool failure;
	char input;

	do {
		failure = false;
		std::cout << prompt;
		std::cin >> input;

		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(IGNORE_CHARS, '\n');
			std::cout << error << std::endl;
			failure = true;
		}
		else {
			std::cin.ignore(IGNORE_CHARS, '\n');

			if (isalpha(input)) {
				input = tolower(input);
			}
			else {
				std::cout << error << std::endl;
				failure = true;
			}
		}
	} while (failure);

	return input;
}

char GetCharacter(const char* prompt, const char* error, const char validInput[], const int validInputLength) {
	bool failure;
	char input;

	do {
		failure = false;
		std::cout << prompt;
		std::cin >> input;

		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(IGNORE_CHARS, '\n');
			std::cout << error << std::endl;
			failure = true;
		}
		else {
			std::cin.ignore(IGNORE_CHARS, '\n');

			if (isalpha(input)) {
				input = tolower(input);

				for (int i = 0; i < validInputLength; ++i) {
					if (input == validInput[i]) {
						return input;
					}
				}

				std::cout << error << std::endl;
				failure = true;
			}
		}
	} while (failure);

	return input;
}
