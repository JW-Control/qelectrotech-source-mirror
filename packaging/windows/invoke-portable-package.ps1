[CmdletBinding()]
param(
    [string] $BuildDir = "build\jw-qet-qt5-nokf",
    [string] $OutputRoot = "build\p",
    [string] $ReleaseDir = "release",
    [string] $SevenZip = "",
    [string] $SfxModule = "",
    [switch] $NoSfx,
    [switch] $KeepStage
)

$ErrorActionPreference = "Stop"

# Some Windows PowerShell installations used in workshop/legacy PCs do not
# expose Get-FileHash even though the rest of the packaging script works.
# Provide a SHA256-compatible fallback so build-portable-package.ps1 can keep
# using the standard Get-FileHash call without depending on a specific host.
if (-not (Get-Command Get-FileHash -ErrorAction SilentlyContinue)) {
    function Get-FileHash {
        [CmdletBinding()]
        param(
            [Parameter(Mandatory = $true)]
            [string] $LiteralPath,

            [string] $Algorithm = "SHA256"
        )

        if ($Algorithm -ne "SHA256") {
            throw "Fallback Get-FileHash solo soporta SHA256."
        }

        $sha256 = [System.Security.Cryptography.SHA256]::Create()
        $stream = [System.IO.File]::OpenRead($LiteralPath)
        try {
            $hash_bytes = $sha256.ComputeHash($stream)
        }
        finally {
            $stream.Dispose()
            $sha256.Dispose()
        }

        $hash_hex = ([System.BitConverter]::ToString($hash_bytes)).Replace("-", "").ToLowerInvariant()
        $result = New-Object PSObject
        Add-Member -InputObject $result -MemberType NoteProperty -Name Algorithm -Value "SHA256"
        Add-Member -InputObject $result -MemberType NoteProperty -Name Hash -Value $hash_hex
        Add-Member -InputObject $result -MemberType NoteProperty -Name Path -Value ([System.IO.Path]::GetFullPath($LiteralPath))
        return $result
    }

    Write-Host "[JW QET] Get-FileHash no disponible; usando fallback SHA256 basado en .NET."
}

$packager = Join-Path $PSScriptRoot "build-portable-package.ps1"
if (-not (Test-Path -LiteralPath $packager)) {
    throw "No se encontro el empaquetador: $packager"
}

$forward = @{
    BuildDir = $BuildDir
    OutputRoot = $OutputRoot
    ReleaseDir = $ReleaseDir
    SevenZip = $SevenZip
    SfxModule = $SfxModule
}
if ($NoSfx) { $forward.NoSfx = $true }
if ($KeepStage) { $forward.KeepStage = $true }

. $packager @forward
