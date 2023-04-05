#pragma once

typedef struct Circle {
    double x;
    double y;
    double radius;
} Circle;

void print_error(int col, const char* line, const char* message);
int parse_circle(const char* line, struct Circle* circle);
double get_circle_area(struct Circle* circle);
double get_circle_perimeter(struct Circle* circle);
int circles_intersect(struct Circle* circle1, struct Circle* circle2);