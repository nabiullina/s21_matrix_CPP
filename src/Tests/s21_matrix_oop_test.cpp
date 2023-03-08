#include "../s21_matrix_oop.h"

#include <gtest/gtest.h>

TEST(S21Matrix_constructor_suite, true_test) {
  S21Matrix first_matrix;

  EXPECT_EQ(first_matrix.getRows(), 0);
  EXPECT_EQ(first_matrix.getCols(), 0);
}

TEST(S21Matrix_copy_constructor_suite, true_test) {
  S21Matrix first_matrix(3, 3);
  S21Matrix second_matrix(first_matrix);

  EXPECT_EQ(first_matrix.getRows(), 3);
  EXPECT_EQ(first_matrix.getCols(), 3);
  EXPECT_EQ(second_matrix.getRows(), 3);
  EXPECT_EQ(second_matrix.getCols(), 3);
  EXPECT_TRUE(first_matrix.EqMatrix(second_matrix));
}

TEST(S21Matrix_copy_constructor_suite, empty_to_empty_test) {
  S21Matrix first_matrix;
  S21Matrix second_matrix(first_matrix);

  EXPECT_EQ(first_matrix.getRows(), 0);
  EXPECT_EQ(first_matrix.getCols(), 0);
  EXPECT_EQ(second_matrix.getRows(), 0);
  EXPECT_EQ(second_matrix.getCols(), 0);
  EXPECT_TRUE(first_matrix.EqMatrix(second_matrix));
}

TEST(S21Matrix_copy_constructor_suite, seg_fault_test) {
  S21Matrix first_matrix(std::move(first_matrix));
}

TEST(S21Matrix_move_constructor_suite, true_test) {
  S21Matrix first_matrix(3, 3);
  S21Matrix second_matrix(std::move(first_matrix));

  EXPECT_EQ(first_matrix.getRows(), 0);
  EXPECT_EQ(first_matrix.getCols(), 0);
  EXPECT_EQ(second_matrix.getRows(), 3);
  EXPECT_EQ(second_matrix.getCols(), 3);
}

TEST(S21Matrix_move_constructor_suite, seg_fault_test) {
  S21Matrix first_matrix(std::move(first_matrix));
}

TEST(setRows_suite, extend_test) {
  S21Matrix first_matrix(3, 3);
  S21Matrix second_matrix(4, 3);

  first_matrix.FillingMatrix();
  second_matrix.FillingMatrix();
  first_matrix.setRows(4);
  second_matrix(3, 0) = 0;
  second_matrix(3, 1) = 0;
  second_matrix(3, 2) = 0;

  EXPECT_TRUE(first_matrix == second_matrix);
}

TEST(setRows_suite, reduce_test) {
  S21Matrix first_matrix(3, 3);
  S21Matrix second_matrix(4, 3);

  first_matrix.FillingMatrix();
  second_matrix.FillingMatrix();
  second_matrix.setRows(3);

  EXPECT_TRUE(first_matrix == second_matrix);
}

TEST(setRows_suite, set_zero_test) {
  S21Matrix first_matrix(3, 3);

  ASSERT_THROW(first_matrix.setRows(0), std::out_of_range);
}

TEST(setCols_suite, extend_test) {
  S21Matrix first_matrix(3, 3);

  first_matrix.FillingMatrix();
  first_matrix.setCols(4);

  EXPECT_EQ(first_matrix(0, 0), 0);
  EXPECT_EQ(first_matrix(0, 1), 1.0);
  EXPECT_EQ(first_matrix(0, 2), 2.0);
  EXPECT_EQ(first_matrix(1, 0), 3.0);
  EXPECT_EQ(first_matrix(1, 1), 4.0);
  EXPECT_EQ(first_matrix(1, 2), 5.0);
  EXPECT_EQ(first_matrix(2, 0), 6.0);
  EXPECT_EQ(first_matrix(2, 1), 7.0);
  EXPECT_EQ(first_matrix(2, 2), 8.0);
  EXPECT_TRUE(0 - first_matrix(0, 3) < 1e-7);
  EXPECT_TRUE(0 - first_matrix(1, 3) < 1e-7);
  EXPECT_TRUE(0 - first_matrix(2, 3) < 1e-7);
}

TEST(setCols_suite, reduce_test) {
  S21Matrix first_matrix(3, 3);

  first_matrix.FillingMatrix();
  first_matrix.setCols(2);

  EXPECT_EQ(first_matrix(0, 0), 0);
  EXPECT_EQ(first_matrix(0, 1), 1.0);
  EXPECT_EQ(first_matrix(1, 0), 3.0);
  EXPECT_EQ(first_matrix(1, 1), 4.0);
  EXPECT_EQ(first_matrix(2, 0), 6.0);
  EXPECT_EQ(first_matrix(2, 1), 7.0);
}

TEST(setCols_suite, set_zero_test) {
  S21Matrix first_matrix(3, 3);

  ASSERT_THROW(first_matrix.setCols(0), std::out_of_range);
}

TEST(EqMatrix_suite, true_test) {
  S21Matrix first_matrix(3, 3);
  S21Matrix second_matrix(3, 3);

  first_matrix.FillingMatrix();
  second_matrix.FillingMatrix();

  EXPECT_TRUE(first_matrix.EqMatrix(second_matrix));
  EXPECT_TRUE(second_matrix.EqMatrix(first_matrix));
  EXPECT_TRUE(first_matrix == second_matrix);
  EXPECT_TRUE(second_matrix == first_matrix);
}

TEST(EqMatrix_suite, false_test) {
  S21Matrix first_matrix(2, 3);
  S21Matrix second_matrix(3, 3);

  first_matrix.FillingMatrix();
  second_matrix.FillingMatrix();

  EXPECT_FALSE(first_matrix.EqMatrix(second_matrix));
  EXPECT_FALSE(second_matrix.EqMatrix(first_matrix));
  EXPECT_FALSE(first_matrix == second_matrix);
  EXPECT_FALSE(second_matrix == first_matrix);
}

TEST(EqMatrix_suite, accuracy_true_test) {
  S21Matrix first_matrix(3, 3);
  S21Matrix second_matrix(3, 3);

  first_matrix.FillingMatrix();
  second_matrix.FillingMatrix();
  for (int i = 0; i < first_matrix.getRows(); i++) {
    for (int j = 0; j < first_matrix.getCols(); j++) {
      first_matrix(i, j) += 0.00000001;
    }
  }

  EXPECT_TRUE(first_matrix.EqMatrix(second_matrix));
  EXPECT_TRUE(first_matrix == second_matrix);
}

TEST(EqMatrix_suite, accuracy_false_test) {
  S21Matrix first_matrix(3, 3);
  S21Matrix second_matrix(3, 3);

  first_matrix.FillingMatrix();
  second_matrix.FillingMatrix();
  for (int i = 0; i < first_matrix.getRows(); i++) {
    for (int j = 0; j < first_matrix.getCols(); j++) {
      first_matrix(i, j) += 0.000001;
    }
  }

  EXPECT_FALSE(first_matrix.EqMatrix(second_matrix));
  EXPECT_FALSE(first_matrix == second_matrix);
}

TEST(EqMatrix_suite, self_comparison_test) {
  S21Matrix first_matrix(3, 3);

  EXPECT_TRUE(first_matrix.EqMatrix(first_matrix));
}

TEST(EqMatrix_suite, empty_one_test) {
  S21Matrix first_matrix(3, 3);
  S21Matrix second_matrix;

  EXPECT_TRUE(!first_matrix.EqMatrix(second_matrix));
}

TEST(EqMatrix_suite, empty_two_test) {
  S21Matrix first_matrix;
  S21Matrix second_matrix;

  EXPECT_TRUE(first_matrix.EqMatrix(second_matrix));
}

TEST(SumMatrix_suite, true_test) {
  S21Matrix first_matrix(3, 3);
  S21Matrix second_matrix(3, 3);
  S21Matrix expected_result(3, 3);

  first_matrix.FillingMatrix();
  second_matrix.FillingMatrix();
  expected_result.FillingMatrix();
  first_matrix.SumMatrix(expected_result);
  second_matrix.SumMatrix(expected_result);

  EXPECT_TRUE(first_matrix.EqMatrix(second_matrix));
}

TEST(SumMatrix_suite, empty_test) {
  S21Matrix first_matrix;
  S21Matrix second_matrix;

  first_matrix.SumMatrix(second_matrix);

  EXPECT_TRUE(first_matrix.EqMatrix(second_matrix));
}

TEST(SumMatrix_suite, exceptional_test) {
  S21Matrix first_matrix(3, 3);
  S21Matrix second_matrix(3, 4);

  first_matrix.FillingMatrix();
  second_matrix.FillingMatrix();

  ASSERT_THROW(first_matrix.SumMatrix(second_matrix), std::out_of_range);
}

TEST(SubMatrix_suite, true_test) {
  S21Matrix first_matrix(3, 3);
  S21Matrix second_matrix(3, 3);
  S21Matrix expected_result(3, 3);

  first_matrix.FillingMatrix();
  second_matrix.FillingMatrix();
  expected_result.FillingMatrix();
  first_matrix.SubMatrix(expected_result);
  second_matrix.SubMatrix(expected_result);

  EXPECT_TRUE(first_matrix.EqMatrix(second_matrix));
}

TEST(SubMatrix_suite, empty_test) {
  S21Matrix first_matrix;
  S21Matrix second_matrix;

  first_matrix.SubMatrix(second_matrix);

  EXPECT_TRUE(first_matrix.EqMatrix(second_matrix));
}

TEST(SubMatrix_suite, exceptional_test) {
  S21Matrix first_matrix(3, 3);
  S21Matrix second_matrix(3, 4);

  first_matrix.FillingMatrix();
  second_matrix.FillingMatrix();

  ASSERT_THROW(first_matrix.SubMatrix(second_matrix), std::out_of_range);
}

TEST(MulNumber_suite, true_test) {
  S21Matrix first_matrix(3, 3);
  S21Matrix second_matrix(3, 3);

  first_matrix.FillingMatrix();
  second_matrix.FillingMatrix();
  for (int i = 0; i < 4; ++i) {
    second_matrix.SumMatrix(first_matrix);
  }
  first_matrix.MulNumber(5);

  EXPECT_TRUE(first_matrix.EqMatrix(second_matrix));
}

TEST(MulNumber_suite, empty_test) {
  S21Matrix first_matrix;
  S21Matrix second_matrix;

  first_matrix.MulNumber(5);

  EXPECT_TRUE(first_matrix.EqMatrix(second_matrix));
}

TEST(MulMatrix_suite, empty_test) {
  S21Matrix first_matrix;
  S21Matrix second_matrix;

  ASSERT_THROW(first_matrix.MulMatrix(second_matrix), std::logic_error);
  EXPECT_TRUE(first_matrix.EqMatrix(second_matrix));
}

TEST(MulMatrix_suite, three_three_true_test) {
  S21Matrix first_matrix(3, 3);
  S21Matrix second_matrix(3, 3);
  S21Matrix expected_result(3, 3);

  first_matrix.FillingMatrix();
  second_matrix.FillingMatrix();
  expected_result(0, 0) = 15;
  expected_result(0, 1) = 18;
  expected_result(0, 2) = 21;
  expected_result(1, 0) = 42;
  expected_result(1, 1) = 54;
  expected_result(1, 2) = 66;
  expected_result(2, 0) = 69;
  expected_result(2, 1) = 90;
  expected_result(2, 2) = 111;
  first_matrix.MulMatrix(second_matrix);

  EXPECT_TRUE(first_matrix.EqMatrix(expected_result));
}

TEST(MulMatrix_suite, four_four_true_test) {
  S21Matrix first_matrix(4, 4);
  S21Matrix second_matrix(4, 4);
  S21Matrix expected_result(4, 4);

  first_matrix.FillingMatrix();
  second_matrix.FillingMatrix();
  expected_result(0, 0) = 56;
  expected_result(0, 1) = 62;
  expected_result(0, 2) = 68;
  expected_result(0, 3) = 74;
  expected_result(1, 0) = 152;
  expected_result(1, 1) = 174;
  expected_result(1, 2) = 196;
  expected_result(1, 3) = 218;
  expected_result(2, 0) = 248;
  expected_result(2, 1) = 286;
  expected_result(2, 2) = 324;
  expected_result(2, 3) = 362;
  expected_result(3, 0) = 344;
  expected_result(3, 1) = 398;
  expected_result(3, 2) = 452;
  expected_result(3, 3) = 506;
  first_matrix.MulMatrix(second_matrix);

  EXPECT_TRUE(first_matrix.EqMatrix(expected_result));
}

TEST(MulMatrix_suite, five_two_true_test) {
  S21Matrix first_matrix(2, 5);
  S21Matrix second_matrix(5, 2);
  S21Matrix expected_result(2, 2);

  first_matrix.FillingMatrix();
  second_matrix.FillingMatrix();
  expected_result(0, 0) = 60;
  expected_result(0, 1) = 70;
  expected_result(1, 0) = 160;
  expected_result(1, 1) = 195;
  first_matrix.MulMatrix(second_matrix);

  EXPECT_TRUE(first_matrix.EqMatrix(expected_result));
}

TEST(MulMatrix_suite, exceptional_test) {
  S21Matrix first_matrix(3, 3);
  S21Matrix second_matrix(2, 3);

  first_matrix.FillingMatrix();
  second_matrix.FillingMatrix();

  ASSERT_THROW(first_matrix.MulMatrix(second_matrix), std::logic_error);
}

TEST(Transpose_matrix_suite, true_test) {
  S21Matrix first_matrix(2, 3);
  S21Matrix expected_result(3, 2);

  first_matrix.FillingMatrix();
  first_matrix = first_matrix.Transpose();
  expected_result(0, 0) = 0;
  expected_result(0, 1) = 3;
  expected_result(1, 0) = 1;
  expected_result(1, 1) = 4;
  expected_result(2, 0) = 2;
  expected_result(2, 1) = 5;

  EXPECT_TRUE(first_matrix.EqMatrix(expected_result));
}

TEST(CalcComplement_suite, four_four_test) {
  S21Matrix first_matrix(4, 4);
  S21Matrix expected_result(4, 4);

  first_matrix.FillingMatrix();
  first_matrix(0, 0) = 50;
  first_matrix = first_matrix.CalcComplements();
  expected_result(0, 0) = 0.000000;
  expected_result(0, 1) = 0.000000;
  expected_result(0, 2) = 0.000000;
  expected_result(0, 3) = 0.000000;
  expected_result(1, 0) = 0.000000;
  expected_result(1, 1) = -200.000000;
  expected_result(1, 2) = 400.000000;
  expected_result(1, 3) = -200.000000;
  expected_result(2, 0) = 0.000000;
  expected_result(2, 1) = 400.000000;
  expected_result(2, 2) = -800.000000;
  expected_result(2, 3) = 400.000000;
  expected_result(3, 0) = 0.000000;
  expected_result(3, 1) = -200.000000;
  expected_result(3, 2) = 400.000000;
  expected_result(3, 3) = -200.000000;

  EXPECT_TRUE(first_matrix.EqMatrix(expected_result));
}

TEST(CalcComplement_suite, three_three_test) {
  S21Matrix first_matrix(3, 3);
  S21Matrix expected_result(3, 3);

  first_matrix.FillingMatrix();
  first_matrix = first_matrix.CalcComplements();
  expected_result(0, 0) = -3.000000;
  expected_result(0, 1) = 6.000000;
  expected_result(0, 2) = -3.000000;
  expected_result(1, 0) = 6.000000;
  expected_result(1, 1) = -12.000000;
  expected_result(1, 2) = 6.000000;
  expected_result(2, 0) = -3.000000;
  expected_result(2, 1) = 6.000000;
  expected_result(2, 2) = -3.000000;

  EXPECT_TRUE(first_matrix.EqMatrix(expected_result));
}

TEST(CalcComplement_suite, exceptional_test) {
  S21Matrix first_matrix(3, 4);

  first_matrix.FillingMatrix();
  ASSERT_THROW(first_matrix.CalcComplements(), std::logic_error);
}

TEST(Determinant_suite, three_three_test) {
  S21Matrix first_matrix(3, 3);
  S21Matrix second_matrix(3, 3);

  first_matrix.FillingMatrix();
  second_matrix.FillingMatrix();
  second_matrix(2, 2) = 56;
  S21Matrix expected_result(second_matrix);
  expected_result(0, 0) = 1000;

  EXPECT_TRUE(first_matrix.Determinant() == 0);
  EXPECT_TRUE(second_matrix.Determinant() == -144);
  EXPECT_TRUE(expected_result.Determinant() == 188856);
}

TEST(Determinant_suite, one_one_test) {
  S21Matrix first_matrix(1, 1);

  first_matrix(0, 0) = 1;

  EXPECT_TRUE(first_matrix.Determinant() == 1);
}

TEST(Determinant_suite, four_four_test) {
  S21Matrix first_matrix(4, 4);
  S21Matrix second_matrix(4, 4);

  first_matrix.FillingMatrix();
  second_matrix.FillingMatrix();
  second_matrix(0, 0) = 100;
  second_matrix(3, 3) = 56;
  S21Matrix expected_result(second_matrix);
  expected_result(0, 0) = 1000;

  EXPECT_TRUE(first_matrix.Determinant() == 0);
  EXPECT_TRUE(second_matrix.Determinant() == -16400);
  EXPECT_TRUE(expected_result.Determinant() == -164000);
}

TEST(Determinant_suite, exceptional_test) {
  S21Matrix first_matrix(3, 4);

  first_matrix.FillingMatrix();

  ASSERT_THROW(first_matrix.Determinant(), std::logic_error);
}

TEST(InverseMatrix_suite, three_three_test) {
  S21Matrix first_matrix(3, 3);
  S21Matrix expected_result(3, 3);

  first_matrix.FillingMatrix();
  first_matrix(0, 0) = 50;
  first_matrix = first_matrix.InverseMatrix();
  expected_result(0, 0) = 0.02;
  expected_result(0, 1) = -0.04;
  expected_result(0, 2) = 0.02;
  expected_result(1, 0) = -0.04;
  expected_result(1, 1) = -2.5866667;
  expected_result(1, 2) = 1.6266667;
  expected_result(2, 0) = 0.02;
  expected_result(2, 1) = 2.2933333;
  expected_result(2, 2) = -1.3133333;

  EXPECT_TRUE(first_matrix.EqMatrix(expected_result));
}

TEST(InverseMatrix_suite, exceptional_test) {
  S21Matrix first_matrix(3, 3);

  first_matrix.FillingMatrix();

  ASSERT_THROW(first_matrix.InverseMatrix(), std::invalid_argument);
}

TEST(index_operator_suite, true_test) {
  S21Matrix first_matrix(3, 3);

  first_matrix.FillingMatrix();

  EXPECT_TRUE(first_matrix(0, 0) == 0);
  EXPECT_TRUE(first_matrix(0, 1) == 1);
  EXPECT_TRUE(first_matrix(0, 2) == 2);
  EXPECT_TRUE(first_matrix(1, 0) == 3);
  EXPECT_TRUE(first_matrix(1, 1) == 4);
  EXPECT_TRUE(first_matrix(1, 2) == 5);
  EXPECT_TRUE(first_matrix(2, 0) == 6);
  EXPECT_TRUE(first_matrix(2, 1) == 7);
  EXPECT_TRUE(first_matrix(2, 2) == 8);
}

TEST(index_operator_suite, exceptional_test) {
  S21Matrix first_matrix(3, 3);

  first_matrix.FillingMatrix();

  ASSERT_THROW(first_matrix(0, -1), std::out_of_range);
  ASSERT_THROW(first_matrix(-1, 0), std::out_of_range);
  ASSERT_THROW(first_matrix(-1, -1), std::out_of_range);
  ASSERT_THROW(first_matrix(10, 0), std::out_of_range);
  ASSERT_THROW(first_matrix(0, 10), std::out_of_range);
  ASSERT_THROW(first_matrix(10, 10), std::out_of_range);
}

TEST(SumMatrix_operator_suite, true_test) {
  S21Matrix first_matrix(3, 3);
  S21Matrix second_matrix(3, 3);
  S21Matrix expected_result(3, 3);

  first_matrix.FillingMatrix();
  second_matrix.FillingMatrix();
  expected_result.FillingMatrix();
  first_matrix = first_matrix + expected_result;
  second_matrix = second_matrix + expected_result;
  expected_result.MulNumber(2);

  EXPECT_TRUE(first_matrix == expected_result);
  EXPECT_TRUE(second_matrix == expected_result);

  first_matrix += expected_result;
  second_matrix += expected_result;
  expected_result.MulNumber(2);

  EXPECT_TRUE(first_matrix == expected_result);
  EXPECT_TRUE(second_matrix == expected_result);
}

TEST(SumMatrix_operator_suite, exceptional_test) {
  S21Matrix first_matrix(3, 3);
  S21Matrix second_matrix(3, 4);

  first_matrix.FillingMatrix();
  second_matrix.FillingMatrix();

  ASSERT_THROW(first_matrix += second_matrix, std::out_of_range);
  ASSERT_THROW(first_matrix = first_matrix + second_matrix, std::out_of_range);
}

TEST(SubMatrix_operator_suite, true_test) {
  S21Matrix first_matrix(3, 3);
  S21Matrix second_matrix(3, 3);
  S21Matrix expected_result(3, 3);

  first_matrix.FillingMatrix();
  second_matrix.FillingMatrix();
  expected_result.FillingMatrix();
  expected_result.MulNumber(2);
  first_matrix = first_matrix - expected_result;
  second_matrix = second_matrix - expected_result;
  expected_result.MulNumber(-0.5);

  EXPECT_TRUE(first_matrix == expected_result);
  EXPECT_TRUE(second_matrix == expected_result);

  first_matrix -= expected_result;
  second_matrix -= expected_result;
  expected_result.ZeroingMatrix();

  EXPECT_TRUE(first_matrix == expected_result);
  EXPECT_TRUE(second_matrix == expected_result);
}

TEST(SubMatrix_operator_suite, exceptional_test) {
  S21Matrix first_matrix(3, 3);
  S21Matrix second_matrix(3, 4);

  first_matrix.FillingMatrix();
  second_matrix.FillingMatrix();

  ASSERT_THROW(first_matrix -= second_matrix, std::out_of_range);
  ASSERT_THROW(first_matrix = first_matrix - second_matrix, std::out_of_range);
}

TEST(MulMatrix_operator_suite, four_four_true_test) {
  S21Matrix first_matrix(4, 4);
  S21Matrix second_matrix(4, 4);
  S21Matrix third_matrix(4, 4);
  S21Matrix expected_result(4, 4);

  first_matrix.FillingMatrix();
  second_matrix.FillingMatrix();
  third_matrix.FillingMatrix();
  expected_result(0, 0) = 56;
  expected_result(0, 1) = 62;
  expected_result(0, 2) = 68;
  expected_result(0, 3) = 74;
  expected_result(1, 0) = 152;
  expected_result(1, 1) = 174;
  expected_result(1, 2) = 196;
  expected_result(1, 3) = 218;
  expected_result(2, 0) = 248;
  expected_result(2, 1) = 286;
  expected_result(2, 2) = 324;
  expected_result(2, 3) = 362;
  expected_result(3, 0) = 344;
  expected_result(3, 1) = 398;
  expected_result(3, 2) = 452;
  expected_result(3, 3) = 506;
  first_matrix = first_matrix * second_matrix;
  second_matrix *= third_matrix;

  EXPECT_TRUE(first_matrix == expected_result);
  EXPECT_TRUE(second_matrix == expected_result);
}

TEST(MulMatrix_operator_suite, five_two_true_test) {
  S21Matrix first_matrix(2, 5);
  S21Matrix second_matrix(5, 2);
  S21Matrix third_matrix(2, 5);
  S21Matrix expected_result(2, 2);

  first_matrix.FillingMatrix();
  second_matrix.FillingMatrix();
  third_matrix.FillingMatrix();
  expected_result(0, 0) = 60;
  expected_result(0, 1) = 70;
  expected_result(1, 0) = 160;
  expected_result(1, 1) = 195;
  first_matrix = first_matrix * second_matrix;
  third_matrix *= second_matrix;

  EXPECT_TRUE(first_matrix == expected_result);
  EXPECT_TRUE(third_matrix == expected_result);
}

TEST(MulMatrix_operator_suite, exceptional_test) {
  S21Matrix first_matrix(3, 3);
  S21Matrix second_matrix(2, 3);

  first_matrix.FillingMatrix();
  second_matrix.FillingMatrix();

  ASSERT_THROW(first_matrix = first_matrix * second_matrix, std::logic_error);
  ASSERT_THROW(first_matrix *= second_matrix, std::logic_error);
}

TEST(MulNumber_operator_suite, num_test) {
  S21Matrix first_matrix(3, 3);
  S21Matrix second_matrix(3, 3);
  S21Matrix expected_result(3, 3);

  first_matrix.FillingMatrix();
  second_matrix.FillingMatrix();
  expected_result.FillingMatrix();
  for (int i = 0; i < 4; ++i) {
    expected_result.SumMatrix(first_matrix);
  }
  first_matrix = first_matrix * 5;
  second_matrix *= 5;

  EXPECT_TRUE(first_matrix.EqMatrix(expected_result));
  EXPECT_TRUE(second_matrix.EqMatrix(expected_result));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
