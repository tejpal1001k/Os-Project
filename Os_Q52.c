#include <stdio.h>
#include <conio.h>
struct pro{
    int id,brustTime,arrivalTime,q,remainingTime;
};

void main(){
	int n;
    printf("Enter no of Process : "); scanf("%d",&n);

    for(int i=0;i<n;i++){
        printf("Enter Arrival Time for Process %d : ",i+1); scanf("%d",&Process[i].arrivalTime);        
        printf("Enter Brust Time for Process %d   : ",i+1); scanf("%d",&Process[i].brustTime);
        printf("Enter Queue(1/2) for Process %d   : ",i+1); scanf("%d",&Process[i].q);
        Process[i].id = (i+1);
        Process[i].remainingTime = Process[i].brustTime;
    }
}
