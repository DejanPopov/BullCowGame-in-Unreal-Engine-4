// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h" 

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    SetupGame();
    EndGame();

    //Debug line
   // PrintLine(TEXT("The HiddenWord is %s.\nIt is %i chars long."), *HiddenWord,
  //     HiddenWord.Len());

}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    if (bGameOver)      
    {
        ClearScreen();
        SetupGame();
    }
    else
    {   
        ProcessGuess(Input);
    }
}

void UBullCowCartridge::SetupGame()
{
    //Welcoming Player
    PrintLine(TEXT("Welcome to BullCow game"));

    HiddenWord = TEXT("cakes ");
    Lives = HiddenWord.Len();
    bGameOver = false;

    PrintLine(TEXT("Guess the %i letter word"), HiddenWord.Len()); //Number is hardcoded REMOVE latter!
    PrintLine(TEXT("Type in your guess. \npress Enter to continue..."));
    PrintLine(TEXT("You have %i lives left"), Lives);
   

   // const TCHAR HW[] = TEXT("cakes");
   // PrintLine(TEXT("Char 1 of the hidden word is %c"), HW[0]);
   // PrintLine(TEXT("Char 4 of the hidden word is %c"), HW[3]);

    IsIsogram(HiddenWord);
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("\nPress Enter to play again"));
}

void UBullCowCartridge::ProcessGuess(FString Guess)
{
    if (Guess == HiddenWord)
    {
        PrintLine(TEXT("You Win"));
        EndGame();
        return;
    }

    if (Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("The hidden word is %i leeters long"), HiddenWord.Len());
        PrintLine(TEXT("Sorry,try again! You have %i lives remaining"), Lives);
        return;
    }

    if (!IsIsogram(Guess))
    {
        PrintLine(TEXT("No repeating letters,guess again!"));
        return;
    }

    PrintLine(TEXT("You have lost a life!"));
    --Lives;

    if (Lives <= 0)
    {
        ClearScreen();
        PrintLine(TEXT("You have no lives left!"));
        PrintLine(TEXT("The hidden word was %s"), *HiddenWord);
        EndGame();
        return;
    }

    PrintLine(TEXT("Guess again, you have %i lives left"), HiddenWord.Len());
}

bool UBullCowCartridge::IsIsogram(FString Word) const
{
    for (int32 Index = 0; Index < Word.Len(); Index++)
    {
        PrintLine(TEXT("%c"), Word[Index]);
    }
    return true;
}
    
