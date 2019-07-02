#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#define THREAD_NUM 4
#define MAX_COUNT 100000
#define METHOD_ONE
void *thread_main(void *data);

#ifdef METHOD_ONE
typedef struct
{
    int id;
    int write_num;
    int *fd_in;
    int *fd_out;
    sem_t *sem_in;
    sem_t *sem_in_end;
    sem_t *sem_out;
    sem_t *sem_out_end;
    int max_count;
}thread_data;
int main(int argc, char *argv[])
{
    int i;
    thread_data data_list[THREAD_NUM];
    int fd_list[THREAD_NUM];
    sem_t *sem_list[THREAD_NUM];
    sem_t *sem_list2[THREAD_NUM];
    pthread_t tid_list[THREAD_NUM];
    char file_name[] = "file_X";
    char sem_name[] = "sem_X";
    char sem_name2[] = "sem2_X";
    for(i = 0; i < THREAD_NUM; ++i)
    {
        file_name[5] = 'A' + i;
        sem_name[4] = 'A' + i;
        sem_name2[5] = 'A' + i;
        fd_list[i] = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0666);
        sem_list[i] = sem_open(sem_name, O_CREAT|O_EXCL, S_IRWXU, 0);
        sem_list2[i] = sem_open(sem_name2, O_CREAT|O_EXCL, S_IRWXU, 1);
    }
    for(i = 0; i < sizeof(data_list)/sizeof(data_list[0]); ++i)
    {
        data_list[i].id = i + 1;
        data_list[i].write_num = i + 1;
        data_list[i].max_count = MAX_COUNT;
        data_list[i].fd_in = &fd_list[i];
        data_list[i].fd_out = &fd_list[(i + 1)%THREAD_NUM];
        data_list[i].sem_in = sem_list[i];
        data_list[i].sem_out = sem_list[(i + 1)%THREAD_NUM];
        data_list[i].sem_in_end = sem_list2[i];
        data_list[i].sem_out_end = sem_list2[(i + 1)%THREAD_NUM];
        pthread_create(&tid_list[i], NULL, thread_main, &data_list[i]);
    }
    for(i = 0; i < THREAD_NUM; ++i)
        pthread_join(tid_list[i], NULL);
    for(i = 0; i < THREAD_NUM; ++i)
        close(fd_list[i]);
    for(i = 0; i < THREAD_NUM; ++i)
    {
        sem_name[4] = 'A' + i;
        sem_name2[5] = 'A' + i;
        sem_unlink(sem_name);
        sem_close(sem_list[i]);
        sem_unlink(sem_name2);
        sem_close(sem_list2[i]);
    }
}

void *thread_main(void *data)
{
    thread_data *my_data = (thread_data*)data;
    char buf[8];
    sprintf(buf, "%d", my_data->write_num);
    int count = 0;
    int fd = 0;
    while(count < my_data->max_count)
    {
        sem_wait(my_data->sem_in_end);
        fd = *(my_data->fd_in);
        write(fd, buf, strlen(buf));
        sem_post(my_data->sem_in);
        sem_wait(my_data->sem_out);
        *(my_data->fd_out) = fd;
        sem_post(my_data->sem_out_end);
        ++count;
    }
    pthread_exit(NULL);
}
#else
typedef struct
{
    int id;
    int write_num;
    int fd_index;
    int *fd_list;
    pthread_mutex_t *lock;
    pthread_cond_t *condition;
    int *shared_counter;
    int max_count;
}thread_data;
int main(int argc, char *argv[])
{
    int i, counter = 0;
    int fd_list[THREAD_NUM];
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    thread_data data_list[THREAD_NUM];
    pthread_t tid_list[THREAD_NUM];
    char file_name[] = "file_X";
    mode_t mode = 0666;
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);
    for(i = 0; i < THREAD_NUM; ++i)
    {
        file_name[5] = 'A' + i;
        fd_list[i] = open(file_name, O_RDWR | O_CREAT | O_TRUNC, mode);
    }
    for(i = 0; i < sizeof(data_list)/sizeof(data_list[0]); ++i)
    {
        data_list[i].id = i + 1;
        data_list[i].write_num = i + 1;
        data_list[i].max_count = MAX_COUNT;
        data_list[i].fd_index = i;
        data_list[i].fd_list = fd_list;
        data_list[i].shared_counter = &counter;
        data_list[i].lock = &mutex;
        data_list[i].condition = &cond;
        pthread_create(&tid_list[i], NULL, thread_main, &data_list[i]);
    }
    for(i = 0; i < THREAD_NUM; ++i)
        pthread_join(tid_list[i], NULL);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    for(i = 0; i < THREAD_NUM; ++i)
        close(fd_list[i]);
}
void *thread_main(void *data)
{
    thread_data *my_data = (thread_data*)data;
    char buf[4];
    int count = 0, fd;
    sprintf(buf, "%d", my_data->write_num);
    while(count < my_data->max_count)
    {
        fd = my_data->fd_list[my_data->fd_index];
        my_data->fd_index = (my_data->fd_index + THREAD_NUM - 1) % THREAD_NUM;
        write(fd, buf, strlen(buf));
        ++count;
        pthread_mutex_lock(my_data->lock);
        my_data->shared_counter[0] = (my_data->shared_counter[0] + 1) % THREAD_NUM;
        if(my_data->shared_counter[0] == 0)
            pthread_cond_broadcast(my_data->condition);
        else
            pthread_cond_wait(my_data->condition, my_data->lock);
        pthread_mutex_unlock(my_data->lock);
    }
    pthread_exit(NULL);
}
#endif
