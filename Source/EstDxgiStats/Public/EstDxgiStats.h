#pragma once

#include "Modules/ModuleInterface.h"

class ESTDXGISTATS_API FEstDxgiStatsModule : public IModuleInterface
{
public:
	virtual void StartupModule();
	virtual void ShutdownModule();
	static class IDXGIAdapter3* GetActiveGraphicsAdapter();
private:
	inline static class IDXGIAdapter3* ActiveGraphicsAdapter;
	inline static class IDXGIFactory4* DxgiFactory;
};
