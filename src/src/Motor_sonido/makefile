INCLUDE_DIR=./inc
LIB_DIR=./lib
LD_LIBRARY_PATH=$(LIB_DIR):\$LD_LIBRARY_PATH

all:
	g++ -I$(INCLUDE_DIR) -g -Wall -c -o Interfaz_sonido.o Interfaz_sonido.cpp 
	g++ -I$(LIB_DIR) -L$(LIB_DIR) -o "Interfaz_sonido" Interfaz_sonido.o -lfmod -lfmodstudio 
	
	# Mac OSX only
	#install_name_tool -change "@rpath/libfmodstudio.dylib" ./libfmodstudio.dylib Interfaz_sonido

all_log:
	g++ -I$(INCLUDE_DIR) -g -Wall -c -o Interfaz_sonido.o Interfaz_sonido.cpp 
	g++ -L$(LIB_DIR) -o "Interfaz_sonido" Interfaz_sonido.o -lfmodL -lfmodstudioL 
	# Mac OSX only
	#install_name_tool -change "@rpath/libfmodstudioL.dylib" ./libfmodstudioL.dylib Interfaz_sonido
	
