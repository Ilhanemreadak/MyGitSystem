#!/bin/sh
#
# Use this script to run your program LOCALLY.

set -e # Exit early if any commands fail

# Derleme i�lemi
(
  cd "$(dirname "$0")" # Proje dizininde derleme i�lemi
  dotnet build --configuration Release --output /tmp/codecrafters-build-mygitsimulator Program.csproj
)

# �al��t�rma i�lemi
exec /tmp/MyGitProject "$@"
