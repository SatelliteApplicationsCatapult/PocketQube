#!/bin/sh
# A shell script to copy the packaged libraries into a user's Arduino library
# Run with -q flag to suppress output

# Checking for quiet flag
getopts ":q" opt; 
if [ "$opt" = "q" ] ; then
	QUIET=true ;
else
	QUIET=false ;
	echo "QUIET:" $QUIET
fi

# No readlink -f on OSX, this should be cross-platform compatible
# (unless someone has decided to redefine $0)
SCRIPT_PATH="$(cd "$(dirname "$0")"; pwd)"
SOURCE_PATH="$(dirname "$(dirname "$0")")"/lib
LIBRARY_PATH="$(dirname "$(dirname "$(dirname "$SCRIPT_PATH")")")"

if ! $QUIET ; then
	echo "Script directory:" $SCRIPT_PATH
	echo "Source directory:" $SOURCE_PATH
	echo "Library directory:" $LIBRARY_PATH
fi

if ! $QUIET ; then
	for d in $SOURCE_PATH/*/ ; do	
		if [ ! -d $LIBRARY_PATH/$(basename "$d") ] ; then
			echo "Creating:" $(basename "$d")
		else
			echo "Updating:" $(basename "$d")
		fi
	done
	read -p "Proceed?" var
	echo "Continuing..."
fi

for d in $SOURCE_PATH/*/ ; do
	if [ ! -d $LIBRARY_PATH/$(basename "$d") ] ; then
		mkdir $LIBRARY_PATH/$(basename "$d")
		cp -R $d/* $LIBRARY_PATH/$(basename "$d")/
	else
		cp -R $d/* $LIBRARY_PATH/$(basename "$d")
	fi
done
