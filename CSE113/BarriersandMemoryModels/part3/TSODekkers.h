#include <atomic>

// this should be the same as RDekkers with the change that every
// relaxed access should be memory_order_relaxed.
// your job is to use the following MACRO to fix the mutex.
// Think about the reorderings allowed under TSO and where the fence
// needs to be placed.

#define FENCE asm volatile("mfence":::"memory");

class dekkers_mutex {
public:
  dekkers_mutex() {
    wantstoenter[0].store(false,std::memory_order_relaxed);
    wantstoenter[1].store(false,std::memory_order_relaxed);
    turn.store(0);
  }

  void lock(int tid) {
    // implement me!
    wantstoenter[tid].store(true,std::memory_order_relaxed);
    FENCE
    while (wantstoenter[1-tid].load() == true) {
      if (turn.load() != tid) {
        wantstoenter[tid].store(false,std::memory_order_relaxed);
        FENCE
        while (turn.load(std::memory_order_relaxed) != tid) {
          // spin
        }
        wantstoenter[tid].store(true,std::memory_order_relaxed);
        FENCE
      }
    }
  }

  void unlock(int tid) {
    // implement me!
    turn.store(1-tid,std::memory_order_relaxed);
    FENCE
    wantstoenter[tid].store(false);
  }

private:
  std::atomic<bool> wantstoenter[2];
  std::atomic<int> turn;
};
