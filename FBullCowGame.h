/*
 * Models, contains the variables that will be used by controller
 * no user interaction
 */

#include <string>

using  FString = std::string;
using int32 = int;

struct FBullCowCount {
    int32 Bulls = 0;
    int32 Cows = 0;
};

enum class EGuessStatus{
    OK,
    Invalid_Status,
    Not_Isogram,
    Not_Lowercase,
    Wrong_Lenght
};

enum class EResetStatus{
    No_Hidden_Word,
    OK
};

class FBullCOwGame{
public:
    FBullCOwGame();
    int32 GetMaxTries() const;
    int32 GetCurrentTry() const;
    int32 GetLengthHidden() const;
    bool Won() const;

    void Reset();

    EGuessStatus ValidGuess(FString) const;
    FBullCowCount SubmitValidGuess(FString);

private:
    int32 CurrentTry;
    int32 MaxTries;
    FString HiddenWord;
    bool IsWon;

    bool IsIsogram(FString) const;
    bool IsLower(FString) const;
};