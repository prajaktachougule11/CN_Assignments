#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;
int main()
{
int m;
cout << "Enter number of data bits: ";
cin >> m;
int data[20];
cout << "Enter data bits: ";
for (int i = 1; i <= m; i++)
cin >> data[i];
int r = 0;
while (pow(2, r) < (m + r + 1))
r++;
int n = m + r;
int code[30];
int j = 1;
// Place data bits and parity positions
for (int i = 1; i <= n; i++)
{
if ((i & (i - 1)) == 0)
code[i] = 0;
else
{
code[i] = data[j];
j++;
}
}
// Calculate parity bits
for (int i = 0; i < r; i++)
{
int p = pow(2, i);
int parity = 0;
for (int k = 1; k <= n; k++)
{
if (k & p)
parity ^= code[k];
}
code[p] = parity;
}
cout << "\n========== TRANSMITTER SIDE ==========\n";
cout << "Generated Codeword: ";
for (int i = n; i >= 1; i--)
cout << code[i] << " ";
cout << endl;
cout << "\nPress Enter to continue...";
cin.ignore();
cin.get();
// Clear Screen (Windows)
system("cls");
// For Linux/macOS use: system("clear");
cout << "========== RECEIVER SIDE ==========\n";
int receive[30];
cout << "Enter received codeword: ";
for (int i = 1; i <= n; i++)
cin >> receive[i];
int error = 0;
// Check parity bits
for (int i = 0; i < r; i++)
{
int p = pow(2, i);
int parity = 0;
for (int k = 1; k <= n; k++)
{
if (k & p)
parity ^= receive[k];
}
if (parity)
error += p;
}
if (error == 0)
{
cout << "\nData received correctly." << endl;
}
else
{
cout << "\nError detected at position: " << error << endl;
receive[error] ^= 1;
cout << "Corrected Codeword: ";
for (int i = n; i >= 1; i--)
cout << receive[i] << " ";
cout << endl;
}
return 0;
}
