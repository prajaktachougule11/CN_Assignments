#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <cstdlib>
using namespace std;
struct IP {
int o1,o2,o3,o4;
IP(int a=0,int b=0,int c=0,int d=0):o1(a),o2(b),o3(c),o4(d){}
};
int toInt(string s){ return atoi(s.c_str()); }
string toString(IP ip){
char buf[20];
sprintf(buf,"%d.%d.%d.%d",ip.o1,ip.o2,ip.o3,ip.o4);
return string(buf);
}
bool validate(string ip, IP& a) {
stringstream ss(ip);
string o;
int c=0;
while(getline(ss,o,'.')) {
if(o.empty()) return false;
for(int i=0;i<o.length();i++) if(!isdigit(o[i])) return false;
int v=toInt(o);
if(v<0||v>255) return false;
if(c==0)a.o1=v;
else if(c==1)a.o2=v;
else if(c==2)a.o3=v;
else if(c==3)a.o4=v;
c++;
}
return c==4;
}
string getClass(int o) {
if(o>=1&&o<=126) return "A";
else if(o>=128&&o<=191) return "B";
else if(o>=192&&o<=223) return "C";
else return "Invalid";
}
unsigned int ipToInt(IP a) {
return (a.o1<<24)|(a.o2<<16)|(a.o3<<8)|a.o4;
}
IP intToIP(unsigned int x) {
return IP((x>>24)&0xFF,(x>>16)&0xFF,(x>>8)&0xFF,x&0xFF);
}
string maskToStr(int prefix) {
unsigned int m=0xFFFFFFFF<<(32-prefix);
return toString(intToIP(m));
}
void printHeader(string title) {
cout << "\n" << string(80, '=') << endl;
cout << " " << title << endl;
cout << string(80, '=') << endl;
}
void printSubHeader(string title) {
cout << "\n" << string(80, '-') << endl;
cout << " " << title << endl;
cout << string(80, '-') << endl;
}
int main() {
string ipStr, subStr;
IP ip;
cout << "\n
======================================================
===========" << endl;
cout << " CLASSFUL IPv4 SUBNET CALCULATOR" << endl;
cout << "
======================================================
===========" << endl;
cout << "\n [*] Enter an IPv4 address: ";
cin >> ipStr;
if(!validate(ipStr,ip)) {
cout << "\n [!] ERROR: Invalid IP address format!" << endl;
cout << " [!] Please ensure the address contains exactly four
octets," << endl;
cout << " [!] each between 0 and 255.\n" << endl;
system("pause");
return 1;
}
string cls=getClass(ip.o1);
if(cls=="Invalid") {
cout << "\n [!] ERROR: This program only supports Class A, B,
and C addresses." << endl;
cout << " [!] The entered address falls outside these
ranges.\n" << endl;
system("pause");
return 1;
}
int defPrefix=(cls=="A")?8:(cls=="B")?16:24;
int hostBits=32-defPrefix;
string
defMask=(cls=="A")?"255.0.0.0":(cls=="B")?"255.255.0.0":"255.25
5.255.0";
cout << " [*] Required number of subnets: ";
cin >> subStr;
for(int i=0;i<subStr.length();i++) {
if(!isdigit(subStr[i])) {
cout << "\n [!] ERROR: Invalid input! Please enter a positive
integer.\n" << endl;
system("pause");
return 1;
}
}
int numSub=toInt(subStr);
if(numSub<=0) {
cout << "\n [!] ERROR: Number of subnets must be
positive.\n" << endl;
system("pause");
return 1;
}
int borrow=0;
for(int i=0;i<=hostBits;i++) {
if(pow(2.0,i)>=numSub) {
borrow=i;
break;
}
}
if(borrow>hostBits) {
cout << "\n [!] ERROR: Not enough host bits available!" <<
endl;
cout << " [!] Maximum subnets possible with " << hostBits <<
" host bits: "
<< (int)pow(2.0,hostBits) << endl;
cout << " [!] Requested: " << numSub << " subnets\n" <<
endl;
system("pause");
return 1;
}
int newPrefix=defPrefix+borrow;
int totalSubs=(int)pow(2.0,borrow);
int remBits=hostBits-borrow;
int totalAddrs=(int)pow(2.0,remBits);
int usable=totalAddrs-2;
int block=totalAddrs;
string newMask=maskToStr(newPrefix);
unsigned int netAddr=ipToInt(ip) &
((cls=="A")?0xFF000000:(cls=="B")?0xFFFF0000:0xFFFFFF00);
printHeader("SUBNETTING SUMMARY");
cout << " IP Address Entered : " << ipStr << endl;
cout << " IP Class : Class " << cls << endl;
cout << string(80, '-') << endl;
cout << " Default Subnet Mask : " << defMask << endl;
cout << " Default Prefix Length : /" << defPrefix << endl;
cout << string(80, '-') << endl;
cout << " Borrowed Bits : " << borrow << " bits" << endl;
cout << " New Subnet Prefix Length : /" << newPrefix << endl;
cout << " New Subnet Mask : " << newMask << endl;
cout << string(80, '-') << endl;
cout << " Total Generated Subnets : " << totalSubs << endl;
cout << " Remaining Host Bits : " << remBits << " bits" <<
endl;
cout << " Total Addresses/Subnet : " << totalAddrs << endl;
cout << " Usable Hosts/Subnet : " << usable << endl;
cout << " Block Size (Increment) : " << block << endl;
cout << string(80, '-') << endl;
cout << " Classful Network Address : " <<
toString(intToIP(netAddr)) << endl;
cout << string(80, '=') << endl;
printSubHeader("SUBNET DETAILS");
cout << " " << left << setw(10) << "Subnet"
<< setw(20) << "Network"
<< setw(20) << "First Host"
<< setw(20) << "Last Host"
<< setw(20) << "Broadcast"
<< setw(18) << "Mask"
<< "CIDR" << endl;
cout << string(80, '-') << endl;
unsigned int curr=netAddr;
for(int i=0;i<totalSubs && i<100;i++) {
unsigned int net=curr;
cout << " " << left << setw(10) << (i+1)
<< setw(20) << toString(intToIP(net))
<< setw(20) << toString(intToIP(net+1))
<< setw(20) << toString(intToIP(net+block-2))
<< setw(20) << toString(intToIP(net+block-1))
<< setw(18) << newMask
<< "/" << newPrefix << endl;
curr+=block;
}
cout << string(80, '-') << endl;
cout << "\n [*] Note: Network and broadcast addresses are
NOT counted as usable hosts.\n" << endl;
cout << string(80, '=') << "\n" << endl;
system("pause");
return 0;
}
