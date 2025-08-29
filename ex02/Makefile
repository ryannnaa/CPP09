# === Compiler and Flags ===
CXX       := c++
CXXFLAGS  := -Wall -Wextra -Werror -std=c++98 -Iinc -MMD -MP

# === Directories ===
SRC_DIR   := src
INC_DIR   := inc
OBJ_DIR   := obj

# === Output Name ===
NAME      := PmergeMe

# === Source Files (manually list them here, relative to src/) ===
SRC_FILES := main.cpp PmergeMe.cpp

# === Source Paths ===
SRCS      := $(addprefix $(SRC_DIR)/, $(SRC_FILES))

# === Object and Dependency Paths ===
OBJS      := $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.cpp=.o))
DEPS      := $(OBJS:.o=.d)

# === Rules ===
all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(DEPS)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
