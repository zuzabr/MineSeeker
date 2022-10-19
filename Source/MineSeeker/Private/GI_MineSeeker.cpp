// Fill out your copyright notice in the Description page of Project Settings.


#include "GI_MineSeeker.h"


// Общая функция по созданию массива ячеек и выставлению в ней информации
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
	const auto Rows = GameSettings.RowsNumber;
	const auto Columns = GameSettings.ColumnsNumber;

	if (MinesNumber >= Rows*Columns) return;
	
	for (int32 i = 0; i < MinesNumber;) 
	{
		int32 CellIndex = FMath::RandRange(0, (Rows * Columns) - 1);
		if (CellsData.IsValidIndex(CellIndex) && !(CellsData[CellIndex].bHasMine))
		{

			CellsData[CellIndex].bHasMine = true;
			++i;
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
		
		CellsData[i].ArrayIndex = i;
		CellsData[i].CellColumnIndex = Column;
		CellsData[i].CellRowIndex = Row;

	//-----------Calculate the number of mines------------------------------------
		if (CellsData[i].bHasMine) { continue; }
	
	//------------------------Maybe Change Once-----------------------------------
		
		for (int32& Index : GetNearbyCellIndexes(i)) // Индекс уже идет значением
		{
			if (CellsData[Index].bHasMine)
			{
					++NumberOfMinesNearby;
			}
		}

		CellsData[i].NumberOfNearMines = NumberOfMinesNearby;
	}

	return;
}

TArray<int32> UGI_MineSeeker::GetNearbyCellIndexes(int32 ArrayIndex)
{
	NearbyCellIndexes.Empty();
	const auto ColumnsNumber = GameSettings.ColumnsNumber;
	int32 Row = ArrayIndex / ColumnsNumber;
	int32 Column = ArrayIndex % ColumnsNumber;
	
	if (CellsData.IsValidIndex(ArrayIndex + 1) && !((ArrayIndex + 1) % ColumnsNumber == 0)) { NearbyCellIndexes.Add(ArrayIndex + 1); }
	if (CellsData.IsValidIndex(ArrayIndex - 1) && !(ArrayIndex % ColumnsNumber == 0)) { NearbyCellIndexes.Add(ArrayIndex - 1); }
	if (CellsData.IsValidIndex(ArrayIndex - ColumnsNumber - 1) && !(ArrayIndex % ColumnsNumber == 0)){ NearbyCellIndexes.Add(ArrayIndex - ColumnsNumber - 1); }
	if (CellsData.IsValidIndex(ArrayIndex - ColumnsNumber + 1) && !(ArrayIndex + 1 % ColumnsNumber == 0)){ NearbyCellIndexes.Add(ArrayIndex - ColumnsNumber + 1); }
	if (CellsData.IsValidIndex(ArrayIndex + ColumnsNumber + 1) && !(ArrayIndex + 1 % ColumnsNumber == 0)) { NearbyCellIndexes.Add(ArrayIndex + ColumnsNumber + 1); }
	if (CellsData.IsValidIndex(ArrayIndex + ColumnsNumber - 1) && !(ArrayIndex % ColumnsNumber == 0)) { NearbyCellIndexes.Add(ArrayIndex + ColumnsNumber - 1); }
	if (CellsData.IsValidIndex(ArrayIndex + ColumnsNumber)){ NearbyCellIndexes.Add(ArrayIndex + ColumnsNumber); }
	if (CellsData.IsValidIndex(ArrayIndex - ColumnsNumber)){ NearbyCellIndexes.Add(ArrayIndex - ColumnsNumber); }

	return NearbyCellIndexes;
}

//--------------------Автоматически открываются близлежащие клетки--------------------
void UGI_MineSeeker::OpenCellsNearbyAutomatically(int32 ArrayIndex)
{
	OnOpenCells.Broadcast(GetNearbyCellIndexes(ArrayIndex));	
}

//-------------------Не работает!!!----Намеренно открываются близлежащие клетки-------------------------
void UGI_MineSeeker::OpenCellsNearbyIntentionally(int32 ArrayIndex)
{
	
//----------------------Инфу о ячейке надо передавать по ссылке-----------------------------------------------
	int32 Count = 0;

	for (const auto& Index : GetNearbyCellIndexes(ArrayIndex))
	{
		UE_LOG(LogTemp, Warning, TEXT("Mines Count %i"), Count);
		if (CellsData[Index].bClosed && CellsData[Index].MarkedAsMine)
		{
			++Count; 	
		}
	}
	
	const auto NumberOfMinesNearby = CellsData[ArrayIndex].NumberOfNearMines;
	UE_LOG(LogTemp, Warning, TEXT("Number of mines nearby %i"), NumberOfMinesNearby);
	UE_LOG(LogTemp, Warning, TEXT("Number of flags nearby %i"), Count);

	if (NumberOfMinesNearby == Count)
	{
		OnOpenCells.Broadcast(GetNearbyCellIndexes(ArrayIndex));
	}


}

void UGI_MineSeeker::SetCellCloseStatus(int32 ArrayIndex, bool Closed)
{
	CellsData[ArrayIndex].bClosed = Closed;
}

void UGI_MineSeeker::SetCellFlagStatus(int32 ArrayIndex, bool Marked)
{
	CellsData[ArrayIndex].MarkedAsMine = Marked;
}