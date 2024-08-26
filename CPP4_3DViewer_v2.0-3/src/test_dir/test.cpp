#include <gtest/gtest.h>
#include <iostream>
#include <math.h>

#include "../model/model_facade.h"

TEST(ModelTest, Test1) {
    s21::Model m("test_object/test.obj");
    m.Init();
    std::vector<float> orig = {0.35, -0.35, -0.35, 0.35, -0.35, 0.35,
                               -0.35, -0.35, 0.35, -0.35, -0.35, -0.35,
                               0.35, 0.35, -0.35, 0.35, 0.35, 0.35,
                               -0.35, 0.35, 0.35, -0.35, 0.35, -0.35};
    ASSERT_EQ(m.GetVertexes().size(), orig.size());
    for (int i = 0; i < orig.size(); ++i) {
        EXPECT_EQ(m.GetVertexes()[i], orig[i]);
    }
}

TEST(ModelTest, Test2) {
    s21::Model m("test_object/test.obj");
    m.Init();
    std::vector<double> orig = {
        1, 2, 2, 3, 3, 1, 7, 6, 6, 5, 5, 7, 4, 5, 5, 1, 1, 4, 5, 6, 6, 2, 2, 5,
        2, 6, 6, 7, 7, 2, 0, 3, 3, 7, 7, 0, 0, 1, 1, 3, 3, 0, 4, 7, 7, 5, 5, 4,
        0, 4, 4, 1, 1, 0, 1, 5, 5, 2, 2, 1, 3, 2, 2, 7, 7, 3, 4, 0, 0, 7, 7, 4};
    ASSERT_EQ(m.GetVertexes().size(), orig.size() / 3);
    for (int i = 0; i < orig.size(); ++i) {
        EXPECT_EQ(m.GetFaces()[i], orig[i]);
    }
}

TEST(ModelTest, Test3) {
    s21::Model m("test_object/????.obj");
    EXPECT_THROW(m.Init();, std::runtime_error);
}

TEST(ModelTest, Test4) {
    s21::Model m("test_object/empty.obj");
    EXPECT_THROW(m.Init(), std::runtime_error);
}

TEST(ModelTest, Test5) {
    s21::Model m("test_object/test_object1.obj");
    EXPECT_THROW(m.Init(), std::runtime_error);
}

TEST(ModelTest, Test6) {
    s21::Model m("test_object/test_object2.obj");
    EXPECT_THROW(m.Init(), std::runtime_error);
}

TEST(ModelTest, Test7) {
    s21::Model m("test_object/test_vertex1.obj");
    EXPECT_THROW(m.Init(), std::runtime_error);
}

TEST(ModelTest, Test8) {
    s21::Model m("test_object/test_vertex2.obj");
    EXPECT_THROW(m.Init(), std::runtime_error);
}

TEST(ModelTest, Test9) {
    s21::Data d;
    s21::Transform t(d);
    t.Move(QVector3D(5, -4, 3));
    QMatrix4x4 res = t.Getter();
    QMatrix4x4 orig = QMatrix4x4(1, 0, 0, 5, 0, 1, 0, -4, 0, 0, 1, 1, 0, 0, 0, 1);
    EXPECT_EQ(res, orig);
}

TEST(ModelTest, Test10) {
    s21::Data d;
    s21::Transform t(d);
    t.Scale(5);
    QMatrix4x4 res = t.Getter();
    QMatrix4x4 orig = QMatrix4x4(5, 0, 0, 0, 0, 5, 0, 0, 0, 0, 5, 0, 0, 0, 0, 1);
    EXPECT_EQ(res, orig);
}

TEST(ModelTest, Test11) {
    s21::Data d;
    s21::Transform t(d);
    t.Rotate(QVector3D(M_PI, M_PI / 2, 0));
    QMatrix4x4 res = t.Getter();
    QMatrix4x4 orig = QMatrix4x4(0.998497, 0.00150229, 0.0547831, 0, 0, 0.999624, -0.0274121, 0, -0.0548037, 0.0273709, 0.998122, 0, 0, 0, 0, 1);
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            ASSERT_NEAR(res(i, j), orig(i, j), 0.000001);
        }
    }
}

TEST(ModelTest, Test12) {
    s21::Data d;
    s21::Transform t(d);
    t.Rotate(QVector3D(M_PI, M_PI / 2, 0));
    QMatrix4x4 res = t.Getter();
    QMatrix4x4 orig = QMatrix4x4(0.998497, 0.00150229, 0.0547831, 0, 0, 0.999624, -0.0274121, 0, -0.0548037, 0.0273709, 0.998122, 0, 0, 0, 0, 1);
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            //     std::cout << res(i, j) << " ";
            ASSERT_NEAR(res(i, j), orig(i, j), 0.000001);
        }
    }
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
