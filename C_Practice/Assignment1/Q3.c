/* CS261- Assignment 1 - Q.3*/
/* Name: Zachary Wetekamm
 * Date: 10/8/18
 * Solution description: Program converts a user input string
 * to lower camel case.
 */

#include <stdio.h>
#include <stdlib.h>



char toUpperCase(char ch) {
	/*Convert ch to upper case, assuming it is in lower case currently*/
	// Use the difference between ASCII values
	return ch - 'a' + 'A';
}

char toLowerCase(char ch) {
	/*Convert ch to lower case, assuming it is in upper case currently*/
	// Use the difference between ASCII values
	return ch - 'A' + 'a';
}

int stringLength(char s[]) {
	/*Return the length of the string*/
	int i = 0;

	// '\0' terminator is at end of string
	while (s[i] != '\0') {
		i++;
	}

	return i;
}


void camelCase(char* word) {
	/*Convert to camelCase*/
	int length;
	int i = 0;
	int j = 0;

	// determine the length of string
	length = stringLength(word);


	do {
		// convert alphabet character after space to uppercase
		if ((i == 0 || word[i-1] == ' ') && (word[i] >= 97 && word[i] <= 122)) {
			word[i] = toUpperCase(word[i]);
		}
			// convert alphabet character to lowercase
		else if ((word[i] >= 65 && word[i] <= 90) && word[i] != ' ') {
			word[i] = toLowerCase(word[i]);
		}
		i++;

	} while (i != length);

	i = 0;
	// overwrite the word array using new counter j
	// which increments after each alphabetical char
	while (word[i] != '\0') {

		// if is alphabetical character
		if ((word[i] >= 65 && word[i] <= 90) ||
			(word[i] >= 97 && word[i] <= 122)) {

			word[j++] = word[i];
		}
		i++;
	}
	// end the new string with null terminator
	word[j] = '\0';
}


int main() {

	// create array of characters for input
	char input[25];

	/*Read the string from the keyboard*/
	printf("Enter a string:\n");

	// Piazza question provided a helpful link
	// https://stackoverflow.com/questions/6282198/reading-string-from-input-with-space-character
	scanf("%[^\n]%*c", input);

	/*Call camelCase*/
	camelCase(input);

	/*Print the new string*/
	printf("%s\n", input);

	return 0;
}

