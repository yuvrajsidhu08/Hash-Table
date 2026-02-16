#include "student.h"
#include <cstring>

// Initializes student data and copies name strings
Student::Student(const char* f, const char* l, int i, float g) {
  first = new char[strlen(f) + 1];
  strcpy(first, f);

  last = new char[strlen(l) + 1];
  strcpy(last, l);

  id = i;
  gpa = g;
}

// Deletes dynamically allocated memory
Student::~Student() {
  delete[] first;
  delete[] last;
}

// Returns the first name
const char* Student::getFirst() {
  return first;
}

// Returns the last name
const char* Student::getLast() {
  return last;
}

// Returns the student ID
int Student::getID() {
  return id;
}

// Returns the student GPA
float Student::getGPA() {
  return gpa;
}
