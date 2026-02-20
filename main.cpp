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

  Node** newTable = new Node*[size];
  for (int i = 0; i < size; i++)
    newTable[i] = 0;

  // Move every node into new table
  for (int i = 0; i < oldSize; i++) {
    while (table[i]) {
      Node* temp = table[i];
      table[i] = table[i]->get_next();

      int index = hashID(temp->get_value()->getID(), size);

      temp->set_next(newTable[index]);
      newTable[index] = temp;
    }
  }

  delete[] table;
  table = newTable;
}

// Add a student into the hash table
void addStudent(Node**& table, int& size, Student* s) {
  int index = hashID(s->getID(), size);

  // Your Node constructor needs 2 parameters
  Node* n = new Node(s, table[index]);
  table[index] = n;

  // Count nodes in this chain
  int count = 0;
  Node* current = table[index];

  while (current) {
    count++;
    current = current->get_next();
  }

  if (count > 3)
    rehash(table, size);
}

// Print all students
void print(Node** table, int size) {
  for (int i = 0; i < size; i++) {
    Node* current = table[i];
    while (current) {
      Student* s = current->get_value();
      cout << s->getFirst() << " "
           << s->getLast()
           << " | ID: " << s->getID()
           << " | GPA: "
           << fixed << setprecision(2)
           << s->getGPA() << endl;

      current = current->get_next();
    }
  }
}

// Remove a student by ID
void removeStudent(Node** table, int size, int id) {
  int index = hashID(id, size);

  Node* curr = table[index];
  Node* prev = 0;

  while (curr) {
    if (curr->get_value()->getID() == id) {

      if (!prev)
        table[index] = curr->get_next();
      else
        prev->set_next(curr->get_next());

      delete curr;
      return;
    }

    prev = curr;
    curr = curr->get_next();
  }
}

// Load names from file into dynamic array
char** loadNames(const char* file, int& count) {
  ifstream f(file);
  char temp[100];
  count = 0;

  while (f.getline(temp, 100))
    count++;

  f.clear();
  f.seekg(0);

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

  for (int i = 0; i < size; i++)
    table[i] = 0;

  int id = 1;

  int fCount, lCount;
  char** first = loadNames("first.txt", fCount);
  char** last = loadNames("last.txt", lCount);

  char cmd[20];

  while (true) {
    cout << "\nADD PRINT DELETE GENERATE QUIT\n";
    cin >> cmd;

    if (!strcmp(cmd, "ADD")) {
      char f[50], l[50];
      float g;
      cin >> f >> l >> g;

      addStudent(table, size,
                 new Student(f, l, id++, g));
    }

    else if (!strcmp(cmd, "PRINT"))
      print(table, size);

    else if (!strcmp(cmd, "DELETE")) {
      int d;
      cin >> d;
      removeStudent(table, size, d);
    }

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

    else if (!strcmp(cmd, "QUIT"))
      break;
  }

  return 0;
}
