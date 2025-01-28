#include "EstDxgiStatsStatics.h"
//#include "DynamicRHI.h"
#include "RHICommandList.h"
#include "RHIDefinitions.h"
#include "ID3D12DynamicRHI.h"
#include "Templates/RefCounting.h"

#include "Windows/AllowWindowsPlatformTypes.h"
THIRD_PARTY_INCLUDES_START
#include <D3D11.h>
#include <dxgi1_4.h>
THIRD_PARTY_INCLUDES_END
#include "Windows/HideWindowsPlatformTypes.h"

FEstGraphicsAdapterInformation UEstDxgiStatsStatics::GetActiveGraphicsAdapterInformation()
{
    DXGI_ADAPTER_DESC adapterDescription;
    IDXGIAdapter3* adapter = GetActiveGraphicsAdapter(&adapterDescription);

    DXGI_QUERY_VIDEO_MEMORY_INFO videoMemoryInfo;
    adapter->QueryVideoMemoryInfo(0, DXGI_MEMORY_SEGMENT_GROUP_LOCAL, &videoMemoryInfo);

    FEstGraphicsAdapterInformation result;
    result.Description = FString(adapterDescription.Description);
    result.TotalGpuMemoryBytes = adapterDescription.DedicatedVideoMemory;
    result.AvaialableGpuMemoryBytes = videoMemoryInfo.Budget;
    result.UsedGpuMemoryBytes = videoMemoryInfo.CurrentUsage;
    return result;
}

IDXGIAdapter3* UEstDxgiStatsStatics::GetActiveGraphicsAdapter(DXGI_ADAPTER_DESC* adapterDescription)
{
    ID3D12Device* D3D11Device = static_cast<ID3D12Device*>(GDynamicRHI->RHIGetNativeDevice());

    LUID AdapterLuid = D3D11Device->GetAdapterLuid();

    IDXGIFactory4* pFactory;
    CreateDXGIFactory1(__uuidof(IDXGIFactory4), (void**)&pFactory);

    int32 i = 0;
    IDXGIAdapter3* adapter;
    while (pFactory->EnumAdapters(i, reinterpret_cast<IDXGIAdapter**>(&adapter)) != DXGI_ERROR_NOT_FOUND)
    {
        i++;
        adapter->GetDesc(adapterDescription);
        if (adapterDescription->AdapterLuid.HighPart == AdapterLuid.HighPart &&
            adapterDescription->AdapterLuid.LowPart == AdapterLuid.LowPart)
        {
            return adapter;
        }
    }

    return nullptr;
}
