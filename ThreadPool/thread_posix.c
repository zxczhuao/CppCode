/*
 * @Author: zxczhuao
 * @Date: 2023-04-29 12:25:00
 * @LastEditTime: 2023-04-29 13:16:31
 * @FilePath: /CppCode/ThreadPool/thread_posix.c
 * @Description: 
 * 
 */
#include <pthread.h>
#include <stdio.h>

void* func(void* arg){
    int i = *((int*)arg);
    int a = 10;
    printf("thread %d is runnging\n", i);
    printf("this thread id is %lu\n", pthread_self());
    pthread_exit(&a);
}

int main(){
    pthread_t id;
    int arg = 10;
    int ret = pthread_create(&id, NULL, func, (void*)&arg);
    if(ret != 0){
        printf("create thread error");
        return -1;
    }
    printf("Main thread id is %lu\n", pthread_self());
    printf("Main thread is waiting for thread %d\n", (int)id);
    pthread_t id_ret;
    int b;
    ret = pthread_join(id, (void*)b);
    if(ret != 0){
        printf("Join thread fail");
        return -1;
    }
    printf("Thread %d exited with val %d\n", (int)id, (int)b);
    return 0;
}
