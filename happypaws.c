#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Pet {
    int id;
    char name[30];
    int health;
    int hunger;
    int happiness;
    struct Pet *next;
};

struct Pet *head = NULL;

struct Action {
    int petId;
    char type[20];
};

struct Action stack[100];
int top = -1;

void pushAction(int id, char type[]) {
    if (top < 99) {
        top++;
        stack[top].petId = id;
        strcpy(stack[top].type, type);
    }
}

struct Action popAction() {
    struct Action a = {-1, ""};
    if (top >= 0) {
        a = stack[top];
        top--;
    }
    return a;
}

struct Pet* findPet(int id) {
    struct Pet *temp = head;
    while (temp != NULL) {
        if (temp->id == id)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

void addPet() {
    struct Pet *newPet = (struct Pet*)malloc(sizeof(struct Pet));
    if (!newPet) {
        printf("Memory error.\n");
        return;
    }

    printf("\nEnter Pet ID: ");
    scanf("%d", &newPet->id);

    printf("Enter Name: ");
    scanf("%s", newPet->name);

    newPet->health = 100;
    newPet->hunger = 40;
    newPet->happiness = 60;
    newPet->next = NULL;

    if (!head) {
        head = newPet;
    } else {
        struct Pet *temp = head;
        while (temp->next)
            temp = temp->next;
        temp->next = newPet;
    }

    printf("%s added.\n", newPet->name);
}

void viewPets() {
    if (!head) {
        printf("\nNo pets.\n");
        return;
    }

    struct Pet *temp = head;
    printf("\n- Pet List -\n");

    while (temp) {
        printf("\nID: %d\n", temp->id);
        printf("Name: %s\n", temp->name);
        printf("Health: %d\n", temp->health);
        printf("Hunger: %d\n", temp->hunger);
        printf("Happiness: %d\n", temp->happiness);
        temp = temp->next;
    }
}

void feedPet() {
    int id;
    printf("\nEnter Pet ID: ");
    scanf("%d", &id);

    struct Pet *p = findPet(id);
    if (!p) {
        printf("Pet not found.\n");
        return;
    }

    pushAction(id, "feed");

    p->hunger -= 15;
    if (p->hunger < 0) p->hunger = 0;

    p->health += 5;
    if (p->health > 100) p->health = 100;

    printf("%s fed.\n", p->name);
}

void playPet() {
    int id;
    printf("\nEnter Pet ID: ");
    scanf("%d", &id);

    struct Pet *p = findPet(id);
    if (!p) {
        printf("Pet not found.\n");
        return;
    }

    pushAction(id, "play");

    p->happiness += 10;
    if (p->happiness > 100) p->happiness = 100;

    p->hunger += 5;
    if (p->hunger > 100) p->hunger = 100;

    printf("Played with %s.\n", p->name);
}

void deletePet() {
    int id;
    printf("\nEnter Pet ID: ");
    scanf("%d", &id);

    struct Pet *temp = head;
    struct Pet *prev = NULL;

    while (temp && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (!temp) {
        printf("Pet not found.\n");
        return;
    }

    if (!prev) {
        head = temp->next;
    } else {
        prev->next = temp->next;
    }

    free(temp);
    printf("Pet removed.\n");
}

void undoAction() {
    struct Action a = popAction();

    if (a.petId == -1) {
        printf("\nNothing to undo.\n");
        return;
    }

    struct Pet *p = findPet(a.petId);
    if (!p) {
        printf("Pet not found.\n");
        return;
    }

    if (strcmp(a.type, "feed") == 0) {
        p->hunger += 15;
        p->health -= 5;
        printf("Feed undone.\n");
    } else if (strcmp(a.type, "play") == 0) {
        p->happiness -= 10;
        p->hunger -= 5;
        printf("Play undone.\n");
    }
}

void showMenu() {
    printf("\n- HappyPaws Menu -\n");
    printf("1. Add Pet\n");
    printf("2. View Pets\n");
    printf("3. Feed Pet\n");
    printf("4. Play with Pet\n");
    printf("5. Undo Last Action\n");
    printf("6. Delete Pet\n");
    printf("7. Exit\n");
    printf("Choice: ");
}

int main() {
    int choice;
    printf("Welcome to HappyPaws\n");

    while (1) {
        showMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addPet();
                break;
            case 2:
                viewPets();
                break;
            case 3:
                feedPet();
                break;
            case 4:
                playPet();
                break;
            case 5:
                undoAction();
                break;
            case 6:
                deletePet();
                break;
            case 7:
                printf("Goodbye.\n");
                exit(0);
            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}

