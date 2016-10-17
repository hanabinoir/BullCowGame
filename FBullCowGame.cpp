#include <string>
#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using  FString = std::string;
using int32 = int;

FBullCOwGame::FBullCOwGame() { Reset(); }

int32 FBullCOwGame::GetCurrentTry() const { return CurrentTry; }
int32 FBullCOwGame::GetLengthHidden() const { return HiddenWord.length(); }
bool FBullCOwGame::Won() const{ return IsWon; }

// Trace the value of max tries based on the hidden word length
int32 FBullCOwGame::GetMaxTries() const {
    TMap<int32, int32> WordLengthToMaxTries{
            {3,3}, {4,3}, {5,3}, {6,4}, {7,4}, {8,5}
    };
    return WordLengthToMaxTries[HiddenWord.length()];
}

void FBullCOwGame::Reset() {
    constexpr int32 MAX_TRIES = 3;
    const FString HIDDEN_WORD = "trois";

    CurrentTry = 1;
    MaxTries = MAX_TRIES;
    HiddenWord = HIDDEN_WORD;
    IsWon = false;
    return;
}

// Normal status and errors of gues
EGuessStatus FBullCOwGame::ValidGuess(FString Guess) const {
    if(!IsIsogram(Guess)){
        return EGuessStatus::Not_Isogram;
    } else if(!IsLower(Guess)){
        return EGuessStatus::Not_Lowercase;
    } else if(Guess.length() != HiddenWord.length()){
        return EGuessStatus::Wrong_Lenght;
    } else{
        return EGuessStatus ::OK;
    }
}

// Get the validated guess, comes out with results
FBullCowCount FBullCOwGame::SubmitValidGuess(FString Guess) {
    CurrentTry++;
    FBullCowCount bullCowCount;
    int32 LenghtHidden = HiddenWord.length();

    // Compare the letters in guess and hidden word
    for(int32 i = 0; i < LenghtHidden; i++){
        for(int32 j = 0; j < LenghtHidden; j++){
            // Compare the letters
            if(Guess[i] == HiddenWord[j]){
                // Compare the positions
                if(i == j){
                    bullCowCount.Bulls++;
                    break;
                } else{
                    bullCowCount.Cows++;
                }
            }
        }
    }

    // The condition of winning
    if (bullCowCount.Bulls == LenghtHidden){
        IsWon = true;
    } else{
        IsWon = false;
    }

    return bullCowCount;
}

// Determine the repeating letters
bool FBullCOwGame::IsIsogram(FString Word) const {
    //
    if (Word.length() <= 1){ return true;}

    // False by default
    // If a letter repeats, returns true
    TMap<char, bool> LetterSeen;
    for (auto Letter: Word) {
        Letter = tolower(Letter);
        if (LetterSeen[Letter]) {
            return false;
        } else {
            LetterSeen[Letter] = true;
        }
    }
    return true;
}

// Determine the uppercase letters
bool FBullCOwGame::IsLower(FString Word) const {
    for (auto Letter: Word) {
        if(!islower(Letter))
            return false;
        else
            return true;
    }
    return true;
}


