#include <iostream> //for input and output
#include <random> //for random number generation
#include <vector> //for vectors
#include <sstream> //for string streams





//Card struct that contains a value and a suit
struct Card
{
    int val = 0;
    char suit = ' ';
};

void sortCards(Card hand[], int numCards);

//Function that counts the number of cards in a hand
int countNumCards(Card cards[], int arrayElements)
{
    int numCards = 0;
    for (int i = 0; i<arrayElements; i++)
    {
        if (cards[i].val!=0)
        {
            numCards++;
        }
    }
    return numCards;
}


//Function that converts a suit to a number for comparison
int suitToNum(char suit)
{
    if (suit == 'c')
    {
        return 0;
    }
    else if (suit == 'd')
    {
        return 1;
    }
    else if (suit == 'h')
    {
        return 2;
    }
    else if (suit == 's')
    {
        return 3;
    }
    else
    {
        return -1;
    }
}

//Function that prints a card
void printCard(Card card)
{
    if (card.val == 12)
    {
        std::cout<<"Ace of ";
    }
    else if (card.val == 13)
    {
        std::cout<<"Two of ";
    }
    else if (card.val == 1)
    {
        std::cout<<"Three of ";
    }
    else if (card.val == 2)
    {
        std::cout<<"Four of ";
    }
    else if (card.val == 3)
    {
        std::cout<<"Five of ";
    }
    else if (card.val == 4)
    {
        std::cout<<"Six of ";
    }
    else if (card.val==5)
    {
        std::cout<<"Seven of ";
    }
    else if (card.val == 6)
    {
        std::cout<<"Eight of ";
    }
    else if (card.val == 7)
    {
        std::cout<<"Nine of ";
    }
    else if (card.val == 8)
    {
        std::cout<<"Ten of ";
    }
    else if (card.val == 9)
    {
        std::cout<<"Jack of ";
    }
    else if (card.val == 10)
    {
        std::cout<<"Queen of ";
    }
    else if (card.val == 11)
    {
        std::cout<<"King of ";
    }
    if (card.suit == 'c')
    {
        std::cout<<"Clubs";
    }
    else if (card.suit == 'd')
    {
        std::cout<<"Diamonds";
    }
    else if (card.suit == 'h')
    {
        std::cout<<"Hearts";
    }
    else if (card.suit == 's')
    {
        std::cout<<"Spades";
    }
}

//Function that prints multiple cards
void printCards(Card cards[], int size)
{
    sortCards(cards, size);
    int numCards = countNumCards(cards, size);
    std::cout<<"[";
    for (int i = 0; i<size; i++)
    {
        if (cards[i].val!=0&&cards[i].suit!=' ')
        {
            printCard(cards[i]);
            if (i<numCards-1)
            {
                std::cout<<", ";
            }
        }
    }
    std::cout<<"] \n";
}

//Function that shuffles the deck
void shuffleDeck (Card deck[])
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> dis(0, 51);
    int suitNum = 0;
    int valNum = 1;
    for (int i = 0; i < 51;)
    {
        int random_number = dis(gen);
        if (deck[random_number].val == 0)
        {
            deck[random_number].val = valNum;
            valNum++;
            if (valNum>13)
            {
                valNum = 1;
                suitNum++;
            }
            if (suitNum==0)
            {
                deck[random_number].suit = 'c';
            }
            else if (suitNum==1)
            {
                deck[random_number].suit = 'd';
            }
            else if (suitNum==2)
            {
                deck[random_number].suit = 'h';
            }
            else if (suitNum==3)
            {
                deck[random_number].suit = 's';
            }
            i++;
        }
    }
}


//Function that distributes the cards to the players
void distributeCards(Card deck[], Card playerCards[], Card bot1Cards[], Card bot2Cards[], Card bot3Cards[])
{
    for (int i = 0; i<13; i++)
    {
        playerCards[i] = deck[i];
        bot1Cards[i] = deck[i+13];
        bot2Cards[i] = deck[i+26];
        bot3Cards[i] = deck[i+39];
    }
}


//Function to find the three of clubs
int findThreeOfClubs(Card playerCards[], Card bot1Cards[], Card bot2Cards[], Card bot3Cards[])
{
    for (int i = 0; i<13; i++)
    {
        if (playerCards[i].val == 1 && playerCards[i].suit == 'c')
        {
            return 0;
        }
        else if (bot1Cards[i].val == 1 && bot1Cards[i].suit == 'c')
        {
            return 1;
        }
        else if (bot2Cards[i].val == 1 && bot2Cards[i].suit == 'c')
        {
            return 2;
        }
        else if (bot3Cards[i].val == 1 && bot3Cards[i].suit == 'c')
        {
            return 3;
        }
    }
    return -1;
}


//Function that sorts cards 
void sortCards(Card hand[], int size)
{
    //Finding empty cards and moving them to the back
    int numCards = countNumCards(hand, size);
    for (int i = 0; i<numCards; i++)
    {
        if (hand[i].val == 0)
        {
            for (int j = size -1; j>i; j--)
            {
                if (hand[j].val!=0)
                {
                    hand[i] = hand[j];
                    hand[j].val = 0;
                    hand[j].suit = ' ';
                    break;
                }
            }
        }
    }

    //Sorting the cards
    for (int i = 0; i<numCards-1; i++)
    {
        for (int j = i+1; j<numCards; j++)
        {
            if (hand[j].val<hand[i].val)
            {
                Card temp = hand[i];
                hand[i] = hand[j];
                hand[j] = temp;
            }
            else if (hand[j].val==hand[i].val)
            {
                if (suitToNum(hand[j].suit)<suitToNum(hand[i].suit))
                {
                    Card temp = hand[i];
                    hand[i] = hand[j];
                    hand[j] = temp;
                }
            }
        }
    }

    
    
}

//Function that returns the rank of a hand
int getHandRank(Card hand[])
{
    
    int numCards = 0;
    for (int i = 0; i<5; i++)
    {
        if (hand[i].suit!=' ')
        {
            numCards++;
        }
    }
    if (numCards==1)
    {
        return numCards;
    }
    else if (numCards==2)
    {
        if (hand[0].val==hand[1].val)
        {
            return 2;
        }
        else return 0;
    }
    else if (numCards==5)
    {
        Card tempHand[5];
        for (int i = 0; i < 5; i++) 
        {
            tempHand[i] = hand[i];
        }
        sortCards(tempHand, 5);
        if (tempHand[0].val == tempHand[1].val-1 && tempHand[1].val == tempHand[2].val-1 && tempHand[2].val == tempHand[3].val-1 && tempHand[3].val == tempHand[4].val-1)
        {
            if (tempHand[0].suit==tempHand[1].suit && tempHand[1].suit==tempHand[2].suit && tempHand[2].suit==tempHand[3].suit && tempHand[3].suit==tempHand[4].suit)
            {
                return 7;
            }
            else
            {
                return 3;
            }
        }
        else if (tempHand[0].suit==tempHand[1].suit && tempHand[1].suit==tempHand[2].suit && tempHand[2].suit==tempHand[3].suit && tempHand[3].suit==tempHand[4].suit)
        {
            return 4;
        }
        else if (tempHand[0].val==tempHand[1].val&&tempHand[1].val==tempHand[2].val&&tempHand[3].val==tempHand[4].val||tempHand[0].val==tempHand[1].val&&tempHand[2].val==tempHand[3].val&&tempHand[3].val==tempHand[4].val)
        {
            return 5;
        }
        else if (tempHand[0].val==tempHand[1].val&&tempHand[1].val==tempHand[2].val&&tempHand[2].val==tempHand[3].val||tempHand[1].val==tempHand[2].val&&tempHand[2].val==tempHand[3].val&&tempHand[3].val==tempHand[4].val)
        {
            return 6;
        }
        else return 0;      
    }
    else return 0;
}


//Function that checks if a play is valid
bool isValidPlay(Card currentPlay[], Card previousPlay[])
{
    sortCards(currentPlay, 5);
    sortCards(previousPlay, 5);
    int numCurrentCards = countNumCards(currentPlay, 5);
    int numPreviousCards = countNumCards(previousPlay, 5);
    if (numPreviousCards != numCurrentCards&&numPreviousCards!=0)
    {
        return false;
    }
    else if (getHandRank(currentPlay)<getHandRank(previousPlay)||getHandRank(currentPlay)==0)
    {
        return false;
    }
    else if (getHandRank(currentPlay)==getHandRank(previousPlay))
    {
        if (getHandRank(currentPlay)==3||getHandRank(currentPlay)==4||getHandRank(currentPlay)==7)
        {
            if (currentPlay[4].val<previousPlay[4].val)
            {
                return false;
            }
            else if (currentPlay[4].val==previousPlay[4].val)
            {
                if (suitToNum(currentPlay[4].suit)<suitToNum(previousPlay[4].suit))
                {
                    return false;
                }
                else return true;
            }
            else return true;
        }
        else if (getHandRank(currentPlay)==5)
        {
            if (currentPlay[2].val<previousPlay[2].val)
            {
                return false;
            }
            else return true;
        }
        else if (getHandRank(currentPlay)==6)
        {
            if (currentPlay[2].val<previousPlay[2].val)
            {
                return false;
            }
            else return true;
        }
        else 
        {
            if (currentPlay[0].val<previousPlay[0].val)
            {
                return false;
            }
            else if (currentPlay[0].val==previousPlay[0].val)
            {
                if (suitToNum(currentPlay[0].suit)<suitToNum(previousPlay[0].suit))
                {
                    return false;
                }
                else return true;
            }
            else return true;
        }
    }
    else return true;
}


int findStartingPlayer (bool playerPassed, bool bot1Passed, bool bot2Passed, bool bot3Passed)
{
    if (!playerPassed)
    {
        return 0;
    }
    else if (!bot1Passed)
    {
        return 1;
    }
    else if (!bot2Passed)
    {
        return 2;
    }
    else if (!bot3Passed)
    {
        return 3;
    }
    else return -1;
}

//Function that gets the player's move
std::vector<int> getPlayerMove()
{
    int num;
    std::vector<int> cardsPlayed;
    std::cout<<"Player 1's turn: \nEnter the cards you want to play by inputting their corresponding number in the deck, or input nothing to pass: \n";
    std::string input;
    std::getline(std::cin, input);
    std::stringstream ss(input);
    while (ss>>num)
    {
        cardsPlayed.push_back(num);
    }
    return cardsPlayed;
}


//Function for the player's turn
void playerTurn(Card previousHand[], Card playerCards[], bool &playerPassed)
{
    sortCards(playerCards, 13);
    std::cout<<"Previous hand: ";
    printCards(previousHand, 5);
    std::cout<<"Your hand: ";
    printCards(playerCards, 13);
    Card playingHand[5];
    std::vector<int> cardsPlayed;
    if (playerPassed)
    {
        std::cout<<"Player 1 passed. \n";
        return;
    }
    do
    {
        cardsPlayed = getPlayerMove();
        if (cardsPlayed.size()==0)
        {
            playerPassed = true;
            break;
        }
        for (int i = 0; i<cardsPlayed.size(); i++)
        {
            playingHand[i] = playerCards[cardsPlayed[i]];
        }
        if (!(isValidPlay(playingHand, previousHand)))
        {
            std::cout<<"Invalid play. Please try again. \n";
        }
    } 
    while (!(isValidPlay(playingHand, previousHand)));
    //Setting the previous hand to the current hand
    if (playerPassed)
    {
        std::cout<<"Player 1 passed. \n";
        playerPassed = true;
        std::cout<<playerPassed<<"\n";
        return;
    }
    else
    {
        for (int i = 0; i<5; i++)
        {
            previousHand[i] = playingHand[i];
        }
    }
    //Remove cards from player's hand
    for (int i = 0; i<13; i++)
    {
        for (int j = 0; j<cardsPlayed.size(); j++)
        {
            if (i==cardsPlayed[j])
            {
                playerCards[i].val = 0;
                playerCards[i].suit = ' ';
            }
        }
    }

    //function for moving empty cards to back of players cards
    for (int i = 0; i<13; i++)
    {
        if (playerCards[i].val == 0)
        {
            for (int j = i; j<12; j++)
            {
                playerCards[j] = playerCards[j+1];
            }
            playerCards[12].val = 0;
            playerCards[12].suit = ' ';
        }
    } 
}


//Function for the bot's turn
//For testing purposes, the bot will just play the smallest possible valid hand
void botsTurn(int botNumber, Card previousHand[], Card botCards[], bool &botPassed)
{
    bool breakLoop = false;
    sortCards(botCards, countNumCards(botCards, 13)); 
    Card playingHand[5];
    std::cout<<"Previous hand: ";
    printCards(previousHand, 5);
    if (botPassed)
    {
        std::cout<<"Bot "<<botNumber<<" passed. \n";
        return;
    }
    if (countNumCards(previousHand, 5)==5||countNumCards(previousHand, 5)==0)
    {
        for (int i = 0; i<9; i++)
        {
            for (int j = i+1; j<10; j++)
            {
                for (int k = i+2; k<11; k++)
                {
                    for (int l = i+3; l<12; l++)
                    {
                        for (int m = i+4; m<13; m++)
                        {
                            
                            if (isValidPlay(playingHand, previousHand))
                            {
                                for (int j = 0; j<5; j++)
                                    {
                                        previousHand[j] = playingHand[j];
                                    }
                                botCards[i].val = 0;
                                botCards[i].suit = ' ';
                                botCards[j].val = 0;
                                botCards[j].suit = ' ';
                                botCards[k].val = 0;
                                botCards[k].suit = ' ';
                                botCards[l].val = 0;
                                botCards[l].suit = ' ';
                                botCards[m].val = 0;
                                botCards[m].suit = ' ';
                                std::cout<<"Bot "<<botNumber<<" played: ";
                                sortCards(previousHand, 5);
                                sortCards(playingHand, 5);
                                printCards(playingHand, 5);
                                breakLoop = true;
                                break;
                            }
                        }
                        if (breakLoop)
                        {
                            break;
                        }
                    }
                    if (breakLoop)
                    {
                        break;
                    }
                }
                if (breakLoop)
                {
                    break;
                }
            }
            if (breakLoop)
            {
                break;
            }
        }
    } 
    if ((countNumCards(previousHand, 5)==2||countNumCards(previousHand, 5)==0)&&!breakLoop)
    {
        for (int i = 0; i<12; i++)
        {
            for (int j = i+1; j<13; j++)
            {
                playingHand[0] = botCards[i];
                playingHand[1] = botCards[j];
                if (isValidPlay(playingHand, previousHand))
                {
                    for (int j = 0; j<5; j++)
                    {
                        previousHand[j] = playingHand[j];
                    }
                    botCards[i].val = 0;
                    botCards[i].suit = ' ';
                    botCards[j].val = 0;
                    botCards[j].suit = ' ';
                    std::cout<<"Bot "<<botNumber<<" played: ";
                    sortCards(previousHand, 5);
                    sortCards(playingHand, 5);
                    printCards(playingHand, 5);
                    breakLoop = true;
                    break;
                }
            }
            if (breakLoop)
            {
                break;
            }
        }
    }
    if ((countNumCards(previousHand, 5)==1||countNumCards(previousHand, 5)==0)&&!breakLoop)
    {
        for (int i = 0; i<13; i++)
        {
            playingHand[0] = botCards[i];
            if (isValidPlay(playingHand, previousHand))
            {
                printCards(playingHand, 5);
                for (int j = 0; j<5; j++)
                {
                    previousHand[j] = playingHand[j];
                }
                botCards[i].val = 0;
                botCards[i].suit = ' ';
                sortCards(previousHand, 5);
                sortCards(previousHand, 5);
                std::cout<<"Bot "<<botNumber<<" played: ";
                printCards(playingHand, 5);
                breakLoop = true;
                break;
            }
        }   
    }
    if (!breakLoop)
    {
        std::cout<<"Bot "<<botNumber<<" passed. \n";
        botPassed = true;
    }
}

//Function that counts the number of players that have passed
int countPassed(bool playerPassed, bool bot1Passed, bool bot2Passed, bool bot3Passed)
{
    return playerPassed + bot1Passed + bot2Passed + bot3Passed;
}

//Function that plays a round (A round continues until all players except one have passed)
int playRound(Card playerCards[], Card bot1Cards[], Card bot2Cards[], Card bot3Cards[], int startingPlayer)
{
    
    int turn = startingPlayer;
    Card previousHand[5];
    for (int i = 0; i<5; i++)
    {
        previousHand[i].val = 0;
        previousHand[i].suit = ' ';
    }
    bool playerPassed = false;
    bool bot1Passed = false;
    bool bot2Passed = false;
    bool bot3Passed = false;
    do
    {
        if (turn == 0)
        {
            playerTurn(previousHand, playerCards, playerPassed);
            turn = 1;
        }
        else if (turn == 1)
        {
            botsTurn(1, previousHand, bot1Cards, bot1Passed);
            turn = 2;
        }
        else if (turn == 2)
        {
            botsTurn(2, previousHand, bot2Cards, bot2Passed);
            turn = 3;
        }
        else if (turn == 3)
        {
            botsTurn(3, previousHand, bot3Cards, bot3Passed);
            turn = 0;
        }
        std::cout<<"Players Passed: "<<countPassed(playerPassed, bot1Passed, bot2Passed, bot3Passed)<<"\n";
    } while (countPassed(playerPassed, bot1Passed, bot2Passed, bot3Passed)<3&&countNumCards(playerCards, 13)!=0&&countNumCards(bot1Cards, 13)!=0&&countNumCards(bot2Cards, 13)!=0&&countNumCards(bot3Cards, 13)!=0);    
    if (countPassed(playerPassed, bot1Passed, bot2Passed, bot3Passed) == 3) // This block was added
    {
        // Reset the previous hand if all players pass
        for (int i = 0; i<5; i++)
        {
            previousHand[i].val = 0;
            previousHand[i].suit = ' ';
        }
    } 
    if (countNumCards(playerCards, 13)==0||countNumCards(bot1Cards, 13)==0||countNumCards(bot2Cards, 13)==0||countNumCards(bot3Cards, 13)==0)
    {
        return -1;
    }
    else return findStartingPlayer(playerPassed, bot1Passed, bot2Passed, bot3Passed);
}


//Function that plays the game (A game is defined as a series of rounds which ends when one player has no cards left)
//Games are repeated until the player decides to stop playing
bool playGame(int playerScore, int bot1Score, int bot2Score, int bot3Score)
{
    //Initialize deck and shuffle and distribute cards
    Card deck[52];
    shuffleDeck(deck);
    Card playerCards[13];
    Card bot1Cards[13];
    Card bot2Cards[13];
    Card bot3Cards[13];  
    distributeCards(deck, playerCards, bot1Cards, bot2Cards, bot3Cards);
    int startingPlayer = findThreeOfClubs(playerCards, bot1Cards, bot2Cards, bot3Cards);
    std::cout<<"Starting player: "<<startingPlayer<<"\n";
    while (countNumCards(playerCards,13)>0&&countNumCards(bot1Cards,13)>0&&countNumCards(bot2Cards,13)>0&&countNumCards(bot3Cards,13)>0)
    {
        startingPlayer = playRound(playerCards, bot1Cards, bot2Cards, bot3Cards, startingPlayer);
        if (startingPlayer == -1)
        {
            break;
        }
    }
    if (countNumCards(playerCards, 13)>=13)
    {
        playerScore+=39;
    }
    else if (countNumCards(playerCards,13)>=10)
    {
        playerScore+=2*countNumCards(playerCards,13);
    }
    else 
    {
        playerScore+=countNumCards(playerCards,13);
    }
    if (countNumCards(bot1Cards,13)>=13)
    {
        bot1Score+=39;
    }
    else if (countNumCards(bot1Cards,13)>=10)
    {
        bot1Score+=2*countNumCards(bot1Cards,13);
    }
    else 
    {
        bot1Score+=countNumCards(bot1Cards,13);
    }
    if (countNumCards(bot2Cards,13)>=13)
    {
        bot2Score+=39;
    }
    else if (countNumCards(bot2Cards,13)>=10)
    {
        bot2Score+=2*countNumCards(bot2Cards,13);
    }
    else 
    {
        bot2Score+=countNumCards(bot2Cards,13);
    }
    if (countNumCards(bot3Cards,13)>=13)
    {
        bot3Score+=39;
    }
    else if (countNumCards(bot3Cards,13)>=10)
    {
        bot3Score+=2*countNumCards(bot3Cards,13);
    }
    else 
    {
        bot3Score+=countNumCards(bot3Cards,13);
    }
        

    //Print scores, then ask if the player wants to play again
    std::cout<<"Player 1's score: "<<playerScore<<"\n";
    std::cout<<"Bot 1's score: "<<bot1Score<<"\n";
    std::cout<<"Bot 2's score: "<<bot2Score<<"\n";
    std::cout<<"Bot 3's score: "<<bot3Score<<"\n";
    std::string input;
    std::cout<<"Do you want to play again? (yes or no) \n";
    std::getline(std::cin, input);
    if (input == "yes"||input == "Yes"||input == "YES")
    {
        return playGame(playerScore, bot1Score, bot2Score, bot3Score);
    }
    else
    {
        return false;
    }
}


int main()
{
    int playerScore = 0;
    int bot1Score = 0;
    int bot2Score = 0;
    int bot3Score = 0;
    return playGame(playerScore, bot1Score, bot2Score, bot3Score);
    /*Card testHand1[5];
    Card testHand2[5];
    testHand1[0] = {2, 's'};
    testHand2[0] = {2, 'd'};
    std::cout<<isValidPlay(testHand1, testHand2)<<"\n";
    return 0;*/
}


