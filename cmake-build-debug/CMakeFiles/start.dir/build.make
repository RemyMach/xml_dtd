# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\Users\Splas\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\202.7660.37\bin\cmake\win\bin\cmake.exe

# The command to remove a file.
RM = C:\Users\Splas\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\202.7660.37\bin\cmake\win\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Splas\Documents\GitHub\xml_C

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Splas\Documents\GitHub\xml_C\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/start.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/start.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/start.dir/flags.make

CMakeFiles/start.dir/main.c.obj: CMakeFiles/start.dir/flags.make
CMakeFiles/start.dir/main.c.obj: CMakeFiles/start.dir/includes_C.rsp
CMakeFiles/start.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Splas\Documents\GitHub\xml_C\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/start.dir/main.c.obj"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\start.dir\main.c.obj   -c C:\Users\Splas\Documents\GitHub\xml_C\main.c

CMakeFiles/start.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/start.dir/main.c.i"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Splas\Documents\GitHub\xml_C\main.c > CMakeFiles\start.dir\main.c.i

CMakeFiles/start.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/start.dir/main.c.s"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\Splas\Documents\GitHub\xml_C\main.c -o CMakeFiles\start.dir\main.c.s

CMakeFiles/start.dir/gtk_functions.c.obj: CMakeFiles/start.dir/flags.make
CMakeFiles/start.dir/gtk_functions.c.obj: CMakeFiles/start.dir/includes_C.rsp
CMakeFiles/start.dir/gtk_functions.c.obj: ../gtk_functions.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Splas\Documents\GitHub\xml_C\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/start.dir/gtk_functions.c.obj"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\start.dir\gtk_functions.c.obj   -c C:\Users\Splas\Documents\GitHub\xml_C\gtk_functions.c

CMakeFiles/start.dir/gtk_functions.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/start.dir/gtk_functions.c.i"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Splas\Documents\GitHub\xml_C\gtk_functions.c > CMakeFiles\start.dir\gtk_functions.c.i

CMakeFiles/start.dir/gtk_functions.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/start.dir/gtk_functions.c.s"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\Splas\Documents\GitHub\xml_C\gtk_functions.c -o CMakeFiles\start.dir\gtk_functions.c.s

# Object files for target start
start_OBJECTS = \
"CMakeFiles/start.dir/main.c.obj" \
"CMakeFiles/start.dir/gtk_functions.c.obj"

# External object files for target start
start_EXTERNAL_OBJECTS =

start.exe: CMakeFiles/start.dir/main.c.obj
start.exe: CMakeFiles/start.dir/gtk_functions.c.obj
start.exe: CMakeFiles/start.dir/build.make
start.exe: CMakeFiles/start.dir/linklibs.rsp
start.exe: CMakeFiles/start.dir/objects1.rsp
start.exe: CMakeFiles/start.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Splas\Documents\GitHub\xml_C\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable start.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\start.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/start.dir/build: start.exe

.PHONY : CMakeFiles/start.dir/build

CMakeFiles/start.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\start.dir\cmake_clean.cmake
.PHONY : CMakeFiles/start.dir/clean

CMakeFiles/start.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Splas\Documents\GitHub\xml_C C:\Users\Splas\Documents\GitHub\xml_C C:\Users\Splas\Documents\GitHub\xml_C\cmake-build-debug C:\Users\Splas\Documents\GitHub\xml_C\cmake-build-debug C:\Users\Splas\Documents\GitHub\xml_C\cmake-build-debug\CMakeFiles\start.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/start.dir/depend

