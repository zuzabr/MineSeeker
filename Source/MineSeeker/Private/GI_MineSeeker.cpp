// Fill out your copyright notice in the Description page of Project Settings.


#include "GI_MineSeeker.h"


// ќбща€ функци€ по созданию массива €чеек и выставлению в ней информации
void UGI_MineSeeker::CreateCellsData()
{
	FillTheGrid();
	SetMines();
	CheckForMinesNearby();
}

void UGI_MineSeeker::FillTheGrid()
{
	CellsData.Empty();
	
	const auto Rows = GameSettings.RowsNumber;
	const auto Columns = GameSettings.ColumnsNumber;

	CellsData.SetNum(Rows * Columns);
	return;
}

void UGI_MineSeeker::SetMines()
{
	const auto MinesNumber = GameSettings.MinesNumber;
	if (MinesNumber >= CellsData.Num()) return;

	for (int32 i = 0; i < MinesNumber; ++i)
	{
		int32 CellIndex =	FMath::RandRange(0, CellsData.Num()-1);
		if (!CellsData.IsValidIndex(CellIndex) || CellsData[CellIndex].bHasMine)
		{
			if (i > 0)
			{
				--i;
				continue;
			}
			
		}

		if (!CellsData[CellIndex].bHasMine)
		{
			CellsData[CellIndex].bHasMine = true;
		}
			
	}
	
}

void UGI_MineSeeker::CheckForMinesNearby()
{
	const auto ColumnsNumber = GameSettings.ColumnsNumber;
	
	for (int32 i = 0; i < CellsData.Num(); ++i)
	{
		int32 NumberOfMinesNearby = 0;
		
		int32 Row = i / ColumnsNumber;
		int32 Column = i% ColumnsNumber;
	
	//----------- Set the Column and Row Indexes For Grid-------------
		
		CellsData[i].CellColumnIndex = Column;
		CellsData[i].CellRowIndex = Row;

	//-----------Calculate the number of mines------------------------
		if (CellsData[i].bHasMine) { continue; }
	
	//------------------------Maybe Change Once------------------------
		if (CellsData.IsValidIndex(i + 1) && !((i+1)% ColumnsNumber==0) && CellsData[i + 1].bHasMine) { ++NumberOfMinesNearby; }
		if (CellsData.IsValidIndex(i - 1) && !(i % ColumnsNumber == 0) && CellsData[i - 1].bHasMine) { ++NumberOfMinesNearby; }
		if (CellsData.IsValidIndex(i - ColumnsNumber - 1) && !(i % ColumnsNumber == 0) && CellsData[i - ColumnsNumber - 1].bHasMine)
		{ ++NumberOfMinesNearby; }
		if (CellsData.IsValidIndex(i - ColumnsNumber + 1) && !(i+1 % ColumnsNumber == 0) && CellsData[i - ColumnsNumber + 1].bHasMine)
		{++NumberOfMinesNearby;}
		if (CellsData.IsValidIndex(i + ColumnsNumber + 1) && !(i + 1 % ColumnsNumber == 0) && CellsData[i + ColumnsNumber + 1].bHasMine)
		{++NumberOfMinesNearby;}
		if (CellsData.IsValidIndex(i + ColumnsNumber - 1) && !(i % ColumnsNumber == 0) && CellsData[i + ColumnsNumber - 1].bHasMine)
		{++NumberOfMinesNearby;}
		if (CellsData.IsValidIndex(i + ColumnsNumber) && CellsData[i + ColumnsNumber].bHasMine)
		{++NumberOfMinesNearby;}
		if (CellsData.IsValidIndex(i - ColumnsNumber) && CellsData[i - ColumnsNumber].bHasMine)
		{++NumberOfMinesNearby;}

		CellsData[i].NumberOfNearMines = NumberOfMinesNearby;
	}

	return;
}



