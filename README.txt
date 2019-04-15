Student Name:  Tejpal Choudhary
Student ID:    11701208
Email Address: choudharytejpal148@gmail.com
GitHub Link:   https://github.com/dhruva2025/Os-Project



Q52.Design a scheduler with multilevel queue having two queues which will schedule the processes
 on the basis of pre-emptive shortest remaining processing time first algorithm (SROT) followed 
by a scheduling in which each process will get 2 units of time to execute. Also note that queue 
1 has higher priority than queue2. Consider the following set of processes (for reference) with 
the arrival times and the CPU burst times in milliseconds.
Pro AT BT
P1 0 5
P2 1 3
P3 2 3
P4 4 1
Calculate the average turnaround time and average waiting time for each process. The input for number
of processes and their arrival time, burst time should be given by the user.


#include <stdio.h>
#include <conio.h>
struct pro{
    int id,brustTime,arrivalTime,q,remainingTime;
};

int turnAround[100];
int waitingTime[100];
struct pro Process[100];
struct pro Queue1[100],Queue2[100];


void sortbyArrivalTime(int n){
	int i,j;
    for(i=0;i<n-1;i++){
        for(j=0;j<n-i-1;j++){
            if(Process[j].arrivalTime > Process[j+1].arrivalTime){
                struct pro temp = Process[j];
                Process[j] = Process[j+1];
                Process[j+1]= temp;
            }
        }
    }
}

void sortQueue1(int n){
	int i,j;
    for(i=0;i<n-1;i++){
        for(j=0;j<n-i-1;j++){
            if(Queue1[j].remainingTime < Queue1[j+1].remainingTime){
                struct pro temp = Queue1[j];
                Queue1[j] = Queue1[j+1];
                Queue1[j+1]= temp;
            }
        }
    }
}

void sortQueue2(int n){
	int i,j;
    for(i=0;i<n-1;i++){
        for(j=0;j<n-i-1;j++){
            if(Queue2[j].remainingTime < Queue2[j+1].remainingTime){
                struct pro temp = Queue2[j];
                Queue2[j] = Queue2[j+1];
                Queue2[j+1]= temp;
            }
        }
    }
}

void main() {
    int n;
    printf("Enter no of Process : "); scanf("%d",&n);
	int i;
    for(i=0;i<n;i++){
        printf("Enter Arrival Time for Process %d : ",i+1); scanf("%d",&Process[i].arrivalTime);        
        printf("Enter Brust Time for Process %d   : ",i+1); scanf("%d",&Process[i].brustTime);
        printf("Enter Queue(1/2) for Process %d   : ",i+1); scanf("%d",&Process[i].q);
        Process[i].id = (i+1);
        Process[i].remainingTime = Process[i].brustTime;
    }

    sortbyArrivalTime(n);

    printf("\n");
    // for(int i=0;i<n;i++)
    //     printf("Process %d  %d %d %d\n",Process[i].id,Process[i].arrivalTime,Process[i].brustTime,Process[i].q);
   
    int len1,len2;    
    len1 = len2 = 0; 
    int timer = 0;
    int pos = 0;
    int timeQuantum = 2;
    struct pro temp;

    while(pos<n || len1!=0 || len2!=0)
    {
        while(pos<n && Process[pos].arrivalTime <= timer){
            if(Process[pos].q==1)
                Queue1[len1++] = Process[pos++];
            else
                Queue2[len2++] = Process[pos++];
        }

        if(len1>0){
            sortQueue1(len1);           
            temp = Queue1[--len1];
            // printf("%d %d %d\n",timer,temp.id,temp.remainingTime);

            if(temp.remainingTime<=timeQuantum){
                timer += temp.remainingTime;
                temp.remainingTime = 0;
                turnAround[temp.id] = timer-temp.arrivalTime;
                waitingTime[temp.id]= turnAround[temp.id] - temp.brustTime;
            }
            else
            {
                timer +=2;
                temp.remainingTime -=2;
                Queue1[len1++]=temp;
            }
        }
        else
        if(len2>0)
        {
            sortQueue2(len2);
            temp = Queue2[--len2];
            // printf("%d %d %d %d\n",timer,temp.id,temp.remainingTime);
            if(temp.remainingTime<=timeQuantum){
                timer += temp.remainingTime;
                temp.remainingTime = 0;
                turnAround[temp.id] = timer-temp.arrivalTime;
                waitingTime[temp.id]= turnAround[temp.id] - temp.brustTime;
            }
            else
            {
                timer += timeQuantum;
                temp.remainingTime -=2;
                Queue2[len2++] = temp;
            }
        }
        else
            timer++;
    }
    printf("\n");
    int avgwT=0,avgTT=0;
        printf("PROCESS ID   TurnAround Time    Waiting Time\n");
    for(i=1;i<=n;i++){
        printf("Process %d : %10d %15d\n",i,turnAround[i],waitingTime[i]);
        avgwT += waitingTime[i];
        avgTT += turnAround[i];
    }
    printf("Average Waiting Time %f",(avgwT/(1.0*n)));
    printf("Average TurnAround Time %f",(avgTT/(1.0*n)));

}



Ques 25. Write a program for multilevel queue scheduling algorithm. There must be three queues generated.
 There must be specific range of priority associated with every queue. Now prompt the user to enter number
 of processes along with their priority and burst time. Each process must occupy the respective queue with 
specific priority range according to its priority. Apply Round Robin algorithm with quantum time 4 on queue
 with highest priority range. Apply priority scheduling algorithm on the queue with medium range of priority
 and First come first serve algorithm on the queue with lowest range of priority. Each and every queue should
 get a quantum time of 10 seconds. CPU will keep on shifting between queues after every 10 seconds.



#include<stdio.h> 
 
int main() 
{ 
    int i, limit, total = 0, x, counter = 0, time_quantum,j;   
	int wait_time = 0, turnaround_time = 0,pos,z,p[10],prio[10], a_time[10], b_time[10], temp[10],b; 
    float average_wait_time, average_turnaround_time;
      
	printf("\nEnter Total Number of Processes:"); 
    scanf("%d", &limit); 
      
	x = limit; 
    for(i = 0; i < limit; i++) 
    {
	    p[i]=i+1;
	    prio[i]=0;
        printf("\nEnter total Details of Process[%d]\n", i + 1);
        printf("Arrival Time  :\t"); scanf("%d", &a_time[i]);
        printf("Burst Time    :\t");   scanf("%d", &b_time[i]); 
        temp[i] = b_time[i];
    }
	   
    printf("\nEnter the Time Quantum:");  scanf("%d", &time_quantum); 
     
	printf("\nProcess ID\tBurst Time\t Turnaround Time \tWaiting Time \tPriority\n"); 
    for(total = 0, i = 0; x != 0;) 
    { 

		for(z=0;z<limit;z++)
		{
			int temp1;
			pos=z;
			for(j=z+1;j<limit;j++)
			{
			    if(prio[j]<prio[pos])
				pos=j;
			}
		 
			temp1=prio[z];
	
			prio[z]=prio[pos];
	
			prio[pos]=temp1;
		 
			temp1=b_time[z];
			b_time[z]=b_time[pos];
			b_time[pos]=temp1;
		 	temp1=a_time[z];
			a_time[z]=a_time[pos];
			a_time[pos]=temp1;

			temp1=p[z];
			p[z]=p[pos];
			p[pos]=temp1;

			temp1=temp[z];
			temp[z]=temp[pos];
			temp[pos]=temp1;
		}
            
		if(temp[i] <= time_quantum && temp[i] > 0) 
        { 
            total = total + temp[i]; 
            temp[i] = 0; 
            counter = 1; 
        } 
        else if(temp[i] > 0) 
        { 
            temp[i] = temp[i] - time_quantum; 
        	total = total + time_quantum; 
        }
        
        for(b=0;b<limit;b++)
		{
			if(b==i)
			prio[b]+=1;
			else
			prio[b]+=2;
		}
		if(temp[i] == 0 && counter == 1) 
        { 
            x--; 
            printf("\nProcess[%d]\t\t%d\t\t %d\t\t\t %d\t\t%d", p[i], b_time[i], total - a_time[i], total - a_time[i] - b_time[i],prio[i]);
            wait_time = wait_time + total - a_time[i] - b_time[i]; 
        	turnaround_time = turnaround_time + total - a_time[i]; 
            counter = 0; 
        } 
        if(i == limit - 1) 
        {
        	i = 0; 
		}
        else if(a_time[i + 1] <= total) 
        {
        	i++;            
		}
        else 
        {
        	i = 0;
		}
	}
}

