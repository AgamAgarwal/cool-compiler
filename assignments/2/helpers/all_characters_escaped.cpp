#include<iostream>
using namespace std;
int main() {
	char x=35;
	while(x<127)
		cout<<"\\"<<(x++);
	return 0;
}