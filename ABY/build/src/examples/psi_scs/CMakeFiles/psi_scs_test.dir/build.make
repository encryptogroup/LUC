# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/mineorbit/CRYPTO-LUC/ABY

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mineorbit/CRYPTO-LUC/ABY/build

# Include any dependencies generated for this target.
include src/examples/psi_scs/CMakeFiles/psi_scs_test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/examples/psi_scs/CMakeFiles/psi_scs_test.dir/compiler_depend.make

# Include the progress variables for this target.
include src/examples/psi_scs/CMakeFiles/psi_scs_test.dir/progress.make

# Include the compile flags for this target's objects.
include src/examples/psi_scs/CMakeFiles/psi_scs_test.dir/flags.make

src/examples/psi_scs/CMakeFiles/psi_scs_test.dir/psi_scs.cpp.o: src/examples/psi_scs/CMakeFiles/psi_scs_test.dir/flags.make
src/examples/psi_scs/CMakeFiles/psi_scs_test.dir/psi_scs.cpp.o: ../src/examples/psi_scs/psi_scs.cpp
src/examples/psi_scs/CMakeFiles/psi_scs_test.dir/psi_scs.cpp.o: src/examples/psi_scs/CMakeFiles/psi_scs_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mineorbit/CRYPTO-LUC/ABY/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/examples/psi_scs/CMakeFiles/psi_scs_test.dir/psi_scs.cpp.o"
	cd /home/mineorbit/CRYPTO-LUC/ABY/build/src/examples/psi_scs && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/examples/psi_scs/CMakeFiles/psi_scs_test.dir/psi_scs.cpp.o -MF CMakeFiles/psi_scs_test.dir/psi_scs.cpp.o.d -o CMakeFiles/psi_scs_test.dir/psi_scs.cpp.o -c /home/mineorbit/CRYPTO-LUC/ABY/src/examples/psi_scs/psi_scs.cpp

src/examples/psi_scs/CMakeFiles/psi_scs_test.dir/psi_scs.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/psi_scs_test.dir/psi_scs.cpp.i"
	cd /home/mineorbit/CRYPTO-LUC/ABY/build/src/examples/psi_scs && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mineorbit/CRYPTO-LUC/ABY/src/examples/psi_scs/psi_scs.cpp > CMakeFiles/psi_scs_test.dir/psi_scs.cpp.i

src/examples/psi_scs/CMakeFiles/psi_scs_test.dir/psi_scs.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/psi_scs_test.dir/psi_scs.cpp.s"
	cd /home/mineorbit/CRYPTO-LUC/ABY/build/src/examples/psi_scs && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mineorbit/CRYPTO-LUC/ABY/src/examples/psi_scs/psi_scs.cpp -o CMakeFiles/psi_scs_test.dir/psi_scs.cpp.s

src/examples/psi_scs/CMakeFiles/psi_scs_test.dir/common/sort_compare_shuffle.cpp.o: src/examples/psi_scs/CMakeFiles/psi_scs_test.dir/flags.make
src/examples/psi_scs/CMakeFiles/psi_scs_test.dir/common/sort_compare_shuffle.cpp.o: ../src/examples/psi_scs/common/sort_compare_shuffle.cpp
src/examples/psi_scs/CMakeFiles/psi_scs_test.dir/common/sort_compare_shuffle.cpp.o: src/examples/psi_scs/CMakeFiles/psi_scs_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mineorbit/CRYPTO-LUC/ABY/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/examples/psi_scs/CMakeFiles/psi_scs_test.dir/common/sort_compare_shuffle.cpp.o"
	cd /home/mineorbit/CRYPTO-LUC/ABY/build/src/examples/psi_scs && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/examples/psi_scs/CMakeFiles/psi_scs_test.dir/common/sort_compare_shuffle.cpp.o -MF CMakeFiles/psi_scs_test.dir/common/sort_compare_shuffle.cpp.o.d -o CMakeFiles/psi_scs_test.dir/common/sort_compare_shuffle.cpp.o -c /home/mineorbit/CRYPTO-LUC/ABY/src/examples/psi_scs/common/sort_compare_shuffle.cpp

src/examples/psi_scs/CMakeFiles/psi_scs_test.dir/common/sort_compare_shuffle.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/psi_scs_test.dir/common/sort_compare_shuffle.cpp.i"
	cd /home/mineorbit/CRYPTO-LUC/ABY/build/src/examples/psi_scs && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mineorbit/CRYPTO-LUC/ABY/src/examples/psi_scs/common/sort_compare_shuffle.cpp > CMakeFiles/psi_scs_test.dir/common/sort_compare_shuffle.cpp.i

src/examples/psi_scs/CMakeFiles/psi_scs_test.dir/common/sort_compare_shuffle.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/psi_scs_test.dir/common/sort_compare_shuffle.cpp.s"
	cd /home/mineorbit/CRYPTO-LUC/ABY/build/src/examples/psi_scs && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mineorbit/CRYPTO-LUC/ABY/src/examples/psi_scs/common/sort_compare_shuffle.cpp -o CMakeFiles/psi_scs_test.dir/common/sort_compare_shuffle.cpp.s

src/examples/psi_scs/CMakeFiles/psi_scs_test.dir/common/WaksmanPermutation.cpp.o: src/examples/psi_scs/CMakeFiles/psi_scs_test.dir/flags.make
src/examples/psi_scs/CMakeFiles/psi_scs_test.dir/common/WaksmanPermutation.cpp.o: ../src/examples/psi_scs/common/WaksmanPermutation.cpp
src/examples/psi_scs/CMakeFiles/psi_scs_test.dir/common/WaksmanPermutation.cpp.o: src/examples/psi_scs/CMakeFiles/psi_scs_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mineorbit/CRYPTO-LUC/ABY/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/examples/psi_scs/CMakeFiles/psi_scs_test.dir/common/WaksmanPermutation.cpp.o"
	cd /home/mineorbit/CRYPTO-LUC/ABY/build/src/examples/psi_scs && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/examples/psi_scs/CMakeFiles/psi_scs_test.dir/common/WaksmanPermutation.cpp.o -MF CMakeFiles/psi_scs_test.dir/common/WaksmanPermutation.cpp.o.d -o CMakeFiles/psi_scs_test.dir/common/WaksmanPermutation.cpp.o -c /home/mineorbit/CRYPTO-LUC/ABY/src/examples/psi_scs/common/WaksmanPermutation.cpp

src/examples/psi_scs/CMakeFiles/psi_scs_test.dir/common/WaksmanPermutation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/psi_scs_test.dir/common/WaksmanPermutation.cpp.i"
	cd /home/mineorbit/CRYPTO-LUC/ABY/build/src/examples/psi_scs && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mineorbit/CRYPTO-LUC/ABY/src/examples/psi_scs/common/WaksmanPermutation.cpp > CMakeFiles/psi_scs_test.dir/common/WaksmanPermutation.cpp.i

src/examples/psi_scs/CMakeFiles/psi_scs_test.dir/common/WaksmanPermutation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/psi_scs_test.dir/common/WaksmanPermutation.cpp.s"
	cd /home/mineorbit/CRYPTO-LUC/ABY/build/src/examples/psi_scs && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mineorbit/CRYPTO-LUC/ABY/src/examples/psi_scs/common/WaksmanPermutation.cpp -o CMakeFiles/psi_scs_test.dir/common/WaksmanPermutation.cpp.s

# Object files for target psi_scs_test
psi_scs_test_OBJECTS = \
"CMakeFiles/psi_scs_test.dir/psi_scs.cpp.o" \
"CMakeFiles/psi_scs_test.dir/common/sort_compare_shuffle.cpp.o" \
"CMakeFiles/psi_scs_test.dir/common/WaksmanPermutation.cpp.o"

# External object files for target psi_scs_test
psi_scs_test_EXTERNAL_OBJECTS =

bin/psi_scs_test: src/examples/psi_scs/CMakeFiles/psi_scs_test.dir/psi_scs.cpp.o
bin/psi_scs_test: src/examples/psi_scs/CMakeFiles/psi_scs_test.dir/common/sort_compare_shuffle.cpp.o
bin/psi_scs_test: src/examples/psi_scs/CMakeFiles/psi_scs_test.dir/common/WaksmanPermutation.cpp.o
bin/psi_scs_test: src/examples/psi_scs/CMakeFiles/psi_scs_test.dir/build.make
bin/psi_scs_test: lib/libaby.a
bin/psi_scs_test: lib/libencrypto_utils.a
bin/psi_scs_test: lib/libotextension.a
bin/psi_scs_test: lib/libencrypto_utils.a
bin/psi_scs_test: /usr/lib/x86_64-linux-gnu/libboost_system.so.1.74.0
bin/psi_scs_test: /usr/lib/x86_64-linux-gnu/libboost_thread.so.1.74.0
bin/psi_scs_test: /usr/lib/x86_64-linux-gnu/libboost_atomic.so.1.74.0
bin/psi_scs_test: /usr/lib/x86_64-linux-gnu/libgmp.so
bin/psi_scs_test: /usr/lib/x86_64-linux-gnu/libgmpxx.so
bin/psi_scs_test: /usr/lib/x86_64-linux-gnu/libcrypto.so
bin/psi_scs_test: lib/librelic_s.a
bin/psi_scs_test: lib/librelic_s.a
bin/psi_scs_test: /usr/lib/x86_64-linux-gnu/libgmp.so
bin/psi_scs_test: /usr/lib/x86_64-linux-gnu/libgmp.so
bin/psi_scs_test: src/examples/psi_scs/CMakeFiles/psi_scs_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mineorbit/CRYPTO-LUC/ABY/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable ../../../bin/psi_scs_test"
	cd /home/mineorbit/CRYPTO-LUC/ABY/build/src/examples/psi_scs && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/psi_scs_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/examples/psi_scs/CMakeFiles/psi_scs_test.dir/build: bin/psi_scs_test
.PHONY : src/examples/psi_scs/CMakeFiles/psi_scs_test.dir/build

src/examples/psi_scs/CMakeFiles/psi_scs_test.dir/clean:
	cd /home/mineorbit/CRYPTO-LUC/ABY/build/src/examples/psi_scs && $(CMAKE_COMMAND) -P CMakeFiles/psi_scs_test.dir/cmake_clean.cmake
.PHONY : src/examples/psi_scs/CMakeFiles/psi_scs_test.dir/clean

src/examples/psi_scs/CMakeFiles/psi_scs_test.dir/depend:
	cd /home/mineorbit/CRYPTO-LUC/ABY/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mineorbit/CRYPTO-LUC/ABY /home/mineorbit/CRYPTO-LUC/ABY/src/examples/psi_scs /home/mineorbit/CRYPTO-LUC/ABY/build /home/mineorbit/CRYPTO-LUC/ABY/build/src/examples/psi_scs /home/mineorbit/CRYPTO-LUC/ABY/build/src/examples/psi_scs/CMakeFiles/psi_scs_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/examples/psi_scs/CMakeFiles/psi_scs_test.dir/depend

