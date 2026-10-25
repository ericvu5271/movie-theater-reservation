#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_ROWS 9
#define MAX_COLS 9
#define TICKET_LIMIT 4

void FillMovieTheater(char MovieTheater[][MAX_COLS], int rows, int seats, char fileLine[])
{
    int index = 0;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < seats; j++)
        {
            MovieTheater[i][j] = fileLine[index];
            index++;
        }
    }
}

void PrintSeatMap(char MovieTheater[][MAX_COLS], int rows, int seats)
{
    printf("\n       ");

    for (int j = 1; j <= seats; j++)
    {
        printf(" Seat %d", j);
    }     
    printf("\n");

    for (int i = 0; i < rows; i++)
    {
        printf("Row %c  ", 'A' + i);
        for (int j = 0; j < seats; j++)
        {
            printf("%7c", MovieTheater[i][j]);
        }    
        printf("\n");
    }
}

int IsSeatSold(char MovieTheater[][MAX_COLS], int rows, int seats)
{
    int seatSold;
    
    if(MovieTheater[rows][seats] == 'X')
    {
        seatSold = 1;
    }
    else
    {
        seatSold = 0;
        MovieTheater[rows][seats] = 'X';
    }
    
    return seatSold;
}

void WriteMovieTheater(char MovieTheater[][MAX_COLS], int rows, int seats)
{
    char outputFileName[100];
    FILE *outFile = {};

    printf("\nEnter output file name: ");
    scanf("%s", outputFileName);

    outFile = fopen(outputFileName, "w+");
    if (outFile == NULL)
    {
        printf("File did not open...exiting\n");
        exit(0);
    }

    fprintf(outFile, "%d %d\n", rows, seats);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < seats; j++)
        {
            fprintf(outFile, "%c", MovieTheater[i][j]);
        }
    }
    fprintf(outFile, "\n");

    fclose(outFile);
}

int main(void)
{
    int ticketsPurchased;
    int ticketsSold = 0;
    int arrayRow, arrayCol;
    int numberRows, numberSeats;
    char rowLetter;
    int seatNumber;

    char MovieTheater[MAX_ROWS][MAX_COLS];
    char fileLine[MAX_ROWS * MAX_COLS + 1];
    char inputFileName[100];
    FILE *inFile = {};

    printf("Enter the name of your Movie Theater file ");
    scanf("%s", inputFileName);

    inFile = fopen(inputFileName, "r");
    if (inFile == NULL)
    {
        printf("File did not open...exiting\n");
        exit(0);
    }

    fscanf(inFile, "%d %d", &numberRows, &numberSeats);
    fscanf(inFile, "%s", fileLine);

    fclose(inFile);

    FillMovieTheater(MovieTheater, numberRows, numberSeats, fileLine);

    printf("How many tickets would you like to purchase?  (limit %d) ", TICKET_LIMIT);
    scanf("%d", &ticketsPurchased);

    while (ticketsPurchased < 0 || ticketsPurchased > TICKET_LIMIT)
    {
        printf("This is a special showing - limit of %d tickets per purchase ", TICKET_LIMIT);
        printf("\nHow many tickets would you like to purchase?  (limit %d) ", TICKET_LIMIT);
        scanf("%d", &ticketsPurchased);
    }

    if (ticketsPurchased == 0)
    {
        printf("No movie for you!\n");
    }
    else
    {
        while (ticketsSold < ticketsPurchased)
        {
            PrintSeatMap(MovieTheater, numberRows, numberSeats);

            printf("\nEnter seat choice by entering the row and seat");
            printf("\nPlease pick a seat ");
            scanf(" %c%d", &rowLetter, &seatNumber);

            rowLetter = toupper(rowLetter);

            arrayRow = rowLetter - 'A';
            arrayCol = seatNumber - 1;

            if (arrayRow < 0 || arrayRow >= numberRows || arrayCol < 0 || arrayCol >= numberSeats)
            {
                printf("That seat is not in this theater!!\n");
            }
            else if (IsSeatSold(MovieTheater, arrayRow, arrayCol))
            {
                printf("Seat %c%d has already been sold. Pick a different seat.\n", rowLetter, seatNumber);
            }
            else
            {
                ticketsSold++;
            }
        }

        printf("\nPlease find your way to your seats using this map...\n");
        PrintSeatMap(MovieTheater, numberRows, numberSeats);

        WriteMovieTheater(MovieTheater, numberRows, numberSeats);

        printf("\nEnjoy your movie!\n");
    }

    return 0;
}
