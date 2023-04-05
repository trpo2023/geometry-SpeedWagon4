#include <ctest.h>
#include <libgeometry/parser.h>
#include <math.h>

CTEST(geometry_parser, circle_parse)
{
    Circle circle = {0, 0, 0};
    const char* test_str = "circle(1     2,   3   )";
    parse_circle(test_str, &circle);

    const int exp_x = 1, exp_y = 2, exp_radius = 3;
    ASSERT_EQUAL(exp_x, circle.x);
    ASSERT_EQUAL(exp_y, circle.y);
    ASSERT_EQUAL(exp_radius, circle.radius);
}

CTEST(geometry_parser, area_check)
{
    Circle circle = {0, 0, 0};
    const char* test_str = "circle(1     2,   3)";
    parse_circle(test_str, &circle);

    double exp_area = M_PI * circle.radius * circle.radius;
    ASSERT_EQUAL(exp_area, get_circle_area(&circle));
}