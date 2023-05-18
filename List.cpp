//-----------------------------------------------------------------------------
// List.cpp
// Implementation file for List ADT
//-----------------------------------------------------------------------------
// Rohan Anand 
// PA 6
// CRUZ ID: ranand1

#include <iostream> 
#include <string> 
#include <stdexcept> 
#include "List.h"

// Private Constructor --------------------------------------------------------

List::Node::Node(ListElement x) {
	data = x;
	next = nullptr; 
	prev = nullptr; 
}

// Class Constructor & Destructors --------------------------------------------

List::List() {
	frontDummy = new Node(-1); 
	backDummy = new Node(-1); 

	frontDummy->next = backDummy; 
	backDummy->prev = frontDummy; 

	beforeCursor = frontDummy; 
	afterCursor = backDummy; 

	pos_cursor = 0; 
	num_elements = 0; 
}

List::List(const List& L) {
	frontDummy = new Node(-1); 
	backDummy = new Node(-1); 

	frontDummy->next = backDummy; 
	backDummy->prev = frontDummy; 

	beforeCursor = frontDummy;
       	afterCursor = backDummy; 

	pos_cursor = 0; 
	num_elements = 0; 
	
	Node *N = L.frontDummy->next; 
	while (num_elements != L.num_elements) {
		insertAfter(N->data); 
		N = N->next; 
		if (pos_cursor < length()) {
			moveNext(); 
		}	
	}
	moveFront(); 	
}

List::~List() {
	moveFront(); 
	while(num_elements > 0) {
		eraseAfter(); 
	}
	delete frontDummy; 
	delete backDummy; 
}

// Access functions ------------------------------------------------------------

int List::length() const {
	return num_elements; 
}

ListElement List::front() const {
	if (num_elements == 0) {
		throw std::length_error("List: front(): empty List"); 
	}
	return frontDummy->next->data; 
}

ListElement List::back() const {
	if (num_elements == 0) {
		throw std::length_error("List: back(): empty List"); 
	}
	return backDummy->prev->data; 
}

int List::position() const {
	return pos_cursor; 
}

ListElement List::peekNext() const {
	if (num_elements == 0) {
		throw std::length_error("List: peekNext(): empty List"); 
	} 
	if (num_elements == pos_cursor) {
		throw std::length_error("List: peekNext(): cursor on last position"); 
	}
	return afterCursor->data; 
}

ListElement List::peekPrev() const {
	if (num_elements == 0) {
		throw std::length_error("List: peekPrev(): empty List"); 
	} 
	if (pos_cursor == 0) {
		throw std::length_error("List: peekPrev(): cursor on index 0"); 
	}
	return beforeCursor->data; 
}

void List::clear() {
	moveFront(); 
	while(num_elements > 0) {
		eraseAfter(); 
	}
	return; 
}

void List::moveFront() {
	pos_cursor = 0; 
	beforeCursor = frontDummy; 
	afterCursor = frontDummy->next; 
	return; 
}

void List::moveBack() {
	pos_cursor = num_elements; 
	beforeCursor = backDummy->prev; 
	afterCursor = backDummy; 
	return; 
}

ListElement List::moveNext() {
	if (length() == pos_cursor) {
		throw std::length_error("List: moveNext(): cursor on last index"); 
	}
	pos_cursor++; 
	beforeCursor = beforeCursor->next; 
	afterCursor = afterCursor->next; 
	return beforeCursor->data; 
}

ListElement List::movePrev() {
	if (pos_cursor == 0) {
		throw std::length_error("List: movePrev(): cursor on index 0"); 
	}
	pos_cursor--; 
	beforeCursor = beforeCursor->prev; 
	afterCursor = afterCursor->prev; 
	return afterCursor->data; 
}

void List::insertAfter(ListElement x) {
	Node* N = new Node(x); 
	N->next = afterCursor; 
	N->prev = beforeCursor;
	beforeCursor->next = N; 
	afterCursor->prev = N; 
	afterCursor = N; 
	num_elements++; 
	return; 
}

void List::insertBefore(ListElement x) {
	Node* N = new Node(x); 
	N->next = afterCursor; 
	N->prev = beforeCursor;
	beforeCursor->next = N; 
	afterCursor->prev = N; 
	beforeCursor = N; 
	pos_cursor++; 
	num_elements++; 
	return; 
}

void List::setAfter(ListElement x) {
	if (length() == pos_cursor) {
		throw std::length_error("List: setAfter(): cursor on last index"); 
	}
	afterCursor->data = x; 
	return; 
}

void List::setBefore(ListElement x) {
	if (pos_cursor == 0) {
		throw std::length_error("List: setBefore(): cursor on index 0"); 
	}
	beforeCursor->data = x; 	
	return; 
}

void List::eraseAfter() {
	if (num_elements == 0) {
		throw std::length_error("List: eraseAfter(): empty List"); 
	}
	if (length() == pos_cursor) {
		throw std::length_error("List: eraseAfter(): cursor on last index"); 
	}
	Node *N = afterCursor;
       	afterCursor = afterCursor->next; 	
	beforeCursor->next = N->next;
	afterCursor->prev = beforeCursor; 
	num_elements--; 
	delete N; 
	return; 
}

void List::eraseBefore() {
	if (num_elements == 0) {
		throw std::length_error("List: eraseAfter(): empty List"); 
	}
	if (pos_cursor == 0) {
		throw std::length_error("List: eraseAfter(): cursor index at 0"); 
	}
	Node *N = beforeCursor; 
	beforeCursor = beforeCursor->prev; 
	beforeCursor->next = afterCursor; 
	afterCursor->prev = beforeCursor;
       	pos_cursor--; 	
	num_elements--; 
	delete N; 
	return; 
}

// Other Functions -------------------------------------------------------------

int List::findNext(ListElement x) {
	ListElement y; 
	while (pos_cursor < num_elements) {
		y = moveNext(); 
		if (y == x) {
			return pos_cursor; 		
		}
	}
	return -1; 
}

int List::findPrev(ListElement x) {
	ListElement y; 
	while(pos_cursor > 0) {
		y = movePrev(); 
		if (y == x) {
			return pos_cursor; 
		}
	}
	return -1; 
}

// from TA pseudocode 

void List::cleanup() {
	Node *dup, *cur = frontDummy->next;	
	int inner_ct, outer_ct = 0; 
	while(cur != backDummy) {
		inner_ct = outer_ct+1; 
		dup = cur->next; 
		while (dup != backDummy) {
			if (cur->data == dup->data) {
				if (beforeCursor == dup) {
					beforeCursor = beforeCursor->prev; 
				} else if (afterCursor == dup) {
					afterCursor = afterCursor->prev; 
				}

				if (this->position() > inner_ct) {
					inner_ct--; 
					pos_cursor--; 
				}

				dup->next->prev = dup->prev; 
				dup->prev->next = dup->next; 
				delete dup; 
				num_elements--; 
			}
			inner_ct++; 
			dup = dup->next; 
		}
		outer_ct++; 
		cur = cur->next; 
	}
}
/*	
	
	if (length() == 0 || length() == 1) {
		return; 
	}
	List L;
	Node* T; 
       	Node* N = frontDummy->next; 
	while (N != backDummy) {
		T = N; 
		N = N->next; 
		L.moveFront(); 
		if (L.findNext(T->data) == -1) {
			L.insertBefore(T->data); 
		} else {
			T->prev->next = T->next; 
			T->next->prev = T->prev;	
			delete T; 
			num_elements--; 	
		}
	}
	return; 
}
*/
/*
void List::cleanup() {
	if (length() == 0 || length() == 1) {
		return; 
	}
	Node* N;
	ListElement y;
       	for (N = frontDummy->next; N != backDummy; N = N->next) {	
		y = N->data;
		std::cout << "y: " << y;
		std::cout << "    " << findNext(y);
		std::cout << std::endl;		
		while (findNext(y) != -1) {
			eraseBefore(); 
		       	// reset cursor
			//moveFront(); 
			//findNext(y); 	
		}
	}	
	return; 
}
*/

List List::concat(const List& L) const{
	List F; 
	Node* N = this->frontDummy->next; 
	Node* M = L.frontDummy->next; 
	while (N != this->backDummy) {
		F.insertBefore(N->data); 
		N = N->next; 
	}
	while (M != L.backDummy) {
		F.insertBefore(M->data); 
		M = M->next; 
	}
	F.moveFront(); 
	return F;
}

// Note: to_string function modified to print BigInteger

std::string List::to_string_big_int(int power) const {
	Node *N = nullptr; 
	std::string s = ""; 
	for (N = backDummy->prev; N != frontDummy; N = N->prev) {
		if (N->data == 0) {
			for (int i = 1; i <= power; i++) {
				s += "0"; 
			}	
		} else {
			std::string y = std::to_string(N->data); 
			if ((y.length() != (size_t) power) && (N != backDummy->prev)) {
				int num_zero = power - y.length(); 
				for (int i = 1; i <= num_zero; i++) {
					y.insert(0, "0"); 
				}
				s += y; 
			} else {	
				s += std::to_string(N->data);
			}
		}
	}
	return s; 
}

std::string List::to_string() const {
	Node* N = nullptr; 
	std::string s = "(";
	for (N = frontDummy->next; N != backDummy; N = N->next) {
		s += std::to_string(N->data) + " "; 
	}
	if (!s.empty()) {
		s.pop_back(); 
	}
	s += ")";
	return s; 
}

void List::make_negative() {
	Node *N = nullptr; 
	for (N = frontDummy->next; N != backDummy; N = N->next) {
		N->data = N->data * -1; 
	}
	return; 
}

bool List::equals(const List& L) const {
	bool eq = false; 
	Node* N = nullptr; 
	Node* M = nullptr; 

	eq = ( this->num_elements == L.num_elements ); 
	N = this->frontDummy->next; 
	M = L.frontDummy->next; 
	while ( eq && N!=backDummy ) {
		eq = (N->data == M->data); 
		N = N->next; 
		M = M->next; 
	}
	return eq; 
}

// Overriden Operators ---------------------------------------------------------

std::ostream& operator<< ( std::ostream& stream, const List& L ) {
	return stream << L.List::to_string(); 
}

bool operator== (const List& A, const List& B) {
	return A.List::equals(B); 
}

List& List::operator=(const List& L) {
	if (this != &L) {
		List temp = L; 

		std::swap(frontDummy, temp.frontDummy); 
		std::swap(backDummy, temp.backDummy); 
		std::swap(beforeCursor, temp.beforeCursor); 
		std::swap(afterCursor, temp.afterCursor); 
		std::swap(num_elements, temp.num_elements); 
		std::swap(pos_cursor, temp.pos_cursor); 
	}
	return *this; 
}

/*
void List::cleanup() {
	if (length() == 0) {
		return; 
	}
	ListElement y; 
	moveFront();	
	while(pos_cursor < num_elements) {
		y = moveNext(); 
		if (findPrev(y) == -1) {
			
		}
	}
}*/
