# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/anokl/Projects/C++/project_template

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/anokl/Projects/C++/project_template/build

# Include any dependencies generated for this target.
include lib_test/CMakeFiles/lib_test.dir/depend.make

# Include the progress variables for this target.
include lib_test/CMakeFiles/lib_test.dir/progress.make

# Include the compile flags for this target's objects.
include lib_test/CMakeFiles/lib_test.dir/flags.make

lib_test/CMakeFiles/lib_test.dir/main.cpp.o: lib_test/CMakeFiles/lib_test.dir/flags.make
lib_test/CMakeFiles/lib_test.dir/main.cpp.o: ../lib_test/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/anokl/Projects/C++/project_template/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object lib_test/CMakeFiles/lib_test.dir/main.cpp.o"
	cd /home/anokl/Projects/C++/project_template/build/lib_test && /usr/local/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/lib_test.dir/main.cpp.o -c /home/anokl/Projects/C++/project_template/lib_test/main.cpp

lib_test/CMakeFiles/lib_test.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lib_test.dir/main.cpp.i"
	cd /home/anokl/Projects/C++/project_template/build/lib_test && /usr/local/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/anokl/Projects/C++/project_template/lib_test/main.cpp > CMakeFiles/lib_test.dir/main.cpp.i

lib_test/CMakeFiles/lib_test.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lib_test.dir/main.cpp.s"
	cd /home/anokl/Projects/C++/project_template/build/lib_test && /usr/local/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/anokl/Projects/C++/project_template/lib_test/main.cpp -o CMakeFiles/lib_test.dir/main.cpp.s

lib_test/CMakeFiles/lib_test.dir/main.cpp.o.requires:
.PHONY : lib_test/CMakeFiles/lib_test.dir/main.cpp.o.requires

lib_test/CMakeFiles/lib_test.dir/main.cpp.o.provides: lib_test/CMakeFiles/lib_test.dir/main.cpp.o.requires
	$(MAKE) -f lib_test/CMakeFiles/lib_test.dir/build.make lib_test/CMakeFiles/lib_test.dir/main.cpp.o.provides.build
.PHONY : lib_test/CMakeFiles/lib_test.dir/main.cpp.o.provides

lib_test/CMakeFiles/lib_test.dir/main.cpp.o.provides.build: lib_test/CMakeFiles/lib_test.dir/main.cpp.o

lib_test/CMakeFiles/lib_test.dir/lib_test.cpp.o: lib_test/CMakeFiles/lib_test.dir/flags.make
lib_test/CMakeFiles/lib_test.dir/lib_test.cpp.o: ../lib_test/lib_test.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/anokl/Projects/C++/project_template/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object lib_test/CMakeFiles/lib_test.dir/lib_test.cpp.o"
	cd /home/anokl/Projects/C++/project_template/build/lib_test && /usr/local/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/lib_test.dir/lib_test.cpp.o -c /home/anokl/Projects/C++/project_template/lib_test/lib_test.cpp

lib_test/CMakeFiles/lib_test.dir/lib_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lib_test.dir/lib_test.cpp.i"
	cd /home/anokl/Projects/C++/project_template/build/lib_test && /usr/local/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/anokl/Projects/C++/project_template/lib_test/lib_test.cpp > CMakeFiles/lib_test.dir/lib_test.cpp.i

lib_test/CMakeFiles/lib_test.dir/lib_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lib_test.dir/lib_test.cpp.s"
	cd /home/anokl/Projects/C++/project_template/build/lib_test && /usr/local/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/anokl/Projects/C++/project_template/lib_test/lib_test.cpp -o CMakeFiles/lib_test.dir/lib_test.cpp.s

lib_test/CMakeFiles/lib_test.dir/lib_test.cpp.o.requires:
.PHONY : lib_test/CMakeFiles/lib_test.dir/lib_test.cpp.o.requires

lib_test/CMakeFiles/lib_test.dir/lib_test.cpp.o.provides: lib_test/CMakeFiles/lib_test.dir/lib_test.cpp.o.requires
	$(MAKE) -f lib_test/CMakeFiles/lib_test.dir/build.make lib_test/CMakeFiles/lib_test.dir/lib_test.cpp.o.provides.build
.PHONY : lib_test/CMakeFiles/lib_test.dir/lib_test.cpp.o.provides

lib_test/CMakeFiles/lib_test.dir/lib_test.cpp.o.provides.build: lib_test/CMakeFiles/lib_test.dir/lib_test.cpp.o

# Object files for target lib_test
lib_test_OBJECTS = \
"CMakeFiles/lib_test.dir/main.cpp.o" \
"CMakeFiles/lib_test.dir/lib_test.cpp.o"

# External object files for target lib_test
lib_test_EXTERNAL_OBJECTS =

lib_test/lib_test: lib_test/CMakeFiles/lib_test.dir/main.cpp.o
lib_test/lib_test: lib_test/CMakeFiles/lib_test.dir/lib_test.cpp.o
lib_test/lib_test: lib/liblib.a
lib_test/lib_test: lib_test/CMakeFiles/lib_test.dir/build.make
lib_test/lib_test: lib_test/CMakeFiles/lib_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable lib_test"
	cd /home/anokl/Projects/C++/project_template/build/lib_test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lib_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib_test/CMakeFiles/lib_test.dir/build: lib_test/lib_test
.PHONY : lib_test/CMakeFiles/lib_test.dir/build

lib_test/CMakeFiles/lib_test.dir/requires: lib_test/CMakeFiles/lib_test.dir/main.cpp.o.requires
lib_test/CMakeFiles/lib_test.dir/requires: lib_test/CMakeFiles/lib_test.dir/lib_test.cpp.o.requires
.PHONY : lib_test/CMakeFiles/lib_test.dir/requires

lib_test/CMakeFiles/lib_test.dir/clean:
	cd /home/anokl/Projects/C++/project_template/build/lib_test && $(CMAKE_COMMAND) -P CMakeFiles/lib_test.dir/cmake_clean.cmake
.PHONY : lib_test/CMakeFiles/lib_test.dir/clean

lib_test/CMakeFiles/lib_test.dir/depend:
	cd /home/anokl/Projects/C++/project_template/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/anokl/Projects/C++/project_template /home/anokl/Projects/C++/project_template/lib_test /home/anokl/Projects/C++/project_template/build /home/anokl/Projects/C++/project_template/build/lib_test /home/anokl/Projects/C++/project_template/build/lib_test/CMakeFiles/lib_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib_test/CMakeFiles/lib_test.dir/depend

