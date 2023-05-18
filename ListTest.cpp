// TEST CLIENT FOR LIST ADT
// ListTest.cpp
// Rohan Anand 
// PA 5
// CRUZ ID: ranand1


#include <iostream>
#include <string>
#include <stdexcept> 
#include "List.h"

using namespace std; 

int main() {
	List A, B;
	A.insertBefore(34);
	A.insertBefore(77);
    	A.insertBefore(77);
    	A.insertAfter(1);
    	A.insertAfter(34);
    	A.insertAfter(1);
	A.moveFront(); 
    	A.insertBefore(55);
    	A.insertBefore(77);
	cout << "A = " << A << endl; 
	cout << "99 exists?: " << A.findPrev(99) << endl; 
	cout << "position: " << A.position() << endl; 
    	A.moveBack();
	cout << "1 exists?: " << A.findPrev(1) << endl; 
	cout << "1 exists?: " << A.findPrev(1) << endl; 
	cout << "1 exists?: " << A.findPrev(1) << endl; 
	cout << "position: " << A.position() << endl; 
       		
	cout << "element: " << A.peekNext() << endl;
       	A.moveNext(); 	
	cout << "element: " << A.peekPrev() << endl;
       	B.insertBefore(81); 
	B.insertAfter(12); 
	List C = A.concat(B); 	
	cout << "C = " << C << endl; 	
	C.moveNext(); 
	C.setAfter(12); 
	C.setBefore(4); 
	cout << "C = " << C << endl; 
	A = C; 
	cout << "A = " << C << endl; 
	if (C == A) {
		cout << "equal" << endl; 
	}
	A.clear(); 
	A.insertBefore(100000); 
	A.insertBefore(200000); 
	A.insertBefore(200000); 
	A.insertBefore(100000); 
	A.insertBefore(200000); 
	A.insertBefore(300000);
	A.insertBefore(100000);
	A.findPrev(3); 

	cout << "position: " << A.position() << endl; 
	cout << "A = " << A  << endl; 
	cout << A.position() << endl; 	
}
