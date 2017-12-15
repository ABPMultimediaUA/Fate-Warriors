SOURCES := $(wildcard *.cpp)
OBJECTS := $(subst .cpp,.o,$(SOURCES))
LIBS := -lsfml-window -lsfml-graphics -lsfml-system -lRakNetDLL -lIrrlicht
INCLUDE := -I.
CC      := g++

ejecutable: $(OBJECTS)
	$(CC) -o $@ $^ $(INCLUDE) $(LIBS)

%.o: %.cpp
	$(CC) -o $@ -c $^ $(INCLUDE)

info: 
	$(info $(SOURCES))
	$(info $(OBJECTS))



#INSTALAR MINGW G++ PARA WINDORS -> PARA PODER COMPILAR PARA WINDOWS 