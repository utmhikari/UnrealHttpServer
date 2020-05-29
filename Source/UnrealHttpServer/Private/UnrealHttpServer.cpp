// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "UnrealHttpServer.h"
#include "WebServer.h"


#define LOCTEXT_NAMESPACE "FUnrealHttpServerModule"

void FUnrealHttpServerModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	UnrealHttpServer::FWebServer::Stop();
	if (!GIsEditor)
	{
		Port = DEFAULT_PORT;
		UnrealHttpServer::FWebServer::Start(Port);
	}
}

void FUnrealHttpServerModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that supporWt dynamic reloading,
	// we call this function before unloading the module.
	UnrealHttpServer::FWebServer::Stop();
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FUnrealHttpServerModule, UnrealHttpServer)