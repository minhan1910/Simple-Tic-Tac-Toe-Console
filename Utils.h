
#ifndef __UTILS_H__
#define __UTILS__H__


int GetInt(const char* prompt, const char* error);

char GetCharacter(const char* prompt, const char* error);
char GetCharacter(const char* prompt, const char* error, const char validInput[], const int validInputLength);

#endif

