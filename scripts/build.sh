#!/usr/bin/env bash
set -euo pipefail

CONFIGURATION="Debug"
RUN=0

while [[ $# -gt 0 ]]; do
  case "$1" in
    -Configuration|--configuration)
      CONFIGURATION="$2"
      shift 2
      ;;
    -Run|--run)
      RUN=1
      shift
      ;;
    *)
      echo "Unknown argument: $1" >&2
      exit 1
      ;;
  esac
done

if [[ "$CONFIGURATION" != "Debug" && "$CONFIGURATION" != "Release" ]]; then
  echo "Configuration must be Debug or Release" >&2
  exit 1
fi

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BUILD_DIR="$REPO_ROOT/build"

cmake -S "$REPO_ROOT" -B "$BUILD_DIR" -G "Unix Makefiles" -DCMAKE_BUILD_TYPE="$CONFIGURATION" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build "$BUILD_DIR" -j8

EXE="$BUILD_DIR/WonderGirl"
echo "Build succeeded: $EXE"

if [[ "$RUN" -eq 1 ]]; then
  cd "$REPO_ROOT" && "$EXE"
fi
