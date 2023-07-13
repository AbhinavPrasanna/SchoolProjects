#include <atomic>

class barrier_object {
 public:
  barrier_object() {
  }

  void init(int num_threads) {
    counter.store(0);
    this->num_threads = num_threads;
    sense.store(false);
    thread_sense = new bool[num_threads];
    for(int i = 0;i<num_threads;i++)
      thread_sense[i] = true;
  }

  void barrier(int tid) {
    int arrivalnumber = atomic_fetch_add(&counter, 1);
    if(arrivalnumber == num_threads - 1){
      counter.store(0);
      sense.store((thread_sense[tid]));
    } else {
      while(sense.load() != thread_sense[tid]){
        
      }
    }
    thread_sense[tid] = !thread_sense[tid];
  }

private:
  std::atomic<int> counter;
  int num_threads;
  std::atomic<bool> sense;
  bool *thread_sense;
};
