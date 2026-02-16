#ifndef NODE
#define NODE

#include <iostream>
#include "Student.h"

class Node{
  public:	
    Node(Student*new_value, Node*new_next); // constructor
    ~Node(); // destructor
    void set_value(Student*new_value); // changes the student
    Student* get_value(); // returns a pointer to the student
    void set_next(Node*new_next); // changes the link
    Node* get_next(); // returns a pointer to the linked node
  private:
    Student* value; // value (student)
    Node* next; // link
};

#endif
