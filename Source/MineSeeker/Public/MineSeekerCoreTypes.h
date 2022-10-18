#pragma once

#include "GameFramework/PlayerController.h"
#include "MineSeekerCoreTypes.generated.h"

UENUM(BlueprintType)
enum class EMatchState : uint8
{
	None = 0,
	WaitingToStart,
	InProgress,
	Pause,
	GameOver
};


//-----------------------Делегаты-----------------------------------------------

DECLARE_MULTICAST_DELEGATE(FOnRMBClickedSignature);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnMatchStateChangedSignature, EMatchState);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnFullGridUpdateNeededSignature, bool bNeeded);


USTRUCT(BlueprintType)
struct FCellData
{

	GENERATED_USTRUCT_BODY()

	
		bool bClosed = true;
		bool bHasMine;
		int32 CellRowIndex;
		int32 CellColumnIndex;
		int32 NumberOfNearMines;
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