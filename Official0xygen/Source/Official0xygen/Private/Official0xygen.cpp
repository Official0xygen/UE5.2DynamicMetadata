// Copyright Epic Games, Inc. All Rights Reserved.

#include "Official0xygen.h"
#include "Core.h"
#include "Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"

#define LOCTEXT_NAMESPACE "FOfficial0xygenModule"

void FOfficial0xygenModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	// Get the base directory of this plugin
	FString BaseDir = IPluginManager::Get().FindPlugin("Official0xygen")->GetBaseDir();

	// Add on the relative location of the third party dll and load it
	FString LibraryPath;
#if PLATFORM_WINDOWS
	LibraryPath = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/Official0xygenLibrary/UnrealEditor-Official0xygen.dll"));
#endif // PLATFORM_WINDOWS

	OxygenLibraryHandle = !LibraryPath.IsEmpty() ? FPlatformProcess::GetDllHandle(*LibraryPath) : nullptr;

	if (!OxygenLibraryHandle)
	{
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("0xygenBPLibraryError", "Failed to 0xygen BP library"));
	}
	// Uncomment else statement to see a confirmation message if 0xygen Library properly loaded at startup
	/*else {
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("0xygenBPLibraryLoaded", "Loaded 0xygen BP library"));
	}*/
}

void FOfficial0xygenModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	// Free the dll handle
	FPlatformProcess::FreeDllHandle(OxygenLibraryHandle);
	OxygenLibraryHandle = nullptr;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FOfficial0xygenModule, Official0xygen)
