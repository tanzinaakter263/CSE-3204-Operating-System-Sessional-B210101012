#include <stdio.h>
#include <string.h>

void fcfs();
void sjf();
void roundRobin();

int main() {
    int choice;

    do {
        printf("\nCPU Scheduling Algorithms\n");
        printf("1. FCFS\n");
        printf("2. SJF (Non Preemptive)\n");
        printf("3. Round Robin\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: fcfs(); break;
            case 2: sjf(); break;
            case 3: roundRobin(); break;
            case 4: printf("Exiting program...\n"); break;
            default: printf("Invalid choice. Try again.\n");
        }
    } while(choice != 4);

    return 0;
}

// ====================== FCFS ======================
void fcfs() {
    int n,i,j,time=0;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    int bt[n],at[n],ct[n],tat[n],wt[n];
    char pname[n][10],temp[10];

    for(i=0;i<n;i++){
        printf("\nProcess %d name: ",i+1);
        scanf("%s",pname[i]);
        printf("Burst time: ");
        scanf("%d",&bt[i]);
        printf("Arrival time: ");
        scanf("%d",&at[i]);
    }

    for(i=0;i<n-1;i++){
        for(j=i+1;j<n;j++){
            if(at[i]>at[j]){
                int t=at[i]; at[i]=at[j]; at[j]=t;
                t=bt[i]; bt[i]=bt[j]; bt[j]=t;
                strcpy(temp,pname[i]);
                strcpy(pname[i],pname[j]);
                strcpy(pname[j],temp);
            }
        }
    }

    printf("\nGantt Chart:\n|");

    for(i=0;i<n;i++){
        if(time<at[i]){
            printf(" Idle |");
            time=at[i];
        }
        printf(" %s |",pname[i]);
        time+=bt[i];
        ct[i]=time;
    }

    float totalWT=0, totalTAT=0;

    printf("\n\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for(i=0;i<n;i++){
        tat[i]=ct[i]-at[i];
        wt[i]=tat[i]-bt[i];
        totalWT+=wt[i];
        totalTAT+=tat[i];

        printf("%s\t%d\t%d\t%d\t%d\t%d\n",
        pname[i],at[i],bt[i],ct[i],tat[i],wt[i]);
    }
    printf("\nAverage Waiting Time = %.2f\n",totalWT/n);
    printf("Average Turnaround Time = %.2f\n",totalTAT/n);

    float throughput = (float)n / (ct[n-1] - at[0]);
    printf("Throughput = %.2f processes/unit time\n", throughput);
}

// ====================== SJF ======================
void sjf(){
    int n,i,time=0,completed=0;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    int bt[n],at[n],ct[n],tat[n],wt[n],done[n];
    char pname[n][10];

    for(i=0;i<n;i++){
        printf("\nProcess %d name: ",i+1);
        scanf("%s",pname[i]);
        printf("Burst time: ");
        scanf("%d",&bt[i]);
        printf("Arrival time: ");
        scanf("%d",&at[i]);
        done[i]=0;
    }

    printf("\nGantt Chart:\n|");

    while(completed<n){
        int idx=-1,min=999;

        for(i=0;i<n;i++){
            if(at[i]<=time && done[i]==0){
                if(bt[i]<min){
                    min=bt[i];
                    idx=i;
                }
            }
        }

        if(idx==-1){
            printf(" Idle |");
            time++;
        }
        else{
            printf(" %s |",pname[idx]);
            time+=bt[idx];
            ct[idx]=time;
            done[idx]=1;
            completed++;
        }
    }

    float totalWT=0, totalTAT=0;

    printf("\n\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for(i=0;i<n;i++){
        tat[i]=ct[i]-at[i];
        wt[i]=tat[i]-bt[i];
        totalWT+=wt[i];
        totalTAT+=tat[i];

        printf("%s\t%d\t%d\t%d\t%d\t%d\n",
        pname[i],at[i],bt[i],ct[i],tat[i],wt[i]);
    }
    printf("\nAverage Waiting Time = %.2f\n",totalWT/n);
    printf("Average Turnaround Time = %.2f\n",totalTAT/n);

    float throughput = (float)n / (ct[n-1] - at[0]);
    printf("Throughput = %.2f processes/unit time\n", throughput);
}

// ====================== ROUND ROBIN ======================
void roundRobin(){
    int n,tq,i,time=0,remain;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    char pname[n][10];
    int bt[n],at[n],rt[n],ct[n],tat[n],wt[n];

    for(i=0;i<n;i++){
        printf("\nProcess %d name: ",i+1);
        scanf("%s",pname[i]);
        printf("Burst time: ");
        scanf("%d",&bt[i]);
        printf("Arrival time: ");
        scanf("%d",&at[i]);
        rt[i]=bt[i];
    }

    printf("Enter Time Quantum: ");
    scanf("%d",&tq);

    remain=n;

    printf("\nGantt Chart:\n|");

    while(remain>0){
        int executed=0;

        for(i=0;i<n;i++){
            if(rt[i]>0 && at[i]<=time){
                executed=1;

                if(rt[i]>tq){
                    printf(" %s |",pname[i]);
                    time+=tq;
                    rt[i]-=tq;
                }else{
                    printf(" %s |",pname[i]);
                    time+=rt[i];
                    ct[i]=time;
                    rt[i]=0;
                    remain--;
                }
            }
        }

        if(!executed){
            printf(" Idle |");
            time++;
        }
    }

    float totalWT=0, totalTAT=0;

    printf("\n\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for(i=0;i<n;i++){
        tat[i]=ct[i]-at[i];
        wt[i]=tat[i]-bt[i];
        totalWT+=wt[i];
        totalTAT+=tat[i];

        printf("%s\t%d\t%d\t%d\t%d\t%d\n",
        pname[i],at[i],bt[i],ct[i],tat[i],wt[i]);
    }
    printf("\nAverage Waiting Time = %.2f\n",totalWT/n);
    printf("Average Turnaround Time = %.2f\n",totalTAT/n);

    float throughput = (float)n / (ct[n-1] - at[0]);
    printf("Throughput = %.2f processes/unit time\n", throughput);
}
