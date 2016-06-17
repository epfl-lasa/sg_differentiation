#include "sg_filter.h"
#include "math.h"


ScalarSavitzkyGolayFilter::ScalarSavitzkyGolayFilter(int order,int winlen, float sample_time): order_(order), winlen_(winlen), sample_time_(sample_time)
{
  n_added_ = 0;
  data_buffer_ = new float[winlen_];
  for(int i=0;i<winlen;i++)
    data_buffer_[i] = 0.0;
    A_.resize(winlen_, order_+1);
    for (int i=0; i<winlen_;i++){
        for(int j=0; j<order_+1; j++){
            A_(i,j) = pow((i-floor(winlen_/2)),j);
        }
    }
}

float ScalarSavitzkyGolayFilter::filter(float input, int diff_order)
{
  AddData(input);
  return GetOutput(0, diff_order);
}

void ScalarSavitzkyGolayFilter::AddData(float new_data)
{
  // fill the buffer with the first data point, better than nothing
  if(n_added_ == 0){
    for(int i=0;i<winlen_;i++)
      data_buffer_[i] = new_data;
  }
  // shift the buffer and add the latest point at the end
  else{
    memmove(&data_buffer_[0], &data_buffer_[1], (winlen_-1)*sizeof(float));
    data_buffer_[winlen_-1] = new_data;
    // memmove(&data_buffer_[1], &data_buffer_[0], (winlen_-1)*sizeof(float));
    // data_buffer_[0] = new_data;
  }
  n_added_++;
}

Eigen::VectorXf ScalarSavitzkyGolayFilter::FitCoeffs()
{
  // an Eigen vector "face" of the data_buffer
  Eigen::Map<Eigen::VectorXf> data_buffer_eigen(data_buffer_,winlen_);
  // least square fit the coeffecients
  Eigen::VectorXf coeffs = A_.fullPivHouseholderQr().solve(data_buffer_eigen);
  return coeffs;
}

float ScalarSavitzkyGolayFilter::GetOutput(float query_val, int diff_order)
{
  Eigen::VectorXf coeffs = FitCoeffs();
  coeffs = diff_poly_coeffs(coeffs, diff_order);
  Eigen::VectorXf query_vec(coeffs.size());
  for(int i=0;i<query_vec.size();i++)
    query_vec(i) = pow(query_val,i);
  float result = coeffs.dot(query_vec);
  if(diff_order>0){
    result *= 1/pow(sample_time_, diff_order);
  }
  // if(diff_order % 2)
  //   result *= -1.0;
  return result;
}

bool ScalarSavitzkyGolayFilter::IsInitialized()
{
    if(n_added_ >= winlen_)
        return true;
    else
        return false;
}
