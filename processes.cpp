/*
 * Berkant Ciftci
 * 0979368
 * TI1D
 * Opdracht: process
 */

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

int newProcess(string name, long address)
{

  char sToChArray[name.length()];

  if (noOfProcesses < 25)
  {
    if (name.length() > 10)
    {
      cout << "Het maximale aantal karakters in de naam is overschreden!" << endl;
      return -1;
    }
    else
    {
      for (int i = 0; i < sizeof(sToChArray); i++)
      {
        sToChArray[i] = name[i];
        if (sToChArray[i] == '0')
        {
          cout << " 0 is een verboden karakter!" << endl;
          return -1;
        }
        for (int i = 0; i < noOfProcesses; i++)
        {
          if (processName[i].compare(name) == 0)
          {
            cout << "Name is already taken." << endl;
            return -1;
          }
        }
        processName[noOfProcesses] = name;
        id[noOfProcesses] = idCounter;
        addr[noOfProcesses] = address;
        state[noOfProcesses] = PAUSED;
      }
    }
  }
  else
  {
    cout << "Het maximale aantal processen is overschreden!" << endl;
    return -1;
  }

  noOfProcesses++;
  return idCounter++;
}

void removeProcess(int i)
{
  noOfProcesses--;
  for (int j = i; j < noOfProcesses; j++)
  {

    processName[j] = processName[j + 1];
    id[j] = id[j + 1];
    addr[j] = addr[j + 1];
    state[j] = state[j + 1];
  }
}

void executeProcesses()
{
  long newAddr;
  for (int i = 0; i < noOfProcesses; i++)
  {
    if (state[i] == RUNNING)
    {

      newAddr = addr[i] - 1;
      if (newAddr == 0)
      {
        cout << "Process \"" << processName[i] << "\" has terminated." << endl;
        removeProcess(i--);
      }
      else
      {
        cout << processName[i] << ' ' << addr[i] << endl;
        addr[i] = newAddr;
      }
    }
  }
}

void listProcesses()
{
  for (int i = 0; i < noOfProcesses; i++)
  {
    cout << id[i] << ' ' << processName[i] << ' ' << state[i] << endl;
  }
}

int findProcess(int i)
{
  for (int j = 0; j < noOfProcesses; j++)
  {

    if (id[j] == i)
    {
      return j;
    }
  }
  return -1;
}

void suspendProcess(int i)
{
  int j = findProcess(i);
  if (j == -1)
  {
    cout << "Process does not exist." << endl;
    return;
  }
  if (state[j] == PAUSED)
  {
    cout << "Process already paused." << endl;
  }
  else
  {

    state[j] = PAUSED;
    cout << "Process \"" << processName[j] << "\" has been suspended." << endl;
  }
}

void resumeProcess(int i)
{
  int j = findProcess(i);
  if (j == -1)
  {
    cout << "Process does not exist." << endl;
    return;
  }
  if (state[j] == RUNNING)
  {
    cout << "Process already running." << endl;
  }
  else
  {

    state[j] = RUNNING;
    cout << "Process \"" << processName[j] << "\" has been resumed." << endl;
  }
}

void killProcess(int i)
{
  int j = findProcess(i);
  if (j == -1)
  {
    cout << "Process does not exist." << endl;
  }
  else
  {

    cout << "Process \"" << processName[j] << "\" has been removed." << endl;
    removeProcess(j);
  }
}

int main()
{
  unblockCin();
  string command;
  while (true)
  {
    if (charactersAvailable())
    {
      command = readLine();
      if (command == "RUN")
      {
        string name = readLine();
        long address = stoi(readLine());
        cout << newProcess(name, address) << endl;
      }
      if (command == "LIST")
      {
        listProcesses();
      }
      if (command == "SUSPEND")
      {
        int i = stoi(readLine());
        suspendProcess(i);
      }
      if (command == "RESUME")
      {
        int i = stoi(readLine());
        resumeProcess(i);
      }
      if (command == "KILL")
      {
        int i = stoi(readLine());
        killProcess(i);
      }
    }
    else
    {
      executeProcesses();
    }
  }
}
