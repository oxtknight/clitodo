$scriptPath = Split-Path -Parent $MyInvocation.MyCommand.Definition
$soucePath = "$scriptPath\repo"
if (-not (Test-Path $sourcePath)){
    Write-Host "source repo not found. please clone to $sourcePath" -ForegroundColor Red
    exit
}
Set-Location $sourcePath
Write-Host "Updating source via Git..." -ForegroundColor Cyan
git pull origin main

Write-Host "Re-compiling..." -ForegroundColor Cyan
gcc souce.code/clitodo.c -lm -o clitodo.exe
if ($LASTEXITCODE -eq 0){
    Write-Host "Installing update..." -ForegroundColor Green 
    $currentExe = (Get-Command clitodo.exe).Source
    Start-Sleep -Seconds 1
    Move-Item -Path .\clitodo.exe -Destination $currentExe -Force
    Write-Host "Done! Run 'clitodo' to see the changes." -ForegroundColor Green
    }
