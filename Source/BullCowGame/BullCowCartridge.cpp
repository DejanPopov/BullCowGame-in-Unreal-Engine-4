// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h" 

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    PrintLine(TEXT("Hello there!"));
    PrintLine(TEXT("Guess the 4 letter word")); //Number is hardcoded REMOVE latter!
    PrintLine(TEXT("Press ENter to continue..."));

    InitGame();
   
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();

    if (Input == HiddenWord)
    {
        PrintLine(TEXT("You Win"));
    }
    else
    {
        PrintLine(TEXT("You Lose!"));
    }

}

void UBullCowCartridge::InitGame()
{
    HiddenWord = TEXT("cake");
    Lives = 4 ;
}