#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int printText(unsigned char *buffer, int bytes) {
	for(int i = 0; i < bytes; i++) {
		char ch = (char)buffer[i];
		printf("%c", ch);
	}

	return 0;
}

int printHex(unsigned char *buffer, int numOfBytes, int offset) {
	int prevI = 0;
	printf("          0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f ");
	for(int i = 0; i < numOfBytes; i++) {
		if(i % 16 == 0) {
			if(i > 0) {
				printf(" | ");
				printText(buffer + prevI, 16);
			}	
			prevI = i;
			printf("\n%.8X: ", (offset + i));
		}
		
		printf("%.2X ", buffer[i]);
	}

	printf("\n");
}

int main(int argc, char** argv) {

	FILE *file = fopen(argv[1], "r");
	if (file == NULL) {
		perror("Error: Specified File could not be opened. ");
		return(1);
	}

	int size = 1024;
/*
	// To be implemented
	long size;
	fseek(file, 0, SEEK_END);
	size = ftell(file);
*/	

	unsigned char buffer[size];
	int numOfBytes = fread(buffer, 1, size, file);		

	printHex(buffer, numOfBytes, 0);

	// Now Let's listen for use input
	char cmd;
	unsigned int loc;
	
	while(true) {
		scanf("%c %x", &cmd, &loc);

		switch(cmd) {
			case 'p':
				// Prints 16 bytes from the given address
				printHex(buffer + loc, 16, loc);
				break;

			case 't':
				// Prints the text content from the given address
				int n = 16;
				printf("How many bytes? ");
				scanf("%d",&n);
				printText(buffer + loc, n);
				printf("\n");
				break;

			case 'x':
				// Exits the program
				fclose(file);
				return 0;
		}
	}
}
