# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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
CMAKE_SOURCE_DIR = /home/anthonyquantum/mp2-lab1-set

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/anthonyquantum/mp2-lab1-set

# Include any dependencies generated for this target.
include src/CMakeFiles/set.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/set.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/set.dir/flags.make

src/CMakeFiles/set.dir/tbitfield.cpp.o: src/CMakeFiles/set.dir/flags.make
src/CMakeFiles/set.dir/tbitfield.cpp.o: src/tbitfield.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/anthonyquantum/mp2-lab1-set/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/set.dir/tbitfield.cpp.o"
	cd /home/anthonyquantum/mp2-lab1-set/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/set.dir/tbitfield.cpp.o -c /home/anthonyquantum/mp2-lab1-set/src/tbitfield.cpp

src/CMakeFiles/set.dir/tbitfield.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/set.dir/tbitfield.cpp.i"
	cd /home/anthonyquantum/mp2-lab1-set/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/anthonyquantum/mp2-lab1-set/src/tbitfield.cpp > CMakeFiles/set.dir/tbitfield.cpp.i

src/CMakeFiles/set.dir/tbitfield.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/set.dir/tbitfield.cpp.s"
	cd /home/anthonyquantum/mp2-lab1-set/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/anthonyquantum/mp2-lab1-set/src/tbitfield.cpp -o CMakeFiles/set.dir/tbitfield.cpp.s

src/CMakeFiles/set.dir/tbitfield.cpp.o.requires:

.PHONY : src/CMakeFiles/set.dir/tbitfield.cpp.o.requires

src/CMakeFiles/set.dir/tbitfield.cpp.o.provides: src/CMakeFiles/set.dir/tbitfield.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/set.dir/build.make src/CMakeFiles/set.dir/tbitfield.cpp.o.provides.build
.PHONY : src/CMakeFiles/set.dir/tbitfield.cpp.o.provides

src/CMakeFiles/set.dir/tbitfield.cpp.o.provides.build: src/CMakeFiles/set.dir/tbitfield.cpp.o


src/CMakeFiles/set.dir/tset.cpp.o: src/CMakeFiles/set.dir/flags.make
src/CMakeFiles/set.dir/tset.cpp.o: src/tset.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/anthonyquantum/mp2-lab1-set/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/set.dir/tset.cpp.o"
	cd /home/anthonyquantum/mp2-lab1-set/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/set.dir/tset.cpp.o -c /home/anthonyquantum/mp2-lab1-set/src/tset.cpp

src/CMakeFiles/set.dir/tset.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/set.dir/tset.cpp.i"
	cd /home/anthonyquantum/mp2-lab1-set/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/anthonyquantum/mp2-lab1-set/src/tset.cpp > CMakeFiles/set.dir/tset.cpp.i

src/CMakeFiles/set.dir/tset.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/set.dir/tset.cpp.s"
	cd /home/anthonyquantum/mp2-lab1-set/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/anthonyquantum/mp2-lab1-set/src/tset.cpp -o CMakeFiles/set.dir/tset.cpp.s

src/CMakeFiles/set.dir/tset.cpp.o.requires:

.PHONY : src/CMakeFiles/set.dir/tset.cpp.o.requires

src/CMakeFiles/set.dir/tset.cpp.o.provides: src/CMakeFiles/set.dir/tset.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/set.dir/build.make src/CMakeFiles/set.dir/tset.cpp.o.provides.build
.PHONY : src/CMakeFiles/set.dir/tset.cpp.o.provides

src/CMakeFiles/set.dir/tset.cpp.o.provides.build: src/CMakeFiles/set.dir/tset.cpp.o


# Object files for target set
set_OBJECTS = \
"CMakeFiles/set.dir/tbitfield.cpp.o" \
"CMakeFiles/set.dir/tset.cpp.o"

# External object files for target set
set_EXTERNAL_OBJECTS =

lib/libset.a: src/CMakeFiles/set.dir/tbitfield.cpp.o
lib/libset.a: src/CMakeFiles/set.dir/tset.cpp.o
lib/libset.a: src/CMakeFiles/set.dir/build.make
lib/libset.a: src/CMakeFiles/set.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/anthonyquantum/mp2-lab1-set/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library ../lib/libset.a"
	cd /home/anthonyquantum/mp2-lab1-set/src && $(CMAKE_COMMAND) -P CMakeFiles/set.dir/cmake_clean_target.cmake
	cd /home/anthonyquantum/mp2-lab1-set/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/set.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/set.dir/build: lib/libset.a

.PHONY : src/CMakeFiles/set.dir/build

src/CMakeFiles/set.dir/requires: src/CMakeFiles/set.dir/tbitfield.cpp.o.requires
src/CMakeFiles/set.dir/requires: src/CMakeFiles/set.dir/tset.cpp.o.requires

.PHONY : src/CMakeFiles/set.dir/requires

src/CMakeFiles/set.dir/clean:
	cd /home/anthonyquantum/mp2-lab1-set/src && $(CMAKE_COMMAND) -P CMakeFiles/set.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/set.dir/clean

src/CMakeFiles/set.dir/depend:
	cd /home/anthonyquantum/mp2-lab1-set && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/anthonyquantum/mp2-lab1-set /home/anthonyquantum/mp2-lab1-set/src /home/anthonyquantum/mp2-lab1-set /home/anthonyquantum/mp2-lab1-set/src /home/anthonyquantum/mp2-lab1-set/src/CMakeFiles/set.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/set.dir/depend

