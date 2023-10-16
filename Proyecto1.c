#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define MAX_LINE_LENGTH 100
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
	Guardian *cardsinTable;
}player;

void printCards(Guardian *deck)
{
    int i = 1;
    printf("\nID   Name  Type HP  ATK  DEF\n\n");
    while (deck != NULL)
    {
        printf("%d.- %s %s %d %d %d\n", deck->id, deck->name, deck->type, deck->HP, deck->ATK, deck->DEF);
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
void createCard2(Guardian **deck,int *id, char *name, char *type, int *health, int *atk, int *defense)
{
    Guardian *newstruct = (Guardian*)malloc(sizeof(Guardian));

    strcpy(newstruct->name, name);
    strcpy(newstruct->type, type);
    newstruct->HP = *health;
    newstruct->ATK = *atk;
    newstruct->DEF = *defense;
    newstruct->id = *id;
    newstruct->next = NULL;

    addGuardian(deck, newstruct);
}

void readFile(Guardian **deck, int *HpMax, int *HpMin, int *ATKMax, int *ATKMin, int *DEFMax, int *DEFMin)
{
    /*
        Aqui es donde se abre el archivo para poder leerlo y guardar su contenido
        a traves de fgets, se reserva la memoria con malloc y luego se llenan los datos
        en los miembros de la estructura.
    */
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
void eraseCard(Guardian **head, int id)
{
    Guardian *current = *head;
    Guardian *last = NULL;

    if (current != NULL && current->id == id)
    {
        *head = current->next;
        free(current);
        return;
    }
    if (current == NULL)
    {
        return;
    }

    while (current != NULL && current->id != id)
    {
        last = current;
        current = current->next;
    }

    last->next = current->next;

    free(current);
}

void getCardsinhand(Guardian *deck, player *inHand, int id, int isPlayer, int *id1, int *id2, int *id3)
{
    int randomIndex;
    int count = 0;
    if(isPlayer == 0)
    {
        for(int i = 0; i < 3; i++)
        {
            createCard2(&inHand->cardsinHand, &deck->id, deck->name, deck->type, &deck->HP, &deck->ATK, &deck->DEF);
            if(i == 0)
            {
                *id1 = deck->id;
            }
            if(i == 1)
            {
                *id2 = deck->id;
            }
            if(i == 2)
            {
                *id3 = deck->id;
            }
            deck = deck->next;

        }
    }
    else
    {
        while (deck != NULL)
        {
            if(deck->id == id)
            {
                createCard2(&inHand->cardsinHand, &deck->id, deck->name, deck->type, &deck->HP, &deck->ATK, &deck->DEF);
            }
            deck = deck->next;
        }
    }
}
void searchCardandAdd(player *p, int id)
{
    Guardian *current = p->cardsinHand;

    while (current != NULL)
    {
        if(current->id == id)
        {
            createCard2(&p->cardsinTable, &current->id, current->name, current->type, &current->HP, &current->ATK, &current->DEF);
            eraseCard(&p->cardsinHand, id);
        }
        current = current->next;
    }
}

void shuffleCards(Guardian **deck, player *p1, player *p2)
{
    int flag = 0;
    int i;
    int sizeL = getSize(*deck);
    Guardian *current = *deck;
    int randomIndex;
    int aux[sizeL];

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

    /*for(i = 0; i < sizeL; i++)
    {
        printf("%d.- %d\n",i, aux[i]);
    }*/

    for(i = 0; i < 15;i++)
    {
        createCard2(&p1->cards, &auxDeck[aux[i]]->id, auxDeck[aux[i]]->name, auxDeck[aux[i]]->type, &auxDeck[aux[i]]->HP, &auxDeck[aux[i]]->ATK, &auxDeck[aux[i]]->DEF);
    }
    for(i = 15; i < 30;i++)
    {
        createCard2(&p2->cards, &auxDeck[aux[i]]->id, auxDeck[aux[i]]->name, auxDeck[aux[i]]->type, &auxDeck[aux[i]]->HP, &auxDeck[aux[i]]->ATK, &auxDeck[aux[i]]->DEF);
    }
}
void drawCard(player *p)
{
    Guardian *current = p->cards;
    while(current->next != NULL)
    {
        current = current->next;
    }
    createCard2(&p->cardsinHand, &current->id, current->name, current->type, &current->HP, &current->ATK, &current->DEF);
    eraseCard(&p->cards, current->id);
}
int mostPowerful(player *p)
{
   int idMostPowerful;
   int force = 0;
   Guardian *current = p->cardsinHand;
   while(current != NULL)
   {
       if(force < current->ATK)
       {
           force = current->ATK;
           idMostPowerful = current->id;
       }
       current = current->next;
   }
    return idMostPowerful;
}
int mostPowerfulinTable(player *p)
{
    /*
            Se analiza una lista en busca de el guardian con más ataque
            y luego se retorna la identificacion del elemento de la lista.
    */
   int idMostPowerful;
   int force = 0;
   Guardian *current = p->cardsinTable;
   while(current != NULL)
   {
       if(force < current->ATK)
       {
           force = current->ATK;
           idMostPowerful = current->id;
       }
       current = current->next;
   }
    return idMostPowerful;
}
void printCards2(Guardian *deck)
{
    while (deck != NULL)
    {
        printf("%d.- %s %s %d %d %d\n", deck->id, deck->name, deck->type, deck->HP, deck->ATK, deck->DEF);
        deck = deck->next;
    }
}
Guardian *searchCard(Guardian *p, int id)
{
    Guardian *current = p;

    while (current != NULL)
    {
        if(current->id == id)
        {
            break;
        }
        current = current->next;
    }
    return current;
}
void damageCalculation(player *p1, player *p2, int id1, int id2)
{
    int result;
    Guardian *attacker = searchCard(p1->cardsinTable, id1);
    Guardian *attacked = searchCard(p2->cardsinTable, id2);
    result = (attacked->DEF) - (attacker->ATK);
    if(result <= 0)
    {
        // SE DESTRUYE
        eraseCard(&p2->cardsinTable, attacked->id);
        p2->lives--;
        printf("\nThe opponent's guardian has been defeated!");
        printf("\nPress any button to continue...");
        getchar();
        getchar();
    }
    else if(result > 0)
    {
        // NO SE DESTRUYE
        printf("\nThe attack was not effective");
        printf("\nPress any button to continue...");
        getchar();
        getchar();
    }

}
int leastPowerful(player *p)
{
   int idLeastPowerful = 0;
   int defense = 0;
   Guardian *current = p->cardsinTable;
   defense = current->DEF;
   idLeastPowerful = current->id;
   while(current != NULL)
   {
       if(defense > current->DEF)
       {
           defense = current->DEF;
           idLeastPowerful = current->id;
       }
       current = current->next;
   }
    return idLeastPowerful;
}

int main()
{
    srand(time(NULL));
    Guardian *deck = NULL;
    Guardian newCard;
    player p1, p2;
    p1.cards = NULL;
    p2.cards = NULL;
    p1.cardsinHand = NULL;
    p2.cardsinHand = NULL;
    p1.cardsinTable = NULL;
    p2.cardsinTable = NULL;
    strcpy(p2.name, "BOT");
    p1.lives = 5;
    p2.lives = 5;
    int cardChoice;
    int idChoices[3];
    int idchoice1, idchoice2, idchoice3;
    int gameChoice;
    int randomNum;

    char *nameTemp;
	char typeTemp;
	int HpTemp;
	int ATKTemp;
	int DEFTemp;
	int typechoice;
	int turn = 1;
	int cicle = 1;

    int choice;
    int HpMax=0;
    int HpMin=0;
    int ATKMax=0;
    int ATKMin=0;
    int DEFMax=0;
    int DEFMin=0;

    readFile(&deck,&HpMax,&HpMin,&ATKMax,&ATKMin,&DEFMax,&DEFMin);

    //printf("%d %d %d %d %d %d\n",HpMax,HpMin,ATKMax,ATKMin,DEFMax,DEFMin); // Impresion de los maximos y minimos de vida, ataque y defensa desde el archivo de texto
	while(choice != 3)
    {
		printf("\n--Clash of the Guardians--\n1.- Play\n2.- Create new card\n\n3.- Quit\n");
		scanf("%d", &choice);
		switch(choice)
		{
			case 1:
                shuffleCards(&deck, &p1, &p2);
			    system("cls");
				printf("Enter your name: ");
				gets(p1.name);
				gets(p1.name);
				printf("\nSelect your first three cards entering the ID:\n");
				printCards(p1.cards);
				printf("\nFirst card: ");
				scanf("%d", &cardChoice);
				getCardsinhand(p1.cards, &p1, cardChoice, 1, &idchoice1, &idchoice2, &idchoice3);
				idChoices[0] = cardChoice;
				printf("Second card: ");
				scanf("%d", &cardChoice);
				getCardsinhand(p1.cards, &p1, cardChoice, 1, &idchoice1, &idchoice2, &idchoice3);
				idChoices[1] = cardChoice;
				printf("Third card: ");
				scanf("%d", &cardChoice);
				getCardsinhand(p1.cards, &p1, cardChoice, 1, &idchoice1, &idchoice2, &idchoice3);
				idChoices[2] = cardChoice;
				eraseCard(&p1.cards, idChoices[0]);
				eraseCard(&p1.cards, idChoices[1]);
				eraseCard(&p1.cards, idChoices[2]);
				getCardsinhand(p2.cards, &p2, 1, 0, &idchoice1, &idchoice2, &idchoice3);
				eraseCard(&p2.cards, idchoice1);
				eraseCard(&p2.cards, idchoice2);
				eraseCard(&p2.cards, idchoice3);
				while(p1.lives > 0 && p2.lives > 0)
                {

                    if(turn == 1)   // TURNO DEL JUGADOR
                    {
                        system("cls");
                        drawCard(&p1);
                        printf("\n%s draw a card\n", p1.name);
                        printf("\nPress any button to continue...\n");
                        getchar();
                        getchar();
                        cicle = 1;
                        system("cls");
                        printf("\n%s's lives: %d", p1.name, p1.lives);
                        printf("\n%s's cards:\n", p1.name);
                        printCards(p1.cardsinHand);
                        printf("\n%s's cards in the table:\n", p1.name);
                        if(p1.cardsinTable == NULL)
                        {
                            printf("\nNO CARDS\n");
                        }
                        else
                        {
                            printCards2(p1.cardsinTable);
                        }
                        printf("\n%s's lives: %d", p2.name, p2.lives);
                        printf("\n%s's cards in the table:\n", p2.name);
                        if(p2.cardsinTable == NULL)
                        {
                            printf("\nNO CARDS\n");
                        }
                        else
                        {
                            printCards2(p2.cardsinTable);
                        }
                        while(cicle == 1)
                        {
                            printf("\nWhat do you want to do?\n");
                            printf("1. Summon a guardian\n");
                            printf("2. Attack\n");

                            scanf("%d", &gameChoice);
                            if(gameChoice == 2 && p1.cardsinTable == NULL)
                            {
                                printf("\nYou have no cards in the table, try again...\n");
                                getchar();
                                getchar();
                            }
                            else
                            {
                                switch(gameChoice)
                                {
                                    case 1:
                                        printf("Which guardian do you want to summon? Enter its id:");
                                        scanf("%d", &cardChoice);
                                        searchCardandAdd(&p1, cardChoice);
                                        cicle = 0;
                                        turn = 0;
                                        break;
                                    case 2:
                                        printf("Which guardian do you want to attack with? Enter its id:");
                                        scanf("%d", &cardChoice);
                                        printf("Which of the opponent's guardians do you want to attack into? Enter its id:");
                                        scanf("%d", &idchoice1);
                                        damageCalculation(&p1, &p2, cardChoice, idchoice1);
                                        if(p2.lives <= 0)
                                        {
                                            printf("Congratulations, %s is the winner!!!", p1.name);
                                            getchar();
                                            getchar();
                                        }
                                        cicle = 0;
                                        turn = 0;
                                        break;
                                }
                            }
                        }
                    }
                    else
                    {
                        system("cls");
                        drawCard(&p2);
                        cicle = 1;
                        while(cicle == 1)
                        {
                            randomNum = (rand()% 2)+1;
                            if(randomNum == 2 && p2.cardsinTable == NULL)
                            {
                                randomNum = 1;
                            }
                            if(randomNum == 2 && p1.cardsinTable == NULL)
                            {
                                randomNum = 1;
                            }
                            switch(randomNum)
                            {
                                case 1:
                                    printf("\n%s's turn\n", p2.name);
                                    cardChoice = mostPowerful(&p2);
                                    searchCardandAdd(&p2, cardChoice);
                                    cicle = 0;
                                    turn = 1;
                                    break;
                                case 2:
                                    printf("\n%s's turn\n", p2.name);
                                    idchoice2 = mostPowerfulinTable(&p2);
                                    idchoice3 = leastPowerful(&p1);
                                    damageCalculation(&p2, &p1, idchoice2, idchoice3);
                                    if(p1.lives <= 0)
                                    {
                                        printf("Congratulations, %s is the winner!!!", p2.name);
                                        getchar();
                                        getchar();
                                    }
                                    cicle = 0;
                                    turn = 1;
                                    break;
                            }
                        }
                    }

                }
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
		}
	}

	freeGuardians(deck);
	freeGuardians(p1.cards);
	freeGuardians(p1.cardsinHand);
	freeGuardians(p1.cardsinTable);
    freeGuardians(p2.cards);
	freeGuardians(p2.cardsinHand);
	freeGuardians(p2.cardsinTable);


    return 0;
}
