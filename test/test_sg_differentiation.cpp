#include "gtest/gtest.h"
#include <iostream>
#include "sg_filter.h"
#include <fstream>
#include <vector>
#include <string>
#include <sstream>


#define COMP_THRESHOLD 1e-6

template<typename t>
void debug_info(t p){
  std::cout<<p<<std::endl;
}

void load_matrix(const char *fname, Eigen::MatrixXf &target) {

  std::ifstream myfile(fname);
  ASSERT_TRUE(myfile);
  std::string line;
  float f;
  int n_rows=0;
  std::vector<float> v;
  while(getline(myfile,line)){
    ++n_rows;
    std::istringstream line_stream(line);
    while(!line_stream.eof()){
      line_stream>>f;
      v.push_back(f);
    }
  }
  int n_cols = v.size()/n_rows;
  target.resize(n_rows,n_cols);
  for(int i=0; i<n_rows;i++){
    for(int j=0;j<n_cols;j++){
      target(i,j) = v[i*n_cols + j];
    }
  }
}


template <typename R>
void assert_matrix_equal(const Eigen::Matrix<R,Eigen::Dynamic,Eigen::Dynamic>& m1, const Eigen::Matrix<R,Eigen::Dynamic,Eigen::Dynamic>& m2, double th){
  ASSERT_EQ(m1.rows(),m2.rows());
  ASSERT_EQ(m1.cols(),m2.cols());
  for (size_t row = 0; row < m1.rows(); ++row)
    {
      for (size_t col = 0; col < m1.cols(); ++col)
	{
	  ASSERT_NEAR(m1(row,col), m2(row,col),th);
	}
    }
}
template <typename T1,typename T2>
void assert_vector_equal(const T1 & m1, const T2& m2, double th){
  ASSERT_EQ(m1.rows(),m2.rows());
  ASSERT_EQ(m1.cols(),m2.cols());
  for (size_t row = 0; row < m1.rows(); ++row)
    {
      for (size_t col = 0; col < m1.cols(); ++col)
	{
	  ASSERT_NEAR(m1(row,col), m2(row,col),th);
	}
    }
}

TEST(CoefficientDifferentiatorTest, CoeffVectorLengthTest){
  Eigen::VectorXf b(4);
  ASSERT_EQ(diff_poly_coeffs(b,1).size(),3);
  ASSERT_EQ(diff_poly_coeffs(b,2).size(),2);
}

TEST(CoefficientDifferentiatorTest, CorrectDifferentiationTest){
  Eigen::VectorXf a(6);
  a << 1,1,1,1,1,1;
  Eigen::VectorXf b(5);
  b << 1,2,3,4,5;
  Eigen::VectorXf c(4);
  c << 2,6,12,20;
  assert_vector_equal(diff_poly_coeffs(a,1), b, COMP_THRESHOLD);
  assert_vector_equal(diff_poly_coeffs(a,2), c, COMP_THRESHOLD);
}

TEST(AddDataTest,test){
  int winlen = 3;
  ScalarSavitzkyGolayFilter filter(2,3);
  Eigen::VectorXf test_add(9);
  test_add << 1,2,3,4,5,6,7,8,9;

  for(int i=0;i<test_add.size();i++){
    filter.AddData(test_add[i]);

    if(i<winlen-1){
      ASSERT_FALSE(filter.IsInitialized());
    }else{
      ASSERT_TRUE(filter.IsInitialized());
    }
    if(filter.IsInitialized()){
      assert_vector_equal(filter.GetData(),test_add.segment(i-winlen+1,winlen), COMP_THRESHOLD);
    }
  }
  
}

TEST(ConstructorTest, 5_51){
  ScalarSavitzkyGolayFilter filter(5,51);
  Eigen::MatrixXf A;
  load_matrix("5_51_matrix.txt",A);
  assert_matrix_equal(A, filter.GetPolynomialMatrix(),COMP_THRESHOLD);
}

int main(int argc, char *argv[]){
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
