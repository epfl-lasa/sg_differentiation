#include <iostream>
#include "sg_filter.h"
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace SGF;

template<typename T>
void load_matrix(const char *fname, T &target) {

  std::ifstream myfile(fname);
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


int main(int argc, char *argv[]){
    int order = 2;
    int winlen = 21;
    float sample_time = 1e-3;
    int dim = 200;
    SGF::Vec inp(dim), inp1(1), inp2(1);

    load_matrix("./data/test_data_1_inp.txt", inp1);
    load_matrix("./data/test_data_2_inp.txt", inp2);

    printf ("****200-d Test****\n");

    for(int i=0; i<inp1.size(); i++){
            inp << inp1(i), inp2(i), inp1(i), inp2(i),inp1(i), inp2(i),inp1(i), inp2(i),inp1(i), inp2(i),inp1(i), inp2(i), inp1(i), inp2(i),inp1(i), inp2(i),inp1(i), inp2(i),inp1(i), inp2(i),inp1(i), inp2(i), inp1(i), inp2(i),inp1(i), inp2(i),inp1(i), inp2(i),inp1(i), inp2(i),inp1(i), inp2(i), inp1(i), inp2(i),inp1(i), inp2(i),inp1(i), inp2(i),inp1(i), inp2(i),inp1(i), inp2(i), inp1(i), inp2(i),inp1(i), inp2(i),inp1(i), inp2(i),inp1(i), inp2(i), inp1(i), inp2(i), inp1(i), inp2(i),inp1(i), inp2(i),inp1(i), inp2(i),inp1(i), inp2(i),inp1(i), inp2(i), inp1(i), inp2(i),inp1(i), inp2(i),inp1(i), inp2(i),inp1(i), inp2(i),inp1(i), inp2(i), inp1(i), inp2(i),inp1(i), inp2(i),inp1(i), inp2(i),inp1(i), inp2(i),inp1(i), inp2(i), inp1(i), inp2(i),inp1(i), inp2(i),inp1(i), inp2(i),inp1(i), inp2(i),inp1(i), inp2(i), inp1(i), inp2(i),inp1(i), inp2(i),inp1(i), inp2(i),inp1(i), inp2(i),
                    inp1(i), inp2(i), inp1(i), inp2(i),inp1(i), inp2(i),inp1(i), inp2(i),inp1(i), inp2(i),inp1(i), inp2(i), inp1(i), inp2(i),inp1(i), inp2(i),inp1(i), inp2(i),inp1(i), inp2(i),inp1(i), inp2(i), inp1(i), inp2(i),inp1(i), inp2(i),inp1(i), inp2(i),inp1(i), inp2(i),inp1(i), inp2(i), inp1(i), inp2(i),inp1(i), inp2(i),inp1(i), inp2(i),inp1(i), inp2(i),inp1(i), inp2(i), inp1(i), inp2(i),inp1(i), inp2(i),inp1(i), inp2(i),inp1(i), inp2(i), inp1(i), inp2(i), inp1(i), inp2(i),inp1(i), inp2(i),inp1(i), inp2(i),inp1(i), inp2(i),inp1(i), inp2(i), inp1(i), inp2(i),inp1(i), inp2(i),inp1(i), inp2(i),inp1(i), inp2(i),inp1(i), inp2(i), inp1(i), inp2(i),inp1(i), inp2(i),inp1(i), inp2(i),inp1(i), inp2(i),inp1(i), inp2(i), inp1(i), inp2(i),inp1(i), inp2(i),inp1(i), inp2(i),inp1(i), inp2(i),inp1(i), inp2(i), inp1(i), inp2(i),inp1(i), inp2(i),inp1(i), inp2(i),inp1(i), inp2(i);
    }

    SGF::SavitzkyGolayFilter filter(dim, order, winlen, sample_time);

    clock_t t;
    t = clock();
    {

        clock_t t_add;
        t_add = clock();
        filter.AddData(inp);
        t_add = clock() - t_add;
        printf ("filter.AddData: %f seconds.\n",((float)t_add)/CLOCKS_PER_SEC);

        clock_t t_get;
        t_get = clock();
        filter.GetOutput(0, inp);
        t_get = clock() - t_get;
        printf ("filter.GetOutput 0: %f seconds.\n",((float)t_get)/CLOCKS_PER_SEC);


        clock_t t_get1;
        t_get1 = clock();
        filter.GetOutput(1, inp);
        t_get1 = clock() - t_get1;
        printf ("filter.GetOutput 1: %f seconds.\n",((float)t_get1)/CLOCKS_PER_SEC);

    }
    t = clock() - t;
    printf ("Total: %f seconds.\n",((float)t)/CLOCKS_PER_SEC);

}


