# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /mnt/c/Users/Splas/Documents/GitHub/GTK-Cours-et-TP

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/Splas/Documents/GitHub/GTK-Cours-et-TP/cmake-build-wsl

# Include any dependencies generated for this target.
include CMakeFiles/start.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/start.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/start.dir/flags.make

CMakeFiles/start.dir/main.c.o: CMakeFiles/start.dir/flags.make
CMakeFiles/start.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Splas/Documents/GitHub/GTK-Cours-et-TP/cmake-build-wsl/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/start.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/start.dir/main.c.o   -c /mnt/c/Users/Splas/Documents/GitHub/GTK-Cours-et-TP/main.c

CMakeFiles/start.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/start.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/Splas/Documents/GitHub/GTK-Cours-et-TP/main.c > CMakeFiles/start.dir/main.c.i

CMakeFiles/start.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/start.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/Splas/Documents/GitHub/GTK-Cours-et-TP/main.c -o CMakeFiles/start.dir/main.c.s

CMakeFiles/start.dir/gtk_functions.c.o: CMakeFiles/start.dir/flags.make
CMakeFiles/start.dir/gtk_functions.c.o: ../gtk_functions.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Splas/Documents/GitHub/GTK-Cours-et-TP/cmake-build-wsl/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/start.dir/gtk_functions.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/start.dir/gtk_functions.c.o   -c /mnt/c/Users/Splas/Documents/GitHub/GTK-Cours-et-TP/gtk_functions.c

CMakeFiles/start.dir/gtk_functions.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/start.dir/gtk_functions.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/Splas/Documents/GitHub/GTK-Cours-et-TP/gtk_functions.c > CMakeFiles/start.dir/gtk_functions.c.i

CMakeFiles/start.dir/gtk_functions.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/start.dir/gtk_functions.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/Splas/Documents/GitHub/GTK-Cours-et-TP/gtk_functions.c -o CMakeFiles/start.dir/gtk_functions.c.s

CMakeFiles/start.dir/structure.c.o: CMakeFiles/start.dir/flags.make
CMakeFiles/start.dir/structure.c.o: ../structure.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Splas/Documents/GitHub/GTK-Cours-et-TP/cmake-build-wsl/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/start.dir/structure.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/start.dir/structure.c.o   -c /mnt/c/Users/Splas/Documents/GitHub/GTK-Cours-et-TP/structure.c

CMakeFiles/start.dir/structure.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/start.dir/structure.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/Splas/Documents/GitHub/GTK-Cours-et-TP/structure.c > CMakeFiles/start.dir/structure.c.i

CMakeFiles/start.dir/structure.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/start.dir/structure.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/Splas/Documents/GitHub/GTK-Cours-et-TP/structure.c -o CMakeFiles/start.dir/structure.c.s

CMakeFiles/start.dir/validate_read.c.o: CMakeFiles/start.dir/flags.make
CMakeFiles/start.dir/validate_read.c.o: ../validate_read.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Splas/Documents/GitHub/GTK-Cours-et-TP/cmake-build-wsl/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/start.dir/validate_read.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/start.dir/validate_read.c.o   -c /mnt/c/Users/Splas/Documents/GitHub/GTK-Cours-et-TP/validate_read.c

CMakeFiles/start.dir/validate_read.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/start.dir/validate_read.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/Splas/Documents/GitHub/GTK-Cours-et-TP/validate_read.c > CMakeFiles/start.dir/validate_read.c.i

CMakeFiles/start.dir/validate_read.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/start.dir/validate_read.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/Splas/Documents/GitHub/GTK-Cours-et-TP/validate_read.c -o CMakeFiles/start.dir/validate_read.c.s

CMakeFiles/start.dir/christophe.c.o: CMakeFiles/start.dir/flags.make
CMakeFiles/start.dir/christophe.c.o: ../christophe.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Splas/Documents/GitHub/GTK-Cours-et-TP/cmake-build-wsl/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/start.dir/christophe.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/start.dir/christophe.c.o   -c /mnt/c/Users/Splas/Documents/GitHub/GTK-Cours-et-TP/christophe.c

CMakeFiles/start.dir/christophe.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/start.dir/christophe.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/Splas/Documents/GitHub/GTK-Cours-et-TP/christophe.c > CMakeFiles/start.dir/christophe.c.i

CMakeFiles/start.dir/christophe.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/start.dir/christophe.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/Splas/Documents/GitHub/GTK-Cours-et-TP/christophe.c -o CMakeFiles/start.dir/christophe.c.s

# Object files for target start
start_OBJECTS = \
"CMakeFiles/start.dir/main.c.o" \
"CMakeFiles/start.dir/gtk_functions.c.o" \
"CMakeFiles/start.dir/structure.c.o" \
"CMakeFiles/start.dir/validate_read.c.o" \
"CMakeFiles/start.dir/christophe.c.o"

# External object files for target start
start_EXTERNAL_OBJECTS =

start: CMakeFiles/start.dir/main.c.o
start: CMakeFiles/start.dir/gtk_functions.c.o
start: CMakeFiles/start.dir/structure.c.o
start: CMakeFiles/start.dir/validate_read.c.o
start: CMakeFiles/start.dir/christophe.c.o
start: CMakeFiles/start.dir/build.make
start: CMakeFiles/start.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/Splas/Documents/GitHub/GTK-Cours-et-TP/cmake-build-wsl/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking C executable start"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/start.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/start.dir/build: start

.PHONY : CMakeFiles/start.dir/build

CMakeFiles/start.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/start.dir/cmake_clean.cmake
.PHONY : CMakeFiles/start.dir/clean

CMakeFiles/start.dir/depend:
	cd /mnt/c/Users/Splas/Documents/GitHub/GTK-Cours-et-TP/cmake-build-wsl && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/Splas/Documents/GitHub/GTK-Cours-et-TP /mnt/c/Users/Splas/Documents/GitHub/GTK-Cours-et-TP /mnt/c/Users/Splas/Documents/GitHub/GTK-Cours-et-TP/cmake-build-wsl /mnt/c/Users/Splas/Documents/GitHub/GTK-Cours-et-TP/cmake-build-wsl /mnt/c/Users/Splas/Documents/GitHub/GTK-Cours-et-TP/cmake-build-wsl/CMakeFiles/start.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/start.dir/depend
