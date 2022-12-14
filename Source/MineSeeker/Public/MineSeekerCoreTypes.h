#pragma once

#include "GameFramework/PlayerController.h"
#include "MineSeekerCoreTypes.generated.h"

UENUM(BlueprintType)
enum class EMatchState : uint8
{
    None = 0,
    WaitingToStart,
    GameOver,
    InProgress,
    Pause,
    Win,
    Settings
    
};

UENUM(BlueprintType)
enum class EGameDifficulty : uint8
{
    Easy,
    Medium,
    Hard,
    Custom
};

//-------------------Custom Delegates-----------------------------------------------
DECLARE_MULTICAST_DELEGATE_OneParam(FOnMatchStateChangedSignature, EMatchState);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnFullGridUpdateNeededSignature, bool bNeeded);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnOpenCellsSignature, TArray<int32>);

USTRUCT(BlueprintType)
struct FCellData
{

    GENERATED_USTRUCT_BODY()

    bool bClosed = true;
    bool bHasMine = false;
    bool MarkedAsMine = false;
    int32 CellRowIndex =0;
    int32 CellColumnIndex=0;
    int32 ArrayIndex =0;
    int32 NumberOfNearMines =0;
};

USTRUCT(BlueprintType)
struct FMinesData
{

    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Mines Data", meta = (ClampMin = "9", ClampMax = "24"))
    int32 RowsNumber = 10;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Mines Data", meta = (ClampMin = "9", ClampMax = "30"))
    int32 ColumnsNumber = 10;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Mines Data", meta = (ClampMin = "9", ClampMax = "252"))
    int32 MinesNumber = 10;
};