# Variables
CC := gcc
CFLAGS := -Wall -Wextra -pedantic
LDFLAGS := -lpthread -lrt -lm
SRCDIR := src
INCDIR := inc
OBJDIR := obj
BINDIR := bin
TARGET := $(BINDIR)/my_app
SOURCES := $(wildcard $(SRCDIR)/*.c)
OBJECTS := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

UTESTDIR := utests
UTESTSOURCES := $(wildcard $(UTESTDIR)/*.c)
UTESTOBJECTS := $(UTESTSOURCES:$(UTESTDIR)/%.c=$(OBJDIR)/%.o)
UTESTTARGETS := $(UTESTSOURCES:$(UTESTDIR)/%.c=$(BINDIR)/%)

all: $(BINDIR) $(OBJDIR) $(TARGET)

$(BINDIR):
	mkdir -p $(BINDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

clean:
	rm -rf $(OBJDIR) $(BINDIR)

$(BINDIR)/%: $(OBJDIR)/%.o $(OBJDIR)/queue.o
	$(CC) $^ -o $@ $(LDFLAGS)

$(BINDIR)/utest_ipc_handler: $(OBJDIR)/utest_ipc_handler.o $(OBJDIR)/queue.o $(OBJDIR)/ipc_handler.o $(OBJDIR)/shutdown.o
	$(CC) $^ -o $@ $(LDFLAGS)

$(OBJDIR)/%.o: $(UTESTDIR)/%.c
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

tests: $(UTESTTARGETS)
	@for test in $(UTESTTARGETS); do \
		$$test; \
	done

.PHONY: all clean tests
