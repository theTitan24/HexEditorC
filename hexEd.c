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
	printf("Offset:   ");
	
	for(int uI = 0; uI < 16; uI++) {
		printf("%.2x ", uI);
	}
	
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

int editHex(unsigned char *buffer, int  numOfBytes) {
	for(int i = 0; i < numOfBytes; i++) {
		scanf("%hhx", buffer + i);
	}
}

int main(int argc, char** argv) {

	FILE *file = fopen(argv[1], "r");
	if (file == NULL) {
		perror("Error: Specified File could not be opened. ");
		return(1);
	}

	int size = 1024;	

	unsigned char buffer[size];
	int numOfBytes = fread(buffer, 1, size, file);		

	printHex(buffer, numOfBytes, 0);
	printf("\n");
	
	// Now Let's listen for use input
	char cmd;
	int loc;
	
	while(true) {
		scanf("%c %x", &cmd, &loc);

		switch(cmd) {
			case 'h':
				printf("Command Syntax: [command] [memory address] \n");
				printf("\nSupported Commands: \n");
				printf("h : Prints this page \n");
				printf("l : Prints the rest of the hex from the given address. \n");
				printf("p : Prints 16 bytes from the given address. \n");
				printf("w : Change specified bytes of the file. \n");			
				printf("t : Displays the text contents of the given address \n");
				printf("x : Exit without saving changes (Use Memory address as 0) \n");
				printf("s : Exit saving changes (Use Memory address as 0) \n");
							
				printf("\n");

				break;
				
			case 'l':
				// Prints the entire Hex of the file
				printHex(buffer, numOfBytes - loc, loc);
				printf("\n");

				break;
			
			case 'p':
				// Prints 16 bytes from the given address
				printHex(buffer + loc, 16, loc);
				printf("\n");
					
				break;

			case 'w':
				// Change specified bytes of the file
				int wBytes;
				
				printf("How Many Bytes? " );
				scanf("%d", &wBytes);
				
				editHex(buffer + loc, wBytes);

				if(wBytes >= 16){
					printHex(buffer + loc, wBytes, loc);
				}
				else {
					printHex(buffer + loc, 16, loc);
				}
				printf("\n");
				
				break;

			case 't':
				// Prints the text content from the given address
				int n = 16;

				printf("How Many Bytes? ");
				scanf("%d", &n);
				
				printText(buffer + loc, n);
				printf("\n");
				
				break;

			case 'x':
				// Exits the program without saving changes
				fclose(file);
				
				return 0;

			case 's':
				// Exits the program after saving changes
				fclose(file);
				
				file = fopen(argv[1], "w");
				fwrite(buffer, 1, numOfBytes, file);
				fclose(file);
			
				return 0;
				 
		}
	}
}
