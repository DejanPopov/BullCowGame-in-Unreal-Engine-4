// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h" 

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    SetupGame();

    //Debug line
    PrintLine(TEXT("The HiddenWord is %s.\nIt is %i chars long."), *HiddenWord,
        HiddenWord.Len());

    PrintLine(TEXT("Hello there!"));
    PrintLine(TEXT("Guess the %i letter word"), HiddenWord.Len()); //Number is hardcoded REMOVE latter!
    PrintLine(TEXT("Type in your guess and press Enter to continue..."));
    
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
            PrintLine(TEXT("Hidden word is %i characters long,try again")
            , HiddenWord.Len());
        }
        PrintLine(TEXT("You Lose!"));
    }

}

void UBullCowCartridge::SetupGame()
{
    HiddenWord = TEXT("cake");
    Lives = 4 ;
}