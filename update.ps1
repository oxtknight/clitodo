<#$scriptPath = Split-Path -Parent $MyInvocation.MyCommand.Definition
$repoPath = "$scriptPath\repo"
if (-not (Test-Path $sourcePath)){
    Write-Host "source repo not found. please clone to $sourcePath" -ForegroundColor Red
    exit
}
Set-Location $sourcePath
Write-Host "Updating source via Git..." -ForegroundColor Cyan
git pull origin main

Write-Host "Re-compiling..." -ForegroundColor Cyan
gcc source.code/clitodo.c -lm -o clitodo.exe
if ($LASTEXITCODE -eq 0){
    Write-Host "Installing update..." -ForegroundColor Green 
    $currentExe = (Get-Command clitodo.exe).Source
    Start-Sleep -Seconds 1
    Move-Item -Path .\clitodo.exe -Destination $currentExe -Force
    Write-Host "Done! Run 'clitodo' to see the changes." -ForegroundColor Green
    }
    #>
$homeDir = $env:USERPROFILE
$repoPath = "$homeDir\.clitodo\repo"
if (-not (Test-Path $repoPath)){
    Write-Host "Source repo not found at $repoPath" -ForegroundColor Red
    exit
}
Set-Location $repoPath
Write-Host "Updating source via Git..." -ForegroundColor Cyan
git pull origin main
Write-Host "Re-compiling..." -ForegroundColor Cyan
gcc source.code/clitodo.c -o clitodo.exe

if ($LASTEXITCODE -eq 0){
    Write-Host "Installing update..." -ForegroundColor Green 
    $currentExe = (Get-Command clitodo.exe).Source
    Start-Sleep -Seconds 2
    Move-Item -Path .\clitodo.exe -Destination $currentExe -Force
    Write-Host "Done! Run 'clitodo' to see the changes." -ForegroundColor Green
} else {
    Write-Host "Compilation failed!" -ForegroundColor Red
}
