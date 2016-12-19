#include <iostream>
#include "sg_filter.h"
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace SGF;


int main(int argc, char *argv[]){
    int order = 2;
    int winlen = 1;
    float sample_time = 1e-3;
    int dim = 200;
    int iters = 50;
    SGF::Vec inp(dim);


    SGF::SavitzkyGolayFilter filter(dim, order, winlen, sample_time);
    for (int j = 0 ; j < iters ; j++ )
    {

      printf ("****%d-d (Step %d) Test****\n",dim, j);  
      for(int i=0; i<dim; i++){
            inp(i) = (float) rand();  
      }

      int retcode;
      clock_t t;
      t = clock();
      {

          clock_t t_add;
          t_add = clock();
          retcode = filter.AddData(inp);
          t_add = clock() - t_add;
          if (retcode == 0){
            printf ("filter.AddData: %f seconds.\n",((float)t_add)/CLOCKS_PER_SEC);  
          }
          else if (retcode == -1){
           printf ("filter not initialized correctly :(.\n");   
          }
          

          clock_t t_get;
          t_get = clock();
          retcode = filter.GetOutput(0, inp);
          t_get = clock() - t_get;
          if (retcode == 0){
            printf ("filter.GetOutput 0: %f seconds.\n",((float)t_get)/CLOCKS_PER_SEC);
          }
          else if (retcode == -1){
           printf ("filter not initialized correctly :(.\n");   
          }

          clock_t t_get1;
          t_get1 = clock();
          retcode = filter.GetOutput(1, inp);
          t_get1 = clock() - t_get1;
          if (retcode == 0){
            printf ("filter.GetOutput 1: %f seconds.\n",((float)t_get1)/CLOCKS_PER_SEC);
          }        
          else if (retcode == -1){
           printf ("filter not initialized correctly :(.\n");   
          }

          clock_t t_get2;
          t_get2 = clock();
          retcode = filter.GetOutput(2, inp);
          t_get2 = clock() - t_get2;
          if (retcode == 0){
            printf ("filter.GetOutput 2: %f seconds.\n",((float)t_get2)/CLOCKS_PER_SEC);
          }        
          else if (retcode == -1){
           printf ("filter not initialized correctly :(.\n");   
          }
      }
      t = clock() - t;
      printf ("Total: %f seconds.\n",((float)t)/CLOCKS_PER_SEC);

  }


}    

