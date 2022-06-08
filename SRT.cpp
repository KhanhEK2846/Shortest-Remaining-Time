#include<stdio.h>
#pragma warning(disable : 4996)

struct process
{
	int Name, Arrival, Burst, Waiting, Turnaround, Start, Finish;
};

int AllTime(process a[], int n)
{
	int time = 0;
	for (int i = 0; i < n; ++i)
	{
		if (time < a[i].Arrival)
			time = a[i].Arrival;
		time = a[i].Burst + time;
	}
	return time;
}

void Input(process a[], int& n)
{
	printf("Moi nhap so luong process: ");
	scanf("%d", &n);
	for (int i = 0; i < n; ++i)
	{
		printf("Moi nhap ten, thoi gian den, burst time cua tien trinh thu %d: ", i + 1);
		scanf("%d%d%d", &a[i].Name, &a[i].Arrival, &a[i].Burst);
		a[i].Start = -1;
		a[i].Turnaround = 0;
		a[i].Waiting = 0;
		a[i].Finish = 0;
	}
}


void Output(process a[], int n, int b, int c)
{
	printf("\nPName\tResponse\tWaiting\tTurnaround");
	for (int i = 0; i < n; i++)
	{
		printf("\n%d\t%d\t\t%d\t%d\t", a[i].Name, a[i].Start, a[i].Waiting, a[i].Turnaround);
	}
	float arvw = (float)b / n;
	float arvt = (float)c / n;
	printf("\nAverage waiting time: %f", arvw);
	printf("\nAverage turnaroundtime: %f", arvt);
}

void HoanVi(int& a, int& b)
{
	int tmp = a;
	a = b;
	b = tmp;
}

void IterchangeSortTime(process a[], int n)
{
	for (int i = 0; i < n - 1; ++i)
	{
		for (int j = i + 1; j < n; ++j)
			if (a[i].Arrival > a[j].Arrival)
			{
				HoanVi(a[i].Name, a[j].Name);
				HoanVi(a[i].Arrival, a[j].Arrival);
				HoanVi(a[i].Burst, a[j].Burst);
			}
	}
}




void SRT(process a[], int n, int& Twaiting, int& TTurnaround)
{
	int smallest;
	int CopyBurst[10];
	for (int i = 0; i < n; ++i)
		CopyBurst[i] = a[i].Burst;
	a[9].Burst = 9999;
	int time, count = 0;
	for (time = 0; count != n; ++time)
	{
		smallest = 9;
		for(int i=0;i<n;++i)
			if (a[i].Arrival <= time && a[i].Burst < a[smallest].Burst && a[i].Burst>0)
			{
				smallest = i;
			}
		if (a[smallest].Start == -1)
		{
				a[smallest].Start = time - a[smallest].Arrival;
		}
		--a[smallest].Burst;
		if (a[smallest].Burst == 0)
		{
			int end = time + 1;
			a[smallest].Finish = end;
			a[smallest].Waiting = end - a[smallest].Arrival - CopyBurst[smallest];
			a[smallest].Turnaround = end - a[smallest].Arrival;
			count++;
		}
	}
	for (int i = 0; i < n; ++i)
	{
		a[i].Burst = CopyBurst[i];
		Twaiting += a[i].Waiting;
		TTurnaround += a[i].Turnaround;
	}
}

int main()
{
	int n;
	int Twaiting = 0;
	int TTurnaround = 0;
	process a[10];
	Input(a, n);
	SRT(a, n, Twaiting, TTurnaround);
	Output(a, n, Twaiting, TTurnaround);
    return 0;
}


