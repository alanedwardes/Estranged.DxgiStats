using UnrealBuildTool;

public class EstDxgiStats : ModuleRules
{
    public EstDxgiStats(ReadOnlyTargetRules Target) : base(Target)
    {
        PrivateDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "RHI" });

        PublicIncludePathModuleNames.AddRange(new string[] { });

        if (Target.IsInPlatformGroup(UnrealPlatformGroup.Windows))
        {
            // Uses DXGI to query GPU hardware
            // This is what will allow us to get GPU usage statistics at runtime
            PublicSystemLibraries.Add("DXGI.lib");

            PrivateDependencyModuleNames.AddRange(new string[]
            {
                "D3D11RHI",
                "D3D12RHI",
            });

            AddEngineThirdPartyPrivateStaticDependencies(Target, "DX11");
            AddEngineThirdPartyPrivateStaticDependencies(Target, "DX12");
        }
    }
}