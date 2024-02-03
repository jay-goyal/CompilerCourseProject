BUILDDIR := build
DBGDIR := $(BUILDDIR)/dbg
TGTDIR := $(BUILDDIR)/target
SRCDIR := src
INCDIR := include

CC := gcc
CFLAGS := -c -Wall -O1
DBGFLAGS := -c -Wall -ggdb

SOURCES := $(shell find $(SRCDIR) -type f -iname '*.c')
HEADERS := $(shell find $(SRCDIR) -type f -iname '*.h')
TGTOBJ := $(subst src,$(TGTDIR),$(SOURCES:.c=.o))
DBGOBJ := $(subst src,$(DBGDIR),$(SOURCES:.c=.o))
TGTDIRS := $(subst src,$(TGTDIR),$(dir $(SOURCES)))
DBGDIRS := $(subst src,$(DBGDIR),$(dir $(SOURCES)))

run: target
	./$(TGTDIR)/compiler

target: $(TGTDIRS) $(SOURCES) $(HEADERS) $(TGTOBJ)
	$(CC) -o $(TGTDIR)/compiler $(TGTOBJ)

debug: $(DBGDIRS) $(SOURCES) $(DBGOBJ)
	$(CC) -o $(DBGDIR)/compiler $(DBGOBJ)

clean:
	rm -rf $(BUILDDIR)

$(DBGDIR)/%.o: $(SRCDIR)/%.c $(HEADERS)
	$(CC) -o $@ $(DBGFLAGS) $<

$(TGTDIR)/%.o: $(SRCDIR)/%.c $(HEADERS)
	$(CC) -o $@ $(CFLAGS) $<

$(TGTDIRS):
	mkdir -p $(TGTDIRS)

$(DBGDIRS):
	mkdir -p $(DBGDIRS)
