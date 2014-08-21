#include<iostream>
using namespace std;
void convert(string s) {
	int i;
	for(i=0;i<s.length();i++)
		cout<<'['<<s[i]<<((char)(s[i]^32))<<']';
	cout<<"\t{ return (";
	for(i=0;i<s.length();i++)
		cout<<((char)(s[i]^32));
	cout<<"); }"<<endl;
}
int main() {
	string s;
	while(true) {
		cout<<"> ";
		cin>>s;
		convert(s);
	}
	return 0;
}