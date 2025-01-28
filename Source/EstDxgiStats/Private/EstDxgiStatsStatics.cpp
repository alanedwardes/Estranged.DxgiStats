#include "EstDxgiStatsStatics.h"
#include "EstDxgiStats.h"
#include "ID3D12DynamicRHI.h"

FEstGraphicsAdapterInformation UEstDxgiStatsStatics::GetActiveGraphicsAdapterInformation()
{
    IDXGIAdapter3* adapter = FEstDxgiStatsModule::GetActiveGraphicsAdapter();
    if (adapter == nullptr)
    {
        return FEstGraphicsAdapterInformation();
    }

    DXGI_ADAPTER_DESC adapterDescription;
    adapter->GetDesc(&adapterDescription);

    DXGI_QUERY_VIDEO_MEMORY_INFO videoMemoryInfo;
    adapter->QueryVideoMemoryInfo(0, DXGI_MEMORY_SEGMENT_GROUP_LOCAL, &videoMemoryInfo);

    FEstGraphicsAdapterInformation result;
    result.Description = FString(adapterDescription.Description);
    result.TotalGpuMemoryBytes = adapterDescription.DedicatedVideoMemory;
    result.AvailableGpuMemoryBytes = videoMemoryInfo.Budget;
    result.UsedGpuMemoryBytes = videoMemoryInfo.CurrentUsage;
    return result;
}
