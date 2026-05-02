#include <gtest/gtest.h>

#include "../src/math_utils.h"

TEST(ClampTest, BelowRange) {
    EXPECT_FLOAT_EQ(clampf(-1.0f, 0.0f, 1.0f), 0.0f);
}
TEST(ClampTest, AboveRange) {
    EXPECT_FLOAT_EQ(clampf(2.0f, 0.0f, 1.0f), 1.0f);
}
TEST(ClampTest, InsideRange) {
    EXPECT_FLOAT_EQ(clampf(0.5f, 0.0f, 1.0f), 0.5f);
}
TEST(ClampTest, AtBounds) {
    EXPECT_FLOAT_EQ(clampf(0.0f, 0.0f, 1.0f), 0.0f);
    EXPECT_FLOAT_EQ(clampf(1.0f, 0.0f, 1.0f), 1.0f);
}

TEST(LerpTest, AtZero) {
    EXPECT_FLOAT_EQ(lerpf(0.0f, 10.0f, 0.0f), 0.0f);
}
TEST(LerpTest, AtOne) {
    EXPECT_FLOAT_EQ(lerpf(0.0f, 10.0f, 1.0f), 10.0f);
}
TEST(LerpTest, AtMiddle) {
    EXPECT_FLOAT_EQ(lerpf(0.0f, 10.0f, 0.5f), 5.0f);
}
TEST(LerpTest, NegativeEndpoints) {
    EXPECT_FLOAT_EQ(lerpf(-5.0f, 5.0f, 0.5f), 0.0f);
}

// Triangle vertices match main.cpp NDC coords:
//   A = (-0.6, -0.4),  B = (0.6, -0.4),  C = (0.0, 0.6)
TEST(TriangleTest, CentreIsInside) {
    EXPECT_TRUE(pointInTriangle(0.0f, 0.0f, -0.6f, -0.4f, 0.6f, -0.4f, 0.0f, 0.6f));
}
TEST(TriangleTest, CornerIsOutside) {
    EXPECT_FALSE(pointInTriangle(0.9f, 0.9f, -0.6f, -0.4f, 0.6f, -0.4f, 0.0f, 0.6f));
}
TEST(TriangleTest, BelowBaseIsOutside) {
    EXPECT_FALSE(pointInTriangle(0.0f, -0.5f, -0.6f, -0.4f, 0.6f, -0.4f, 0.0f, 0.6f));
}
TEST(TriangleTest, VertexIsInside) {
    EXPECT_TRUE(pointInTriangle(-0.6f, -0.4f, -0.6f, -0.4f, 0.6f, -0.4f, 0.0f, 0.6f));
}
