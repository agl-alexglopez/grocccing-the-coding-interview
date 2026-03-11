.PHONY: default build gcc-release gcc-debug clang-release clang-debug sanitize-debug sanitize-release clean tidy format problems

MAKE := $(MAKE)
MAKEFLAGS += --no-print-directory
# Adjust parallel build jobs based on your available cores.
JOBS ?= $(shell (command -v nproc > /dev/null 2>&1 && echo "-j$$(nproc)") || echo "")
BUILD_DIR := build/

default: build

build:
	cmake --build $(BUILD_DIR) $(JOBS) --target utility problems

gcc-release:
	cmake --preset=gcc-release
	$(MAKE) build

gcc-debug:
	cmake --preset=gcc-debug
	$(MAKE) build

clang-release:
	cmake --preset=clang-release
	$(MAKE) build

clang-debug:
	cmake --preset=clang-debug
	$(MAKE) build

sanitize-release:
	cmake --preset=gcc-sanitize-release
	$(MAKE) build

sanitize-debug:
	cmake --preset=gcc-sanitize-debug
	$(MAKE) build

format:
	cmake --build $(BUILD_DIR) $(JOBS) --target format

tidy:
	cmake --build $(BUILD_DIR) $(JOBS) --target tidy $(JOBS)

problems:
	$(MAKE) build
	@if [ -x "$(BUILD_DIR)debug/bin/run_problems" ]; then                   \
		$(BUILD_DIR)debug/bin/run_problems $(BUILD_DIR)debug/bin/problems/; \
	elif [ -x "$(BUILD_DIR)bin/run_problems" ]; then                        \
		$(BUILD_DIR)bin/run_problems $(BUILD_DIR)bin/problems/;             \
	else                                                                    \
		echo "No problem runner found";                                     \
		exit 1;                                                             \
	fi

clean:
	rm -rf build/ install/
