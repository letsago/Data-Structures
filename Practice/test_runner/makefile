include ../makefile.inc

OUTPUT_NAME = test_runner.out
C_FLAGS = $(DEFAULT_FLAGS)

INCLUDE_PATH = \
	$(INC) \
	-I../PigLatin \
	-I../LinkedList \
	-I../Queue \
	-I../Stack \
	-I../LinearStorageInterface \
	-I../Vector \
	-I../Array \
	-I../Tree \
	-I../Shared_Ptr \

OUTPUT_PATH = $(TARGET_PATH)
OBJ_PATH = $(TARGET_PATH)/obj

all: build
	$(OUTPUT_PATH)/$(OUTPUT_NAME)

build: dirmake
	$(CC) $(C_FLAGS) $(INCLUDE_PATH) *.cpp  $(OBJ_PATH)/*.o -o $(OUTPUT_PATH)/$(OUTPUT_NAME)

dirmake:
	@mkdir -p $(OUTPUT_PATH)

clean:
	rm -f -r $(OUTPUT_PATH)

rebuild: clean all