#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct {
    char** lines;       
    int lineCount;      
    int capacity;      
} TextEditor;

TextEditor* createEditor(int initialCapacity);
void insertLine(TextEditor* editor, int index, const char* text);
void deleteLine(TextEditor* editor, int index);
void printAllLines(const TextEditor* editor);
void freeAll(TextEditor* editor);
void shrinkToFit(TextEditor* editor);
void saveToFile(const TextEditor* editor, const char* filename);
void loadFromFile(TextEditor* editor, const char* filename);

int main() {
    TextEditor* editor = createEditor(10); 
    
    printf("=== Minimal Line-Based Text Editor ===\n");
    printf("Commands:\n");
    printf("  insert <index> <text>  - Insert text at line index (0-based)\n");
    printf("  delete <index>         - Delete line at index\n");
    printf("  print                  - Print all lines\n");
    printf("  shrink                 - Reduce memory to fit exact line count\n");
    printf("  save <filename>        - Save to file\n");
    printf("  load <filename>        - Load from file\n");
    printf("  quit                   - Exit program\n\n");
    
    char command[20];
    while (1) {
        printf("> ");
        scanf("%s", command);
        
        if (strcmp(command, "insert") == 0) {
            int index;
            char text[1000];
            
            scanf("%d", &index);
            getchar(); 
            printf("Enter text: ");
            fgets(text, sizeof(text), stdin);
            text[strcspn(text, "\n")] = 0; 
            
            insertLine(editor, index, text);
            printf("Line inserted at index %d\n", index);
        }
        else if (strcmp(command, "delete") == 0) {
            int index;
            scanf("%d", &index);
            deleteLine(editor, index);
            printf("Line at index %d deleted\n", index);
        }
        else if (strcmp(command, "print") == 0) {
            printAllLines(editor);
        }
        else if (strcmp(command, "shrink") == 0) {
            shrinkToFit(editor);
            printf("Memory shrunk to fit %d lines\n", editor->lineCount);
        }
        else if (strcmp(command, "save") == 0) {
            char filename[100];
            scanf("%s", filename);
            saveToFile(editor, filename);
            printf("Saved to %s\n", filename);
        }
        else if (strcmp(command, "load") == 0) {
            char filename[100];
            scanf("%s", filename);
            loadFromFile(editor, filename);
            printf("Loaded from %s\n", filename);
        }
        else if (strcmp(command, "quit") == 0) {
            break;
        }
        else {
            printf("Unknown command. Try again.\n");
        }
    }
    
    freeAll(editor);
    free(editor);
    printf("Editor closed. Memory freed.\n");
    
    return 0;
}


TextEditor* createEditor(int initialCapacity) {
    TextEditor* editor = (TextEditor*)malloc(sizeof(TextEditor));
    if (!editor) {
        perror("Failed to allocate editor");
        exit(EXIT_FAILURE);
    }
    
    editor->lines = (char**)malloc(initialCapacity * sizeof(char*));
    if (!editor->lines) {
        perror("Failed to allocate lines array");
        free(editor);
        exit(EXIT_FAILURE);
    }
    
    editor->lineCount = 0;
    editor->capacity = initialCapacity;
    
    return editor;
}


void insertLine(TextEditor* editor, int index, const char* text) {
    if (index < 0 || index > editor->lineCount) {
        printf("Error: Index %d out of bounds (0-%d)\n", index, editor->lineCount);
        return;
    }
    
    
    if (editor->lineCount >= editor->capacity) {
        int newCapacity = editor->capacity * 2;
        char** newLines = (char**)realloc(editor->lines, newCapacity * sizeof(char*));
        if (!newLines) {
            perror("Failed to expand lines array");
            return;
        }
        editor->lines = newLines;
        editor->capacity = newCapacity;
        printf("Expanded capacity to %d lines\n", newCapacity);
    }
    
    if (index < editor->lineCount) {
        memmove(&editor->lines[index + 1], &editor->lines[index], 
                (editor->lineCount - index) * sizeof(char*));
    }
    
    editor->lines[index] = (char*)malloc(strlen(text) + 1);
    if (!editor->lines[index]) {
        perror("Failed to allocate memory for line");
        
        if (index < editor->lineCount) {
            memmove(&editor->lines[index], &editor->lines[index + 1], 
                    (editor->lineCount - index) * sizeof(char*));
        }
        return;
    }
    
    strcpy(editor->lines[index], text);
    editor->lineCount++;
}

void deleteLine(TextEditor* editor, int index) {
    if (index < 0 || index >= editor->lineCount) {
        printf("Error: Index %d out of bounds (0-%d)\n", index, editor->lineCount - 1);
        return;
    }
    
    free(editor->lines[index]);
    
    if (index < editor->lineCount - 1) {
        memmove(&editor->lines[index], &editor->lines[index + 1], 
                (editor->lineCount - index - 1) * sizeof(char*));
    }
    
    editor->lineCount--;
}

void printAllLines(const TextEditor* editor) {
    if (editor->lineCount == 0) {
        printf("Editor is empty.\n");
        return;
    }
    
    printf("\n=== Text Buffer (%d lines) ===\n", editor->lineCount);
    for (int i = 0; i < editor->lineCount; i++) {
        printf("%3d: %s\n", i, editor->lines[i]);
    }
    printf("==============================\n");
}

void freeAll(TextEditor* editor) {
    for (int i = 0; i < editor->lineCount; i++) {
        free(editor->lines[i]);
    }
    free(editor->lines);
}

void shrinkToFit(TextEditor* editor) {
    if (editor->lineCount < editor->capacity) {
        char** newLines = (char**)realloc(editor->lines, editor->lineCount * sizeof(char*));
        if (!newLines && editor->lineCount > 0) {
            perror("Failed to shrink array");
            return;
        }
        if (editor->lineCount > 0) {
            editor->lines = newLines;
        }
        editor->capacity = editor->lineCount;
    }
}

void saveToFile(const TextEditor* editor, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("Failed to open file for writing");
        return;
    }
    
    for (int i = 0; i < editor->lineCount; i++) {
        fprintf(file, "%s\n", editor->lines[i]);
    }
    
    fclose(file);
}

void loadFromFile(TextEditor* editor, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file for reading");
        return;
    }
    
    for (int i = 0; i < editor->lineCount; i++) {
        free(editor->lines[i]);
    }
    editor->lineCount = 0;
    
    char buffer[1000];
    int lineNum = 0;
    
    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = 0;
        
        if (lineNum >= editor->capacity) {
            int newCapacity = editor->capacity * 2;
            char** newLines = (char**)realloc(editor->lines, newCapacity * sizeof(char*));
            if (!newLines) {
                perror("Failed to expand during file load");
                fclose(file);
                return;
            }
            editor->lines = newLines;
            editor->capacity = newCapacity;
        }
        
        editor->lines[lineNum] = (char*)malloc(strlen(buffer) + 1);
        if (!editor->lines[lineNum]) {
            perror("Failed to allocate memory during file load");
            fclose(file);
            return;
        }
        
        strcpy(editor->lines[lineNum], buffer);
        lineNum++;
    }
    
    editor->lineCount = lineNum;
    fclose(file);
}