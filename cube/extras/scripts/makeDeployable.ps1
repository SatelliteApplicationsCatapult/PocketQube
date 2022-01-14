# A power shell script to copy the contents of the repository into a format compatible with the Arduino IDE

# Stupid placeholders required to prevent Test-Path throwing a hissy fit.
$ARDUINO_DIRECTORY="notADirectory"
$REPOSITORY_DIRECTORY="notADirectory"

# Hard coded Arduino / repository directories
#$ARDUINO_DIRECTORY="C:\Users\George.Addison\Documents\Arduino_test"
#$REPOSITORY_DIRECTORY="C:Users\George.Addison\Documents\Repositories\ubo\UboFirmware\deployable"
# Uncomment and set for your system to avoid having to manually specify paths every time
# Alternatively, use makeDeployableTerse.ps1 and the corresponding batch file to avoid powershell nonsense
# See wiki

# Requesting local Arduino library / hardware directory if not hard coded
# Without directly accessing this, old versions may not be overwritten
if (-not(Test-Path $ARDUINO_DIRECTORY)) {
	while (-not(Test-Path $ARDUINO_DIRECTORY)) {
		Write-Host 'Please enter the full directory of your Arduino folder in the following format:'
		Write-Host 'C:\Users\George.Addison\Documents\Arduino'
		$ARDUINO_DIRECTORY=Read-Host
		if (-not($ARDUINO_DIRECTORY)) {
			$ARDUINO_DIRECTORY="notADirectory!"
		}
		if (-not(Test-Path $ARDUINO_DIRECTORY)) {
			Write-Host 'Invalid directory!'
		}
	}
}
Write-Host 'You entered: '$ARDUINO_DIRECTORY
Read-Host 'Press [Enter] key to continue...'

# Checking if repo directory is already specified
if (-not(Test-Path $REPOSITORY_DIRECTORY)) {
	Write-Host 'Invalid repository directory'
	$REPOSITORY_DIRECTORY = (Get-Item -Path ".\" -Verbose).FullName
	Write-Host 'Using: '$REPOSITORY_DIRECTORY
}

# Checking hardware folder
if (Test-Path $ARDUINO_DIRECTORY\hardware\sparkfun) {
	# Abort, abort!
	# Either we've previously copied the folder over, if so great.
	# Or they already have a sparkfun folder with their own stuff in
	# In which case we don't want to mess with it
	Write-Host "'"$ARDUINO_DIRECTORY"\hardware\sparkfun' already exists, ignoring "
} else { 
	# Copy Sparkfun drivers etc. to hardware folder
	Write-Host "Copying Sparkfun drivers to " $ARDUINO_DIRECTORY"\hardware\sparkfun"
	Copy-Item $REPOSITORY_DIRECTORY\utils\hardware $ARDUINO_DIRECTORY -recurse
}

if (-not(Test-Path $ARDUINO_DIRECTORY\libraries)) {
	New-Item -ItemType directory -Path $ARDUINO_DIRECTORY\libraries
}

# Copying external libraries
# Checking src/platform/lib
Write-Host "Copying external libraries"
$liDirs = Get-ChildItem "$REPOSITORY_DIRECTORY"
Get-ChildItem $REPOSITORY_DIRECTORY\..\src\platform\lib\ -exclude unverified| `
ForEach-Object{
	$repoLibPath = $_
	$libPath = Split-Path -leaf $repoLibPath
	$libPath = Join-Path -Path $ARDUINO_DIRECTORY\libraries\ -ChildPath $libPath
	if (Test-Path $libPath) {
		Write-Host "Updating "$libPath
		Remove-Item -recurse $libPath 
	}
	#Copying libraries
	Write-Host "Copying " $libPath
	Copy-Item $repoLibPath $libPath -recurse
}

# Copying payload libraries
Get-ChildItem $REPOSITORY_DIRECTORY\..\src\payload\*\lib\* |`
ForEach-Object{
	$repoLibPath = $_
	$libPath = Split-Path -leaf $repoLibPath
	$libPath = Join-Path -Path $ARDUINO_DIRECTORY\libraries\ -ChildPath $libPath
	if (Test-Path $libPath) {
		Write-Host "Updating "$libPath
		Remove-Item -recurse $libPath 
	}
	Write-Host "Copying " $libPath
	Copy-Item $repoLibPath $libPath -recurse
}

# Removing previous Cube libraries and create new directory structure
Write-Host "Creating Cube library"
if (Test-Path $ARDUINO_DIRECTORY\libraries\Cube) {
	Remove-Item -recurse $ARDUINO_DIRECTORY\libraries\Cube
}
New-Item -ItemType directory -Path $ARDUINO_DIRECTORY\libraries\Cube
Write-Host "Creating examples folder"
New-Item -ItemType directory -Path $ARDUINO_DIRECTORY\libraries\Cube\examples
Write-Host "Creating extras folder"
New-Item -ItemType directory -Path $ARDUINO_DIRECTORY\libraries\Cube\extras
Write-Host "Creating src folder"
New-Item -ItemType directory -Path $ARDUINO_DIRECTORY\libraries\Cube\src

# Copying Arduino library manager files
Write-Host "Copying Arduino library manager files"
Copy-Item $REPOSITORY_DIRECTORY\utils\lbr\* $ARDUINO_DIRECTORY\libraries\Cube

# Copying base Cube library code
Write-Host "Copying base cube library code"
Copy-Item -Path $REPOSITORY_DIRECTORY\..\src\platform\* -Destination $ARDUINO_DIRECTORY\libraries\Cube\src -Include "*.cpp","*.h"

# Copying payload code to cube library
Write-Host "Copying library code files"
#possible powershell bug?? Can't use wildcard immediately prior to directory contents specifier, hence two lines and -filter instead of -include
Get-ChildItem -Path $REPOSITORY_DIRECTORY\..\src\payload\*\* -Filter *.cpp | Copy-Item -Destination $ARDUINO_DIRECTORY\libraries\Cube\src
Get-ChildItem -Path $REPOSITORY_DIRECTORY\..\src\payload\*\* -Filter *.h | Copy-Item -Destination $ARDUINO_DIRECTORY\libraries\Cube\src

# Creating example structure
Write-Host "Creating example payload directory"
New-Item -ItemType directory -Path $ARDUINO_DIRECTORY\libraries\Cube\examples\Payload
Write-Host "Creating example platform directory"
New-Item -ItemType directory -Path $ARDUINO_DIRECTORY\libraries\Cube\examples\Platform

# Copying payload examples to cube library examples
Write-Host "Copying examples to library"
Copy-Item -Path $REPOSITORY_DIRECTORY\..\src\platform\examples\* -Destination $ARDUINO_DIRECTORY\libraries\Cube\examples\Platform -recurse -exclude unverified
Write-Host "Copying payload example code"
Copy-Item -Path $REPOSITORY_DIRECTORY\..\src\payload\*\examples\* -Destination $ARDUINO_DIRECTORY\libraries\Cube\examples\Payload -recurse -exclude unverified