#include <thread>
using namespace std;

/** You may add additional functions as needed in this file. */

/** Write your sequential computation here. */
void sequential_increment(volatile int *a, int size, int k) {
   for(int i = 0; i < size; i++) {
      for(int j = 0; j < k; j++) {
            a[i]++;
      }
   }
}

void round_robin(volatile int *a, int size , int tid,int k, int num_threads) {
    for(int i = tid; i < size; i+=num_threads) {
      for(int j = 0; j < k; j++) {
            a[i]++;
      }
    }
}

/** Write your round robin computation here.*/
void round_robin_increment(volatile int *b, int size, int k, int num_threads) {
    //number of threads = (k) x ((size - (i % numthreads)/numthreads))
    thread thread_arr[num_threads];
    for(int i=0;i<num_threads;i++){
      thread_arr[i] = thread(round_robin, b, size, (i%num_threads), k, num_threads);
    }
    for(int j=0;j<num_threads;j++){
      thread_arr[j].join();
    }
}

void increment(volatile int *a, int index, int k ){
      for(int j = 0; j < k; j++) {
            a[index]++;
      }
}

void custom(volatile int *a, int size , int k, int index, int num_threads) {
    int unroll = (size % num_threads == 0) ? size/num_threads : (size/num_threads) + 1;
      for(int j=0; j<unroll;j++){
          if(index+j<size)
            increment(a, index+j, k);
      }
}

void custom_increment(volatile int *c, int size, int k, int num_threads) {
      thread thread_arr[num_threads];
      int unroll = (size % num_threads == 0) ? size/num_threads : (size/num_threads) + 1;
      int savedindex = 0;
      for(int i=0;i<num_threads;i++){
         thread_arr[i] = thread(custom, c, size, k, savedindex, num_threads);
         savedindex = savedindex + unroll;
      }
      for(int j=0;j<num_threads;j++){
         thread_arr[j].join();
      }
}
