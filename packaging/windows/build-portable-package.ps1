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

function Resolve-RepoPath([string] $RelativePath) {
    return [System.IO.Path]::GetFullPath((Join-Path $repo_root $RelativePath))
}

function Find-FirstExistingPath([string[]] $Paths) {
    foreach ($path in $Paths) {
        if ($path -and (Test-Path -LiteralPath $path)) {
            return (Resolve-Path -LiteralPath $path).Path
        }
    }
    return $null
}

function Assert-InsidePath([string] $Path, [string] $Parent) {
    $full_path = [System.IO.Path]::GetFullPath($Path).TrimEnd('\')
    $full_parent = [System.IO.Path]::GetFullPath($Parent).TrimEnd('\')
    if (-not $full_path.StartsWith($full_parent + '\', [System.StringComparison]::OrdinalIgnoreCase) -and
        -not $full_path.Equals($full_parent, [System.StringComparison]::OrdinalIgnoreCase)) {
        throw "Ruta fuera del directorio esperado: $full_path"
    }
}

function Copy-DirectoryContents([string] $Source, [string] $Destination) {
    if (-not (Test-Path -LiteralPath $Source)) {
        throw "No existe la carpeta requerida: $Source"
    }

    New-Item -ItemType Directory -Force -Path $Destination | Out-Null

    & robocopy $Source $Destination /E /COPY:DAT /DCOPY:DAT /R:2 /W:1 /NFL /NDL /NJH /NJS /NP
    $robocopy_exit = $LASTEXITCODE

    if ($robocopy_exit -ge 8) {
        throw "Robocopy fallo copiando '$Source' a '$Destination' con codigo $robocopy_exit."
    }
}

function Get-DllImports([string] $BinaryPath) {
    $output = & $objdump -p $BinaryPath 2>$null
    foreach ($line in $output) {
        if ($line -match "DLL Name:\s*(.+)$") {
            $matches[1].Trim()
        }
    }
}

function Test-SystemDll([string] $DllName) {
    $lower = $DllName.ToLowerInvariant()
    if ($lower -like "api-ms-win-*.dll") {
        return $true
    }
    return $system_dlls.Contains($lower)
}

function Find-Dll([string] $DllName) {
    foreach ($dir in $dll_search_dirs) {
        $candidate = Join-Path $dir $DllName
        if (Test-Path -LiteralPath $candidate) {
            return (Resolve-Path -LiteralPath $candidate).Path
        }
    }
    return $null
}

function Add-BinaryToQueue([System.Collections.Queue] $Queue, [string] $Path) {
    if (Test-Path -LiteralPath $Path) {
        $Queue.Enqueue((Resolve-Path -LiteralPath $Path).Path)
    }
}

function Append-FileToStream([System.IO.Stream] $OutputStream, [string] $Path) {
    $input_stream = [System.IO.File]::OpenRead($Path)
    try {
        $input_stream.CopyTo($OutputStream)
    }
    finally {
        $input_stream.Dispose()
    }
}

$repo_root = [System.IO.Path]::GetFullPath((Join-Path $PSScriptRoot "..\.."))
$build_path = Resolve-RepoPath $BuildDir
$output_root_path = Resolve-RepoPath $OutputRoot
$release_path = Resolve-RepoPath $ReleaseDir
$portable_dir = Join-Path $output_root_path "JW_QET_Portable"
$exe_path = Join-Path $build_path "qelectrotech.exe"
$launcher_source = Join-Path $repo_root "packaging\windows\run-qelectrotech-portable.bat"

Assert-InsidePath $output_root_path $repo_root
Assert-InsidePath $release_path $repo_root
Assert-InsidePath $portable_dir $output_root_path

if (-not (Test-Path -LiteralPath $exe_path)) {
    throw "No existe qelectrotech.exe. Compile primero el proyecto en: $build_path"
}
if (-not (Test-Path -LiteralPath $launcher_source)) {
    throw "No existe el launcher portable: $launcher_source"
}

if (-not $SevenZip) {
    $SevenZip = Find-FirstExistingPath @(
        "C:\Program Files\7-Zip\7z.exe",
        "C:\Program Files (x86)\7-Zip\7z.exe",
        "C:\msys64\ucrt64\bin\7z.exe",
        "C:\msys64\usr\bin\7z.exe"
    )
}
if (-not $SevenZip) {
    throw "No se encontro 7-Zip. Ejecute setup-jw-qet-dev-environment.bat o pase -SevenZip <ruta a 7z.exe>."
}

if (-not $SfxModule) {
    $SfxModule = Find-FirstExistingPath @(
        "C:\Program Files\7-Zip\7z.sfx",
        "C:\Program Files (x86)\7-Zip\7z.sfx"
    )
}
if ((-not $NoSfx) -and (-not $SfxModule)) {
    throw "No se encontro 7z.sfx. Instale 7-Zip para Windows o use -NoSfx para generar solo .7z."
}

$windeployqt = Find-FirstExistingPath @(
    "C:\msys64\ucrt64\bin\windeployqt-qt5.exe",
    "C:\msys64\ucrt64\bin\windeployqt.exe"
)
if (-not $windeployqt) {
    throw "No se encontro windeployqt de Qt/MSYS2."
}

$objdump = Find-FirstExistingPath @(
    "C:\msys64\ucrt64\bin\objdump.exe",
    "C:\msys64\usr\bin\objdump.exe"
)
if (-not $objdump) {
    throw "No se encontro objdump para resolver dependencias DLL."
}

New-Item -ItemType Directory -Force -Path $output_root_path | Out-Null
New-Item -ItemType Directory -Force -Path $release_path | Out-Null

if (Test-Path -LiteralPath $portable_dir) {
    Remove-Item -LiteralPath $portable_dir -Recurse -Force
}
New-Item -ItemType Directory -Force -Path $portable_dir | Out-Null

Copy-Item -LiteralPath $exe_path -Destination (Join-Path $portable_dir "qelectrotech.exe") -Force
Copy-Item -LiteralPath $launcher_source -Destination (Join-Path $portable_dir "run-qelectrotech.bat") -Force

Copy-DirectoryContents (Join-Path $repo_root "elements") (Join-Path $portable_dir "elements")
Copy-DirectoryContents (Join-Path $repo_root "titleblocks") (Join-Path $portable_dir "titleblocks")
Copy-DirectoryContents (Join-Path $repo_root "lang") (Join-Path $portable_dir "lang")
Copy-DirectoryContents (Join-Path $repo_root "fonts") (Join-Path $portable_dir "fonts")

if (Test-Path -LiteralPath (Join-Path $repo_root "docs\collaboration")) {
    Copy-DirectoryContents (Join-Path $repo_root "docs\collaboration") (Join-Path $portable_dir "docs\collaboration")
}
if (Test-Path -LiteralPath (Join-Path $repo_root "tools")) {
    Copy-DirectoryContents (Join-Path $repo_root "tools") (Join-Path $portable_dir "tools")
}

& $windeployqt --compiler-runtime --force --no-angle --no-opengl-sw --ignore-library-errors --dir $portable_dir (Join-Path $portable_dir "qelectrotech.exe")
if ($LASTEXITCODE -ne 0) {
    throw "windeployqt fallo con codigo $LASTEXITCODE"
}

$sql_driver_dir = Join-Path $portable_dir "sqldrivers"
if (Test-Path -LiteralPath $sql_driver_dir) {
    Get-ChildItem -LiteralPath $sql_driver_dir -Filter "qsql*.dll" |
        Where-Object { $_.Name -ne "qsqlite.dll" } |
        Remove-Item -Force
}

$system_dlls = [System.Collections.Generic.HashSet[string]]::new([System.StringComparer]::OrdinalIgnoreCase)
@(
    "advapi32.dll", "bcrypt.dll", "combase.dll", "comctl32.dll", "comdlg32.dll",
    "crypt32.dll", "d3d11.dll", "dnsapi.dll", "dwmapi.dll", "dwrite.dll", "dxgi.dll", "gdi32.dll",
    "gdi32full.dll", "imm32.dll", "kernel32.dll", "kernelbase.dll", "mpr.dll",
    "msvcp_win.dll", "msvcrt.dll", "netapi32.dll", "ntdll.dll", "ole32.dll",
    "oleaut32.dll", "opengl32.dll", "odbc32.dll", "powrprof.dll", "rpcrt4.dll", "sechost.dll",
    "shell32.dll", "shlwapi.dll", "user32.dll", "userenv.dll", "uxtheme.dll",
    "usp10.dll", "version.dll", "win32u.dll", "winmm.dll", "winspool.drv", "ws2_32.dll",
    "wtsapi32.dll", "iphlpapi.dll"
) | ForEach-Object { [void] $system_dlls.Add($_) }

$dll_search_dirs = @(
    $portable_dir,
    $build_path,
    "C:\msys64\ucrt64\bin",
    "C:\msys64\usr\bin"
)

$queue = [System.Collections.Queue]::new()
Get-ChildItem -LiteralPath $portable_dir -Recurse -File |
    Where-Object { $_.Extension -in ".exe", ".dll" } |
    ForEach-Object { Add-BinaryToQueue $queue $_.FullName }

$processed = [System.Collections.Generic.HashSet[string]]::new([System.StringComparer]::OrdinalIgnoreCase)
$missing = [System.Collections.Generic.HashSet[string]]::new([System.StringComparer]::OrdinalIgnoreCase)
$copied = [System.Collections.Generic.List[string]]::new()

while ($queue.Count -gt 0) {
    $binary = [string] $queue.Dequeue()
    if (-not $processed.Add($binary)) {
        continue
    }

    foreach ($dll in Get-DllImports $binary) {
        if (Test-SystemDll $dll) {
            continue
        }

        $target = Join-Path $portable_dir $dll
        if (Test-Path -LiteralPath $target) {
            Add-BinaryToQueue $queue $target
            continue
        }

        $source = Find-Dll $dll
        if ($source) {
            Copy-Item -LiteralPath $source -Destination $target -Force
            $copied.Add($dll) | Out-Null
            Add-BinaryToQueue $queue $target
        }
        else {
            $missing.Add($dll) | Out-Null
        }
    }
}

if ($missing.Count -gt 0) {
    Write-Warning ("DLL no resueltas: " + (($missing | Sort-Object) -join ", "))
}

$archive_path = Join-Path $release_path "JW-QET-Portable.7z"
$sfx_path = Join-Path $release_path "JW-QET-Portable.exe"
$hash_path = Join-Path $release_path "SHA256SUMS.txt"
$config_path = Join-Path $output_root_path "sfx-config.txt"

foreach ($old_file in @($archive_path, $sfx_path, $hash_path, $config_path)) {
    if (Test-Path -LiteralPath $old_file) {
        Remove-Item -LiteralPath $old_file -Force
    }
}

Push-Location $portable_dir
try {
    & $SevenZip a -t7z $archive_path ".\*" -mx=7 -mmt=on
    if ($LASTEXITCODE -ne 0) {
        throw "7-Zip fallo al crear $archive_path con codigo $LASTEXITCODE"
    }
}
finally {
    Pop-Location
}

if (-not $NoSfx) {
    $config = @"
;!@Install@!UTF-8!
Title="JW QET Portable"
BeginPrompt="Instalar o actualizar JW QET Portable y abrir QElectroTech?"
InstallPath="%LOCALAPPDATA%\\JWControl\\JW_QET_Portable"
RunProgram="run-qelectrotech.bat"
GUIMode="2"
OverwriteMode="2"
;!@InstallEnd@!
"@
    [System.IO.File]::WriteAllText($config_path, $config, [System.Text.UTF8Encoding]::new($false))

    $output_stream = [System.IO.File]::Create($sfx_path)
    try {
        Append-FileToStream $output_stream $SfxModule
        Append-FileToStream $output_stream $config_path
        Append-FileToStream $output_stream $archive_path
    }
    finally {
        $output_stream.Dispose()
    }

    Remove-Item -LiteralPath $config_path -Force
}

$hash_lines = [System.Collections.Generic.List[string]]::new()
$archive_hash = (Get-FileHash -LiteralPath $archive_path -Algorithm SHA256).Hash.ToLowerInvariant()
$hash_lines.Add("$archive_hash  $([System.IO.Path]::GetFileName($archive_path))") | Out-Null

if (-not $NoSfx) {
    $sfx_hash = (Get-FileHash -LiteralPath $sfx_path -Algorithm SHA256).Hash.ToLowerInvariant()
    $hash_lines.Add("$sfx_hash  $([System.IO.Path]::GetFileName($sfx_path))") | Out-Null
}

[System.IO.File]::WriteAllLines($hash_path, $hash_lines, [System.Text.UTF8Encoding]::new($false))

Write-Host "Archivo 7z generado en: $archive_path"
if (-not $NoSfx) {
    Write-Host "Ejecutable generado en: $sfx_path"
}
Write-Host "Hashes SHA256 en: $hash_path"

if ($copied.Count -gt 0) {
    Write-Host ("DLL copiadas por resolucion recursiva: " + (($copied | Sort-Object -Unique) -join ", "))
}

if ($KeepStage) {
    Write-Host "Staging conservado en: $portable_dir"
}
else {
    Remove-Item -LiteralPath $portable_dir -Recurse -Force
    Write-Host "Staging temporal eliminado: $portable_dir"
}
