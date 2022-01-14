#Rationale
The current structure of the repository, while making logical sense for development, is not directly compatible with the Arduino structure. To avoid manually having to copy code back and forth between repo and Arduino libraries, which is both time consuming and error-prone, these set of scripts aim to automate the process. This enables developing and testing the same code, avoiding the issues of complete dependancies not necessarily being uploaded to the respository simultaneously.

# Generating the deployable code
### Linux shell script
In linux, run the script _makeDeployable.sh_. It will prompt you for your home Arduino folder, located at /home/username/Arduino by default. The script will then attempt to copy over the required hardware folder for the Sparkfun pro micro, if a directory called sparkfun already exists however it will leave the existing directory, as this may contain additional drivers etc.

It will copy all the external libraries to your user library folder, extract any dependant libraries from your payloads and add them too, and generate the cube library from the repository in a structure compatible with the new arduino IDE.

### OSX script
Should be similar to linux, need to test however

### Windows batch file
For windows the process is not quite so simple. The script _makeDeployable.ps1_ is the functional equivalent of the linux shell script. However, on work computers we cannot run powershell script files without script certification, running as admin, adding security exceptions and changing the execution policy to remotesigned. We can however, use the powershell command line. To this end, we can use the powershell to create a batch file to echo commands back to the powershell CLI. The script _makeDeployableTerse.ps1_ (terse due to the maximum 8K input to the CLI) will generate a file, _makeDeployable.bat_, base 64 encoded, to echo commands back to the powershell. I am fully aware that this is an absolutely horrific bodge, but the end result is absolutely usable, and will rarely need to be updated. The intention being, that this file can be generated with your own file structure hard-coded, and placed outside of your repository (so as not to be overwritten). Then simply double clicking the batch file will automatically generate the arduino libraries from the repository. If you cannot run powershell scripts to generate the batch file in the first place, we have one computer capable of this, to generate batch files for other people. Once generated, it should never need to be modified, unless the structure of either the repository or Arduino libraries is significantly updated.

Alternatively, the default generated batch file, _makeDeployable.bat_ in the respository, if run while within the repository, will request the location of your Arduino folder through the console, and use the directory it is run from as the respository directory, which can be used, but requires manually entering a directory every time the script is run.