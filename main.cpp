#include <cstdio>
#include <cmath>
#include <conio.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <windows.h>
using namespace std;
int const N=3;
int sign(int val) {
  if (val == 0)  return 0;
  if (val > 0)  return 1;
  else return -1;
}
int mod(int n, int d)
{
    int result = n % d;
    if (sign(result) * sign(d) < 0)
        result += d;
    return result;
}
using namespace std;
void rash_euclid(int a, int b, int *x, int *y, int *d) //extended euclid algorithm
{
    long q,r,x1,x2,y1,y2;
    if (b==0) {
        *d=a; *x=1; *y=0;
        return;
    }
    x2=1; x1=0; y2=0; y1=1;
    while (b>0) {
        q=a/b; r=a-q*b; *x=x2-q*x1; *y=y2-q*y1;
        a=b; b=r; x2=x1; x1=*x; y2=y1; y1=*y;
    }
    *d=a; *x=x2; *y=y2;
}

int inverse(int a, int n)
{
    int d,x,y;
    rash_euclid(a,n,&x,&y,&d);
    if (d==1) {
        return x; }
    return 0;
}
int main()
{
    setlocale(LC_ALL,"Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    cout << "========================================================================" << endl;
    cout << "================== Hill's cypher (encrypt and decrypt) =================" << endl;
    cout << "======================== MAI cryptographic course ======================" << endl;
    cout << "========================================================================" << endl;
    cout << "============================= Alphabet used: ===========================" << endl;
    string alph="ABCDEFGHIJKLMNOPQRSTUVWXYZàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþÿ ,.:!?"; //26 upper English letters, 33 lower Russian letters, space, comma, point, colon, exclamation and question marks
    cout << alph << endl;
    cout << "========================================================================" << endl;
    int K[3][3], C[3][3], A[3][3];
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            K[i][j]=0; A[i][j]=0; C[i][j]=0;
        }
    }
    string s, shifr, deshifr; shifr=""; deshifr="";
    cout << "Enter the open text: " << endl;
    getline(cin, s);
    int kt=s.length();
    cout << "kt: " << kt << endl;
    if (kt%3!=0) {
        while (kt%3!=0) {
            s+=' ';
            kt++;
        }
    }
    cout << "Positions of letters in alphabet above:" << endl;
    for (int i=0; i<s.length(); i++) {
        cout << alph.find(s[i]) << " ";
    }
    cout << endl;

    cout << "Enter the matrix key:" << endl;
    cout << "Example key: AAFDEHCHA" << endl;
    string key;
    cin >> key;
    //Forming a key
    if ((key.length())!=9) {
        cout << "Incorrect number of symbols in key. Please enter 9 symbols exactly" << endl;
    }
    else {
        for (int i=0; i<N; i++) {
            for (int j=0; j<N; j++) {
                K[i][j]=alph.find(key[0]);
                key.erase(0,1);
            }
        }
    }
    cout << K[0][0] << " " << K[0][1] << " " << K[0][2] << endl;
    cout << K[1][0] << " " << K[1][1] << " " << K[1][2] << endl;
    cout << K[2][0] << " " << K[2][1] << " " << K[2][2] << endl;
    int z=0;
    int ls=s.length();
    //Encrypt
    while (ls>0) {
        for (int i=0; i<N; i++) {
            A[0][i]=alph.find(s[i]);
        }
        for (int i=0; i<N; i++) {
            for (int j=0; j<N; j++) {
                C[0][i]+=K[i][j]*A[0][j];
            }
            C[0][i]=C[0][i]%64;
            int f=C[0][i];
            int p=alph[f];
            shifr+=p;
            C[0][i]=0; f=0; p=0;
        }
        ls-=3;
        s.erase(0,3);
    }
    cout << "============================ ENCRYPTED TEXT: ===========================" << endl;
    cout << shifr << endl;
    for (int i=0; i<shifr.length(); i++) {
        cout << alph.find(shifr[i]) << " ";
    }
    cout << endl;
    cout << "========================================================================" << endl;
    int det00=(K[1][1]*K[2][2]-K[1][2]*K[2][1])%64;
    int det10=(K[0][1]*K[2][2]-K[0][2]*K[2][1])%64;
    int det20=(K[0][1]*K[1][2]-K[1][1]*K[0][2])%64;
    int det01=(K[1][0]*K[2][2]-K[1][2]*K[2][0])%64;
    int det11=(K[0][0]*K[2][2]-K[0][2]*K[2][0])%64;
    int det21=(K[0][0]*K[1][2]-K[0][2]*K[1][0])%64;
    int det02=(K[1][0]*K[2][1]-K[1][1]*K[2][0])%64;
    int det12=(K[0][0]*K[2][1]-K[0][1]*K[2][0])%64;
    int det22=(K[0][0]*K[1][1]-K[0][1]*K[1][0])%64;
    int det=(K[0][0]*det00-K[0][1]*det01+K[0][2]*det02)%64;
    if (det<0) {
        det=mod(det,64);
    }
    int S[3][3];
    S[0][0]=det00; S[0][1]=det10; S[0][2]=det20;
    S[1][0]=det01; S[1][1]=det11; S[1][2]=det21;
    S[2][0]=det02; S[2][1]=det12; S[2][2]=det22;
    cout << "Matrix without bullshit: " << endl;
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            cout << mod(S[i][j],64) << " ";
        } cout << endl;
    }
    S[0][0]=det00; S[0][1]=-det10; S[0][2]=det20;
    S[1][0]=-det01; S[1][1]=det11; S[1][2]=-det21;
    S[2][0]=det02; S[2][1]=-det12; S[2][2]=det22;
    //Inverse element for module 64:
    int inv=inverse(det,64);
    //Allied Matrix:
    for(int i=0; i<N; i++) {
            for(int j=0; j<N; j++) {
                S[i][j]=(inv*(mod(S[i][j],64)))%64;
            }
        }
    ls=shifr.length();
    cout << "========================================================================" << endl;
    cout << "Service information: " << endl;
    cout << "Code matrix determinant: " << det << endl;
    cout << "Union transposed matrix:" << endl;
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            cout << S[i][j] << " ";
        } cout << endl;
    }
    cout << "Inversive element by 64: " << inv << endl;
    cout << "Length of decrypting text: " << ls << endl;
    cout << "========================================================================" << endl;
    float X[3][3];
    for (int i=0; i<N; i++) {
        A[0][i]=0;
        X[0][i]=0;
    }
    while (ls>0)
    {
        for (int i=0; i<N; i++) {
            A[0][i]=alph.find(shifr[i]);
        }
        for(int i=0; i<N; i++) {
            for(int j=0; j<N; j++) {
                X[0][i]+=S[i][j]*A[0][j];
            }
            X[0][i]=((int)X[0][i])%64;
            int f=X[0][i];
            int p=alph[f];
            deshifr+=p;
            X[0][i]=0; f=0; p=0;
        }
        ls-=3;
        shifr.erase(0,3);
        for (int i=0; i<N; i++){
            A[0][i]=0; X[0][i]=0;
        }
    }
    cout << "============================ DECRYPTED TEXT: ===========================" << endl;
    cout << deshifr << endl;
    cout << "========================================================================" << endl;
    return 0;
}
