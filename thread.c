#include <pthread.h>
#include <stdio.h>

#define tick(time) (time)++

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int time_cnt = 0;
int turn = 0;

void *thread_a(void *arg) {
  for (int i = 0; i < 5; i++) {
    pthread_mutex_lock(&mutex);
    tick(time_cnt);
    while (turn) {
      printf("A: sleep  (i=%d)(time=%d)\n", i, time_cnt);
      pthread_cond_wait(&cond, &mutex);
    }

    printf("A: active (i=%d)(time=%d)\n", i, time_cnt);

    turn = 1;

    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);
  }
  return NULL;
}

void *thread_b(void *arg) {
  for (int i = 0; i < 5; i++) {
    pthread_mutex_lock(&mutex);
    tick(time_cnt);
    while (!turn) {
      printf("B: sleep  (i=%d)(time=%d)\n", i, time_cnt);
      pthread_cond_wait(&cond, &mutex);
    }

    printf("B: active (i=%d)(time=%d)\n", i, time_cnt);

    turn = 0;

    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);
  }
  return NULL;
}

int main() {
  pthread_t a, b;

  pthread_create(&a, NULL, thread_a, NULL);
  pthread_create(&b, NULL, thread_b, NULL);

  pthread_join(a, NULL);
  pthread_join(b, NULL);

  return 0;
}
