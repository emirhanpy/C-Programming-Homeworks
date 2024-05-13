#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void displayBoard(char board[10][10]) {
    printf("   ");
    for (int j = 0; j < 10; j++) {
        printf("%d ", j);               //To print our columns.
    }
    printf("\n");

    for (int i = 0; i < 10; i++) {
        printf("%d  ", i);                //To print our rows.
        for (int j = 0; j < 10; j++) {
            printf("%c ", board[i][j]);   //For printing our Computer position (which is in [9][9]) and Player position (which is in [0][0]).
        }
        printf("\n");
    }
}

int generateTrapValues() {
    return rand() % 5 + 1;     //To generate our trap value between 1 and 5.
}

int rollDice(){
    return 1 + rand() % 6;   //To generate our dice.
}

int checkTrapIndex(int row, int col) {                      //This function check our trap index whether in the sides of the board.
    if ((row == 0 || row == 9 || col == 0 || col == 9) &&
        !(row == 0 && col == 0) && !(row == 9 && col == 9)) {
        return 1;  //true
    }
    return 0;   //false
}

void generateTrapIndexPlayer(int *trap_i_player, int *trap_j_player) {
    do {                                                         //This do-while loop asks for the trapIndex until it is write correctly.
        printf("Enter trap index (row col): \n");
        scanf("%d %d", trap_i_player, trap_j_player);
        if (!checkTrapIndex(*trap_i_player, *trap_j_player)) { // If checkTrapIndex is true (1), this converts it to false (0), meaning it skips the if statement.

            printf("The trap index should be placed around the board.\n");
        }
    } while (!checkTrapIndex(*trap_i_player, *trap_j_player));
}


int randomBetweenOneAndNine() {        //To generate random numbers between 1-9 trap index for computer.
    return rand() % 9 + 1;
}


void generateTrapIndexComputer(int *trap_i_computer, int *trap_j_computer){   //This function is generating trap index for computer randomly.

    do {                                                   //This do-while loop same as previous one.
        *trap_i_computer = randomBetweenOneAndNine();
        *trap_j_computer = randomBetweenOneAndNine();
        if (!checkTrapIndex(*trap_i_computer, *trap_j_computer)) {

        }
    } while (!checkTrapIndex(*trap_i_computer, *trap_j_computer));

    printf("Generated trap index (row col): %d %d\n",*trap_i_computer,*trap_j_computer);

}

int stepPlayer(char (*boardPlayer)[10], int *i, int *j, int numSteps, int *trap_i_player, int *trap_j_player, int playerTrapValue) {
    if (*i == *trap_i_player && *j == *trap_j_player){      //We check if player is on a trap or not.
        if (numSteps <= playerTrapValue){
            int result = numSteps-playerTrapValue;
            printf("Trapped at index %d %d %d forward - %d backward = %d!\n",*i,*j,numSteps,playerTrapValue, result);
            numSteps = 0;
        }
        else{
            int result = numSteps-playerTrapValue;
            printf("Trapped at index %d %d %d forward - %d backward = %d!\n",*i,*j,numSteps,playerTrapValue, result);
            numSteps = numSteps - playerTrapValue;
        }
    }

    for (int step = 0; step < numSteps; step++) {


        if (*i == 0 && *j < 9) {
            (*j)++;     //Move right.
        }else if (*i < 9 && *j == 9)  {
            (*i)++;     //Move down.
        }else if (*i == 9 && *j > 0){
            (*j)--;     //Move left.
        }else if (*i > 0 && *j == 0){
            (*i)--;     //Move up.
        }

        boardPlayer[*i][*j] = 'P';          //We mark player's new position on the board.

    }
    displayBoard(boardPlayer);       //We display the board after movement.
    return 0;
}

int stepComputer(char (*boardComputer)[10], int *ic, int *jc, int numSteps, int *trap_i_computer, int *trap_j_computer, int computerTrapValue){

    if (*ic == *trap_i_computer && *jc == *trap_j_computer){  //We check if computer is on a trap or not.
        if (numSteps <= computerTrapValue){
            int result = numSteps-computerTrapValue;
            printf("Trapped at index %d %d %d forward - %d backward = %d!\n",*ic,*jc,numSteps,computerTrapValue,
                   result);
            numSteps = 0;
        }
        else{
            int result = numSteps-computerTrapValue;
            printf("Trapped at index %d %d %d forward - %d backward = %d!\n",*ic,*jc,numSteps,computerTrapValue,
                   result);
            numSteps = numSteps - computerTrapValue;
        }
    }

    for (int step = 0; step < numSteps; step++){
        if(*ic == 9 && *jc > 0){
            (*jc)--;
        }else if(*ic > 0 && *jc == 0){
            (*ic)--;
        }else if(*ic == 0 && *jc < 9){
            (*jc)++;
        }else if (*ic < 9 && *jc == 9){
            (*ic)++;
        }

        boardComputer[*ic][*jc] = 'C';     //We mark computer's new position on the board.
    }
    displayBoard(boardComputer);    //We display the board after movement.
    return 0;
}


int main() {
    srand(time(NULL));
    int countComputer = 0;   //This variable represents sum of computer's steps on board.
    int countPlayer = 0;     //This variable represents sum of player's steps on board.
    int trap_i_player = 0;   //We use as trap value after in function of generateTrapIndexPlayer.
    int trap_j_player = 0;
    int trap_i_computer = 0; //We use as trap value after in function of generateTrapIndexComputer.
    int trap_j_computer = 0;

    printf("---Player---\n");
    int playerTrapValue = generateTrapValues();
    printf("Generated Trap Value: %d\n",playerTrapValue);
    generateTrapIndexPlayer(&trap_i_player, &trap_j_player);

    printf("---Computer---\n");
    int computerTrapValue = generateTrapValues();
    printf("Generated Trap Value: %d\n",computerTrapValue);
    generateTrapIndexComputer(&trap_i_computer, &trap_j_computer);
    printf("\n-----Initial Board-----\n");
    printf("\n    Player Board\n");
    char boardPlayer[10][10] = {0};       //We created our 10x10 char matrix board for player and initialize all elements with 0.
    boardPlayer[0][0] = 'P';              //We initialize P in [0][0].
    int i = 0;                       //Starting location of player.(Row)
    int j = 0;                       //Starting location of player.(Column)
    displayBoard(boardPlayer);     //We call our function to display player board.

    printf("\n    Computer Board\n");
    char boardComputer[10][10] = {0};    //We created our 10x10 char matrix board for computer and initialize all elements with 0.
    boardComputer[9][9] = 'C';           //We initialize C in [9][9].
    int ic = 9;                      //Starting location of computer.(Row)
    int jc = 9;                      //Starting location of computer.(Column)
    displayBoard(boardComputer);   //We call our function to display computer board.

    int countRound = 1;
    int active = 0;

    do {                                        //This do-while loop control whole game.
        int computerDice = rollDice();
        int playerDice = rollDice();

        printf("---Round %d---\n",countRound);
        printf("I have rolled the dice and I got %d\n", computerDice);
        printf("I have rolled the dice and You got %d\n", playerDice);
        printf("\n    Player Board\n");
        stepPlayer(boardPlayer, &i, &j ,playerDice, &trap_i_player,
                   &trap_j_player, playerTrapValue);
        printf("\n    Computer Board\n");
        stepComputer(boardComputer, &ic, &jc ,computerDice, &trap_i_computer,
                     &trap_j_computer, computerTrapValue);

        countComputer += computerDice;     //We update total computer movement.
        countPlayer += playerDice;         //We update total player movement.
        countRound++;                      //To increase number of rounds.

        if (countComputer >= 36 && countComputer > countPlayer){
            active = 1;
        }
        else if  (countPlayer >= 36 && countPlayer > countComputer){
            active = 1;
        }
    } while ( (countComputer <= 36 || countPlayer <= 36) && ( !active ) );

    printf("\n---END---\n");
    if (countComputer > countPlayer){
        printf("I won.");
    }
    else{
        printf("You won.");
    }

    return 0;
}