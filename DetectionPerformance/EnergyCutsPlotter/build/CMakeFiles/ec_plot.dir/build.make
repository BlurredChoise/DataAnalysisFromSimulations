# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/mateusz/Repositories/DataAnalysisFromSimulations/DetectionPerformance/EnergyCutsPlotter

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mateusz/Repositories/DataAnalysisFromSimulations/DetectionPerformance/EnergyCutsPlotter/build

# Include any dependencies generated for this target.
include CMakeFiles/ec_plot.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ec_plot.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ec_plot.dir/flags.make

CMakeFiles/ec_plot.dir/Run.cpp.o: CMakeFiles/ec_plot.dir/flags.make
CMakeFiles/ec_plot.dir/Run.cpp.o: ../Run.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mateusz/Repositories/DataAnalysisFromSimulations/DetectionPerformance/EnergyCutsPlotter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ec_plot.dir/Run.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ec_plot.dir/Run.cpp.o -c /home/mateusz/Repositories/DataAnalysisFromSimulations/DetectionPerformance/EnergyCutsPlotter/Run.cpp

CMakeFiles/ec_plot.dir/Run.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ec_plot.dir/Run.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mateusz/Repositories/DataAnalysisFromSimulations/DetectionPerformance/EnergyCutsPlotter/Run.cpp > CMakeFiles/ec_plot.dir/Run.cpp.i

CMakeFiles/ec_plot.dir/Run.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ec_plot.dir/Run.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mateusz/Repositories/DataAnalysisFromSimulations/DetectionPerformance/EnergyCutsPlotter/Run.cpp -o CMakeFiles/ec_plot.dir/Run.cpp.s

CMakeFiles/ec_plot.dir/Run.cpp.o.requires:

.PHONY : CMakeFiles/ec_plot.dir/Run.cpp.o.requires

CMakeFiles/ec_plot.dir/Run.cpp.o.provides: CMakeFiles/ec_plot.dir/Run.cpp.o.requires
	$(MAKE) -f CMakeFiles/ec_plot.dir/build.make CMakeFiles/ec_plot.dir/Run.cpp.o.provides.build
.PHONY : CMakeFiles/ec_plot.dir/Run.cpp.o.provides

CMakeFiles/ec_plot.dir/Run.cpp.o.provides.build: CMakeFiles/ec_plot.dir/Run.cpp.o


CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/HistogramsCreator.cpp.o: CMakeFiles/ec_plot.dir/flags.make
CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/HistogramsCreator.cpp.o: /home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/HistogramsCreator.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mateusz/Repositories/DataAnalysisFromSimulations/DetectionPerformance/EnergyCutsPlotter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/HistogramsCreator.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/HistogramsCreator.cpp.o -c /home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/HistogramsCreator.cpp

CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/HistogramsCreator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/HistogramsCreator.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/HistogramsCreator.cpp > CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/HistogramsCreator.cpp.i

CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/HistogramsCreator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/HistogramsCreator.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/HistogramsCreator.cpp -o CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/HistogramsCreator.cpp.s

CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/HistogramsCreator.cpp.o.requires:

.PHONY : CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/HistogramsCreator.cpp.o.requires

CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/HistogramsCreator.cpp.o.provides: CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/HistogramsCreator.cpp.o.requires
	$(MAKE) -f CMakeFiles/ec_plot.dir/build.make CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/HistogramsCreator.cpp.o.provides.build
.PHONY : CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/HistogramsCreator.cpp.o.provides

CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/HistogramsCreator.cpp.o.provides.build: CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/HistogramsCreator.cpp.o


CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/Message.cpp.o: CMakeFiles/ec_plot.dir/flags.make
CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/Message.cpp.o: /home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/Message.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mateusz/Repositories/DataAnalysisFromSimulations/DetectionPerformance/EnergyCutsPlotter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/Message.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/Message.cpp.o -c /home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/Message.cpp

CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/Message.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/Message.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/Message.cpp > CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/Message.cpp.i

CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/Message.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/Message.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/Message.cpp -o CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/Message.cpp.s

CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/Message.cpp.o.requires:

.PHONY : CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/Message.cpp.o.requires

CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/Message.cpp.o.provides: CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/Message.cpp.o.requires
	$(MAKE) -f CMakeFiles/ec_plot.dir/build.make CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/Message.cpp.o.provides.build
.PHONY : CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/Message.cpp.o.provides

CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/Message.cpp.o.provides.build: CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/Message.cpp.o


CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/RandomGenerator.cpp.o: CMakeFiles/ec_plot.dir/flags.make
CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/RandomGenerator.cpp.o: /home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/RandomGenerator.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mateusz/Repositories/DataAnalysisFromSimulations/DetectionPerformance/EnergyCutsPlotter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/RandomGenerator.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/RandomGenerator.cpp.o -c /home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/RandomGenerator.cpp

CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/RandomGenerator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/RandomGenerator.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/RandomGenerator.cpp > CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/RandomGenerator.cpp.i

CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/RandomGenerator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/RandomGenerator.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/RandomGenerator.cpp -o CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/RandomGenerator.cpp.s

CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/RandomGenerator.cpp.o.requires:

.PHONY : CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/RandomGenerator.cpp.o.requires

CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/RandomGenerator.cpp.o.provides: CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/RandomGenerator.cpp.o.requires
	$(MAKE) -f CMakeFiles/ec_plot.dir/build.make CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/RandomGenerator.cpp.o.provides.build
.PHONY : CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/RandomGenerator.cpp.o.provides

CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/RandomGenerator.cpp.o.provides.build: CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/RandomGenerator.cpp.o


CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/ReadAndSave.cpp.o: CMakeFiles/ec_plot.dir/flags.make
CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/ReadAndSave.cpp.o: /home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/ReadAndSave.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mateusz/Repositories/DataAnalysisFromSimulations/DetectionPerformance/EnergyCutsPlotter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/ReadAndSave.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/ReadAndSave.cpp.o -c /home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/ReadAndSave.cpp

CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/ReadAndSave.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/ReadAndSave.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/ReadAndSave.cpp > CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/ReadAndSave.cpp.i

CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/ReadAndSave.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/ReadAndSave.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/ReadAndSave.cpp -o CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/ReadAndSave.cpp.s

CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/ReadAndSave.cpp.o.requires:

.PHONY : CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/ReadAndSave.cpp.o.requires

CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/ReadAndSave.cpp.o.provides: CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/ReadAndSave.cpp.o.requires
	$(MAKE) -f CMakeFiles/ec_plot.dir/build.make CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/ReadAndSave.cpp.o.provides.build
.PHONY : CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/ReadAndSave.cpp.o.provides

CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/ReadAndSave.cpp.o.provides.build: CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/ReadAndSave.cpp.o


# Object files for target ec_plot
ec_plot_OBJECTS = \
"CMakeFiles/ec_plot.dir/Run.cpp.o" \
"CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/HistogramsCreator.cpp.o" \
"CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/Message.cpp.o" \
"CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/RandomGenerator.cpp.o" \
"CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/ReadAndSave.cpp.o"

# External object files for target ec_plot
ec_plot_EXTERNAL_OBJECTS =

ec_plot: CMakeFiles/ec_plot.dir/Run.cpp.o
ec_plot: CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/HistogramsCreator.cpp.o
ec_plot: CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/Message.cpp.o
ec_plot: CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/RandomGenerator.cpp.o
ec_plot: CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/ReadAndSave.cpp.o
ec_plot: CMakeFiles/ec_plot.dir/build.make
ec_plot: /home/mateusz/Libraries/Installed/root/lib/libCore.so
ec_plot: /home/mateusz/Libraries/Installed/root/lib/libRIO.so
ec_plot: /home/mateusz/Libraries/Installed/root/lib/libNet.so
ec_plot: /home/mateusz/Libraries/Installed/root/lib/libHist.so
ec_plot: /home/mateusz/Libraries/Installed/root/lib/libGraf.so
ec_plot: /home/mateusz/Libraries/Installed/root/lib/libGraf3d.so
ec_plot: /home/mateusz/Libraries/Installed/root/lib/libGpad.so
ec_plot: /home/mateusz/Libraries/Installed/root/lib/libTree.so
ec_plot: /home/mateusz/Libraries/Installed/root/lib/libRint.so
ec_plot: /home/mateusz/Libraries/Installed/root/lib/libPostscript.so
ec_plot: /home/mateusz/Libraries/Installed/root/lib/libMatrix.so
ec_plot: /home/mateusz/Libraries/Installed/root/lib/libPhysics.so
ec_plot: /home/mateusz/Libraries/Installed/root/lib/libMathCore.so
ec_plot: /home/mateusz/Libraries/Installed/root/lib/libThread.so
ec_plot: /home/mateusz/Libraries/Installed/root/lib/libMultiProc.so
ec_plot: CMakeFiles/ec_plot.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mateusz/Repositories/DataAnalysisFromSimulations/DetectionPerformance/EnergyCutsPlotter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable ec_plot"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ec_plot.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ec_plot.dir/build: ec_plot

.PHONY : CMakeFiles/ec_plot.dir/build

CMakeFiles/ec_plot.dir/requires: CMakeFiles/ec_plot.dir/Run.cpp.o.requires
CMakeFiles/ec_plot.dir/requires: CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/HistogramsCreator.cpp.o.requires
CMakeFiles/ec_plot.dir/requires: CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/Message.cpp.o.requires
CMakeFiles/ec_plot.dir/requires: CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/RandomGenerator.cpp.o.requires
CMakeFiles/ec_plot.dir/requires: CMakeFiles/ec_plot.dir/home/mateusz/Repositories/DataAnalysisFromSimulations/Tools/ToolsForROOT/ReadAndSave.cpp.o.requires

.PHONY : CMakeFiles/ec_plot.dir/requires

CMakeFiles/ec_plot.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ec_plot.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ec_plot.dir/clean

CMakeFiles/ec_plot.dir/depend:
	cd /home/mateusz/Repositories/DataAnalysisFromSimulations/DetectionPerformance/EnergyCutsPlotter/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mateusz/Repositories/DataAnalysisFromSimulations/DetectionPerformance/EnergyCutsPlotter /home/mateusz/Repositories/DataAnalysisFromSimulations/DetectionPerformance/EnergyCutsPlotter /home/mateusz/Repositories/DataAnalysisFromSimulations/DetectionPerformance/EnergyCutsPlotter/build /home/mateusz/Repositories/DataAnalysisFromSimulations/DetectionPerformance/EnergyCutsPlotter/build /home/mateusz/Repositories/DataAnalysisFromSimulations/DetectionPerformance/EnergyCutsPlotter/build/CMakeFiles/ec_plot.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ec_plot.dir/depend

