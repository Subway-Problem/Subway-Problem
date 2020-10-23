# Generic makefile for all cpp projects in the directory
# Resides one level above project Makefile
# This file depends on variables having been set before calling:
#   EXE: The name of the result file
#   OBJS: Array of object files (.o)
#   CLEAN_RM: Optional list of additional files to delete on `make clean`
#
# @author Asher Desai

# Compiler/linker config and object/depfile directory:
CXX = g++
LD = g++
OBJS_DIR = .objs

# Asks g++ to gather which headers are used in each source file for later use
# Asks g++ to create a phony target for each dependency
DEPFILE_FLAGS = -MMD -MP

#WARNINGS_AS_ERRORS = -Werror # Enables strict compilation
#WFATAL_ERRORS = -Wfatal-errors # All errors are immediately fatal
WARNINGS = -pedantic -Wall -Wextra $(WARNINGS_AS_ERRORS) $(WFATAL_ERRORS)

# Flags for linking/compiling:
CXXFLAGS += -std=c++14 -O$(OPT_LVL) $(WARNINGS) $(DEPFILE_FLAGS) -g -c
LDFLAGS += -std=c++14

all: $(EXE)

# Rule for linking the final executable:
$(EXE): $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS))
	$(LD) $^ $(LDFLAGS) -o $@

# Ensures that .objs/ exists:
$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

# Compiles each source file into its respective object file:
$(OBJS_DIR)/%.o: %.cpp | $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

-include $(OBJS_DIR)/*.d

# Standard C++ Makefile rules:
clean:
	rm -rf $(EXE) $(OBJS_DIR) $(CLEAN_RM) *.o *.d

tidy: clean
	rm -rf doc

run: $(EXE)
	./$(EXE)

.PHONY: all tidy clean run