// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h" 

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    SetupGame();
    EndGame();

    //Debug line
    PrintLine(TEXT("The HiddenWord is %s.\nIt is %i chars long."), *HiddenWord,
        HiddenWord.Len());

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
        if (Input == HiddenWord)
        {
            PrintLine(TEXT("You Win"));
            EndGame();
        }
        else
        {
            --Lives;
            if (Lives > 0)
            {
                if (Input.Len() != HiddenWord.Len())
                {
                    PrintLine(TEXT("Sorry,try again! You have %i lives remaining"), Lives);
                }
            }
        }
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
    PrintLine(TEXT("Press Enter to play again"));
}