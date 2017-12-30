/**
 * First project to IZP.
 * Created in CLion by Jakub Čábera <cabera.jakub@gmail.com> <xcaber00@stud.fit.vutbr.cz> on 10/5/16.
 */
//region Includes
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
//endregion

//region Defines
#define FALSE 0
#define TRUE 1
#define ERROR -1
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define RESET "\x1b[0m"
#define SEPARATOR "|"
#define OUT_OF_RANGE 4
#define INVALID_ARGUMENTS 5
#define HEX_ERROR 6
#define HEX_GROUP 2
#define LENGTH 16
#define HEX_OFFSET LENGTH
#define HEX_GROUPS 8
#define HEX_COLUMNS 16
//endregion

//region Completed functions
/**
 * Return "length" of char array.
 *
 * @param array Given array to measure.
 *
 * @return Length of given array.
 */
int arrayLength(char *array){
	int count = 0;
	while(array[count] != '\0') count++;
	return count;
}

/**
 * Compare two strings.
 *
 * @param left Left/First string to compare.
 * @param rigt Right/Second string to compare.
 *
 * @return 1 If strings are equal.
 */
int stringCompare(char *left, char *right){
	int leftCharLength = arrayLength(left);

	if(leftCharLength != arrayLength(right)) return FALSE;

	for(int index = 0; index < leftCharLength; index++) {
		if(left[index] != right[index]) return FALSE;
	}

	return TRUE;
}

/**
 * Determine if given character is number.
 *
 * @param character Character to analyze.
 * @return 1 If character is number.
 */
int isNumber(char character){
	return (int) character >= 48 && (int) character < 58
	       ? TRUE
	       : FALSE;
}

/**
 * Convert string to Integer.
 *
 * @param string String to convert
 * @return Final converted Integer.
 */
int stringToInt(char *string){
	int mult   = 1;
	int result = 0;
	int len    = arrayLength(string);

	for(int i = len - 1; i >= 0; i--) {
		if(!isNumber(string[i])){
			printf("Wrong data type");
			exit(2);
		}
		result = result + ((int) string[i] - '0') * mult;
		mult   = mult * 10;
	}

	return result;
}

/**
 *
 *
 * @param character Character to be translated.
 */
void decToHex(int character){
	printf("%02x", character);
}

/**
 * Determine if there is next character.
 *
 * @param character Analyze next character of this character.
 *
 * @return 1 If there is next character.
 */
int hasNext(char character){
	return character != '\0'
	       ? TRUE
	       : FALSE;
}

/**
 * Print error message and exit program with given statuscode.
 *
 * @param message Error message.
 * @param statusCode Error statuscode.
 */
void error(char *message, int statusCode){
	fprintf(stderr, RED "%s\n" RESET, message);
	exit(statusCode);
}

/**
 * Print help text and succesfully exit.
 */
void help(){
	printf(GREEN "Program should be run in this ways:\n"
			       "echo \"some text\" | ./proj1\n"
			       "echo \"some text\" | ./proj1 -s <S> -n <N>\n"
			       "echo \"some text\" | ./proj1 -x\n"
			       "printf 'some\\0text\\n\\0CC\\n' | ./proj1 -S <N>\n"
			       "echo \"48656c6c6fa\" | ./proj1 -r\n" RESET);
	exit(0);
}
//endregion

//region Completed flags
/**
 * All input data will be converted to hexadecimal format and printed to one line.
 */
void flagX(){
	int c;
	while((c = getchar()) != EOF){
		decToHex(c);
	}
	printf("\n");
}

//region Flag R
/**
 * Validate hexadecimal character.
 *
 * @param c Hexadecimal character for validation.
 *
 * @return Integer value of hex char.
 */
int validateHex(char c){
	if(isdigit(c)) return c % LENGTH;
	if(isalpha(c)) c = (char) tolower(c);
	/** Values must be 0-15 */
	if(c >= 'a' && c <= 'f') return (c - 'a') + 10;
	error("Invalid hex. Only [0-9a-fA-F]+ accepted", HEX_ERROR);

	return 0;
}

/**
 * Convert two hex values into its decimal value.
 *
 * @param firstHex
 * @param secondHex
 *
 * @return Converted integer from two hex values.
 */
int hexToDec(char firstHex, char secondHex){
	return validateHex(firstHex) * LENGTH + validateHex(secondHex);
}

/**
 * Print ASCII value of two hex characters.
 * @param firstHex
 * @param secondHex
 */
void hexToASCII(char firstHex, char secondHex){
	printf("%c", hexToDec(firstHex, secondHex));
}

/**
 * Convert hexadecimal sequence of chars to binary form.
 * White spaces are ignored.
 */
void flagR(){
	char c = '\0', buffer = '\0';
	int  i = 0;

	do{
		c = (char) getchar();
		if(isprint(c) && !isspace(c)){
			/** If i value is even => there are two characters => print */
			++i % 2 != 0
			? buffer = c
			: hexToASCII(buffer, c);
		}
	}while(c != EOF && c != '\n');

	i % 2 != 0
	? hexToASCII('0', buffer)
	: 0;
}
//endregion

//region Flag SN
/**
 * Print adress of line.
 *
 * @param count
 */
void offset(int count){
	printf("%08x ", count);
}

/**
 * Print string after hex values.
 *
 * @param buffer Buffer for iterating through and print its text.
 */
void text(char *buffer){
	printf(" "SEPARATOR);

	for(int l = 0; l < HEX_GROUP * 8; l++) printf("%c", buffer[l]);

	printf(SEPARATOR);
}

/**
 * Output format consist of sequence of lines, where each line describes a series of 16 bytes from input file.
 * Each look like:
 * 			 <AAAAAAAA  xx xx xx xx xx xx xx xx  xx xx xx xx xx xx xx xx  |bbbbbbbbbbbbbbbb|>
 * If there are no flags (-s or -n) function will be called with s = 0, n = -1.
 *
 * @param skip Determine how many chars will be skipped (ignored).
 * @param numberOfChars Determine maximum length of "string". If -1 run to EOF
 *
 * @example 00000000  48 65 6c 6c 6f 2c 20 77  6f 72 6c 64 21 20 41 68  |Hello, world! Ah|
 *  		00000010  6f 6a 20 73 76 65 74 65  21 0a                    |oj svete!.      |
 */
void flags_s_n(int skip, int numberOfChars){
	if(numberOfChars == 0) error("Invalid input", INVALID_ARGUMENTS);

	int  i, counter = 0;
	char c          = '\0';

	for(i = 0; i < skip; i++) {
		c = (char) getchar();
	}

	char buffer[LENGTH];

	for(i = skip; c != EOF && i != numberOfChars; i += LENGTH) {
		/** ADRESS */
		offset(i);

		/** HEX */
		for(int j = 0; j < HEX_GROUP; j++) { //2
			printf(" ");
			for(int k = 0; k < HEX_GROUPS; k++) { //8
				counter++;
				c = (char) getchar();
				if(c != EOF && (counter <= numberOfChars || numberOfChars == -1)){
					printf("%02x ", c);
					if(c < ' '){
						buffer[j * HEX_GROUPS + k] = '.';
					} else {
						buffer[j * HEX_GROUPS + k] = c;
					}
				} else {
					printf("   ");
					buffer[j * HEX_GROUPS + k] = 32;
				}
			}
		}
		/** TEXT */
		text(buffer);
		/** End print if counter is bigger than number */
		if(counter > numberOfChars && numberOfChars != -1) c = EOF;
		/** Line fold */
		printf("\n");
	}
}
//endregion
//endregion

//region Flags in progress
/**
 * Print character consequences that looks like string.
 * Each string is printed on one line.
 * Limitation: 0 < N < 200.
 *
 * @param n Length of consequence.
 */
void flagS(int n){
	if(!(n > 0 && n < 200)) error("Argument is not permitted.", OUT_OF_RANGE);

	int buffer[n], c = getchar();

	for(int i = 0; c != EOF; i++) {
		if((isprint(c) || isblank(c)) && i < n){
			buffer[i] = c;
			c = getchar();
			continue;
		} else if(i >= n){
			for(int j = 0; j < n; j++) {
				printf("%c", buffer[j]);
			}
			while((isprint(c) || isblank(c))){
				printf("%c", c);
				c = getchar();
			}
			i         = -1;
			printf("\n");
		} else {
			i = -1;
			c = getchar();
			continue;
		}
	}
}

/**
 * Handle arguments and determine, which operation will be executed.
 *
 * @param argCount Quantity of arguments.
 * @param arguments String array.
 *
 * @return 	-1 If there is invalid argument.
 * 			1 If there are only 1 argument (filename).
 * 			2 If there is <-r> argument.
 * 			3 If there is <-x> argument.
 * 			4 If there is <-S> and its value.
 * 			5 If there are <-s> <-n> and their values.
 */
int argumentHandler(int argCount, char *arguments[]){
	char *s, *n, *S;
	switch(argCount){
		/** One argument (filename) */
		case 1:{
			flags_s_n(0, -1);
			return 1;
		}

		case 2:{
			/** Two arguments => r or x => or error state (empty -s or -n) */
			if(stringCompare(arguments[1], "-r")){
				flagR();
				return 2;
			} else if(stringCompare(arguments[1], "-x")){
				flagX();
				return 3;
			}

			error("Error while processing argument.", INVALID_ARGUMENTS);
			return ERROR;
		}

		case 3:{
			/** Three arguments => S and value */
			if(stringCompare(arguments[1], "-S") && isNumber(*arguments[2])){
				S = arguments[2];
				flagS(stringToInt(S));
				return 4;
			} else {
				error("Error while processing -S argument.", INVALID_ARGUMENTS);
				return ERROR;
			}
		}

		case 5:{
			/** i+=2 => skip number values of each argument */
			for(int i = 1; i < argCount; i += 2) {
				if(!(stringCompare(arguments[i], "-n") ||
				     stringCompare(arguments[i], "-s")) &&
				   isNumber(*arguments[i + 1])){
					return ERROR;
				} else {
					if(stringCompare(arguments[i], "-n")){
						n = arguments[i + 1];
					} else if(stringCompare(arguments[i], "-s")){
						s = arguments[i + 1];
					}
				}
			}
			flags_s_n(stringToInt(s), stringToInt(n));
			return 5;
		}

		default: help();
			return ERROR;
	}
}
//endregion

int main(int argc, char *argv[]){
	argumentHandler(argc, argv);
	return 0;
}
