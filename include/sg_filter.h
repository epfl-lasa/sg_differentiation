
#include <boost/circular_buffer.hpp>
#include <eigen3/Eigen/Dense>
#include <vector>



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
  float GetOutput(float forward_param,int diff_order);
  float GetOutput(int diff_order);
  void AddData(float new_data);
  float filter(float input, int diff_order);
  bool IsInitialized();
  Eigen::MatrixXf GetPolynomialMatrix(){
    return A_;
  }

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



class SavitzkyGolayFilter{
private:
  std::vector<ScalarSavitzkyGolayFilter> scalar_filters_;
  int dim_;
public:
  SavitzkyGolayFilter(int dim, int order, int winlen, float sample_time);
  bool IsInitialized();
  void AddData(Eigen::VectorXf inp);
  Eigen::VectorXf GetOutput(int diff_order);
  Eigen::VectorXf GetOutput(float forward_param, int diff_order);
};

