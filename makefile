CC = gcc
# Add the -I flag here
CFLAGS = -I./headers

# Define paths
SRC_DIR = sources
OBJ_DIR = objects

# Find all .c files in the source directory
SRCS = $(wildcard $(SRC_DIR)/*.c)
# Convert source filenames to object filenames in the object directory
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

run: $(OBJS)
	$(CC) $(CFLAGS) -o run $(OBJS)

# Compile .c files into the objects directory
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) run
