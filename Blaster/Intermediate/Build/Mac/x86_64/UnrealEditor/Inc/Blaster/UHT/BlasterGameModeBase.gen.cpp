// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Blaster/BlasterGameModeBase.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeBlasterGameModeBase() {}
// Cross Module References
	BLASTER_API UClass* Z_Construct_UClass_ABlasterGameModeBase();
	BLASTER_API UClass* Z_Construct_UClass_ABlasterGameModeBase_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_Blaster();
// End Cross Module References
	void ABlasterGameModeBase::StaticRegisterNativesABlasterGameModeBase()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ABlasterGameModeBase);
	UClass* Z_Construct_UClass_ABlasterGameModeBase_NoRegister()
	{
		return ABlasterGameModeBase::StaticClass();
	}
	struct Z_Construct_UClass_ABlasterGameModeBase_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ABlasterGameModeBase_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_Blaster,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ABlasterGameModeBase_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "BlasterGameModeBase.h" },
		{ "ModuleRelativePath", "BlasterGameModeBase.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ABlasterGameModeBase_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ABlasterGameModeBase>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ABlasterGameModeBase_Statics::ClassParams = {
		&ABlasterGameModeBase::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009002ACu,
		METADATA_PARAMS(Z_Construct_UClass_ABlasterGameModeBase_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ABlasterGameModeBase_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ABlasterGameModeBase()
	{
		if (!Z_Registration_Info_UClass_ABlasterGameModeBase.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ABlasterGameModeBase.OuterSingleton, Z_Construct_UClass_ABlasterGameModeBase_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ABlasterGameModeBase.OuterSingleton;
	}
	template<> BLASTER_API UClass* StaticClass<ABlasterGameModeBase>()
	{
		return ABlasterGameModeBase::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ABlasterGameModeBase);
	ABlasterGameModeBase::~ABlasterGameModeBase() {}
	struct Z_CompiledInDeferFile_FID_alexandrkrotov_dev_UE_MultiplayerCourse_multiplayer_game_blaster_Blaster_Source_Blaster_BlasterGameModeBase_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_alexandrkrotov_dev_UE_MultiplayerCourse_multiplayer_game_blaster_Blaster_Source_Blaster_BlasterGameModeBase_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ABlasterGameModeBase, ABlasterGameModeBase::StaticClass, TEXT("ABlasterGameModeBase"), &Z_Registration_Info_UClass_ABlasterGameModeBase, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ABlasterGameModeBase), 1554009261U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_alexandrkrotov_dev_UE_MultiplayerCourse_multiplayer_game_blaster_Blaster_Source_Blaster_BlasterGameModeBase_h_247214700(TEXT("/Script/Blaster"),
		Z_CompiledInDeferFile_FID_alexandrkrotov_dev_UE_MultiplayerCourse_multiplayer_game_blaster_Blaster_Source_Blaster_BlasterGameModeBase_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_alexandrkrotov_dev_UE_MultiplayerCourse_multiplayer_game_blaster_Blaster_Source_Blaster_BlasterGameModeBase_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
