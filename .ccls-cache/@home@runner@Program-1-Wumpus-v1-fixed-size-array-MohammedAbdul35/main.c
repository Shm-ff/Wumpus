/*
Program 1: Hunt the Wumpus

Course: CS 211, Fall 2022. Tues 4pm lab
System: Linux using Repl.it
Author: Mohammed Abdulaziz
*/
#include <stdio.h>
#include <stdlib.h> // for srand
#include <stdbool.h>
//--------------------------------------------------------------------------------
void displayCave() {
  printf("\n       ______18______             \n"
         "      /      |       \\           \n"
         "     /      _9__      \\          \n"
         "    /      /    \\      \\        \n"
         "   /      /      \\      \\       \n"
         "  17     8        10     19       \n"
         "  | \\   / \\      /  \\   / |    \n"
         "  |  \\ /   \\    /    \\ /  |    \n"
         "  |   7     1---2     11  |       \n"
         "  |   |    /     \\    |   |      \n"
         "  |   6----5     3---12   |       \n"
         "  |   |     \\   /     |   |      \n"
         "  |   \\       4      /    |      \n"
         "  |    \\      |     /     |      \n"
         "  \\     15---14---13     /       \n"
         "   \\   /            \\   /       \n"
         "    \\ /              \\ /        \n"
         "    16---------------20           \n"
         "\n");
}

//--------------------------------------------------------------------------------
void displayInstructions() {
  printf("Hunt the Wumpus:                                             \n"
         "The Wumpus lives in a completely dark cave of 20 rooms. Each \n"
         "room has 3 tunnels leading to other rooms.                   \n"
         "                                                             \n"
         "Hazards:                                                     \n"
         "1. Two rooms have bottomless pits in them.  If you go there you fall "
         "and die.   \n"
         "2. The Wumpus is not bothered by the pits, as he has sucker feet. "
         "Usually he is \n"
         "   asleep. He will wake up if you enter his room. When you move into "
         "the Wumpus'\n"
         "   room, then he wakes and moves if he is in an odd-numbered room, "
         "but stays    \n"
         "   still otherwise.  After that, if he is in your room, he snaps "
         "your neck and  \n"
         "   you die!                                                          "
         "           \n"
         "                                                                     "
         "           \n"
         "Moves:                                                               "
         "           \n"
         "On each move you can do the following, where input can be upper or "
         "lower-case:  \n"
         "1. Move into an adjacent room.  To move enter 'M' followed by a "
         "space and       \n"
         "   then a room number.                                               "
         "           \n"
         "2. Enter 'R' to reset the person and hazard locations, useful for "
         "testing.      \n"
         "3. Enter 'C' to cheat and display current board positions.           "
         "           \n"
         "4. Enter 'D' to display this set of instructions.                    "
         "           \n"
         "5. Enter 'P' to print the maze room layout.                          "
         "           \n"
         "6. Enter 'G' to guess which room Wumpus is in, to win or lose the "
         "game!         \n"
         "7. Enter 'X' to exit the game.                                       "
         "           \n"
         "                                                                     "
         "           \n"
         "Good luck!                                                           "
         "           \n"
         " \n\n");
} // end displayInstructions()

void choiceD(int moveNum) {
    displayCave(); // displays both cave and instructions
    displayInstructions();
    return;
}

void choiceP(int playerPos) {
    displayCave(); // simply displays cave diagram
}

void choiceC(int playerPos, int wumpusPos, int pit1Pos, int pit2Pos) {
    printf("Cheating! Game elements are in the following rooms:\nPlayer Wumpus Pit1 Pit2  \n  %d      %d     %d     %d \n\n", playerPos, wumpusPos, pit1Pos, pit2Pos);
    return; // simply outputs debugging/"cheating" info
}

bool validMove(const int cavePos[4][20], int origPos, int moveTo) {
    for (int i = 0; i < 4; i++) { 
        if (cavePos[i][origPos - 1] == moveTo) {
            return true; 
        }
    } // goes through each set at the position of the original number and compares it to the number/location user wants to move towards, if the number that the user wants to move towards matches one of the numbers in either set then it is possible to move because of adjacency on a squashed dodecahedron
    return false;
}

void wumpusEsc(const int cavePos[4][20], int * wumpusPos) {
    int low = cavePos[0][*wumpusPos]; // goes through the 2-D Array and finds the lowest number at the same position in each set as the wumpus location and makes wumpus's new location the lowest number. Due to the inherent adjacency checking the lowest number is also a number that is connected wumpus's current location and when this is called will let wumpus escape
    for (int i = 0; i < 4; i++) {
        if (cavePos[i][*wumpusPos] < low){
            low = cavePos[i][*wumpusPos];
        }
    }
    *wumpusPos = low;
    return;
}

bool huntState(const int cavePos[4][20], int playerPos, int wumpusPos, int pit1Pos, int pit2Pos) {
    if ((playerPos == wumpusPos) && ((wumpusPos % 2) == 0)) {
        printf(	"You briefly feel a slimy tentacled arm as your neck is snapped. \n" "It is over.\n");
        return true;
    } // checks if player position matches any of the possible ways to die or interact with wumpus
    else if (playerPos == pit1Pos) {
        printf("Aaaaaaaaahhhhhh....   \n");
        printf("    You fall into a pit and die. \n");
        return true;
    }
    else if (playerPos == pit2Pos) {
        printf("Aaaaaaaaahhhhhh....   \n");
        printf("    You fall into a pit and die. \n");
        return true;
    }
    else if ((playerPos == wumpusPos) && !((wumpusPos % 2) == 0)) {
        printf( "You hear a slithering sound, as the Wumpus slips away. \n" "Whew, that was close! \n");
        wumpusEsc(cavePos, &wumpusPos);
        return false;
    }
    return false; // returns false because the function is used to see if death or interaction with wumpus has occured
}

void checkAdj(const int cavePos[4][20], int playerPos, int moveTo, int wumpusPos, int pit1Pos, int pit2Pos) {
    if (validMove(cavePos, playerPos, wumpusPos)) {
        printf("You smell a stench. ");
    } // simply checks if it is possible to move to a room that has either a pit or wumpus in and if so then say appropraite statemen. Does not actually move player, just checks to see if it is possible.
    if (validMove(cavePos, playerPos, pit1Pos)) {
        printf("You feel a draft. ");
    }
    else if (validMove(cavePos, playerPos, pit2Pos)) {
        printf("You feel a draft. ");
    }
    return;
}

//--------------------------------------------------------------------------------
int main(void) {
    srand(1);
    int cavePos[4][20] = {
    {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20},
    {8, 10, 12, 14, 6, 5, 17, 1, 18, 2, 19, 3, 20, 4, 16, 15, 7, 9, 11, 13},
    {5, 1, 2, 3, 4, 7, 6, 9, 8, 11, 10, 13, 12, 15, 14, 17, 18, 19, 20, 16},
    {2, 3, 4, 5, 1, 15, 8, 7, 10, 9, 12, 11, 14, 13, 6, 20, 16, 17, 18, 19}
    }; // 2-D array with each set element position lining up such that the number in the each of the same positions for each set will all be numbers that are connected to each other in a squashed dodecahedron
    int pit1Pos = rand() % 20 + 1; // original pit1, pit2, player, and wumpus locations
    int pit2Pos = rand() % 20 + 1; // 
    int wumpusStart = rand() % 20 + 1;
    int wumpusPos = wumpusStart;
    int playerStart = rand() % 20 + 1; // Using +1 gives random number 1..20 rather than 0..19
    int playerPos = playerStart;
    int guess = 0;
    int moveNum = 1; // counter to keep track of succesful moves
    char userChoice[1];
    int gameOver = 1; // 
    int moveToPos = 0;
    userChoice[0] = toupper(userChoice[0]); // sets choice to a standard upperCase
    while (gameOver != 0) {
        printf("You are in room %d. ",playerPos);
        checkAdj(cavePos,playerPos, moveToPos, wumpusPos, pit1Pos, pit2Pos);
        printf("\n\n%d. Enter your move (or 'D' for directions): ", moveNum);
        scanf("%c", &userChoice[0]);
        userChoice[0] = toupper(userChoice[0]);
        if (userChoice[0] == 'D') {
            choiceD(playerPos); //simple options with no complicated passes are offloaded with functions for smaller main()
        }
        else if(userChoice[0] == 'P') {
            choiceP(playerPos);
        }
        else if(userChoice[0] == 'C') {
            choiceC(playerPos, wumpusPos, pit1Pos, pit2Pos);
        }
        else if (userChoice[0] == 'M') {
            scanf(" %d", &moveToPos); // takes input and checks if move if possible to do
            if (validMove(cavePos, playerPos, moveToPos)) {
                playerPos = moveToPos; // once move is possible checks to see if the move made will kill player
                if ( huntState(cavePos, playerPos, wumpusPos, pit1Pos, pit2Pos)) {
                    userChoice[0] = 'X'; // if move made kills player exit game by setting userChoice to 'X' and breaking continuos game loop
                    break;
                }
                moveNum++; // increases turn after a successful move
            }
            else {
                printf("Invalid move.  Please retry. \n"); // only if user inputs something that doesnt make sense
            }
        }
        else if ( userChoice[0] == 'R') {
            printf("Enter the room locations (1..20) for player, wumpus, pit1, and pit2: \n\n");
            scanf("%d %d %d %d", &playerPos, &wumpusPos, &pit1Pos, &pit2Pos); //changes each of the variables to user input
        }
        else if (userChoice[0] == 'G') {
            printf("Enter room (1..20) you think Wumpus is in: ");
            scanf(" %d", &guess); // takes user guess and if matches wumpus location then user wins and game loop is broken
            if (guess == wumpusPos) {
                printf("You won!\n");
                userChoice[0] = 'X';
                break;
            }
        }
        else if (userChoice[0] == 'X') {
            break;
        }
        scanf("%c", &userChoice[0]);
        userChoice[0] = toupper(userChoice[0]); 
    }
    if (userChoice[0] == 'X') {
        printf("\nExiting Program ..."); // prints exiting statement
    }
    return 0;
}