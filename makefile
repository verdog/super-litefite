CC = g++
CFLAGS = -g -Wall -MMD -MP -std=c++14
LLIBS = -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-network

SRCDIR = src
OBJDIR = obj
BINDIR = bin

SRCS = $(shell find src -name '*.cpp')
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))
DEPS = $(OBJS:.o=.d)
BIN = super-litefite

all: $(BINDIR)/$(BIN)

fast: clean $(BINDIR)/$(BIN)

fast: CFLAGS += -O2

$(BINDIR)/$(BIN): $(OBJS)
	@mkdir -p $(@D)
	$(CC) $^ -o $@ $(LLIBS)

$(OBJS): $(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

-include $(DEPS)

run: $(BINDIR)/$(BIN)
	./bin/$(BIN)

benchmark: all
	./bin/$(BIN) benchmark

clean:
	-rm $(BINDIR)/$(BIN) $(OBJS) $(DEPS)
