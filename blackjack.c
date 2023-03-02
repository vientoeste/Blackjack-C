#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>
int money;
int shuff(int cards[])
{

    int t;
    int i;
    int desk[52];
    for (i = 0; i < 52; i++)
        desk[i] = (i / 13 + 3) * 100 + i % 13 + 1;

    srand((unsigned)time(NULL));
    for (i = 0; i < 52; i++)
    {
        do
        {
            t = rand() % 52;
        } while (desk[t] == 0);
        cards[i] = desk[t];
        desk[t] = 0;
    }
    return 0;
}

int convert_jkq(int a)
{
    if ((a % 100 == 11) || (a % 100 == 12) || (a % 100 == 13)) return (a / 100) * 100 + 10;
    else return a;
}

void pic(int num)
{
    int po_num;
    char const* fl[4];
    fl[0] = "◆";
    fl[1] = "♠";
    fl[2] = "♥";
    fl[3] = "♣";

    int suit = rand() % 4;

    setlocale(LC_ALL, " "); //Output Unicode
    po_num = num % 100;


    switch (po_num)
    {
    case 1:
    {
        printf("*******\n");
        printf("*     *\n");
        printf("* %s  *\n", fl[suit]);
        printf("*   A *\n");
        printf("*     *\n");
        printf("*******\n");
        break;
    }
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    {
        printf("*******\n");
        printf("*     *\n");
        printf("* %s  *\n", fl[suit]);
        printf("*  %2d *\n", po_num);
        printf("*     *\n");
        printf("*******\n");
        break;
    }
    case 11:
    {
        printf("*******\n");
        printf("*     *\n");
        printf("* %s  *\n", fl[suit]);
        printf("*   J *\n");
        printf("*     *\n");
        printf("*******\n");
        break;
    }
    case 12:
    {
        printf("*******\n");
        printf("*     *\n");
        printf("* %s  *\n", fl[suit]);
        printf("*   Q *\n");
        printf("*     *\n");
        printf("*******\n");
        break;
    }
    case 13:
    {
        printf("*******\n");
        printf("*     *\n");
        printf("* %s  *\n", fl[suit]);
        printf("*   K *\n");
        printf("*     *\n");
        printf("*******\n");
        break;
    }
    }
}

int play(void)
{
    int i;
    int psum = 0;
    int bsum = 0;
    int pcards[5] = { 0 };
    int bcards[5] = { 0 };
    int cards[52];
    char go_on;
    char d;
    int bet;

    printf("\nWelcome to SimpleBlackJack!\n\n"
        "Anytime you can press Ctrl+C to exit.\n"
        "Enjoy! Press Enter to go on......\n\n"
        "How much are you going to bet?: ");
    //while문을 통해 scanf_s에서 정수만 입력받도록 설정
    while (1) {
        if (scanf_s("%d", &bet) == 0) {
            printf("You`ve entered a character\nPlease enter a positive integer value: ");
            rewind(stdin);
        }
        else {
            if (bet > 0) {
                break;
            }
            else {
                printf("You`ve entered negative\nPlease enter a positive integer value: ");
            }
        }
    }

    if (bet > money)
    {
        printf("You don`t have enough money. Please try again.");
        return bet;
    }

    money = money - bet;    //there is no need to cut money separately in the event of defeat because the bet was cut in here
							//betting amount will be provided in the event of a draw, and betting amount will be doubled in the event of a victory
    do {
        go_on = getchar();
    } while (go_on != '\n');
    printf("\n");

    //shuff the cards
    shuff(cards);
    for (int i = 0; i <= 5; i++) {
        printf("%d\n", cards[i]);
    };
    //give the cards
    pcards[0] = cards[0];
    pcards[1] = cards[1];
    bcards[0] = cards[2];
    bcards[1] = cards[3];

    //the 2 cards player get
    printf("One of computer's cards:\n");
    pic(bcards[0]);
    printf("\n");
    printf("Cards of player:\n");
    pic(pcards[0]);
    pic(pcards[1]);

    i = 0;
    for (i = 0; i < 2; i++)
    {
        if (pcards[i] % 100 == 1)
        {
            printf("choose A value of the card %d, input 'y' for 11 or 'n' for 1 :\n", i + 1);
            do {
                d = getchar();
            } while (d != 'y' && d != 'n');

            if (d == 'y')
            {
                printf("You've chosen value 11 for card A.\n");
                psum = psum + 11;
            }
            else if (d == 'n')
            {
                printf("You've chosen value 1 for card A.\n");
                psum = psum + 1;
            }
        }
        else if (convert_jkq(pcards[i]) % 100 == 10) psum = psum + 10;
        else psum = psum + pcards[i] % 100;

        if (psum > 21)
        {
            printf("Sum of player's cards now:%d\n\n", psum);
            printf("Computer win!\n");                //no deduct
            return 1;
        }
        else if (psum == 21)
        {
            printf("Sum of player's cards now:%d\n\n", psum);
            printf("Player win!\n");
            money = money + bet * 2;                //add amount
            return 0;
        }
    }
    printf("Sum of player's cards now:%d\n\n", psum);

    //whether player get another cards
    i = 0;
    for (i = 0; i < 3; i++)
    {
        char j = 'n';
        printf("*******************************Want more cards?*******************************\n");
        printf("*                        Input y or n for more cards                         *\n");
        printf("* Or you can input s for Surrender and you will only lose 50%% from you bet.  *\n");
        printf("*   Or you can input d for Double and you will bet 100%% more from you bet.   *\n");
        printf("******************************************************************************\n");
        do {
            j = getchar();
        } while (j != 'y' && j != 'n' && j != 's' && j != 'd');

        if (j == 'y')
        {
            printf("You've got another card now.\n");
            pcards[i + 2] = cards[i + 4];
            printf("and your card %d is:\n", i + 3);
            pic(pcards[i + 2]);

            if (pcards[i + 2] % 100 == 1)//when ace be chosen
            {
                printf("Choose A value of the card %d, input 'y' for 11 or 'n' for 1:\n", i + 3);
                do {
                    d = getchar();
                } while (d != 'y' && d != 'n');
                if (d == 'y')
                {
                    printf("You've chosen value 11 for card A.\n");
                    psum = psum + 11;
                }
                else if (d == 'n')
                {
                    printf("You've chosen value 1 for card A.\n");
                    psum = psum + 1;
                }

            }
            else if (convert_jkq(pcards[i + 2]) % 100 == 10) psum = psum + 10;
            else psum = psum + pcards[i + 2] % 100;

            if (psum > 21)
            {
                printf("Sum of player's cards now:%d\n\n", psum);
                printf("Computer win!\n");            //no deduct
                return 1;
            }
            else if (psum == 21)
            {
                printf("Sum of player's cards now:%d\n\n", psum);
                printf("Player win!\n");
                money = money + bet * 2;            //add amount
                return 0;
            }
            else printf("Sum of player's cards now:%d\n\n", psum);
        }

        if (j == 'n')
        {
            printf("Sum of player's cards now:%d\n\n", psum);
            break;
        }
        if (j == 's')//서렌더
        {
            //베팅금액 1/2 감소
            printf("Surrender\n");
            printf("Computer win!\n");
            money = money + bet * 0.5;
            return 1;
        }
        if (j == 'd')
        {
            //배팅액 2배로 더걸기
            money = money - bet;
            printf("You've got another card now.\n");
            pcards[i + 2] = cards[i + 4];
            printf("and your card %d is:\n", i + 3);
            pic(pcards[i + 2]);

            if (pcards[i + 2] % 100 == 1)//에이스 선택
            {
                printf("choose A value of the card %d, input 'y' for 11 or 'n' for 1 :\n", i + 1);//에이스 선택
                do {
                    d = getchar();
                } while (d != 'y' && d != 'n');

                if (d == 'y')
                {
                    printf("You've chosen value 11 for card A.\n");
                    psum = psum + 11;
                }
                else if (d == 'n')
                {
                    printf("You've chosen value 1 for card A.\n");
                    psum = psum + 1;
                }

            }

            else if (convert_jkq(pcards[i + 2]) % 100 == 10) psum = psum + 10;
            else psum = psum + pcards[i + 2] % 100;

            if (psum == bsum)
            {
                printf("Sum of player's cards now:%d\n\n", psum);
                printf("Draw!\n");
                money = money + 2 * bet;
                return 3;
            }
            else if (psum > 21)
            {
                printf("Sum of player's cards now:%d\n\n", psum);
                printf("Computer win!\n");            //no deduct
                return 1;
            }
            else if (psum < 21 && psum < bsum && bsum < 22)
            {
                printf("Sum of player's cards now:%d\n\n", psum);
                printf("Computer win!\n");            //no deduct
                return 1;
            }
            else if (psum > bsum && psum <= 21)
            {
                printf("Sum of player's cards now:%d\n\n", psum);
                printf("Player win!\n");
                money = money + bet * 4;            //add amount
                return 0;
            }
            else if (bsum > 21)
            {
                printf("Sum of player's cards now:%d\n\n", psum);
                printf("Player win!\n");
                money = money + bet * 4;            //add amount
                return 0;
            }
            break;
        }
    }
    if (i == 3)
    {
        printf("Player win! Because the sum of your 5 cards is no larger than 21! So lucky!\n");
        money = money + bet * 2;
        return 0;
    }

    //the 2 cards of boss/computer
    //i=0;
    printf("Computer's cards:\n");
    pic(bcards[0]);
    pic(bcards[1]);

    if (bcards[0] % 100 + bcards[1] % 100 == 2)
    {
        bsum = 12; //two A cards
        printf("Sum of computer's cards now:%d\n\n", bsum);
    }
    else if ((convert_jkq(bcards[0])) % 100 + (convert_jkq(bcards[1])) % 100 == 1)
    {
        bsum = 21;
        printf("Sum of computer's cards now:%d\n\n", bsum);
        printf("Computer win!\n");            //No deduct
        return 1;
    }
    else if (bcards[0] % 100 == 1 || bcards[1] % 100 == 1)
    {
        bsum = (bcards[0] + bcards[1]) % 100 + (rand() % 2) * 10;
        printf("Sum of computer's cards now:%d\n\n", bsum);
    }
    else
    {
        bsum = (convert_jkq(bcards[0])) % 100 + (convert_jkq(bcards[1])) % 100;
        printf("Sum of computer's cards now:%d\n\n", bsum);
    }

    //whether computer get another cards until bsum>16
    for (i = 0; i < 3 && bsum < 17; i++)
    {
        bcards[i + 2] = cards[i + 7];
        printf("Computer's card %d is:\n", i + 3);
        pic(bcards[i + 2]);

        if (bcards[i + 2] % 100 == 1)
        {
            if (bsum + 11 <= 21)
            {
                printf("Computer has chosen A as 11\n");
                bsum = bsum + 11;
                printf("Sum of computer's cards now:%d\n\n", bsum);
            }
            else
            {
                printf("Computer has chosen A as 1\n");
                bsum = bsum + 1;
                printf("Sum of computer's cards now:%d\n\n", bsum);
            }
        }
        else
        {
            bsum = bsum + convert_jkq(bcards[i + 2]) % 100;
            printf("Sum of computer's cards now:%d\n\n", bsum);
        }
    }

    if (i == 3)
    {
        printf("Computer win! Because the sum of its 5 cards is no larger than 21! So lucky!\n");
        return 1;
    }

    //the last step
    if (bsum > 21 || psum > bsum)
    {
        printf("Player win!\n");
        money = money + bet * 2;
        return 0;

    }
    else if (psum == bsum)
    {
        printf("Oh, player and computer get the same score!\n");
        money = money + bet;
        return 3;
    }
    else if (psum < bsum)
    {
        printf("Computer win!\n");
        return 1;
    }

    return 3;
}
void play1() {
    char again;
    play();
    //Show the balance after a game, and if there is no game, end the game
    printf("You have %d coin.\n\n", money);
    if (money <= 0) {
        printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
        printf("$   You`ve spent all your money.   $\n");
        printf("$        See you next time!        $\n");
        printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n\n");
        return;
    }
    printf("\nAnd now would you like to play again? Input 'y' or 'n':\n");
    do {
        again = getchar();
    } while (again != 'y' && again != 'n');

    if (again == 'y')
    {
        printf("\nOK, let's go again!\n\n");

        play1();
    }
    printf("\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$");
    printf("\nYou`re taking %d coin! \nSee you next time and have a nice day!\n", money);
    printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
}
int main(void)
{
    printf("Please enter the coin amount to start with: ");

    while (1) {
        if (scanf_s("%d", &money) == 0) {
            printf("You`ve entered a character\nPlease enter a positive integer value: ");
            rewind(stdin);
        }
        else {
            if (money > 0) {
                break;
            }
            else {
                printf("You`ve entered negative\nPlease enter a positive integer value: ");
            }
        }
    }
    play1();

    return 0;
}