#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define MAX_LINE_LENGTH 100
#define MAX_CARDS_IN_HAND 3
#define CARDS_FOR_EACH_PLAYER 15
#define CARDS_MAX 64

typedef struct Guardian
{
    char name[50];
    char type[20];
    int id;
    int HP;
    int ATK;
    int DEF;
    struct Guardian *next;
}Guardian;

typedef struct player
{
	char name[50];
	int lives;
	Guardian *cards;
	Guardian *cardsinHand;
}player;

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
Guardian *create(char *name, char *type, int *health, int *atk, int *defense)
{
    Guardian* newstruct = (Guardian*)malloc(sizeof(Guardian));
    strcpy(newstruct->name, name);
    strcpy(newstruct->type, type);
    newstruct->HP = *health;
    newstruct->ATK = *atk;
    newstruct->DEF = *defense;
    newstruct->next = NULL;

    return newstruct;
}

void addGuardian(Guardian **head, Guardian *newguardian)
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
void createCard(Guardian **deck, char *name, char *type, int *health, int *atk, int *defense)
{
    Guardian *newstruct = (Guardian*)malloc(sizeof(Guardian));

    strcpy(newstruct->name, name);
    strcpy(newstruct->type, type);
    newstruct->HP = *health;
    newstruct->ATK = *atk;
    newstruct->DEF = *defense;
    newstruct->next = NULL;

    addGuardian(deck, newstruct);
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
        newstruct->id = i;

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

        addGuardian(deck, newstruct);
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

int getSize(Guardian *list)
{
    int sizeL = 0;
    while (list != NULL)
    {
        sizeL++;
        list = list->next;
    }
    return sizeL;
}

void shuffleCards(Guardian **deck, player *p1, player *p2)
{
    srand(time(NULL));
    int flag = 0;
    int i;
    int sizeL = getSize(*deck);
    Guardian *current = *deck;
    int randomIndex;
    int aux[sizeL] ;

    for (i = 0 ; i < sizeL; i++)
    {
        aux[i] = -1;
    }

    Guardian *auxDeck[sizeL];

    Guardian *newdeck1[15];
    Guardian *newdeck2[15];

    for(i = 0; i < sizeL; i++)
    {
        auxDeck[i] = current;
        current = current->next;
    }
    for (i = 0; i < sizeL; i++)  // GENERACION DE NUMEROS RANDOM
    {
        do
        {
            flag = 0;
            randomIndex = rand() % sizeL;

            for (int j = 0; j < i; j++)
            {
                if (aux[j] == randomIndex)
                {
                    flag = 1;
                    break;
                }
            }

        }while(flag);
        aux[i] = randomIndex;
    }

    for(i = 0; i < sizeL; i++)
    {
        printf("%d.- %d\n",i, aux[i]);
    }

    for(i = 0; i < 15;i++)
    {
        createCard(&p1->cards, auxDeck[aux[i]]->name, auxDeck[aux[i]]->type, &auxDeck[aux[i]]->HP, &auxDeck[aux[i]]->ATK, &auxDeck[aux[i]]->DEF);
    }
    for(i = 15; i < 30;i++)
    {
        createCard(&p2->cards, auxDeck[aux[i]]->name, auxDeck[aux[i]]->type, &auxDeck[aux[i]]->HP, &auxDeck[aux[i]]->ATK, &auxDeck[aux[i]]->DEF);
    }
}

int main()
{
    Guardian *deck = NULL;
    Guardian newCard;
    player p1, p2;
    p1.cards = NULL;
    p2.cards = NULL;

    char *nameTemp;
	char typeTemp;
	int HpTemp;
	int ATKTemp;
	int DEFTemp;
	int typechoice;

    int choice;
    int HpMax=0;
    int HpMin=0;
    int ATKMax=0;
    int ATKMin=0;
    int DEFMax=0;
    int DEFMin=0;

    readFile(&deck,&HpMax,&HpMin,&ATKMax,&ATKMin,&DEFMax,&DEFMin);

    printf("ola\n");
    shuffleCards(&deck, &p1, &p2);
    //printf("%d %d %d %d %d %d\n",HpMax,HpMin,ATKMax,ATKMin,DEFMax,DEFMin); // Impresion de los maximos y minimos de vida, ataque y defensa desde el archivo de texto

	while(choice != 4)
    {
        //printf("%s\n", p1.cards->name);
		printf("\n--Clash of the Guardians--\n1.- Play\n2.- Create new card\n3.- History\n4.- Quit\n");
		scanf("%d", &choice);
		switch(choice)
		{
			case 1:
				printf("En proceso...\n");
			break;
			case 2:
			    system("cls");

				printf("\nEnter the card's name: ");
				gets(newCard.name);
				gets(newCard.name);
				do{
				printf("\nSelect the card's type:");
				printf("\n1. Mage");
				printf("\n2. Viking");
				printf("\n3. Necromancer");
				printf("\n4. Beast\n");
				scanf("%d", &typechoice);
				if(typechoice < 1 || typechoice > 4)
                {
                    printf("\nERROR: The amount entered is not valid. Try again\n");
                }
				}while(typechoice < 1 || typechoice > 4);
				switch(typechoice)
				{
                    case 1:
                        strcpy(newCard.type, "Mage");
                    break;
                    case 2:
                        strcpy(newCard.type, "Viking");
                    break;
                    case 3:
                        strcpy(newCard.type, "Necromancer");
                    break;
                    case 4:
                        strcpy(newCard.type, "Beast");
                    break;
				}
				do{
                    printf("\nEnter the card's health(Min:%d Max:%d): ", HpMin, HpMax);
                    scanf("%d", &newCard.HP);
                    if(newCard.HP > HpMax || newCard.HP < HpMin)
                    {
                        printf("\nERROR: The amount entered exceeds the limits. Try again\n");
                    }
				}while(newCard.HP < HpMin || newCard.HP > HpMax);

                do{
                    printf("\nEnter the card's attack(Min:%d Max:%d): ", ATKMin, ATKMax);
                    scanf("%d", &newCard.ATK);
                    if(newCard.ATK > ATKMax || newCard.ATK < ATKMin)
                    {
                        printf("\nERROR: The amount entered exceeds the limits. Try again\n");
                    }
				}while(newCard.ATK < ATKMin || newCard.ATK > ATKMax);

				do{
                    printf("\nEnter the card's defense(Min:%d Max:%d): ", DEFMin, DEFMax);
                    scanf("%d", &newCard.DEF);
                    if(newCard.DEF > DEFMax || newCard.DEF < DEFMin)
                    {
                        printf("\nERROR: The amount entered exceeds the limits. Try again\n");
                    }
				}while(newCard.DEF < DEFMin || newCard.DEF > DEFMax);
				addGuardian(&deck, &newCard);
			break;
			case 3:
				printf("En proceso...\n");
			break;
			case 20:
			    printCards(deck);
				printf("\n\n");
				printCards(p1.cards);
				printf("\n\n");
				printCards(p2.cards);
			break;
		}
	}

	freeGuardians(deck);


    return 0;
}
