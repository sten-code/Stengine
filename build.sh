#!/bin/bash

# Default values
projectName="Steditor"
config="Release"

# Parse command line arguments
while getopts "p:c:" opt; do
  case $opt in
    p)
      projectName=$OPTARG
      ;;
    c)
      config=$OPTARG
      ;;
    \?)
      echo "Invalid option: -$OPTARG" >&2
      exit 1
      ;;
    :)
      echo "Option -$OPTARG requires an argument." >&2
      exit 1
      ;;
  esac
done

# Check if required arguments are provided
if [ -z "$projectName" ] || [ -z "$config" ]; then
  echo "Usage: $0 -p {projectName} -c {config (release|debug|dist)}"
  exit 1
fi

# Config in lower case
config=$(echo "$config" | tr "[:upper:]" "[:lower:]")

# Config with the first letter capitalized
configDir="$(tr '[:lower:]' '[:upper:]' <<< ${config:0:1})${config:1}"

# Run premake5 to generate makefiles
premake5 gmake &&

# Build the project
make -j10 config=$config &&

# Navigate to the project directory
cd bin/$configDir-linux-x86_64/$projectName &&

# Run the executable
if [ "$config" = "debug" ]; then
  gf2 -ex r $projectName
else
  ./$projectName
fi


# Return to the original directory
cd -

