NAME	= raytracer

# Compiler and flags
CXX	= g++
CXXFLAGS	= -Wall -Wextra -std=c++11 -I include

# Directories
SRC_DIR	= srcs
OBJ_DIR	= obj
DEP_DIR	= dep

# Source and object files
SRCS	= $(wildcard $(SRC_DIR)/*.cpp)
OBJS	= $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
DEPS	= $(SRCS:$(SRC_DIR)/%.cpp=$(DEP_DIR)/%.d)

# Create directories if they don't exist
$(shell mkdir -p $(OBJ_DIR) $(DEP_DIR))

# Main target
$(NAME): $(OBJS)
		$(CXX) $(OBJS) -o $(NAME)

# Include dependencies
-include $(DEPS)

# Compile source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
		$(CXX) $(CXXFLAGS) -MMD -MP -MF $(DEP_DIR)/$*.d -c $< -o $@

.PHONY: clean fclean re

clean:
		rm -rf $(OBJ_DIR) $(DEP_DIR)

fclean: clean
		rm -f $(NAME)

re: fclean $(NAME)
