$batch1={
	$ADIR="C:\Users\George.Addison\Documents\Arduino"
	$RDIR="C:\Users\George.Addison\Documents\Repositories\ubo\UboFirmware\deployable"
	if (-not(Test-Path $ADIR)) {
		while (-not(Test-Path $ADIR)) {
			Write-Host 'Enter the full Arduino directory in the following format:'
			Write-Host 'C:\Users\George.Addison\Documents\Arduino'
			$ADIR=Read-Host
			if (-not($ADIR)) {
				$ADIR="notADirectory!"
			}
			if (-not(Test-Path $ADIR)) {
				Write-Host 'Invalid directory!'
			}
		}
	}
	if (-not(Test-Path $RDIR)) {
		$RDIR = (Get-Item -Path ".\" -Verbose).FullName
		Write-Host 'Using: '$RDIR
	}
	if (-not(Test-Path $ADIR\hardware\sparkfun)) {
		Copy-Item $RDIR\utils\hardware $ADIR -recurse
	}
	if (-not(Test-Path $ADIR\libraries)) {
		New-Item -ItemType directory -Path $ADIR\libraries
	}
	Get-ChildItem $RDIR\..\src\platform\lib\ -exclude unverified| `
	ForEach-Object{
		$repoLibPath = $_
		$libPath = Split-Path -leaf $repoLibPath
		$libPath = Join-Path -Path $ADIR\libraries\ -ChildPath $libPath
		if (Test-Path $libPath) {
			Remove-Item -recurse $libPath 
		}
		Copy-Item $repoLibPath $libPath -recurse
	}
	Get-ChildItem $RDIR\..\src\payload\*\lib\* |`
	ForEach-Object{
		$repoLibPath = $_
		$libPath = Split-Path -leaf $repoLibPath
		$libPath = Join-Path -Path $ADIR\libraries\ -ChildPath $libPath
		if (Test-Path $libPath) {
			Remove-Item -recurse $libPath 
		}
		Copy-Item $repoLibPath $libPath -recurse
	}
	if (Test-Path $ADIR\libraries\Cube){Remove-Item -recurse $ADIR\libraries\Cube}
	New-Item -ItemType directory -Path $ADIR\libraries\Cube
	New-Item -ItemType directory -Path $ADIR\libraries\Cube\examples
	New-Item -ItemType directory -Path $ADIR\libraries\Cube\extras
	New-Item -ItemType directory -Path $ADIR\libraries\Cube\src
	Copy-Item $RDIR\utils\lbr\* $ADIR\libraries\Cube
	Copy-Item -Path $RDIR\..\src\platform\* -Destination $ADIR\libraries\Cube\src -Include "*.cpp","*.h"
	Get-ChildItem -Path $RDIR\..\src\payload\*\* -Filter *.cpp | Copy-Item -Destination $ADIR\libraries\Cube\src
	Get-ChildItem -Path $RDIR\..\src\payload\*\* -Filter *.h | Copy-Item -Destination $ADIR\libraries\Cube\src
	New-Item -ItemType directory -Path $ADIR\libraries\Cube\examples\Payload
	New-Item -ItemType directory -Path $ADIR\libraries\Cube\examples\Platform
	Copy-Item -Path $RDIR\..\src\platform\examples\* -Destination $ADIR\libraries\Cube\examples\Platform -recurse -exclude unverified
	Copy-Item -Path $RDIR\..\src\payload\*\examples\* -Destination $ADIR\libraries\Cube\examples\Payload -recurse -exclude unverified
}
$header = "powershell.exe -EncodedCommand "
$header | Out-File -NoNewline -Encoding default C:\Users\George.Addison\Documents\Repositories\ubo\UboFirmware\deployable\makeDeployable.bat
[convert]::ToBase64String([Text.Encoding]::Unicode.GetBytes($batch1)) | Out-File -Append -NoNewline -Encoding default C:\Users\George.Addison\Documents\Repositories\ubo\UboFirmware\deployable\makeDeployable.bat