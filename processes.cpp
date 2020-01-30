#include "tinbes.h"

#define TABLE_SIZE 25
#define RUNNING 'r'
#define PAUSED 'p'

string processName[TABLE_SIZE];
int id[TABLE_SIZE];
char state[TABLE_SIZE];
long addr[TABLE_SIZE];
int noOfProcesses = 0;
int idCounter = 0;

int newProcess(string name, long address) {
  // TO DO
  if(name.size() <= 10)
  {
    addr[idCounter] = address;
    state[idCounter] = RUNNING;
    id[idCounter] = idCounter;
    processName[idCounter] = name;
  
  noOfProcesses++;
  return idCounter++;
  } 
  else {
    return -1;
  }
  // DONE
}

void removeProcess(int i) {
  noOfProcesses--;
  for (int j = i; j < noOfProcesses; j++) 
  {
    // TO DO
    id[i]= (id[i+1])-1;
    state[i]=state[i+1];
    processName[i]= processName[i+1];
    addr[i]= (addr[i+1])-1;

    // DONE

  }
}

void executeProcesses() {
  long newAddr;
  for (int i = 0; i < noOfProcesses; i++) {
    if (state[i] == RUNNING) {
      // TO DO
        newAddr = addr[i]--;
      // DONE
      if (newAddr == 0) {
        cout << "Process \"" << processName[i] << "\" has terminated." << endl;
        removeProcess(i--);
      } else {
        addr[i] = newAddr;
      }
    }
  }
}

void listProcesses() {
  for (int i = 0; i < noOfProcesses; i++) {
    cout << id[i] << ' ' << processName[i] << ' ' << state[i] << endl;
  }
}

int findProcess(int i) {
  for (int j = 0; j < noOfProcesses; j++) 
  {
    // TO DO
      if( j == i){
        return j;
      }
    // DONE

    
     
  }
  return -1;
}

void suspendProcess(int i) {
  int j = findProcess(i);
  if (j == -1) {
    cout << "Process does not exist." << endl;
    return;
  }
  if (state[j] == PAUSED) {
    cout << "Process already paused." << endl;
  }
  else {
    // TO DO
    state[j] = PAUSED;
    // DONE

  }
}

void resumeProcess(int i) {
  int j = findProcess(i);
  if (j == -1) {
    cout << "Process does not exist." << endl;
    return;
  }
  if (state[j] == RUNNING) {
    cout << "Process already running." << endl;
  }
  else {
    // TO DO
    state[j] = RUNNING;
    // DONE

  }
}

void killProcess(int i) {
  int j = findProcess(i);
  if (j == -1) {
    cout << "Process does not exist." << endl;
  } else {
    // TO DO
    processName[j] = -1;
    id[j] = -1;
    state[j] = -1;
    addr[j] = -1;
    noOfProcesses--;
    // DONE
    
  }
}

int main() {
  unblockCin();
  string command;
  while (true) {
    if (charactersAvailable()) {
      command = readLine();
      if (command == "RUN") {
        string name = readLine();
        long address = stoi(readLine());
        cout << newProcess(name, address) << endl;
      }
      if (command == "LIST") {
        listProcesses();
      }
      if (command == "SUSPEND") {
        int i = stoi(readLine());
        suspendProcess(i);
      }
      if (command == "RESUME") {
        int i = stoi(readLine());
        resumeProcess(i);
      }
      if (command == "KILL") {
        int i = stoi(readLine());
        killProcess(i);
      }
    }
    else {
      executeProcesses();
    }
  }
}
