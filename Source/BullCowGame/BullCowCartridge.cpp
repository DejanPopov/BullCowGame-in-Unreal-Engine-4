// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h" 
#include "HiddenWordList.h"


void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    Isograms = GetValidWords(Words); 

    SetupGame();
    
}

void UBullCowCartridge::OnInput(const FString& PlayerInput) // When the player hits enter
{
    if (bGameOver)      
    {
        ClearScreen();
        SetupGame();
    }
    else
    {   
        ProcessGuess(PlayerInput);
    }
}

void UBullCowCartridge::SetupGame()
{
    //Welcoming Player
    PrintLine(TEXT("Welcome to BullCow game"));

    HiddenWord = Isograms[FMath::RandRange(0,Isograms.Num() - 1)];
    Lives = HiddenWord.Len() * 2;
    bGameOver = false;

    PrintLine(TEXT("Guess the %i letter word"), HiddenWord.Len()); //Number is hardcoded REMOVE latter!
    PrintLine(TEXT("Type in your guess. \npress Enter to continue..."));
    PrintLine(TEXT("You have %i lives left"), Lives);
    //Debug line
  // PrintLine(TEXT("The HiddenWord is %s.\nIt is %i chars long."), *HiddenWord,
 //     HiddenWord.Len());
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("\nPress Enter to play again"));
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
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
    
    FBullCowCount Score = GetBullCows(Guess);
    PrintLine(TEXT("You have %i Bulls and %i Cows"), Score.Bulls, Score.Cows);

    PrintLine(TEXT("Guess again, you have %i lives left"), Lives);
}

bool UBullCowCartridge::IsIsogram(const FString& Word) const
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

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const
{
    TArray<FString> ValidWords;
    
    for (FString Word : WordList)
    {
        if (Word.Len() >= 4 && Word.Len() <= 8 && IsIsogram(Word))
        {
            ValidWords.Emplace(Word);
        }
    
    }
    return ValidWords;
}

FBullCowCount UBullCowCartridge::GetBullCows(const FString& Guess) const
{
    FBullCowCount Count;

    for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
    {
        if (Guess[GuessIndex] == HiddenWord[GuessIndex])
        {
            Count.Bulls++;
            continue;
        }

        for (int32 HiddenIndex = 0; HiddenIndex < HiddenWord.Len(); HiddenIndex++)
        {
            if (Guess[GuessIndex] == HiddenWord[HiddenIndex])
            {
                Count.Cows++;
            }

        }
    }
    return Count;
}