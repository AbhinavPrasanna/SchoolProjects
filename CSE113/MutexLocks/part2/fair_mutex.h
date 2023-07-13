#pragma once

#include <atomic>
#include <mutex>
#include <condition_variable>
using namespace std;

class rw_mutex {
 public:
  rw_mutex() : readers_count(0), writers_waiting(0), writer_active(false) {
  }

  void lock_reader() {
    unique_lock<mutex> lock(mtx);
    while (1) {
      if(writers_waiting > 0){
        cv.wait(lock);
      }
      else if(writer_active){
        cv.wait(lock);
      }
      else{
        break;
      }
    }
    readers_count++;
  }
  
  void unlock_reader() {
    unique_lock<mutex> lock(mtx);
    readers_count--;
    if (readers_count == 0) {
      cv.notify_all();
    }
  }

  
  void lock() {
    unique_lock<mutex> lock(mtx);
    writers_waiting++;
    while (1) {
      if(readers_count > 0){
        cv.wait(lock);
      }
      else if(writer_active){
        cv.wait(lock);
      }
      else{
        break;
      }
    }
    writer_active = true;
    writers_waiting--;
  }
  
  void unlock() {
    unique_lock<mutex> lock(mtx);
    writer_active = false;
    cv.notify_all();
  }

 private:
  atomic<int> readers_count;
  atomic<int> writers_waiting;
  atomic<bool> writer_active;
  mutex mtx;
  condition_variable cv;
};
