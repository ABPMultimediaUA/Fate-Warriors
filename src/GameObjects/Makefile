ODIR	:= obj
SDIR	:= src
SUBDIRS:=$(filter-out ., $(shell find $(SDIR) -type d -print))
OBJSUBDIRS:=$(foreach DIR, $(SUBDIRS), $(patsubst $(SDIR)%, $(ODIR)%, $(DIR)))
SRCFILES:=$(foreach DIR, $(SUBDIRS), $(wildcard $(DIR)/*.cpp))
OBJFILES:=$(patsubst $(SDIR)%, $(ODIR)%, $(SRCFILES:%.cpp=%.o))
SOURCES := $(wildcard $(SDIR)/*.cpp)
DELOBJ:= $(wildcard $(ODIR)/*.o)
OBJECTS := $(patsubst $(SDIR)/%.cpp,$(ODIR)/%.o,$(SOURCES))
LIBS := -lsfml-window -lsfml-graphics -lsfml-system -lRakNetDLL -lIrrlicht
INCLUDE := -I.
CC      := g++
OBJS	:= $(patsubst %,$(ODIR)/%,$(OBJECTS))
RM	:=rm -f

define COMPILAR
$(1): $(2)
	$(CC) -o $(1) -c $(2) $(INCLUDE)
endef


ejecutable: $(OBJFILES)
	$(CC) -o $@ $^ $(INCLUDE) $(LIBS)

$(foreach OF, $(OBJFILES), $(eval $(call COMPILAR, $(OF), $(patsubst $(ODIR)%,$(SDIR)%,$(OF:%.o=%.cpp)))))

#$(ODIR)/%.o: $(SDIR)/%.cpp
#$(OBJFILES): $(SRCFILES)
#	$(CC) -o $@ -c $^ $(INCLUDE)

clean:
	$(RM) -r $(DELOBJ)
	
info: 
#	$(info $(SUBDIRS))
#	$(info $(SOURCES))
#	$(info $(OBJECTS))
#	$(info $(SRCFILES))
#	$(info $(OBJSUBDIRS))
	$(info $(OBJFILES))



#INSTALAR MINGW G++ PARA WINDORS -> PARA PODER COMPILAR PARA WINDOWS 
