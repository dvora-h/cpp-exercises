//
// Created by student on 09/06/2020.
//
#include "test.h"
int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST(CtorTest, CreateFixedPoint)
{
    FixedPoint<3> p1(5, 2532);
    ASSERT_DOUBLE_EQ(p1, 7.532);
    FixedPoint<2, char> p2(5,-25);
    ASSERT_DOUBLE_EQ(p2, -5.25);
    FixedPoint<2, short> p3;
    ASSERT_DOUBLE_EQ(p3, 0);
    FixedPoint<3, long> p4(999999999,999);
    ASSERT_EQ(p4.getDollar(), 999999999);
    ASSERT_EQ(p4.getCent(), 999);
    ASSERT_DOUBLE_EQ(p4, 999999999.999);
}

TEST(ArithmeticOperatorTest, PlusOp)
{
    FixedPoint<4, char> p1(5,25);
    FixedPoint<1> p2(2,5);
    FixedPoint<2, char> p3(-1);
    FixedPoint<3> p5(2, 700), p6(2, 400);
    //FixedPoint<4, char> p4=p3+p1;
    ASSERT_DOUBLE_EQ(p1+p2, 7.5025);
    ASSERT_DOUBLE_EQ(p1+5, 10.0025);
    //ASSERT_DOUBLE_EQ(p4, 4.0025);
    ASSERT_DOUBLE_EQ(p5+p6, 5.1);
}

TEST(ArithmeticOperatorTest, MinusOp)
{
    FixedPoint<3> p1(5,257);
    FixedPoint<4, char> p2(2,5098);
    ASSERT_DOUBLE_EQ(p1-p2, 2.7472);
    ASSERT_DOUBLE_EQ(p2-p1, -2.7472);
    ASSERT_DOUBLE_EQ(p2-5, -2.4902);
}

//TEST(ArithmeticOperatorTest, MultiplicationOp)
//{
//    FixedPoint<3, long> p1(2,578);
//    FixedPoint<3, long> p2(2, 369);
//    ASSERT_DOUBLE_EQ(p1*p2, 6.107282);
////    ASSERT_EQ((p1*p2).get_price_in_cents(), 105000);
////    ASSERT_EQ((p2*5).get_price_in_cents(), 100000);
////    ASSERT_EQ((p2*-5).get_price_in_cents(), -100000);
//}

///*TEST(ArithmeticOperatorTest, DivideOp)
//{
//    FixedPoint p1(6,25);
//    FixedPoint p2(2,50);
//    FixedPoint p3(-2,50);
//    ASSERT_EQ((p1/p2).get_price_in_cents(), 2);
//    ASSERT_EQ((p1/3).get_price_in_cents(), 2);
//    ASSERT_EQ((p2/p3).get_price_in_cents(), -1);
//}
//
//TEST(ArithmeticOperatorTest, ModuloOp)
//{
//    FixedPoint p1(5,30);
//    FixedPoint p2(2);
//    ASSERT_EQ((p1%p2).get_price_in_cents(), 130);
//    ASSERT_EQ((p2%5).get_price_in_cents(), 200);
//    ASSERT_EQ((p2%1).get_price_in_cents(), 0);
//}*/
//
//
TEST(ArithmeticOperatorTest, PlusEqOp)
{
    FixedPoint<2, long> p1(5,25);
    FixedPoint<5, long> p2(2,5);
    FixedPoint<1, int> p3(-2,5);
    p1+=p2;
    p2+=2;
    p3+=1;

    ASSERT_DOUBLE_EQ(p1, 7.25);
    ASSERT_DOUBLE_EQ(p2, 4.00005);
    ASSERT_DOUBLE_EQ(p3, -1.5);
}

TEST(ArithmeticOperatorTest, MinusEqOp) {
    FixedPoint<2> p1(5, 25);
    FixedPoint<2> p2(2, 5);
    p1 -= p2;
    p2 -= 3;
    ASSERT_DOUBLE_EQ(p1, 3.20);
    ASSERT_DOUBLE_EQ(p2, -0.95);
}

/*TEST(ArithmeticOperatorTest, MultEqOp)
{
    FixedPoint p1(5,25);
    FixedPoint p2(2,5);
    FixedPoint p3(-2,5);
    p1*=p2;
    p2*=1;
    p3*=1;
    ASSERT_EQ(p1.get_price_in_cents(), 107625);
    ASSERT_EQ(p2.get_price_in_cents(), 20500);
    ASSERT_EQ(p3.get_price_in_cents(), -20500);
}*/

TEST(ArithmeticOperatorTest, Unary)
{
    FixedPoint<2, short> p1(5,25);
    ASSERT_DOUBLE_EQ(-p1, -5.25);
}

TEST(ArithmeticOperatorTest, PreIncreaseOp)
{
    FixedPoint<2, int> p1(5,25);
    FixedPoint<2, int> p2(-1);
    FixedPoint<2, char> p3(0,-25);
    ++p1;
    ++p2;
    ++p3;
    ASSERT_DOUBLE_EQ(p1, 6.25);
    ASSERT_DOUBLE_EQ(p2, 0);
    ASSERT_DOUBLE_EQ(p3, 0.75);
}

TEST(ArithmeticOperatorTest, PreDecreaseOp)
{
    FixedPoint<2> p1(5,25);
    FixedPoint<2, long> p2(0,25);
    --p1;
    --p2;
    ASSERT_DOUBLE_EQ(p1, 4.25);
    ASSERT_DOUBLE_EQ(p2, -0.75);
}

TEST(ArithmeticOperatorTest, PostIncreaseOp)
{
    FixedPoint<2, int> p1(5,25);
    FixedPoint<2, int> p2(-1);
    FixedPoint<2, int> p3(0,-25);
    p1++;
    p2++;
    p3++;
    ASSERT_DOUBLE_EQ(p1, 6.25);
    ASSERT_DOUBLE_EQ(p2, 0);
    ASSERT_DOUBLE_EQ(p3, 0.75);
}

TEST(ArithmeticOperatorTest, PostDecreaseOp)
{
    FixedPoint<2, long> p1(5,25);
    FixedPoint<2, short> p2(0,25);
    p1--;
    p2--;
    ASSERT_DOUBLE_EQ(p1, 4.25);
    ASSERT_DOUBLE_EQ(p2, -0.75);
}

TEST(ComparisonOperatorTest, Equal)
{
    FixedPoint<2> p1(5,25);
    FixedPoint<2> p2(5,25);
    FixedPoint<2, int> p3(2,5);
    ASSERT_TRUE(p1==p2);
    ASSERT_FALSE(p1==p3);
}


TEST(ComparisonOperatorTest, NotEqual)
{
    FixedPoint<2, short> p1(5,25);
    FixedPoint<2, short> p2(5,25);
    FixedPoint<2, char> p3(2,5);
    ASSERT_TRUE(p1!=p3);
    ASSERT_FALSE(p1!=p2);
}


TEST(ComparisonOperatorTest, Smaller)
{
    FixedPoint<2, int> p1(5,25);
    FixedPoint<2, long> p2(2,5);
    ASSERT_FALSE(p1<p2);
    ASSERT_TRUE(p2<p1);
}

TEST(ComparisonOperatorTest, Larger)
{
    FixedPoint<2> p1(5,25);
    FixedPoint<2, char> p2(2,5);
    ASSERT_TRUE(p1>p2);
    ASSERT_FALSE(p2>p1);
}

TEST(ComparisonOperatorTest, SmallerEqual)
{
    FixedPoint<2> p1(5,25);
    FixedPoint<2> p2(2,5);
    FixedPoint<2> p3(2,5);
    ASSERT_FALSE(p1<=p2);
    ASSERT_TRUE(p2<=p3);
}

TEST(ComparisonOperatorTest, LargerEqual)
{
    FixedPoint<2, long> p1(5,25);
    FixedPoint<2, char> p2(2,5);
    FixedPoint<2, short> p3(2,5);
    ASSERT_FALSE(p2>=p1);
    ASSERT_TRUE(p2>=p3);
}

TEST(BasicTest,AssignmentOp)
{
    FixedPoint<2> p1;
    p1=7;
    FixedPoint<2> p2;
    p2=-7;
    ASSERT_DOUBLE_EQ(p1,7.00);
    ASSERT_DOUBLE_EQ(p2,-7.00);
}

TEST(BasicTest, Print)
{
    FixedPoint<4> p1(3);
    FixedPoint<2, int> p2(1,-30);
    FixedPoint<4, long> p3(50,-35);
    FixedPoint<2, char> p4(3,47);
    ASSERT_TRUE(std::cout<<p1<<std::endl);
    ASSERT_TRUE(std::cout<<p2<<std::endl);
    ASSERT_TRUE(std::cout<<p3<<std::endl);
    ASSERT_TRUE(std::cout<<p4<<std::endl);
}

TEST(BasicTest, CastToDouble)
{
    FixedPoint<4> p1(-48695,5784);
    //ASSERT_DOUBLE_EQ(double(p1), -4.5);
    std::cout<<p1.asString()<<std::endl;
    std::cout<<p1.getPrecision()<<std::endl;
    std::cout<<makeMoney(p1)<<std::endl;
}

