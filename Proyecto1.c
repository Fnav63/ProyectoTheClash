#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LINE_LENGTH 100

typedef struct Guardian
{
    char name[50];
    char type[20];
    int HP;
    int ATK;
    int DEF;
    struct Guardian *next;
}Guardian;

void printCards(Guardian *deck)
{
    int i = 1;
    printf("\nDeck:\n");
    while (deck != NULL)
    {
        printf("%d.- %s %s %d %d %d\n", i, deck->name, deck->type, deck->HP, deck->ATK, deck->DEF);
        deck = deck->next;
        i++;
    }
}

void addStruct(Guardian **head, Guardian *newguardian)
{
    if (*head == NULL)
    {
        *head = newguardian;
    }
    else
    {
        Guardian *current = *head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newguardian;
    }
}

void readFile(Guardian **deck, int *HpMax, int *HpMin, int *ATKMax, int *ATKMin, int *DEFMax, int *DEFMin)
{
    int i = 0;
    FILE *file = fopen("guardianes.txt", "r");
    if (file == NULL)
    {
        return;
    }

    char line[MAX_LINE_LENGTH];

    while(fgets(line, MAX_LINE_LENGTH, file))
    {

        Guardian *newstruct = (Guardian*)malloc(sizeof(Guardian));

        char *text = strtok(line, ",");
        strcpy(newstruct->name, text);

        char *text2 = strtok(NULL, ",");
        strcpy(newstruct->type, text2);

        newstruct->HP = atoi(strtok(NULL, ","));
        newstruct->ATK = atoi(strtok(NULL, ","));
        newstruct->DEF = atoi(strtok(NULL, ","));

        if(i == 0)
        {
            *HpMin = newstruct->HP;
            *ATKMin = newstruct->ATK;
            *DEFMin = newstruct->DEF;
        }

        if(newstruct->HP >= *HpMax)
        {
            *HpMax = newstruct->HP;
        }
        if(newstruct->HP <= *HpMin)
        {
            *HpMin = newstruct->HP;
        }
        if(newstruct->ATK >= *ATKMax)
        {
            *ATKMax = newstruct->ATK;
        }
        if(newstruct->ATK <= *ATKMin)
        {
            *ATKMin = newstruct->ATK;
        }
        if(newstruct->DEF >= *DEFMax)
        {
            *DEFMax = newstruct->DEF;
        }
        if(newstruct->DEF <= *DEFMin)
        {
            *DEFMin = newstruct->DEF;
        }

        newstruct->next = NULL;

        addStruct(deck, newstruct);
        i++;
    }
    fclose(file);
}
void freeGuardians(Guardian *head)
{
    Guardian *current = head;

    while (current != NULL)
    {
        Guardian *next = current->next;
        free(current);
        current = next;
    }
}


int main()
{
    Guardian *deck = NULL;

    int choice;
    int HpMax=0;
    int HpMin=0;
    int ATKMax=0;
    int ATKMin=0;
    int DEFMax=0;
    int DEFMin=0;

    readFile(&deck,&HpMax,&HpMin,&ATKMax,&ATKMin,&DEFMax,&DEFMin);

    //printf("%d %d %d %d %d %d\n",HpMax,HpMin,ATKMax,ATKMin,DEFMax,DEFMin); // Impresion de los maximos y minimos de vida, ataque y defensa desde el archivo de texto

	while(choice != 5)
    {
		printf("\n--Clash of the Guardians--\n1.- Play\n2.- Create new card\n3.- History\n4.- Quit\n");
		scanf("%d", &choice);
		switch(choice)
		{
			case 1:
				printf("En proceso...\n");
			break;
			case 2:
				printf("En proceso...\n");
			break;
			case 3:
				printf("En proceso...\n");
			break;
			case 20:
				printCards(deck);
			break;
		}
	}

	freeGuardians(deck);


    return 0;
}
