#include <atomic>
#include "IOQueue.h"
ScheduleType t = local_32_t;


IOQueue Q[NUM_THREADS];
std::atomic_int finished_threads(0);

void parallel_enq(int size, int tid, int num_threads) {
  // Use this function to equeue indexes to each of the local
  // workstealing queues

  // Hint: this should be the same as in main3.cpp
   int chunk_size = (size + (num_threads -1))/num_threads; 
  int start = chunk_size * tid;
  int end = 0;
    if(start + chunk_size > size){
      end = start + chunk_size;
    }
    else{
      end = size;
    }
  for (int x = start; x < end; x++) {
      Q[tid].enq(x);
  }
}

void parallel_mult(float * result, int *mult, int size, int tid, int num_threads) {
  // Implement me using a workstealing approach.
  // You should use the Q IOQueues to compute
  // local work and then try to steal work
  // from others until all the work is completed

  // Unlike in part3_local.h, you should deq 32 elements
  // at a time.
  // Implement me using a workstealing approach.
  // You should use the Q IOQueues to compute
  // local work and then try to steal work
  // from others until all the work is completed
  int elements[32];
  for (int i = Q[tid].deq(); i != -1; i = Q[tid].deq()) {
    float base = result[i];
    for (int w = 0; w < mult[i] - 1; w++) {
      result[i] = result[i] + base;
    }
  }

  atomic_fetch_add(&finished_threads, 1);
  while (finished_threads.load() != num_threads) {
    int target = (tid+1) % num_threads;
    int task = Q[target].deq_32(elements);
    if (task != -1) {
      for(int x=0;x<32;x++){
      float base = result[task];
        for (int w = 0; w < mult[task] - 1; w++) {
          result[task] = result[task] + base;
        }
      }
    }
  }
}

void launch_threads(float* result_parallel, int* mult) {
  // Launch NUM_THREADS threads to intialize the IOQueues in Q with
  // the indexes for each thread. Remember to initialize the Queues
  // with the size that they will need. Join the threads afterwards.

  // Next, launch the parallel function that performs the parallel_mult
  // function from part1_static.h and part2_global.h but using workstealing

  // hint: this part should be the same as in part3_local.h
   std::thread *thread_array = new std::thread[NUM_THREADS];
  for (int i = 0; i < NUM_THREADS; i++) {
    thread_array[i] = std::thread(parallel_mult, result_parallel, mult, SIZE, i, NUM_THREADS);
  }
  
  // Join the threads
  for (int i = 0; i < NUM_THREADS; i++) {
    thread_array[i].join();
  }
}