/*
 * This program takes several integers as input and prints their average to the nearest integer.
 * The input is stopped when the user enters a 0.
 * eg.
 * Input - 
 * 3
 * 4
 * 6
 * 0
 * Output -
 * 4
 */
#include<stdio.h>
int main() {
	int x, c=0, s=0;	//x stores the current number, c stores count of numbers, s stores the sum of the numbers
	printf("Enter the numbers(0 to end).\n");
	int flag=1;	//to check if 0 has been entered
	while(flag) {
		scanf("%d", &x);
		if(x==0)
			flag=0;
		else {
			c++;	//increase count
			s+=x;	//add to sum
		}
	}
	if(c==0)
		printf("Please enter atleast 1 number.\n");
	else
		printf("The average of the numbers is %d.\n", s/c);
	return 0;
}