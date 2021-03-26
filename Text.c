#include "Text.h"

void textMenu(char* fileName)
{
	int option;

	do {
	
		system("CLS");
		printf(" Choose option by entering their first letter\n 1 - Input \n 2 - Output \n 3 - Count the amount of words in the file\n 4 - Revers of the biggest word\n 5 - Additional");
		scanf_s("%d", &option);
		switch (option) {
		case 1:
			inputTextFile(fileName, 'n');
			break;
		case 2:
			textOutput(fileName);
			break;
		case 3:
			printf(" Amount of words in file %s are %d \n", fileName, countAmountWords(fileName));
			break;
		case 4:
			searchBiggestWord(fileName);
			break;
		case 5:
			inputTextFile(fileName, 'a');
			break;
		default:break;
		}
		printf(" Do you want to do anything else? Enter 9");
		scanf_s("%d", &option);
		rewind(stdin);
	} while (option == 9);
}

void inputTextFile(char* fileName, char mod)
{
	FILE* textFile;
	char words[1000];
	char buffer;
	bool repeater;
	if (mod == 'n') {
		do {

			printf(" Input name of text file you want to create ");
			rewind(stdin);
			gets_s(fileName, MAX_FILE_NAME);
			fopen_s(&textFile, fileName, "w+b");
			if (!textFile) {
				printf(" Can't create file %s \n Try again", fileName);
				repeater = 1;
			}
			else repeater = 0;
		} while (repeater);
	}
	else {
		fopen_s(&textFile, fileName, "r+b");
		if (!textFile) {
			printf(" Can't open file %s \n Try again", fileName);
			return;
		}
		fseek(textFile, 0, SEEK_END);
		fprintf(textFile, "%c", '\n');
	}
	do {
		printf(" Input words ");
		rewind(stdin);
		gets_s(words, 1000);
		fprintf(textFile, "%s", words);
		printf(" If you want to input one more string, enter y, else enter any other letter");
		rewind(stdin);
		buffer = getchar();
		buffer = toUpperCase(buffer);
		if (buffer == 'Y') fprintf(textFile, "%c", '\n');
	} while (buffer == 'Y');
	
	fclose(textFile);
}

void textOutput(char* fileName)
{
	FILE* textFile;
	char buffer;
	fopen_s(&textFile, fileName, "r");
	if (!textFile) {
		printf(" Can't open file %s ", fileName);
		return;
	}
	printf("	File contents\n");
	while ((buffer = getc(textFile)) != EOF)
		printf("%c", buffer);
	printf("\n");
	fclose(textFile);
}

int countAmountWords(char* fileName)
{
	int wordsAmount = 0;
	char buffer1, buffer2;
	FILE* textFile;
	fopen_s(&textFile, fileName, "r");
	if (!textFile) {
		printf(" Can't open file %s", fileName);
		return 0;
	}
	while (!feof(textFile))
	{
		buffer2 = getc(textFile);
		if ((buffer2 == ' ' || buffer2 == '\n' || buffer2 == EOF) 
			&& (buffer1 != ' ' && buffer1 != '\n' && buffer1 != EOF))
			wordsAmount++;
		buffer1 = buffer2;
	}
	fclose(textFile);
	return wordsAmount;
}

char toUpperCase(const char symbol)
{
	return (symbol >= 'a' && symbol <= 'z') ? symbol - 32 : symbol;
}

void revers(char* fileName, fpos_t start, fpos_t end)
{
	FILE* textFile;
	char startBuf, endBuf;
	fopen_s(&textFile, fileName, "r+");
	if (textFile == NULL) {
		printf(" Can't open file %s \n", fileName);
		rewind(stdin);
	}
	while (start < end) {
		fsetpos(textFile, &start);
		fscanf_s(textFile, "%c", &startBuf);
		fsetpos(textFile, &end);
		fscanf_s(textFile, "%c", &endBuf);
		fsetpos(textFile, &start);
		fprintf(textFile, "%c", endBuf);
		fsetpos(textFile, &end);
		fprintf(textFile, "%c", startBuf);
		start++;
		end--;
	}
	fclose(textFile);
	return;
}

void searchBiggestWord(char* fileName)
{
	FILE* textFile;
	fpos_t startMax,
		endMax,
		start,
		end;
	char buffer;
	int intBuffer;
	fopen_s(&textFile, fileName, "r");
	if (!textFile) {
		printf(" Can't open file %s \n", fileName);
		rewind(stdin);
	}
	fgetpos(textFile, &startMax);

	while ((buffer = getc(textFile)) != ' ' 
		&& buffer != '\n'
		&& buffer != '!'
		&& buffer != '?'
		&& buffer != '.'
		&& buffer != ',');
	fgetpos(textFile, &endMax);
	endMax--;
	while (!feof(textFile)) {
		fgetpos(textFile, &start);
		while ((buffer = getc(textFile)) != ' ' 
			&& buffer != '\n'
			&& buffer != '!'
			&& buffer != '?'
			&& buffer != '.'
			&& buffer != EOF
			&& buffer != ',');
		fgetpos(textFile, &end);
		end--;
		if (end - start > endMax - startMax) {
			endMax = end;
			startMax = start;
			if (buffer == EOF) endMax++;
		}
	
	}
	fclose(textFile);
	
	revers(fileName, startMax, --endMax);

}
