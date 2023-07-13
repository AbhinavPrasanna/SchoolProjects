#pragma once

#include <atomic>
#include <thread>

class mutex {
 public:
  mutex() {
    
  }
  
  void init (int num_threads) {
    this->thread_count = num_threads;
    level = new std::atomic<int>[num_threads];
    flag = new std::atomic<bool>[num_threads];
    for (int i = 0; i < num_threads; i++) {
      level[i].store(0);
      flag[i].store(false);
    }

  }
  
  void lock(int thread_id) {
    flag[thread_id] = true;
    int thread = -1;
    for(int i = 0; i < thread_count - 1; i++){
      int compared = level[i].load(); 
        if(thread < compared){
          thread = compared;
        }
    }
    thread++; 
    level[thread_id] = thread;
    for (int k = 0; k < thread_count; k++) {
      while(1){
        if(k!=thread_id){
          if(flag[k].load()){
             if(level[k].load() < level[thread_id].load() || level[k].load() == level[thread_id].load() && thread_id < k){
                std::this_thread::yield();
             }
             else{
                break;
             }
          }
          else{
            break;
          }
        }
        else{
          break;
        }
      }
    }
}
  
  void unlock(int thread_id) {
    flag[thread_id].store(false);
  }

 private:
  std::atomic<int> *level;
  std::atomic<bool> *flag;
  int thread_count;
};