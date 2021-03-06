# The makefile!

PROJECT_DIR  = $(PWD)/../..
BUILD_DIR    = $(PROJECT_DIR)/build/tool
SRC_DIR      = $(PROJECT_DIR)/src/tool
GEN_MAKEFILE = $(BIN_DIR)/Makefile

TOOLCHAIN    = ../share/cmake/generic.cmake
FLAGS        = -DCMAKE_TOOLCHAIN_FILE=$(TOOLCHAIN)

EXECUTABLE = tool
LOC_EXECUTABLE = loc_tool
BALL_EXECUTABLE = ball_tool
VISION_EXECUTABLE = vision_tool
CALIBRATE_EXECUTABLE = calibrate_tool
PLAYBOOK_EXECUTABLE = playbook_tool

.PHONY: build_tool
build_tool:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR); \
	cmake $(FLAGS) $(SRC_DIR); \
	$(MAKE) --no-print-directory $(EXECUTABLE)

.PHONY: tool
tool: build_tool
	@echo "Running tool executable."
	@$(BUILD_DIR)/$(EXECUTABLE)

.PHONY: build_loc
build_loc:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR); \
	cmake $(FLAGS) $(SRC_DIR); \
	$(MAKE) --no-print-directory $(LOC_EXECUTABLE)

.PHONY: loc
loc: build_loc
	@echo "Running loc_tool executable."
	@cd $(BUILD_DIR); \
	./$(LOC_EXECUTABLE)

.PHONY: build_ball
build_ball:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR); \
	cmake $(FLAGS) $(SRC_DIR); \
	$(MAKE) --no-print-directory $(BALL_EXECUTABLE)

.PHONY: ball
ball: build_ball
	@echo "Running ball_tool executable."
	@cd $(BUILD_DIR); \
	./$(BALL_EXECUTABLE)

.PHONY: build_vision
build_vision:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR); \
	cmake $(FLAGS) $(SRC_DIR); \
	$(MAKE) --no-print-directory $(VISION_EXECUTABLE)

.PHONY: vision
vision: build_vision
	@echo "Running vision_tool executable."
	@cd $(BUILD_DIR); \
	./$(VISION_EXECUTABLE)

.PHONY: build_calibrate
build_calibrate:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR); \
	cmake $(FLAGS) $(SRC_DIR); \
	$(MAKE) --no-print-directory $(CALIBRATE_EXECUTABLE)

.PHONY: calibrate
calibrate: build_calibrate
	@echo "Running calibrate_tool executable."
	@cd $(BUILD_DIR); \
	./$(CALIBRATE_EXECUTABLE)

.PHONY: build_playbook
build_playbook:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR); \
	cmake $(FLAGS) $(SRC_DIR); \
	$(MAKE) --no-print-directory $(PLAYBOOK_EXECUTABLE)

.PHONY: playbook
playbook: build_playbook
	@echo "Running playbook_tool executable."
	@cd $(BUILD_DIR); \
	./$(PLAYBOOK_EXECUTABLE)

.PHONY: config
config:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR); \
	cmake $(FLAGS) $(SRC_DIR); \
	ccmake $(SRC_DIR)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)/*
