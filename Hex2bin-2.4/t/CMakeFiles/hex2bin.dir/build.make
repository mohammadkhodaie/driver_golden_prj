# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/parto/Downloads/Hex2bin-2.4

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/parto/Downloads/Hex2bin-2.4/t

# Include any dependencies generated for this target.
include CMakeFiles/hex2bin.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/hex2bin.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/hex2bin.dir/flags.make

CMakeFiles/hex2bin.dir/hex2bin.c.o: CMakeFiles/hex2bin.dir/flags.make
CMakeFiles/hex2bin.dir/hex2bin.c.o: ../hex2bin.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/parto/Downloads/Hex2bin-2.4/t/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/hex2bin.dir/hex2bin.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/hex2bin.dir/hex2bin.c.o   -c /home/parto/Downloads/Hex2bin-2.4/hex2bin.c

CMakeFiles/hex2bin.dir/hex2bin.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/hex2bin.dir/hex2bin.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/parto/Downloads/Hex2bin-2.4/hex2bin.c > CMakeFiles/hex2bin.dir/hex2bin.c.i

CMakeFiles/hex2bin.dir/hex2bin.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/hex2bin.dir/hex2bin.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/parto/Downloads/Hex2bin-2.4/hex2bin.c -o CMakeFiles/hex2bin.dir/hex2bin.c.s

CMakeFiles/hex2bin.dir/hex2bin.c.o.requires:

.PHONY : CMakeFiles/hex2bin.dir/hex2bin.c.o.requires

CMakeFiles/hex2bin.dir/hex2bin.c.o.provides: CMakeFiles/hex2bin.dir/hex2bin.c.o.requires
	$(MAKE) -f CMakeFiles/hex2bin.dir/build.make CMakeFiles/hex2bin.dir/hex2bin.c.o.provides.build
.PHONY : CMakeFiles/hex2bin.dir/hex2bin.c.o.provides

CMakeFiles/hex2bin.dir/hex2bin.c.o.provides.build: CMakeFiles/hex2bin.dir/hex2bin.c.o


CMakeFiles/hex2bin.dir/common.c.o: CMakeFiles/hex2bin.dir/flags.make
CMakeFiles/hex2bin.dir/common.c.o: ../common.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/parto/Downloads/Hex2bin-2.4/t/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/hex2bin.dir/common.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/hex2bin.dir/common.c.o   -c /home/parto/Downloads/Hex2bin-2.4/common.c

CMakeFiles/hex2bin.dir/common.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/hex2bin.dir/common.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/parto/Downloads/Hex2bin-2.4/common.c > CMakeFiles/hex2bin.dir/common.c.i

CMakeFiles/hex2bin.dir/common.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/hex2bin.dir/common.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/parto/Downloads/Hex2bin-2.4/common.c -o CMakeFiles/hex2bin.dir/common.c.s

CMakeFiles/hex2bin.dir/common.c.o.requires:

.PHONY : CMakeFiles/hex2bin.dir/common.c.o.requires

CMakeFiles/hex2bin.dir/common.c.o.provides: CMakeFiles/hex2bin.dir/common.c.o.requires
	$(MAKE) -f CMakeFiles/hex2bin.dir/build.make CMakeFiles/hex2bin.dir/common.c.o.provides.build
.PHONY : CMakeFiles/hex2bin.dir/common.c.o.provides

CMakeFiles/hex2bin.dir/common.c.o.provides.build: CMakeFiles/hex2bin.dir/common.c.o


CMakeFiles/hex2bin.dir/libcrc.c.o: CMakeFiles/hex2bin.dir/flags.make
CMakeFiles/hex2bin.dir/libcrc.c.o: ../libcrc.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/parto/Downloads/Hex2bin-2.4/t/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/hex2bin.dir/libcrc.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/hex2bin.dir/libcrc.c.o   -c /home/parto/Downloads/Hex2bin-2.4/libcrc.c

CMakeFiles/hex2bin.dir/libcrc.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/hex2bin.dir/libcrc.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/parto/Downloads/Hex2bin-2.4/libcrc.c > CMakeFiles/hex2bin.dir/libcrc.c.i

CMakeFiles/hex2bin.dir/libcrc.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/hex2bin.dir/libcrc.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/parto/Downloads/Hex2bin-2.4/libcrc.c -o CMakeFiles/hex2bin.dir/libcrc.c.s

CMakeFiles/hex2bin.dir/libcrc.c.o.requires:

.PHONY : CMakeFiles/hex2bin.dir/libcrc.c.o.requires

CMakeFiles/hex2bin.dir/libcrc.c.o.provides: CMakeFiles/hex2bin.dir/libcrc.c.o.requires
	$(MAKE) -f CMakeFiles/hex2bin.dir/build.make CMakeFiles/hex2bin.dir/libcrc.c.o.provides.build
.PHONY : CMakeFiles/hex2bin.dir/libcrc.c.o.provides

CMakeFiles/hex2bin.dir/libcrc.c.o.provides.build: CMakeFiles/hex2bin.dir/libcrc.c.o


CMakeFiles/hex2bin.dir/binary.c.o: CMakeFiles/hex2bin.dir/flags.make
CMakeFiles/hex2bin.dir/binary.c.o: ../binary.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/parto/Downloads/Hex2bin-2.4/t/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/hex2bin.dir/binary.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/hex2bin.dir/binary.c.o   -c /home/parto/Downloads/Hex2bin-2.4/binary.c

CMakeFiles/hex2bin.dir/binary.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/hex2bin.dir/binary.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/parto/Downloads/Hex2bin-2.4/binary.c > CMakeFiles/hex2bin.dir/binary.c.i

CMakeFiles/hex2bin.dir/binary.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/hex2bin.dir/binary.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/parto/Downloads/Hex2bin-2.4/binary.c -o CMakeFiles/hex2bin.dir/binary.c.s

CMakeFiles/hex2bin.dir/binary.c.o.requires:

.PHONY : CMakeFiles/hex2bin.dir/binary.c.o.requires

CMakeFiles/hex2bin.dir/binary.c.o.provides: CMakeFiles/hex2bin.dir/binary.c.o.requires
	$(MAKE) -f CMakeFiles/hex2bin.dir/build.make CMakeFiles/hex2bin.dir/binary.c.o.provides.build
.PHONY : CMakeFiles/hex2bin.dir/binary.c.o.provides

CMakeFiles/hex2bin.dir/binary.c.o.provides.build: CMakeFiles/hex2bin.dir/binary.c.o


# Object files for target hex2bin
hex2bin_OBJECTS = \
"CMakeFiles/hex2bin.dir/hex2bin.c.o" \
"CMakeFiles/hex2bin.dir/common.c.o" \
"CMakeFiles/hex2bin.dir/libcrc.c.o" \
"CMakeFiles/hex2bin.dir/binary.c.o"

# External object files for target hex2bin
hex2bin_EXTERNAL_OBJECTS =

hex2bin: CMakeFiles/hex2bin.dir/hex2bin.c.o
hex2bin: CMakeFiles/hex2bin.dir/common.c.o
hex2bin: CMakeFiles/hex2bin.dir/libcrc.c.o
hex2bin: CMakeFiles/hex2bin.dir/binary.c.o
hex2bin: CMakeFiles/hex2bin.dir/build.make
hex2bin: CMakeFiles/hex2bin.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/parto/Downloads/Hex2bin-2.4/t/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C executable hex2bin"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/hex2bin.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/hex2bin.dir/build: hex2bin

.PHONY : CMakeFiles/hex2bin.dir/build

CMakeFiles/hex2bin.dir/requires: CMakeFiles/hex2bin.dir/hex2bin.c.o.requires
CMakeFiles/hex2bin.dir/requires: CMakeFiles/hex2bin.dir/common.c.o.requires
CMakeFiles/hex2bin.dir/requires: CMakeFiles/hex2bin.dir/libcrc.c.o.requires
CMakeFiles/hex2bin.dir/requires: CMakeFiles/hex2bin.dir/binary.c.o.requires

.PHONY : CMakeFiles/hex2bin.dir/requires

CMakeFiles/hex2bin.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/hex2bin.dir/cmake_clean.cmake
.PHONY : CMakeFiles/hex2bin.dir/clean

CMakeFiles/hex2bin.dir/depend:
	cd /home/parto/Downloads/Hex2bin-2.4/t && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/parto/Downloads/Hex2bin-2.4 /home/parto/Downloads/Hex2bin-2.4 /home/parto/Downloads/Hex2bin-2.4/t /home/parto/Downloads/Hex2bin-2.4/t /home/parto/Downloads/Hex2bin-2.4/t/CMakeFiles/hex2bin.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/hex2bin.dir/depend
