#include <thread>
#if defined(SR)
#include "SRBarrier.h"
#elif defined(SRO)
#include "SROBarrier.h"
#else
#error "No barrier specified"
#endif
barrier_object B;
#include <vector>
#include <atomic>
#include <iostream>
using namespace std;


void repeated_blur_func(double *input, double *output, int start, int end, int tid, int repeats) {
    for (int r = 0; r < repeats; r++) {
        for (int i = start; i < end; i++) {
            output[i] = (input[i] + input[i + 1] + input[i - 1]) / 3;
        }
        double *tmp = input;
        input = output;
        output = tmp;
        B.barrier(tid);
    }
}

void repeated_blur(double *input, double *output, int size, int repeats, int num_threads) {
    std::thread threads[num_threads]; 
    B.init(num_threads);
    int chunk_size = (size) / num_threads; //11 / 10 = 1
    for(int t = 0; t < num_threads; t++) {
        int start = (t*chunk_size);
        int end = start + chunk_size; 
        if(end+chunk_size > size){
            end = size - 1;
        }
        if(start == 0){
            start = 1;
        }
        threads[t] = std::thread(repeated_blur_func, input, output, start, end, t, repeats);
    }
    for(int i=0;i<num_threads;i++){ 
        threads[i].join();
    }
}