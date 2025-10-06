CC     := gcc
CFLAGS := -Wall -O3
DFLAGS := -Wall -g
LIBS   := -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
LD     := gcc

SRC     := src
INCLUDE := include
BUILD   := build
DEPSDIR := $(BUILD)

BINARY := mutualAttraction
DBGBINARY := $(BINARY)_dbg

SOURCESPATHS := $(wildcard $(SRC)/*.c)
OBJECTS      := $(SOURCESPATHS:$(SRC)/%.c=$(BUILD)/%.o)
DEPS         := $(SOURCESPATHS:$(SRC)/%.c=$(DEPSDIR)/%.d)

$(BINARY): $(OBJECTS)
	$(LD) $(CFLAGS) -I$(INCLUDE) $(OBJECTS) -o $(BINARY) $(LIBS) 

install: $(BINARY)
	cp $(BINARY) /usr/bin/

-include $(DEPSDIR)/$(DEPS)
$(BUILD)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@ -MMD

clean:
	$(RM) $(BUILD)/*

wipe: clean
	$(RM) $(BINARY)

re: fullclean
	$(MAKE) $(BINARY)

run: $(BINARY)
	./$(BINARY)

rerun:
	$(MAKE) re
	$(MAKE) run
