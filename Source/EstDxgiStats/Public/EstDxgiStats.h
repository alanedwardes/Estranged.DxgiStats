#pragma once

#include "Modules/ModuleInterface.h"

class ESTDXGISTATS_API FEstDxgiStatsModule : public IModuleInterface
{
public:
	virtual void StartupModule();
	virtual void ShutdownModule();
};
