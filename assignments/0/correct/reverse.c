/*
 * This program takes a string as an input and prints its reverse.
 * eg.
 * Input - Cool
 * Output - looC
 */
#include<stdio.h>
#include<string.h>
int main() {
	char s[100];
	printf("Enter the string: ");
	scanf("%[^\n]", s);	//get the string
	int i=strlen(s);	//get its length
	while(--i>=0)	//decrease i and check if more than 0
		printf("%c", s[i]);	//print character
	printf("\n");
	return 0;
}