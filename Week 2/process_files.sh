#!/usr/bin/env bash


KEYWORD="TODO"              # Keyword to look for in the filename 
RESULT_FILE="result.log"    # Log file to write matching paths
START_DIR="$(pwd)"          # Directory to start searching

# Clear/overwrite previous result log if it exists
> "$RESULT_FILE"



while IFS= read -r -d '' file; do
    echo "$file" >> "$RESULT_FILE"   # record path
    chmod 444 "$file"                # read-only
done < <(find "$START_DIR" -type f -name '*.txt' -print0 | grep -z "${KEYWORD}")
# -print0 | grep -z handle paths with spaces or unusual characters safely.

# Count processed files
count=$(wc -l < "$RESULT_FILE")

if [[ "$count" -eq 0 ]]; then
    # No matches: overwrite log with message and inform user
    echo "nothing has been found, please update the keyword and try again." > "$RESULT_FILE"
    echo "⚠️  Nothing matched the keyword \"$KEYWORD\". Check $RESULT_FILE for details."
else
    echo "✅ Process finished. $count file(s) processed. Paths saved to '$RESULT_FILE'."  
     # Mathes: Final message to the user
fi
