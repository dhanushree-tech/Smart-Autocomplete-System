SMART AUTOCOMPLETE SYSTEM
DSA Mini Project using C

FILES
- smart_autocomplete.c : Complete C source code
- README.txt            : Instructions and project details

DSA CONCEPTS
- Trie (Prefix Tree): stores words character by character.
- Depth First Search (DFS): visits the Trie nodes to display all
  words that begin with the entered prefix.

FEATURES
1. Add a word to the dictionary.
2. Search for words using a prefix.
3. Display all matching suggestions.
4. Exit the application.

HOW TO COMPILE
Using GCC:
    gcc smart_autocomplete.c -o autocomplete

HOW TO RUN
Windows:
    autocomplete.exe

Linux / macOS:
    ./autocomplete

SAMPLE
Choose 2 (Search Suggestions), then enter:
    pro

Possible suggestions:
    program
    programmer
    programming
    process
    project

NOTES
- The initial dictionary is loaded when the program starts.
- Words and prefixes may be entered in uppercase or lowercase.
- Only English letters are accepted; spaces and numbers are not supported.
- Words added during a run remain available until the program exits.
