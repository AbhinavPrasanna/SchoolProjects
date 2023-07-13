#pragma once

#include <atomic>
#include <thread>

class mutex {
 public:
  mutex() {
    // Implement me!
  }
  
  void init(int num_threads) {
    // Implement me!
    this->thread_count = num_threads;
    level = new std::atomic<int>[num_threads];
    victim = new std::atomic<int>[num_threads];
    for (int i = 0; i < num_threads; i++) {
      level[i].store(0);
    }
  }
  
  void lock(int thread_id) {
    // Implement me!
    for (int i = 1; i < thread_count; i++) {
      level[thread_id].store(i);
      victim[i].store(thread_id);
      for (int k = 0; k < thread_count; k++) {
        while(1){
        if(k!=thread_id && level[k].load() >= i && victim[i].load() == thread_id){
          std::this_thread::yield();
        }
        else{
          break;
        }
      }

    }
    }
}
  
  void unlock(int thread_id) {
    // Implement me!
    level[thread_id].store(0);
  }

 private:
  // Give me some private variables!
  std::atomic<int> *level;
  std::atomic<int> *victim;
  int thread_count;
};
