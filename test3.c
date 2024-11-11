#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <stdbool.h>




#define MAX_FILES 10
#define MAX_THREADS 10

typedef struct 
{
    char filename[50];
    sem_t rw_mutex;
    sem_t mutex;
    int reader_count;
} FileResource;

FileResource files[MAX_FILES];
pthread_t readers[MAX_FILES][MAX_THREADS];
pthread_t writers[MAX_FILES][MAX_THREADS];

// Array to keep track of reader and writer thread indices for each file
int rptr[MAX_FILES] = { -1 };
int wptr[MAX_FILES] = { -1 };

// Reader thread function
void *reader(void *arg) {
    int file_index = *(int *)arg;
    FileResource *file = &files[file_index];

    sem_wait(&file->mutex);
    file->reader_count++;
    if (file->reader_count == 1) {
        sem_wait(&file->rw_mutex);
    }
    sem_post(&file->mutex);

    int fd = open(file->filename, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file for reading");
        return NULL;
    }

    printf("Reader %ld is reading the file %s:\n", pthread_self(), file->filename);
    char buffer[256];
    ssize_t bytes;
    //while ((bytes = read(fd, buffer, sizeof(buffer) - 1)) > 0) {
    ///    buffer[bytes] = '\0';
        //printf("%s", buffer);
    //}
    printf("\n");

    //system("python3 main.py");

    char command[256];
    sprintf(command, "python3 main.py file%d.txt 2", file_index+1);
    system(command);

    close(fd);

    sem_wait(&file->mutex);
    file->reader_count--;
    if (file->reader_count == 0) {
        sem_post(&file->rw_mutex);
    }
    sem_post(&file->mutex);

    return NULL;
}

// Writer thread function
void *writer(void *arg) 
{
    int file_index = *(int *)arg;
    FileResource *file = &files[file_index];

    sem_wait(&file->rw_mutex);

    int fd = open(file->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1) 
    {
        perror("Error opening file for writing");
        sem_post(&file->rw_mutex);
        return NULL;
    }

    printf("Writer %ld is writing to the file %s.\n", pthread_self(), file->filename);

    char command[256];
    sprintf(command, "python3 main.py file%d.txt 1", file_index+1);
    system(command);

 
    close(fd);

    sem_post(&file->rw_mutex);

    return NULL;
}

int main() 
{
    // Initialize file resources
    for (int i = 0; i < MAX_FILES; i++) 
    {
        snprintf(files[i].filename, sizeof(files[i].filename), "file%d.txt", i + 1);
        sem_init(&files[i].rw_mutex, 0, 1);
        sem_init(&files[i].mutex, 0, 1);
        files[i].reader_count = 0;
    }

    int file_index;
    bool file_manager = true;
    int choice;

    while (file_manager) 
    {
        printf("Enter the file index (0 to %d) and choice (0: Reader, 1: Writer, 2: Exit):\n", MAX_FILES - 1);
        scanf("%d %d", &file_index, &choice);

        if (file_index < 0 || file_index >= MAX_FILES) 
        {
            printf("Invalid file index.\n");
            continue;
        }

        switch (choice) 
        {
            case 0:
                pthread_create(&readers[file_index][++rptr[file_index]], NULL, reader, &file_index);
                break;
            case 1:
                pthread_create(&writers[file_index][++wptr[file_index]], NULL, writer, &file_index);
                break;
            case 2:
                
            case 3:
                file_manager = false;
                break;
            default:
                printf("Invalid choice.\n");
        }
    }

    for (int i = 0; i < MAX_FILES; i++) 
    {
        for (int j = 0; j <= rptr[i]; j++) 
        {
            pthread_join(readers[i][j], NULL);
        }
        for (int j = 0; j <= wptr[i]; j++) 
        {
            pthread_join(writers[i][j], NULL);
        }
    }

    for (int i = 0; i < MAX_FILES; i++) 
    {
        sem_destroy(&files[i].rw_mutex);
        sem_destroy(&files[i].mutex);
    }

    return 0;
}
