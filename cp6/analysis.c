
#include "repository.h"

void print_student(Student *s) {
    fprintf(stdout, "+---------------+--------+---+----------+");
    if(s->tests != NULL) {
    for(int i = 0; i < s->count; i++) {
        for(int j = 0; j < strlen(s->tests[i]->name); j++) fprintf(stdout, "-");
        fprintf(stdout, "--+");
    }
    }
    fprintf(stdout, "\n");
    fprintf(stdout, "|%-15s|   %c.%c  | %s |%-10s|", s->surname, s->initials[0], s->initials[1], s->sex, s->group);
    if(s->tests != NULL) {
    for(int i = 0; i < s->count; i++) fprintf(stdout, "%s %d|", s->tests[i]->name, s->tests[i]->score);
    }
    fprintf(stdout, "\n");
    fprintf(stdout, "+---------------+--------+---+----------+");
    if(s->tests != NULL) {
    for(int i = 0; i < s->count; i++) {
        for(int j = 0; j < strlen(s->tests[i]->name); j++) fprintf(stdout, "-");
        fprintf(stdout, "--+");
    }
        fprintf(stdout, "\n");
    }
}

int main(int argc, const char * argv[]) {

    FILE *f;
    
    f = fopen("BD.bin", "rb");
    char p[MAXCHAR] = "";
    bool fflag = false;
    for(int i = 1; i< argc; i++) {
        if(strcmp(argv[i], "-f") == 0) {
            fprintf(stdout, "+---------------+--------+---+----------+-----\n");
            fprintf(stdout, "|    Surname    |initials|sex|  group   |exams\n");
            fflag = true;
        }
        if(strcmp(argv[i], "-p") == 0) {
            strcpy(p, argv[i+1]);
            i++;
        }
    }
    Student s;
    int count = 0;
    while(get_student(&s, f) == 0) {
            int five_count = 0;
            for(int i = 0; i < s.count; i ++) {
                if(s.tests[i]->score == 3) {
                    five_count+=1;
                }
            }
            if(five_count > 2) {
                count+=1;
                if(fflag) print_student(&s);
            }
    }
    fprintf(stdout, "Count of students with more than two '3' scores in tests or exams: %d\n", count);
    fclose(f);
    return 0;
}

