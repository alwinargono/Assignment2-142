#ifndef SCHEDULING_H
#define SCHEDULING_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


using namespace std;

struct process{
    int id;
    int arrival;
    int duration;
    int startTime;
    int endTime;
    int tempDur;
    int remaining;
    bool running;
    bool done;

    process(): startTime(-1),endTime(-1),done(0),running(0)
    {}
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
        newProc[i].remaining = arr[i].duration;
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

int minIndex(int arr[],int count)
{
    int temp;
    int j =0;

    for(int i = 0;i<count;i++)
    {
        j++;
        if(arr[i] > arr[j])
        {
            temp = j;
        }
    }
    return temp;
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

void sortArvlnDurLtoH(process arr[], int n)
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
            else if(arr[j].arrival == arr[j+1].arrival && arr[j].duration > arr[j+1].duration)
            {
                swap(&arr[j], &arr[j+1]);
            }
        }
    }
    return;
}

void sortArvlnDurHtoL(process arr[], int n)
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
            else if(arr[j].arrival == arr[j+1].arrival && arr[j].duration > arr[j+1].duration)
            {
                swap(&arr[j], &arr[j+1]);
            }
        }
    }
    return;
}

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
    return num;
}

void BJF(process proc[], int count)
{
    int time = 0;
    int jobDone = 0;
    int sameArvl;

    sortArvlnDurHtoL(proc, count);
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

    sortArvlnDurLtoH(proc, count);
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
                    if(proc[counter].startTime < 0)
                    {
                        proc[counter].startTime = time;
                        if(proc[0].arrival == 0)
                        {
                            proc[0].startTime = 0;
                        }
                    }
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

void STCF(process proc[], int count)
{
    int processDone = 0;
    int time = 0;
    int incoming; 
    int finish;

    sortArvlnDurLtoH(proc,count);

    for(time = 0;processDone != count;time++)
    {
        incoming = -1;
        int temp = INT_MAX;
        for(int i = 0; i < count; i++)
        {
            if(proc[i].arrival <= time && proc[i].duration < temp && proc[i].duration > 0)
            {
                cout << "swap "<< endl;
                incoming = i;
                temp = proc[i].duration;
            }
        }
        if(proc[incoming].startTime == -1)
        {
            proc[incoming].startTime = time;
        }
        proc[incoming].duration--;

        if(proc[incoming].duration == 0)
        {
            processDone++;
            finish = time + 1;
            proc[incoming].endTime = finish;
        }
    }
    cout << "PRINT PROCESSES\n[";
    printStruct(proc, 0, count);
    cout << "PRINT PROCESSES INFO\n";
    printStructInfo(proc, 0, count);

}

#endif
