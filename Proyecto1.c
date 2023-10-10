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

void imprimir(Guardian *deck)
{
    printf("\nMazo:\n");
    while (deck != NULL)
    {
        printf("%s %s %d %d %d\n", deck->name, deck->type, deck->HP, deck->ATK, deck->DEF);
        deck = deck->next;
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

void readFile(Guardian **deck)
{
    FILE *file = fopen("guardianes.txt", "r");
    if (file == NULL)
    {
        return;
    }

    char line[MAX_LINE_LENGTH]; //MAX_LINE_LENGTH es un valor global que definen ustedes

    while(fgets(line, MAX_LINE_LENGTH, file))
    {
        Guardian *newstruct = (Guardian*)malloc(sizeof(Guardian));

        char *text = strtok(line, ",");
        strcpy(newstruct->name, text);

        char *text2 = strtok(NULL, ",");
        strcpy(newstruct->type, text2);

        newstruct->HP = atoi(strtok(NULL, ",")); //atof para valores decimales
        newstruct->ATK = atoi(strtok(NULL, ","));
        newstruct->DEF = atoi(strtok(NULL, ","));

        newstruct->next = NULL;

        // Se añade el Struct creado a la lista existente.
        addStruct(deck, newstruct);
        //printf("%s %s %d %d %d\n", newstruct->name, newstruct->type, newstruct->HP, newstruct->ATK, newstruct->DEF);
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

    int eleccion;

    readFile(&deck);

	while(eleccion != 4)
    {
		printf("\n--BIENVENIDO--\n1.- Jugar\n2.- Crear Carta\n3.- Imprimir Mazo\n4.- Salir\n");
		scanf("%d", &eleccion);
		switch(eleccion)
		{
			case 1:
				printf("En proceso...\n");
			break;
			case 2:
				printf("En proceso...\n");
			break;
			case 3:
				imprimir(deck);
			break;
		}
	}

	freeGuardians(deck);


    return 0;
}
