/*
 * This program checks if a given number is an armstrong number or not.
 * An armstrong number is one whose value is equal to the sum of the cubes of its digits.
 * eg. 153=1^3 + 5^3 + 3^3
 */
#include<stdio.h>
int main() {
	int n;
	printf("Enter a number: ");
	scanf("%d", &n);	//getting the number
	int flag=0;	//flag for marking armstrong number
	if(n>=0) {
		int y=n, d, s=0;	//y stores copy of n, d stores each digit, s stores sum of cubes of digits
		while(y!=0) {
			d=y%10;	//getting a digit
			s+=d*d*d;	//adding cube of the digit
			y/=10;	//removing last digit
		}
		flag=s==n;	//checking if sum of cubes equals the number or not
	}
	printf("%d is%s an armstrong number.\n", n, flag?"":" not");	//output
	return 0;
}