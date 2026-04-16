#include <stdio.h>
#include <string.h>

int main() {
    int n,i,j,time=0;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    int bt[n],at[n],ct[n],tat[n],wt[n];
    char pname[n][10],temp[10];

    for(i=0;i<n;i++){
        printf("\nProcess %d name: ",i+1);
        scanf("%s",pname[i]);
        printf("Arrival Time: "); scanf("%d",&at[i]);
        printf("Burst Time: "); scanf("%d",&bt[i]);
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
        if(time < at[i]){
            printf(" Idle |");
            time = at[i];
        }
        printf(" %s |",pname[i]);
        time += bt[i];
        ct[i] = time;
    }

    float totalWT=0,totalTAT=0;

    printf("\n\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for(i=0;i<n;i++){
        tat[i]=ct[i]-at[i];
        wt[i]=tat[i]-bt[i];

        totalWT+=wt[i];
        totalTAT+=tat[i];

        printf("%s\t%d\t%d\t%d\t%d\t%d\n",
        pname[i],at[i],bt[i],ct[i],tat[i],wt[i]);
    }

    printf("\nAvg WT = %.2f",totalWT/n);
    printf("\nAvg TAT = %.2f",totalTAT/n);

    float throughput = (float)n / (ct[n-1] - at[0]);
    printf("\nThroughput = %.2f\n",throughput);

    return 0;
}
