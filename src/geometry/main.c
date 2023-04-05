#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libgeometry/parser.h>

#define MAX_LINE_LENGTH 100

int main(int argc, char* argv[])
{
    char line[MAX_LINE_LENGTH];
    int is_succeed = 1;
    int line_count = 0;

    FILE* fp;
    Circle* circles = (Circle*)malloc(sizeof(Circle));

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
        line_count++;
        circles = (Circle*)realloc(circles, line_count * sizeof(Circle));
        if (!parse_circle(line, &circles[line_count - 1])) {
            printf("Unexpected parsing error!");
            is_succeed = 0;
        }
    }

    if (is_succeed == 0)
        return 1;

    for (int i = 0; i < line_count; i++) {
        printf("%d. circle(%f %f, %f)\n",
               i + 1,
               circles[i].x,
               circles[i].y,
               circles[i].radius);
        printf("\tperimeter = %f\n", get_circle_perimeter(&circles[i]));
        printf("\tarea = %f\n", get_circle_area(&circles[i]));
        printf("\tintersects:\n");

        for (int j = 0; j < line_count; j++) {
            if (i == j)
                continue;
            if (circles_intersect(&circles[i], &circles[j])) {
                printf("\t\t%d. circle\n", j + 1);
            }
        }
    }
    fclose(fp);
    return 0;
}