#!/bin/sh
#
# Use this script to run your program LOCALLY.

set -e # Exit early if any commands fail

# Derleme iþlemi
(
  cd "$(dirname "$0")" # Proje dizininde derleme iþlemi
  dotnet build --configuration Release --output /tmp/MyGitProject MyGitProject.csproj
)

# Çalýþtýrma iþlemi
exec /tmp/MyGitProject/MyGitProject "$@"
