//-----------------------------------------------------------------------------
//  BigIntegerClient.cpp 
//  A test client for the BigInteger ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"BigInteger.h"

using namespace std;

int main(){

	string s1 = "91287346389234563456345619187236478";
   	string s2 = "-33029384798475";
   	string s3 = "98731465450000200000000000006543654365346534";
   	string s4 = "982700000000006543654365346534";
   	string s5 = "918765000000000000000000000065436543";
   	string s6 = "1198456876545439000000000000000000000000000006543";
	BigInteger A = BigInteger(s1); 
	BigInteger B = BigInteger(s2);
	BigInteger C = BigInteger(s3);
	BigInteger D = BigInteger(s4);
	BigInteger E = BigInteger(s5);
	BigInteger F = BigInteger(s6);
	BigInteger G = F;
	BigInteger R = BigInteger("+22760513235017249485312182256620379054691648041393022029"); 
	BigInteger S = BigInteger("0077565423238991085675906554459642294029683201863865856036"); 
       	cout << endl; 	
       	
	cout << "BigInteger A: " << A << endl; 
	cout << "String 1:     " << s1 << endl;	
	cout << "BigInteger B: " << B << endl; 
	cout << "String 2:     " << s2 << endl;	
	cout << "BigInteger C: " << C << endl; 
	cout << "String 3:     " << s3 << endl;	
	cout << "BigInteger D: " << D << endl; 
	cout << "String 4:     " << s4 << endl;	
	cout << "BigInteger E: " << E << endl; 
	cout << "String 5:     " << s5 << endl;	
	cout << "BigInteger F: " << F << endl; 
	cout << "String 6:     " << s6 << endl;	

	cout << endl; 

	cout << "compare A/B: " << A.compare(B) << endl; 
	cout << "compare C/D: " << C.compare(D) << endl; 
	cout << "compare G/F: " << G.compare(F) << endl;

	cout << "BigInteger G: " <<  G << endl;	
	G.negate(); 
	cout << "Negate G:     " << G << endl; 
	cout << "String 7:     " <<  s6 << endl;
       	G.makeZero(); 
	cout << "MakeZero G:   " << G << endl; 
	cout << endl; 
	
	cout << "R: " << R << endl; 
	cout << "S: " << S << endl; 
	R *= S;
	cout << "R: " << R << endl; 
       	BigInteger Result2 = R - S; 
	cout << "R: " << Result2 << endl; 
       	BigInteger Result3 = R - R; 
	cout << "R: " << Result3 << endl; 
	cout << A + B + C << endl; 
	cout << A * C * D << endl; 
	cout << 3*A - B << endl;

}	
