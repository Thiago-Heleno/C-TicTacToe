/*
 * Program:    Jogo da Velha 2
 * Author:     Thiago Heleno
 * Date:       2024-08-07
 * Description: Just a game.
 * Version:    1.0
 * License:    MIT License
 */

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#define clrscr() printf("\e[1;1H\e[2J")

void render(int game[3][3], int activePlayer)
{
  // Clears the Screen and print the game to the Terminal

  clrscr();
  printf("Player %d turn: \n", activePlayer);
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      printf("%d ", game[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

int checkWinner(int game[3][3])
{
  // Check if there's a winner

  int p1Diag = 0;
  int p2Diag = 0;
  int p1Diag2 = 0;
  int p2Diag2 = 0;

  // Lines and Columns check
  for (int i = 0; i < 3; i++)
  {
    int p1Line = 0, p1Col = 0;
    int p2Line = 0, p2Col = 0;
    for (int j = 0; j < 3; j++)
    {
      if (game[i][j] == 1)
      {
        p1Line += 1;
      }
      if (game[j][i] == 1)
      {
        p1Col += 1;
      }

      if (game[i][j] == 2)
      {
        p2Line += 1;
      }
      if (game[j][i] == 2)
      {
        p2Col += 1;
      }
    }
    if (p1Line == 3)
    {
      // Winner
      return 1;
    }
    if (p1Col == 3)
    {
      return 1;
    }

    if (p2Line == 3)
    {
      // Winner
      return 2;
    }
    if (p2Col == 3)
    {
      return 2;
    }
  }

  // First Diagonal Check Top to Bottom
  for (int i = 0; i < 3; i++)
  {
    if (game[i][i] == 1)
    {
      p1Diag += 1;
    }
    if (game[i][i] == 2)
    {
      p2Diag += 1;
    }
    if (p1Diag == 3)
    {
      return 1;
    }
    if (p2Diag == 3)
    {
      return 2;
    }
  }

  // Second Diagonal Check Bottom to Top
  int diag2 = 2;
  for (int i = 0; i < 3; i++)
  {
    if (game[i][diag2 - i] == 1)
    {
      p1Diag2 += 1;
    }
    if (game[i][diag2 - i] == 2)
    {
      p2Diag2 += 1;
    }
    if (p1Diag2 == 3)
    {
      return 1;
    }
    if (p2Diag2 == 3)
    {
      return 2;
    }
  }

  return 0;
}

void PvP()
{
  int game[3][3] = {0}, activePlayer = 1, gameOver = 0, chosenX, chosenY, winner = 0, acceptInput = 0;

  while (gameOver == 0)
  {
    render(game, activePlayer);
    winner = checkWinner(game);
    if (winner != 0)
      break;

    while (acceptInput == 0)
    {
      printf("Input (X) (Y): ");
      scanf("%d %d", &chosenX, &chosenY);
      if (game[chosenX][chosenY] == 0)
      {
        game[chosenX][chosenY] = activePlayer;
        acceptInput = 1;
      }
    }

    if (activePlayer == 1)
    {
      activePlayer = 2;
    }
    else
    {
      activePlayer = 1;
    };
    acceptInput = 0;
  }
  printf("\n\n\nPlayer %d Wins!", winner);
}

void PvAI()
{
  int game[3][3] = {0}, activePlayer = 1, gameOver = 0, chosenX, chosenY, winner = 0, acceptInput = 0;

  while (gameOver == 0)
  {
    render(game, activePlayer);
    winner = checkWinner(game);
    if (winner != 0)
      break;

    while (acceptInput == 0)
    {
      if (activePlayer == 1)
      {
        printf("Input (X) (Y): ");
        scanf("%d %d", &chosenX, &chosenY);
        if (game[chosenX][chosenY] == 0)
        {
          game[chosenX][chosenY] = 1;
          acceptInput = 1;
        }
      }
      else
      {
        int randomNumber1 = rand() % 3;
        int randomNumber2 = rand() % 3;
        if (game[randomNumber1][randomNumber2] == 0)
        {
          game[randomNumber1][randomNumber2] = 2;
          acceptInput = 1;
        }
      }
    }

    if (activePlayer == 1)
    {
      activePlayer = 2;
    }
    else
    {
      activePlayer = 1;
    };
    acceptInput = 0;
  }
  printf("\n\n\nPlayer %d Wins!", winner);
}

int main()
{
  srand(time(0));
  int GameMode;
  printf("Choose your game mode:\n1 - PvP\n2 - PvAI\n");
  scanf("%d", &GameMode);
  switch (GameMode)
  {
  case 1:
    PvP();
    break;
  case 2:
    PvAI();
  default:
    break;
  }

  return 0;
}