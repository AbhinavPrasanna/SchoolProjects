#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

typedef struct queue {
    int s;
    int h;
    int t;
    int cnt;
    void **buf;
    pthread_mutex_t lk;
    pthread_cond_t n_full;
    pthread_cond_t n_empty;
} queue_t;

queue_t *queue_new(int size) {
    queue_t *q = malloc(sizeof(queue_t));
    if (q == NULL) {
        return NULL;
    }
    q->s = size;
    q->h = 0;
    q->t = 0;
    q->cnt = 0;
    q->buf = malloc(size * sizeof(void *));
    if (q->buf == NULL) {
        free(q);
        return NULL;
    }
    pthread_mutex_init(&q->lk, NULL);
    pthread_cond_init(&q->n_full, NULL);
    pthread_cond_init(&q->n_empty, NULL);
    return q;
}

void queue_delete(queue_t **q) {
    if (*q != NULL) {
        pthread_mutex_destroy(&(*q)->lk);
        pthread_cond_destroy(&(*q)->n_full);
        pthread_cond_destroy(&(*q)->n_empty);
        free((*q)->buf);
        free(*q);
        *q = NULL;
    }
}

bool queue_push(queue_t *q, void *elem) {
    pthread_mutex_lock(&q->lk);
    while (true) {
        if (q->cnt != q->s) {
            break;
        }
        pthread_cond_wait(&q->n_full, &q->lk);
    }
    q->buf[q->t] = elem;
    q->t = (q->t + 1) % q->s;
    q->cnt++;
    pthread_cond_signal(&q->n_empty);
    pthread_mutex_unlock(&q->lk);
    return true;
}

bool queue_pop(queue_t *q, void **elem) {
    pthread_mutex_lock(&q->lk);
    while (true) {
        if (q->cnt != 0) {
            break;
        }
        pthread_cond_wait(&q->n_empty, &q->lk);
    }
    *elem = q->buf[q->h];
    q->h = (q->h + 1) % q->s;
    q->cnt--;
    pthread_cond_signal(&q->n_full);
    pthread_mutex_unlock(&q->lk);
    return true;
}
