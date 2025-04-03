#!/bin/bash

MINISHELL=./minishell  # Adjust path to your minishell binary

# Colors
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

# Define test cases (command => expected_output)
declare -A tests=(
    ["echo Hello World"]="Hello World"
    ["echo 'Single Quotes'"]="Single Quotes"
    ["echo \"Double Quotes\""]="Double Quotes"
    ["echo 'Mixed \"Quotes\"'"]="Mixed \"Quotes\""
    ["ls | wc -l"]="$(ls | wc -l)"
    ["echo \$HOME"]="$HOME"
    ["cat < /etc/passwd | grep root"]="$(cat < /etc/passwd | grep root)"
    ["echo Hello > test_output.txt; cat test_output.txt"]="Hello"
    ["echo hello >> test_output.txt; cat test_output.txt"]="Hello"$'\n'"hello"
    ["mkdir testdir && cd testdir || echo 'Failed'"]="$(mkdir testdir 2>/dev/null && cd testdir && echo Success || echo Failed)"
    ["(echo subshell test)"]="subshell test"
    ["sleep 1 & echo 'Background'"]="Background"
    ["false || echo 'Recovered'"]="Recovered"
)

# Run tests
echo "Running tests..."
for cmd in "${!tests[@]}"; do
    # Run in minishell
    echo -n "$cmd" | $MINISHELL > minishell_out.txt 2>/dev/null
    # Run in bash
    echo -n "$cmd" | bash > bash_out.txt 2>/dev/null
    
    # Read outputs
    minishell_output=$(cat minishell_out.txt)
    bash_output=$(cat bash_out.txt)

    # Compare
    if [ "$minishell_output" == "$bash_output" ]; then
        echo -e "[${GREEN}PASS${NC}] $cmd"
    else
        echo -e "[${RED}FAIL${NC}] $cmd"
        echo "  Expected: '$bash_output'"
        echo "  Got:      '$minishell_output'"
    fi
done

# Cleanup
rm -f test_output.txt bash_out.txt minishell_out.txt
rm -rf testdir

echo "✅ Test run complete!"
