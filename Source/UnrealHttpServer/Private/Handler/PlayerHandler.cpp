#include "Handler/PlayerHandler.h"
#include "Log.h"
#include "Util/WebUtil.h"
#include "Service/PlayerService.h"
#include "Runtime/JsonUtilities/Public/JsonObjectConverter.h"
#include "GameFramework/Pawn.h"

namespace UnrealHttpServer
{
	TUniquePtr<FHttpServerResponse> FPlayerHandler::GetPlayerLocation(const FHttpServerRequest& Request)
	{
		APawn* PlayerPawn = FPlayerService::GetPlayerPawn();
		if (PlayerPawn == nullptr)
		{
			return FWebUtil::ErrorResponse(TEXT("Failed to get valid player pawn instance!"));
		}
		FVector PlayerLocation = PlayerPawn->GetActorLocation();
		TSharedPtr<FJsonObject> Body = MakeShareable(new FJsonObject());
		Body->SetNumberField(TEXT("x"), PlayerLocation.X);
		Body->SetNumberField(TEXT("y"), PlayerLocation.Y);
		Body->SetNumberField(TEXT("z"), PlayerLocation.Z);
		return FWebUtil::SuccessResponse(Body);
	}

	TUniquePtr<FHttpServerResponse> FPlayerHandler::SetPlayerLocation(const FHttpServerRequest& Request)
	{
		// get request json and player pawn
		TSharedPtr<FJsonObject> RequestBody = FWebUtil::GetRequestJsonBody(Request);
		if (RequestBody == nullptr)
		{
			return FWebUtil::ErrorResponse(TEXT("Failed to parse request body to json!"));
		}
		APawn* PlayerPawn = FPlayerService::GetPlayerPawn();
		if (PlayerPawn == nullptr)
		{
			return FWebUtil::ErrorResponse(TEXT("Failed to get valid player pawn instance!"));
		}
		// set new location
		FVector NewLocation;
		NewLocation.X = RequestBody->GetNumberField(TEXT("x"));
		NewLocation.Y = RequestBody->GetNumberField(TEXT("y"));
		NewLocation.Z = RequestBody->GetNumberField(TEXT("z"));
		UE_LOG(UHttpLog, Log, TEXT("Set player new location to (%.2f, %.2f, %.2f)"), NewLocation.X, NewLocation.Y, NewLocation.Z);
		if (!PlayerPawn->SetActorLocation(NewLocation, false, nullptr, ETeleportType::ResetPhysics))
		{
			return FWebUtil::ErrorResponse(TEXT("Failed to set player location!"));
		}
		return FWebUtil::SuccessResponse(TEXT("Player location set successfully!"));
	}

	TUniquePtr<FHttpServerResponse> FPlayerHandler::GetPlayerRotation(const FHttpServerRequest& Request)
	{
		APawn* PlayerPawn = FPlayerService::GetPlayerPawn();
		if (PlayerPawn == nullptr)
		{
			return FWebUtil::ErrorResponse(TEXT("Failed to get valid player pawn instance!"));
		}
		FRotator PlayerRotation = PlayerPawn->GetActorRotation();
		TSharedPtr<FJsonObject> Body = MakeShareable(new FJsonObject());
		Body->SetNumberField(TEXT("pitch"), PlayerRotation.Pitch);
		Body->SetNumberField(TEXT("yaw"), PlayerRotation.Yaw);
		Body->SetNumberField(TEXT("roll"), PlayerRotation.Roll);
		return FWebUtil::SuccessResponse(Body);
	}

	TUniquePtr<FHttpServerResponse> FPlayerHandler::SetPlayerRotation(const FHttpServerRequest& Request)
	{
		// get request json and player pawn
		TSharedPtr<FJsonObject> RequestBody = FWebUtil::GetRequestJsonBody(Request);
		if (RequestBody == nullptr)
		{
			return FWebUtil::ErrorResponse(TEXT("Failed to parse request body to json!"));
		}
		APawn* PlayerPawn = FPlayerService::GetPlayerPawn();
		if (PlayerPawn == nullptr)
		{
			return FWebUtil::ErrorResponse(TEXT("Failed to get valid player pawn instance!"));
		}
		// set new rotation
		FRotator NewRotation;
		NewRotation.Pitch = RequestBody->GetNumberField("pitch");
		NewRotation.Yaw = RequestBody->GetNumberField("yaw");
		NewRotation.Roll = RequestBody->GetNumberField("roll");
		UE_LOG(UHttpLog, Log, TEXT("Set player new rotation to (pitch: %.2f, yaw: %.2f, roll: %.2f)"), NewRotation.Pitch, NewRotation.Yaw, NewRotation.Roll);
		if (!PlayerPawn->SetActorRotation(NewRotation, ETeleportType::ResetPhysics))
		{
			return FWebUtil::ErrorResponse(TEXT("Failed to set player rotation!"));
		}
		return FWebUtil::SuccessResponse(TEXT("Player rotation set successfully!"));
	}
}