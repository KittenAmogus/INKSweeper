# == Paths ==
# SDK Sysroot
# To download sdk use `make sdk`
SDK_PATH  = ~/libs/SDK_6.3.0
SYSROOT   = $(SDK_PATH)/SDK-B288/usr/arm-obreey-linux-gnueabi/sysroot
LIB_DIR   = $(SYSROOT)/usr/local/lib

# == Settings ==
# InkPad Compiler
CC  = $(SDK_PATH)/SDK-B288/usr/bin/arm-obreey-linux-gnueabi-gcc

# Flags
CFLAGS  = -Wall -O2 -I$(SYSROOT)/usr/local/include -I./src
LDFLAGS = -L$(LIB_DIR) -linkview -Wl,--allow-shlib-undefined

# Main file
TARGET  = app.app

# Directories
SRCDIR  = src
BLDDIR  = build

# Source dirs autosearch
SRC_INNER = $(shell find $(SRCDIR) -mindepth 1 -type d)
BLD_INNER = $(patsubst $(SRCDIR)/%,$(BLDDIR)/%,$(SRC_INNER))

# Source files autosearch
SOURCES = $(shell find $(SRCDIR) -name '*.c')
OBJECTS = $(patsubst $(SRCDIR)/%,$(BLDDIR)/%.o,$(SOURCES))

# == Rules ==
.PHONY: clean all sdk
all: sdk $(TARGET)

# Main link
$(TARGET): $(OBJECTS)
	@echo "-- Linking $@ "
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)
	@rm -rf $(BLDDIR)

# src/dir/File.c -> build/dir/File.o
$(BLDDIR)/%.c.o: $(SRCDIR)/%.c
	@echo "-- Compiling $< -> $@"
	@mkdir -p $(BLDDIR) $(BLD_INNER)
	$(CC) $(CFLAGS) -c $< -o $@

# Cleaning
clean:
	@echo "-- Cleaning up"
	@rm -rf $(BLDDIR) $(TARGET)

# Github cloning
sdk: $(SDK_PATH)

$(SDK_PATH):
	@mkdir -pv $(SDK_PATH)
	@echo "-- SDK not found!"
	@echo "  - Downloading SDK 6.3.0"
	@git clone "https://github.com/pocketbook/SDK_6.3.0" $(SDK_PATH)
	# @echo "To get headers run `git checkout 6.5` in $(SDK_PATH)"
	@echo "  - Changing branch to 6.5"
	@git -C $(SDK_PATH) checkout 6.5
