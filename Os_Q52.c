#include <stdio.h>
#include <conio.h>
struct pro{
    int id,brustTime,arrivalTime,q,remainingTime;
};

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


void main(){
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
    for(i=0;i<n;i++)
        printf("Process %d  %d %d %d\n",Process[i].id,Process[i].arrivalTime,Process[i].brustTime,Process[i].q);
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
            	printf("\nProcess %d ended\n at time %d",temp.id,timer);    
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
            	printf("\nProcess %d ended\n at time %d",temp.id,timer);
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
}
