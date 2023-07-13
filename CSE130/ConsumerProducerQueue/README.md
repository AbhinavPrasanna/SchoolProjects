#Assignment 3 directory

This directory contains source code and other files for Assignment 3.

Use this README document to store notes about design, testing, and
questions you have while developing your assignment.

queue_t *queue_new(int size):
    Initializes a new multi-threaded Producer and Consumer Queue Structure to size passed by the user. The queue data structure contains the size(s), head(h), tail(t), amount of items in the queue(cnt), and a buffer(buf) which are initialized in our queue_new method. The queue new method initializes the mutex we are using for this assignment, a condition for if the queue is full and if the queue is method which is used later in the assigmment.


void queue_delete(queue_t **q):
      Queue Delete acts as a destructor and destroys the mutex for our assignment along with the not full condition and not empty condition. We free the memory of the buffer used for our queue and the queue object itself to create the destructor.

bool queue_push(queue_t *q, void *elem):
    Queue Push is creating a method to push to the multithreaded producer and consumer queue structure. We are using mutexes in conjunction with threads to prevent collisions for our producer and consumer queue. We initially lock the mutex before we push the element into our queue. The void pointer element refers to any data type for the element we push in the queue. While the count of the queue doesn't equal the size of the queue, our not full condition will wait with the mutex until the count equals the size. We set the tail of the queue to the element, increment the tail, and change the signal for queue not empty. Finally, the mutex is unlocked and we return true since we are able to pop to the mutex.
}

bool queue_pop(queue_t *q, void **elem):
    Queue Pop is creating a method to pop to the multithreaded producer and consumer queue structure. We are using mutexes in conjunction with threads to prevent collisions for our producer and consumer queue. We initially lock the mutex before we pop the element into our queue.While the queue is not empty , our not empty condition will wait with the mutex until the queue is empty. We set the void pointer element of any data type and we set the element equal top the buffer which is our queue at the head. We increment the head and decrease the count of the queue. The Not Full condition is signaled after the pop operation is succeeded and unlock the mutex.
