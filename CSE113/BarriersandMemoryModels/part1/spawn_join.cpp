#include <thread>
#include <vector>
#include <atomic>
#include <iostream>
using namespace std;

void repeated_blur_func(double *input, double *output, int start, int end) {
      for (int i = start;i < end; i++) {
         output[i] = (input[i] + input[i+1] + input[i-1])/3;
      }
}
void repeated_blur(double *input, double *output, int size, int repeats, int num_threads) {
    int chunk_size = (size) / num_threads; //11 / 10 = 1
    int remainder = (size) % num_threads; //1 
    for(int i = 0; i<repeats; i++){
        std::thread *threads = new std::thread[num_threads];
        for (int t = 0; t < num_threads; t++) {
            int start = (t*chunk_size);
            int end = start + chunk_size; 
            if(end+chunk_size > size){
                //start = end;
                end = size - 1;
            }
            if(start == 0){
                start = 1;
            }
            threads[t] = std::thread(repeated_blur_func, input, output, start,end);
        }
        for (int i = 0; i < num_threads; i++) {
            threads[i].join();
        }
        double *tmp = input;
        input = output;
        output = tmp;   
    }
}
