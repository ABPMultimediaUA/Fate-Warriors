INCLUDE_DIR=./inc
LIB_DIR=./lib
LD_LIBRARY_PATH=$(LIB_DIR):\$LD_LIBRARY_PATH

all:
	g++ -I$(INCLUDE_DIR) -g -Wall -c -o simple_event.o simple_event.cpp 
	g++ -I$(LIB_DIR) -L$(LIB_DIR) -o "simple_event" simple_event.o -lfmod -lfmodstudio 
	
	# Mac OSX only
	#install_name_tool -change "@rpath/libfmodstudio.dylib" ./libfmodstudio.dylib simple_event

all_log:
	g++ -I$(INCLUDE_DIR) -g -Wall -c -o simple_event.o simple_event.cpp 
	g++ -L$(LIB_DIR) -o "simple_event" simple_event.o -lfmodL -lfmodstudioL 
	# Mac OSX only
	#install_name_tool -change "@rpath/libfmodstudioL.dylib" ./libfmodstudioL.dylib simple_event
	
