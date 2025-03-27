#!/bin/bash

# Navigate to the pinkshell directory and run make re
make re

# Check if make re was successful
if [ $? -eq 0 ]; then
    # Run the minishell program with valgrind
    valgrind --leak-check=full ./minishell
else
    echo "make re failed. Exiting."
    exit 1
fi
