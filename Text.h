#ifndef _TEXT_H
#define _TEXT_H

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <io.h>
#include <locale.h>

#define MAX_FILE_NAME 256
#define MAX_LENGTH 1000

void textMenu(char*);
void inputTextFile(char*, char);
void textOutput(char*);
int countAmountWords(char*);
char toUpperCase(const char);
void revers(char*, fpos_t, fpos_t);
void searchBiggestWord(char*);


#endif