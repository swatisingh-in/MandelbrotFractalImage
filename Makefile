#############################################################################
# Makefile for building Mini Database
#############################################################################

TARGET_EXEC ?= main

BUILD_DIR ?= ./build
SRC_DIRS ?= ./src

CC = g++
CFLAGS = -Wall -g

SRCS := $(shell find $(SRC_DIRS) -name *.cc)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)


CPPFLAGS ?= -std=gnu++11 

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@

# c++ source
$(BUILD_DIR)/%.cc.o: %.cc
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@


.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)

-include $(DEPS)

MKDIR_P ?= mkdir -p
