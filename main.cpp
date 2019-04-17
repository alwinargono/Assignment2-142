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

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// A function to implement bubble sort and get the sorted array's index
int* bubbleSort(int arr[], int n)
{
   int i, j;
   int* ind = new int[n];
   for(int i = 0; i<n; i++)
   {
	   ind[i]=i;
   }
   for (i = 0; i < n-1; i++)
   {
       // Last i elements are already in place
       for (j = 0; j < n-i-1; j++)
       {
           if (arr[j] > arr[j+1])
           {
        	   swap(&arr[j], &arr[j+1]);
        	   swap(&ind[j], &ind[j+1]);
           }
       }
   }

    return ind;
}

int main() {
    int jobCount = 0;
    int Ori_Job_ID[100];
    int Ori_Arrival_Time[100];
    int Ori_Duration[100];
    string buffer;

    int jobID, arrTime, dur;
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
            ss>>jobID>>arrTime>>dur;
            Ori_Job_ID[jobCount]=jobID;
            Ori_Arrival_Time[jobCount]=arrTime;
            Ori_Duration[jobCount]=dur;
            jobCount++;
        }
        fin.close();
        cout << "Job Count : " << jobCount << endl;

        for(int i = 0; i<jobCount; i++)
        {
        	cout << Ori_Job_ID[i] << " " << Ori_Arrival_Time[i] << " " <<
        			Ori_Duration[i] << endl;
        }
    }

    int* jobIndex = bubbleSort(Ori_Duration, jobCount);
    for(int i =0; i<jobCount;i++){
    	cout<<"dur index : " << jobIndex[i] << endl;
    }

    return 0;
}
