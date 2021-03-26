#include "Binary.h"
#include "Text.h"

void binMenu(char* fileName) {
	int buffer;
	bool repeater;
	do {
		repeater = true;
		system("CLS");
		printf(" Choose option by entering their first letter\n 1 - Input with creating new file ");
			printf("	\n 2 - Additional input\n 3 - Output \n 4 - PrintSmallestMul\n 5 - Change");
				printf("	\n 6 - Ascending sort\n 7 - descending sort\n Exit any other number");
		while (!scanf_s("%d", &buffer))
		{
			printf(" Your enter wrong number, try again");
			rewind(stdin);
		}
		switch (buffer) {
		case 1:
			binInput(fileName, 'n');
			break;
		case 3:
			output(fileName);
			break;
		case 4:
			printSmallestMul(fileName);

			break;
		case 5:
			change(fileName);
			break;
		case 6: 
			sort(fileName, 'a');
			break;
		case 7:
			sort(fileName, 'd');
			break;
		default:break;
		}
		printf(" Do you want to do anything else? Enter (y/n)");
		rewind(stdin);
		buffer = getchar();
		buffer = toUpperCase(buffer);
		if (buffer != 'Y')
			repeater = 0;
	} while (repeater);
}

void binInput(char* fileName, char mod) {
	FILE* binFile;
	int buffer, repeater;
	if (mod == 'n') {


		do {
		
			printf(" Input name of binary file you want to create ");
			rewind(stdin);
			gets_s(fileName, MAX_FILE_NAME);
			fopen_s(&binFile, fileName, "w+b");
			if (!binFile) {
				printf(" Can't create file %s \n Try again", fileName);
				repeater = 1;
			}
			else repeater = 0;
		} while (repeater);

	}
	else {
		fopen_s(&binFile, fileName, "r+b");
		if (!binFile) {
			printf(" Can't open file %s \n ", fileName);
			return;
		}
	}
	printf(" Enter your numbers ");
	do {
		while (!scanf_s("%d", &buffer)) {
			printf(" You tried to enter incorrect number, try again");
			rewind(stdin);
		}
		if (buffer == 999) {
			printf(" If you want to enter 999 press 0? If you really want to stop entering press any other number ");
			scanf_s("%d", &repeater);
			if (!repeater) fwrite(&buffer, sizeof(int), 1, binFile);
			else break;
		}
		else {
			fwrite(&buffer, sizeof(int), 1, binFile);
		}
	} while (1);
	fclose(binFile);
}

void printSmallestMul(char* fileName)
{
	FILE* binFile;
	int intFirst, intSecond;
	int prod = 999999999;
	fpos_t position;
	fopen_s(&binFile, fileName, "r+b");
	if (!binFile) {
		printf(" Can't open file %s", fileName);
		return;
	}
	fread(&intFirst, sizeof(int), 1, binFile);
	fread(&intSecond, sizeof(int), 1, binFile);
	while (!feof(binFile)) {
		if (intFirst * intSecond <= prod) {
			prod = intFirst * intSecond;
			fgetpos(binFile, &position);
			position -= sizeof(int);
		}
		intFirst = intSecond;
		fread(&intSecond, sizeof(int), 1, binFile);
	}
	fsetpos(binFile, &position);
	fread(&intSecond, sizeof(int), 1, binFile);
	int numberSmallest = ((int)((int)(position)) / sizeof(int)) + 1;
	printf(" Smallest multiplexing with previous has number %d, position %d\n", intSecond, numberSmallest);
	fclose(binFile);
}

void change(char* fileName)
{
	FILE* binFile;
	int intFirst, intSecond;
	fpos_t arrayPosition, currentPosition, maxPosition;
	fopen_s(&binFile, fileName, "r+b");
	if (!binFile) {
		printf(" Can't open file %s", fileName);
		return;
	}
	fseek(binFile, 0, SEEK_END);
	fgetpos(binFile, &maxPosition);
	rewind(binFile);

	fgetpos(binFile, &arrayPosition);
	while (arrayPosition < maxPosition) {
		fgetpos(binFile, &currentPosition);
		fread(&intFirst, sizeof(int), 1, binFile);

		fgetpos(binFile, &arrayPosition);
		if (arrayPosition >= maxPosition) {
			break;
		}

		fread(&intSecond, sizeof(int), 1, binFile);
		fgetpos(binFile, &arrayPosition);
		fsetpos(binFile, &currentPosition);

		fwrite(&intSecond, sizeof(int), 1, binFile);
		fwrite(&intFirst,sizeof(int), 1, binFile);
		currentPosition += sizeof(int) * 2;
		fsetpos(binFile, &currentPosition);
	}
	fclose(binFile);
}

void output(char* fileName)
{
	FILE* binFile;
	int buffer;
	fpos_t currentPosition, maxPosition;
	fopen_s(&binFile, fileName, "r+b");
	if (!binFile) {
		printf(" Can't open file %s", fileName);
		return;
	}
	fseek(binFile, 0, SEEK_END);
	fgetpos(binFile, &maxPosition);
	rewind(binFile);
	fgetpos(binFile, &currentPosition);
	printf("\n File %s has : ", fileName);
	while (currentPosition < maxPosition) {
		fgetpos(binFile, &currentPosition);
		fread(&buffer, sizeof(int), 1, binFile);

		printf("%d   ", buffer);
		fgetpos(binFile, &currentPosition);
	}
	printf("\n");
	fclose(binFile);
}

void sort(char* fileName, char mod)
{
	FILE* binFile;
	int intFirst, intSecond, amount, i = 0;
	fpos_t position, pos, maxPosition;
	fopen_s(&binFile, fileName, "r+b");
	if (!binFile) {
		printf(" Can't open file %s", fileName);
		return;
	}
	fseek(binFile, 0, SEEK_END);
	fgetpos(binFile, &maxPosition);
	rewind(binFile);
	amount = maxPosition / sizeof(int);
	fgetpos(binFile, &position);
	if (mod == 'd') {
		while (i < amount) {
			rewind(binFile);
			fgetpos(binFile, &position);
			while (position < maxPosition - i * sizeof(int)) {
				fgetpos(binFile, &pos);
				fread(&intFirst, sizeof(int), 1, binFile);

				fgetpos(binFile, &position);
				if (position >= maxPosition) {
					break;
				}

				fread(&intSecond, sizeof(int), 1, binFile);
				if (intFirst < intSecond) {
					fgetpos(binFile, &position);
					fsetpos(binFile, &pos);

					fwrite(&intSecond, sizeof(int), 1, binFile);
					fwrite(&intFirst, sizeof(int), 1, binFile);
				}
				pos += sizeof(int);
				fsetpos(binFile, &pos);
			}
			i++;
		}
	}
	else {
		while (i < amount) {
			rewind(binFile);
			fgetpos(binFile, &position);
			while (position < maxPosition - i * sizeof(int)) {
				fgetpos(binFile, &pos);
				fread(&intFirst, sizeof(int), 1, binFile);

				fgetpos(binFile, &position);
				if (position >= maxPosition) {
					break;
				}

				fread(&intSecond, sizeof(int), 1, binFile);
				if (intFirst > intSecond) {
					fgetpos(binFile, &position);
					fsetpos(binFile, &pos);

					fwrite(&intSecond, sizeof(int), 1, binFile);
					fwrite(&intFirst, sizeof(int), 1, binFile);
				}
				pos += sizeof(int);
				fsetpos(binFile, &pos);
			}
			i++;
		}
	}
	fclose(binFile);
}
