ODIR	:= obj
SDIR	:= src
SUBDIRS:=$(filter-out ., $(shell find $(SDIR) -type d -print))
OBJSUBDIRS:=$(foreach DIR, $(SUBDIRS), $(patsubst $(SDIR)%, $(ODIR)%, $(DIR)))
SRCFILES:=$(foreach DIR, $(SUBDIRS), $(wildcard $(DIR)/*.cpp))
OBJFILES:=$(patsubst $(SDIR)%, $(ODIR)%, $(SRCFILES:%.cpp=%.o))
SOURCES := $(wildcard $(SDIR)/*.cpp)
DELOBJ:= $(wildcard $(ODIR)/*)
OBJECTS := $(patsubst $(SDIR)/%.cpp,$(ODIR)/%.o,$(SOURCES))
LIBS := -lsfml-window -lsfml-graphics -lsfml-system -lRakNetDLL -lIrrlicht -lBulletDynamics -lBulletCollision -lLinearMath
INCLUDE := -I. -I/usr/include/bullet
CC      := g++ -g
OBJS	:= $(patsubst %,$(ODIR)/%,$(OBJECTS))
RM		:= rm -f
MKDIR 	:= mkdir


PRUEBA  := $(filter-out $(ODIR), $(OBJSUBDIRS))
PRUEBA2 := $(MKDIR) $(PRUEBA)
#PRUEBA3 := $(eval $(call MKOBJDIR, $(PRUEBA)))

TARGET	:= ejecutable


define COMPILAR
$(1): $(2)
	$(CC) -o $(1) -c $(2) $(INCLUDE)

endef

define MKOBJDIR
$(1):
	@$(MKDIR) -p $(1)
endef

define BORRAR
$(1):
	$(RM) -r $(1)

endef

.PHONY: all

all: $(ODIR) $(TARGET)


$(TARGET): $(OBJFILES)
	$(CC) -o $@ $^ $(INCLUDE) $(LIBS)

## CREATING SUBDIRS OF THE OBJDIR
#dir:
#	 $(eval $(call COMPILAR, $(PRUEBA),  ))
dir: $(OBJSUBDIRS)

$(foreach OSD, $(filter-out $(ODIR), $(OBJSUBDIRS)), $(eval $(call MKOBJDIR, $(OSD))))


$(foreach OF, $(OBJFILES), $(eval $(call COMPILAR, $(OF), $(patsubst $(ODIR)%,$(SDIR)%,$(OF:%.o=%.cpp)))))


# CREATE OBJDIR & SUBDIRS IF THEY DO NOT EXIST
$(OBJDIR): $(filter-out $(ODIR), $(OBJSUBDIRS))
	$(call PRINT,"Tree structure for obj files created")
#$(ODIR)/%.o: $(SDIR)/%.cpp
#$(OBJFILES): $(SRCFILES)
#	$(CC) -o $@ -c $^ $(INCLUDE)

.PHONY: clean
clean:
	$(RM) -r $(DELOBJ) && $(RM) $(TARGET)
#	$(foreach VAR, $(OBJSUBDIRS), $(eval $(call BORRAR, $(VAR))))

.PHONY: info
info: 
#	$(info $(SUBDIRS))
#	$(info $(SOURCES))
#	$(info $(OBJECTS))
#	$(info $(SRCFILES))
#	$(info $(OBJSUBDIRS))
#	$(info $(OBJFILES))
	$(info $(PRUEBA))
	$(info $(PRUEBA2))
#	$(info $(PRUEBA3))



#INSTALAR MINGW G++ PARA WINDORS -> PARA PODER COMPILAR PARA WINDOWS 

