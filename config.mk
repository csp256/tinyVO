# The name of the executable to be created
BIN_NAME := app
# Compiler used
CXX ?= clang
# Extension of source files used in the project
SRC_EXT = cpp
# Path to the source directory, relative to the makefile
SRC_PATH = .
# Space-separated pkg-config libraries used by this project
LIBS =
# General compiler flags
MODULE_FLAGS = -fmodules -fimplicit-modules -fimplicit-module-maps
COMPILE_FLAGS = -std=c++20 $(MODULE_FLAGS) -Wall -Wextra -g -O3
# Additional release-specific flags
RCOMPILE_FLAGS = -D NDEBUG
# Additional debug-specific flags
DCOMPILE_FLAGS = -D DEBUG
# Add additional include paths
INCLUDES = -I $(SRC_PATH)
# General linker settings
LINK_FLAGS =
# Additional release-specific linker settings
RLINK_FLAGS =
# Additional debug-specific linker settings
DLINK_FLAGS =
# Destination directory, like a jail or mounted system
DESTDIR = /
# Install path (bin/ is appended automatically)
INSTALL_PREFIX = usr/local