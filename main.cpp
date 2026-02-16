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
