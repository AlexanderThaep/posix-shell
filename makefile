SHELL=/bin/sh
CC_VERBOSE = $(CC)
CC_NO_VERBOSE = @echo "Building $@..."; $(CC)

ifeq ($(VERBOSE),YES)
  V_CC = $(CC_VERBOSE)
  AT := 
else
  V_CC = $(CC_NO_VERBOSE)
  AT := @
endif

CC := gcc
OUT := shell
BUILD_DIR := ./build
SRC_DIR := ./src
INC_DIR := ./include

C_FILES = $(wildcard *.c)
O_FILES = $(C_FILES:.c=.o)
	
SRCS = $(shell find $(SRC_DIR) -name '*.c')
OBJS = $(SRCS:%.c=$(BUILD_DIR)/%.o)

.PHONY: all clean build run
.DEFAULT: all

all: clean build

build: $(BUILD_DIR)/$(OUT).out

$(BUILD_DIR)/$(OUT).out: $(OBJS)
	$(V_CC) -o $(BUILD_DIR)/$(OUT).out $^  

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(V_CC) -I$(INC_DIR) -c -o $@ $<

clean:
	$(AT)-rm -rf $(BUILD_DIR)/*

run: $(BUILD_DIR)/$(OUT).out
	$(AT)$<
