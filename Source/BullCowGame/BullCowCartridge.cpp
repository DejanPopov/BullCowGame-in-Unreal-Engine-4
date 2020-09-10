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

    HiddenWord = TEXT("cake");
    Lives = HiddenWord.Len();
    bGameOver = false;

    PrintLine(TEXT("Guess the %i letter word"), HiddenWord.Len()); //Number is hardcoded REMOVE latter!
    PrintLine(TEXT("Type in your guess. \npress Enter to continue..."));
    PrintLine(TEXT("You have %i lives left"), Lives);

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

   // if (!IsIsogram)
  //  {
  //      PrintLine(TEXT("No repeating letters,guess again!"));
   // }

    if (Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("The hidden word is %i leeters long"), HiddenWord.Len());
        PrintLine(TEXT("Sorry,try again! You have %i lives remaining"), Lives);
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
    
