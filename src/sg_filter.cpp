#include "sg_filter.h"
#include "math.h"


ScalarSavitzkyGolayFilter::ScalarSavitzkyGolayFilter(int order,int winlen): order_(order), winlen_(winlen)
{
  data_buffer_ = new float[winlen_];
  for(int i=0;i<winlen;i++)
    data_buffer_[i] = 0.0;
    n_added_ = 0;
    A_.resize(winlen_, order_+1);
    for (int i=0; i<winlen_;i++){
        for(int j=0; j<order_+1; j++){
            A_(i,j) = pow((i-floor(winlen_/2)),j);
        }
    }
}

Eigen::VectorXf ScalarSavitzkyGolayFilter::filter(Eigen::VectorXf input, int diff_order)
{
}

void ScalarSavitzkyGolayFilter::AddData(float new_data)
{
  if(n_added_ == 0){
    for(int i=0;i<winlen_;i++)
      data_buffer_[i] = new_data;
  }
  else{
    memmove(&data_buffer_[0], &data_buffer_[1], (winlen_-1)*sizeof(float));
    data_buffer_[winlen_-1] = new_data;
  }
  n_added_++;
}

void ScalarSavitzkyGolayFilter::FitCoeffs()
{
}

float ScalarSavitzkyGolayFilter::GetOutput(float query_val, int diff_order)
{
  Eigen::Map<Eigen::VectorXf> data_buffer_eigen(data_buffer_,winlen_);
  Eigen::VectorXf coeffs = A_.fullPivHouseholderQr().solve(data_buffer_eigen);
  coeffs = diff_poly_coeffs(coeffs, diff_order);
  Eigen::VectorXf query_vec(coeffs.size());
  for(int i=0;i<query_vec.size();i++)
    query_vec(i) = pow(query_val,i);
  return coeffs.dot(query_vec);
}

bool ScalarSavitzkyGolayFilter::IsInitialized()
{
    if(n_added_ >= winlen_)
        return true;
    else
        return false;
}
