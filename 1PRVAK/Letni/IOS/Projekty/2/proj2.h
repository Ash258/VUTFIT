#include <fcntl.h>
#include <limits.h>
#include <semaphore.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>

#ifndef IOS2_PROJ2_H
#define IOS2_PROJ2_H

//region Syntax sugar and variables
#ifdef NDEBUG
#define WRITE(type, id, text) {printf("%lu\t: %s %u  : %s\n", ++(*operation_number), (type), (id), (text));}
#else
#define WRITE(type, id, text) {fprintf(file_ptr, "%lu\t: %s %u  : %s\n", ++(*operation_number), (type), (id), (text));}
#endif //DNDEBUG

#define MOD 0666
#define MAX_WAIT_TIME 5000
#define EXIT_ERROR 2
#define TRUE 1 // Because I can. F*** lowercase defines.
#define FALSE 0 // Because I can. F*** lowercase defines.

#define START_TRAN sem_wait(lock);
#define END_TRAN sem_post(lock);

#define UNLOCK_SEM(sem) sem_post((sem));
#define LOCK_SEM(sem) sem_wait((sem));

#define MMAP(pointer) {(pointer) = mmap(NULL, sizeof(*(pointer)), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);}
#define UNMAP(pointer) {munmap((pointer), sizeof((pointer)));}
#define SLEEP(max){usleep(max == 0 ? 0 : (rand() % max) * 1000);}
#define WAIT(count) {for (unsigned long i = 0; i < count; ++i) waitpid(-1, NULL, 0);}
#define WRITE_SPECIAL(type, id, first, next) {fprintf(file_ptr, "%lu\t: %s %u  : waiting : %u : %u\n", ++(*operation_number), (type), (id), (first), (next)); fflush(file_ptr);}
/** Serial number of operation. */
unsigned long *operation_number;
/** File for writing. */
FILE *file_ptr;
sem_t *ch_enter, *a_leave, *lock, *barrier;
struct counter {
	/** How many children/adults are in center. */
	unsigned int center;
	/** How many children/adults are waiting to enter center. */
	unsigned int waiting;
} *adults, *children;

struct arguments {
	unsigned int A, /**< Number of "Adult" processes. A > 0. How many adults should enter to center. */
			C, /**< Number of "Child" processes. C > 0. How many children should enter to center. */
			AGT, /**< Maximum time (in milliseconds) after which is "adult" process generated. AGT >= 0 && AGT < 5001. */
			CGT, /**< Maximum time (in milliseconds) after which is "child" process generated. CGT >= 0 && CGT < 5001. */
			AWT, /**< How long (in milliseconds) should "adult" process simulate activity in center. AWT >= 0 && AWT < 5001. */
			CWT; /**< How long (in milliseconds) should "child" process simulate activity in center. CWT >= 0 && CWT < 5001. */
};
//endregion

/** @brief Print help for program running. */
void *usage();

/** @brief Initialize semaphores. */
bool init();

/**
 * @brief Handle system arguments.
 *
 * @param argc Arguments count.
 * @param argv Array of arguments.
 * @param args Structure where to save arguments.
 *
 * @return True on success.
 */
bool handle_arguments(int argc, char **argv, struct arguments *args);

/**
 * @brief Convert string to integer and check if result is between given min and max.
 *
 * @return True if conversion and validation was successfully completed.
 */
bool parse_int(char *source, unsigned int *dest, unsigned int min, unsigned int max);

/** @brief Release all semaphores and close file stream. */
void clean_up();

/**
 * @brief Generate given number of processes.
 *
 * @param count How many processes will be generated.
 * @param gen_delay Time (in milliseconds) after which is process generated.
 * @param type Child or adult?
 * @param max_work How long should process simulate activity in center.
 * @param perf Pointer to function, which will be executed.
 *
 * @see http://stackoverflow.com/q/26793402
 */
void gen_proc(unsigned int count, unsigned int gen_delay, char *type, unsigned int max_work,
			  void (perf)(unsigned int, unsigned int));

/**
 * @brief Wait until specific process stop or terminate.
 *
 * @param type Type of waiting precess.
 * @param id ID of waiting process.
 *
 * @see https://linux.die.net/man/3/sem_post
 * @see https://linux.die.net/man/3/sem_wait
 */
void wait_for_specific(const char *type, unsigned int id);

/**
 * @brief Handle child process.
 *
 * @param id ID of process.
 * @param max_time How long should process simulate activity in center.
 */
void proces_child(unsigned int id, unsigned int max_time);

/**
 * @brief Handle adult process.
 *
 * @param id ID of process.
 * @param max_time How long should process simulate activity in center.
 */
void proces_adult(unsigned int id, unsigned int max_time);

#endif //IOS2_PROJ2_H
