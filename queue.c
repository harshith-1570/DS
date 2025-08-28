#include <stdio.h>
#include <stdlib.h>

// Node structure
struct node {
    int data;
    struct node *next;
};

// Queue structure
struct queue {
    struct node *front;
    struct node *rear;
};

// Function prototypes
struct queue *create_queue();
struct queue *insert(struct queue *, int);
struct queue *delete_element(struct queue *);
void display(struct queue *);
int peek(struct queue *);

int main() {
    int val, option;
    struct queue *q = create_queue();

    do {
        printf("\n\n***** MAIN MENU *****");
        printf("\n1. INSERT");
        printf("\n2. DELETE");
        printf("\n3. PEEK");
        printf("\n4. DISPLAY");
        printf("\n5. EXIT");
        printf("\nEnter your option: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                printf("Enter the number to insert in the queue: ");
                scanf("%d", &val);
                q = insert(q, val);
                break;
            case 2:
                q = delete_element(q);
                break;
            case 3:
                val = peek(q);
                if (val != -1)
                    printf("The value at front of queue is: %d", val);
                break;
            case 4:
                display(q);
                break;
            case 5:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid option. Please try again.");
        }
    } while (option != 5);

    return 0;
}

// Create and initialize an empty queue
struct queue *create_queue() {
    struct queue *q = (struct queue *)malloc(sizeof(struct queue));
    q->front = NULL;
    q->rear = NULL;
    return q;
}

// Insert a value into the queue
struct queue *insert(struct queue *q, int val) {
    struct node *ptr = (struct node *)malloc(sizeof(struct node));
    ptr->data = val;
    ptr->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = ptr;
    } else {
        q->rear->next = ptr;
        q->rear = ptr;
    }

    printf("Inserted %d into the queue.", val);
    return q;
}

// Delete the front element from the queue
struct queue *delete_element(struct queue *q) {
    if (q->front == NULL) {
        printf("UNDERFLOW: Queue is empty.");
        return q;
    }

    struct node *ptr = q->front;
    printf("The value being deleted is: %d", ptr->data);

    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(ptr);
    return q;
}

// Peek at the front value of the queue
int peek(struct queue *q) {
    if (q->front == NULL) {
        printf("QUEUE IS EMPTY");
        return -1;
    }
    return q->front->data;
}

// Display all elements in the queue
void display(struct queue *q) {
    struct node *ptr = q->front;
    if (ptr == NULL) {
        printf("QUEUE IS EMPTY");
        return;
    }

    printf("Queue elements: ");
    while (ptr != NULL) {
        printf("%d\t", ptr->data);
        ptr = ptr->next;
    }
}

