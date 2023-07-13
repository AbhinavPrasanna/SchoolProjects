#include <atomic>

ScheduleType t = global_t;

std::atomic_int counter(0);

void parallel_mult(float * result, int *mult, int size, int tid, int num_threads) {
  // Write me a parallel way using the global counter
  // as an implicit worklist. That is, every thread
  // should get its index from increment(ing the counter
  int chunk_size = (size + (num_threads-1)) / num_threads;
  int start_index = tid * chunk_size;
  int end_index = 0;
    if(start_index + chunk_size > size){
      end_index = start_index + chunk_size;
    }
    else{
      end_index = size;
    }

  for(int local_index = atomic_fetch_add(&counter, 1); local_index < size; local_index = atomic_fetch_add(&counter, 1)){
      float base = result[local_index];
    for (int w = 0; w < mult[local_index]-1; w++) {
      result[local_index] = result[local_index]+base;
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