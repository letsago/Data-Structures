ifeq ($(shell uname -s),Linux)
OS = Linux
LIB_EXT = so
else
OS = Mac
LIB_EXT = dylib
endif

CC = g++
DEFAULT_FLAGS = -Wall -std=c++14 -Werror
LIB_FLAGS = -c -fPIC
LINKER_FLAGS := $(LINKER_FLAGS)
DEBUG_FLAGS = -ggdb

C_FLAGS := $(C_FLAGS) $(DEFAULT_FLAGS)

ifneq ($(DEBUG),)
C_FLAGS := $(C_FLAGS) $(DEBUG_FLAGS)
endif

TARGET_PATH ?= $(PROJECT_DIR)/outputs
TARGET_OBJECTS_PATH ?= $(TARGET_PATH)/obj
TARGET_LIBRARY_PATH ?= $(TARGET_PATH)/lib
LIBRARY_PATH := $(LIBRARY_PATH) $(TARGET_LIBRARY_PATH)

SOURCES ?= $(wildcard *.cpp)
CPP_SOURCE = $(filter %.cpp,$(SOURCES))
HEADER_SOURCE = $(filter %.h,$(SOURCES))
OBJECTS := $(patsubst %.cpp, $(TARGET_OBJECTS_PATH)/%.o, $(CPP_SOURCE))

INCLUDE_PATH := $(sort $(INCLUDE_PATH))
TARGET_LIBS := $(sort $(TARGET_LIBS))
LIBRARY_PATH := $(sort $(LIBRARY_PATH))
LINKER_FLAGS := $(sort $(LINKER_FLAGS))
C_FLAGS := $(sort $(C_FLAGS))
RAW_INCLUDE_PATH := $(sort $(RAW_INCLUDE_PATH))
RAW_LIBRARY_PATH := $(sort $(RAW_LIBRARY_PATH))
RAW_TARGET_LIBS := $(sort $(RAW_TARGET_LIBS))

ifeq ($(OS), Mac)
rpath_base = -Wl,-rpath
R_PATH := $(addprefix $(rpath_base) ,$(LIBRARY_PATH))
else
rpath_base = -Wl,-rpath=
R_PATH := $(addprefix $(rpath_base),$(LIBRARY_PATH))
endif 

TARGET_LIBS := $(filter-out $(TARGET_NAME), $(TARGET_LIBS))
TARGET_LIBS := $(addprefix -l, $(TARGET_LIBS))
RAW_INCLUDE_PATH := $(RAW_INCLUDE_PATH) $(addprefix -I, $(INCLUDE_PATH))
RAW_TARGET_LIBS := $(RAW_TARGET_LIBS) $(TARGET_LIBS)
RAW_LIBRARY_PATH := $(RAW_LIBRARY_PATH) $(addprefix -L , $(LIBRARY_PATH))
LINKER_FLAGS += $(R_PATH)

LIBRARY_COMPILER := $(RAW_LIBRARY_PATH) $(RAW_TARGET_LIBS) $(LINKER_FLAGS)

BASE_CMD = $(CC) $(RAW_INCLUDE_PATH) $(C_FLAGS)

ifeq ($(TARGET_TYPE),library)
FULL_TARGET_NAME = $(TARGET_LIBRARY_PATH)/lib$(TARGET_NAME).$(LIB_EXT)
LINKER = $(CC) -shared -o $(FULL_TARGET_NAME) $(OBJECTS) $(LIBRARY_COMPILER)
else
	ifeq ($(TARGET_TYPE),program)
FULL_TARGET_NAME = $(TARGET_PATH)/$(TARGET_NAME).out
LINKER = $(BASE_CMD) -o $(FULL_TARGET_NAME) $(OBJECTS) $(LIBRARY_COMPILER)
	else
		$(error TARGET_TYPE $(TARGET_TYPE) is not valid. Choose program or library.)
	endif
endif

all: dirmake $(DIRS) $(FULL_TARGET_NAME)

# pull in dependency info for *existing* .o files
-include $(OBJECTS:.o=.d)

$(DIRS):
	make -C $@ $(MAKECMDGOALS)

$(FULL_TARGET_NAME): $(OBJECTS)
	$(LINKER)

#Compiling every *.cpp to* .o
$(TARGET_OBJECTS_PATH)/%.o: %.cpp $(TARGET_OBJECTS_PATH)/%.d
	$(BASE_CMD) $(LIB_FLAGS) -o $@  $<

$(TARGET_OBJECTS_PATH)/%.d: %.cpp
	@set -e; rm -f $@; \
	$(BASE_CMD) -M $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

dirmake:
	@mkdir -p $(TARGET_PATH)
	@mkdir -p $(TARGET_OBJECTS_PATH)
	@mkdir -p $(TARGET_LIBRARY_PATH)

clean: $(DIRS)
ifeq ($(TARGET_TYPE),library)
	rm -f $(OBJECTS)
	rm -f $(patsubst %.o, %.d*, $(OBJECTS))
endif
	rm -f $(FULL_TARGET_NAME)
	rm -rf $(FULL_TARGET_NAME)*

fullclean:
	rm -rf $(TARGET_PATH)

rebuild: clean all

.PHONY: $(DIRS)

run: all
ifeq ($(TARGET_TYPE),program)
	-@$(FULL_TARGET_NAME) $(ARGS)
else
	@:
endif

valgrind: all
ifeq ($(TARGET_TYPE),program)
	-@valgrind $(FULL_TARGET_NAME) $(ARGS)
else
	@:
endif
