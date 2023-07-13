ScheduleType t = static_t;

#include<thread>

using namespace std;

void parallel_mult(float * result, int *mult, int size, int tid, int num_threads) {
  // write me in a SPMD parallel way!  partition the data using
  // "chunks" rather than strides.  That is thread 0 computes elements
  // 0 through size/num_threads.  thread 1 computes elements
  // size/num_threads through 2*(size/num_threads)

    int chunk_size = (size + (num_threads-1)) / num_threads;
    int start_index = tid * chunk_size;
    int end_index = 0;
    if(start_index + chunk_size < size){
      end_index = start_index + chunk_size;
    }
    else{
      end_index = size;
    }

  for (int i = start_index; i < end_index; i++) {
    float base = result[i];
    for (int w = 0; w < mult[i]-1; w++) {
      result[i] = result[i]+base;
    }
  }
}

void launch_threads(float* result_parallel, int* mult) {
  // Launch NUM_THREADS threads and then join them

     std::thread *thread_array = new std::thread[NUM_THREADS];
  for (int i = 0; i < NUM_THREADS; i++) {
    thread_array[i] = std::thread(parallel_mult, result_parallel, mult, SIZE, i, NUM_THREADS);
  }
  
  // Join the threads
  for (int i = 0; i < NUM_THREADS; i++) {
    thread_array[i].join();
  }
}