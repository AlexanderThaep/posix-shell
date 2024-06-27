PREFIX := /usr/local

INCS := -Iinclude/

CFLAGS := -std=gnu17 -Wall $(INCS)
LDFLAGS :=
CC := cc

ifeq ($(DEBUG),1)
	CFLAGS += -Og -g3
else
	CFLAGS += -O3 -s
endif

OUT := shell
BUILD := ./build
SRC := ${wildcard src/*.c}
OBJ := ${SRC:%.c=$(BUILD)/%.o}


.PHONY: all clean build
.DEFAULT: all

all: build

build: $(BUILD)/$(OUT)

$(BUILD)/$(OUT): $(OBJ)
	$(CC) -o $(BUILD)/$(OUT) $(LDFLAGS) $^  

$(BUILD)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@rm -r $(BUILD)