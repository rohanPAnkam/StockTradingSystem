# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.30.2/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.30.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/rohanankam/Desktop/c++/Projects/StockTrading

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/rohanankam/Desktop/c++/Projects/StockTrading/build

# Include any dependencies generated for this target.
include CMakeFiles/my_app.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/my_app.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/my_app.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/my_app.dir/flags.make

CMakeFiles/my_app.dir/main.cpp.o: CMakeFiles/my_app.dir/flags.make
CMakeFiles/my_app.dir/main.cpp.o: /Users/rohanankam/Desktop/c++/Projects/StockTrading/main.cpp
CMakeFiles/my_app.dir/main.cpp.o: CMakeFiles/my_app.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/rohanankam/Desktop/c++/Projects/StockTrading/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/my_app.dir/main.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/my_app.dir/main.cpp.o -MF CMakeFiles/my_app.dir/main.cpp.o.d -o CMakeFiles/my_app.dir/main.cpp.o -c /Users/rohanankam/Desktop/c++/Projects/StockTrading/main.cpp

CMakeFiles/my_app.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/my_app.dir/main.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/rohanankam/Desktop/c++/Projects/StockTrading/main.cpp > CMakeFiles/my_app.dir/main.cpp.i

CMakeFiles/my_app.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/my_app.dir/main.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/rohanankam/Desktop/c++/Projects/StockTrading/main.cpp -o CMakeFiles/my_app.dir/main.cpp.s

CMakeFiles/my_app.dir/src/order.cpp.o: CMakeFiles/my_app.dir/flags.make
CMakeFiles/my_app.dir/src/order.cpp.o: /Users/rohanankam/Desktop/c++/Projects/StockTrading/src/order.cpp
CMakeFiles/my_app.dir/src/order.cpp.o: CMakeFiles/my_app.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/rohanankam/Desktop/c++/Projects/StockTrading/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/my_app.dir/src/order.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/my_app.dir/src/order.cpp.o -MF CMakeFiles/my_app.dir/src/order.cpp.o.d -o CMakeFiles/my_app.dir/src/order.cpp.o -c /Users/rohanankam/Desktop/c++/Projects/StockTrading/src/order.cpp

CMakeFiles/my_app.dir/src/order.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/my_app.dir/src/order.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/rohanankam/Desktop/c++/Projects/StockTrading/src/order.cpp > CMakeFiles/my_app.dir/src/order.cpp.i

CMakeFiles/my_app.dir/src/order.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/my_app.dir/src/order.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/rohanankam/Desktop/c++/Projects/StockTrading/src/order.cpp -o CMakeFiles/my_app.dir/src/order.cpp.s

CMakeFiles/my_app.dir/src/orderBook.cpp.o: CMakeFiles/my_app.dir/flags.make
CMakeFiles/my_app.dir/src/orderBook.cpp.o: /Users/rohanankam/Desktop/c++/Projects/StockTrading/src/orderBook.cpp
CMakeFiles/my_app.dir/src/orderBook.cpp.o: CMakeFiles/my_app.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/rohanankam/Desktop/c++/Projects/StockTrading/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/my_app.dir/src/orderBook.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/my_app.dir/src/orderBook.cpp.o -MF CMakeFiles/my_app.dir/src/orderBook.cpp.o.d -o CMakeFiles/my_app.dir/src/orderBook.cpp.o -c /Users/rohanankam/Desktop/c++/Projects/StockTrading/src/orderBook.cpp

CMakeFiles/my_app.dir/src/orderBook.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/my_app.dir/src/orderBook.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/rohanankam/Desktop/c++/Projects/StockTrading/src/orderBook.cpp > CMakeFiles/my_app.dir/src/orderBook.cpp.i

CMakeFiles/my_app.dir/src/orderBook.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/my_app.dir/src/orderBook.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/rohanankam/Desktop/c++/Projects/StockTrading/src/orderBook.cpp -o CMakeFiles/my_app.dir/src/orderBook.cpp.s

CMakeFiles/my_app.dir/src/stock.cpp.o: CMakeFiles/my_app.dir/flags.make
CMakeFiles/my_app.dir/src/stock.cpp.o: /Users/rohanankam/Desktop/c++/Projects/StockTrading/src/stock.cpp
CMakeFiles/my_app.dir/src/stock.cpp.o: CMakeFiles/my_app.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/rohanankam/Desktop/c++/Projects/StockTrading/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/my_app.dir/src/stock.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/my_app.dir/src/stock.cpp.o -MF CMakeFiles/my_app.dir/src/stock.cpp.o.d -o CMakeFiles/my_app.dir/src/stock.cpp.o -c /Users/rohanankam/Desktop/c++/Projects/StockTrading/src/stock.cpp

CMakeFiles/my_app.dir/src/stock.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/my_app.dir/src/stock.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/rohanankam/Desktop/c++/Projects/StockTrading/src/stock.cpp > CMakeFiles/my_app.dir/src/stock.cpp.i

CMakeFiles/my_app.dir/src/stock.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/my_app.dir/src/stock.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/rohanankam/Desktop/c++/Projects/StockTrading/src/stock.cpp -o CMakeFiles/my_app.dir/src/stock.cpp.s

CMakeFiles/my_app.dir/src/trader.cpp.o: CMakeFiles/my_app.dir/flags.make
CMakeFiles/my_app.dir/src/trader.cpp.o: /Users/rohanankam/Desktop/c++/Projects/StockTrading/src/trader.cpp
CMakeFiles/my_app.dir/src/trader.cpp.o: CMakeFiles/my_app.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/rohanankam/Desktop/c++/Projects/StockTrading/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/my_app.dir/src/trader.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/my_app.dir/src/trader.cpp.o -MF CMakeFiles/my_app.dir/src/trader.cpp.o.d -o CMakeFiles/my_app.dir/src/trader.cpp.o -c /Users/rohanankam/Desktop/c++/Projects/StockTrading/src/trader.cpp

CMakeFiles/my_app.dir/src/trader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/my_app.dir/src/trader.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/rohanankam/Desktop/c++/Projects/StockTrading/src/trader.cpp > CMakeFiles/my_app.dir/src/trader.cpp.i

CMakeFiles/my_app.dir/src/trader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/my_app.dir/src/trader.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/rohanankam/Desktop/c++/Projects/StockTrading/src/trader.cpp -o CMakeFiles/my_app.dir/src/trader.cpp.s

# Object files for target my_app
my_app_OBJECTS = \
"CMakeFiles/my_app.dir/main.cpp.o" \
"CMakeFiles/my_app.dir/src/order.cpp.o" \
"CMakeFiles/my_app.dir/src/orderBook.cpp.o" \
"CMakeFiles/my_app.dir/src/stock.cpp.o" \
"CMakeFiles/my_app.dir/src/trader.cpp.o"

# External object files for target my_app
my_app_EXTERNAL_OBJECTS =

my_app: CMakeFiles/my_app.dir/main.cpp.o
my_app: CMakeFiles/my_app.dir/src/order.cpp.o
my_app: CMakeFiles/my_app.dir/src/orderBook.cpp.o
my_app: CMakeFiles/my_app.dir/src/stock.cpp.o
my_app: CMakeFiles/my_app.dir/src/trader.cpp.o
my_app: CMakeFiles/my_app.dir/build.make
my_app: CMakeFiles/my_app.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/rohanankam/Desktop/c++/Projects/StockTrading/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable my_app"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/my_app.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/my_app.dir/build: my_app
.PHONY : CMakeFiles/my_app.dir/build

CMakeFiles/my_app.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/my_app.dir/cmake_clean.cmake
.PHONY : CMakeFiles/my_app.dir/clean

CMakeFiles/my_app.dir/depend:
	cd /Users/rohanankam/Desktop/c++/Projects/StockTrading/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/rohanankam/Desktop/c++/Projects/StockTrading /Users/rohanankam/Desktop/c++/Projects/StockTrading /Users/rohanankam/Desktop/c++/Projects/StockTrading/build /Users/rohanankam/Desktop/c++/Projects/StockTrading/build /Users/rohanankam/Desktop/c++/Projects/StockTrading/build/CMakeFiles/my_app.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/my_app.dir/depend

