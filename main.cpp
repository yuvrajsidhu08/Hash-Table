#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "node.h"

using namespace std;

int hashID(int id, int size) {
  return id % size;
}

void rehash(Node**& table, int& size) {
  int oldSize = size;
  size *= 2;

  Node** newTable = new Node*[size];
  for (int i = 0; i < size; i++) newTable[i] = 0;

  for (int i = 0; i < oldSize; i++) {
    while (table[i]) {
      Node* temp = table[i];
      table[i] = table[i]->getNext();

      int index = hashID(temp->getStudent()->getID(), size);
      temp->setNext(newTable[index]);
      newTable[index] = temp;
    }
  }

  delete[] table;
  table = newTable;
}

void addStudent(Node**& table, int& size, Student* s) {
  int index = hashID(s->getID(), size);

  Node* n = new Node(s);
  n->setNext(table[index]);
  table[index] = n;

   int count = 0;
  Node* current = table[index];
  while (current) {
    count++;
    current = current->getNext();
  }

  if (count > 3)
    rehash(table, size);
}

void print(Node** table, int size) {
  for (int i = 0; i < size; i++) {
    Node* current = table[i];
    while (current) {
      Student* s = current->getStudent();
      cout << s->getFirst() << " "
           << s->getLast()
           << " | ID: " << s->getID()
           << " | GPA: "
           << fixed << setprecision(2)
           << s->getGPA() << endl;
      current = current->getNext();
    }
  }
}
