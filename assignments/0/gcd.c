/*
 * This program takes two numbers as input and finds their greatest common divisor.
 */
#include<stdio.h>
//function to calculate the gcd using Euclidean algorithm
int gcd(int a, int b) {
	int t;	//t is temporary variable
	while(b!=0) {
		t=b;
		b=a%b;	//get remainder
		a=t;
	}
	return a;	//return gcd
}
int main() {
	int x, y;
	printf("Enter the two numbers:\n");
	scanf("%d\n%d", &x, &y);
	printf("The GCD is %d.\n", gcd(x, y));
	return 0;
}