TOPTARGETS := all clean
BASEDIRS := ./test_engine ./test_runner
SUBDIRS := \
	./LinkedList \
	./PigLatin \
	./Queue \
	./Stack \

ALLDIRS := $(SUBDIRS) $(BASEDIRS)

$(TOPTARGETS): $(ALLDIRS)
$(ALLDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

.PHONY: $(TOPTARGETS) $(ALLDIRS)
