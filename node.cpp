#include <iostream>
#include "student.h"
#include "node.h"
using namespace std;

// base functions for node class (linked lists)

Node::Node(Student*new_value, Node*new_next){ // constructor
	value = new_value;
	next = new_next;
}

Node::~Node(){ // destructor
	
	next = nullptr;
}

void Node::set_value(Student*new_value){
	value = new_value;
}

Student* Node::get_value(){
	return value;
}

void Node::set_next(Node*new_next){
	next = new_next;
}

Node* Node::get_next(){
	return next;
}
