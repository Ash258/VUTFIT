#include "proj2.h"
//region Done

void *usage() {
	char *result =
			"Usage: ./proj2 [A] [C] [AGT] [CGT] [AWT] [CWT]\n"
					"\t A   \t Number of \"adult\" processes. A > 0. \n"
					"\t C   \t Number of \"Child\" processes. C > 0. \n"
					"\t AGT \t Maximum time (in milliseconds) after which is \"adult\" process generated. AGT >= 0 && AGT < 5001. \n"
					"\t CGT \t Maximum time (in milliseconds) after which is \"child\" process generated. CGT >= 0 && CGT < 5001. \n"
					"\t AWT \t How long (in milliseconds) should \"adult\" process simulate activity in center. AWT >= 0 && AWT < 5001. \n"
					"\t CWT \t How long (in milliseconds) should \"child\" process simulate activity in center. CWT >= 0 && CWT < 5001. \n";
	printf(result);
	exit(EXIT_FAILURE);
}

bool init() {
	file_ptr = fopen("proj2.out", "w");
	//Shared memory
	MMAP(children)
	MMAP(adults)
	MMAP(operation_number)

	*children = (struct counter) {.center = 0, .waiting = 0};
	*adults = (struct counter) {.center = 0, .waiting = 0};
	*operation_number = 0;

	//Semaphores
	if ((lock = sem_open("/xcaber00_lock", O_CREAT, MOD, 1)) == SEM_FAILED) return FALSE;
	if ((a_leave = sem_open("/xcaber00_adult", O_CREAT, MOD, 1)) == SEM_FAILED) return FALSE;
	if ((ch_enter = sem_open("/xcaber00_child", O_CREAT, MOD, 0)) == SEM_FAILED) return FALSE;
	if ((barrier = sem_open("/xcaber00_barrier", O_CREAT, MOD, 0)) == SEM_FAILED) return FALSE;
	return TRUE;
}

bool handle_arguments(int argc, char **argv, struct arguments *args) {
	if (argc == 1 || argc < 7) {
		fprintf(stderr, "Too few arguments. 6 are expected.\n");
		return FALSE;
	} else if (argc >= 8) {
		fprintf(stderr, "Too many arguments.\n");
		return FALSE;
	}

	unsigned int values[6]; // Empty array for storing all values.
	unsigned int rules[6][2] = {{1, UINT_MAX}, // Adults
								{1, UINT_MAX}, // Children
								{0, MAX_WAIT_TIME}, // AGT
								{0, MAX_WAIT_TIME}, // CGW
								{0, MAX_WAIT_TIME}, // AWT
								{0, MAX_WAIT_TIME} // CWT
	};

	for (int i = 0; i < 6; i++) {
		if (!parse_int(argv[i + 1], &values[i], rules[i][0], rules[i][1])) {
			fprintf(stderr, "Cannot process %d. argument. Expected unsigned integer from %u to %u.\n",
					i + 1, rules[i][0], rules[i][1]);

			return FALSE;
		}
	}

	*args = (struct arguments) {
			.A = values[0], .C = values[1], .AGT = values[2], .CGT = values[3], .AWT = values[4], .CWT = values[5]
	};

	return TRUE;
}

bool parse_int(char *source, unsigned int *dest, unsigned int min, unsigned int max) {
	char *pointer;
	long result = strtoul(source, &pointer, 10);

	*dest = (unsigned int) result;

	return (*pointer == '\0'
			&& pointer != source
			&& result <= max
			&& result >= min
	);
}

void clean_up() {
	// Unmap shared memory.
	UNMAP(children);
	UNMAP(adults);
	UNMAP(operation_number);

	sem_close(ch_enter);
	sem_close(a_leave);
	sem_close(lock);
	sem_close(barrier);

	sem_unlink("/xcaber00_child");
	sem_unlink("/xcaber00_adult");
	sem_unlink("/xcaber00_lock");
	sem_unlink("/xcaber00_barrier");
	if (file_ptr != NULL) fclose(file_ptr);
}
//endregion

void wait_for_specific(const char *type, unsigned int id) {
	START_TRAN
	if (children->waiting != 0 || children->center != 0
		|| adults->center != 0 || adults->waiting != 0) {
		END_TRAN
		LOCK_SEM(barrier)
		START_TRAN
	}

	UNLOCK_SEM(barrier)
	WRITE(type, id, "finished")
	END_TRAN
}

void gen_proc(unsigned int count, unsigned int gen_delay, char *type, unsigned int max_work,
			  void (*perf)(unsigned int, unsigned int)) {
	for (unsigned int i = 1; i <= count; ++i) {
		SLEEP(gen_delay);

		pid_t adult = fork();
		if (adult == 0) {
			perf(i, max_work);
			wait_for_specific(type, i);
			break;
		}
	}

	WAIT(count)
}

void proces_child(unsigned int id, unsigned int max_time) {
	START_TRAN
	WRITE("C", id, "started")
	// Specification -> Process child -> 2 -> a
	// TODO: Resolve waiting.
	if ((children->center + 1) > (3 * (adults->center)) && adults->waiting != 0) {
		//WRITE_SPECIAL("C", id, adults->center, children->center)
	}
	END_TRAN

	LOCK_SEM(a_leave)
	LOCK_SEM(ch_enter)

	START_TRAN
	WRITE("C", id, "enter")
	++(children->center);
	--(children->waiting);
	END_TRAN

	SLEEP(max_time)

	START_TRAN
	WRITE("C", id, "trying to leave")
	WRITE("C", id, "leave")
	--(children->center);
	UNLOCK_SEM(ch_enter)
	UNLOCK_SEM(a_leave)
	END_TRAN
}

void proces_adult(unsigned int id, unsigned int max_time) {
	START_TRAN
	WRITE("A", id, "started")
	WRITE("A", id, "enter")
	// One adult enter == -wait, + in
	++(adults->center);
	--(adults->waiting);

	// Let 3 children enter.
	UNLOCK_SEM(ch_enter)
	UNLOCK_SEM(ch_enter)
	UNLOCK_SEM(ch_enter)
	END_TRAN

	SLEEP(max_time);

	LOCK_SEM(a_leave)

	START_TRAN
	WRITE("A", id, "trying to leave")
	// Specification -> Process child -> 4 -> a
	// TODO: Resolve waiting.
	if ((children->center) > ((adults->center) * 3)) {
		//WRITE_SPECIAL("A", id, adults->center, children->center)
	}
	END_TRAN

	LOCK_SEM(ch_enter)
	LOCK_SEM(ch_enter)
	LOCK_SEM(ch_enter)

	START_TRAN

	--(adults->center);
	// Clean waiting children and add space for coming children if the adult is last
	if (adults->waiting == 0 && adults->center == 0) {
		int waiting = 0;
		sem_getvalue(ch_enter, &waiting);
		unsigned int count = abs(waiting) + children->waiting;

		for (unsigned int i = 0; i < count; ++i) UNLOCK_SEM(ch_enter);
	}

	WRITE("A", id, "leave")
	UNLOCK_SEM(a_leave)
	END_TRAN
}

/**
 * @brief Program startup.
 *
 * @param argc Arguments count.
 * @param argv Arguments.
 *
 * @see http://stackoverflow.com/a/7085638
 *
 * @return 0 on success.
 */
int main(int argc, char **argv) {
	setbuf(stdout, NULL); // See link above
	struct arguments args;

	if (!handle_arguments(argc, argv, &args)) return EXIT_ERROR;
	if (!init()) {
		clean_up();
		perror("Something went wrong");
		return EXIT_ERROR;
	}
	setbuf(file_ptr, NULL);
	// Insert adults and children to counters.
	adults->waiting = args.A;
	children->waiting = args.C;
	pid_t adult_gen = fork();

	if (adult_gen == 0) {
		gen_proc(args.A, args.AGT, "A", args.AWT, proces_adult);
	} else {
		pid_t child_gen = fork();
		if (child_gen == 0) {
			gen_proc(args.C, args.CGT, "C", args.CWT, proces_child);
		} else {
			WAIT(2);
		}
	}

	clean_up();
	return EXIT_SUCCESS;
}
