#include <atomic>
#include <thread>

// this should be the same as SCDekkers with the change that every
// relaxed access should be memory_order_relaxed

class dekkers_mutex {
public:
  dekkers_mutex() {
    wantstoenter[0].store(false, std::memory_order_relaxed);
    wantstoenter[1].store(false, std::memory_order_relaxed);
    turn.store(0, std::memory_order_relaxed);
  }

  void lock(int tid) {
    wantstoenter[tid].store(true, std::memory_order_relaxed);
    while (wantstoenter[1-tid].load(std::memory_order_relaxed)) {
      if (turn.load(std::memory_order_relaxed) != tid) {
        wantstoenter[tid].store(false, std::memory_order_relaxed);
        while (turn.load(std::memory_order_relaxed) != tid) {
          std::this_thread::yield();
        }
        wantstoenter[tid].store(true, std::memory_order_relaxed);
      }
    }
  }

  void unlock(int tid) {
    turn.store(1-tid, std::memory_order_relaxed);
    wantstoenter[tid].store(false, std::memory_order_relaxed);
  }

private:
  std::atomic<bool> wantstoenter[2];
  std::atomic<int> turn;
};