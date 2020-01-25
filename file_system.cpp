#include "tinbes.h"

#define TABLE_SIZE 25

string name[TABLE_SIZE];
long addr[TABLE_SIZE];
long size[TABLE_SIZE];
int noOfFiles = 0;

void sort() {
  bool sorted = false;
  long tmp;
  string s;
  while (!sorted) {
    sorted = true;
    for (int i = 0; i < noOfFiles - 1; i++) {
      if (addr[i] > addr[i + 1]) {

        // TO DO

        sorted = false;
      }
    }
  }
}

long findFreeSpace(long fileSize) {
  sort();
  long prev = 0;
  for (int i = 0; i < noOfFiles; i++) {
    if (addr[i] - prev > fileSize) return prev;
    
    // TO DO

  }
  if (getSize() - prev > fileSize) return prev;
  return -1;
}

int findFile(string fileName) {
  for (int i = 0; i < noOfFiles; i++) {
    if (name[i] == fileName) return i;
  }
  return -1;
}

void store(long fileSize, string fileName, char *data) {
  int f = findFreeSpace(fileSize);
  if (f == -1) {
    cout << "Not enough space." << endl;    
  }
  else if (findFile(fileName) != -1) {
    cout << "File already exists." << endl;
  }
  else {

    // TO DO

    for (int i = 0; i < fileSize; i++) {
      writeByte(data[i], f + i);
    }
  }
}

string retrieve(string fileName) {
  int f = findFile(fileName);
  if (f == -1) {
    cout << "File not found." << endl;
    return string();
  }
  string ret;
  for (long a = addr[f]; a < addr[f] + size[f]; a++) {
    
    // TO DO

  }
  return ret;
}

void erase(string fileName) {
  int f = findFile(fileName);
  if (f == -1) {
    cout << "File not found." << endl;
    return;
  }

  // TO DO

}

void copy(string fileName1, string fileName2) {
  string contents = retrieve(fileName1);
  long fileSize = contents.length();
  if (fileSize > 0) {
    char *data = (char *)malloc(fileSize);
    contents.copy(data, fileSize);
    store(fileSize, fileName2, data);
    free(data);
  }
}

void rename(string fileName1, string fileName2) {
  int f = findFile(fileName1);
  if (f == -1) {
    cout << "File not found." << endl;
  }
  else if (findFile(fileName2) != -1) {
    cout << "File already exists." << endl;
  }
  else {
    
    // TO DO

  }
}

void files() {
  for (int i = 0; i < noOfFiles; i++) {
    cout << name[i] << '\t' << size[i] << endl;
  }
}

long freeSpace() {
  sort();
  long largest = 0, start = 0, length;
  for (int i = 0; i < noOfFiles; i++) {
    
    // TO DO

    if (length > largest) largest = length;
    start = addr[i] + size[i];
  }
  length = getSize() - start;
  if (length > largest) largest = length;
  return largest;
}

void pack() {
  sort();
  long pos = 0, newpos;
  for (int i = 0; i < noOfFiles; i++) {
    newpos = pos;    
    for (long a = addr[i]; a < addr[i] + size[i]; a++) {
      
      // TO DO
      
      pos++;
    }
    addr[i] = newpos;
  }
}

int main() {
  string command;
  while (true) {
    command = readLine();
    if (command == "STORE") {
      string fileName = readLine();
      long fileSize = stoi(readLine());
      char* data = (char *)malloc(fileSize);
      cin.read(data, fileSize);
      store(fileSize, fileName, data);
      free(data);
    }
    if (command == "RETRIEVE") {
      string fileName = readLine();
      string data = retrieve(fileName);
      if (data.length() > 0) cout << data << endl;
    }
    if (command == "ERASE") {
      string fileName = readLine();
      erase(fileName);
    }
    if (command == "COPY") {
      string fileName1 = readLine();
      string fileName2 = readLine();
      copy(fileName1, fileName2);
    }
    if (command == "RENAME") {
      string fileName1 = readLine();
      string fileName2 = readLine();
      rename(fileName1, fileName2);
    }
    if (command == "FILES") {
      files();
    }
    if (command == "FREESPACE") {
      cout << freeSpace() << endl;
    }
    if (command == "PACK") {
      pack();
    }
  }
}

