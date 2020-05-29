#include "PlayerService.h"
#include "Log.h"
#include "Engine.h"


namespace UnrealHttpServer
{
	/* ================= Public Methods ==================== */

	APawn* FPlayerService::GetPlayerPawn()
	{
		if (GEngine == nullptr)
		{
			UE_LOG(UHttpLog, Warning, TEXT("Cannot find GEngine!"));
			return nullptr;
		}
		auto WorldContexts = GEngine->GetWorldContexts();
		if (WorldContexts.Num() == 0)
		{
			UE_LOG(UHttpLog, Warning, TEXT("No world context!"));
			return nullptr;
		}
		auto World = WorldContexts[0].World();
		if (World == nullptr)
		{
			UE_LOG(UHttpLog, Warning, TEXT("No current world!"));
			return nullptr;
		}
		auto FirstPlayerController = World->GetFirstPlayerController();
		if (FirstPlayerController == nullptr)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Failed to get first player controller!"));
			return nullptr;
		}
		auto PlayerPawn = FirstPlayerController->GetPawn();
		if (PlayerPawn == nullptr)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Player is not a pawn or not under control!"));
		}
		return PlayerPawn;
	}
}