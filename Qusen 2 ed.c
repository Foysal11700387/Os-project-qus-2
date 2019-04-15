#include<stdio.h> 
#include<conio.h>

void rr(int no,int remt[20],int Cur_t,int arT[20], int bsT[20]);

main() 
{
	int Proc_no,j,no,CurT,RemProc,indicator,time_quan,wait,tut,arT[20],bsT[20],remt[20],x=1;
	indicator = 0;
	wait = 0;
	tut = 0;
	printf("ENTER THE NUMBER OF PROCESSES\n "); 
	scanf("%d",&no);
	RemProc = no;
	
	printf("\nEnter the arrival time and burst time of the processes\n");
	for(Proc_no = 0;Proc_no < no;Proc_no++) 
	{
		printf("\nPROCESSES P%d\n",Proc_no+1);
		printf("Arrival Time = "); 
		scanf("%d",&arT[Proc_no]);
		printf("Burst Time = "); 
		scanf("%d",&bsT[Proc_no]); 
		remt[Proc_no]=bsT[Proc_no]; 
	} 
	printf("The details of time quantum are as follows:\n");
	printf("The time quantum for first round is 3.\n"); 
	time_quan=3;
	CurT=0;
	for(Proc_no=0;RemProc!=0;) 
	{
		if(remt[Proc_no]<=time_quan && remt[Proc_no]>0)
		{ 
			CurT+=remt[Proc_no]; 
			remt[Proc_no]=0; 
			indicator=1; 
		} 
		else if(remt[Proc_no]>0)
		{ 
			remt[Proc_no]-=time_quan; 
			CurT+=time_quan; 
		} 
		if(remt[Proc_no]==0 && indicator==1)			
		{ printf("%d",Proc_no);
			RemProc--;				
			printf("P %d",Proc_no+1); 
			printf("\t\t\t%d",CurT-arT[Proc_no]);
			printf("\t\t\t%d\n",CurT-bsT[Proc_no]-arT[Proc_no]);
			wait+=CurT-arT[Proc_no]-bsT[Proc_no]; 
			tut+=CurT-arT[Proc_no]; 
			indicator=0; 
                       
		} 
		if(Proc_no==no-1){
			x++;
			if(x==2){
				Proc_no=0;
				time_quan=6;
				
				printf("The time quantum for second round is 6. \n");
			}
			else{
				break;
			}
		}
		else if(CurT >= arT[Proc_no+1]){
			Proc_no++;
		}
		else{
			Proc_no=0;
		}
	}
	
	rr(no,remt,CurT,arT,bsT);
	
	return 0;
}


void rr(int no,int remt[20],int Cur_t,int arT[20], int bsT[20]){
	
	float avg_wait,avg_tut;
    int k,j,n=no,temp,btime[30],Proc_no[30],w_time[30],tut_t[30],total=0,loc;
    
    printf("Third round with least Burst time.\n");
    
    for(k=0;k<n;k++)
    {
        btime[k]=remt[k];
        w_time[k]=Cur_t-arT[k]-btime[k];
		Proc_no[k]=k+1;
    }
	
    for(k=0;k<n;k++)
    {
        loc=k;
        for(j=k+1;j<n;j++)
        {
            if(btime[j]<btime[loc]){
            	loc=j;
            }
        }
        temp=btime[k];
        btime[k]=btime[loc];
        btime[loc]=temp;
        temp=Proc_no[k];
        Proc_no[k]=Proc_no[loc];
        Proc_no[loc]=temp;
    }
	
    for(k=1;k<n;k++)
    {
        for(j=0;j<k;j++){
        	w_time[k]+=btime[j];
        }
        total+=w_time[k];
    }
 
    avg_wait=(float)total/n;
    total=0;
    printf("\nProcess\t\tBurst time\t\twaiting time\t\tTurnaround Time");
    for(k=0;k<n;k++)
    {
        tut_t[k]=btime[k]+w_time[k];
        total=total + tut_t[k];
        printf("\nP%d\t\t\t%d\t\t\t%d\t\t\t%d",Proc_no[k],btime[k],w_time[k],tut_t[k]);
    }
    avg_tut=(float)total/n;
    printf("\n\nAverage waiting time = %f",avg_wait);
    printf("\n Average turnaround time = %f\n",avg_tut);
	
}
