TOPTARGETS := all clean
BASEDIRS := ./test_engine ./test_runner
SUBDIRS := \
	./LinkedList \
	./PigLatin \
	./Queue \
	./Stack \
	./LinearStorageInterface \
	./Vector \
	./Array \
	./Shared_Ptr \

ALLDIRS := $(SUBDIRS) $(BASEDIRS)

$(TOPTARGETS): clearscreen $(ALLDIRS)

$(ALLDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

clearscreen:
	clear

.PHONY: $(TOPTARGETS) $(ALLDIRS)
