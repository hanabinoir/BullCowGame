/* Console executable that makes use of the BullCowGame class, the logic
 * view in MVC, for interaction
 * */

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// Unreal friendly variables
using  FText = std::string;
using int32 = int;

void GamePlay();
void PrintIntro();
FText GetGuess();
bool PlayAgain();

FBullCOwGame BCGame;  // instantiate a new game

// Entry of the game
int32 main() {
    bool isPlayAgain;
    do{
        PrintIntro();
        GamePlay();
        if (!BCGame.Won())
            std::cout << "Game Over!\n";
        else
            std::cout << "You Won!\n";
        isPlayAgain = PlayAgain();
        if (!isPlayAgain)
            std::cout << "Thanks for playing!\n";
        else
            std::cout << "Game reset\n";
        std::cout << std::endl;
    }while (isPlayAgain);

    return 0;   // exit the application
}

// Gameplay
void GamePlay() {
    BCGame.Reset();

    int32 MaxTries = BCGame.GetMaxTries();
    std::cout << "Max tries: " << MaxTries << std::endl;

    // loop the num of turns for guessing
    while (!BCGame.Won() && BCGame.GetCurrentTry() <= MaxTries){
        FText Guess = GetGuess();

        FBullCowCount bullCowCount = BCGame.SubmitValidGuess(Guess);
        std::cout << "Bulls = " << bullCowCount.Bulls << std::endl;
        std::cout << "Cows = " << bullCowCount.Cows << std::endl;
        std::cout << std::endl;
    }
}

// Print out introduction
void PrintIntro(){
    // game introduction
    std::cout << "Bulls & Cows!\n";
    std::cout << "Guess the " << BCGame.GetLengthHidden();
    std::cout << " letter isogram\n";
    std::cout << std::endl;
    return;
}

FText GetGuess(){
    FText Guess = "";
    EGuessStatus guessStatus = EGuessStatus::Invalid_Status;
    do{
        // guess from player
        int32 CurrentTry = BCGame.GetCurrentTry();
        std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << ". Enter your guess: ";
        std::getline(std::cin, Guess);

        // check validity
        guessStatus = BCGame.ValidGuess(Guess);

        switch (guessStatus){
            case EGuessStatus::Wrong_Lenght:
                std::cout << "Please enter an " << BCGame.GetLengthHidden() << " letter word.\n";
                break;
            case EGuessStatus::Not_Isogram:
                std::cout << "Please enter a word without repeating letter\n";
                break;
            case EGuessStatus::Not_Lowercase:
                std::cout << "Please enter all lowercase letters.\n";
                break;
            default:
                break;
        }
        std::cout << std::endl;
    } while(guessStatus != EGuessStatus::OK);
    return Guess;
}

bool PlayAgain(){
    std::cout << "Play Again? (y/n): ";
    FText Response = "";
    std::getline(std::cin, Response);

    return (Response[0] == 'y') || (Response[0] == 'Y');
}