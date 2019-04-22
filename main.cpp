//
//  main.cpp
//  as2
//
//  Created by michelle natasha on 4/16/19.
//  Copyright © 2019 michelle natasha. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct process{
    int id;
    int arrival;
    int duration;
    int startTime = NULL;
    int endTime = NULL;
    int tempDur;
    bool done = 0;
};

process* copyStruct(process arr[], int startIndex, int endIndex)
{
    process* newProc = new process[endIndex-startIndex];
    for(int i = startIndex; i<endIndex; i++)
    {
        newProc[i].id = arr[i].id;
        newProc[i].arrival = arr[i].arrival;
        newProc[i].duration = arr[i].duration;
        newProc[i].startTime = arr[i].startTime;
        newProc[i].endTime = arr[i].endTime;
    }
    return newProc;
}

void printStruct(process arr[], int startIndex, int endIndex)
{
    for(int i = startIndex; i<endIndex; i++)
    {
        cout << "process id : " << arr[i].id << endl;
        cout << "process arrival : " << arr[i].arrival << endl;
        cout << "process duration : " << arr[i].duration<< endl;
        cout << "process start time : " << arr[i].startTime << endl;
        cout << "process end time : " << arr[i].endTime << endl << endl;
    }
    return;
}

void printStructInfo(process arr[], int startIndex, int endIndex)
{
    for(int i = startIndex; i<endIndex; i++)
    {
        cout << "process id : " << arr[i].id << endl;
        cout << "start time : " << arr[i].startTime << endl;
        cout << "finish time : " << arr[i].endTime << endl;
        cout << "time elapsed : " << arr[i].endTime-arr[i].startTime << endl;
        cout << "response time : " << arr[i].startTime-arr[i].arrival << endl << endl;
    }
    return;
}

void swap(struct process *xp, struct process *yp)
{
    process temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// A function to implement bubble sort and modify the array
void SortArvlLtoH(process arr[], int n)
{
    int i, j;
    for (i = 0; i < n-1; i++)
    {
        // Last i elements are already in place
        for (j = 0; j < n-i-1; j++)
        {
            if (arr[j].arrival > arr[j+1].arrival)
            {
                swap(&arr[j], &arr[j+1]);
            }
        }
    }
    return;
}

/*void SortArvlHtoL(process arr[], int n)
 {
 int i, j;
 for (i = 0; i < n-1; i++)
 {
 // Last i elements are already in place
 for (j = 0; j < n-i-1; j++)
 {
 if (arr[j].arrival < arr[j+1].arrival)
 {
 swap(&arr[j], &arr[j+1]);
 }
 }
 }

 return;
 }*/

process* SortDurLtoH(process arr[], int jobDone, int n) //n= # waiting processes
{
    process* newArr = new process[n];
    int c = 0;
    for(int i = jobDone; i<jobDone+n; i++)
    {
        newArr[c].id = arr[i].id;
        newArr[c].arrival = arr[i].arrival;
        newArr[c].duration = arr[i].duration;
        newArr[c].startTime = arr[i].startTime;
        newArr[c].endTime = arr[i].endTime;
        c++;
    }
    int i, j;
    for (i = 0; i < n-1; i++)
    {
        // Last i elements are already in place
        for (j = 0; j < n-i-1; j++)
        {
            if (newArr[j].duration > newArr[j+1].duration)
            {
                swap(&newArr[j], &newArr[j+1]);
            }
        }
    }
    return newArr;
}

process* SortDurHtoL(process arr[], int jobDone, int n) //n= # waiting processes
{
    process* newArr = new process[n];
    int c = 0;
    for(int i = jobDone; i<jobDone+n; i++)
    {
        newArr[c].id = arr[i].id;
        newArr[c].arrival = arr[i].arrival;
        newArr[c].duration = arr[i].duration;
        newArr[c].startTime = arr[i].startTime;
        newArr[c].endTime = arr[i].endTime;
        c++;
    }
    //    cout << "in function\n";
    //    printStruct(newArr, 0, n);
    int i, j;
    for (i = 0; i < n-1; i++)
    {
        // Last i elements are already in place
        for (j = 0; j < n-i-1; j++)
        {
            if (newArr[j].duration < newArr[j+1].duration)
            {
                swap(&newArr[j], &newArr[j+1]);
            }
        }
    }
    //   cout << "sorted \n";
    //   printStruct(newArr, 0, n);
    return newArr;
}

int checkWaitingProc(process array[], int jobDone, int time, int count)
{
    int num = 0;
    for(int i = jobDone; i < count; i++)
    {
        if(array[i].arrival <= time)
        {
            num++;
        }
    }
    //cout << "num : " << num << endl;
    return num;
}

void BJF(process proc[], int count)
{
    int time = 0;
    int jobDone = 0;
    int sameArvl;

    SortArvlLtoH(proc, count);
    time += proc[jobDone].arrival;

    while(jobDone < count)
    {
        sameArvl = checkWaitingProc(proc, jobDone, time, count);
        cout << sameArvl<< endl;
        if(sameArvl == 1)
        {
            proc[jobDone].startTime = time;
            time+=proc[jobDone].duration;
            proc[jobDone].endTime = time;
            cout << proc[jobDone].id << "process is done\n";
            jobDone++;
        }
        else if(sameArvl == 0)
        {
            time = proc[jobDone].arrival;
            proc[jobDone].startTime = time;
            time+=proc[jobDone].duration;
            proc[jobDone].endTime = time;
            cout << proc[jobDone].id << "process is done\n";
            jobDone++;
        }
        else
        {
            process* temp = new process[sameArvl];
            temp = SortDurHtoL(proc, jobDone, sameArvl);
            //            cout << "TEMP\n";
            //            printStruct(temp, 0, sameArvl);
            int tempCount = 0;
            for(int i = jobDone; i<jobDone+sameArvl; i++)
            {
                proc[i].id = temp[tempCount].id;
                proc[i].arrival = temp[tempCount].arrival;
                proc[i].duration = temp[tempCount].duration;
                proc[i].startTime = temp[tempCount].startTime;
                proc[i].endTime = temp[tempCount].endTime;
                tempCount++;
            }
            proc[jobDone].startTime = time;
            time+=proc[jobDone].duration;
            proc[jobDone].endTime = time;
            cout << proc[jobDone].id << "process is done\n";
            //printStruct(proc, 0, count);
            jobDone++;
        }
    }
    cout << "PRINT PROCESSES\n";
    printStruct(proc, 0, count);
    cout << "PRINT PROCESSES INFO\n";
    printStructInfo(proc, 0, count);
    return;
}

void SJF(process proc[], int count)
{
    int time = 0;
    int jobDone = 0;
    int sameArvl;

    SortArvlLtoH(proc, count);
    time += proc[jobDone].arrival;

    while(jobDone < count)
    {
        sameArvl = checkWaitingProc(proc, jobDone, time, count);
        cout << sameArvl<< endl;
        if(sameArvl == 1)
        {
            proc[jobDone].startTime = time;
            time+=proc[jobDone].duration;
            proc[jobDone].endTime = time;
            cout << proc[jobDone].id << " process is done\n";
            jobDone++;
        }
        else if(sameArvl == 0)
        {
            time = proc[jobDone].arrival;
            proc[jobDone].startTime = time;
            time+=proc[jobDone].duration;
            proc[jobDone].endTime = time;
            cout << proc[jobDone].id << " process is done\n";
            jobDone++;
        }
        else
        {
            process* temp = new process[sameArvl];
            temp = SortDurLtoH(proc, jobDone, sameArvl);
            //            cout << "TEMP\n";
            //            printStruct(temp, 0, sameArvl);
            int tempCount = 0;
            for(int i = jobDone; i<jobDone+sameArvl; i++)
            {
                proc[i].id = temp[tempCount].id;
                proc[i].arrival = temp[tempCount].arrival;
                proc[i].duration = temp[tempCount].duration;
                proc[i].startTime = temp[tempCount].startTime;
                proc[i].endTime = temp[tempCount].endTime;
                tempCount++;
            }
            proc[jobDone].startTime = time;
            time+=proc[jobDone].duration;
            proc[jobDone].endTime = time;
            cout << proc[jobDone].id << " process is done\n";
            //printStruct(proc, 0, count);
            jobDone++;
        }
    }
    cout << "PRINT PROCESSES\n";
    printStruct(proc, 0, count);
    cout << "PRINT PROCESSES INFO\n";
    printStructInfo(proc, 0, count);
    return;
}

void FIFO(process proc[], int count)
{
    int time = 0;
    int jobDone = 0;
    int sameArvl;

    SortArvlLtoH(proc, count);
    time += proc[jobDone].arrival;

    while(jobDone < count)
    {
        sameArvl = checkWaitingProc(proc, jobDone, time, count);
        cout << sameArvl<< endl;
        if(sameArvl == 0)
        {
            time = proc[jobDone].arrival;
            proc[jobDone].startTime = time;
            time+=proc[jobDone].duration;
            proc[jobDone].endTime = time;
            cout << proc[jobDone].id << "process is done\n";
            jobDone++;
        }
        else
        {
            proc[jobDone].startTime = time;
            time+=proc[jobDone].duration;
            proc[jobDone].endTime = time;
            cout << proc[jobDone].id << "process is done\n";
            jobDone++;
        }
    }
    cout << "PRINT PROCESSES\n";
    printStruct(proc, 0, count);
    cout << "PRINT PROCESSES INFO\n";
    printStructInfo(proc, 0, count);
    return;
}

void RR(process proc[], int count)
{
    int time = 0;
    int jobDone = 0;
    int sameArvl;
    int counter;

    SortArvlLtoH(proc, count);
    time = proc[0].arrival;

    while(jobDone < count)
    {
        sameArvl = checkWaitingProc(proc, 0, time, count);
        counter = 0;

        if(sameArvl == 0) // no job waiting
        {
            time++;
        }
        else
        {
            while(counter < sameArvl)
            {
                if(!proc[counter].done)
                {
                    if(proc[counter].startTime == NULL)
                    {
                        proc[counter].startTime = time;
                        if(proc[0].arrival == 0)
                        {
                        	proc[0].startTime = 0;
                        }
                    }

//                  cout << "prog " << counter << " is running\n";
                    time++;
                    proc[counter].tempDur--;
                    if(proc[counter].tempDur == 0)
                    {
                        proc[counter].endTime = time;
                        cout << proc[counter].id << "process is done\n";
                        proc[counter].done = 1;
                        jobDone++;
                    }
                }
                counter++;
            }
        }
    }
    cout << "PRINT PROCESSES\n";
    printStruct(proc, 0, count);
    cout << "PRINT PROCESSES INFO\n";
    printStructInfo(proc, 0, count);
    return;
}

int main() {
    int jobCount = 0;
    process procArray[100];
    string buffer;

    ifstream fin("/Users/michellenatasha/eclipse-workspace/assign2_142/job.dat");
    if (!fin.good()){
        cout << "File not found\n";
    }
    else{
        cout <<"File is found\n";
        while (!fin.eof()&&jobCount<100){
            getline(fin, buffer);
            cout << buffer << endl;
            stringstream ss(buffer);
            ss>>procArray[jobCount].id>>procArray[jobCount].arrival>>procArray[jobCount].duration;
            jobCount++;
        }
        fin.close();
        cout << "Job Count : " << jobCount << endl;

        for(int i = 0; i<jobCount; i++)
        {
            cout << procArray[i].id << " " << procArray[i].arrival << " " <<
            procArray[i].duration << endl;
        }
    }

    char in;
    int choice;
    while(1)
    {
        cout << "Enter n to quit and y to continue\n";
        cin >> in;

        process* copyArr = new process[jobCount];
        if(in == 'y')
        {
        	cout << "1 for FIFO\n";
        	cout << "2 for SJF\n";
        	cout << "3 for BJF\n";
        	cout << "4 for STCF\n";
        	cout << "5 for RR\n";
        	cout << "Enter choice : ";
        	cin >>choice;
            copyArr = copyStruct(procArray, 0, jobCount);
            if(choice == 3)
            {
                cout << "Running BJF\n";
                BJF(copyArr, jobCount);
                cout << "END\n";
            }
            else if(choice == 1)
            {
                cout << "Running FIFO\n";
                FIFO(copyArr, jobCount);
                cout << "END\n";
            }
            else if(choice == 5)
            {
                //copy temporary duration
                for(int i = 0; i < jobCount; i++)
                {
                    copyArr[i].tempDur = copyArr[i].duration;
                }
                cout << "Running RR\n";
                RR(copyArr, jobCount);
                cout << "END\n";
            }
            else if(choice == 2)
            {
                cout << "Running SJF\n";
                SJF(copyArr, jobCount);
                cout << "END\n";
            }
            else if(choice == 4)
            {
            	cout << "Running STCF\n";
//            	STCF(copyArr, jobCount);
                cout << "END\n";
            }
            else
            	cout << "Invalid choice\n";
        }
        else if(in == 'n')
            return 0;
        else
        	cout << "Invalid choice\n";
    }

}
