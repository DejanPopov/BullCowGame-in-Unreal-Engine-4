// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h" 

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    PrintLine(TEXT("Hello there!"));
    PrintLine(TEXT("Guess the 4 letter word")); //Number is hardcoded REMOVE latter!
    PrintLine(TEXT("Press Enter to continue..."));

    SetupGame();
   
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();

    HiddenWord.Len(); 

    if (Input == HiddenWord)
    {
        PrintLine(TEXT("You Win"));
    }
    else
    {
        if (Input.Len() != HiddenWord.Len())
        {
            PrintLine(TEXT("Hidden word is 4 characters long,try again"));
        }
        PrintLine(TEXT("You Lose!"));
    }

}

void UBullCowCartridge::SetupGame()
{
    HiddenWord = TEXT("cake");
    Lives = 4 ;
}