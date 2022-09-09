/*
        Program 1: Wumpus, version 1 (fixed size array)

        Mohammed Abdulaziz
  CS211
  Professor Dale Reed

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
    
    displayCave();
    displayInstructions();
    printf("You are in room %d. \n\n",moveNum);
    return;
}

void choiceP(int playerPos) {
    displayCave();
    printf("You are in room %d. \n\n",playerPos);
}

void choiceC(int playerPos, int wumpusPos, int pit1Pos, int pit2Pos) {
    printf("Cheating! Game elements are in the following rooms:\nPlayer Wumpus Pit1 Pit2  \n  %d      %d     %d     %d \n\n", playerPos, wumpusPos, pit1Pos, pit2Pos);
    printf("You are in room %d. \n\n",playerPos);
    return;
}

// bool validMove(int playerPos, int moveTo) {
    
// }

//--------------------------------------------------------------------------------
int main(void) {

    // Seed the random number generator.  Change seed to time(0) to change output
    // each time.
    // srand(time(0));
    srand(1);
    // How to get a random number
    int cavePos[2][20];
    int pit1Pos = rand() % 20 + 1;
    int pit2Pos = rand() % 20 + 1;
    int wumpusStart = rand() % 20 + 1;
    int wumpusPos = wumpusStart;
    int playerStart = rand() % 20 + 1; // Using +1 gives random number 1..20 rather than 0..19
    int playerPos = playerStart;
    
    int temp;
    
    int moveNum = 1;
    char userChoice[4];
    
    int gameOver = 1;
    long moveToPos;
    printf("You are in room %d. \n\n",playerPos);
    printf("%d. Enter your move (or 'D' for directions): ", moveNum);
    fgets(userChoice, 5, stdin);
    //printf("1. %c\n2. %c\n3. %c\n4. %c\n", userChoice[0], userChoice[1], userChoice[2], userChoice[3]);
    userChoice[0] = toupper(userChoice[0]);

    while ((userChoice[0] != 'X') && (gameOver != 0)) {
    
        if (userChoice[0] == 'D') {
            choiceD(playerPos);
            printf("%d. Enter your move (or 'D' for directions): ", moveNum);
        }
        else if(userChoice[0] == 'P') {
            choiceP(playerPos);
            printf("%d. Enter your move (or 'D' for directions): ", moveNum);
        }
        else if(userChoice[0] == 'C') {
            choiceC(playerPos, wumpusPos, pit1Pos, pit2Pos);
            printf("%d. Enter your move (or 'D' for directions): ", moveNum);
        }
        else if(userChoice[0] == 'M') {
            
        
        }
        fgets(userChoice, 5, stdin);
        //scanf("%c", userChoice);
        userChoice[0] = toupper(userChoice[0]);
    }

    if (userChoice[0] == 'X') {
        printf("\nExiting Program ...");
    }
    
        /*
              // Below are all the messages used throughout the program. You may
         need to change them,
              // or move them to a different place in the code.
              printf("1. Enter your move (or 'D' for directions): ");	// prompt
         for user to enter their move printf("Invalid move.  Please retry. \n");
         // message for invalid move

              // Message for menu option C (cheating). Note that the printf()
         statement below always prints 1 2 3 4
              // for the player room, wumpus room, pit 1 room, and pit 2 room
              printf( "Cheating! Game elements are in the following rooms: \n"
                      "Player Wumpus Pit1 Pit2  \n"
                      "%4d %7d %5d %5d \n\n",
                              1,
                              2,
                              3,
                              4
                      );

              // All messages possible when player is in a given room
              printf("You are in room 1. ");
              printf("You smell a stench. ");
              printf("You feel a draft. ");
              printf("\n\n");

              // Message when the player dies by falling into a pit
              printf("Aaaaaaaaahhhhhh....   \n");
              printf("    You fall into a pit and die. \n");

              // Both possible messages when the player enters a room that has
         the Wumpus printf( "You hear a slithering sound, as the Wumpus slips
         away. \n" "Whew, that was close! \n"); printf(	"You briefly feel a
         slimy tentacled arm as your neck is snapped. \n" "It is over.\n");

          // Both possible messages after the user guesses where the Wumpus is,
         for a win or loss. printf("You won!\n"); printf("You lost.\n");

              // Prompt for user when they choose to reset
              printf("Enter the room locations (1..20) for player, wumpus, pit1,
         and pit2: \n");

          // Prompt for guess of where Wumpus room is
          printf("Enter room (1..20) you think Wumpus is in: ");

              // Message that prints at the end of the program
              printf("\nExiting Program ...\n");
        */
        return 0;
}