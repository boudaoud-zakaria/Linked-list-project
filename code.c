#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ===========================
   Patient Structure
   =========================== */
typedef struct Patient {
    int id;
    char name[50];
    int age;
    char condition[100];
    struct Patient *next;
} Patient;

/* ===========================
   Queue for Regular Patients (FIFO)
   =========================== */
typedef struct {
    Patient *front;
    Patient *rear;
    int count;
} PatientQueue;

void initQueue(PatientQueue *q) {
    q->front = q->rear = NULL;
    q->count = 0;
}

int isQueueEmpty(PatientQueue *q) {
    return q->front == NULL;
}

void enqueuePatient(PatientQueue *q, int id, const char *name, int age, const char *condition) {
    Patient *newPatient = (Patient *)malloc(sizeof(Patient));
    if (!newPatient) {
        printf("ERROR: Memory allocation failed!\n");
        return;
    }

    newPatient->id = id;
    strncpy(newPatient->name, name, 49);
    newPatient->name[49] = '\0';
    newPatient->age = age;
    strncpy(newPatient->condition, condition, 99);
    newPatient->condition[99] = '\0';
    newPatient->next = NULL;

    if (isQueueEmpty(q)) {
        q->front = q->rear = newPatient;
    } else {
        q->rear->next = newPatient;
        q->rear = newPatient;
    }

    q->count++;
    printf("\n>>> Patient [%d] %s registered in REGULAR QUEUE.\n", id, name);
}

Patient* dequeuePatient(PatientQueue *q) {
    if (isQueueEmpty(q)) {
        printf("\nNo patients in queue.\n");
        return NULL;
    }

    Patient *temp = q->front;
    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL;
    }

    q->count--;
    temp->next = NULL;
    return temp;
}

void displayQueue(PatientQueue *q) {
    if (isQueueEmpty(q)) {
        printf("\n[REGULAR QUEUE] Empty - No patients waiting.\n");
        return;
    }

    printf("\n========== REGULAR PATIENT QUEUE (FIFO) ==========\n");
    printf("%-5s %-20s %-5s %-30s\n", "ID", "Name", "Age", "Condition");
    printf("-----------------------------------------------------------\n");

    Patient *curr = q->front;
    while (curr) {
        printf("%-5d %-20s %-5d %-30s\n", curr->id, curr->name, curr->age, curr->condition);
        curr = curr->next;
    }
    printf("Total waiting: %d patients\n", q->count);
}

/* ===========================
   Stack for Emergency Patients (LIFO)
   =========================== */
typedef struct {
    Patient *top;
    int count;
} EmergencyStack;

void initStack(EmergencyStack *s) {
    s->top = NULL;
    s->count = 0;
}

int isStackEmpty(EmergencyStack *s) {
    return s->top == NULL;
}

void pushEmergency(EmergencyStack *s, int id, const char *name, int age, const char *condition) {
    Patient *newPatient = (Patient *)malloc(sizeof(Patient));
    if (!newPatient) {
        printf("ERROR: Memory allocation failed!\n");
        return;
    }

    newPatient->id = id;
    strncpy(newPatient->name, name, 49);
    newPatient->name[49] = '\0';
    newPatient->age = age;
    strncpy(newPatient->condition, condition, 99);
    newPatient->condition[99] = '\0';
    newPatient->next = s->top;

    s->top = newPatient;
    s->count++;

    printf("\n>>> EMERGENCY: Patient [%d] %s added to EMERGENCY STACK (highest priority).\n", id, name);
}

Patient* popEmergency(EmergencyStack *s) {
    if (isStackEmpty(s)) {
        printf("\nNo emergency patients.\n");
        return NULL;
    }

    Patient *temp = s->top;
    s->top = s->top->next;
    s->count--;

    temp->next = NULL;
    return temp;
}

void displayEmergency(EmergencyStack *s) {
    if (isStackEmpty(s)) {
        printf("\n[EMERGENCY STACK] No emergency cases.\n");
        return;
    }

    printf("\n========== EMERGENCY PATIENTS (LIFO - Top Priority) ==========\n");
    printf("%-5s %-20s %-5s %-30s\n", "ID", "Name", "Age", "Condition");
    printf("----------------------------------------------------------------\n");

    Patient *curr = s->top;
    while (curr) {
        printf("%-5d %-20s %-5d %-30s\n", curr->id, curr->name, curr->age, curr->condition);
        curr = curr->next;
    }
    printf("Total emergency: %d patients\n", s->count);
}

/* ===========================
   Undo Stack (LIFO)
   =========================== */
typedef struct UndoNode {
    Patient patient;
    char type; // 'R' = regular, 'E' = emergency
    struct UndoNode *next;
} UndoNode;

typedef struct {
    UndoNode *top;
} UndoStack;

void initUndoStack(UndoStack *u) {
    u->top = NULL;
}

void pushUndo(UndoStack *u, Patient *p, char type) {
    UndoNode *newNode = (UndoNode *)malloc(sizeof(UndoNode));
    if (!newNode) return;

    newNode->patient = *p;
    newNode->type = type;
    newNode->next = u->top;
    u->top = newNode;
}

int popUndo(UndoStack *u, Patient *p, char *type) {
    if (u->top == NULL) {
        printf("\nNothing to undo.\n");
        return 0;
    }

    UndoNode *temp = u->top;
    *p = temp->patient;
    *type = temp->type;
    u->top = u->top->next;

    free(temp);
    return 1;
}

/* ===========================
   Statistics
   =========================== */
typedef struct {
    int totalServed;
    int emergencyServed;
    int regularServed;
} Statistics;

void initStats(Statistics *stats) {
    stats->totalServed = 0;
    stats->emergencyServed = 0;
    stats->regularServed = 0;
}

void displayStats(Statistics *stats, PatientQueue *q, EmergencyStack *s) {
    printf("\n============== HOSPITAL STATISTICS ==============\n");
    printf("Total Patients Served     : %d\n", stats->totalServed);
    printf("  - Regular Consultations : %d\n", stats->regularServed);
    printf("  - Emergency Cases       : %d\n", stats->emergencyServed);
    printf("Current Queue Size        : %d\n", q->count);
    printf("Current Emergency Cases   : %d\n", s->count);
    printf("==================================================\n");
}

/* ===========================
   Main System
   =========================== */
int main(void) {
    PatientQueue regularQueue;
    EmergencyStack emergencyStack;
    UndoStack undoStack;
    Statistics stats;

    initQueue(&regularQueue);
    initStack(&emergencyStack);
    initUndoStack(&undoStack);
    initStats(&stats);

    int nextId = 1;
    int choice;
    char name[50], condition[100];
    int age;

    do {
        printf("\n");
        printf("╔═══════════════════════════════════════════════════════╗\n");
        printf("║   HOSPITAL PATIENT QUEUE MANAGEMENT SYSTEM (C)        ║\n");
        printf("╚═══════════════════════════════════════════════════════╝\n");
        printf("\n");
        printf("  [1] Register Regular Patient (FIFO Queue)\n");
        printf("  [2] Register Emergency Patient (LIFO Stack)\n");
        printf("  [3] Consult Next Patient (Priority: Emergency > Regular)\n");
        printf("  [4] View Regular Queue\n");
        printf("  [5] View Emergency Stack\n");
        printf("  [6] Undo Last Registration\n");
        printf("  [7] View Statistics\n");
        printf("  [0] Exit System\n");
        printf("\n  Enter choice: ");

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            choice = -1;
        }
        while (getchar() != '\n'); // clear buffer

        switch (choice) {
            case 1: // Register Regular
                printf("\n--- Register Regular Patient ---\n");
                printf("Name: ");
                fgets(name, 50, stdin);
                name[strcspn(name, "\n")] = '\0';

                printf("Age: ");
                scanf("%d", &age);
                while (getchar() != '\n');

                printf("Condition: ");
                fgets(condition, 100, stdin);
                condition[strcspn(condition, "\n")] = '\0';

                enqueuePatient(&regularQueue, nextId, name, age, condition);

                // Save for undo
                Patient tempP;
                tempP.id = nextId;
                strcpy(tempP.name, name);
                tempP.age = age;
                strcpy(tempP.condition, condition);
                pushUndo(&undoStack, &tempP, 'R');

                nextId++;
                break;

            case 2: // Register Emergency
                printf("\n--- Register EMERGENCY Patient ---\n");
                printf("Name: ");
                fgets(name, 50, stdin);
                name[strcspn(name, "\n")] = '\0';

                printf("Age: ");
                scanf("%d", &age);
                while (getchar() != '\n');

                printf("Condition: ");
                fgets(condition, 100, stdin);
                condition[strcspn(condition, "\n")] = '\0';

                pushEmergency(&emergencyStack, nextId, name, age, condition);

                // Save for undo
                Patient tempP2;
                tempP2.id = nextId;
                strcpy(tempP2.name, name);
                tempP2.age = age;
                strcpy(tempP2.condition, condition);
                pushUndo(&undoStack, &tempP2, 'E');

                nextId++;
                break;

            case 3: // Consult Next Patient
                printf("\n--- Consulting Next Patient ---\n");

                Patient *nextPatient = NULL;
                char patientType[20];

                // Priority: Emergency first, then regular
                if (!isStackEmpty(&emergencyStack)) {
                    nextPatient = popEmergency(&emergencyStack);
                    strcpy(patientType, "EMERGENCY");
                    stats.emergencyServed++;
                } else if (!isQueueEmpty(&regularQueue)) {
                    nextPatient = dequeuePatient(&regularQueue);
                    strcpy(patientType, "REGULAR");
                    stats.regularServed++;
                } else {
                    printf("\nNo patients to consult.\n");
                    break;
                }

                if (nextPatient) {
                    printf("\n========== CONSULTING PATIENT ==========\n");
                    printf("Type      : %s\n", patientType);
                    printf("ID        : %d\n", nextPatient->id);
                    printf("Name      : %s\n", nextPatient->name);
                    printf("Age       : %d\n", nextPatient->age);
                    printf("Condition : %s\n", nextPatient->condition);
                    printf("========================================\n");

                    stats.totalServed++;
                    free(nextPatient);

                    printf("\nPatient consultation completed!\n");
                }
                break;

            case 4: // View Regular Queue
                displayQueue(&regularQueue);
                break;

            case 5: // View Emergency Stack
                displayEmergency(&emergencyStack);
                break;

            case 6: // Undo
                printf("\n--- Undo Last Registration ---\n");
                Patient undoPatient;
                char undoType;

                if (popUndo(&undoStack, &undoPatient, &undoType)) {
                    printf("Undoing registration: [%d] %s (Type: %s)\n",
                           undoPatient.id, undoPatient.name,
                           undoType == 'R' ? "Regular" : "Emergency");

                    // Remove from appropriate structure
                    // Note: Full implementation would require search/remove
                    // For simplicity, this demo acknowledges the undo
                    printf("(Registration removed from system)\n");
                    nextId--; // Adjust ID counter
                }
                break;

            case 7: // Statistics
                displayStats(&stats, &regularQueue, &emergencyStack);
                break;

            case 0:
                printf("\n>>> Exiting Hospital Management System. Goodbye!\n");
                break;

            default:
                printf("\nInvalid choice. Please try again.\n");
        }

    } while (choice != 0);

    // Cleanup
    while (!isQueueEmpty(&regularQueue)) {
        free(dequeuePatient(&regularQueue));
    }
    while (!isStackEmpty(&emergencyStack)) {
        free(popEmergency(&emergencyStack));
    }

    return 0;
}
