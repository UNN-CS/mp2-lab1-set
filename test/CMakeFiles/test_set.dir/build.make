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
include test/CMakeFiles/test_set.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/test_set.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/test_set.dir/flags.make

test/CMakeFiles/test_set.dir/test_additional.cpp.o: test/CMakeFiles/test_set.dir/flags.make
test/CMakeFiles/test_set.dir/test_additional.cpp.o: test/test_additional.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/anthonyquantum/mp2-lab1-set/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/test_set.dir/test_additional.cpp.o"
	cd /home/anthonyquantum/mp2-lab1-set/test && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_set.dir/test_additional.cpp.o -c /home/anthonyquantum/mp2-lab1-set/test/test_additional.cpp

test/CMakeFiles/test_set.dir/test_additional.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_set.dir/test_additional.cpp.i"
	cd /home/anthonyquantum/mp2-lab1-set/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/anthonyquantum/mp2-lab1-set/test/test_additional.cpp > CMakeFiles/test_set.dir/test_additional.cpp.i

test/CMakeFiles/test_set.dir/test_additional.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_set.dir/test_additional.cpp.s"
	cd /home/anthonyquantum/mp2-lab1-set/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/anthonyquantum/mp2-lab1-set/test/test_additional.cpp -o CMakeFiles/test_set.dir/test_additional.cpp.s

test/CMakeFiles/test_set.dir/test_additional.cpp.o.requires:

.PHONY : test/CMakeFiles/test_set.dir/test_additional.cpp.o.requires

test/CMakeFiles/test_set.dir/test_additional.cpp.o.provides: test/CMakeFiles/test_set.dir/test_additional.cpp.o.requires
	$(MAKE) -f test/CMakeFiles/test_set.dir/build.make test/CMakeFiles/test_set.dir/test_additional.cpp.o.provides.build
.PHONY : test/CMakeFiles/test_set.dir/test_additional.cpp.o.provides

test/CMakeFiles/test_set.dir/test_additional.cpp.o.provides.build: test/CMakeFiles/test_set.dir/test_additional.cpp.o


test/CMakeFiles/test_set.dir/test_main.cpp.o: test/CMakeFiles/test_set.dir/flags.make
test/CMakeFiles/test_set.dir/test_main.cpp.o: test/test_main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/anthonyquantum/mp2-lab1-set/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object test/CMakeFiles/test_set.dir/test_main.cpp.o"
	cd /home/anthonyquantum/mp2-lab1-set/test && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_set.dir/test_main.cpp.o -c /home/anthonyquantum/mp2-lab1-set/test/test_main.cpp

test/CMakeFiles/test_set.dir/test_main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_set.dir/test_main.cpp.i"
	cd /home/anthonyquantum/mp2-lab1-set/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/anthonyquantum/mp2-lab1-set/test/test_main.cpp > CMakeFiles/test_set.dir/test_main.cpp.i

test/CMakeFiles/test_set.dir/test_main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_set.dir/test_main.cpp.s"
	cd /home/anthonyquantum/mp2-lab1-set/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/anthonyquantum/mp2-lab1-set/test/test_main.cpp -o CMakeFiles/test_set.dir/test_main.cpp.s

test/CMakeFiles/test_set.dir/test_main.cpp.o.requires:

.PHONY : test/CMakeFiles/test_set.dir/test_main.cpp.o.requires

test/CMakeFiles/test_set.dir/test_main.cpp.o.provides: test/CMakeFiles/test_set.dir/test_main.cpp.o.requires
	$(MAKE) -f test/CMakeFiles/test_set.dir/build.make test/CMakeFiles/test_set.dir/test_main.cpp.o.provides.build
.PHONY : test/CMakeFiles/test_set.dir/test_main.cpp.o.provides

test/CMakeFiles/test_set.dir/test_main.cpp.o.provides.build: test/CMakeFiles/test_set.dir/test_main.cpp.o


test/CMakeFiles/test_set.dir/test_tbitfield.cpp.o: test/CMakeFiles/test_set.dir/flags.make
test/CMakeFiles/test_set.dir/test_tbitfield.cpp.o: test/test_tbitfield.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/anthonyquantum/mp2-lab1-set/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object test/CMakeFiles/test_set.dir/test_tbitfield.cpp.o"
	cd /home/anthonyquantum/mp2-lab1-set/test && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_set.dir/test_tbitfield.cpp.o -c /home/anthonyquantum/mp2-lab1-set/test/test_tbitfield.cpp

test/CMakeFiles/test_set.dir/test_tbitfield.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_set.dir/test_tbitfield.cpp.i"
	cd /home/anthonyquantum/mp2-lab1-set/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/anthonyquantum/mp2-lab1-set/test/test_tbitfield.cpp > CMakeFiles/test_set.dir/test_tbitfield.cpp.i

test/CMakeFiles/test_set.dir/test_tbitfield.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_set.dir/test_tbitfield.cpp.s"
	cd /home/anthonyquantum/mp2-lab1-set/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/anthonyquantum/mp2-lab1-set/test/test_tbitfield.cpp -o CMakeFiles/test_set.dir/test_tbitfield.cpp.s

test/CMakeFiles/test_set.dir/test_tbitfield.cpp.o.requires:

.PHONY : test/CMakeFiles/test_set.dir/test_tbitfield.cpp.o.requires

test/CMakeFiles/test_set.dir/test_tbitfield.cpp.o.provides: test/CMakeFiles/test_set.dir/test_tbitfield.cpp.o.requires
	$(MAKE) -f test/CMakeFiles/test_set.dir/build.make test/CMakeFiles/test_set.dir/test_tbitfield.cpp.o.provides.build
.PHONY : test/CMakeFiles/test_set.dir/test_tbitfield.cpp.o.provides

test/CMakeFiles/test_set.dir/test_tbitfield.cpp.o.provides.build: test/CMakeFiles/test_set.dir/test_tbitfield.cpp.o


test/CMakeFiles/test_set.dir/test_tset.cpp.o: test/CMakeFiles/test_set.dir/flags.make
test/CMakeFiles/test_set.dir/test_tset.cpp.o: test/test_tset.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/anthonyquantum/mp2-lab1-set/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object test/CMakeFiles/test_set.dir/test_tset.cpp.o"
	cd /home/anthonyquantum/mp2-lab1-set/test && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_set.dir/test_tset.cpp.o -c /home/anthonyquantum/mp2-lab1-set/test/test_tset.cpp

test/CMakeFiles/test_set.dir/test_tset.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_set.dir/test_tset.cpp.i"
	cd /home/anthonyquantum/mp2-lab1-set/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/anthonyquantum/mp2-lab1-set/test/test_tset.cpp > CMakeFiles/test_set.dir/test_tset.cpp.i

test/CMakeFiles/test_set.dir/test_tset.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_set.dir/test_tset.cpp.s"
	cd /home/anthonyquantum/mp2-lab1-set/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/anthonyquantum/mp2-lab1-set/test/test_tset.cpp -o CMakeFiles/test_set.dir/test_tset.cpp.s

test/CMakeFiles/test_set.dir/test_tset.cpp.o.requires:

.PHONY : test/CMakeFiles/test_set.dir/test_tset.cpp.o.requires

test/CMakeFiles/test_set.dir/test_tset.cpp.o.provides: test/CMakeFiles/test_set.dir/test_tset.cpp.o.requires
	$(MAKE) -f test/CMakeFiles/test_set.dir/build.make test/CMakeFiles/test_set.dir/test_tset.cpp.o.provides.build
.PHONY : test/CMakeFiles/test_set.dir/test_tset.cpp.o.provides

test/CMakeFiles/test_set.dir/test_tset.cpp.o.provides.build: test/CMakeFiles/test_set.dir/test_tset.cpp.o


# Object files for target test_set
test_set_OBJECTS = \
"CMakeFiles/test_set.dir/test_additional.cpp.o" \
"CMakeFiles/test_set.dir/test_main.cpp.o" \
"CMakeFiles/test_set.dir/test_tbitfield.cpp.o" \
"CMakeFiles/test_set.dir/test_tset.cpp.o"

# External object files for target test_set
test_set_EXTERNAL_OBJECTS =

bin/test_set: test/CMakeFiles/test_set.dir/test_additional.cpp.o
bin/test_set: test/CMakeFiles/test_set.dir/test_main.cpp.o
bin/test_set: test/CMakeFiles/test_set.dir/test_tbitfield.cpp.o
bin/test_set: test/CMakeFiles/test_set.dir/test_tset.cpp.o
bin/test_set: test/CMakeFiles/test_set.dir/build.make
bin/test_set: lib/libgtest.a
bin/test_set: lib/libset.a
bin/test_set: test/CMakeFiles/test_set.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/anthonyquantum/mp2-lab1-set/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable ../bin/test_set"
	cd /home/anthonyquantum/mp2-lab1-set/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_set.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/test_set.dir/build: bin/test_set

.PHONY : test/CMakeFiles/test_set.dir/build

test/CMakeFiles/test_set.dir/requires: test/CMakeFiles/test_set.dir/test_additional.cpp.o.requires
test/CMakeFiles/test_set.dir/requires: test/CMakeFiles/test_set.dir/test_main.cpp.o.requires
test/CMakeFiles/test_set.dir/requires: test/CMakeFiles/test_set.dir/test_tbitfield.cpp.o.requires
test/CMakeFiles/test_set.dir/requires: test/CMakeFiles/test_set.dir/test_tset.cpp.o.requires

.PHONY : test/CMakeFiles/test_set.dir/requires

test/CMakeFiles/test_set.dir/clean:
	cd /home/anthonyquantum/mp2-lab1-set/test && $(CMAKE_COMMAND) -P CMakeFiles/test_set.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/test_set.dir/clean

test/CMakeFiles/test_set.dir/depend:
	cd /home/anthonyquantum/mp2-lab1-set && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/anthonyquantum/mp2-lab1-set /home/anthonyquantum/mp2-lab1-set/test /home/anthonyquantum/mp2-lab1-set /home/anthonyquantum/mp2-lab1-set/test /home/anthonyquantum/mp2-lab1-set/test/CMakeFiles/test_set.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/test_set.dir/depend

