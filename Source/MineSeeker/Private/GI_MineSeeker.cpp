// Zuzabr Games 2022 All Rights Reserved

#include "GI_MineSeeker.h"

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

    if (MinesNumber >= Rows * Columns) return;

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
        int32 Column = i % ColumnsNumber;

        //----------- Set the Column and Row Indexes For Grid-------------

        CellsData[i].ArrayIndex = i;
        CellsData[i].CellColumnIndex = Column;
        CellsData[i].CellRowIndex = Row;

        //-----------Calculate the number of mines------------------------------------
        if (CellsData[i].bHasMine)
        {
            continue;
        }

        //------------------------Maybe Change Once-----------------------------------

        for (int32& Index : GetNearbyCellIndexes(i))  // Индекс уже идет значением
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

    if (CellsData.IsValidIndex(ArrayIndex + 1) && !((ArrayIndex + 1) % ColumnsNumber == 0))
    {
        NearbyCellIndexes.Add(ArrayIndex + 1);
    }
    if (CellsData.IsValidIndex(ArrayIndex - 1) && !(ArrayIndex % ColumnsNumber == 0))
    {
        NearbyCellIndexes.Add(ArrayIndex - 1);
    }
    if (CellsData.IsValidIndex(ArrayIndex - ColumnsNumber - 1) && !(ArrayIndex % ColumnsNumber == 0))
    {
        NearbyCellIndexes.Add(ArrayIndex - ColumnsNumber - 1);
    }
    if (CellsData.IsValidIndex(ArrayIndex - ColumnsNumber + 1) && !(ArrayIndex + 1 % ColumnsNumber == 0))
    {
        NearbyCellIndexes.Add(ArrayIndex - ColumnsNumber + 1);
    }
    if (CellsData.IsValidIndex(ArrayIndex + ColumnsNumber + 1) && !(ArrayIndex + 1 % ColumnsNumber == 0))
    {
        NearbyCellIndexes.Add(ArrayIndex + ColumnsNumber + 1);
    }
    if (CellsData.IsValidIndex(ArrayIndex + ColumnsNumber - 1) && !(ArrayIndex % ColumnsNumber == 0))
    {
        NearbyCellIndexes.Add(ArrayIndex + ColumnsNumber - 1);
    }
    if (CellsData.IsValidIndex(ArrayIndex + ColumnsNumber))
    {
        NearbyCellIndexes.Add(ArrayIndex + ColumnsNumber);
    }
    if (CellsData.IsValidIndex(ArrayIndex - ColumnsNumber))
    {
        NearbyCellIndexes.Add(ArrayIndex - ColumnsNumber);
    }

    return NearbyCellIndexes;
}

//--------------------Automatically open cells nearby--------------------
void UGI_MineSeeker::OpenCellsNearbyAutomatically(int32 ArrayIndex)
{
    OnOpenCells.Broadcast(GetNearbyCellIndexes(ArrayIndex));
}

//-------------------Intentionally open cells nearby-------------------------
void UGI_MineSeeker::OpenCellsNearbyIntentionally(int32 ArrayIndex)
{
    int32 Count{0};

    for (const auto& Index : GetNearbyCellIndexes(ArrayIndex))
    {

        if (CellsData[Index].bClosed && CellsData[Index].MarkedAsMine)
        {
            ++Count;
        }
    }

    const auto NumberOfMinesNearby = CellsData[ArrayIndex].NumberOfNearMines;

    if (NumberOfMinesNearby == Count)
    {
        OnOpenCells.Broadcast(GetNearbyCellIndexes(ArrayIndex));
    }
}

