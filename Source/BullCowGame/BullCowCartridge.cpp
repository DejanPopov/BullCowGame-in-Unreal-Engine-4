// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h" 
#include "HiddenWordList.h"


void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    SetupGame();
    
    PrintLine(TEXT("The number of possible words is %i"), Words.Num());
    PrintLine(TEXT("The number of valid words is %i"), GetValidWords(Words).Num());
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
        for (int32 Comparison = Index + 1; Comparison < Word.Len(); Comparison++)
        {
            if (Word[Index] == Word[Comparison])
            {
                return false;
            }
            
        }
    }

    /*int32 Index = 0;
    int32 Comparison = Index = 1;

    for (int32 Index = 0, Comparison = Index +1;Comparison < Word.Len(); Comparison++)
    {
        if (Word[Index] == Word[Comparison])
        {
            return false;
        }
    }

    for (int32 Index = 0; Index < Word.Len(); Index++)
    {
        PrintLine(TEXT("%c"), Word[Index]);
    }
     */
    return true;
}
    
TArray<FString> UBullCowCartridge::GetValidWords(TArray<FString> WordList) const
{
    TArray<FString> ValidWords;
    
    for (int32 Index = 0; Index < Words.Num(); Index++)
    {
        if (Words[Index].Len() >= 4 && Words[Index].Len() <= 8)
        {
            ValidWords.Emplace(Words[Index]);
        }
    
    }
    return ValidWords;
}