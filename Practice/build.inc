ifeq ($(PROJECT_DIR),)
    $(error PROJECT_DIR is not set)
endif

CC = g++
DEFAULT_FLAGS = -Wall -std=c++14 -Werror
LIB_FLAGS = -c -fPIC
LINKER_FLAGS = -pthread
DEBUG_FLAGS = -ggdb

TARGET_PATH ?= $(PROJECT_DIR)/outputs
TARGET_OBJECTS_PATH := $(TARGET_PATH)/obj
TARGET_LIBRARY_PATH := $(TARGET_PATH)/lib
LIBRARY_PATH := $(LIBRARY_PATH) $(TARGET_LIBRARY_PATH)

SOURCES ?= $(wildcard *.cpp)
OBJECTS := $(patsubst %.cpp, $(TARGET_OBJECTS_PATH)/%.o, $(SOURCES))

INCLUDE_PATH := $(sort $(INCLUDE_PATH))
TARGET_LIBS := $(sort $(TARGET_LIBS))
LIBRARY_PATH := $(sort $(LIBRARY_PATH))

RAW_INCLUDE_PATH := $(sort $(RAW_INCLUDE_PATH))

RAW_INCLUDE_PATH := $(RAW_INCLUDE_PATH) $(addprefix -I, $(INCLUDE_PATH))
RAW_TARGET_LIBS = $(addprefix -l, $(TARGET_LIBS))
RAW_LIBRARY_PATH = $(addprefix -L , $(LIBRARY_PATH))

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
LIBRARY_COMPILER := $(RAW_LIBRARY_PATH) -Wl,--whole-archive $(RAW_TARGET_LIBS) -Wl,--no-whole-archive $(LINKER_FLAGS)
else
LIBRARY_COMPILER := $(RAW_LIBRARY_PATH) -all_load $(RAW_TARGET_LIBS) $(LINKER_FLAGS)
endif

BASE_CMD = $(CC) $(RAW_INCLUDE_PATH) $(DEFAULT_FLAGS)

ifneq ($(DEBUG),)
BASE_CMD := $(BASE_CMD) $(DEBUG_FLAGS)
endif

ifeq ($(TARGET_TYPE),library)
FULL_TARGET_NAME = $(TARGET_LIBRARY_PATH)/lib$(TARGET_NAME).a
LINKER = ar rsv $(FULL_TARGET_NAME) $(OBJECTS)
else
	ifeq ($(TARGET_TYPE),program)
FULL_TARGET_NAME = $(TARGET_PATH)/$(TARGET_NAME).out
LINKER = $(BASE_CMD) -o $(FULL_TARGET_NAME) $(OBJECTS) $(LIBRARY_COMPILER)
	else
		$(error TARGET_TYPE $(TARGET_TYPE) is not valid. Choose program or library.)
	endif
endif

all: dirmake $(FULL_TARGET_NAME)

$(FULL_TARGET_NAME): $(OBJECTS)
	$(LINKER)

#Compiling every *.cpp to* .o
$(TARGET_OBJECTS_PATH)/%.o: %.cpp
	$(BASE_CMD) $(LIB_FLAGS) -o $@  $^

dirmake:
	@mkdir -p $(TARGET_PATH)
	@mkdir -p $(TARGET_OBJECTS_PATH)
	@mkdir -p $(TARGET_LIBRARY_PATH)

clean:
	rm -f $(OBJECTS)
	rm -f $(FULL_TARGET_NAME)

rebuild: clean all

run: $(FULL_TARGET_NAME)
ifeq ($(TARGET_TYPE),program)
	$(FULL_TARGET_NAME) $(ARGS)
endif
