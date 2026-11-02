/*
 * Smart Autocomplete System
 * DSA Mini Project using C
 *
 * Data structure: Trie (Prefix Tree)
 * Algorithm: Depth First Search (DFS)
 *
 * Features:
 * 1. Add a word to the dictionary
 * 2. Search suggestions using a prefix
 * 3. Display all matching words
 * 4. Exit the application
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26
#define MAX_WORD_LENGTH 100

typedef struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
    int isEndOfWord;
} TrieNode;

/* Create and initialize a new Trie node. */
TrieNode *createNode(void) {
    TrieNode *node = (TrieNode *)malloc(sizeof(TrieNode));

    if (node == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        node->children[i] = NULL;
    }

    node->isEndOfWord = 0;
    return node;
}

/* Convert a word to lowercase and check that it contains only letters. */
int normalizeWord(char *word) {
    size_t length = strlen(word);

    while (length > 0 &&
           (word[length - 1] == '\n' || word[length - 1] == '\r')) {
        word[--length] = '\0';
    }

    if (length == 0 || length >= MAX_WORD_LENGTH) {
        return 0;
    }

    for (size_t i = 0; i < length; i++) {
        if (!isalpha((unsigned char)word[i])) {
            return 0;
        }
        word[i] = (char)tolower((unsigned char)word[i]);
    }

    return 1;
}

/* Insert a word into the Trie. */
void insertWord(TrieNode *root, const char *word) {
    TrieNode *current = root;

    for (size_t i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';

        if (current->children[index] == NULL) {
            current->children[index] = createNode();
        }

        current = current->children[index];
    }

    current->isEndOfWord = 1;
}

/* Find and return the Trie node corresponding to a prefix. */
TrieNode *findPrefixNode(TrieNode *root, const char *prefix) {
    TrieNode *current = root;

    for (size_t i = 0; prefix[i] != '\0'; i++) {
        int index = prefix[i] - 'a';

        if (current->children[index] == NULL) {
            return NULL;
        }

        current = current->children[index];
    }

    return current;
}

/* Use DFS to collect and display all words below the prefix node. */
void displayWordsDFS(TrieNode *node, char *word, int depth, int *count) {
    if (node == NULL) {
        return;
    }

    if (node->isEndOfWord) {
        word[depth] = '\0';
        printf("%d. %s\n", ++(*count), word);
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i] != NULL) {
            word[depth] = (char)('a' + i);
            displayWordsDFS(node->children[i], word, depth + 1, count);
        }
    }
}

/* Search for and display autocomplete suggestions. */
void searchSuggestions(TrieNode *root, const char *prefix) {
    TrieNode *prefixNode = findPrefixNode(root, prefix);

    if (prefixNode == NULL) {
        printf("\nNo suggestions found for \"%s\".\n", prefix);
        return;
    }

    char word[MAX_WORD_LENGTH];
    strcpy(word, prefix);

    int count = 0;
    printf("\nAutocomplete suggestions for \"%s\":\n", prefix);
    displayWordsDFS(prefixNode, word, (int)strlen(prefix), &count);

    if (count == 0) {
        printf("No suggestions found.\n");
    }
}

/* Read a line safely from standard input. */
void readLine(char *buffer, size_t size) {
    if (fgets(buffer, (int)size, stdin) == NULL) {
        buffer[0] = '\0';
        return;
    }

    size_t length = strlen(buffer);
    if (length > 0 && buffer[length - 1] == '\n') {
        buffer[length - 1] = '\0';
    } else {
        /* Clear remaining characters if the input exceeded the buffer. */
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {
            /* discard */
        }
    }
}

/* Free all dynamically allocated Trie nodes. */
void freeTrie(TrieNode *node) {
    if (node == NULL) {
        return;
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        freeTrie(node->children[i]);
    }

    free(node);
}

int main(void) {
    TrieNode *root = createNode();

    const char *initialWords[] = {
        "program", "programming", "programmer",
        "project", "process", "computer",
        "code", "coding", "college",
        "data", "database", "design",
        "development", "developer", "digital",
        "network", "notebook", "science",
        "search", "student", "system",
        "technology", "tree", "trie"
    };

    int initialWordCount =
        (int)(sizeof(initialWords) / sizeof(initialWords[0]));

    for (int i = 0; i < initialWordCount; i++) {
        insertWord(root, initialWords[i]);
    }

    int choice;
    char input[MAX_WORD_LENGTH];

    printf("====================================\n");
    printf("       SMART AUTOCOMPLETE SYSTEM    \n");
    printf("====================================\n");

    do {
        printf("\n1. Add Word\n");
        printf("2. Search Suggestions\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {
                /* discard invalid input */
            }
            continue;
        }

        /* Remove the newline left by scanf. */
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {
            /* discard */
        }

        switch (choice) {
            case 1:
                printf("Enter a word (letters only): ");
                readLine(input, sizeof(input));

                if (!normalizeWord(input)) {
                    printf("Invalid word. Enter 1 to 99 letters only.\n");
                } else {
                    insertWord(root, input);
                    printf("Word \"%s\" added successfully.\n", input);
                }
                break;

            case 2:
                printf("Enter a prefix (letters only): ");
                readLine(input, sizeof(input));

                if (!normalizeWord(input)) {
                    printf("Invalid prefix. Enter letters only.\n");
                } else {
                    searchSuggestions(root, input);
                }
                break;

            case 3:
                printf("Thank you for using Smart Autocomplete System!\n");
                break;

            default:
                printf("Invalid choice. Please select 1, 2, or 3.\n");
        }

    } while (choice != 3);

    freeTrie(root);
    return 0;
}
