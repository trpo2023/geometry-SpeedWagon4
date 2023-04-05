#include "parser.h"
#include "math.h"
#include "stdio.h"

void print_error(int col, const char* line, const char* message)
{
    printf("%s\n", line);
    for (int i = 0; i < col; i++) {
        printf(" ");
    }
    printf("^ Error at colusmn %d: %s\n", col, message);
}

int parse_circle(const char* line, struct Circle* circle)
{
    int count = sscanf(
            line,
            "circle(%lf%*[ \t]%lf,%lf)",
            &circle->x,
            &circle->y,
            &circle->radius);
    if (count == 3) {
        return 1;
    } else {
        print_error(0, line, "invalid circle format.");
        return 0;
    }
}

double get_circle_area(struct Circle* circle)
{
    return M_PI * circle->radius * circle->radius;
}

double get_circle_perimeter(struct Circle* circle)
{
    return 2 * M_PI * circle->radius;
}

int circles_intersect(struct Circle* circle1, struct Circle* circle2)
{
    double distance = sqrt(
            pow(circle2->x - circle1->x, 2) + pow(circle2->y - circle1->y, 2));
    double radius_sum = circle1->radius + circle2->radius;
    return distance <= radius_sum;
}
