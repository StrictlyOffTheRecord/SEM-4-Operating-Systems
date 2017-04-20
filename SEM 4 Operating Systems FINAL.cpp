#include<iostream>
#include<stdio.h>
#include<process.h>
#include<cmath>

using namespace std;

int arr[100], arr_temp[100], arr_working[100], number_of_processes, max_cylinders;
int total_head_movement=0;


void quicksort(int arr[], int low, int high)
{
	int i,j,pivot,temp;
	
	if(low<high)
	{
		pivot=low;
		j=high;
		while(i<j)
		{
			while(arr[i]<=arr[pivot] && i<high)
			{
				i++;
			}
			while(arr[j]>arr[pivot])
			{
				j--;	
			}
			if(i<j)
			{
				temp=arr[i];
				arr[i]=arr[j];
				arr[j]=temp; 
			}
		}
		
		temp=arr[pivot];
		
		arr[pivot]=arr[j];
		
		arr[j]=temp;
		
		quicksort(arr,low,j-1);
		quicksort(arr,j+1,high);
	}
}



void initialize_arr()
{

	for(int i=0;i<100;i++)
	{
		arr[i]=0;
	}
}


void initialize_arr_working()
{

	for(int i=0;i<100;i++)
	{
		arr_working[i]=0;
	}
}

void input()
{
	printf("\n\nEnter the number of processes(not more than 100):\t");
	scanf("%d",&number_of_processes);

	printf("\n\nEnter the maximum number of cylinders in the system:\t");
	scanf("%d",&max_cylinders);

	for(int i=0;i<number_of_processes;i++)
	{
		printf("\n\nEnter the cylinder number for process number %d:\t",i+1);
		scanf("%d",&arr[i]);
		
		arr_temp[i]=arr[i];
	}
}






void display_arr_working()  /*works for fcfs, sstf, look, c-look*/
{
	total_head_movement=0;
	cout<<"**------ Arr WORKING is \n\n";

	for(int i=0;i<number_of_processes;i++)
	{
		printf("\t%d",arr_working[i]);

		if(i>0)

            total_head_movement=total_head_movement+abs(arr_working[i]-arr_working[i-1]);
	}

	cout<<endl;

	cout<<"\n\t Total Head Movement = "<<total_head_movement;
}


void display_arr()  /*works for fcfs, sstf, look, c-look*/
{
	cout<<"**------ ARR is \n\n";


	for(int i=0;i<number_of_processes;i++)
	{
		printf("\t%d",arr[i]);
	}

	cout<<endl;
}

void display_arr_working_cscan()
{
	total_head_movement=0;
	cout<<"**------ Arr WORKING is \n\n";

	for(int i=0;i<number_of_processes+2;i++)
	{
		printf("\t%d",arr_working[i]);
	}
	
	cout<<endl;
}

void display_arr_working_scan()
{
	total_head_movement=0;
	cout<<"**------ Arr WORKING is \n\n";

	for(int i=0;i<number_of_processes+1;i++)
	{
		printf("\t%d",arr_working[i]);

		if(i>0)

            total_head_movement=total_head_movement+abs(arr_working[i]-arr_working[i-1]);
	}

	cout<<endl;

	cout<<"\n\t Total Head Movement = "<<total_head_movement;
	
	
	for(int i=0;i<number_of_processes;i++)
	{
		arr[i]=arr_temp[i];
	}
}








void fcfs()
{

    for(int i=0; i<number_of_processes; i++)
	{
		arr_working[i]=arr[i];
	}
        
    display_arr();
    display_arr_working();

}

void sstf()
{

	
	int curr,k=0, count=0,j;

	curr=arr[0];

	arr_working[k++]=curr;

	for(int i=0;i<number_of_processes;i++)
	{
		quicksort(arr,0,number_of_processes-1);

		cout<<"\n\n----------Iteration "<<count<<endl;

		display_arr();


		for(j=count;j<number_of_processes;j++)
		{
			if(arr[j]==curr)
			{
				break;
			}
		}

		cout<<"\n\n--** j is "<<j;



		if(arr[j-1]==-1 || arr[j-1]==0)
		{
			arr_working[k++]=arr[j+1];
			arr[j]=-1;
			curr=arr[j+1];
			cout<<"\n\n   j+1  Hit on "<<arr[j+1]<<endl;
			display_arr_working();
		}

		else if(arr[j+1]==0)
		{
				arr_working[k++]=arr[j-1];
				arr[j]=-1;
				curr=arr[j-1];
				cout<<"\n\n j-1  Hit on "<<arr[j-1]<<endl;
				display_arr_working();
		}
		
		else
		{
			if((arr[j]-arr[j-1])>(arr[j+1]-arr[j]))
			{
				arr_working[k++]=arr[j+1];
				arr[j]=-1;
				curr=arr[j+1];

				cout<<"\n\n  j+1  Hit on "<<arr[j+1]<<endl;

				display_arr_working();

			}

			else
			{
				arr_working[k++]=arr[j-1];
				arr[j]=-1;
				curr=arr[j-1];
				cout<<"\n\n j-1  Hit on "<<arr[j-1]<<endl;
				display_arr_working();
			}
		}


		count++;
	}
	
	
	for(int i=0;i<number_of_processes;i++)
	{
		arr[i]=arr_temp[i];
	}
   
}


void look()
{

	int curr,k=0, count=0,j;

	curr=arr[0];

	arr_working[k++]=curr;

	quicksort(arr,0,number_of_processes-1);

	for(j=count;j<number_of_processes;j++)
	{
		if(arr[j]==curr)
		{
			break;
		}
	}

	if(arr[j]-arr[j-1]>arr[j+1]-arr[j])
	{
		for(int i=j+1;i<number_of_processes;i++)
		{
			arr_working[k++]=arr[i];
		}

        for(int i=j-1;i>=0;i--)
		{
			arr_working[k++]=arr[i];
		}

	}

	else
	{

		for(int i=j-1;i>=0;i--)
		{
			arr_working[k++]=arr[i];
		}

		for(int i=j+1;i<number_of_processes;i++)
		{
			arr_working[k++]=arr[i];
		}

	}
	
	display_arr();
	display_arr_working();

	
	for(int i=0;i<number_of_processes;i++)
	{
		arr[i]=arr_temp[i];
	}


}



void c_look()
{

	int curr,k=0, count=0,j;

	curr=arr[0];

	arr_working[k++]=curr;

	quicksort(arr,0,number_of_processes-1);

	for(j=count;j<number_of_processes;j++)
	{
		if(arr[j]==curr)
		{
			break;
		}
	}

	if(arr[j]-arr[j-1]>arr[j+1]-arr[j])
	{
		for(int i=j+1;i<number_of_processes;i++)
		{
			arr_working[k++]=arr[i];
		}

		for(int i=0;i<j;i++)
		{
			arr_working[k++]=arr[i];
		}

	}

	else
	{


		for(int i=j-1;i>=0;i--)
		{
			arr_working[k++]=arr[i];
		}

		for(int i=number_of_processes-1;i>j;i--)
		{
			arr_working[k++]=arr[i];
		}

	}
	
	display_arr();
	display_arr_working();

	
	for(int i=0;i<number_of_processes;i++)
	{
		arr[i]=arr_temp[i];
	}

}


void scan()
{

	int curr,k=0, count=0,j;

	curr=arr[0];

	arr_working[k++]=curr;

	quicksort(arr,0,number_of_processes-1);

	for(j=count;j<number_of_processes;j++)
	{
		if(arr[j]==curr)
		{
			break;
		}
	}

	if(arr[j]-arr[j-1]>arr[j+1]-arr[j])
	{
		for(int i=j+1;i<number_of_processes;i++)
		{
			arr_working[k++]=arr[i];
		}

        arr_working[k++]=max_cylinders-1;

        for(int i=j-1;i>=0;i--)
		{
			arr_working[k++]=arr[i];
		}

	}

	else
	{

		for(int i=j-1;i>=0;i--)
		{
			arr_working[k++]=arr[i];
		}

		arr_working[k++]=0;

		for(int i=j+1;i<number_of_processes;i++)
		{
			arr_working[k++]=arr[i];
		}

	}
	
	display_arr();
	display_arr_working_scan();

	
	for(int i=0;i<number_of_processes;i++)
	{
		arr[i]=arr_temp[i];
	}

}


void c_scan()
{

	int curr,k=0, count=0,j;

	curr=arr[0];

	arr_working[k++]=curr;

	quicksort(arr,0,number_of_processes-1);

	for(j=count;j<number_of_processes;j++)
	{
		if(arr[j]==curr)
		{
			break;
		}
	}

	if(arr[j]-arr[j-1]>arr[j+1]-arr[j])
	{
		for(int i=j+1;i<number_of_processes;i++)
		{
			arr_working[k++]=arr[i];
		}

		arr_working[k++]=max_cylinders-1;

		arr_working[k++]=0;

		for(int i=0;i<j;i++)
		{
			arr_working[k++]=arr[i];
		}

	}

	else
	{


		for(int i=j-1;i>=0;i--)
		{
			arr_working[k++]=arr[i];
		}

		arr_working[k++]=0;

		arr_working[k++]=max_cylinders-1;

		for(int i=number_of_processes-1;i>j;i--)
		{
			arr_working[k++]=arr[i];
		}

	}
	
	     
    display_arr();
    display_arr_working_cscan();

	for(int i=0;i<number_of_processes;i++)
	{
		arr[i]=arr_temp[i];
	}

}




void menu()
{
	
	
	int choice;
	
	while(choice!=7)
	{	
		system("cls");
		
		display_arr();
		display_arr_working();
		
		printf("\n1. FCFS\n");
		printf("2. SSTF\n");
		printf("3. LOOK\n");
		printf("4. C-LOOK\n");
		printf("5. SCAN\n");
		printf("6. C-SCAN\n");
		printf("7. Exit\n");
		printf("\n\nEnter your choice:\t");
		scanf("%d",&choice);
		
		switch(choice)
		{
			case 1:	total_head_movement=0;fcfs();	system("pause");
					break;
			case 2:	total_head_movement=0;sstf(); system("pause");
					break;
			case 3:	total_head_movement=0;look(); system("pause");
					break;
			case 4:	total_head_movement=0;c_look(); system("pause");
					break;
			case 5:	total_head_movement=0;scan(); system("pause");
					break;
			case 6:	total_head_movement=0;c_scan(); system("pause");
					break;
			case 7:	 system("pause"); exit(0);//dekhte hain. DEV C++ mein exit() ka alternative kya hai.
					break;
			default: break;
		};
		
				
	}

}

int main()
{
	
	initialize_arr();

	initialize_arr_working();

	input();

	menu();
	
	return 0;
}
