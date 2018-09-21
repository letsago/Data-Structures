include ../makefile.inc

C_FLAGS = $(DEFAULT_FLAGS) -c
INCLUDE_PATH = $(INC) -I../LinearStorageInterface
OBJ_DIR = $(TARGET_PATH)/obj

all: $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(wildcard *.cpp))

#Compiling every *.cpp to* .o
$(OBJ_DIR)/%.o: %.cpp dirmake
	$(CC) $(INCLUDE_PATH) $(C_FLAGS) -o $@  $<

dirmake:
	@mkdir -p $(OBJ_DIR)

clean:
	rm -f -r $(OBJ_DIR)

rebuild: clean all
