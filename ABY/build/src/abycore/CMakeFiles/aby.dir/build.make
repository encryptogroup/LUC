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
include src/abycore/CMakeFiles/aby.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/abycore/CMakeFiles/aby.dir/compiler_depend.make

# Include the progress variables for this target.
include src/abycore/CMakeFiles/aby.dir/progress.make

# Include the compile flags for this target's objects.
include src/abycore/CMakeFiles/aby.dir/flags.make

src/abycore/CMakeFiles/aby.dir/aby/abyparty.cpp.o: src/abycore/CMakeFiles/aby.dir/flags.make
src/abycore/CMakeFiles/aby.dir/aby/abyparty.cpp.o: ../src/abycore/aby/abyparty.cpp
src/abycore/CMakeFiles/aby.dir/aby/abyparty.cpp.o: src/abycore/CMakeFiles/aby.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mineorbit/CRYPTO-LUC/ABY/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/abycore/CMakeFiles/aby.dir/aby/abyparty.cpp.o"
	cd /home/mineorbit/CRYPTO-LUC/ABY/build/src/abycore && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/abycore/CMakeFiles/aby.dir/aby/abyparty.cpp.o -MF CMakeFiles/aby.dir/aby/abyparty.cpp.o.d -o CMakeFiles/aby.dir/aby/abyparty.cpp.o -c /home/mineorbit/CRYPTO-LUC/ABY/src/abycore/aby/abyparty.cpp

src/abycore/CMakeFiles/aby.dir/aby/abyparty.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/aby.dir/aby/abyparty.cpp.i"
	cd /home/mineorbit/CRYPTO-LUC/ABY/build/src/abycore && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mineorbit/CRYPTO-LUC/ABY/src/abycore/aby/abyparty.cpp > CMakeFiles/aby.dir/aby/abyparty.cpp.i

src/abycore/CMakeFiles/aby.dir/aby/abyparty.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/aby.dir/aby/abyparty.cpp.s"
	cd /home/mineorbit/CRYPTO-LUC/ABY/build/src/abycore && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mineorbit/CRYPTO-LUC/ABY/src/abycore/aby/abyparty.cpp -o CMakeFiles/aby.dir/aby/abyparty.cpp.s

src/abycore/CMakeFiles/aby.dir/aby/abysetup.cpp.o: src/abycore/CMakeFiles/aby.dir/flags.make
src/abycore/CMakeFiles/aby.dir/aby/abysetup.cpp.o: ../src/abycore/aby/abysetup.cpp
src/abycore/CMakeFiles/aby.dir/aby/abysetup.cpp.o: src/abycore/CMakeFiles/aby.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mineorbit/CRYPTO-LUC/ABY/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/abycore/CMakeFiles/aby.dir/aby/abysetup.cpp.o"
	cd /home/mineorbit/CRYPTO-LUC/ABY/build/src/abycore && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/abycore/CMakeFiles/aby.dir/aby/abysetup.cpp.o -MF CMakeFiles/aby.dir/aby/abysetup.cpp.o.d -o CMakeFiles/aby.dir/aby/abysetup.cpp.o -c /home/mineorbit/CRYPTO-LUC/ABY/src/abycore/aby/abysetup.cpp

src/abycore/CMakeFiles/aby.dir/aby/abysetup.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/aby.dir/aby/abysetup.cpp.i"
	cd /home/mineorbit/CRYPTO-LUC/ABY/build/src/abycore && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mineorbit/CRYPTO-LUC/ABY/src/abycore/aby/abysetup.cpp > CMakeFiles/aby.dir/aby/abysetup.cpp.i

src/abycore/CMakeFiles/aby.dir/aby/abysetup.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/aby.dir/aby/abysetup.cpp.s"
	cd /home/mineorbit/CRYPTO-LUC/ABY/build/src/abycore && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mineorbit/CRYPTO-LUC/ABY/src/abycore/aby/abysetup.cpp -o CMakeFiles/aby.dir/aby/abysetup.cpp.s

src/abycore/CMakeFiles/aby.dir/circuit/abycircuit.cpp.o: src/abycore/CMakeFiles/aby.dir/flags.make
src/abycore/CMakeFiles/aby.dir/circuit/abycircuit.cpp.o: ../src/abycore/circuit/abycircuit.cpp
src/abycore/CMakeFiles/aby.dir/circuit/abycircuit.cpp.o: src/abycore/CMakeFiles/aby.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mineorbit/CRYPTO-LUC/ABY/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/abycore/CMakeFiles/aby.dir/circuit/abycircuit.cpp.o"
	cd /home/mineorbit/CRYPTO-LUC/ABY/build/src/abycore && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/abycore/CMakeFiles/aby.dir/circuit/abycircuit.cpp.o -MF CMakeFiles/aby.dir/circuit/abycircuit.cpp.o.d -o CMakeFiles/aby.dir/circuit/abycircuit.cpp.o -c /home/mineorbit/CRYPTO-LUC/ABY/src/abycore/circuit/abycircuit.cpp

src/abycore/CMakeFiles/aby.dir/circuit/abycircuit.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/aby.dir/circuit/abycircuit.cpp.i"
	cd /home/mineorbit/CRYPTO-LUC/ABY/build/src/abycore && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mineorbit/CRYPTO-LUC/ABY/src/abycore/circuit/abycircuit.cpp > CMakeFiles/aby.dir/circuit/abycircuit.cpp.i

src/abycore/CMakeFiles/aby.dir/circuit/abycircuit.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/aby.dir/circuit/abycircuit.cpp.s"
	cd /home/mineorbit/CRYPTO-LUC/ABY/build/src/abycore && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mineorbit/CRYPTO-LUC/ABY/src/abycore/circuit/abycircuit.cpp -o CMakeFiles/aby.dir/circuit/abycircuit.cpp.s

src/abycore/CMakeFiles/aby.dir/circuit/arithmeticcircuits.cpp.o: src/abycore/CMakeFiles/aby.dir/flags.make
src/abycore/CMakeFiles/aby.dir/circuit/arithmeticcircuits.cpp.o: ../src/abycore/circuit/arithmeticcircuits.cpp
src/abycore/CMakeFiles/aby.dir/circuit/arithmeticcircuits.cpp.o: src/abycore/CMakeFiles/aby.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mineorbit/CRYPTO-LUC/ABY/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/abycore/CMakeFiles/aby.dir/circuit/arithmeticcircuits.cpp.o"
	cd /home/mineorbit/CRYPTO-LUC/ABY/build/src/abycore && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/abycore/CMakeFiles/aby.dir/circuit/arithmeticcircuits.cpp.o -MF CMakeFiles/aby.dir/circuit/arithmeticcircuits.cpp.o.d -o CMakeFiles/aby.dir/circuit/arithmeticcircuits.cpp.o -c /home/mineorbit/CRYPTO-LUC/ABY/src/abycore/circuit/arithmeticcircuits.cpp

src/abycore/CMakeFiles/aby.dir/circuit/arithmeticcircuits.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/aby.dir/circuit/arithmeticcircuits.cpp.i"
	cd /home/mineorbit/CRYPTO-LUC/ABY/build/src/abycore && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mineorbit/CRYPTO-LUC/ABY/src/abycore/circuit/arithmeticcircuits.cpp > CMakeFiles/aby.dir/circuit/arithmeticcircuits.cpp.i

src/abycore/CMakeFiles/aby.dir/circuit/arithmeticcircuits.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/aby.dir/circuit/arithmeticcircuits.cpp.s"
	cd /home/mineorbit/CRYPTO-LUC/ABY/build/src/abycore && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mineorbit/CRYPTO-LUC/ABY/src/abycore/circuit/arithmeticcircuits.cpp -o CMakeFiles/aby.dir/circuit/arithmeticcircuits.cpp.s

src/abycore/CMakeFiles/aby.dir/circuit/booleancircuits.cpp.o: src/abycore/CMakeFiles/aby.dir/flags.make
src/abycore/CMakeFiles/aby.dir/circuit/booleancircuits.cpp.o: ../src/abycore/circuit/booleancircuits.cpp
src/abycore/CMakeFiles/aby.dir/circuit/booleancircuits.cpp.o: src/abycore/CMakeFiles/aby.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mineorbit/CRYPTO-LUC/ABY/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object src/abycore/CMakeFiles/aby.dir/circuit/booleancircuits.cpp.o"
	cd /home/mineorbit/CRYPTO-LUC/ABY/build/src/abycore && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/abycore/CMakeFiles/aby.dir/circuit/booleancircuits.cpp.o -MF CMakeFiles/aby.dir/circuit/booleancircuits.cpp.o.d -o CMakeFiles/aby.dir/circuit/booleancircuits.cpp.o -c /home/mineorbit/CRYPTO-LUC/ABY/src/abycore/circuit/booleancircuits.cpp

src/abycore/CMakeFiles/aby.dir/circuit/booleancircuits.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/aby.dir/circuit/booleancircuits.cpp.i"
	cd /home/mineorbit/CRYPTO-LUC/ABY/build/src/abycore && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mineorbit/CRYPTO-LUC/ABY/src/abycore/circuit/booleancircuits.cpp > CMakeFiles/aby.dir/circuit/booleancircuits.cpp.i

src/abycore/CMakeFiles/aby.dir/circuit/booleancircuits.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/aby.dir/circuit/booleancircuits.cpp.s"
	cd /home/mineorbit/CRYPTO-LUC/ABY/build/src/abycore && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mineorbit/CRYPTO-LUC/ABY/src/abycore/circuit/booleancircuits.cpp -o CMakeFiles/aby.dir/circuit/booleancircuits.cpp.s

src/abycore/CMakeFiles/aby.dir/circuit/circuit.cpp.o: src/abycore/CMakeFiles/aby.dir/flags.make
src/abycore/CMakeFiles/aby.dir/circuit/circuit.cpp.o: ../src/abycore/circuit/circuit.cpp
src/abycore/CMakeFiles/aby.dir/circuit/circuit.cpp.o: src/abycore/CMakeFiles/aby.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mineorbit/CRYPTO-LUC/ABY/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object src/abycore/CMakeFiles/aby.dir/circuit/circuit.cpp.o"
	cd /home/mineorbit/CRYPTO-LUC/ABY/build/src/abycore && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/abycore/CMakeFiles/aby.dir/circuit/circuit.cpp.o -MF CMakeFiles/aby.dir/circuit/circuit.cpp.o.d -o CMakeFiles/aby.dir/circuit/circuit.cpp.o -c /home/mineorbit/CRYPTO-LUC/ABY/src/abycore/circuit/circuit.cpp

src/abycore/CMakeFiles/aby.dir/circuit/circuit.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/aby.dir/circuit/circuit.cpp.i"
	cd /home/mineorbit/CRYPTO-LUC/ABY/build/src/abycore && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mineorbit/CRYPTO-LUC/ABY/src/abycore/circuit/circuit.cpp > CMakeFiles/aby.dir/circuit/circuit.cpp.i

src/abycore/CMakeFiles/aby.dir/circuit/circuit.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/aby.dir/circuit/circuit.cpp.s"
	cd /home/mineorbit/CRYPTO-LUC/ABY/build/src/abycore && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mineorbit/CRYPTO-LUC/ABY/src/abycore/circuit/circuit.cpp -o CMakeFiles/aby.dir/circuit/circuit.cpp.s

src/abycore/CMakeFiles/aby.dir/circuit/share.cpp.o: src/abycore/CMakeFiles/aby.dir/flags.make
src/abycore/CMakeFiles/aby.dir/circuit/share.cpp.o: ../src/abycore/circuit/share.cpp
src/abycore/CMakeFiles/aby.dir/circuit/share.cpp.o: src/abycore/CMakeFiles/aby.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mineorbit/CRYPTO-LUC/ABY/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object src/abycore/CMakeFiles/aby.dir/circuit/share.cpp.o"
	cd /home/mineorbit/CRYPTO-LUC/ABY/build/src/abycore && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/abycore/CMakeFiles/aby.dir/circuit/share.cpp.o -MF CMakeFiles/aby.dir/circuit/share.cpp.o.d -o CMakeFiles/aby.dir/circuit/share.cpp.o -c /home/mineorbit/CRYPTO-LUC/ABY/src/abycore/circuit/share.cpp

src/abycore/CMakeFiles/aby.dir/circuit/share.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/aby.dir/circuit/share.cpp.i"
	cd /home/mineorbit/CRYPTO-LUC/ABY/build/src/abycore && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mineorbit/CRYPTO-LUC/ABY/src/abycore/circuit/share.cpp > CMakeFiles/aby.dir/circuit/share.cpp.i

src/abycore/CMakeFiles/aby.dir/circuit/share.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/aby.dir/circuit/share.cpp.s"
	cd /home/mineorbit/CRYPTO-LUC/ABY/build/src/abycore && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mineorbit/CRYPTO-LUC/ABY/src/abycore/circuit/share.cpp -o CMakeFiles/aby.dir/circuit/share.cpp.s

src/abycore/CMakeFiles/aby.dir/DGK/dgkparty.cpp.o: src/abycore/CMakeFiles/aby.dir/flags.make
src/abycore/CMakeFiles/aby.dir/DGK/dgkparty.cpp.o: ../src/abycore/DGK/dgkparty.cpp
src/abycore/CMakeFiles/aby.dir/DGK/dgkparty.cpp.o: src/abycore/CMakeFiles/aby.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mineorbit/CRYPTO-LUC/ABY/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object src/abycore/CMakeFiles/aby.dir/DGK/dgkparty.cpp.o"
	cd /home/mineorbit/CRYPTO-LUC/ABY/build/src/abycore && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/abycore/CMakeFiles/aby.dir/DGK/dgkparty.cpp.o -MF CMakeFiles/aby.dir/DGK/dgkparty.cpp.o.d -o CMakeFiles/aby.dir/DGK/dgkparty.cpp.o -c /home/mineorbit/CRYPTO-LUC/ABY/src/abycore/DGK/dgkparty.cpp

src/abycore/CMakeFiles/aby.dir/DGK/dgkparty.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/aby.dir/DGK/dgkparty.cpp.i"
	cd /home/mineorbit/CRYPTO-LUC/ABY/build/src/abycore && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mineorbit/CRYPTO-LUC/ABY/src/abycore/DGK/dgkparty.cpp > CMakeFiles/aby.dir/DGK/dgkparty.cpp.i

src/abycore/CMakeFiles/aby.dir/DGK/dgkparty.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/aby.dir/DGK/dgkparty.cpp.s"
	cd /home/mineorbit/CRYPTO-LUC/ABY/build/src/abycore && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mineorbit/CRYPTO-LUC/ABY/src/abycore/DGK/dgkparty.cpp -o CMakeFiles/aby.dir/DGK/dgkparty.cpp.s

src/abycore/CMakeFiles/aby.dir/DJN/djnparty.cpp.o: src/abycore/CMakeFiles/aby.dir/flags.make
src/abycore/CMakeFiles/aby.dir/DJN/djnparty.cpp.o: ../src/abycore/DJN/djnparty.cpp
src/abycore/CMakeFiles/aby.dir/DJN/djnparty.cpp.o: src/abycore/CMakeFiles/aby.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mineorbit/CRYPTO-LUC/ABY/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object src/abycore/CMakeFiles/aby.dir/DJN/djnparty.cpp.o"
	cd /home/mineorbit/CRYPTO-LUC/ABY/build/src/abycore && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/abycore/CMakeFiles/aby.dir/DJN/djnparty.cpp.o -MF CMakeFiles/aby.dir/DJN/djnparty.cpp.o.d -o CMakeFiles/aby.dir/DJN/djnparty.cpp.o -c /home/mineorbit/CRYPTO-LUC/ABY/src/abycore/DJN/djnparty.cpp

src/abycore/CMakeFiles/aby.dir/DJN/djnparty.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/aby.dir/DJN/djnparty.cpp.i"
	cd /home/mineorbit/CRYPTO-LUC/ABY/build/src/abycore && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mineorbit/CRYPTO-LUC/ABY/src/abycore/DJN/djnparty.cpp > CMakeFiles/aby.dir/DJN/djnparty.cpp.i

src/abycore/CMakeFiles/aby.dir/DJN/djnparty.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/aby.dir/DJN/djnparty.cpp.s"
	cd /home/mineorbit/CRYPTO-LUC/ABY/build/src/abycore && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mineorbit/CRYPTO-LUC/ABY/src/abycore/DJN/djnparty.cpp -o CMakeFiles/aby.dir/DJN/djnparty.cpp.s

src/abycore/CMakeFiles/aby.dir/sharing/arithsharing.cpp.o: src/abycore/CMakeFiles/aby.dir/flags.make
src/abycore/CMakeFiles/aby.dir/sharing/arithsharing.cpp.o: ../src/abycore/sharing/arithsharing.cpp
src/abycore/CMakeFiles/aby.dir/sharing/arithsharing.cpp.o: src/abycore/CMakeFiles/aby.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mineorbit/CRYPTO-LUC/ABY/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object src/abycore/CMakeFiles/aby.dir/sharing/arithsharing.cpp.o"
	cd /home/mineorbit/CRYPTO-LUC/ABY/build/src/abycore && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/abycore/CMakeFiles/aby.dir/sharing/arithsharing.cpp.o -MF CMakeFiles/aby.dir/sharing/arithsharing.cpp.o.d -o CMakeFiles/aby.dir/sharing/arithsharing.cpp.o -c /home/mineorbit/CRYPTO-LUC/ABY/src/abycore/sharing/arithsharing.cpp

src/abycore/CMakeFiles/aby.dir/sharing/arithsharing.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/aby.dir/sharing/arithsharing.cpp.i"
	cd /home/mineorbit/CRYPTO-LUC/ABY/build/src/abycore && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mineorbit/CRYPTO-LUC/ABY/src/abycore/sharing/arithsharing.cpp > CMakeFiles/aby.dir/sharing/arithsharing.cpp.i

src/abycore/CMakeFiles/aby.dir/sharing/arithsharing.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/aby.dir/sharing/arithsharing.cpp.s"
	cd /home/mineorbit/CRYPTO-LUC/ABY/build/src/abycore && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mineorbit/CRYPTO-LUC/ABY/src/abycore/sharing/arithsharing.cpp -o CMakeFiles/aby.dir/sharing/arithsharing.cpp.s

src/abycore/CMakeFiles/aby.dir/sharing/boolsharing.cpp.o: src/abycore/CMakeFiles/aby.dir/flags.make
src/abycore/CMakeFiles/aby.dir/sharing/boolsharing.cpp.o: ../src/abycore/sharing/boolsharing.cpp
src/abycore/CMakeFiles/aby.dir/sharing/boolsharing.cpp.o: src/abycore/CMakeFiles/aby.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mineorbit/CRYPTO-LUC/ABY/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object src/abycore/CMakeFiles/aby.dir/sharing/boolsharing.cpp.o"
	cd /home/mineorbit/CRYPTO-LUC/ABY/build/src/abycore && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/abycore/CMakeFiles/aby.dir/sharing/boolsharing.cpp.o -MF CMakeFiles/aby.dir/sharing/boolsharing.cpp.o.d -o CMakeFiles/aby.dir/sharing/boolsharing.cpp.o -c /home/mineorbit/CRYPTO-LUC/ABY/src/abycore/sharing/boolsharing.cpp

src/abycore/CMakeFiles/aby.dir/sharing/boolsharing.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/aby.dir/sharing/boolsharing.cpp.i"
	cd /home/mineorbit/CRYPTO-LUC/ABY/build/src/abycore && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mineorbit/CRYPTO-LUC/ABY/src/abycore/sharing/boolsharing.cpp > CMakeFiles/aby.dir/sharing/boolsharing.cpp.i

src/abycore/CMakeFiles/aby.dir/sharing/boolsharing.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/aby.dir/sharing/boolsharing.cpp.s"
	cd /home/mineorbit/CRYPTO-LUC/ABY/build/src/abycore && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mineorbit/CRYPTO-LUC/ABY/src/abycore/sharing/boolsharing.cpp -o CMakeFiles/aby.dir/sharing/boolsharing.cpp.s

src/abycore/CMakeFiles/aby.dir/sharing/sharing.cpp.o: src/abycore/CMakeFiles/aby.dir/flags.make
src/abycore/CMakeFiles/aby.dir/sharing/sharing.cpp.o: ../src/abycore/sharing/sharing.cpp
src/abycore/CMakeFiles/aby.dir/sharing/sharing.cpp.o: src/abycore/CMakeFiles/aby.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mineorbit/CRYPTO-LUC/ABY/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object src/abycore/CMakeFiles/aby.dir/sharing/sharing.cpp.o"
	cd /home/mineorbit/CRYPTO-LUC/ABY/build/src/abycore && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/abycore/CMakeFiles/aby.dir/sharing/sharing.cpp.o -MF CMakeFiles/aby.dir/sharing/sharing.cpp.o.d -o CMakeFiles/aby.dir/sharing/sharing.cpp.o -c /home/mineorbit/CRYPTO-LUC/ABY/src/abycore/sharing/sharing.cpp

src/abycore/CMakeFiles/aby.dir/sharing/sharing.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/aby.dir/sharing/sharing.cpp.i"
	cd /home/mineorbit/CRYPTO-LUC/ABY/build/src/abycore && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mineorbit/CRYPTO-LUC/ABY/src/abycore/sharing/sharing.cpp > CMakeFiles/aby.dir/sharing/sharing.cpp.i

src/abycore/CMakeFiles/aby.dir/sharing/sharing.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/aby.dir/sharing/sharing.cpp.s"
	cd /home/mineorbit/CRYPTO-LUC/ABY/build/src/abycore && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mineorbit/CRYPTO-LUC/ABY/src/abycore/sharing/sharing.cpp -o CMakeFiles/aby.dir/sharing/sharing.cpp.s

src/abycore/CMakeFiles/aby.dir/sharing/splut.cpp.o: src/abycore/CMakeFiles/aby.dir/flags.make
src/abycore/CMakeFiles/aby.dir/sharing/splut.cpp.o: ../src/abycore/sharing/splut.cpp
src/abycore/CMakeFiles/aby.dir/sharing/splut.cpp.o: src/abycore/CMakeFiles/aby.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mineorbit/CRYPTO-LUC/ABY/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object src/abycore/CMakeFiles/aby.dir/sharing/splut.cpp.o"
	cd /home/mineorbit/CRYPTO-LUC/ABY/build/src/abycore && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/abycore/CMakeFiles/aby.dir/sharing/splut.cpp.o -MF CMakeFiles/aby.dir/sharing/splut.cpp.o.d -o CMakeFiles/aby.dir/sharing/splut.cpp.o -c /home/mineorbit/CRYPTO-LUC/ABY/src/abycore/sharing/splut.cpp

src/abycore/CMakeFiles/aby.dir/sharing/splut.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/aby.dir/sharing/splut.cpp.i"
	cd /home/mineorbit/CRYPTO-LUC/ABY/build/src/abycore && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mineorbit/CRYPTO-LUC/ABY/src/abycore/sharing/splut.cpp > CMakeFiles/aby.dir/sharing/splut.cpp.i

src/abycore/CMakeFiles/aby.dir/sharing/splut.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/aby.dir/sharing/splut.cpp.s"
	cd /home/mineorbit/CRYPTO-LUC/ABY/build/src/abycore && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mineorbit/CRYPTO-LUC/ABY/src/abycore/sharing/splut.cpp -o CMakeFiles/aby.dir/sharing/splut.cpp.s

src/abycore/CMakeFiles/aby.dir/sharing/yaoclientsharing.cpp.o: src/abycore/CMakeFiles/aby.dir/flags.make
src/abycore/CMakeFiles/aby.dir/sharing/yaoclientsharing.cpp.o: ../src/abycore/sharing/yaoclientsharing.cpp
src/abycore/CMakeFiles/aby.dir/sharing/yaoclientsharing.cpp.o: src/abycore/CMakeFiles/aby.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mineorbit/CRYPTO-LUC/ABY/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object src/abycore/CMakeFiles/aby.dir/sharing/yaoclientsharing.cpp.o"
	cd /home/mineorbit/CRYPTO-LUC/ABY/build/src/abycore && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/abycore/CMakeFiles/aby.dir/sharing/yaoclientsharing.cpp.o -MF CMakeFiles/aby.dir/sharing/yaoclientsharing.cpp.o.d -o CMakeFiles/aby.dir/sharing/yaoclientsharing.cpp.o -c /home/mineorbit/CRYPTO-LUC/ABY/src/abycore/sharing/yaoclientsharing.cpp

src/abycore/CMakeFiles/aby.dir/sharing/yaoclientsharing.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/aby.dir/sharing/yaoclientsharing.cpp.i"
	cd /home/mineorbit/CRYPTO-LUC/ABY/build/src/abycore && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mineorbit/CRYPTO-LUC/ABY/src/abycore/sharing/yaoclientsharing.cpp > CMakeFiles/aby.dir/sharing/yaoclientsharing.cpp.i

src/abycore/CMakeFiles/aby.dir/sharing/yaoclientsharing.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/aby.dir/sharing/yaoclientsharing.cpp.s"
	cd /home/mineorbit/CRYPTO-LUC/ABY/build/src/abycore && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mineorbit/CRYPTO-LUC/ABY/src/abycore/sharing/yaoclientsharing.cpp -o CMakeFiles/aby.dir/sharing/yaoclientsharing.cpp.s

src/abycore/CMakeFiles/aby.dir/sharing/yaoserversharing.cpp.o: src/abycore/CMakeFiles/aby.dir/flags.make
src/abycore/CMakeFiles/aby.dir/sharing/yaoserversharing.cpp.o: ../src/abycore/sharing/yaoserversharing.cpp
src/abycore/CMakeFiles/aby.dir/sharing/yaoserversharing.cpp.o: src/abycore/CMakeFiles/aby.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mineorbit/CRYPTO-LUC/ABY/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building CXX object src/abycore/CMakeFiles/aby.dir/sharing/yaoserversharing.cpp.o"
	cd /home/mineorbit/CRYPTO-LUC/ABY/build/src/abycore && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/abycore/CMakeFiles/aby.dir/sharing/yaoserversharing.cpp.o -MF CMakeFiles/aby.dir/sharing/yaoserversharing.cpp.o.d -o CMakeFiles/aby.dir/sharing/yaoserversharing.cpp.o -c /home/mineorbit/CRYPTO-LUC/ABY/src/abycore/sharing/yaoserversharing.cpp

src/abycore/CMakeFiles/aby.dir/sharing/yaoserversharing.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/aby.dir/sharing/yaoserversharing.cpp.i"
	cd /home/mineorbit/CRYPTO-LUC/ABY/build/src/abycore && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mineorbit/CRYPTO-LUC/ABY/src/abycore/sharing/yaoserversharing.cpp > CMakeFiles/aby.dir/sharing/yaoserversharing.cpp.i

src/abycore/CMakeFiles/aby.dir/sharing/yaoserversharing.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/aby.dir/sharing/yaoserversharing.cpp.s"
	cd /home/mineorbit/CRYPTO-LUC/ABY/build/src/abycore && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mineorbit/CRYPTO-LUC/ABY/src/abycore/sharing/yaoserversharing.cpp -o CMakeFiles/aby.dir/sharing/yaoserversharing.cpp.s

src/abycore/CMakeFiles/aby.dir/sharing/yaosharing.cpp.o: src/abycore/CMakeFiles/aby.dir/flags.make
src/abycore/CMakeFiles/aby.dir/sharing/yaosharing.cpp.o: ../src/abycore/sharing/yaosharing.cpp
src/abycore/CMakeFiles/aby.dir/sharing/yaosharing.cpp.o: src/abycore/CMakeFiles/aby.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mineorbit/CRYPTO-LUC/ABY/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Building CXX object src/abycore/CMakeFiles/aby.dir/sharing/yaosharing.cpp.o"
	cd /home/mineorbit/CRYPTO-LUC/ABY/build/src/abycore && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/abycore/CMakeFiles/aby.dir/sharing/yaosharing.cpp.o -MF CMakeFiles/aby.dir/sharing/yaosharing.cpp.o.d -o CMakeFiles/aby.dir/sharing/yaosharing.cpp.o -c /home/mineorbit/CRYPTO-LUC/ABY/src/abycore/sharing/yaosharing.cpp

src/abycore/CMakeFiles/aby.dir/sharing/yaosharing.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/aby.dir/sharing/yaosharing.cpp.i"
	cd /home/mineorbit/CRYPTO-LUC/ABY/build/src/abycore && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mineorbit/CRYPTO-LUC/ABY/src/abycore/sharing/yaosharing.cpp > CMakeFiles/aby.dir/sharing/yaosharing.cpp.i

src/abycore/CMakeFiles/aby.dir/sharing/yaosharing.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/aby.dir/sharing/yaosharing.cpp.s"
	cd /home/mineorbit/CRYPTO-LUC/ABY/build/src/abycore && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mineorbit/CRYPTO-LUC/ABY/src/abycore/sharing/yaosharing.cpp -o CMakeFiles/aby.dir/sharing/yaosharing.cpp.s

# Object files for target aby
aby_OBJECTS = \
"CMakeFiles/aby.dir/aby/abyparty.cpp.o" \
"CMakeFiles/aby.dir/aby/abysetup.cpp.o" \
"CMakeFiles/aby.dir/circuit/abycircuit.cpp.o" \
"CMakeFiles/aby.dir/circuit/arithmeticcircuits.cpp.o" \
"CMakeFiles/aby.dir/circuit/booleancircuits.cpp.o" \
"CMakeFiles/aby.dir/circuit/circuit.cpp.o" \
"CMakeFiles/aby.dir/circuit/share.cpp.o" \
"CMakeFiles/aby.dir/DGK/dgkparty.cpp.o" \
"CMakeFiles/aby.dir/DJN/djnparty.cpp.o" \
"CMakeFiles/aby.dir/sharing/arithsharing.cpp.o" \
"CMakeFiles/aby.dir/sharing/boolsharing.cpp.o" \
"CMakeFiles/aby.dir/sharing/sharing.cpp.o" \
"CMakeFiles/aby.dir/sharing/splut.cpp.o" \
"CMakeFiles/aby.dir/sharing/yaoclientsharing.cpp.o" \
"CMakeFiles/aby.dir/sharing/yaoserversharing.cpp.o" \
"CMakeFiles/aby.dir/sharing/yaosharing.cpp.o"

# External object files for target aby
aby_EXTERNAL_OBJECTS =

lib/libaby.a: src/abycore/CMakeFiles/aby.dir/aby/abyparty.cpp.o
lib/libaby.a: src/abycore/CMakeFiles/aby.dir/aby/abysetup.cpp.o
lib/libaby.a: src/abycore/CMakeFiles/aby.dir/circuit/abycircuit.cpp.o
lib/libaby.a: src/abycore/CMakeFiles/aby.dir/circuit/arithmeticcircuits.cpp.o
lib/libaby.a: src/abycore/CMakeFiles/aby.dir/circuit/booleancircuits.cpp.o
lib/libaby.a: src/abycore/CMakeFiles/aby.dir/circuit/circuit.cpp.o
lib/libaby.a: src/abycore/CMakeFiles/aby.dir/circuit/share.cpp.o
lib/libaby.a: src/abycore/CMakeFiles/aby.dir/DGK/dgkparty.cpp.o
lib/libaby.a: src/abycore/CMakeFiles/aby.dir/DJN/djnparty.cpp.o
lib/libaby.a: src/abycore/CMakeFiles/aby.dir/sharing/arithsharing.cpp.o
lib/libaby.a: src/abycore/CMakeFiles/aby.dir/sharing/boolsharing.cpp.o
lib/libaby.a: src/abycore/CMakeFiles/aby.dir/sharing/sharing.cpp.o
lib/libaby.a: src/abycore/CMakeFiles/aby.dir/sharing/splut.cpp.o
lib/libaby.a: src/abycore/CMakeFiles/aby.dir/sharing/yaoclientsharing.cpp.o
lib/libaby.a: src/abycore/CMakeFiles/aby.dir/sharing/yaoserversharing.cpp.o
lib/libaby.a: src/abycore/CMakeFiles/aby.dir/sharing/yaosharing.cpp.o
lib/libaby.a: src/abycore/CMakeFiles/aby.dir/build.make
lib/libaby.a: src/abycore/CMakeFiles/aby.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mineorbit/CRYPTO-LUC/ABY/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_17) "Linking CXX static library ../../lib/libaby.a"
	cd /home/mineorbit/CRYPTO-LUC/ABY/build/src/abycore && $(CMAKE_COMMAND) -P CMakeFiles/aby.dir/cmake_clean_target.cmake
	cd /home/mineorbit/CRYPTO-LUC/ABY/build/src/abycore && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/aby.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/abycore/CMakeFiles/aby.dir/build: lib/libaby.a
.PHONY : src/abycore/CMakeFiles/aby.dir/build

src/abycore/CMakeFiles/aby.dir/clean:
	cd /home/mineorbit/CRYPTO-LUC/ABY/build/src/abycore && $(CMAKE_COMMAND) -P CMakeFiles/aby.dir/cmake_clean.cmake
.PHONY : src/abycore/CMakeFiles/aby.dir/clean

src/abycore/CMakeFiles/aby.dir/depend:
	cd /home/mineorbit/CRYPTO-LUC/ABY/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mineorbit/CRYPTO-LUC/ABY /home/mineorbit/CRYPTO-LUC/ABY/src/abycore /home/mineorbit/CRYPTO-LUC/ABY/build /home/mineorbit/CRYPTO-LUC/ABY/build/src/abycore /home/mineorbit/CRYPTO-LUC/ABY/build/src/abycore/CMakeFiles/aby.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/abycore/CMakeFiles/aby.dir/depend

