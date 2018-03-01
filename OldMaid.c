/*=============================================================================
 |   Assignment:  Final Project: Old Maid
 |       Author:  Jonathan Herron (jherron5225@email.arizona.edu)
 | Date Created:  4/12/17
 |
 |       Course:  ECE175 S2
 |   Instructor:  Ratchaneekorn Thamvichai
 |     Due Date:  4/26/17
 |
 |  Description:  This is a two-player card game using a standard deck of 53
 |                cards. Player 1 (the computer) is named Aida for personal
 |                flaire, and because its easier to keep track of player 1 vs
 |                player 2 if both have names. It is a reference to the 
 |                artificial intelligence from Agents of Shield. The game 
 |                consists of each player choosing cards from the other
 |                players hand and removing cards of the same faces until 
 |                only the joker card is left. The last player holding the 
 |                joker loses the game.
 |
 |     Language:  C
 *===========================================================================*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

typedef struct card_struct card;
void CreateDeck();
void appendCard(int, char, int);
void freeMem();
void printStartScreen();
void printDeck(int);

/*---------------------------------------------------------------------
 |  Struct: card
 |
 |  Purpose: This constructs a card. Each card has a suit, face and a
 |           pointer to the next card. Each also contains six strings
 |           that contain relevant display data for the card
 *-------------------------------------------------------------------*/
struct card_struct {
    char suit;
    char specChar[12];
    char bspecChar[12];
    char line3[20];
    char line4[20];
    char line5[20];
    char line6[20];
    int face;
    card *next;
};

/*---------------------------------------------------------------------
 |Global Variables
 *-------------------------------------------------------------------*/
card *head = NULL;     // Holds the position of the first card in the deck
card *p1Head = NULL;   // Holds the position of the first card in P1's deck
card *p2Head = NULL;   // Holds the position of the first card in P2'S deck
int p1Size = 0;        // Holds the size of P1's deck
int p2Size = 0;        // Holds the size of P2's deck
int exitFlag = 0;      // Code that is returned when the program terminates

/*---------------------------------------------------------------------
 |  Funtion: CreateDeck()
 |
 |  Purpose: Creates a deck of 53 cards with appropriate faces and suits.
 |
 |  Parameters:  None
 |
 |  Returns:  void
 *-------------------------------------------------------------------*/
void CreateDeck() {
    char suits[4]  = {'H', 'S', 'C', 'D'};
    int faces[13] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int i = 0, j = 0;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 13; j++) {
            appendCard(0, suits[i], faces[j]);
        }
    }
    appendCard(0, 'J', 0);
} // CreateDeck()

/*---------------------------------------------------------------------
 |  Funtion: addSpecialCharacters(int p)
 |
 |  Purpose: Adds the special characters and appropriate display data
 |           to each card.
 |
 |  Parameters:  int p
 |
 |  Returns:  void
 *-------------------------------------------------------------------*/
void addSpecialCharacters(int p) {
    char *H = "\u2665  ";
    char *S = "\u2660  ";
    char *C = "\u2663  ";
    char *D = "\u2666  ";
    char *BH = "\u2665";
    char *BS = "\u2660";
    char *BC = "\u2663";
    char *BD = "\u2666";
    char *J = "JOKER";
    card* ptr = NULL;
    ptr = head;
    if (p == 0) {
        ptr = head;
    }
    if (p == 1) {
        ptr = p1Head;
    }
    if (p == 2) {
        ptr = p2Head;
    }
    while (ptr != NULL) {
        if (ptr->face == 0) {
            strcpy(ptr->specChar, "");
            strcpy(ptr->bspecChar, "");
        }
        else if (ptr->face == 1) {
            strcpy(ptr->specChar, "A ");
            strcpy(ptr->bspecChar, "  A ");
        }
        else if (ptr->face == 2) {
            strcpy(ptr->specChar, "2 ");
            strcpy(ptr->bspecChar, "  2 ");
        }
        else if (ptr->face == 3) {
            strcpy(ptr->specChar, "3 ");
            strcpy(ptr->bspecChar, "  3 ");
        }
        else if (ptr->face == 4) {
            strcpy(ptr->specChar, "4 ");
            strcpy(ptr->bspecChar, "  4 ");
        }
        else if (ptr->face == 5) {
            strcpy(ptr->specChar, "5 ");
            strcpy(ptr->bspecChar, "  5 ");
        }
        else if (ptr->face == 6) {
            strcpy(ptr->specChar, "6 ");
            strcpy(ptr->bspecChar, "  6 ");
        }
        else if (ptr->face == 7) {
            strcpy(ptr->specChar, "7 ");
            strcpy(ptr->bspecChar, "  7 ");
        }
        else if (ptr->face == 8) {
            strcpy(ptr->specChar, "8 ");
            strcpy(ptr->bspecChar, "  8 ");
        }
        else if (ptr->face == 9) {
            strcpy(ptr->specChar, "9 ");
            strcpy(ptr->bspecChar, "  9 ");
        }
        else if (ptr->face == 10) {
            strcpy(ptr->specChar, "10");
            strcpy(ptr->bspecChar, "  10");
        }
        else if (ptr->face == 11) {
            strcpy(ptr->specChar, "J ");
            strcpy(ptr->bspecChar, "  J ");
        }
        else if (ptr->face == 12) {
            strcpy(ptr->specChar, "Q ");
            strcpy(ptr->bspecChar, "  Q ");
        }
        else {
            strcpy(ptr->specChar, "K ");
            strcpy(ptr->bspecChar, "  K ");
        }
        ptr = ptr->next;
    }
    if (p == 0) {
        ptr = head;
    }
    if (p == 1) {
        ptr = p1Head;
    }
    if (p == 2) {
        ptr = p2Head;
    }
    while (ptr != NULL) {
        if (ptr->suit == 'H') {
            strcat(ptr->specChar, H);
            strcat(ptr->bspecChar, BH);
            strcpy(ptr->line3, "│  __ __  │");
            strcpy(ptr->line4, "│ (  V  ) │");
            strcpy(ptr->line5, "│  \\   /  │");
            strcpy(ptr->line6, "│    V    │");
        }
        else if (ptr->suit == 'S') {
            strcat(ptr->specChar, S);
            strcat(ptr->bspecChar, BS);
            strcpy(ptr->line3, "│    .    │");
            strcpy(ptr->line4, "│   / \\   │");
            strcpy(ptr->line5, "│  (_,_)  │");
            strcpy(ptr->line6, "│    I    │");
        }
        else if (ptr->suit == 'C') {
            strcat(ptr->specChar, C);
            strcat(ptr->bspecChar, BC);
            strcpy(ptr->line3, "│    _    │");
            strcpy(ptr->line4, "│   ( )   │");
            strcpy(ptr->line5, "│  (_x_)  │");
            strcpy(ptr->line6, "│    Y    │");
        }
        else if (ptr->suit == 'D'){
            strcat(ptr->specChar, D);
            strcat(ptr->bspecChar, BD);
            strcpy(ptr->line3, "│   /\\    │");
            strcpy(ptr->line4, "│  /  \\   │");
            strcpy(ptr->line5, "│  \\  /   │");
            strcpy(ptr->line6, "│   \\/    │");
        }
        else {
            strcat(ptr->specChar, J);
            strcat(ptr->bspecChar, J);
            strcpy(ptr->line3, "│  \\|||/  │");
            strcpy(ptr->line4, "│  (o o)  │");
            strcpy(ptr->line5, "│  | ! |  │");
            strcpy(ptr->line6, "│   \\v/   │");
        }
        ptr = ptr->next;
    }
} // addSpecialCharacters()

/*---------------------------------------------------------------------
 |  Funtion: appendCard(int p, char suit, int face)
 |
 |  Purpose: Adds a card with the suit and face from the parameter
 |           to end end of a chosen deck.
 |
 |  Parameters:  int p
 |               char suit
 |               int face
 |
 |  Returns:  void
 *-------------------------------------------------------------------*/
void appendCard(int p, char suit, int face) {
    card *newCard = (card *)malloc(sizeof(card));
    card *curr = NULL;
    if (p == 0) {
        curr = head;
    }
    if (p == 1) {
        curr = p1Head;
        p1Size++;
    }
    if (p == 2) {
        curr = p2Head;
        p2Size++;
    }
    if (newCard == NULL) {
        fprintf(stderr,"ERROR Out of memory\n");
        freeMem();
        exit(1);
    }
    newCard->face = face;
    newCard->suit = suit;
    
    if (head == NULL && p == 0) {
        head = newCard;
        head->next = NULL;
        return;
    }
    if (p1Head == NULL && p == 1) {
        p1Head = newCard;
        p1Head->next = NULL;
        return;
    }
    if (p2Head == NULL && p == 2) {
        p2Head = newCard;
        p2Head->next = NULL;
        return;
    }
    else {
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = newCard;
        newCard->next = NULL;
    }
} // appendCard()

/*---------------------------------------------------------------------
 |  Funtion: freemem()
 |
 |  Purpose: Frees all memory taken up by the decks.
 |
 |  Parameters:  None.
 |
 |  Returns:  void
 *-------------------------------------------------------------------*/
void freeMem() {
    card *ptr, *ptr2;
    
    ptr = head;
    while (ptr != NULL) {
        ptr2 = ptr->next;
        if (ptr == NULL)
            break;
        free(ptr);
        ptr = ptr2;
    }
    
    ptr = p1Head;
    while (ptr != NULL) {
        ptr2 = ptr->next;
        if (ptr == NULL)
            break;
        free(ptr);
        ptr = ptr2;
    }
    
    ptr = p2Head;
    while (ptr != NULL) {
        ptr2 = ptr->next;
        if (ptr == NULL)
            break;
        free(ptr);
        ptr = ptr2;
    }
    return;
} // freemem()

/*---------------------------------------------------------------------
 |  Funtion: printStartScreen()
 |
 |  Purpose: Prints a fancy start screen for the game/
 |
 |  Parameters:  None.
 |
 |  Returns:  void
 *-------------------------------------------------------------------*/
void printStartScreen() {
    printf(" .----------------.  .----------------.  .----------------.  .----------------.   .----------------.  .----------------.  .----------------.  .----------------.  .----------------. \n");
    printf("| .--------------. || .--------------. || .--------------. || .--------------. | | .--------------. || .--------------. || .--------------. || .--------------. || .--------------. |\n");
    printf("| |              | || |     ____     | || |   _____      | || |  ________    | | | | ____    ____ | || |      __      | || |     _____    | || |  ________    | || |              | |\n");
    printf("| |    ___.-.    | || |   .'    `.   | || |  |_   _|     | || | |_   ___ `.  | | | ||_   \\  /   _|| || |     /  \\     | || |    |_   _|   | || | |_   ___ `.  | || |    ___.-.    | |\n");
    printf("| |   |  ___|    | || |  /  .--.  \\  | || |    | |       | || |   | |   `. \\ | | | |  |   \\/   |  | || |    / /\\ \\    | || |      | |     | || |   | |   `. \\ | || |   |  ___|    | |\n");
    printf("| |   '-'        | || |  | |    | |  | || |    | |   _   | || |   | |    | | | | | |  | |\\  /| |  | || |   / ____ \\   | || |      | |     | || |   | |    | | | || |   '-'        | |\n");
    printf("| |              | || |  \\  `--'  /  | || |   _| |__/ |  | || |  _| |___.' / | | | | _| |_\\/_| |_ | || | _/ /    \\ \\_ | || |     _| |_    | || |  _| |___.' / | || |              | |\n");
    printf("| |              | || |   `.____.'   | || |  |________|  | || | |________.'  | | | ||_____||_____|| || ||____|  |____|| || |    |_____|   | || | |________.'  | || |              | |\n");
    printf("| |              | || |              | || |              | || |              | | | |              | || |              | || |              | || |              | || |              | |\n");
    printf("| '--------------' || '--------------' || '--------------' || '--------------' | | '--------------' || '--------------' || '--------------' || '--------------' || '--------------' |\n");
    printf(" '----------------'  '----------------'  '----------------'  '----------------'   '----------------'  '----------------'  '----------------'  '----------------'  '----------------' \n");
    printf("            .----------------.  .----------------.  .----------------.  .----------------.   .----------------.  .----------------.  .----------------.  .----------------.          \n");
    printf("           | .--------------. || .--------------. || .--------------. || .--------------. | | .--------------. || .--------------. || .--------------. || .--------------. |         \n");
    printf("           | |     ______   | || |      __      | || |  _______     | || |  ________    | | | |    ______    | || |      __      | || | ____    ____ | || |  _________   | |         \n");
    printf("           | |   .' ___  |  | || |     /  \\     | || | |_   __ \\    | || | |_   ___ `.  | | | |  .' ___  |   | || |     /  \\     | || ||_   \\  /   _|| || | |_   ___  |  | |         \n");
    printf("           | |  / .'   \\_|  | || |    / /\\ \\    | || |   | |__) |   | || |   | |   `. \\ | | | | / .'   \\_|   | || |    / /\\ \\    | || |  |   \\/   |  | || |   | |_  \\_|  | |         \n");
    printf("           | |  | |         | || |   / ____ \\   | || |   |  __ /    | || |   | |    | | | | | | | |    ____  | || |   / ____ \\   | || |  | |\\  /| |  | || |   |  _|  _   | |         \n");
    printf("           | |  \\ `.___.'\\  | || | _/ /    \\ \\_ | || |  _| |  \\ \\_  | || |  _| |___.' / | | | | \\ `.___]  _| | || | _/ /    \\ \\_ | || | _| |_\\/_| |_ | || |  _| |___/ |  | |         \n");
    printf("           | |   `._____.'  | || ||____|  |____|| || | |____| |___| | || | |________.'  | | | |  `._____.'   | || ||____|  |____|| || ||_____||_____|| || | |_________|  | |         \n");
    printf("           | |              | || |              | || |              | || |              | | | |              | || |              | || |              | || |              | |         \n");
    printf("           | '--------------' || '--------------' || '--------------' || '--------------' | | '--------------' || '--------------' || '--------------' || '--------------' |         \n");
    printf("            '----------------'  '----------------'  '----------------'  '----------------'   '----------------'  '----------------'  '----------------'  '----------------'          \n");
    printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t          %%%%%%%%%%%%\n");
    printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t          %%%%%%\\__/%%\n");
    printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t          %%%%%%%%\"\"\"%%\n");
    printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t          %%%%c ^\\^%%\n");
    printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t           %%\\ _=/                .\n");
    printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t           _.'_(               .::\n");
    printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t       .'`\\     `._    _   _..;:::'\n");
    printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t      /    '._  .' \\ =/ (=(:]::;:::.\n");
    printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t      \\__./__.``_/_/ / /     ';::;:.\n");
    printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t      / / )    / \\ \\/ /        '::.\n");
    printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t     / /.'`-._(   \\  /          '.\n");
    printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t    / /'      `\\   ``\n");
    printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t   /.(          \\ \n");
    printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t   \\_(`\";-..___  \\ \n");
    printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t        |=*==||```\n");
    printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t         \\   ||\n");
    printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t          \\  ||\n");
    printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t           ) ))\n");
    printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t          /  ||\n");
    printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t          \\  ||\n");
    printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t           )_||\n");
    printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t          (  \\\\\\\n");
    printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t           Y\\__\\\\\n");
    printf("\n");
} // printStartScreen()

/*---------------------------------------------------------------------
 |  Funtion: printCard(card *ptr, int num)
 |
 |  Purpose: Prints up to 15 cards starting from the card ptr in the 
 |           parameter up to num.
 |
 |  Parameters:  card *ptr
 |               int num
 |
 |  Returns:  void
 *-------------------------------------------------------------------*/
void printCard(card *ptr, int num) {
    if (num == 15) {
        printf("┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\n");
        printf("│%s    │\t│%s    │\t│%s    │\t│%s    │\t│%s    │\t│%s    │\t│%s    │\t│%s    │\t│%s    │\t│%s    │\t│%s    │\t│%s    │\t│%s    │\t│%s    │\t│%s    │\n", ptr->specChar, ptr->next->specChar, ptr->next->next->specChar, ptr->next->next->next->specChar, ptr->next->next->next->next->specChar, ptr->next->next->next->next->next->specChar, ptr->next->next->next->next->next->next->specChar, ptr->next->next->next->next->next->next->next->specChar, ptr->next->next->next->next->next->next->next->next->specChar, ptr->next->next->next->next->next->next->next->next->next->specChar, ptr->next->next->next->next->next->next->next->next->next->next->specChar, ptr->next->next->next->next->next->next->next->next->next->next->next->specChar, ptr->next->next->next->next->next->next->next->next->next->next->next->next->specChar,  ptr->next->next->next->next->next->next->next->next->next->next->next->next->next->specChar, ptr->next->next->next->next->next->next->next->next->next->next->next->next->next->next->specChar);
        printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", ptr->line3, ptr->next->line3, ptr->next->next->line3, ptr->next->next->next->line3, ptr->next->next->next->next->line3, ptr->next->next->next->next->next->line3, ptr->next->next->next->next->next->next->line3, ptr->next->next->next->next->next->next->next->line3, ptr->next->next->next->next->next->next->next->next->line3, ptr->next->next->next->next->next->next->next->next->next->line3, ptr->next->next->next->next->next->next->next->next->next->next->line3, ptr->next->next->next->next->next->next->next->next->next->next->next->line3, ptr->next->next->next->next->next->next->next->next->next->next->next->next->line3, ptr->next->next->next->next->next->next->next->next->next->next->next->next->next->line3, ptr->next->next->next->next->next->next->next->next->next->next->next->next->next->next->line3);
        printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", ptr->line4, ptr->next->line4, ptr->next->next->line4, ptr->next->next->next->line4, ptr->next->next->next->next->line4, ptr->next->next->next->next->next->line4, ptr->next->next->next->next->next->next->line4, ptr->next->next->next->next->next->next->next->line4, ptr->next->next->next->next->next->next->next->next->line4, ptr->next->next->next->next->next->next->next->next->next->line4, ptr->next->next->next->next->next->next->next->next->next->next->line4, ptr->next->next->next->next->next->next->next->next->next->next->next->line4, ptr->next->next->next->next->next->next->next->next->next->next->next->next->line4, ptr->next->next->next->next->next->next->next->next->next->next->next->next->next->line4, ptr->next->next->next->next->next->next->next->next->next->next->next->next->next->next->line4);
        printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", ptr->line5, ptr->next->line5, ptr->next->next->line5, ptr->next->next->next->line5, ptr->next->next->next->next->line5, ptr->next->next->next->next->next->line5, ptr->next->next->next->next->next->next->line5, ptr->next->next->next->next->next->next->next->line5, ptr->next->next->next->next->next->next->next->next->line5, ptr->next->next->next->next->next->next->next->next->next->line5, ptr->next->next->next->next->next->next->next->next->next->next->line5, ptr->next->next->next->next->next->next->next->next->next->next->next->line5, ptr->next->next->next->next->next->next->next->next->next->next->next->next->line5, ptr->next->next->next->next->next->next->next->next->next->next->next->next->next->line5, ptr->next->next->next->next->next->next->next->next->next->next->next->next->next->next->line5);
        printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", ptr->line6, ptr->next->line6, ptr->next->next->line6, ptr->next->next->next->line6, ptr->next->next->next->next->line6, ptr->next->next->next->next->next->line6, ptr->next->next->next->next->next->next->line6, ptr->next->next->next->next->next->next->next->line6, ptr->next->next->next->next->next->next->next->next->line6, ptr->next->next->next->next->next->next->next->next->next->line6, ptr->next->next->next->next->next->next->next->next->next->next->line6, ptr->next->next->next->next->next->next->next->next->next->next->next->line6, ptr->next->next->next->next->next->next->next->next->next->next->next->next->line6, ptr->next->next->next->next->next->next->next->next->next->next->next->next->next->line6, ptr->next->next->next->next->next->next->next->next->next->next->next->next->next->next->line6);
        printf("│         │\t│         │\t│         │\t│         │\t│         │\t│         │\t│         │\t│         │\t│         │\t│         │\t│         │\t│         │\t│         │\t│         │\t│         │\n");
        printf("│    %s│\t│    %s│\t│    %s│\t│    %s│\t│    %s│\t│    %s│\t│    %s│\t│    %s│\t│    %s│\t│    %s│\t│    %s│\t│    %s│\t│    %s│\t│    %s│\t│    %s│\n", ptr->bspecChar, ptr->next->bspecChar, ptr->next->next->bspecChar, ptr->next->next->next->bspecChar, ptr->next->next->next->next->bspecChar, ptr->next->next->next->next->next->bspecChar, ptr->next->next->next->next->next->next->bspecChar, ptr->next->next->next->next->next->next->next->bspecChar, ptr->next->next->next->next->next->next->next->next->bspecChar, ptr->next->next->next->next->next->next->next->next->next->bspecChar, ptr->next->next->next->next->next->next->next->next->next->next->bspecChar, ptr->next->next->next->next->next->next->next->next->next->next->next->bspecChar, ptr->next->next->next->next->next->next->next->next->next->next->next->next->bspecChar, ptr->next->next->next->next->next->next->next->next->next->next->next->next->next->bspecChar, ptr->next->next->next->next->next->next->next->next->next->next->next->next->next->next->bspecChar);
        printf("└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\n");
    }
    if (num == 14) {
        printf("┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\n");
        printf("│%s    │\t│%s    │\t│%s    │\t│%s    │\t│%s    │\t│%s    │\t│%s    │\t│%s    │\t│%s    │\t│%s    │\t│%s    │\t│%s    │\t│%s    │\t│%s    │\n", ptr->specChar, ptr->next->specChar, ptr->next->next->specChar, ptr->next->next->next->specChar, ptr->next->next->next->next->specChar, ptr->next->next->next->next->next->specChar, ptr->next->next->next->next->next->next->specChar, ptr->next->next->next->next->next->next->next->specChar, ptr->next->next->next->next->next->next->next->next->specChar, ptr->next->next->next->next->next->next->next->next->next->specChar, ptr->next->next->next->next->next->next->next->next->next->next->specChar, ptr->next->next->next->next->next->next->next->next->next->next->next->specChar, ptr->next->next->next->next->next->next->next->next->next->next->next->next->specChar, ptr->next->next->next->next->next->next->next->next->next->next->next->next->next->specChar);
        printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", ptr->line3, ptr->next->line3, ptr->next->next->line3, ptr->next->next->next->line3, ptr->next->next->next->next->line3, ptr->next->next->next->next->next->line3, ptr->next->next->next->next->next->next->line3, ptr->next->next->next->next->next->next->next->line3, ptr->next->next->next->next->next->next->next->next->line3, ptr->next->next->next->next->next->next->next->next->next->line3, ptr->next->next->next->next->next->next->next->next->next->next->line3, ptr->next->next->next->next->next->next->next->next->next->next->next->line3, ptr->next->next->next->next->next->next->next->next->next->next->next->next->line3, ptr->next->next->next->next->next->next->next->next->next->next->next->next->next->line3);
        printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", ptr->line4, ptr->next->line4, ptr->next->next->line4, ptr->next->next->next->line4, ptr->next->next->next->next->line4, ptr->next->next->next->next->next->line4, ptr->next->next->next->next->next->next->line4, ptr->next->next->next->next->next->next->next->line4, ptr->next->next->next->next->next->next->next->next->line4, ptr->next->next->next->next->next->next->next->next->next->line4, ptr->next->next->next->next->next->next->next->next->next->next->line4, ptr->next->next->next->next->next->next->next->next->next->next->next->line4, ptr->next->next->next->next->next->next->next->next->next->next->next->next->line4, ptr->next->next->next->next->next->next->next->next->next->next->next->next->next->line4);
        printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", ptr->line5, ptr->next->line5, ptr->next->next->line5, ptr->next->next->next->line5, ptr->next->next->next->next->line5, ptr->next->next->next->next->next->line5, ptr->next->next->next->next->next->next->line5, ptr->next->next->next->next->next->next->next->line5, ptr->next->next->next->next->next->next->next->next->line5, ptr->next->next->next->next->next->next->next->next->next->line5, ptr->next->next->next->next->next->next->next->next->next->next->line5, ptr->next->next->next->next->next->next->next->next->next->next->next->line5, ptr->next->next->next->next->next->next->next->next->next->next->next->next->line5, ptr->next->next->next->next->next->next->next->next->next->next->next->next->next->line5);
        printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", ptr->line6, ptr->next->line6, ptr->next->next->line6, ptr->next->next->next->line6, ptr->next->next->next->next->line6, ptr->next->next->next->next->next->line6, ptr->next->next->next->next->next->next->line6, ptr->next->next->next->next->next->next->next->line6, ptr->next->next->next->next->next->next->next->next->line6, ptr->next->next->next->next->next->next->next->next->next->line6, ptr->next->next->next->next->next->next->next->next->next->next->line6, ptr->next->next->next->next->next->next->next->next->next->next->next->line6, ptr->next->next->next->next->next->next->next->next->next->next->next->next->line6, ptr->next->next->next->next->next->next->next->next->next->next->next->next->next->line6);
        printf("│         │\t│         │\t│         │\t│         │\t│         │\t│         │\t│         │\t│         │\t│         │\t│         │\t│         │\t│         │\t│         │\t│         │\n");
        printf("│    %s│\t│    %s│\t│    %s│\t│    %s│\t│    %s│\t│    %s│\t│    %s│\t│    %s│\t│    %s│\t│    %s│\t│    %s│\t│    %s│\t│    %s│\t│    %s│\n", ptr->bspecChar, ptr->next->bspecChar, ptr->next->next->bspecChar, ptr->next->next->next->bspecChar, ptr->next->next->next->next->bspecChar, ptr->next->next->next->next->next->bspecChar, ptr->next->next->next->next->next->next->bspecChar, ptr->next->next->next->next->next->next->next->bspecChar, ptr->next->next->next->next->next->next->next->next->bspecChar, ptr->next->next->next->next->next->next->next->next->next->bspecChar, ptr->next->next->next->next->next->next->next->next->next->next->bspecChar, ptr->next->next->next->next->next->next->next->next->next->next->next->bspecChar, ptr->next->next->next->next->next->next->next->next->next->next->next->next->bspecChar, ptr->next->next->next->next->next->next->next->next->next->next->next->next->next->bspecChar);
        printf("└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\n");
    }
    if (num == 13) {
        printf("┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\n");
        printf("│%s    │\t│%s    │\t│%s    │\t│%s    │\t│%s    │\t│%s    │\t│%s    │\t│%s    │\t│%s    │\t│%s    │\t│%s    │\t│%s    │\t│%s    │\n", ptr->specChar, ptr->next->specChar, ptr->next->next->specChar, ptr->next->next->next->specChar, ptr->next->next->next->next->specChar, ptr->next->next->next->next->next->specChar, ptr->next->next->next->next->next->next->specChar, ptr->next->next->next->next->next->next->next->specChar, ptr->next->next->next->next->next->next->next->next->specChar, ptr->next->next->next->next->next->next->next->next->next->specChar, ptr->next->next->next->next->next->next->next->next->next->next->specChar, ptr->next->next->next->next->next->next->next->next->next->next->next->specChar, ptr->next->next->next->next->next->next->next->next->next->next->next->next->specChar);
        printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", ptr->line3, ptr->next->line3, ptr->next->next->line3, ptr->next->next->next->line3, ptr->next->next->next->next->line3, ptr->next->next->next->next->next->line3, ptr->next->next->next->next->next->next->line3, ptr->next->next->next->next->next->next->next->line3, ptr->next->next->next->next->next->next->next->next->line3, ptr->next->next->next->next->next->next->next->next->next->line3, ptr->next->next->next->next->next->next->next->next->next->next->line3, ptr->next->next->next->next->next->next->next->next->next->next->next->line3, ptr->next->next->next->next->next->next->next->next->next->next->next->next->line3);
        printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", ptr->line4, ptr->next->line4, ptr->next->next->line4, ptr->next->next->next->line4, ptr->next->next->next->next->line4, ptr->next->next->next->next->next->line4, ptr->next->next->next->next->next->next->line4, ptr->next->next->next->next->next->next->next->line4, ptr->next->next->next->next->next->next->next->next->line4, ptr->next->next->next->next->next->next->next->next->next->line4, ptr->next->next->next->next->next->next->next->next->next->next->line4, ptr->next->next->next->next->next->next->next->next->next->next->next->line4, ptr->next->next->next->next->next->next->next->next->next->next->next->next->line4);
        printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", ptr->line5, ptr->next->line5, ptr->next->next->line5, ptr->next->next->next->line5, ptr->next->next->next->next->line5, ptr->next->next->next->next->next->line5, ptr->next->next->next->next->next->next->line5, ptr->next->next->next->next->next->next->next->line5, ptr->next->next->next->next->next->next->next->next->line5, ptr->next->next->next->next->next->next->next->next->next->line5, ptr->next->next->next->next->next->next->next->next->next->next->line5, ptr->next->next->next->next->next->next->next->next->next->next->next->line5, ptr->next->next->next->next->next->next->next->next->next->next->next->next->line5);
        printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", ptr->line6, ptr->next->line6, ptr->next->next->line6, ptr->next->next->next->line6, ptr->next->next->next->next->line6, ptr->next->next->next->next->next->line6, ptr->next->next->next->next->next->next->line6, ptr->next->next->next->next->next->next->next->line6, ptr->next->next->next->next->next->next->next->next->line6, ptr->next->next->next->next->next->next->next->next->next->line6, ptr->next->next->next->next->next->next->next->next->next->next->line6, ptr->next->next->next->next->next->next->next->next->next->next->next->line6, ptr->next->next->next->next->next->next->next->next->next->next->next->next->line6);
        printf("│         │\t│         │\t│         │\t│         │\t│         │\t│         │\t│         │\t│         │\t│         │\t│         │\t│         │\t│         │\t│         │\n");
        printf("│    %s│\t│    %s│\t│    %s│\t│    %s│\t│    %s│\t│    %s│\t│    %s│\t│    %s│\t│    %s│\t│    %s│\t│    %s│\t│    %s│\t│    %s│\n", ptr->bspecChar, ptr->next->bspecChar, ptr->next->next->bspecChar, ptr->next->next->next->bspecChar, ptr->next->next->next->next->bspecChar, ptr->next->next->next->next->next->bspecChar, ptr->next->next->next->next->next->next->bspecChar, ptr->next->next->next->next->next->next->next->bspecChar, ptr->next->next->next->next->next->next->next->next->bspecChar, ptr->next->next->next->next->next->next->next->next->next->bspecChar, ptr->next->next->next->next->next->next->next->next->next->next->bspecChar, ptr->next->next->next->next->next->next->next->next->next->next->next->bspecChar, ptr->next->next->next->next->next->next->next->next->next->next->next->next->bspecChar);
        printf("└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\n");
    }
    if (num == 12) {
        printf("┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\n");
        printf("│%s    │\t│%s    │\t│%s    │\t│%s    │\t│%s    │\t│%s    │\t│%s    │\t│%s    │\t│%s    │\t│%s    │\t│%s    │\t│%s    │\n", ptr->specChar, ptr->next->specChar, ptr->next->next->specChar, ptr->next->next->next->specChar, ptr->next->next->next->next->specChar, ptr->next->next->next->next->next->specChar, ptr->next->next->next->next->next->next->specChar, ptr->next->next->next->next->next->next->next->specChar, ptr->next->next->next->next->next->next->next->next->specChar, ptr->next->next->next->next->next->next->next->next->next->specChar, ptr->next->next->next->next->next->next->next->next->next->next->specChar, ptr->next->next->next->next->next->next->next->next->next->next->next->specChar);
        printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", ptr->line3, ptr->next->line3, ptr->next->next->line3, ptr->next->next->next->line3, ptr->next->next->next->next->line3, ptr->next->next->next->next->next->line3, ptr->next->next->next->next->next->next->line3, ptr->next->next->next->next->next->next->next->line3, ptr->next->next->next->next->next->next->next->next->line3, ptr->next->next->next->next->next->next->next->next->next->line3, ptr->next->next->next->next->next->next->next->next->next->next->line3, ptr->next->next->next->next->next->next->next->next->next->next->next->line3);
        printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", ptr->line4, ptr->next->line4, ptr->next->next->line4, ptr->next->next->next->line4, ptr->next->next->next->next->line4, ptr->next->next->next->next->next->line4, ptr->next->next->next->next->next->next->line4, ptr->next->next->next->next->next->next->next->line4, ptr->next->next->next->next->next->next->next->next->line4, ptr->next->next->next->next->next->next->next->next->next->line4, ptr->next->next->next->next->next->next->next->next->next->next->line4, ptr->next->next->next->next->next->next->next->next->next->next->next->line4);
        printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", ptr->line5, ptr->next->line5, ptr->next->next->line5, ptr->next->next->next->line5, ptr->next->next->next->next->line5, ptr->next->next->next->next->next->line5, ptr->next->next->next->next->next->next->line5, ptr->next->next->next->next->next->next->next->line5, ptr->next->next->next->next->next->next->next->next->line5, ptr->next->next->next->next->next->next->next->next->next->line5, ptr->next->next->next->next->next->next->next->next->next->next->line5, ptr->next->next->next->next->next->next->next->next->next->next->next->line5);
        printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", ptr->line6, ptr->next->line6, ptr->next->next->line6, ptr->next->next->next->line6, ptr->next->next->next->next->line6, ptr->next->next->next->next->next->line6, ptr->next->next->next->next->next->next->line6, ptr->next->next->next->next->next->next->next->line6, ptr->next->next->next->next->next->next->next->next->line6, ptr->next->next->next->next->next->next->next->next->next->line6, ptr->next->next->next->next->next->next->next->next->next->next->line6, ptr->next->next->next->next->next->next->next->next->next->next->next->line6);
        printf("│         │\t│         │\t│         │\t│         │\t│         │\t│         │\t│         │\t│         │\t│         │\t│         │\t│         │\t│         │\n");
        printf("│    %s│\t│    %s│\t│    %s│\t│    %s│\t│    %s│\t│    %s│\t│    %s│\t│    %s│\t│    %s│\t│    %s│\t│    %s│\t│    %s│\n", ptr->bspecChar, ptr->next->bspecChar, ptr->next->next->bspecChar, ptr->next->next->next->bspecChar, ptr->next->next->next->next->bspecChar, ptr->next->next->next->next->next->bspecChar, ptr->next->next->next->next->next->next->bspecChar, ptr->next->next->next->next->next->next->next->bspecChar, ptr->next->next->next->next->next->next->next->next->bspecChar, ptr->next->next->next->next->next->next->next->next->next->bspecChar, ptr->next->next->next->next->next->next->next->next->next->next->bspecChar, ptr->next->next->next->next->next->next->next->next->next->next->next->bspecChar);
        printf("└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\n");
    }
    if (num == 11) {
        printf("┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\n");
        printf("│%s    │\t│%s    │\t│%s    │\t│%s    │\t│%s    │\t│%s    │\t│%s    │\t│%s    │\t│%s    │\t│%s    │\t│%s    │\n", ptr->specChar, ptr->next->specChar, ptr->next->next->specChar, ptr->next->next->next->specChar, ptr->next->next->next->next->specChar, ptr->next->next->next->next->next->specChar, ptr->next->next->next->next->next->next->specChar, ptr->next->next->next->next->next->next->next->specChar, ptr->next->next->next->next->next->next->next->next->specChar, ptr->next->next->next->next->next->next->next->next->next->specChar, ptr->next->next->next->next->next->next->next->next->next->next->specChar);
        printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", ptr->line3, ptr->next->line3, ptr->next->next->line3, ptr->next->next->next->line3, ptr->next->next->next->next->line3, ptr->next->next->next->next->next->line3, ptr->next->next->next->next->next->next->line3, ptr->next->next->next->next->next->next->next->line3, ptr->next->next->next->next->next->next->next->next->line3, ptr->next->next->next->next->next->next->next->next->next->line3, ptr->next->next->next->next->next->next->next->next->next->next->line3);
        printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", ptr->line4, ptr->next->line4, ptr->next->next->line4, ptr->next->next->next->line4, ptr->next->next->next->next->line4, ptr->next->next->next->next->next->line4, ptr->next->next->next->next->next->next->line4, ptr->next->next->next->next->next->next->next->line4, ptr->next->next->next->next->next->next->next->next->line4, ptr->next->next->next->next->next->next->next->next->next->line4, ptr->next->next->next->next->next->next->next->next->next->next->line4);
        printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", ptr->line5, ptr->next->line5, ptr->next->next->line5, ptr->next->next->next->line5, ptr->next->next->next->next->line5, ptr->next->next->next->next->next->line5, ptr->next->next->next->next->next->next->line5, ptr->next->next->next->next->next->next->next->line5, ptr->next->next->next->next->next->next->next->next->line5, ptr->next->next->next->next->next->next->next->next->next->line5, ptr->next->next->next->next->next->next->next->next->next->next->line5);
        printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", ptr->line6, ptr->next->line6, ptr->next->next->line6, ptr->next->next->next->line6, ptr->next->next->next->next->line6, ptr->next->next->next->next->next->line6, ptr->next->next->next->next->next->next->line6, ptr->next->next->next->next->next->next->next->line6, ptr->next->next->next->next->next->next->next->next->line6, ptr->next->next->next->next->next->next->next->next->next->line6, ptr->next->next->next->next->next->next->next->next->next->next->line6);
        printf("│         │\t│         │\t│         │\t│         │\t│         │\t│         │\t│         │\t│         │\t│         │\t│         │\t│         │\n");
        printf("│    %s│\t│    %s│\t│    %s│\t│    %s│\t│    %s│\t│    %s│\t│    %s│\t│    %s│\t│    %s│\t│    %s│\t│    %s│\n", ptr->bspecChar, ptr->next->bspecChar, ptr->next->next->bspecChar, ptr->next->next->next->bspecChar, ptr->next->next->next->next->bspecChar, ptr->next->next->next->next->next->bspecChar, ptr->next->next->next->next->next->next->bspecChar, ptr->next->next->next->next->next->next->next->bspecChar, ptr->next->next->next->next->next->next->next->next->bspecChar, ptr->next->next->next->next->next->next->next->next->next->bspecChar, ptr->next->next->next->next->next->next->next->next->next->next->bspecChar);
        printf("└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\n");
    }
    if (num == 10) {
        printf("┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\n");
        printf("│%s    │\t│%s    │\t│%s    │\t│%s    │\t│%s    │\t│%s    │\t│%s    │\t│%s    │\t│%s    │\t│%s    │\n", ptr->specChar, ptr->next->specChar, ptr->next->next->specChar, ptr->next->next->next->specChar, ptr->next->next->next->next->specChar, ptr->next->next->next->next->next->specChar, ptr->next->next->next->next->next->next->specChar, ptr->next->next->next->next->next->next->next->specChar, ptr->next->next->next->next->next->next->next->next->specChar, ptr->next->next->next->next->next->next->next->next->next->specChar);
        printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", ptr->line3, ptr->next->line3, ptr->next->next->line3, ptr->next->next->next->line3, ptr->next->next->next->next->line3, ptr->next->next->next->next->next->line3, ptr->next->next->next->next->next->next->line3, ptr->next->next->next->next->next->next->next->line3, ptr->next->next->next->next->next->next->next->next->line3, ptr->next->next->next->next->next->next->next->next->next->line3);
        printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", ptr->line4, ptr->next->line4, ptr->next->next->line4, ptr->next->next->next->line4, ptr->next->next->next->next->line4, ptr->next->next->next->next->next->line4, ptr->next->next->next->next->next->next->line4, ptr->next->next->next->next->next->next->next->line4, ptr->next->next->next->next->next->next->next->next->line4, ptr->next->next->next->next->next->next->next->next->next->line4);
        printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", ptr->line5, ptr->next->line5, ptr->next->next->line5, ptr->next->next->next->line5, ptr->next->next->next->next->line5, ptr->next->next->next->next->next->line5, ptr->next->next->next->next->next->next->line5, ptr->next->next->next->next->next->next->next->line5, ptr->next->next->next->next->next->next->next->next->line5, ptr->next->next->next->next->next->next->next->next->next->line5);
        printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", ptr->line6, ptr->next->line6, ptr->next->next->line6, ptr->next->next->next->line6, ptr->next->next->next->next->line6, ptr->next->next->next->next->next->line6, ptr->next->next->next->next->next->next->line6, ptr->next->next->next->next->next->next->next->line6, ptr->next->next->next->next->next->next->next->next->line6, ptr->next->next->next->next->next->next->next->next->next->line6);
        printf("│         │\t│         │\t│         │\t│         │\t│         │\t│         │\t│         │\t│         │\t│         │\t│         │\n");
        printf("│    %s│\t│    %s│\t│    %s│\t│    %s│\t│    %s│\t│    %s│\t│    %s│\t│    %s│\t│    %s│\t│    %s│\n", ptr->bspecChar, ptr->next->bspecChar, ptr->next->next->bspecChar, ptr->next->next->next->bspecChar, ptr->next->next->next->next->bspecChar, ptr->next->next->next->next->next->bspecChar, ptr->next->next->next->next->next->next->bspecChar, ptr->next->next->next->next->next->next->next->bspecChar, ptr->next->next->next->next->next->next->next->next->bspecChar, ptr->next->next->next->next->next->next->next->next->next->bspecChar);
        printf("└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\n");
    }
    if (num == 9) {
        printf("┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\n");
        printf("│%s    │\t│%s    │\t│%s    │\t│%s    │\t│%s    │\t│%s    │\t│%s    │\t│%s    │\t│%s    │\n", ptr->specChar, ptr->next->specChar, ptr->next->next->specChar, ptr->next->next->next->specChar, ptr->next->next->next->next->specChar, ptr->next->next->next->next->next->specChar, ptr->next->next->next->next->next->next->specChar, ptr->next->next->next->next->next->next->next->specChar, ptr->next->next->next->next->next->next->next->next->specChar);
        printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", ptr->line3, ptr->next->line3, ptr->next->next->line3, ptr->next->next->next->line3, ptr->next->next->next->next->line3, ptr->next->next->next->next->next->line3, ptr->next->next->next->next->next->next->line3, ptr->next->next->next->next->next->next->next->line3, ptr->next->next->next->next->next->next->next->next->line3);
        printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", ptr->line4, ptr->next->line4, ptr->next->next->line4, ptr->next->next->next->line4, ptr->next->next->next->next->line4, ptr->next->next->next->next->next->line4, ptr->next->next->next->next->next->next->line4, ptr->next->next->next->next->next->next->next->line4, ptr->next->next->next->next->next->next->next->next->line4);
        printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", ptr->line5, ptr->next->line5, ptr->next->next->line5, ptr->next->next->next->line5, ptr->next->next->next->next->line5, ptr->next->next->next->next->next->line5, ptr->next->next->next->next->next->next->line5, ptr->next->next->next->next->next->next->next->line5, ptr->next->next->next->next->next->next->next->next->line5);
        printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", ptr->line6, ptr->next->line6, ptr->next->next->line6, ptr->next->next->next->line6, ptr->next->next->next->next->line6, ptr->next->next->next->next->next->line6, ptr->next->next->next->next->next->next->line6, ptr->next->next->next->next->next->next->next->line6, ptr->next->next->next->next->next->next->next->next->line6);
        printf("│         │\t│         │\t│         │\t│         │\t│         │\t│         │\t│         │\t│         │\t│         │\n");
        printf("│    %s│\t│    %s│\t│    %s│\t│    %s│\t│    %s│\t│    %s│\t│    %s│\t│    %s│\t│    %s│\n", ptr->bspecChar, ptr->next->bspecChar, ptr->next->next->bspecChar, ptr->next->next->next->bspecChar, ptr->next->next->next->next->bspecChar, ptr->next->next->next->next->next->bspecChar, ptr->next->next->next->next->next->next->bspecChar, ptr->next->next->next->next->next->next->next->bspecChar, ptr->next->next->next->next->next->next->next->next->bspecChar);
        printf("└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\n");
    }
    if (num == 8) {
        printf("┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\n");
        printf("│%s    │\t│%s    │\t│%s    │\t│%s    │\t│%s    │\t│%s    │\t│%s    │\t│%s    │\n", ptr->specChar, ptr->next->specChar, ptr->next->next->specChar, ptr->next->next->next->specChar, ptr->next->next->next->next->specChar, ptr->next->next->next->next->next->specChar, ptr->next->next->next->next->next->next->specChar, ptr->next->next->next->next->next->next->next->specChar);
        printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", ptr->line3, ptr->next->line3, ptr->next->next->line3, ptr->next->next->next->line3, ptr->next->next->next->next->line3, ptr->next->next->next->next->next->line3, ptr->next->next->next->next->next->next->line3, ptr->next->next->next->next->next->next->next->line3);
        printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", ptr->line4, ptr->next->line4, ptr->next->next->line4, ptr->next->next->next->line4, ptr->next->next->next->next->line4, ptr->next->next->next->next->next->line4, ptr->next->next->next->next->next->next->line4, ptr->next->next->next->next->next->next->next->line4);
        printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", ptr->line5, ptr->next->line5, ptr->next->next->line5, ptr->next->next->next->line5, ptr->next->next->next->next->line5, ptr->next->next->next->next->next->line5, ptr->next->next->next->next->next->next->line5, ptr->next->next->next->next->next->next->next->line5);
        printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", ptr->line6, ptr->next->line6, ptr->next->next->line6, ptr->next->next->next->line6, ptr->next->next->next->next->line6, ptr->next->next->next->next->next->line6, ptr->next->next->next->next->next->next->line6, ptr->next->next->next->next->next->next->next->line6);
        printf("│         │\t│         │\t│         │\t│         │\t│         │\t│         │\t│         │\t│         │\n");
        printf("│    %s│\t│    %s│\t│    %s│\t│    %s│\t│    %s│\t│    %s│\t│    %s│\t│    %s│\n", ptr->bspecChar, ptr->next->bspecChar, ptr->next->next->bspecChar, ptr->next->next->next->bspecChar, ptr->next->next->next->next->bspecChar, ptr->next->next->next->next->next->bspecChar, ptr->next->next->next->next->next->next->bspecChar, ptr->next->next->next->next->next->next->next->bspecChar);
        printf("└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\n");
    }
    if (num == 7) {
        printf("┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\n");
        printf("│%s    │\t│%s    │\t│%s    │\t│%s    │\t│%s    │\t│%s    │\t│%s    │\n", ptr->specChar, ptr->next->specChar, ptr->next->next->specChar, ptr->next->next->next->specChar, ptr->next->next->next->next->specChar, ptr->next->next->next->next->next->specChar, ptr->next->next->next->next->next->next->specChar);
        printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\n", ptr->line3, ptr->next->line3, ptr->next->next->line3, ptr->next->next->next->line3, ptr->next->next->next->next->line3, ptr->next->next->next->next->next->line3, ptr->next->next->next->next->next->next->line3);
        printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\n", ptr->line4, ptr->next->line4, ptr->next->next->line4, ptr->next->next->next->line4, ptr->next->next->next->next->line4, ptr->next->next->next->next->next->line4, ptr->next->next->next->next->next->next->line4);
        printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\n", ptr->line5, ptr->next->line5, ptr->next->next->line5, ptr->next->next->next->line5, ptr->next->next->next->next->line5, ptr->next->next->next->next->next->line5, ptr->next->next->next->next->next->next->line5);
        printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\n", ptr->line6, ptr->next->line6, ptr->next->next->line6, ptr->next->next->next->line6, ptr->next->next->next->next->line6, ptr->next->next->next->next->next->line6, ptr->next->next->next->next->next->next->line6);
        printf("│         │\t│         │\t│         │\t│         │\t│         │\t│         │\t│         │\n");
        printf("│    %s│\t│    %s│\t│    %s│\t│    %s│\t│    %s│\t│    %s│\t│    %s│\n", ptr->bspecChar, ptr->next->bspecChar, ptr->next->next->bspecChar, ptr->next->next->next->bspecChar, ptr->next->next->next->next->bspecChar, ptr->next->next->next->next->next->bspecChar, ptr->next->next->next->next->next->next->bspecChar);
        printf("└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\n");
    }

    if (num == 6) {
        printf("┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\n");
        printf("│%s    │\t│%s    │\t│%s    │\t│%s    │\t│%s    │\t│%s    │\n", ptr->specChar, ptr->next->specChar, ptr->next->next->specChar, ptr->next->next->next->specChar, ptr->next->next->next->next->specChar, ptr->next->next->next->next->next->specChar);
        printf("%s\t%s\t%s\t%s\t%s\t%s\n", ptr->line3, ptr->next->line3, ptr->next->next->line3, ptr->next->next->next->line3, ptr->next->next->next->next->line3, ptr->next->next->next->next->next->line3);
        printf("%s\t%s\t%s\t%s\t%s\t%s\n", ptr->line4, ptr->next->line4, ptr->next->next->line4, ptr->next->next->next->line4, ptr->next->next->next->next->line4, ptr->next->next->next->next->next->line4);
        printf("%s\t%s\t%s\t%s\t%s\t%s\n", ptr->line5, ptr->next->line5, ptr->next->next->line5, ptr->next->next->next->line5, ptr->next->next->next->next->line5, ptr->next->next->next->next->next->line5);
        printf("%s\t%s\t%s\t%s\t%s\t%s\n", ptr->line6, ptr->next->line6, ptr->next->next->line6, ptr->next->next->next->line6, ptr->next->next->next->next->line6, ptr->next->next->next->next->next->line6);
        printf("│         │\t│         │\t│         │\t│         │\t│         │\t│         │\n");
        printf("│    %s│\t│    %s│\t│    %s│\t│    %s│\t│    %s│\t│    %s│\n", ptr->bspecChar, ptr->next->bspecChar, ptr->next->next->bspecChar, ptr->next->next->next->bspecChar, ptr->next->next->next->next->bspecChar, ptr->next->next->next->next->next->bspecChar);
        printf("└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\n");
    }

    if (num == 5) {
        printf("┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\n");
        printf("│%s    │\t│%s    │\t│%s    │\t│%s    │\t│%s    │\n", ptr->specChar, ptr->next->specChar, ptr->next->next->specChar, ptr->next->next->next->specChar, ptr->next->next->next->next->specChar);
        printf("%s\t%s\t%s\t%s\t%s\n", ptr->line3, ptr->next->line3, ptr->next->next->line3, ptr->next->next->next->line3, ptr->next->next->next->next->line3);
        printf("%s\t%s\t%s\t%s\t%s\n", ptr->line4, ptr->next->line4, ptr->next->next->line4, ptr->next->next->next->line4, ptr->next->next->next->next->line4);
        printf("%s\t%s\t%s\t%s\t%s\n", ptr->line5, ptr->next->line5, ptr->next->next->line5, ptr->next->next->next->line5, ptr->next->next->next->next->line5);
        printf("%s\t%s\t%s\t%s\t%s\n", ptr->line6, ptr->next->line6, ptr->next->next->line6, ptr->next->next->next->line6, ptr->next->next->next->next->line6);
        printf("│         │\t│         │\t│         │\t│         │\t│         │\n");
        printf("│    %s│\t│    %s│\t│    %s│\t│    %s│\t│    %s│\n", ptr->bspecChar, ptr->next->bspecChar, ptr->next->next->bspecChar, ptr->next->next->next->bspecChar, ptr->next->next->next->next->bspecChar);
        printf("└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\n");
    }
    if (num == 4) {
        printf("┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\n");
        printf("│%s    │\t│%s    │\t│%s    │\t│%s    │\n", ptr->specChar, ptr->next->specChar, ptr->next->next->specChar, ptr->next->next->next->specChar);
        printf("%s\t%s\t%s\t%s\n", ptr->line3, ptr->next->line3, ptr->next->next->line3, ptr->next->next->next->line3);
        printf("%s\t%s\t%s\t%s\n", ptr->line4, ptr->next->line4, ptr->next->next->line4, ptr->next->next->next->line4);
        printf("%s\t%s\t%s\t%s\n", ptr->line5, ptr->next->line5, ptr->next->next->line5, ptr->next->next->next->line5);
        printf("%s\t%s\t%s\t%s\n", ptr->line6, ptr->next->line6, ptr->next->next->line6, ptr->next->next->next->line6);
        printf("│         │\t│         │\t│         │\t│         │\n");
        printf("│    %s│\t│   s%s│\t│    %s│\t│    %s│\n", ptr->bspecChar, ptr->next->bspecChar, ptr->next->next->bspecChar, ptr->next->next->next->bspecChar);
        printf("└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\n");
    }
    if (num == 3) {
        printf("┌─────────┐\t┌─────────┐\t┌─────────┐\n");
        printf("│%s    │\t│%s    │\t│%s    │\n", ptr->specChar, ptr->next->specChar, ptr->next->next->specChar);
        printf("%s\t%s\t%s\n", ptr->line3, ptr->next->line3, ptr->next->next->line3);
        printf("%s\t%s\t%s\n", ptr->line4, ptr->next->line4, ptr->next->next->line4);
        printf("%s\t%s\t%s\n", ptr->line5, ptr->next->line5, ptr->next->next->line5);
        printf("%s\t%s\t%s\n", ptr->line6, ptr->next->line6, ptr->next->next->line6);
        printf("│         │\t│         │\t│         │\n");
        printf("│    %s│\t│    %s│\t│    %s│\n", ptr->bspecChar, ptr->next->bspecChar, ptr->next->next->bspecChar);
        printf("└─────────┘\t└─────────┘\t└─────────┘\n");
    }
    if (num == 2) {
        printf("┌─────────┐\t┌─────────┐\n");
        printf("│%s    │\t│%s    │\n", ptr->specChar, ptr->next->specChar);
        printf("%s\t%s\n", ptr->line3, ptr->next->line3);
        printf("%s\t%s\n", ptr->line4, ptr->next->line4);
        printf("%s\t%s\n", ptr->line5, ptr->next->line5);
        printf("%s\t%s\n", ptr->line6, ptr->next->line6);
        printf("│         │\t│         │\n");
        printf("│    %s│\t│    %s│\n", ptr->bspecChar, ptr->next->bspecChar);
        printf("└─────────┘\t└─────────┘\n");
    }
    if (num == 1) {
        printf("┌─────────┐\n");
        printf("│%s    │\n", ptr->specChar);
        printf("%s\n", ptr->line3);
        printf("%s\n", ptr->line4);
        printf("%s\n", ptr->line5);
        printf("%s\n", ptr->line6);
        printf("│         │\n");
        printf("│    %s│\n", ptr->bspecChar);
        printf("└─────────┘\n");
    }
} // printCard()

/*---------------------------------------------------------------------
 |  Funtion: printBacks(int num)
 |
 |  Purpose: Prints up to 15 card backs.
 |
 |  Parameters:  int num
 |
 |  Returns:  void
 *-------------------------------------------------------------------*/
void printBacks(int num) {
    if (num == 15) {
        printf("┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\n");
        printf("│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\n");
    }
    if (num == 14) {
        printf("┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\n");
        printf("│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\n");
    }
    if (num == 13) {
        printf("┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\n");
        printf("│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\n");
    }
    if (num == 12) {
        printf("┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\n");
        printf("│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\n");
    }
    if (num == 11) {
        printf("┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\n");
        printf("│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\n");
    }
    if (num == 10) {
        printf("┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\n");
        printf("│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\n");
    }
    if (num == 9) {
        printf("┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\n");
        printf("│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\n");
    }
    if (num == 8) {
        printf("┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\n");
        printf("│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\n");
    }
    if (num == 7) {
        printf("┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\n");
        printf("│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\n");
    }
    if (num == 6) {
        printf("┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\n");
        printf("│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\n");
    }
    if (num == 5) {
        printf("┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\n");
        printf("│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\n");
    }
    if (num == 4) {
        printf("┌─────────┐\t┌─────────┐\t┌─────────┐\t┌─────────┐\n");
        printf("│ ####### │\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("└─────────┘\t└─────────┘\t└─────────┘\t└─────────┘\n");
    }
    if (num == 3) {
        printf("┌─────────┐\t┌─────────┐\t┌─────────┐\n");
        printf("│ ####### │\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\t│ ####### │\n");
        printf("└─────────┘\t└─────────┘\t└─────────┘\n");
    }
    if (num == 2) {
        printf("┌─────────┐\t┌─────────┐\n");
        printf("│ ####### │\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\n");
        printf("| ####### |\t│ ####### │\n");
        printf("└─────────┘\t└─────────┘\n");
    }
    if (num == 1) {
        printf("┌─────────┐\n");
        printf("│ ####### │\n");
        printf("| ####### |\n");
        printf("| ####### |\n");
        printf("| ####### |\n");
        printf("| ####### |\n");
        printf("| ####### |\n");
        printf("| ####### |\n");
        printf("└─────────┘\n");
    }
} // printBacks()

/*---------------------------------------------------------------------
 |  Funtion: printDeck(int p)
 |
 |  Purpose: Prints the entire contents of a chosen deck.
 |
 |  Parameters:  int p
 |
 |  Returns:  void
 *-------------------------------------------------------------------*/
void printDeck(int p) {
    int i = 0;
    card *ptr = NULL;
    if (p == 0) {
        ptr = head;
    }
    if (p == 1) {
        ptr = p1Head;
    }
    if (p == 2) {
        ptr = p2Head;
    }
    card *ptr2 = NULL;
    while (ptr != NULL) {
        ptr2 = ptr;
        while (i < 15 && ptr != NULL) {
            i++;
            ptr = ptr->next;
        }
        printCard(ptr2, i);
        printf("\n");
        i = 0;
    }
} // printDeck()

/*---------------------------------------------------------------------
 |  Funtion: ShuffleCard(card *ptr, int size)
 |
 |  Purpose: Shuffles a deck by performing 100 top-card swaps.
 |
 |  Parameters:  card *ptr
 |               int size
 |
 |  Returns:  void
 *-------------------------------------------------------------------*/
void ShuffleCard(card *ptr, int size) {
    if (size == 1)
        return;
    int i = 0, j = 0;
    int random = 0;
    char tempSuit;
    char tempSpecChar[12];
    char tempBSpecChar[12];
    char tempLine3[20];
    char tempLine4[20];
    char tempLine5[20];
    char tempLine6[20];
    int tempFace;
    srand((int)time(NULL));
    card* ptr2 = NULL, *start;
    start = ptr;
    while (i < 100) {
        ptr2 = start;
        random = rand()%size-1;
        j = 0;
        while (j <= random && ptr2 != NULL) {
            ptr2 = ptr2->next;
            j++;
        }
        if (ptr == ptr2) {
            continue;
        }
        tempSuit = ptr->suit;
        strcpy(tempSpecChar, ptr->specChar);
        strcpy(tempBSpecChar, ptr->bspecChar);
        strcpy(tempLine3, ptr->line3);
        strcpy(tempLine4, ptr->line4);
        strcpy(tempLine5, ptr->line5);
        strcpy(tempLine6, ptr->line6);
        tempFace = ptr->face;
        ptr->suit = ptr2->suit;
        strcpy(ptr->specChar, ptr2->specChar);
        strcpy(ptr->bspecChar, ptr2->bspecChar);
        strcpy(ptr->line3, ptr2->line3);
        strcpy(ptr->line4, ptr2->line4);
        strcpy(ptr->line5, ptr2->line5);
        strcpy(ptr->line6, ptr2->line6);
        ptr->face = ptr2->face;
        ptr2->suit = tempSuit;
        strcpy(ptr2->specChar, tempSpecChar);
        strcpy(ptr2->bspecChar, tempBSpecChar);
        strcpy(ptr2->line3, tempLine3);
        strcpy(ptr2->line4, tempLine4);
        strcpy(ptr2->line5, tempLine5);
        strcpy(ptr2->line6, tempLine6);
        ptr2->face = tempFace;
        i++;
    }
} // ShuffleCard()

/*---------------------------------------------------------------------
 |  Funtion: splitDeck(card *deck, card *p1Head, card *p2Head, int size)
 |
 |  Purpose: Splits the 53 card deck. Whoever ends up with one extra
 |           card is random.
 |
 |  Parameters:  card *deck
 |               card *p1Head
 |               card *p2Head
 |               int size
 |
 |  Returns:  void
 *-------------------------------------------------------------------*/
void splitDeck(card *deck, card *p1Head, card *p2Head, int size) {
    int random = 0;
    card *deckPtr;
    srand((int)time(NULL));
    random = rand()%2;
    deckPtr = deck;
    if (random == 1) {
        while (deckPtr != NULL) {
            appendCard(1, deckPtr->suit, deckPtr->face);
            if (deckPtr->next == NULL)
                break;
            deckPtr = deckPtr->next;
            appendCard(2, deckPtr->suit, deckPtr->face);
            deckPtr = deckPtr->next;
        }
        addSpecialCharacters(1);
        addSpecialCharacters(2);
    }
    else {
        while (deckPtr != NULL) {
            appendCard(2, deckPtr->suit, deckPtr->face);
            if (deckPtr->next == NULL)
                break;
            deckPtr = deckPtr->next;
            appendCard(1, deckPtr->suit, deckPtr->face);
            deckPtr = deckPtr->next;
        }
        addSpecialCharacters(1);
        addSpecialCharacters(2);
    }
} // splitDeck()

/*---------------------------------------------------------------------
 |  Funtion: deleteCard(int p, card *c)
 |
 |  Purpose: Deletes card c from a chosen deck.
 |
 |  Parameters:  int p
 |               card *c
 |
 |  Returns:  void
 *-------------------------------------------------------------------*/
void deleteCard(int p, card *c) {
    card *ptr = NULL;
    card *temp = NULL;
    if (p == 0) {
        ptr = head;
    }
    if (p == 1) {
        ptr = p1Head;
        p1Size--;
    }
    if (p == 2) {
        ptr = p2Head;
        p2Size--;
    }
    // If target is head node
    if (ptr == c) {
        // If target is the only node
        if (ptr->next == NULL) {
            c = NULL;
            return;
        }
        ptr->suit = ptr->next->suit;
        strcpy(ptr->specChar, ptr->next->specChar);
        strcpy(ptr->bspecChar, ptr->next->bspecChar);
        strcpy(ptr->line3, ptr->next->line3);
        strcpy(ptr->line4, ptr->next->line4);
        strcpy(ptr->line5, ptr->next->line5);
        strcpy(ptr->line6, ptr->next->line6);
        ptr->face = ptr->next->face;
        c = ptr->next;
        ptr->next = ptr->next->next;
        c = NULL;
        return;
    }
    card *prev = ptr;
    while (prev->next != NULL && prev->next != c) {
        temp = prev;
        prev = prev->next;
    }
    if (prev->next == NULL) {
        free(prev);
        temp->next = NULL;
        return;
    }
    temp = prev->next;
    prev->next = prev->next->next;
    temp = NULL;
    return;
} // deleteCard()

/*---------------------------------------------------------------------
 |  Funtion: removeDups(int p)
 |
 |  Purpose: Removes the duplicates (cards with the same faces) from
 |           a chosen deck.
 |
 |  Parameters:  int p
 |
 |  Returns:  void
 *-------------------------------------------------------------------*/
void removeDups(int p) {
    card *ptr = NULL;
    card removed;
    removed.next = malloc(sizeof(card));
    if (p == 0) {
        ptr = head;
    }
    if (p == 1) {
        ptr = p1Head;
    }
    if (p == 2) {
        ptr = p2Head;
    }

    card *ptr2 = ptr->next;
    while (ptr != NULL) {
        while (ptr2 != NULL) {
            if (ptr->face == ptr2->face) {
                removed.suit = ptr->suit;
                strcpy(removed.specChar, ptr->specChar);
                strcpy(removed.bspecChar, ptr->bspecChar);
                strcpy(removed.line3, ptr->line3);
                strcpy(removed.line4, ptr->line4);
                strcpy(removed.line5, ptr->line5);
                strcpy(removed.line6, ptr->line6);
                removed.face = ptr->face;
                removed.next->suit = ptr2->suit;
                strcpy(removed.next->specChar, ptr2->specChar);
                strcpy(removed.next->bspecChar, ptr2->bspecChar);
                strcpy(removed.next->line3, ptr2->line3);
                strcpy(removed.next->line4, ptr2->line4);
                strcpy(removed.next->line5, ptr2->line5);
                strcpy(removed.next->line6, ptr2->line6);
                removed.next->face = ptr2->face;
                printf("Removed Pair:\n");
                printCard(&removed, 2);
                deleteCard(p, ptr);
                deleteCard(p, ptr2);
                if (p == 0) {
                    ptr = head;
                }
                if (p == 1) {
                    ptr = p1Head;
                }
                if (p == 2) {
                    ptr = p2Head;
                }
                ptr2 = ptr;
            }
            ptr2 = ptr2->next;
        }
        ptr = ptr->next;
        if (p == 1 && p1Size == 1)
            break;
        if (p == 2 && p2Size == 1)
            break;
        if (ptr->next == NULL)
            break;
        ptr2 = ptr->next;
    }
} // removeDups()

/*---------------------------------------------------------------------
 |  Funtion: takeCard(int from, int pos)
 |
 |  Purpose: Takes a card from deck "from" at position "pos" and 
 |           appends that card to the other players deck.
 |
 |  Parameters:  int from
 |               int pos
 |
 |  Returns:  void
 *-------------------------------------------------------------------*/
void takeCard(int from, int pos) {
    card *ptr = NULL;
    int i = 1;
    int to = 0;
    if (from == 1) {
        ptr = p1Head;
        to = 2;
    }
    if (from == 2) {
        ptr = p2Head;
        to = 1;
    }
    while (i != pos) {
        ptr = ptr->next;
        i++;
    }
    appendCard(to, ptr->suit, ptr->face);
    addSpecialCharacters(to);
    deleteCard(from, ptr);
} // takeCard()

/*---------------------------------------------------------------------
 |  Funtion: gameOver(char p2[])
 |
 |  Purpose: Determines if the game is over by looking for the player
 |           with the joker.
 |
 |  Parameters:  char p2[]
 |
 |  Returns:   1 if the game is over. 0 otherwise.
 *-------------------------------------------------------------------*/
int gameOver(char p2[]) {
    if (p1Size == 0) {
        printf("%s has the Joker, Aida wins \n", p2);
        printf("%s's final hand: \n", p2);
        printDeck(2);
        printf("Aida's final hand: \n");
        printDeck(1);
        return 1;
    }
    if (p2Size == 0) {
        printf("Aida has the Joker, %s wins \n", p2);
        printf("%s's final hand: \n", p2);
        printDeck(2);
        printf("Aida's final hand: \n");
        printDeck(1);
        return 1;
    }
    if (p1Size == 1) {
        if (p1Head->face == 0) {
            printf("Aida has the Joker, %s wins \n", p2);
            printf("%s's final hand: \n", p2);
            printDeck(2);
            printf("Aida's final hand: \n");
            printDeck(1);
            return 1;
        }
    }
    if (p2Size == 1) {
        if (p2Head->face == 0) {
            printf("%s has the Joker, Aida wins \n", p2);
            printf("%s's final hand: \n", p2);
            printDeck(2);
            printf("Aida's final hand: \n");
            printDeck(1);
            return 1;
        }
    }
    return 0;
} // gameOver()

/*---------------------------------------------------------------------
 |  Funtion: main()
 |
 |  Purpose: Provides the execution pathway for player interactions,
 |           the construction and modification of the decks, and 
 |           freeing of memory.
 |
 |  Parameters:  None.
 |
 |  Returns:  void
 *-------------------------------------------------------------------*/
int main(void) {
    char c = 'y';
    while (c != 'q' && c != 'Q') {
        int random = 0;
        int select = 0;
        int turn = 0;
        char p2[64] = " ";
        char num[64] = "0";
    
        // Start screen and deck creation
        printStartScreen();
        printf("Welcome challenger, enter your name: \n");
        scanf(" %s", p2);
        printf("\nHello %s, Aida the AI will take you to smash town \n\n", p2);
        CreateDeck();
        addSpecialCharacters(0);
        printf("***---***Hit Enter key to continue***---***\n");
        
        // Deck display and shuffling of deck
        char enter = 0;
        while (enter != '\r' && enter != '\n') {
            enter = getchar();
        }
        printf("\nHere is the 53 card deck: \n");
        printDeck(0);
        printf("***---***Hit Enter key to continue***---***\n");
        enter = 0;
        while (enter != '\r' && enter != '\n') {
            enter = getchar();
        }
        printf("\nHere is the shuffled deck: \n");
        ShuffleCard(head, 53);
        printDeck(0);

        // Splitting of deck and removal of duplicates.
        printf("***---***Hit Enter key to continue***---***\n");
        enter = 0;
        while (enter != '\r' && enter != '\n') {
            enter = getchar();
        }
        printf("\nThe deck has been split: \n");
        card *p1Deck = NULL;
        card *p2Deck = NULL;
        splitDeck(head, p1Deck, p2Deck, 53);
        printf("This is Aida's Deck. Aid has %d cards: \n", p1Size);
        printDeck(1);
        printf("This is %s's Deck. %s has %d cards: \n", p2, p2, p2Size);
        printDeck(2);
        printf("***---***Hit Enter key to continue***---***\n");
        enter = 0;
        while (enter != '\r' && enter != '\n') {
            enter = getchar();
        }
        printf("Removed duplicates from Aida's deck: \n");
        removeDups(1);
        printf("\n");
        printf("Removed duplicates from %s's deck: \n", p2);
        removeDups(2);
        printf("\nAida's new hand \n");
        printDeck(1);
        printf("\n%s's new hand \n", p2);
        printDeck(2);
        printf("%s has %d cards \n\n", p2, p2Size);
        printf("Aida has %d cards \n\n", p1Size);
    
        // Determination of starting player
        printf("***---***Hit Enter key to continue***---***\n");
        enter = 0;
        while (enter != '\r' && enter != '\n') {
            enter = getchar();
        }
        // Aida pathway
        if (p2Size > p1Size) {
            printf("%s has more cards, Aida starts: \n", p2);
            srand((int)time(NULL));
            random = rand()%p2Size + 1;
            printf("Aida has chosen card #%d from %s's hand \n", random, p2);
            takeCard(2, random);
            removeDups(1);
            ShuffleCard(p1Head, p1Size);
            turn = 1;
            printf("%s, this is your hand. You have %d cards \n", p2, p2Size);
            printDeck(2);
            printf("Aida now has %d cards \n\n", p1Size);
        }
        // Player 2 pathway
        else {
            printf("Aida has more cards, %s starts: \n", p2);
            printf ("Aida has %d cards: \n", p1Size);
            printBacks(p1Size);
            printf("Select a card from Aida's hand (1-%d) \n", p1Size);
            scanf("%s", num);
            while (1 == 1) {
                int i = 0;
                select = 0;
                if (strlen(num) > 2) {
                    printf("Aida has only %d cards \n", p1Size);
                    printf("Select a card from Aida's hand (1-%d) \n", p1Size);
                    scanf("%s", num);
                    continue;
                }
                for (i = 0; i < strlen(num); i++) {
                    if (!isdigit(num[i])) {
                        printf("Aida has only %d cards \n", p1Size);
                        printf("Select a card from Aida's hand (1-%d) \n", p1Size);
                        scanf("%s", num);
                        continue;
                    }
                }
                if (i == 1) {
                    select += num[0]-'0';
                }
                if (i == 2) {
                    select += num[0]-'0';
                    select *= 10;
                    select += num[1]-'0';
                }
                if (select < 1 || select > p1Size) {
                    printf("Aida has only %d cards \n", p1Size);
                    printf("Select a card from Aida's hand (1-%d) \n", p1Size);
                    scanf("%s", num);
                    continue;
                }
                break;
            }
            takeCard(1, select);
            removeDups(2);
            turn = 2;
            printf("%s, this is your shuffled hand. You have %d cards \n", p2, p2Size);
            ShuffleCard(p2Head, p2Size);
            printDeck(2);
            printf("Aida now has %d cards \n", p1Size);
        }
        // Game progression until winner is determined
        while (gameOver(p2) == 0) {
            printf("***---***Hit Enter key to continue***---***\n");
            enter = 0;
            while (enter != '\r' && enter != '\n') {
                enter = getchar();
            }
            if (turn%2 == 0) {
                enter = 0;
                while (enter != '\r' && enter != '\n') {
                    enter = getchar();
                }
            }
            if (turn%2 != 0) {
                printf ("Aida has %d cards: \n", p1Size);
                printBacks(p1Size);
                printf("Select a card from Aida's hand (1-%d) \n", p1Size);
                scanf("%s", num);
                while (1 == 1) {
                    int i = 0;
                    select = 0;
                    if (strlen(num) > 2) {
                        printf("Aida has only %d cards \n", p1Size);
                        printf("Select a card from Aida's hand (1-%d) \n", p1Size);
                        scanf("%s", num);
                        continue;
                    }
                    for (i = 0; i < strlen(num); i++) {
                        if (!isdigit(num[i])) {
                            printf("Aida has only %d cards \n", p1Size);
                            printf("Select a card from Aida's hand (1-%d) \n", p1Size);
                            scanf("%s", num);
                            continue;
                        }
                    }
                    if (i == 1) {
                        select += num[0]-'0';
                    }
                    if (i == 2) {
                        select += num[0]-'0';
                        select *= 10;
                        select += num[1]-'0';
                    }
                    if (select < 1 || select > p1Size) {
                        printf("Aida has only %d cards \n", p1Size);
                        printf("Select a card from Aida's hand (1-%d) \n", p1Size);
                        scanf("%s", num);
                        continue;
                    }
                    break;
                }
                takeCard(1, select);
                if (gameOver(p2) == 1) {
                    break;
                }
                removeDups(2);
                if (gameOver(p2) == 1) {
                    break;
                }

                turn++;
                printf("%s, this is your shuffled hand. You have %d cards \n", p2, p2Size);
                ShuffleCard(p2Head, p2Size);
                printDeck(2);
                printf("Aida now has %d cards \n\n", p1Size);
                continue;
            }
            if (turn%2 == 0) {
                srand((int)time(NULL));
                random = rand()%p2Size + 1;
                printf("Aida has chosen card #%d from %s's hand \n", random, p2);
                takeCard(2, random);
                if (gameOver(p2) == 1) {
                    break;
                }
                removeDups(1);
                if (gameOver(p2) == 1) {
                    break;
                }
                ShuffleCard(p1Head, p1Size);
                turn++;
                printf("%s, this is your hand. You have %d cards \n", p2, p2Size);
                printDeck(2);
                printf("Aida now has %d cards \n\n", p1Size);
                continue;
            }
        }
        
        // Frees memory, sets all deck sizes back to initial value
        freeMem();
        p1Size = 0;
        p2Size = 0;
        head = NULL;
        p1Head = NULL;
        p2Head = NULL;
        printf("***---***Hit Enter key to continue***---***\n");
        enter = 0;
        while (enter != '\r' && enter != '\n') {
            enter = getchar();
        }
        // Conintuation statement
        printf("Do you want to continue? (q or Q to quit): \n");
        scanf(" %c", &c);
    }
    return 0;
} // main()
