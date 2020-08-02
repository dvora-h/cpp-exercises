
#include "test.h"
int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
TEST(basicFuncTest, vectorCtor){
    Vector<int> v1;
    Vector<double> v2(3, 8.4);
    Vector<double> v3(v2);
    ASSERT_EQ(v1.size(), 0);
    ASSERT_EQ(v1.capacity(), 0);
    v1.push_back(5);
    ASSERT_EQ(v1.size(), 1);
    ASSERT_EQ(v1[0], 5);
    ASSERT_EQ(v1.capacity(), 1);
    ASSERT_EQ(v2.size(), 3);
    ASSERT_EQ(v2.capacity(), 3);
    ASSERT_EQ(v2.size(), v3.size());
    ASSERT_EQ(v2.capacity(), v3.capacity());
    ASSERT_EQ(v2[1], 8.4);
}
TEST(basicFuncTest, eqOperator){
    Vector<double> v2(3, 8.4);
    Vector<double> v1(5, 9);
    v1 = v2;
    ASSERT_EQ(v1.size(), 3);
    ASSERT_EQ(v1.capacity(), 3);
    ASSERT_EQ(v1[2], 8.4);
}
TEST(modifiersFuncTest, insert){
    Vector<int> v1(7, 3);
    v1.insert(2, 4, 7);
    ASSERT_EQ(v1.size(), 11);
    ASSERT_EQ(v1.capacity(), 11);
    ASSERT_EQ(v1[2], 7);
    ASSERT_EQ(v1[5], 7);
    ASSERT_EQ(v1[6], 3);
    ASSERT_EQ(v1[10], 3);
}

