// Assignment-5.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include <iostream>
#include <iomanip> 
#include <fstream>
using namespace std;

// Constants
#define MAXROW 20
#define MAXCOLUMN 20
#define MAXGEN 5

void DisplayFinalGrid(int Grid[MAXROW][MAXCOLUMN], int Gen);

bool InitializeGridFromFile(int Grid[MAXROW][MAXCOLUMN]);

int CountLiveNeighbors(int Grid[MAXROW][MAXCOLUMN], int Row, int Column);

void main()
{
	int Row, Column, Gen, NeighborLifeCount;
	int Grid[MAXROW][MAXCOLUMN] = { 0 };

	if (InitializeGridFromFile(Grid))
	{
		//	DisplayGrid(Grid, true, -1);

		for (Gen = 0; Gen < MAXGEN; Gen++)
		{
			int NextGenGrid[MAXROW][MAXCOLUMN] = { 0 };

			for (Row = 0; Row < MAXROW; Row++)
			{
				for (Column = 0; Column < MAXCOLUMN; Column++)
				{
					NeighborLifeCount = CountLiveNeighbors(Grid, Row, Column);

					if (!Grid[Row][Column])
					{
						if (NeighborLifeCount == 3)
						{
							NextGenGrid[Row][Column]++;
						}
					}
					else if ((NeighborLifeCount == 2) || (NeighborLifeCount == 3))
					{
						NextGenGrid[Row][Column]++;
					}
				}
			}
			for (Row = 0; Row < MAXROW; Row++)
				for (Column = 0; Column < MAXCOLUMN; Column++)
					Grid[Row][Column] = NextGenGrid[Row][Column];

			//		DisplayGrid(Grid, false, Gen);
		}
		DisplayFinalGrid(Grid, Gen);
	}
	
	system("PAUSE");
}

void DisplayFinalGrid(int Grid[MAXROW][MAXCOLUMN], int Gen)
{
	int Row, Column;
	int AliveInRow[MAXROW] = { 0 };
	int AliveInColumn[MAXCOLUMN] = { 0 };
	int TotalAlive = 0;

	cout << endl << "  01234567890123456789" << endl;
	for (Row = 0; Row < MAXROW; Row++)
	{
		std::cout << std::setw(2) << Row;
		for (Column = 0; Column < MAXCOLUMN; Column++)
		{
			if (Grid[Row][Column])
			{
				cout << "*";
				AliveInRow[Row]++;
				AliveInColumn[Column]++;
				TotalAlive++;
			}
			else
			{
				cout << " ";
			}
		}
		cout << endl;
	}

	cout << "GAME OF LIFE STATS ("<< Gen << "th Generation)...check figures listed below.." << endl;
	cout << "Total alive in row 10 = " << AliveInRow[10] << endl;
	cout << "Total alive in col 10 = " << AliveInColumn[10] << endl;
	cout << "Total dead in row 16 = " << (MAXROW - AliveInRow[16]) << endl;
	cout << "Total dead in col 1 = " << (MAXCOLUMN - AliveInColumn[1]) << endl;
	cout << "Total alive = " << TotalAlive << endl;
	cout << "Total dead = " << ((MAXROW * MAXCOLUMN) - TotalAlive) << endl;

}

bool InitializeGridFromFile(int Grid[MAXROW][MAXCOLUMN])
{
	ifstream Bacteria;
	int Row, Column;
	bool Success;

	Bacteria.open("bacteria.txt");
	if (!Bacteria)
	{
		cout << "File not found" << endl;
		Success = false;
	}
	else
	{
		Success = true;
		while (!Bacteria.eof())
		{
			Bacteria >> Row >> Column;
			if ((Row < MAXROW) && (Column < MAXCOLUMN))
			{
				Grid[Row][Column] = 1;
			}
		}
	}
	return (Success);
}

int CountLiveNeighbors(int Grid[MAXROW][MAXCOLUMN], int Row, int Column)
{
	int i, j, x, y;
	int NeighborLifeCount;

	NeighborLifeCount = 0;
	for (i = -1; i < 2; i++)
	{
		for (j = -1; j < 2; j++)
		{
			x = Row + i;
			y = Column + j;
			if ((i != 0 || j != 0) && (x >= 0) && (x < MAXROW) && (y >= 0) && (y < MAXCOLUMN) && Grid[x][y])
			{
				NeighborLifeCount++;
			}
		}
	}
	return(NeighborLifeCount);
}