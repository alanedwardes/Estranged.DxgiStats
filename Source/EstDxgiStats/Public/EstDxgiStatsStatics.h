#pragma once

#include "EstDxgiStatsStatics.generated.h"

USTRUCT(BlueprintType)
struct ESTDXGISTATS_API FEstGraphicsAdapterInformation
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = DxgiStats)
	FString Description;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = DxgiStats)
	int64 TotalGpuMemoryBytes;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = DxgiStats)
	int64 AvailableGpuMemoryBytes;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = DxgiStats)
	int64 UsedGpuMemoryBytes;
};

UCLASS()
class ESTDXGISTATS_API UEstDxgiStatsStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = DxgiStats)
	static FEstGraphicsAdapterInformation GetActiveGraphicsAdapterInformation();
private:
	static class IDXGIAdapter3* GetActiveGraphicsAdapter(struct DXGI_ADAPTER_DESC* adapterDescription);
};