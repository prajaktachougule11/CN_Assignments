#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>
using namespace std;
bool validateIP(string ip, vector<int>& oct) {
stringstream ss(ip);
string o;
oct.clear();
while(getline(ss,o,'.')) {
if(o.empty()) return false;
for(int i=0;i<o.length();i++) if(!isdigit(o[i])) return false;
int v=atoi(o.c_str());
if(v<0||v>255) return false;
oct.push_back(v);
}
return oct.size()==4;
}
void getClass(int first, string& cls, string& range, string& mask,
int& nets, int& hosts, string& purpose) {
if(first==0||first==127) {
cls="Special (Reserved)";
range=(first==0)?"0.0.0.0 - 0.255.255.255":"127.0.0.0 -
127.255.255.255";
mask="N/A"; nets=0; hosts=0;
purpose=(first==0)?"Reserved for default route":"Reserved
for loopback";
}
else if(first>=1&&first<=126) { cls="Class A"; range="1.0.0.0 -
126.255.255.255"; mask="255.0.0.0"; nets=126; hosts=16777214;
purpose="Large networks"; }
else if(first>=128&&first<=191) { cls="Class B"; range="128.0.0.0
- 191.255.255.255"; mask="255.255.0.0"; nets=16384;
hosts=65534; purpose="Medium networks"; }
else if(first>=192&&first<=223) { cls="Class C"; range="192.0.0.0
- 223.255.255.255"; mask="255.255.255.0"; nets=2097152;
hosts=254; purpose="Small networks"; }
else if(first>=224&&first<=239) { cls="Class D"; range="224.0.0.0
- 239.255.255.255"; mask="N/A"; nets=0; hosts=0;
purpose="Multicast"; }
else { cls="Class E"; range="240.0.0.0 - 255.255.255.255";
mask="N/A"; nets=0; hosts=0; purpose="Experimental"; }
}
int main() {
string ip;
vector<int> oct;
cout<<"Enter IPv4 address: ";
cin>>ip;
if(!validateIP(ip,oct)) { cout<<"Invalid IP!\n"; system("pause");
return 1; }
string cls,range,mask,purpose;
int nets,hosts;
getClass(oct[0],cls,range,mask,nets,hosts,purpose);
cout<<"\n============================================\n
";
cout<<"IP: "<<ip<<"\nClass: "<<cls<<"\nRange: "<<range<<"\n";
if(mask!="N/A") cout<<"Subnet Mask: "<<mask<<"\nNetwork
IDs: "<<nets<<"\nUsable Hosts: "<<hosts<<"\n";
else cout<<"Subnet Mask: Not applicable\n";
cout<<"Purpose:
"<<purpose<<"\n========================================
====\n";
system("pause");
return 0;
}
