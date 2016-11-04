# Savitzky-Golay smoothing and differentiation
A package implementing Savitzky-Golay smoothing and differentiation. May be useful to estimate e.g. velocity and acceleration from position measurements.

## Documentation
You can use doxygen to get some source code documentation which you may find useful when using the library. 

First install dixygen if you don't have it, then navigate to the sg_differentiation folder and run
```
doxygen Doxyfile
```

This will produce html files documenting the code. Open doc/html/index.html to browse them. 

## Installation
To install the library and build testing script, run the following commands:

```c++
$ mkdir build && cd build
$ cmake ..
$ make
$ sudo make install
```
If you get the following problem:
```c++
Could NOT find GTest (missing: GTEST_LIBRARY GTEST_INCLUDE_DIR GTEST_MAIN_LIBRARY)
```
follow the steps in this link [GTEST CMAKE FIX](http://stackoverflow.com/questions/24295876/cmake-cannot-find-a-googletest-required-library). 

To test that everything is working accordingly, run the following commands:
```c++
cd ./test
./sg_differentiation-test
```

Once all tests are passed, it's safe to say that you can use this library in your own project, to include it, add the following lines to your CMakeLists.txt (assuming ```test-sg.cpp``` is where you want to use the library)
```
find_package (Eigen3 REQUIRED) 
include_directories(include ${SG_DIFFERENTATION_INCLUDE_DIRS})

add_executable(test-sg src/test-sg.cpp)
target_link_libraries(test-sg sg_differentiation)
```

## Usage
A minimalist cpp program using the filter could look like:

```c++
#include "eigen3/Eigen/Dense"
#include "sg_filter.h"

int main(int argc, char* argv[]){
  // for scalar data:
  int order = 2;
  int winlen = 11;
  SGF::real sample_time = 1e-3; // this is simply a float or double, you can change it in the header sg_filter.h if yo u want
  SGF::ScalarSavitzkyGolayFilter filter(order, winlen, sample_time);
  // add some data
  SGF::real new_data = GetYourSensorData() //put your raw data
  filter.AddData(new_data);
  // to get output:
  SGF::real output;
  int ret_code;
  ret_code = filter.GetOutput(0, output); // the 0 means we dont want differntiation. Put 1 to differentiate once, etc
  // ret_code will be -1 until at least winlen data points have been added, then it will be 0
  
  
  // multidim case
  int dim = 2;
  SGF::SavitzkyGolayFilter filter(dim, order, winlen, sample_time);
  SGF::Vec inp(dim); // SGF::Vec is the same as Eigen::Matrix<SGF::real, Eigen::Dynamic, 1>
  inp = GetYourSensorData();
  ret_code = filter.AddData(inp);
  // ret_code will be -2 if you try tp add data of wrong size
  
  SGF::Vec outp(dim);
  ret_code = filter.GetOutput(0, outp);
  // ret_code will be -1 until at least winlen data points have been added, then it will be 0
   
}


```
