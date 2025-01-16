#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX 100

struct process
{
	int pid, at, bt, ct, tat, wt;
};

struct Queue
{
	struct process *arr[MAX];
	int front, rear;
};

struct Queue *createQueue()
{
	struct Queue *queue = (struct Queue *)malloc(sizeof(struct Queue));
	queue->front = -1;
	queue->rear = -1;
	return queue;
}

int isFull(struct Queue *queue)
{
	return (queue->rear + 1) % MAX == queue->front;
}

int isEmpty(struct Queue *queue)
{
	return queue->front == -1;
}

void enqueue(struct Queue *queue, struct process *p)
{
	if (isFull(queue))
	{
		printf("Queue Overflow! Cannot enqueue process with PID %d\n", p->pid);
		return;
	}

	if (isEmpty(queue))
	{
		queue->front = 0;
	}
	queue->rear = (queue->rear + 1) % MAX;
	queue->arr[queue->rear] = p;
}

struct process *dequeue(struct Queue *queue)
{
	if (isEmpty(queue))
	{
		printf("Queue Underflow! Cannot dequeue from empty queue.\n");
		return NULL;
	}

	struct process *p = queue->arr[queue->front];

	if (queue->front == queue->rear)
	{
		queue->front = -1;
		queue->rear = -1;
	}
	else
	{
		queue->front = (queue->front + 1) % MAX;
	}

	return p;
}

int compare(const void *s1, const void *s2)
{
	struct process *p1 = (struct process *)s1;
	struct process *p2 = (struct process *)s2;
	return p1->at - p2->at;
}

void move_cursor(int col, int n)
{
	printf("\r");
	printf("\033[%dC", n * col);
	fflush(stdout);
}

int main()
{
	struct process p[10];
	struct Queue *pQueue = createQueue();

	int n, i, total_wait = 0, total_tat = 0, latest_ct = 0;

	printf("Enter total number of processes: ");
	scanf("%d", &n);

	for (i = 0; i < n; i++)
	{
		printf("Enter process id: ");
		scanf("%d", &p[i].pid);
		printf("Enter process arrival time: ");
		scanf("%d", &p[i].at);
		printf("Enter process burst time: ");
		scanf("%d", &p[i].bt);
		p[i].ct = 0;
		p[i].tat = 0;
		p[i].wt = 0;
	}

	qsort(p, n, sizeof(struct process), compare);

	for (i = 0; i < n; i++)
	{
		if (i == 0 || p[i].at > latest_ct)
		{
			latest_ct += (p[i].at > latest_ct) ? (p[i].at - latest_ct) : 0;
			enqueue(pQueue, &p[i]);
			latest_ct += p[i].bt;
			p[i].ct = latest_ct;
			p[i].tat = p[i].ct - p[i].at;
			p[i].wt = p[i].tat - p[i].bt;

			total_wait += p[i].wt;
			total_tat += p[i].tat;

			while (!isEmpty(pQueue))
			{
				struct process *nextProcess = dequeue(pQueue);
				nextProcess->ct = latest_ct + nextProcess->bt;
				latest_ct = nextProcess->ct;
				nextProcess->tat = nextProcess->ct - nextProcess->at;
				nextProcess->wt = nextProcess->tat - nextProcess->bt;

				total_wait += nextProcess->wt;
				total_tat += nextProcess->tat;

				enqueue(pQueue, nextProcess);
			}
		}
	}

	printf("Printing Gantt Chart:\n");

	printf("%d", 0);

	for (i = 0; i < n; i++)
	{
		move_cursor(p[i].ct, 4);
		printf("%d", p[i].ct);
	}

	printf("\n");

	int mv = 0;

	for (i = 0; i < n; i++)
	{
		move_cursor(mv + (p[i + 1].ct - p[i].ct) / 2, 4);
		mv = p[i].ct;
		printf("P%d", p[i].pid);
	}

	printf("\n\nAverage TAT is %f\n", (float)total_tat / n);
	printf("Average WT is %f\n", (float)total_wait / n);

	free(pQueue);

	return 0;
}
