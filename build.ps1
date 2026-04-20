param(
  [string]$Out = 'build/paciencia.exe',
  [switch]$Raylib,
  [switch]$NoRaylib
)
$ErrorActionPreference = 'Stop'

# Default to Raylib if not explicitly provided
if (-not $PSBoundParameters.ContainsKey('Raylib')) { $Raylib = $true }
if ($NoRaylib) { $Raylib = $false }

New-Item -ItemType Directory -Force -Path (Split-Path -Parent $Out) | Out-Null
Write-Host "Killing any running $(Split-Path -Leaf $Out) (if exists)..." -ForegroundColor DarkGray
try { taskkill /IM (Split-Path -Leaf $Out) /F | Out-Null } catch { }

$incs = @('-Isrc')
$srcs = @(
  'main.cpp',
  'src/menu/menu.cpp',
  'src/fila/fila.cpp',
  'src/pilha/pilha.cpp',
  'src/lista/lista.cpp',
  'src/baralho/baralho.cpp',
  'src/ordenacao/ordenacao.cpp',
  'src/regras/regras.cpp',
  'src/render/render_console.cpp',
  'src/graphics/graphics.cpp'
)

$cxx = 'g++'
$baseFlags = @('-std=c++17','-O2','-Wall','-Wextra','-pedantic','-fno-lto')

if ($Raylib) {
  $baseFlags += '-DUSE_RAYLIB'
  # Ajuste os caminhos abaixo se necessário
  $incs += '-I"C:\msys64\ucrt64\include"'
  $libs = @('-L"C:\msys64\ucrt64\lib"','-lraylib','-lopengl32','-lgdi32','-lwinmm')
} else {
  $libs = @()
}

$cmd = @($cxx) + $baseFlags + $incs + $srcs + @('-o', $Out) + $libs
Write-Host "Building: $($cmd -join ' ')" -ForegroundColor Cyan
& $cxx @baseFlags @incs @srcs -o $Out @libs
if ($LASTEXITCODE -ne 0) {
  Write-Error "Build failed with exit code $LASTEXITCODE"
  exit $LASTEXITCODE
}
Write-Host "Done: $Out" -ForegroundColor Green
