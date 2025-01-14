#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct process{
	int pid, at, bt, ct, tat, wt;
};

int compare(const void *s1, const void *s2)
{
	struct process *p1 = (struct process *)s1;
	struct process *p2 = (struct process *)s2;
	return p1->at - p2->at;
}

void move_cursor(int col, int n) {
	printf("\r");
    	printf("\033[%dC", n*col);
    	fflush(stdout);
}

int main() {
	struct process p[10];
	int n, i, j, total_wait, total_burst, total_tat, av_turn, av_wait, mv;
	printf("Enter total number of process: ");
	scanf("%d", &n);
	for(i=0; i<n; i++) {
		printf("Enter process id: ");
		scanf("%d", &p[i].pid);
		printf("Enter process arrival time: ");
		scanf("%d", &p[i].at);
		printf("Enter process burst time: ");
		scanf("%d", &p[i].bt);
	}
	qsort(p, n, sizeof(struct process), compare);

	p[0].ct = p[0].bt;
	p[0].tat = p[0].ct - p[0].at;
	p[0].wt = p[0].tat - p[0].bt;
	total_burst = p[0].bt;
	total_tat = p[0].tat;
	total_wait = p[0].wt;

	for(i=1; i<n; i++) 
	{
		p[i].ct = p[i-1].ct + p[i].bt;
		p[i].tat = p[i].ct - p[i].at;
		p[i].wt = p[i].tat - p[i].bt;

		total_burst += p[i].bt;
		total_tat += p[i].tat;
		total_wait += p[i].wt;
	}

	printf("Printing Gantt Chart. \n");
	printf("%d", 0);
	for(i=0; i<n; i++) {
		move_cursor(p[i].ct, 4);
		printf("%d", p[i].ct);
	}
	printf("\n");
	mv = 0;
	for(i=0; i<n; i++) {
		move_cursor(mv + (p[i+1].ct-p[i].ct)/2 ,4);
		mv = p[i].ct;
		printf("P%d", p[i].pid);
	}
	printf("\n\nAverage TAT is %f",(float) total_tat/n);
	printf("\nAverage WT is %f \n", (float) total_wait/n);


	return 0;
}


