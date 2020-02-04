/* Berkant Ciftci
 * 0979368
 * TINBES-01
 * TI1D
 */

#include "tinbes.h"

#define TABLE_SIZE 25

string name[TABLE_SIZE];
long addr[TABLE_SIZE];
long size[TABLE_SIZE];
int noOfFiles = 0;

void sort()
{
    bool sorted = false;
    long tmp;
    string s;
    while (!sorted)
    {
        sorted = true;
        for (int i = 0; i < noOfFiles - 1; i++)
        {
            if (addr[i] > addr[i + 1])
            {

                // Done.

                tmp = addr[i];
                addr[i] = addr[i + 1];
                addr[i + 1] = tmp;

                tmp = size[i];
                size[i] = size[i + 1];
                size[i + 1] = tmp;

                s = name[i];
                name[i] = name[i + 1];
                name[i + 1] = s;

                sorted = false;
            }
        }
    }
}

long findFreeSpace(long fileSize)
{
    sort();
    long prev = 0;
    for (int i = 0; i < noOfFiles; i++)
    {
        // Verbeteren.
        if (addr[i] - prev > fileSize)
        {
            // prev += 1;
            return prev;
        }
        else
        {

            prev = addr[i] + size[i];
        }
        if (getSize() - prev > fileSize)
            return prev;
        return -1;
    }
}

int findFile(string fileName)
{
    for (int i = 0; i < noOfFiles; i++)
    {
        if (name[i] == fileName)
            return i;
    }
    return -1;
}

void store(long fileSize, string fileName, char *data)
{
    int f = findFreeSpace(fileSize);
    if (f == -1)
    {
        cout << "Not enough space." << endl;
    }
    else if (findFile(fileName) != -1)
    {
        cout << "File already exists." << endl;
    }
    else
    {

        // Done.

        name[noOfFiles] = fileName;
        addr[noOfFiles] = f;
        size[noOfFiles] = fileSize;
        noOfFiles++;

        for (int i = 0; i < fileSize; i++)
        {
            writeByte(data[i], f + i);
        }
    }
}

string retrieve(string fileName)
{
    int f = findFile(fileName);
    if (f == -1)
    {
        cout << "File not found." << endl;
        return string();
    }
    string ret;
    for (long a = addr[f]; a < addr[f] + size[f]; a++)
    {

        // Done.

        ret += (char)readByte(a);
    }
    return ret;
}

void erase(string fileName)
{
    int f = findFile(fileName);
    if (f == -1)
    {
        cout << "File not found." << endl;
        return;
    }

    // Verbeterd.

    cout << "File is being erased." << endl;
    name[f].clear();
    addr[f] = 0;
    size[f] = 0;
    sort();
    noOfFiles = -1;

    cout << "Done!" << endl;
}

void copy(string fileName1, string fileName2)
{
    string contents = retrieve(fileName1);
    long fileSize = contents.length();
    if (fileSize > 0)
    {
        char *data = (char *)malloc(fileSize);
        contents.copy(data, fileSize);
        store(fileSize, fileName2, data);
        free(data);
    }
}

void rename(string fileName1, string fileName2)
{
    int f = findFile(fileName1);
    if (f == -1)
    {
        cout << "File not found." << endl;
    }
    else if (findFile(fileName2) != -1)
    {
        cout << "File already exists." << endl;
    }
    else
    {

        // Done
        name[f] = fileName2;
    }
}

void files()
{
    for (int i = 0; i < noOfFiles; i++)
    {
        cout << name[i] << '\t' << size[i] << endl;
    }
}

long freeSpace()
{
    sort();
    long largest = 0, start = 0, length;
    for (int i = 0; i < noOfFiles; i++)
    {

        // Verbeterd.
        length = addr[i + 1] - start;

        if (length > largest)
            largest = length;
        start = addr[i] + size[i];
    }
    length = getSize() - start;
    if (length > largest)
        largest = length;
    return largest;
}

void pack()
{
    sort();
    long pos = 0, newpos;
    for (int i = 0; i < noOfFiles; i++)
    {
        newpos = pos;
        for (long a = addr[i]; a < addr[i] + size[i]; a++)
        {

            // Not done.

            pos++;
        }
        addr[i] = newpos;
    }
}

int main()
{
    string command;
    while (true)
    {
        command = readLine();
        if (command == "STORE")
        {
            string fileName = readLine();
            long fileSize = stoi(readLine());
            char *data = (char *)malloc(fileSize);
            cin.read(data, fileSize);
            store(fileSize, fileName, data);
            free(data);
        }
        if (command == "RETRIEVE")
        {
            string fileName = readLine();
            string data = retrieve(fileName);
            if (data.length() > 0)
                cout << data << endl;
        }
        if (command == "ERASE")
        {
            string fileName = readLine();
            erase(fileName);
        }
        if (command == "COPY")
        {
            string fileName1 = readLine();
            string fileName2 = readLine();
            copy(fileName1, fileName2);
        }
        if (command == "RENAME")
        {
            string fileName1 = readLine();
            string fileName2 = readLine();
            rename(fileName1, fileName2);
        }
        if (command == "FILES")
        {
            files();
        }
        if (command == "FREESPACE")
        {
            cout << freeSpace() << endl;
        }
        if (command == "PACK")
        {
            pack();
        }
    }
}
