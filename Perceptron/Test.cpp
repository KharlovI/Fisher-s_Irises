//#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
//#include"doctest.h"
//#include"NN.h"
//TEST_CASE("Matrix multiplication 1")
//{
//
//	Matrix A1({ {1,2,3},{-1,2,3},{1,-2,3} });
//	Matrix B1({ {0,4,6}, {8,9,2},{1,1,1} });
//	Matrix answer1({ {19,25,13},{19,17,1},{-13,-11,5} });
//	Matrix temp1 = A1 * B1;
//
//	CHECK(temp1 == answer1);
//}
//
//TEST_CASE("Matrix multiplication 2")
//{
//	Matrix A2({ {1,2,3},{-1,2,3},{1,-2,3} });
//	Matrix B2({ {0,4}, {8,9},{1,1} });
//	Matrix answer2({ {19,25},{19,17},{-13,-11} });
//	Matrix temp2 = A2 * B2;
//	CHECK(temp2 == answer2);
//}
//
//TEST_CASE("Matrix multiplication 3")
//{
//	Matrix A3({ {1,2,3},{-1,2,3}});
//	Matrix B3({ {0,4,6}, {8,9,2},{1,1,1} });
//	Matrix answer3({ {19,25,13},{19,17,1}});
//	Matrix temp3 = A3 * B3;
//	CHECK(temp3 == answer3);
//}