# Inverted-Search
An Inverted Search is a data structure used for efficient text searching. Instead of scanning through entire documents, it builds an inverted index that maps each word to the files where it appears. This makes searching much faster, especially for large datasets.
✨ Features

Build an inverted index from multiple text files.

Store words along with the list of files in which they occur.

Handle duplicate words efficiently (word stored once, with file references).

Case-insensitive search for words.

Display results showing all files containing the given word.

Save and load the inverted index from a file.
⚙️ Build & Run

Clone the repository:
git clone https://github.com/your-username/inverted-search.git
cd inverted-search
Compile the project:
gcc inverted_search.c -o inverted_search
Run with text files as input:
Example Usage
Input files:
file1.txt
hello again
search test project
Command:
Example Output:
Word: hello
    Found in: file1.txt, file2.txt

Word: test
    Found in: file1.txt, file2.txt

Word: search
    Found in: file2.txt
Project Structure
.
├── inverted_search.c   # Main source code
├── inverted_index.dat  # Saved index (generated)
├── file1.txt
├── file2.txt
└── README.md
🔑 Core Concepts Demonstrated
Data Structures → Hash tables / Linked lists for word-to-file mapping.

File Handling → Reading multiple files and storing data.

String Processing → Tokenizing and normalizing words.

Search Optimization → Faster lookup using an index.
📝 Sample Code Snippet
typedef struct FileNode {
    char filename[50];
    struct FileNode *next;
} FileNode;

typedef struct WordNode {
    char word[50];
    FileNode *files;
    struct WordNode *next;
} WordNode;

WordNode *indexHead = NULL;

// Function to insert a word into the index
void insertWord(char *word, char *filename) {
    WordNode *current = indexHead;

    // Search if word already exists
    while (current != NULL) {
        if (strcmp(current->word, word) == 0) {
            // Add filename if not already present
            FileNode *f = current->files;
            while (f != NULL) {
                if (strcmp(f->filename, filename) == 0) return; // already exists
                f = f->next;
            }
            // Add new file node
            FileNode *newFile = malloc(sizeof(FileNode));
            strcpy(newFile->filename, filename);
            newFile->next = current->files;
            current->files = newFile;
            return;
        }
        current = current->next;
    }

    // Word not found → create new node
    WordNode *newWord = malloc(sizeof(WordNode));
    strcpy(newWord->word, word);
    newWord->files = NULL;
    newWord->next = indexHead;
    indexHead = newWord;

    FileNode *newFile = malloc(sizeof(FileNode));
    strcpy(newFile->filename, filename);
    newFile->next = NULL;
    newWord->files = newFile;
}
Future Enhancements

Add support for phrase/regex search.

Improve performance with hashing.

Add interactive CLI menu.

Store index in JSON/CSV for external use.
