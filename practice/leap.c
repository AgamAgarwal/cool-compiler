/*
 * This program takes an year as input and prints if it is a leap year or not.
 */
#include<stdio.h>
int main() {
	int y, flag=0;
	printf("Enter the year: ");
	scanf("%d", &y);
	if(y<0)	//if negative year
		printf("Invalid year.\n");
	else {
		if(y%100==0)
			flag=y%400==0;
		else
			flag=y%4==0;
		printf("%sleap year\n", flag?"":"not ");
	}
	return 0;
}