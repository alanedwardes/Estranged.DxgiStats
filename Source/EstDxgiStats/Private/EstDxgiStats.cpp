#include "EstDxgiStats.h"
#include "ID3D12DynamicRHI.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_GAME_MODULE(FEstDxgiStatsModule, EstDxgiStats);

void FEstDxgiStatsModule::StartupModule()
{
}

void FEstDxgiStatsModule::ShutdownModule()
{
    if (ActiveGraphicsAdapter != nullptr)
    {
        ActiveGraphicsAdapter->Release();
    }

    if (DxgiFactory != nullptr)
    {
        DxgiFactory->Release();
    }
}

IDXGIAdapter3* FEstDxgiStatsModule::GetActiveGraphicsAdapter()
{
    if (DxgiFactory == nullptr)
    {
        CreateDXGIFactory1(__uuidof(IDXGIFactory4), (void**)&DxgiFactory);
    }

    if (ActiveGraphicsAdapter == nullptr)
    {
        ID3D12Device* NativeDevice = static_cast<ID3D12Device*>(GDynamicRHI->RHIGetNativeDevice());
        LUID AdapterLuid = NativeDevice->GetAdapterLuid();

        int32 i = 0;
        IDXGIAdapter3* adapter;
        DXGI_ADAPTER_DESC adapterDescription;
        while (DxgiFactory->EnumAdapters(i, reinterpret_cast<IDXGIAdapter**>(&adapter)) != DXGI_ERROR_NOT_FOUND)
        {
            i++;
            adapter->GetDesc(&adapterDescription);
            if (adapterDescription.AdapterLuid.HighPart == AdapterLuid.HighPart &&
                adapterDescription.AdapterLuid.LowPart == AdapterLuid.LowPart)
            {
                ActiveGraphicsAdapter = adapter;
                break;
            }
        }
    }

    return ActiveGraphicsAdapter;
}
