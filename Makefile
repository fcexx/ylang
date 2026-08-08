CC  := gcc
CXX := g++

TARGET := ylang

CFLAGS   := -Wall -Wextra -O2
CXXFLAGS := -Wall -Wextra -O2

C_SOURCES := $(shell find . -type f -name '*.c')
CPP_SOURCES := $(shell find . -type f -name '*.cpp')

C_OBJECTS := $(C_SOURCES:.c=.o)
CPP_OBJECTS := $(CPP_SOURCES:.cpp=.o)

OBJECTS := $(C_OBJECTS) $(CPP_OBJECTS)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@

%.o: %.c
	@echo "CC  $<"
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.cpp
	@echo "CXX $<"
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	find . -type f -name '*.o' -delete
	rm -f $(TARGET)
