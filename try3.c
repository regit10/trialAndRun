#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>


sem_t even_lock, odd_lock;

void *even_thread(void *args)
{
  int i = 0;
  while (i < 100)
  {

    sem_wait(&even_lock);
    sleep(1);
    printf("%d\n", i);
    i += 2;
    sem_post(&odd_lock);
  }
  pthread_exit(0);
}

void *odd_thread(void *args)
{
  int i = 1;
  while (i < 100)
  {
    sem_wait(&odd_lock);
    sleep(1);
    printf("%d\n", i);
    i += 2;
    sem_post(&even_lock);
  }
  pthread_exit(0);
}

int main()
{

  pthread_t thread[2];
  sem_open(&even_lock, 0, 1);
  sem_open(&odd_lock, 0, 0);

  printf("Solution\n");
  pthread_create(&thread[0], NULL, even_thread, NULL);
  pthread_create(&thread[1], NULL, odd_thread, NULL);
  pthread_join(thread[0], NULL);
  pthread_join(thread[1], NULL);
  sem_close(&even_lock);
  sem_close(&odd_lock);
  return 0;
}