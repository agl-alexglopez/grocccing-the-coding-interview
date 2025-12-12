#!/usr/bin/env bash

set -euo pipefail

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <problem_name>"
    exit 1
fi

PROBLEM="$1"
DIR="groccc/$PROBLEM"
CMAKELISTS="groccc/CMakeLists.txt"

###########################################
# Validate input
###########################################
if [ ! -d "$DIR" ]; then
    echo "Error: problem '$PROBLEM' does not exist at $DIR"
    exit 1
fi

if [ ! -f "$CMAKELISTS" ]; then
    echo "Error: $CMAKELISTS not found."
    exit 1
fi

###########################################
# Remove problem directory
###########################################
echo "Removing directory $DIR"
rm -rf "$DIR"

###########################################
# Remove add_problem(PROBLEM) line
###########################################
# We remove the exact literal "add_problem(<problem>)"
# anchored to the line so no substring matches occur.
pattern="add_problem(${PROBLEM})"

echo "Updating $CMAKELISTS: removing line '$pattern'"

# Use a temporary file to safely rewrite
tmpfile=$(mktemp)

# Filter out the exact line
grep -v -x "$pattern" "$CMAKELISTS" > "$tmpfile"

# Move result back into place
mv "$tmpfile" "$CMAKELISTS"

echo "Problem '$PROBLEM' removed."

