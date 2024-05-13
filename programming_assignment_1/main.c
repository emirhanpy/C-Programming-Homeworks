#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int scoresheet(int dice1, int dice2, int dice3){    //This is the scoresheet function.
    int sumOfDices = 0;
    int score = 0;
    sumOfDices = dice1+dice2+dice3;


    if( (dice1==dice2 || dice1==dice3 || dice2==dice3) && sumOfDices==13 ){
        score += 50;
        printf("\nCRAG!!\n");
    }
    else if(sumOfDices==13){
        score += 26;
    }
    else if(dice1 == dice2 && dice1 == dice3 && dice2 == dice3){
        score += 25;
    }
    else if(dice1 == 1 && dice2 == 2 && dice3 == 3){
        score += 20;
    }
    else if(dice1 == 4 && dice2 == 5 && dice3 == 6){
        score += 20;
    }
    else if(dice1 == 1 && dice2 == 3 && dice3 == 5){
        score += 20;
    }
    else if(dice1 == 2 && dice2 == 4 && dice3 == 6){
        score += 20;
    }
    else{
        score += sumOfDices;
    }

    return score;
}



int roll_a_die() {          //To roll a dice.
    return 1 + (rand() % 6);
}



int play_computer(){                //This is the function of Computer's gameplay function.
    int dice1 = roll_a_die();
    int dice2 = roll_a_die();
    int dice3 = roll_a_die();

    printf("I rolled them and I got --> [Dice 1]: %d [Dice 2]: %d [Dice 3]: %d\n",dice1,dice2,dice3);

    if(dice1 == 4 && dice2 == 5)
    {
        printf("Rolled dice 3.\n");
        dice3 = roll_a_die();
        printf("[Dice 1]: %d [Dice 2]: %d [Dice 3]: %d\n",dice1,dice2,dice3);

    }else{
    }
    if(dice1 == 4 && dice3 == 6)
    {
        printf("Rolled dice 2\n");
        dice2 = roll_a_die();
        printf("[Dice 1]: %d [Dice 2]: %d [Dice 3]: %d\n",dice1,dice2,dice3);

    }else{
    }
    if(dice2 == 5 && dice3 == 6)
    {
        printf("Rolled dice 1\n");
        dice1 = roll_a_die();
        printf("[Dice 1]: %d [Dice 2]: %d [Dice 3]: %d\n",dice1,dice2,dice3);

    }else{
    }

    int round_score = scoresheet(dice1, dice2, dice3);    //We get the values of the dices and use them in the function of scoresheet.

    return round_score;
}



int play_user(){   //This is the user's gameplay function.
    int dice1 = roll_a_die();
    int dice2 = roll_a_die();
    int dice3 = roll_a_die();

    int keep1 = 0;
    int keep2 = 0;

    char decision;
    int exit = 0;
    int exit2 = 0;

    printf("You got --> [Dice 1]: %d [Dice 2]: %d [Dice 3]: %d\n",dice1,dice2,dice3);

    while(!exit)
    {
        printf("Shall I roll for you (Y/N)? ");
        scanf(" %c",&decision);

        if (decision == 'Y')
        {

            while(!exit2)
            {
                printf("Which ones do you want to keep? ");
                scanf(" %d %d",&keep1, &keep2);
                if ((keep1 >= 1 && keep1 <= 3) && (keep2 >= 1 && keep2 <= 3))
                {
                    if(keep1 == 1 && keep2 == 2)
                    {
                        dice3 = roll_a_die();
                    }
                    else if(keep1 == 1 && keep2 == 3)
                    {
                        dice2 = roll_a_die();
                    }
                    else if(keep1 == 2 && keep2 == 3)
                    {
                        dice1 = roll_a_die();
                    }
                    exit2 = 1;
                    exit = 1;
                }
                else
                {
                    printf("Invalid input! Please enter two numbers between 1 and 3.\n");
                }
            }
        }
        else if (decision == 'N')
        {
            printf("You decided not to roll again.\n");
            exit = 1;
        }
        else
        {
            printf("Sorry, I don't understand!\n");
        }

    }

    printf("You got --> [Dice 1]: %d [Dice 2]: %d [Dice 3]: %d\n",dice1,dice2,dice3);
    int round_score = scoresheet(dice1, dice2, dice3);

    return round_score;
}

int starter(){    // To determine the starter.
    int exit = 0;
    int starter;

    while(!exit)
    {
        int computerDice = roll_a_die();
        int playerDice = roll_a_die();

        printf("\nI have rolled the dice and got %d!\n",computerDice);
        printf("I have rolled the dice for you and you got %d!\n",playerDice);

        if (computerDice > playerDice)
        {
            starter = 0;
            exit = 1;
        }else if (computerDice < playerDice)
        {
            starter = 1;
            exit = 1;
        }
        else{
            printf("We are draw. I'll roll the dice again.\n");
            exit = 0;
        }
    }

    return starter;
}


int main()
{
    srand(time(0));
    int round;
    int compTotalScore = 0;
    int userTotalScore = 0;
    int round_score;
    int starterMain;

    printf("Welcome to Crag game.\n Let\'s get started!\n");
    printf("How many rounds would you like to play? ");
    scanf("%d",&round);

    starterMain = starter();

    for(int i=1; i<=round; i++)
    {
        if(starterMain == 0)
        {

            printf("\n----------Round %d My Turn---------------- \n",i);
            round_score = play_computer();
            compTotalScore += round_score;
            printf("My score: %d Total score: %d", round_score, compTotalScore);

            printf("\n----------Round %d Your Turn---------------- \n",i);
            round_score = play_user();
            userTotalScore += round_score;
            printf("Your score: %d Total score: %d", round_score, userTotalScore);

        }
        else
        {

            printf("\n----------Round %d Your Turn---------------- \n",i);
            round_score = play_user();
            userTotalScore += round_score;
            printf("Your score: %d Total score: %d\n", round_score, userTotalScore);

            printf("\n----------Round %d My Turn---------------- \n",i);
            round_score = play_computer();
            compTotalScore += round_score;
            printf("My score: %d Total score: %d\n", round_score, compTotalScore);

        }

        printf("\n\n------------------------Our scoresheet after round %d: --------------------------------\n",i);
        printf("My Score : %d\t Your Score : %d\n", compTotalScore,userTotalScore);

    }

    //This is the part that determines the end of the game.
    if(compTotalScore>userTotalScore)
    {
        printf("\nI AM THE WINNER!");
    }else if(compTotalScore==userTotalScore)
    {
        printf("\nWE ARE DRAW.");
    }
    else
    {
        printf("\nYOU ARE THE WINNER!");
    }

    return 0;
}