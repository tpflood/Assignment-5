// Assignment-5.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include <iostream>
#include <iomanip> 
#include <fstream>
using namespace std;

void DisplayGrid(int Grid[20][20], int MaxRow, int MaxColumn, bool OriginalGrid, int Gen)
{
	int Row, Column;
	int AliveInRow[20];
	int AliveInColumn[20];
	int TotalAlive = 0;

	for (Row = 0; Row < MaxRow; Row++)
	{
		AliveInRow[Row] = 0;
	}

	for (Column = 0; Column < MaxColumn; Column++)
	{
		AliveInColumn[Column] = 0;
	}

	cout << "  01234567890123456789" << endl;
	for (Row = 0; Row < MaxRow; Row++)
	{
		std::cout << std::setw(2) << Row;
		for (Column = 0; Column < MaxColumn; Column++)
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

	if (OriginalGrid)
	{
		cout << "(ORIGINAL GRID) ";
	} 
	else
	{
		cout << endl << "The grid after " << (Gen + 1) << " generations have passed." << endl;
		cout << "(GENERATION #" << (Gen + 1) << ") ";
	}
	cout << "GAME OF LIFE STATISTICS" << endl << endl;
	cout << "Total alive in row 10 = " << AliveInRow[10] << endl;
	cout << "Total alive in col 10 = " << AliveInColumn[10] << endl;
	cout << "Total dead in row 16 = " << (MaxRow - AliveInRow[16]) << endl;
	cout << "Total dead in col 1 = " << (MaxColumn - AliveInColumn[1]) << endl;
	cout << "Total alive = " << TotalAlive << endl;
	cout << "Total dead = " << ((MaxRow * MaxColumn) - TotalAlive) << endl << endl;
	
}

void main(int argc, _TCHAR* argv[])
{
	const int MaxRow = 20;
	const int MaxColumn = 20;
	const int MaxGen = 8;
	bool Temp;
	int Row, Column, Gen, i, j, x, y, NeighborLifeCount;
	int CellType;
	ifstream Bacteria;
	int Grid[MaxRow][MaxColumn];
	int NextGenGrid[MaxRow][MaxColumn];

	for (Row = 0; Row < MaxRow; Row++)
		for (Column = 0; Column < MaxColumn; Column++)
			Grid[Row][Column] = 0;

			

	Bacteria.open("bacteria.txt");
	if (!Bacteria)
	{
		cout << "File not found" << endl;
	}
	else
	{
		while (!Bacteria.eof())
		{
			Bacteria >> Row >> Column;
			if ((Row < MaxRow) && (Column < MaxColumn))
			{
				Grid[Row][Column] = 1;
			}			
		}
	}
	
	DisplayGrid(Grid, MaxRow, MaxColumn, true, -1);

	for (Gen = 0; Gen < MaxGen; Gen++)
	{
		for (Row = 0; Row < MaxRow; Row++)
			for (Column = 0; Column < MaxColumn; Column++)
				NextGenGrid[Row][Column] = 0;

		for (Row = 0; Row < MaxRow; Row++)
		{
			for (Column = 0; Column < MaxColumn; Column++)
			{
				Temp = false;
				if (Row == 2 && Column == 19)
				{
					Temp = true;
				}
				NeighborLifeCount = 0;
				for (i = -1; i < 2; i++)
				{
					for (j = -1; j < 2; j++)
					{
						x = Row + i;
						y = Column + j;
						if (Temp)
						{
							Temp = true;
						}
						if ((i != 0 || j != 0) && (x >= 0) && (x < MaxRow) && (y >= 0) && (y < MaxColumn) && Grid[x][y])
						{
							NeighborLifeCount++;
						}
					}
				}
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
		for (Row = 0; Row < MaxRow; Row++)
			for (Column = 0; Column < MaxColumn; Column++)
				Grid[Row][Column] = NextGenGrid[Row][Column];

		DisplayGrid(Grid, MaxRow, MaxColumn, false, Gen);
		system("PAUSE");
	}
}

