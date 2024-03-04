BUILDDIR := build
DBGDIR := $(BUILDDIR)/dbg
TGTDIR := $(BUILDDIR)/target
SRCDIR := ./
INCDIR := include

CC := gcc
CFLAGS := -c -w -O2
DBGFLAGS := -c -w -O2 -ggdb

SOURCES := $(shell find $(SRCDIR) -type f -iname '*.c')
HEADERS := $(shell find $(SRCDIR) -type f -iname '*.h')
TGTOBJ := $(subst ./,$(TGTDIR)/,$(SOURCES:.c=.o))
DBGOBJ := $(subst ./,$(DBGDIR)/,$(SOURCES:.c=.o))

build: target

run: target
	./$(TGTDIR)/compiler $(filter-out $@,$(MAKECMDGOALS))

target: $(TGTDIR) $(SOURCES) $(HEADERS) $(TGTOBJ)
	$(CC) -o $(TGTDIR)/compiler $(TGTOBJ)

debug: $(DBGDIR) $(SOURCES) $(HEADERS) $(DBGOBJ)
	$(CC) -o $(DBGDIR)/compiler $(DBGOBJ)

clean:
	rm -rf $(BUILDDIR)

$(DBGDIR)/%.o: $(SRCDIR)/%.c $(HEADERS)
	$(CC) -o $@ $(DBGFLAGS) $<

$(TGTDIR)/%.o: $(SRCDIR)/%.c $(HEADERS)
	$(CC) -o $@ $(CFLAGS) $<

$(TGTDIR):
	mkdir -p $(TGTDIR)

$(DBGDIR):
	mkdir -p $(DBGDIR)

%:
	@:
