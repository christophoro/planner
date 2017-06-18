#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int n;
	int p;
	struct node *next;
} node;

void list(int p, node *head);
void create(int n, int p, node *& hi, node *& nm, node *& lo, int *pr);
void terminate(int n, node *& head);
void nextproc(node *& hi, node *& nm, node *& lo);

int main() {
	char input[10];
	char c; // instrukcja
	int  n;	// nr procesu
	int  p; // priorytet 
	int  x; 
	int pr[10000];

	node *hi = NULL;
	node *nm = NULL;
	node *lo = NULL;

	while (1) {
		fgets(input, sizeof input, stdin);
		sscanf(input, "%c %d %d", &c, &n, &p);

		if (c == 'l'){
	       		list( 1, hi);
	       		list( 0, nm);
	       		list(-1, lo);
		}

		if (c == 'c')
			create(n, p, hi, nm, lo, pr);

		if (c == 't') {
			x = pr[n];
			if (x == 1)
				terminate(n, hi);
			else if (x == 0)
				terminate(n, nm);
			else
				terminate(n, lo);
		}

		if (c == 'p') {
			x = pr[n];
			if (x == 1)
				terminate(n, hi);
			else if (x == 0)
				terminate(n, nm);
			else
				terminate(n, lo);
			create(n, p, hi, nm, lo, pr);
		}


		if (c == 'n')
			nextproc(hi, nm, lo);
	}
}

void list(int p, node *head) {
	node *ptr;
	printf("%d : ", p);
	if (head) {
		ptr = head->next;
		do {
			if (ptr->p == p)
				printf("%d ", ptr->n);
			ptr = ptr->next;
		} while (ptr != head->next);
	}
	printf("\n");
}

void create(int n, int p, node *& hi, node *& nm, node *& lo, int *pr) {
	node *ptr = new node;

	pr[n] = p;
	ptr->n = n;
	ptr->p = p;
	if (p == 1) {
		if (hi) {
			ptr->next = hi->next;
			hi->next = ptr;
		}
		else
			ptr->next = ptr;
		hi = ptr;
		return;
	}
	else if (p == 0) {
		if (nm) {
			ptr->next = nm->next;
			nm->next = ptr;
		}
		else
			ptr->next = ptr;
		nm = ptr;
		return;
	}
	else if (p == -1) {
		if (lo) {
			ptr->next = lo->next;
			lo->next = ptr;
		}
		else
			ptr->next = ptr;
		lo = ptr;
	}
}

void terminate(int n, node *& head) {
	if (head) {
		node *ptr = head;
		node *del;

		while (ptr->next->n != n) {
			ptr = ptr->next;
			if (ptr == head)
				return;
		}
		del = ptr->next;
		if (del == head)
			head = head->next;
		if (ptr->next != ptr)
			ptr->next = ptr->next->next;
		else
			head = NULL;
		delete del;
	}
}

void nextproc(node *& hi, node *& nm, node *& lo) {
	if (lo) {
		printf("%d\n", lo->next->n);
		lo = lo->next;
		return;
	}
	if (nm) {
		printf("%d\n", nm->next->n);
		nm = nm->next;
		return;
	}
	if (hi) {
		printf("%d\n", hi->next->n);
		hi = hi->next;
		return;
	}
	printf("idle\n");
}
