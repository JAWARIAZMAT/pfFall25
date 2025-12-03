#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 100
#define FILENAME "members.dat"

typedef struct {
    int studentID;
    char fullName[MAX_NAME];
    char batch[20];
    char membershipType[10];
    char registrationDate[11];
    char dateOfBirth[11];
    char interest[10];
} Student;

typedef struct {
    Student* students;
    int count;
    int capacity;
} Database;

Database* createDatabase();
void freeDatabase(Database* db);
int loadDatabase(Database* db);
int saveDatabase(Database* db);
int addStudent(Database* db, Student s);
int updateStudent(Database* db, int id);
int deleteStudent(Database* db, int id);
void displayAll(Database* db);
void batchReport(Database* db);
int findStudent(Database* db, int id);

int main() {
    Database* db = createDatabase();
    int choice, id;
    Student newStudent;
    
    printf("=== IEEE/ACM Membership System ===\n");
    
    if (loadDatabase(db)) {
        printf("Loaded %d records\n", db->count);
    }
    
    do {
        printf("\n1. Add Student\n2. Update Student\n3. Delete Student\n");
        printf("4. View All\n5. Batch Report\n6. Exit\nChoice: ");
        scanf("%d", &choice);
        getchar();
        
        switch(choice) {
            case 1:
                printf("Student ID: "); scanf("%d", &newStudent.studentID);
                getchar();
                if (findStudent(db, newStudent.studentID) != -1) {
                    printf("ID already exists!\n");
                    break;
                }
                printf("Name: "); fgets(newStudent.fullName, MAX_NAME, stdin);
                newStudent.fullName[strlen(newStudent.fullName)-1] = '\0';
                printf("Batch (CS/SE/Cyber Security/AI): "); 
                fgets(newStudent.batch, 20, stdin);
                newStudent.batch[strlen(newStudent.batch)-1] = '\0';
                printf("Membership (IEEE/ACM): "); 
                fgets(newStudent.membershipType, 10, stdin);
                newStudent.membershipType[strlen(newStudent.membershipType)-1] = '\0';
                printf("Registration (YYYY-MM-DD): "); 
                fgets(newStudent.registrationDate, 11, stdin);
                getchar();
                printf("Birth (YYYY-MM-DD): "); 
                fgets(newStudent.dateOfBirth, 11, stdin);
                getchar();
                printf("Interest (IEEE/ACM/Both): "); 
                fgets(newStudent.interest, 10, stdin);
                newStudent.interest[strlen(newStudent.interest)-1] = '\0';
                
                if (addStudent(db, newStudent)) {
                    printf("Student added!\n");
                    saveDatabase(db);
                }
                break;
                
            case 2:
                printf("Student ID to update: ");
                scanf("%d", &id);
                getchar();
                if (updateStudent(db, id)) {
                    printf("Updated!\n");
                    saveDatabase(db);
                } else {
                    printf("Not found!\n");
                }
                break;
                
            case 3:
                printf("Student ID to delete: ");
                scanf("%d", &id);
                getchar();
                if (deleteStudent(db, id)) {
                    printf("Deleted!\n");
                    saveDatabase(db);
                } else {
                    printf("Not found!\n");
                }
                break;
                
            case 4:
                displayAll(db);
                break;
                
            case 5:
                batchReport(db);
                break;
                
            case 6:
                saveDatabase(db);
                printf("Saved %d records. Goodbye!\n", db->count);
                break;
        }
    } while (choice != 6);
    
    freeDatabase(db);
    return 0;
}

Database* createDatabase() {
    Database* db = malloc(sizeof(Database));
    db->capacity = 5;
    db->count = 0;
    db->students = malloc(db->capacity * sizeof(Student));
    return db;
}

void freeDatabase(Database* db) {
    free(db->students);
    free(db);
}

int loadDatabase(Database* db) {
    FILE* file = fopen(FILENAME, "rb");
    if (!file) return 0;
    
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    int maxRecords = size / sizeof(Student);
    while (db->capacity < maxRecords) {
        db->capacity *= 2;
        db->students = realloc(db->students, db->capacity * sizeof(Student));
    }
    
    db->count = fread(db->students, sizeof(Student), maxRecords, file);
    fclose(file);
    return 1;
}

int saveDatabase(Database* db) {
    FILE* file = fopen(FILENAME, "wb");
    if (!file) return 0;
    
    fwrite(db->students, sizeof(Student), db->count, file);
    fclose(file);
    return 1;
}

int findStudent(Database* db, int id) {
    for (int i = 0; i < db->count; i++) {
        if (db->students[i].studentID == id) {
            return i;
        }
    }
    return -1;
}

int addStudent(Database* db, Student s) {
    if (db->count >= db->capacity) {
        db->capacity *= 2;
        db->students = realloc(db->students, db->capacity * sizeof(Student));
    }
    
    db->students[db->count] = s;
    db->count++;
    return 1;
}

int updateStudent(Database* db, int id) {
    int index = findStudent(db, id);
    if (index == -1) return 0;
    
    printf("New Batch (CS/SE/Cyber Security/AI): ");
    fgets(db->students[index].batch, 20, stdin);
    db->students[index].batch[strlen(db->students[index].batch)-1] = '\0';
    
    printf("New Membership (IEEE/ACM): ");
    fgets(db->students[index].membershipType, 10, stdin);
    db->students[index].membershipType[strlen(db->students[index].membershipType)-1] = '\0';
    
    return 1;
}

int deleteStudent(Database* db, int id) {
    int index = findStudent(db, id);
    if (index == -1) return 0;
    
    for (int i = index; i < db->count - 1; i++) {
        db->students[i] = db->students[i + 1];
    }
    db->count--;
    return 1;
}

void displayAll(Database* db) {
    if (db->count == 0) {
        printf("No students found.\n");
        return;
    }
    
    printf("\nID\tName\t\tBatch\t\tType\tInterest\n");
    printf("------------------------------------------------\n");
    for (int i = 0; i < db->count; i++) {
        printf("%d\t%s\t%s\t%s\t%s\n",
               db->students[i].studentID,
               db->students[i].fullName,
               db->students[i].batch,
               db->students[i].membershipType,
               db->students[i].interest);
    }
}

void batchReport(Database* db) {
    int csIEEE = 0, csACM = 0, csBoth = 0;
    int seIEEE = 0, seACM = 0, seBoth = 0;
    int cyberIEEE = 0, cyberACM = 0, cyberBoth = 0;
    int aiIEEE = 0, aiACM = 0, aiBoth = 0;
    
    for (int i = 0; i < db->count; i++) {
        Student s = db->students[i];
        
        if (strcmp(s.batch, "CS") == 0) {
            if (strcmp(s.interest, "IEEE") == 0) csIEEE++;
            else if (strcmp(s.interest, "ACM") == 0) csACM++;
            else if (strcmp(s.interest, "Both") == 0) csBoth++;
        }
        else if (strcmp(s.batch, "SE") == 0) {
            if (strcmp(s.interest, "IEEE") == 0) seIEEE++;
            else if (strcmp(s.interest, "ACM") == 0) seACM++;
            else if (strcmp(s.interest, "Both") == 0) seBoth++;
        }
        else if (strcmp(s.batch, "Cyber Security") == 0) {
            if (strcmp(s.interest, "IEEE") == 0) cyberIEEE++;
            else if (strcmp(s.interest, "ACM") == 0) cyberACM++;
            else if (strcmp(s.interest, "Both") == 0) cyberBoth++;
        }
        else if (strcmp(s.batch, "AI") == 0) {
            if (strcmp(s.interest, "IEEE") == 0) aiIEEE++;
            else if (strcmp(s.interest, "ACM") == 0) aiACM++;
            else if (strcmp(s.interest, "Both") == 0) aiBoth++;
        }
    }
    
    printf("\n=== BATCH REPORT ===\n");
    if (csIEEE + csACM + csBoth > 0)
        printf("CS: IEEE=%d, ACM=%d, Both=%d\n", csIEEE, csACM, csBoth);
    if (seIEEE + seACM + seBoth > 0)
        printf("SE: IEEE=%d, ACM=%d, Both=%d\n", seIEEE, seACM, seBoth);
    if (cyberIEEE + cyberACM + cyberBoth > 0)
        printf("Cyber Security: IEEE=%d, ACM=%d, Both=%d\n", cyberIEEE, cyberACM, cyberBoth);
    if (aiIEEE + aiACM + aiBoth > 0)
        printf("AI: IEEE=%d, ACM=%d, Both=%d\n", aiIEEE, aiACM, aiBoth);
}