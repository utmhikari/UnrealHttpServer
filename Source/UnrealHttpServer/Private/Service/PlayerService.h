#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Controller.h"

namespace UnrealHttpServer
{
	class FPlayerService
	{
	public:
		/**
		 * Get player pawn
		 */
		static APawn* GetPlayerPawn();
	};
}