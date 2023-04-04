#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100

typedef struct {
    double x;
    double y;
    double radius;
} Circle;

void print_error(int col, const char* line, const char* message) {
    printf("%s\n", line);
    for(int i = 0; i < col; i++)
    {
        printf(" ");
    }
    printf("^Error at column %d: %s\n", col, message);
}

int parse_circle(const char* line, Circle* circle) {
    int count = sscanf(line, "circle(%lf%*[ \t]%lf,%lf)", &circle->x, &circle->y, &circle->radius);
    if (count == 3) {
        return 1;
    } else {
        print_error(0, line, "invalid circle format.");
        return 0;
    }
}


int main(int argc, char* argv[]) {
    FILE* fp;
    char line[MAX_LINE_LENGTH];
    Circle circle;
    int line_num = 1;
    if (argc < 2) {
        printf("Usage: %s [input_file_name]\n", argv[0]);
        return 1;
    }
    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("Error: could not open input file\n");
        return 1;
    }
    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
        if (parse_circle(line, &circle)) {
            printf("Circle: (%f, %f, %f)\n", circle.x, circle.y, circle.radius);
        }
        line_num++;
    }
    fclose(fp);
    return 0;
}