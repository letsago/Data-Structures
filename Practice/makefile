BASEDIRS := ./test_engine ./test_runner
SUBDIRS := \
	./Array \
	./BalancedTree \
	./LinearStorageInterface \
	./LinkedList \
	./PigLatin \
	./Queue \
	./Shared_Ptr \
	./Stack \
	./Tree \
	./Vector \

ifeq (run,$(firstword $(MAKECMDGOALS)))
  # use the rest as arguments for "run"
  RUN_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  # ...and turn them into do-nothing targets
  $(eval $(RUN_ARGS):;@:)
endif

all: $(SUBDIRS) $(BASEDIRS)

clean: $(SUBDIRS) $(BASEDIRS)

rebuild: $(SUBDIRS) $(BASEDIRS)

$(BASEDIRS): $(SUBDIRS)
	$(MAKE) -C $@ rebuild

$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

.PHONY: all clean rebuild $(SUBDIRS) $(BASEDIRS)

run:
	make -C ./test_runner $(MAKECMDGOALS)

