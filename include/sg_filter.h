
#include <boost/circular_buffer.hpp>
#include <eigen3/Eigen/Dense>


class ScalarSavitzkyGolayFilter{
private:
  int winlen_;
  int order_;
  float * data_buffer_;
  int n_added_;
  float sample_time_;

  Eigen::MatrixXf A_;


  Eigen::VectorXf FitCoeffs();


public:
  ScalarSavitzkyGolayFilter(int order,int winlen, float sample_time);
  float GetOutput(float,int);
  void AddData(float new_data);
  float filter(float input, int n_differentiations);
  bool IsInitialized();
  Eigen::MatrixXf GetPolynomialMatrix(){
    return A_;
  };
  Eigen::Map<Eigen::VectorXf> GetData(){
    return Eigen::Map<Eigen::VectorXf>(data_buffer_,winlen_);
  }








};
inline  Eigen::VectorXf diff_poly_coeffs(Eigen::VectorXf coeffs,int n_diff){
  if(n_diff == 0)
    return coeffs;
  for(int i=0; i<coeffs.size(); i++)
    coeffs[i] = coeffs[i]*i;
  return diff_poly_coeffs(coeffs.tail(coeffs.size()-1), n_diff-1);
}
