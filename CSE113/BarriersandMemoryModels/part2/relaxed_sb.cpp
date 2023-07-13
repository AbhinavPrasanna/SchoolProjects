#define SRBARRIER // So that the header is not included twice in driver.cpp
#include "SRBarrier.h"
#include <atomic>

using namespace std;

void t0_function(atomic_int* x, atomic_int* y, int* r0, barrier_object* B) {
    x->store(1,memory_order_relaxed); 
    *r0 = y->load(memory_order_relaxed);
}

void t1_function(atomic_int* x, atomic_int* y, int* r1, barrier_object* B) {
    y->store(1,memory_order_relaxed);
    *r1 = x->load(memory_order_relaxed);
}

