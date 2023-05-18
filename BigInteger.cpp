//-----------------------------------------------------------------------------
// BigInteger.cpp
// BigInteger implementation file 
//-----------------------------------------------------------------------------
// Rohan Anand 
// PA 6
// CRUZ ID: ranand1
// ----------------------------------------------------------------------------

#include <iostream>
#include <string> 
#include <stdexcept>
#include <string> 
#include <cmath>
#include "BigInteger.h"
#include "List.h"

// Global Variables -----------------------------------------------------------
/*
int POWER { 9 };  
const long BASE { (long)pow(10, POWER)  }; 
*/
// Private Constructor --------------------------------------------------------

BigInteger::BigInteger() {
	signum = 0; 
	digits = List(); 
}


BigInteger::BigInteger(std::string s) {
	if (s[0] != '-') {
		this->signum = 1; 
	} else {
		this->signum = -1; 
	}

	if (!(isdigit(s[0]))) {
		s = s.substr(1); 
	}

	s = s.erase(0, s.find_first_not_of('0')); 

	if (s.length() == 0) {
		this->signum = 0; 
	} else if (s.length() != 0) {
		std::string substring;
		while (s.length() > 0) {
			if (s.length() < POWER) {
				substring = s; 
			} else {
				substring = s.substr(s.length() - POWER); 
			}
			digits.insertBefore(std::stol(substring));
		       	int y = s.length() - substring.length();	
			s = s.substr(0, y); 
		}
	}
	// std::cout << "Digit List: " << digits << std::endl;
       	// std::cout << BASE << std::endl; 	
	// std::cout << "Sign: " << signum << std::endl; 
}

BigInteger::BigInteger(const BigInteger& N) {
	signum = N.signum; 
	digits = N.digits;  
}

// Access functions ----------------------------------------------------------

int BigInteger::sign() const {
	return signum; 
}

int BigInteger::compare(const BigInteger& N) const {
	if (this->signum == 0 && N.signum == 0) {
		return 0; 
	}
	if (this->signum > N.signum) {
		return 1; 
	} 
	if (this->signum < N.signum) {
		return -1; 
	} 
	if (this->digits == N.digits) {
		return 0; 
	}
	// two cases, each with two cases: 
	// 	+ both positive
	// 		- digits equal length
	// 		- digits not equal length
	// 	+ both negative
	// 		- digits equal length
	// 		- digits not equal length
	List L = this->digits;
       	List M = N.digits; 	
	if (this->signum == 1 && N.signum == 1) {
		if (L.length() == M.length()) {
			L.moveFront(); 
			M.moveFront(); 
			while (L.position() < L.length()) {
				if (L.peekNext() > M.peekNext()) {
					return 1; 
				} else if (L.peekNext() < M.peekNext()) {
					return -1; 
				} else {
					L.moveNext();
					M.moveNext(); 
				}
			}
			return 0; 
		} else {
			if (L.length() > M.length()) {
				return 1; 
			} else {
				return -1; 
			}
		}
	} else {
		if (L.length() == M.length()) {
			L.moveFront(); 
			M.moveFront(); 
			while (L.position() < L.length()) {
				if (L.peekNext() > M.peekNext()) {
					return -1; 
				} else if (L.peekNext() < M.peekNext()) {
					return 1; 
				} else {
					L.moveNext();
					M.moveNext(); 
				}
			}
			return 0; 
		} else {
			if (L.length() > M.length()) {
				return -1; 
			} else {
				return 1; 
			}
		}
	}
}

// Manipulation procedures ---------------------------------------------------

void BigInteger::makeZero() {
	signum = 0; 
	digits.clear(); 
	return; 
}

void BigInteger::negate() {
	if (signum == 1) {
		signum = -1; 
	} else if (signum == -1) {
		signum = 1; 
	}
	return; 
}

// BigInteger Arithmetic operations -------------------------------------------

void sumList(List &S, List A, List B, int sgn) {
	A.moveFront(); 
	B.moveFront(); 
	S.clear(); 
	S.moveFront(); 
	ListElement x; 
	ListElement data_A, data_B, data_S; 
	if (A.length() == 0 && B.length() == 0) {
		return; 
	} else if (A.length() == 0) {
		while (B.position() < B.length()) {
			x = B.moveNext(); 
			S.insertBefore(sgn*x); 
		}
		return; 
	} else if (B.length() == 0) {
		while (A.position() < A.length()) {
			x = A.moveNext(); 
			S.insertBefore(x); 
		}
		return; 
	}
	while ((A.position() < A.length()) || (B.position() < B.length())) {
		if (A.position() == A.length()) {
			while (B.position() < B.length()) {
				x = B.moveNext(); 
				S.insertBefore(sgn*x); 
			}
			return; 
		} else if (B.position() == B.length()) {
			while (A.position() < A.length()) {
				x = A.moveNext(); 
				S.insertBefore(x); 
			}
			return; 
		}
		data_A = A.moveNext(); 
		data_B = B.moveNext(); 
		if (sgn == -1) {
			data_B = data_B * -1; 
		}
		data_S = data_A + data_B; 
		S.insertBefore(data_S); 
	}
	return; 
}

int normalizeList(List &L) {
	if (L.length() == 0) {
		L.clear(); 
		return 0; 
	}
	int sign = 1; 

	if (L.back() < 0) {
		L.make_negative(); 
		sign = -1; 
	}
	if (L.back() == 0) {
		L.moveBack(); 
		ListElement x = L.peekPrev(); 
		while (x == 0) {
			if (L.length() != 0) {
				L.eraseBefore();
			}
			if (L.length() != 0) {
				x = L.peekPrev();
			} else {
				break; 
			}
		}
	}

	L.moveFront(); 
	ListElement current, remainder = 0, carry = 0; 

	while (L.position() < L.length()) {
		current = L.peekNext(); 
		current = current + carry; 
		if (current < BASE && current >= 0) {
			carry = 0; 
			L.setAfter(current); 
		} else if (current > BASE) {
			carry = current / BASE; 
			remainder = current - (carry*BASE); 
			L.setAfter(remainder); 
		} else if (current < 0) {
			carry = 0; 
		       	while (!(current < BASE && current >= 0)) {
				current += BASE; 
				carry--; 
			}	
			L.setAfter(current);
		}
		L.moveNext(); 
	}

	if (carry > 0) {
		L.insertBefore(carry); 
	}
	return sign; 
}

BigInteger BigInteger::add(const BigInteger& N) const {
	BigInteger R; 
	List S = List();
	
	if (this->sign() == N.sign()) {
		if (this->sign() == 0) {
			return R; 
		}
		R.signum = this->sign(); 
		sumList(S, this->digits, N.digits, 1);
		normalizeList(S); 
		R.digits = S; 
	} else {
		if (this->sign() == 0) {
			return N; 
		} else if (N.sign() == 0) {
			R.signum = this->sign();
		       	R.digits = this->digits; 	
		} else if (this->sign() == -1) {
			sumList(S, N.digits, this->digits, -1);
	       		R.signum = normalizeList(S);
		       	R.digits = S; 
		} else if (N.sign() == -1) {
			sumList(S, this->digits, N.digits, -1); 
			R.signum = normalizeList(S); 
			R.digits = S; 
		}
	}	
	if (R.digits.length() == 0) {
		R.signum = 0; 
	}

	return R; 
}

BigInteger BigInteger::sub(const BigInteger& N) const {
	BigInteger R; 
	List S = List(); 
	
	if (this->compare(N) == 0) {
		return R; 
	}
	
	if (this->sign() == 1 && N.sign() == 1) {
		sumList(S, this->digits, N.digits, -1); 
		R.signum = normalizeList(S); 
		R.digits = S; 
	} else if (this->sign() == -1 && N.sign() == -1) {
		sumList(S, N.digits, this->digits, -1);
	       	R.signum = normalizeList(S);
		R.digits = S; 
	} else if ( this->sign() == 1 && N.sign() == -1) {
		R.signum = 1; 
		sumList(S, this->digits, N.digits, 1);
		normalizeList(S); 
		R.digits = S; 
	} else if ( this->sign() == -1 && N.sign() == 1) {
		R.signum = -1; 
		sumList(S, this->digits, N.digits, 1);
		normalizeList(S); 
		R.digits = S; 
	} else if ( this->sign() == 0 && N.sign() == 0) {
		return R; 
	} else if ( this->sign() == 0 ) {
		R.digits = N.digits;
	if ( N.sign() == 1) {
			R.signum = -1; 	
		} else {
			R.signum = 1; 
		}	
		return R; 
	} else if ( N.sign() == 0) {
		return N; 
	}

	return R; 
}

void scalarMultList(List &L, ListElement m) {
	L.moveFront();
       	ListElement x;  
	while (L.position() < L.length()) {
		x = L.peekNext();  
		L.setAfter(x*m); 
		L.moveNext(); 
	}
	return; 
}

void shiftList(List &L, int shift) {
	L.moveFront(); 
	for (int i = 1; i <= shift; i++) {
		L.insertAfter(0); 
	}
	return; 
}


void normalize_m(List &L) {
	L.moveFront(); 
	ListElement current, remainder = 0, carry = 0; 

	while (L.position() < L.length()) {
		current = L.peekNext(); 
		current = current + carry; 
		if (current < BASE && current >= 0) {
			carry = 0; 
			L.setAfter(current); 
		} else if (current > BASE) {
			carry = current / BASE; 
			remainder = current - (carry*BASE); 
			L.setAfter(remainder);
			
		}
		L.moveNext(); 
	}
	while (carry > 0) {
		if (carry > BASE) {
			current = carry; 
			carry = current / BASE; 
			remainder = current - (carry*BASE); 
			L.insertBefore(remainder); 
		} else {
			L.insertBefore(carry); 
			carry = 0; 
		}
	}
	return; 
}

BigInteger BigInteger::mult(const BigInteger& N) const {
	BigInteger R; 
	if ((this->sign() == 1 && N.sign() == 1) || (this->sign() == -1 && N.sign() == -1)) {
		R.signum = 1;  
	}
	if ((this->sign() == 1 && N.sign() == -1) || (this->sign() == -1 && N.sign() == 1)) {
		R.signum = -1;  
	}
	if (this->sign() == 0 || N.sign() == 0) {
		return R; 
	}
	List S = List(); 
	List T = List();
	List Q = N.digits; 
	Q.moveFront(); 
	ListElement current; 
	while (Q.position() < Q.length()) {
		current = Q.peekNext();
		S = this->digits; 
		if (Q.position() != 0) {
			shiftList(S, Q.position()); 
		}
		scalarMultList(S, current);
	       	normalize_m(S); 	
		sumList(T, T, S, 1);
		normalize_m(T); 
		//std::cout << T << std::endl;
	       	//std::cout << std::endl; 	
	       	Q.moveNext(); 	
	}
	normalize_m(T);
       	R.digits = T; 	
	return R; 
}

// Other Functions ------------------------------------------------------------

std::string BigInteger::to_string() {
	std::string s = ""; 
	if (signum == 0) {
		s += "0"; 
		return s; 
	}	
	if (signum == -1) {
		s += "-"; 
	}
	s += digits.to_string_big_int(POWER); 	
	return s;
}

// Overriden Operators --------------------------------------------------------

std::ostream& operator<< ( std::ostream& stream, BigInteger N ) {
	return stream << N.BigInteger::to_string();  
}

bool operator== (const BigInteger& A, const BigInteger& B) {
	if (A.compare(B) == 0) {
		return true; 
	} 
	return false; 
}

bool operator<= (const BigInteger & A, const BigInteger& B) {
	if(A.compare(B) == 0 || A.compare(B) == -1) {
		return true; 
	}
	return false; 
}

bool operator>= (const BigInteger & A, const BigInteger& B) {
	if (A.compare(B) == 0 || A.compare(B) == 1) {
		return true; 
	}	
	return false; 
}

bool operator< (const BigInteger & A, const BigInteger& B) {
	if (A.compare(B) == -1) {
		return true; 
	}
	return false; 
}

bool operator> (const BigInteger & A, const BigInteger& B) {
	if (A.compare(B) == 1) {
		return true; 
	}
	return false; 
}

BigInteger operator+(const BigInteger& A, const BigInteger& B) {
	return A.add(B); 
}

BigInteger operator-(const BigInteger &A, const BigInteger& B) {
	return A.sub(B); 
}

BigInteger operator*(int scalar, const BigInteger &A) {
	BigInteger C; 
	List L = List();
      	L = A.digits; 
	scalarMultList(L, (ListElement) scalar); 
	normalize_m(L);
       	C.digits = L; 
	C.signum = A.sign(); 	
	return C; 
}

BigInteger operator*(const BigInteger &A, const BigInteger &B) {
	return A.mult(B); 
}

BigInteger& BigInteger::operator+=(const BigInteger &B) {
	if ( this!= &B ) {
		BigInteger temp = this->add(B); 
		std::swap(signum, temp.signum); 
		std::swap(digits, temp.digits); 
	}
	return *this; 
}

BigInteger& BigInteger::operator-=(const BigInteger &B) {
	if ( this!= &B ) {
		BigInteger temp = this->sub(B); 
		std::swap(signum, temp.signum); 
		std::swap(digits, temp.digits); 
	}
	return *this; 
}

BigInteger& BigInteger::operator*=(const BigInteger &B) {
	if ( this!= &B ) {
		BigInteger temp = this->mult(B); 
		std::swap(signum, temp.signum); 
		std::swap(digits, temp.digits); 
	}
	return *this; 
}
