#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int printHex(unsigned char *buffer, int numOfBytes, int offset) {
	int prevI = 0;
	for(int i = 0; i < numOfBytes; i++) {
		if(i % 16 == 0) {
		
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

		if(cmd == 'p') {
			printHex(buffer + loc, 16, loc);
		else if(cmd == 'x') {
		}
			fclose(file);
			return 0;
		}
	}
}
