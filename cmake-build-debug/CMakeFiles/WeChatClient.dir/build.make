# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/victor/CLionProjects/WeChatClient

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/victor/CLionProjects/WeChatClient/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/WeChatClient.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/WeChatClient.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/WeChatClient.dir/flags.make

CMakeFiles/WeChatClient.dir/main.cpp.o: CMakeFiles/WeChatClient.dir/flags.make
CMakeFiles/WeChatClient.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/victor/CLionProjects/WeChatClient/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/WeChatClient.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/WeChatClient.dir/main.cpp.o -c /Users/victor/CLionProjects/WeChatClient/main.cpp

CMakeFiles/WeChatClient.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/WeChatClient.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/victor/CLionProjects/WeChatClient/main.cpp > CMakeFiles/WeChatClient.dir/main.cpp.i

CMakeFiles/WeChatClient.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/WeChatClient.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/victor/CLionProjects/WeChatClient/main.cpp -o CMakeFiles/WeChatClient.dir/main.cpp.s

CMakeFiles/WeChatClient.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/WeChatClient.dir/main.cpp.o.requires

CMakeFiles/WeChatClient.dir/main.cpp.o.provides: CMakeFiles/WeChatClient.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/WeChatClient.dir/build.make CMakeFiles/WeChatClient.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/WeChatClient.dir/main.cpp.o.provides

CMakeFiles/WeChatClient.dir/main.cpp.o.provides.build: CMakeFiles/WeChatClient.dir/main.cpp.o


CMakeFiles/WeChatClient.dir/Envolop.cpp.o: CMakeFiles/WeChatClient.dir/flags.make
CMakeFiles/WeChatClient.dir/Envolop.cpp.o: ../Envolop.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/victor/CLionProjects/WeChatClient/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/WeChatClient.dir/Envolop.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/WeChatClient.dir/Envolop.cpp.o -c /Users/victor/CLionProjects/WeChatClient/Envolop.cpp

CMakeFiles/WeChatClient.dir/Envolop.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/WeChatClient.dir/Envolop.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/victor/CLionProjects/WeChatClient/Envolop.cpp > CMakeFiles/WeChatClient.dir/Envolop.cpp.i

CMakeFiles/WeChatClient.dir/Envolop.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/WeChatClient.dir/Envolop.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/victor/CLionProjects/WeChatClient/Envolop.cpp -o CMakeFiles/WeChatClient.dir/Envolop.cpp.s

CMakeFiles/WeChatClient.dir/Envolop.cpp.o.requires:

.PHONY : CMakeFiles/WeChatClient.dir/Envolop.cpp.o.requires

CMakeFiles/WeChatClient.dir/Envolop.cpp.o.provides: CMakeFiles/WeChatClient.dir/Envolop.cpp.o.requires
	$(MAKE) -f CMakeFiles/WeChatClient.dir/build.make CMakeFiles/WeChatClient.dir/Envolop.cpp.o.provides.build
.PHONY : CMakeFiles/WeChatClient.dir/Envolop.cpp.o.provides

CMakeFiles/WeChatClient.dir/Envolop.cpp.o.provides.build: CMakeFiles/WeChatClient.dir/Envolop.cpp.o


# Object files for target WeChatClient
WeChatClient_OBJECTS = \
"CMakeFiles/WeChatClient.dir/main.cpp.o" \
"CMakeFiles/WeChatClient.dir/Envolop.cpp.o"

# External object files for target WeChatClient
WeChatClient_EXTERNAL_OBJECTS =

WeChatClient: CMakeFiles/WeChatClient.dir/main.cpp.o
WeChatClient: CMakeFiles/WeChatClient.dir/Envolop.cpp.o
WeChatClient: CMakeFiles/WeChatClient.dir/build.make
WeChatClient: CMakeFiles/WeChatClient.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/victor/CLionProjects/WeChatClient/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable WeChatClient"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/WeChatClient.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/WeChatClient.dir/build: WeChatClient

.PHONY : CMakeFiles/WeChatClient.dir/build

CMakeFiles/WeChatClient.dir/requires: CMakeFiles/WeChatClient.dir/main.cpp.o.requires
CMakeFiles/WeChatClient.dir/requires: CMakeFiles/WeChatClient.dir/Envolop.cpp.o.requires

.PHONY : CMakeFiles/WeChatClient.dir/requires

CMakeFiles/WeChatClient.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/WeChatClient.dir/cmake_clean.cmake
.PHONY : CMakeFiles/WeChatClient.dir/clean

CMakeFiles/WeChatClient.dir/depend:
	cd /Users/victor/CLionProjects/WeChatClient/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/victor/CLionProjects/WeChatClient /Users/victor/CLionProjects/WeChatClient /Users/victor/CLionProjects/WeChatClient/cmake-build-debug /Users/victor/CLionProjects/WeChatClient/cmake-build-debug /Users/victor/CLionProjects/WeChatClient/cmake-build-debug/CMakeFiles/WeChatClient.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/WeChatClient.dir/depend

