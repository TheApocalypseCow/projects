//-----------------------------------------------------------------------------
// Arithmetic.cpp
// Top Level client for the project 
//-----------------------------------------------------------------------------
// Rohan Anand 
// PA 6
// CRUZ ID: ranand1
// ----------------------------------------------------------------------------

#include <stdio.h> 
#include <iostream> 
#include <string> 
#include <stdexcept> 
#include <fstream> 
// #include <iomanip>
#include "List.h"
#include "BigInteger.h"

using namespace std;

int main(int argc, char * argv[]) {
	ifstream in; 
	ofstream out; 
	string contents;
       	BigInteger A, B; 	
	
	if ( argc != 3) {
		cerr << "Usage: " << argv[0] << " <input file> <output file" << endl;
		return(EXIT_FAILURE); 
	}

	in.open(argv[1]); 
	if ( !in.is_open() ) {
		cerr << "Unable to open input file." << endl; 
		return(EXIT_FAILURE); 
	}

	out.open(argv[2]); 
	if ( !out.is_open() ) {
		cerr << "Unable to open output file." << endl; 
		return(EXIT_FAILURE); 
	}
	
	int count = 0; 
	while (getline(in, contents)) {
		if (count == 0) {
			A = BigInteger(contents); 
		}
		if (count == 2) {
			B = BigInteger(contents); 
		}
		count++; 
	}

	out << A << endl;
	out << endl; 
	out << B << endl;
       	out << endl; 
	out << A+B << endl; 
       	out << endl; 
	out << A-B << endl; 
       	out << endl; 
	out << A-A << endl; 	
       	out << endl;
       	BigInteger Q = 3*A; 
	BigInteger R = 2*B; 	
	out << Q-R << endl; 	
       	out << endl; 
	out << A*B << endl; 	
       	out << endl; 
	out << A*A << endl; 	
       	out << endl; 
	out << B*B << endl; 	
       	out << endl; 
	out << 9*(A*A*A*A) + 16*(B*B*B*B*B) << endl; 

	in.close(); 
	out.close(); 

	return(EXIT_SUCCESS); 
}


























#if 0
	string s1 = "9128734667000004389234563456345619187236478";
   	string s2 = "-330293847502398475";
   	string s3 = "9876545439000000000000000200000000000006543654365346534";
   	string s4 = "9876545439000000000000000100000000000006543654365346534";
   	string s5 = "98765454390000000000000000000000000000065436543";
   	string s6 = "9876545439000000000000000000000000000006543";
//	BigInteger A = BigInteger(s1); 
//	BigInteger B = BigInteger(s2);
//	BigInteger C = BigInteger(s3);
//	BigInteger D = BigInteger(s4);
//	BigInteger E = BigInteger(s5);
//	BigInteger F = BigInteger(s6);
//	BigInteger G = F;
	BigInteger R = BigInteger("+2276072577093344144759489101587794740543956923406513235017249485312182256620379054691648041393022029"); 
	BigInteger S = BigInteger("+9521651023449965519405564118547355094880066777565423238991085675906554459642294029683201863865856036"); 
       	cout << endl; 	
       	/*
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
	*/
	cout << "R: " << R << endl; 
	cout << "S: " << S << endl; 
	R *= S;
       	//BigInteger Result2 = R - S; 
       	//BigInteger Result3 = R - R; 
	//BigInteger Result4 = R * S; 

	cout << "R (new): " << R << endl; 	
	//cout << "Sub: " << Result2 << endl; 	
	//cout << "Sub (A-A): " << Result3 << endl;
	//cout << "Mult: " << Result4 << endl; 


	return 0; 
}
#endif
