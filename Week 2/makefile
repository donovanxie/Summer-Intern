# ------ config ----------------------------------------------------------
SRC      := week1.c
X86_BIN  := week1_x86
ARM_BIN  := week1_arm

HOST_CC  := gcc
ARM_CC   ?= arm-linux-gnueabihf-gcc       # override: make ARM_CC=aarch64-linux-gnu-gcc

# ------ default target --------------------------------------------------
all: $(X86_BIN) $(ARM_BIN)
	@echo "✅  all builds done"

# ------ individual builds ----------------------------------------------
$(X86_BIN): $(SRC)
	@echo "→ compiling $(SRC) for x86…"
	@$(HOST_CC) $< -o $@
	@echo "  x86 build done"

$(ARM_BIN): $(SRC)
	@echo "→ compiling $(SRC) for ARM…"
	@$(ARM_CC)  $< -o $@
	@echo "  ARM build done"

# ------ housekeeping ----------------------------------------------------
clean:
	@rm -f $(X86_BIN) $(ARM_BIN)
	@echo "🗑️  cleaned"

.PHONY: all clean


