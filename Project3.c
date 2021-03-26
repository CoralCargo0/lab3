#include "Text.h"
#include "Binary.h"


int main() {
	system("chcp 1251");
	system("CLS");

	char* textFileName = (char*)calloc(MAX_FILE_NAME, sizeof(char));
	char* binFileName = (char*)calloc(MAX_FILE_NAME, sizeof(char));
	char buffer;

	do {
		system("CLS");
		printf(" Choose to work with a binary or text file by entering their first letter, exit any other symbol ");
		rewind(stdin);
		buffer = getchar();
		if (buffer >= 'a' && buffer <= 'z')buffer -= 32;
		switch (buffer)
		{
		case 'T':
			textMenu(textFileName);
			break;
		case 'B':
			binMenu(binFileName);
			break;
		default: 
			buffer = 0;
			break;
		}
	} while (buffer);


	free(textFileName);
	free(binFileName);

	return 0;

}
