# Savitzky-Golay smoothing and differentiation
A package implementing Savitzky-Golay smoothing and differentiation. May be useful to estimate e.g. velocity and acceleration from position measurements.

## Documentation
You can use doxygen to get some source code documentation which you may find useful when using the library. 

First install dixygen if you don't have it, then navigate to the sg_differentiation folder and run
```
doxygen Doxyfile
```

This will produce html files documenting the code. Open doc/html/index.html to browse them. 

## Usage
A minimalist cpp program using the filter could look like:

```c++
#include "eigen3/Eigen/Dense"
#include "sg_filter.h"

int main(int argc, char* argv[]){
  // for scalar data:
  int order = 2;
  int winlen = 11;
  float sample_time = 1e-3;
  ScalarSavitzkyGolayFilter filter(order, winlen, sample_time);
  // add some data
  float new_data = GetYourSensorData() //put your raw data
  filter.AddData(new_data);
  // to get output:
  float output;
  int ret_code;
  ret_code = filter.GetOutput(0, output); // the 0 means we dont want differntiation. Put 1 to differentiate once, etc
  // ret_code will be -1 until at least winlen data points have been added, then it will be 0
  
  
  // multidim case
  int dim = 2;
  SavitzkyGolayFilter filter(dim, order, winlen, sample_time);
  Eigen::VectorXf inp(dim);
  inp = GetYourSensorData();
  ret_code = filter.AddData(inp);
  // ret_code will be -2 if you try tp add data of wrong size
  
  Eigen::VectorXf outp(dim);
  ret_code = filter.GetOutput(0, outp);
  // ret_code will be -1 until at least winlen data points have been added, then it will be 0
   
}


```
