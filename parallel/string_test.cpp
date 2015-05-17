#include <iostream>
#include <cstdlib>
#include <string.h>
#include <sstream>
using namespace std;

/*void itoa(int i, char *string)
{
int power=0;
int j=i;
while(j!=0){
j/=10;
power++;
}
for(int k=0;k<power;k++){
j=i%10;
i/=10;
*string+='0'+j;
}
*string='\0';
}*/


int main()
{
string s="Hello";
cout<<s<<endl;
s+="World";
cout<<s<<endl;
/*int i=1;
s+='0'+i;
cout<<s<<endl;
*/
ostringstream a;
int i=101;
a<<i;
string astr=a.str();
s+=astr;
cout<<s<<endl;

char aa[50];
//*a="message";
//cout<<*a<<endl;
strcpy(aa,s.c_str());
//a+=" of ";
cout<<aa<<endl;

return 0;
}
