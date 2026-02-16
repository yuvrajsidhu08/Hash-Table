#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "node.h"

using namespace std;

// Simple hash function using ID
int hashID(int id, int size) {
  return id % size;
}

// Double table size and rehash all students
void rehash(Node**& table, int& size) {
  int oldSize = size;
  size *= 2;

  // Create new larger table
  Node** newTable = new Node*[size];
  for (int i = 0; i < size; i++)
    newTable[i] = 0;

  // Move every student into new table
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

// Add a student into the hash table
void addStudent(Node**& table, int& size, Student* s) {
  int index = hashID(s->getID(), size);

  // Insert at front of linked list
  Node* n = new Node(s);
  n->setNext(table[index]);
  table[index] = n;

  // Count nodes in this chain
  int count = 0;
  Node* current = table[index];
  while (current) {
    count++;
    current = current->getNext();
  }

  // If more than 3 collisions, resize table
  if (count > 3)
    rehash(table, size);
}

// Print all students in table
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

// Remove a student by ID
void removeStudent(Node** table, int size, int id) {
  int index = hashID(id, size);

  Node* curr = table[index];
  Node* prev = 0;

  while (curr) {
    if (curr->getStudent()->getID() == id) {
      if (!prev)
        table[index] = curr->getNext();
      else
        prev->setNext(curr->getNext());

      delete curr;
      return;
    }
    prev = curr;
    curr = curr->getNext();
  }
}

// Load names from file into dynamic array
char** loadNames(const char* file, int& count) {
  ifstream f(file);
  char temp[100];
  count = 0;

  // Count lines first
  while (f.getline(temp, 100))
    count++;

  f.clear();
  f.seekg(0);

  // Allocate array of C-strings
  char** names = new char*[count];

  for (int i = 0; i < count; i++) {
    f.getline(temp, 100);
    names[i] = new char[strlen(temp) + 1];
    strcpy(names[i], temp);
  }

  return names;
}

int main() {
  srand(time(0));

  int size = 100;
  Node** table = new Node*[size];

  // Initialize table to null
  for (int i = 0; i < size; i++)
    table[i] = 0;

  int id = 1; // Auto-increment student ID

  // Load name files
  int fCount, lCount;
  char** first = loadNames("first.txt", fCount);
  char** last = loadNames("last.txt", lCount);

  char cmd[20];

  // Main command loop
  while (true) {
    cout << "\nADD PRINT DELETE GENERATE QUIT\n";
    cin >> cmd;

    // Manually add student
    if (!strcmp(cmd, "ADD")) {
      char f[50], l[50];
      float g;

      cin >> f >> l >> g;

      addStudent(table, size,
                 new Student(f, l, id++, g));
    }

    // Print all students
    else if (!strcmp(cmd, "PRINT"))
      print(table, size);

    // Delete by ID
    else if (!strcmp(cmd, "DELETE")) {
      int d;
      cin >> d;
      removeStudent(table, size, d);
    }

    // Generate random students
    else if (!strcmp(cmd, "GENERATE")) {
      int n;
      cin >> n;

      for (int i = 0; i < n; i++) {
        addStudent(
          table,
          size,
          new Student(
            first[rand() % fCount],
            last[rand() % lCount],
            id++,
            (rand() % 401) / 100.0f
          )
        );
      }
    }

    // Exit program
    else if (!strcmp(cmd, "QUIT"))
      break;
  }
}
