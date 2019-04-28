#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Scheduling.h"

using namespace std;

void print_proccesslist(process p[], int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << p[0].id << p[0].arrival << p[0].duration << p[0].remaining << p[0].running << p[0].done << endl;
    }
}
int main()
{
    int jobCount = 0;
    process procArray[100];
    string buffer;

    ifstream fin("job.dat");
    if (!fin.good())
    {
        cout << "File not found\n";
    }
    else
    {
        cout << "File is found\n";
        while (!fin.eof() && jobCount < 100)
        {
            getline(fin, buffer);
            cout << buffer << endl;
            stringstream ss(buffer);
            ss >> procArray[jobCount].id >> procArray[jobCount].arrival >> procArray[jobCount].duration;
            jobCount++;
        }
        fin.close();
        cout << "Job Count : " << jobCount << endl;

        for (int i = 0; i < jobCount; i++)
        {
            cout << procArray[i].id << " " << procArray[i].arrival << " " << procArray[i].duration << endl;
        }
    }

    char in;
    int choice;

    do
    {
        process *copyArr = new process[jobCount];
        cout << "*****************\n";
        cout << "1 for FIFO\n";
        cout << "2 for SJF\n";
        cout << "3 for BJF\n";
        cout << "4 for STCF\n";
        cout << "5 for RR\n";
         cout << "0 to exit\n";
        cout << "Enter choice : ";
        cin >> choice;
        cout << "*****************\n";
        copyArr = copyStruct(procArray, 0, jobCount);
        if (choice == 3)
        {
            cout << "Running BJF\n";
            BJF(copyArr, jobCount);
            cout << "END\n";
        }
        else if (choice == 1)
        {
            cout << "Running FIFO\n";
            FIFO(copyArr, jobCount);
            cout << "END\n";
        }
        else if (choice == 5)
        {
            //copy temporary duration
            for (int i = 0; i < jobCount; i++)
            {
                copyArr[i].tempDur = copyArr[i].duration;
            }
            cout << "Running RR\n";
            RR(copyArr, jobCount);
            cout << "END\n";
        }
        else if (choice == 2)
        {
            cout << "Running SJF\n";
            SJF(copyArr, jobCount);
            cout << "END\n";
        }
        else if (choice == 4)
        {
            cout << "Running STCF\n";
            STCF(copyArr, jobCount);
            cout << "END\n";
        }
    }
    while((choice != 0));
    return 0;
}
