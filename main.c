#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<conio.h>

// Structure for Books
struct books {
    int id;
    char bookName[50];
    char authorName[50];
    char date[12];
} b;

// Structure for Students
struct student {
    int id;
    char sName[50];
    char sClass[50];
    int sRoll;
    char bookName[50];
    char date[12];
} s;

FILE *fp;

// Function prototypes
void addBook();
void booksList();
void del();
void issueBook();
void issueList();
void drawLine();

// Main Function
int main() {
    int ch;

    while (1) {
        system("cls");
        drawLine();
        printf("\n\t\t<== Library Management System ==>\n");
        drawLine();
        printf("\n\t1. Add Book\n");
        printf("\t2. Books List\n");
        printf("\t3. Remove Book\n");
        printf("\t4. Issue Book\n");
        printf("\t5. Issued Book List\n");
        printf("\t0. Exit\n");
        drawLine();
        printf("\n\tEnter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 0:
                system("cls");
                printf("\n\tThank you for using the Library Management System!\n");
                drawLine();
                exit(0);

            case 1:
                addBook();
                break;

            case 2:
                booksList();
                break;

            case 3:
                del();
                break;

            case 4:
                issueBook();
                break;

            case 5:
                issueList();
                break;

            default:
                printf("\n\tInvalid Choice! Please try again...\n");
        }
        printf("\n\tPress Any Key To Continue...");
        getch();
    }

    return 0;
}

// Function to draw a horizontal line
void drawLine() {
    for (int i = 0; i < 50; i++) printf("=");
    printf("\n");
}

// Function to add a new book
void addBook() {
    char myDate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(myDate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    strcpy(b.date, myDate);

    fp = fopen("books.txt", "ab");

    system("cls");
    drawLine();
    printf("\n\t<== Add New Book ==>\n");
    drawLine();

    printf("\n\tEnter Book ID: ");
    scanf("%d", &b.id);

    printf("\tEnter Book Name: ");
    fflush(stdin);
    gets(b.bookName);

    printf("\tEnter Author Name: ");
    fflush(stdin);
    gets(b.authorName);

    printf("\n\tBook Added Successfully!\n");

    fwrite(&b, sizeof(b), 1, fp);
    fclose(fp);
}

// Function to display all books
void booksList() {
    system("cls");
    drawLine();
    printf("\n\t<== Available Books ==>\n");
    drawLine();
    printf("\n\t%-10s %-30s %-20s %s\n", "Book ID", "Book Name", "Author", "Date");
    drawLine();

    fp = fopen("books.txt", "rb");
    while (fread(&b, sizeof(b), 1, fp) == 1) {
        printf("\t%-10d %-30s %-20s %s\n", b.id, b.bookName, b.authorName, b.date);
    }

    fclose(fp);
}

// Function to delete a book
void del() {
    int id, f = 0;
    system("cls");
    drawLine();
    printf("\n\t<== Remove Book ==>\n");
    drawLine();

    printf("\n\tEnter Book ID to remove: ");
    scanf("%d", &id);

    FILE *ft;

    fp = fopen("books.txt", "rb");
    ft = fopen("temp.txt", "wb");

    while (fread(&b, sizeof(b), 1, fp) == 1) {
        if (id == b.id) {
            f = 1;
        } else {
            fwrite(&b, sizeof(b), 1, ft);
        }
    }

    if (f == 1) {
        printf("\n\tBook Deleted Successfully!\n");
    } else {
        printf("\n\tBook Not Found!\n");
    }

    fclose(fp);
    fclose(ft);

    remove("books.txt");
    rename("temp.txt", "books.txt");
}

// Function to issue a book
void issueBook() {
    char myDate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(myDate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    strcpy(s.date, myDate);

    int f = 0;

    system("cls");
    drawLine();
    printf("\n\t<== Issue Book ==>\n");
    drawLine();

    printf("\n\tEnter Book ID to issue: ");
    scanf("%d", &s.id);

    fp = fopen("books.txt", "rb");
    while (fread(&b, sizeof(b), 1, fp) == 1) {
        if (b.id == s.id) {
            strcpy(s.bookName, b.bookName);
            f = 1;
            break;
        }
    }
    fclose(fp);

    if (f == 0) {
        printf("\n\tNo book found with this ID. Please try again.\n");
        return;
    }

    fp = fopen("issue.txt", "ab");

    printf("\n\tEnter Student Name: ");
    fflush(stdin);
    gets(s.sName);

    printf("\tEnter Student Class: ");
    fflush(stdin);
    gets(s.sClass);

    printf("\tEnter Student Roll Number: ");
    scanf("%d", &s.sRoll);

    printf("\n\tBook Issued Successfully!\n");

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);
}

// Function to display issued books
void issueList() {
    system("cls");
    drawLine();
    printf("\n\t<== Issued Book List ==>\n");
    drawLine();
    printf("\n\t%-10s %-30s %-20s %-10s %-30s %s\n", "S.ID", "Name", "Class", "Roll", "Book Name", "Date");
    drawLine();

    fp = fopen("issue.txt", "rb");
    while (fread(&s, sizeof(s), 1, fp) == 1) {
        printf("\t%-10d %-30s %-20s %-10d %-30s %s\n", s.id, s.sName, s.sClass, s.sRoll, s.bookName, s.date);
    }

    fclose(fp);
}
