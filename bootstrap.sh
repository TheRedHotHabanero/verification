#!/bin/bash

# Config script for setting up environment for Clang + KLEE C++ code test generator

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
NC='\033[0m' # No Color
HOME=$1

# Function to compare two semantic versions (returns 0 if $1 >= $2)
version_ge() {
  printf '%s\n%s' "$1" "$2" | sort -V | head -n1 | grep -q "^$2$"
}

# Function to check command existence and version
check_version() {
  local cmd=$1
  local version_flag=$2
  local required_version=$3

  if ! command -v $cmd &> /dev/null; then
    echo -e "${RED}Error: $cmd is not installed.${NC}"
    return 1
  fi

  local version=$($cmd $version_flag | grep -oE '[0-9]+\.[0-9]+\.[0-9]+')
  if version_ge "$version" "$required_version"; then
    echo -e "${GREEN}$cmd version $version is sufficient (>= $required_version).${NC}"
  else
    echo -e "${RED}Error: $cmd version $version is less than required version $required_version.${NC}"
  fi
}

# Check required tools and versions
echo "Checking dependencies..."

check_version "clang" "--version" "13.0.1"
check_version "llvm-config" "--version" "13.0.1"
check_version "z3" "--version" "4.8.12"

# Check KLEE uClibc installation
if [[ ! -d "$HOME/bootstrap/klee-uclibc" ]]; then
  echo -e "${RED}Error: klee-uclibc not found in $HOME/bootstrap/klee-uclibc.${NC}"
  echo "installation will start now..."
  git clone https://github.com/klee/klee-uclibc.git $HOME/bootstrap/klee-uclibc
  cd $HOME/bootstrap/klee-uclibc
  ./configure --make-llvm-lib
  make
  cd -
else
  echo -e "${GREEN}klee-uclibc is installed.${NC}"
fi

# Check Google Test installation
GTEST_DIR="$HOME/bootstrap/gtests/googletest-release-1.11.0"
if [[ ! -d "$GTEST_DIR" ]]; then
  echo -e "${RED}Error: Google Test not found in $GTEST_DIR.${NC}"
  echo "Please download and install Google Test version 1.11.0 or higher."
else
  GTEST_VERSION=$(grep -m1 "set(PROJECT_VERSION" "$GTEST_DIR/CMakeLists.txt" | grep -oE '[0-9]+\.[0-9]+\.[0-9]+')
  REQUIRED_GTEST_VERSION="1.11.0"
  if version_ge "$GTEST_VERSION" "$REQUIRED_GTEST_VERSION"; then
    echo -e "${GREEN}Google Test version $GTEST_VERSION is sufficient (>= $REQUIRED_GTEST_VERSION).${NC}"
  else
    echo -e "${RED}Error: Google Test version $GTEST_VERSION is less than required version $REQUIRED_GTEST_VERSION.${NC}"
  fi
fi

# Check KLEE installation
cd $HOME
if [[ ! -d "$HOME/bootstrap/klee" ]]; then
  echo -e "${RED}Error: KLEE not found in $HOME/bootstrap/klee.${NC}"
  echo "installation will start now..."
  cd $HOME/bootstrap
  wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key|sudo apt-key add -
  mkdir -p ~/bootstrap/build
  cd $HOME/bootstrap
  curl -OL https://github.com/google/googletest/archive/release-1.11.0.zip
  unzip release-1.11.0.zip
  cd klee
  mkdir build
  cd build
  cmake -DSQLITE3_INCLUDE_DIR=/usr/bin/sqlite3 -DENABLE_POSIX_RUNTIME=ON -DENABLE_SOLVERS=Z3 -DKLEE_UCLIBC_PATH=$HOME/bootstrap/klee-uclibc -DENABLE_UNIT_TESTS=ON $HOME/bootstrap/klee
  make
  cd -
else
  echo -e "${GREEN}KLEE is installed.${NC}"
fi

echo -e "${GREEN}Environment check complete.${NC}"