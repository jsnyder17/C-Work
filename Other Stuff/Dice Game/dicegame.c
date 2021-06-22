//*______ Joshua Snyder ______*//

/*
    * Dice Rolling Game 
    * Inspired by post from r/badcode.
*/

#include <stdio.h>
#include <stdlib.h>


struct Player {         /* structure for player with player name and score */
    char name[100];
    int score;
};
struct NameContainer {  /* structure for name container array */
    char name[100];
};

/* compare if two char arrays of names are equal */
int compareNames(char name1[], char name2[]) {
    int i;
    int notEqual = 0;

    for (i = 0; i < 100 && notEqual == 0; ++i) {
        if (name1[i] != name2[i]) {
            notEqual = 1;
            printf("At %i: ", i);
            putchar(name1[i]);
            printf("\n");
        }
    }
    printf("%i\n", notEqual);
    return notEqual;
}

/* roll d6 */
int rollDice() {
    int result = (rand() % 6) + 1;

    printf("Rolled %i\n", result);
    
    return result;
}

/* game loop */
void game(struct Player players[]) {
    int round, tempScore, roll1, roll2, roll3, turnIndex, turnCount, winIndex;
    round = 1;
    tempScore = 0;
    turnIndex = 0;
    turnCount = 0;
    winIndex = 0;

    while (round < 6) {
        printf("\nRound #%i --------------------\n", round);

        while (turnCount < 2) {
            /* display whose turn it is */
            printf("%s's turn ...\n", players[turnIndex].name);

            /* roll initial dice */
            roll1 = rollDice();
            roll2 = rollDice();
            tempScore = roll1 + roll2;

            /* roll conditions */
            if (roll1 == roll2) {                                       /* if player rolls doubles, an additional dice is rolled */
                printf("Rolled doubles. Extra dice roll ... \n");
                roll3 = rollDice();
                tempScore += roll3;
            }
            if (tempScore % 2 == 0) {                                   /* if total rolled is even, 10 points are added */
                printf("Rolled even total. Add 10 pts ... \n");

                players[turnIndex].score += 10;
            }
            else {                                                      /* if total rolled is odd, 5 points are subtracted */
                printf("Rolled odd total. Subtract 5 pts ... \n");

                if (players[turnIndex].score - 5 < 0) { /* ensure that the player's scores will never be negative */
                    players[turnIndex].score = 0;
                }
                else {
                    players[turnIndex].score -= 5;
                }
            }

            /* assign points and switch turns */
            players[turnIndex].score += tempScore;

            if (turnIndex == 0) {
                turnIndex = 1;
            }
            else {
                turnIndex = 0;
            }

            /* display the current scores */
            printf("\nCURRENT SCORES: %s: %i | %s: %i\n", players[0].name, players[0].score, players[1].name, players[1].score);

            turnCount += 1;
        }

        round += 1;
        turnCount = 0;
    }

    while (players[0].score == players[1].score) {
        printf("Rolling tiebreaker ... \n");
        players[0].score += rollDice();
        players[1].score += rollDice();
    }

    if (players[1].score > players[winIndex].score) {
        winIndex = 1;
    }
    printf("%s wins! \n", players[winIndex].name);
}

/* initialize player array, input player names, and start the game */
void start() {
    struct Player players[2];
    int i, j, k;
    char c;
    FILE *fp;
    struct NameContainer names[7];
    char tempName[100];
    int userNotExists = 0;

    /* get all verified users from file and store them in a list */
    fp = fopen("users.txt", "r");

    for (i = 0; i < 7; ++i) {
        fscanf(fp, "%s", names[i].name);
        printf("Stored %s in the list. \n", names[i].name);
    }

    players[0].score = players[1].score = 0;

    for (i = 0; i < 2; ++i) {
        userNotExists = 0;
        while (userNotExists == 0) {
            printf("Enter the name of player %i -> ", i + 1);

            for (j = 0; (c = getchar()) != '\n'; ++j) {
                players[i].name[j] = c;
            }

            /* Check if name is part of verified users */
            for (k = 0; k < 7 && userNotExists == 0; ++k) {
                printf("Does %s == %s?\n", names[k].name, players[i].name);
                
                userNotExists = compareNames(names[k].name, players[i].name);
            }
            if (userNotExists == 1) {
                printf("User is not valid. Enter a valid user. \n");
                userNotExists = 0;
            }
        }

        printf("\n");
    }

    game(players);
}

int main() {
    time_t t;
    
    srand((unsigned) time(&t)); /* ensure random values per run */

    start();

    return 0;
}