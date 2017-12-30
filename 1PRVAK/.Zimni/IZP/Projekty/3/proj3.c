/**
 * Third project to IZP.
 *
 * Complete linkage.
 *
 * @see http://is.muni.cz/th/172767/fi_b/5739129/web/web/clsrov.html
 * @author Jakub "Ash258" Čábera <xcaber00@stud.fit.vutbr.cz>
 */

//region Includes
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <limits.h>
//endregion

//region Defines / Macros
#ifdef NDEBUG
#define debug(s)
#define dfmt(s, ...)
#define dint(i)
#define dfloat(f)
#else
/**
 * Print string for debugging purpose.
 *
 *  @example debug(string);
 */
#define debug(s) printf("- %s\n", s)

/**
 * Print debug information about variable
 *
 * @example dint(integer);
 */
#define dint(i) printf("- " __FILE__ ":%u: " #i " = %d\n", __LINE__, i)

/**
 * Print float for debugging purpose.
 *
 * @example dfloat(float);
 */
#define dfloat(f) printf("- " __FILE__ ":%u: " #f " = %g\n", __LINE__, f)

/**
 * Print string for debugging purpose (with specific format).
 *
 * @example dfmt("Cosi %d, %lf, %lf\n", a, cosi, nevim);
 */
#define dfmt(s, ...) printf("- " __FILE__ ":%u: " s "\n", __LINE__, __VA_ARGS__)
#endif

#define RED "\x1b[31m"
//#define GREEN "\x1b[32m"
#define RESET "\x1b[0m"
#define FALSE 0
#define TRUE 1

/** Error status codes */
enum errors{
	FLAG_ERROR     = 0,
	INVALID_FILE   = 1,
	INVALID_NUMBER = 2,
	OPEN_FILE      = 3,
	EMPTY_FILE     = 4,
	SAME_CLUSTER   = 5,
	ABOVE_1000     = 6,
	INVALID_COUNT  = 7,
	BIGGER_N       = 8,
	VALUES_INT     = 9,
	LINES          = 10,
	NULL_COUNT     = 11
};
//endregion

//region Structs
/**
 * Object.
 *
 * @param id Identifier of object.
 * @param x X coordinates.
 * @param y Y coordinates.
 */
struct obj_t{
	int   id;
	float x;
	float y;
};

/**
 * Object cluster.
 *
 *  @param size Object counter.
 *  @param capacity Cluster capacity.<br /> Quantity of objects for which is a reserved spot in field.
 *  @param obj_t Pointer to cluster.
 */
struct cluster_t{
	int          size;
	int          capacity;
	struct obj_t *obj;
};
//endregion

//region Helpers
/**
 * Print error message and exit program with given status code.
 *
 * @param statusCode Status code to exit.
 * @param fp File for closing before exit program.
 */
void die(int statusCode, FILE *fp){
	static const char *errs[] = {"Not supported arguments passed to program.",
	                             "Invalid file passed to program.",
	                             "Invalid object counter passed to program.",
	                             "File could not be opened.",
	                             "File is empty.",
	                             "Cannot merge same cluster.",
	                             "Coordinates must be smaller than 1000.",
	                             "Incorrect count in file.",
	                             "Given number of clusters cannot be bigger than number of clusters in file.",
	                             "One of cluster value is not integer.",
	                             "Count value in file is bigger than lines in file.",
	                             "Number of counts cannot be negative or zero."
	};

	fprintf(stderr, RED
			"%s\n"
			"Exit status code: %d\n"
			RESET, errs[statusCode], statusCode + 100);
	fclose(fp);
	exit(statusCode + 100);
}

//region File Helpers
/**
 * Check if given file exists.
 *
 * @param filename Name of file.
 *
 * @return 1 If file exists.
 */
int file_exists(char *filename){
	FILE *filePointer;

	if(!(filePointer = fopen(filename, "r"))) return FALSE;

	fclose(filePointer);
	return TRUE;
}

/**
 * Chceck if file is empty.
 *
 * @param file File to check.
 *
 * @see http://stackoverflow.com/questions/30133210/check-if-file-is-empty-or-not-in-c
 *
 * @return 1 If file is empty
 */
int is_empty(FILE *file){
	long savedOffset = ftell(file);
	fseek(file, 0, SEEK_END);

	if(ftell(file) == 0) return TRUE;

	fseek(file, savedOffset, SEEK_SET);
	return FALSE;
}

/**
 * Count lines in file.
 *
 * @param fp File to check.
 *
 * @see http://stackoverflow.com/questions/12733105/c-function-that-counts-lines-in-file
 *
 * @return Quantity of lines in file.
 */
int count_lines(char *filename){
	FILE *fp       = fopen(filename, "r");
	int  ch, lines = 1;

	while(!feof(fp)){
		ch = fgetc(fp);
		if(ch == '\n') lines++;
	}
	fclose(fp);

	return lines - 1;
}
//endregion

/**
 * Chunk of cluster objects. Value recommended for reallocation.
 */
const int CLUSTER_CHUNK = 10;
//endregion

//region Completed functions
//region Sorting
/**
 * Compare two clusters by their ids.
 * @param a Cluster a.
 * @param b Cluster b.
 *
 * @return -1 If id of first object is lower than id of second cluster.
 * 			0 If ids are same.
 * 			1 If id of first object is bigger than id of second cluster.
 */
static int obj_sort_compare(const void *a, const void *b){
	const struct obj_t *o1 = a;
	const struct obj_t *o2 = b;

	if(o1->id < o2->id) return -1;
	if(o1->id > o2->id) return 1;

	return 0;
}

/**
 * Ascending sort objects in cluster by object identifiers.
 *
 * @param c Cluster where to sort objects.
 */
void sort_cluster(struct cluster_t *c){
	qsort(c->obj, (size_t) c->size, sizeof(struct obj_t), &obj_sort_compare);
}
//endregion

//region Initializing and loading clusters
/**
 * Initialize cluster. Allocate memory for object capacity.
 *
 * @param c Cluster.
 * @param cap Object capacity.
 *
 * @details Null pointer in array => capacity == 0.
 */
void init_cluster(struct cluster_t *c, int cap){
	assert(c != NULL);
	assert(cap >= 0);

	c->size     = 0;
	c->capacity = cap;
	c->obj      = (cap == 0)
	              ? NULL
	              : (struct obj_t *) malloc(sizeof(struct obj_t) * cap);
}

/**
 * Initialize object.
 *
 * @param id Object ID.
 * @param x Object x coordinate.
 * @param y Object y coordinate.
 * @param obj Pointer to object for creating.
 */
void init_object(int id, float x, float y, struct obj_t *obj){
	obj->id = id;
	obj->x  = x;
	obj->y  = y;
}

/**
 * Remove all objects from cluster ==> Initialize empty cluster.
 *
 * @param c Cluster to clear.
 */
void clear_cluster(struct cluster_t *c){
	free(c->obj);

	init_cluster(c, 0);
}
//endregion

//region Sizing
/**
 * Change cluster capacity.
 *
 * @param c Cluster for capacity change.
 * @param new_cap New capacity.
 *
 * @return Changed cluster.
 */
struct cluster_t *resize_cluster(struct cluster_t *c, int new_cap){
	assert(c);
	assert(c->capacity >= 0);
	assert(new_cap >= 0);

	if(c->capacity >= new_cap) return c;

	size_t size = sizeof(struct obj_t) * new_cap;

	void *arr = realloc(c->obj, size);
	if(arr == NULL) return NULL;

	c->obj      = arr;
	c->capacity = new_cap;

	return c;
}

/**
 * Final clearing before program quit.
 *
 * @param cluster Pointer to clusters array.
 * @param count Number of clusters to clear.
 */
void clear_clusters(struct cluster_t *cluster, int count){
	for(int i = 0; i < count; i++) {
		clear_cluster(&cluster[i]);
	}
	free(cluster);
}

/**
 * Add object to end of cluster.
 *
 * @details Enlarge cluster, if there is full capacity.
 *
 * @param c Cluster, where to add object.
 * @param obj Object which will be added.
 */
void append_cluster(struct cluster_t *c, struct obj_t obj){
	if(c->size == c->capacity) resize_cluster(c, c->capacity + 1 + CLUSTER_CHUNK);

	c->obj[(c->size)++] = obj;
}

/**
 * Merge two clusters.
 *
 * @details Append first cluster by second clusters objects. First cluster will be enlarged if there is no available space.
 * Objects in first cluster will be ascending sorted by identifiers.
 * Second cluster will not be changed.
 *
 * @param c1 Cluster, where to add objects.
 * @param c2 Cluster with objects to merge.
 */
void merge_clusters(struct cluster_t *c1, struct cluster_t *c2){
	assert(c1 != NULL);
	assert(c2 != NULL);
	assert(c1->obj->id != c2->obj->id);

	if(c1 == c2) die(SAME_CLUSTER, NULL);

	for(int i = 0; i < c2->size; i++) append_cluster(c1, c2->obj[i]);

	sort_cluster(c1);
}

/**
 * Remove cluster from array of clusters.
 *
 * @details Array of clusters contains 'narr' clusters.
 * Cluster for deletions is located at 'idx' index.
 *
 * @param carr Array of clusters.
 * @param narr Quantity of clusters in array.
 * @param idx Index of cluster for deletion.
 *
 * @return New capacity of array.
 */
int remove_cluster(struct cluster_t *carr, int narr, int idx){
	assert(idx < narr);
	assert(narr > 0);

	/*struct cluster_t *current, *next, tmp;
	for(int          i = idx; i < narr - 1; i++) {
		current = &carr[i];
		next    = &carr[i + 1];
		tmp     = *current;

		*current = *next;
		*next    = tmp;
	}
	clear_cluster(&carr[narr - 1]);*/

	clear_cluster(&carr[idx]);
	carr[idx] = carr[narr -1];
	init_cluster(&carr[narr -1], 0);

	return narr - 1;
}
//endregion

//region Printing
/**
 * Print cluster to stdout.
 *
 * @param c Cluster to be printed.
 */
void print_cluster(struct cluster_t *c){
	for(int i = 0; i < c->size; i++) {
		if(i) putchar(' ');
		printf("%d[%g,%g]", c->obj[i].id, c->obj[i].x, c->obj[i].y);
	}
	putchar('\n');
}

/**
 * Print specific number of clusters.
 *
 * @param carr Pointer to first cluster.
 * @param narr Which clusters will be printed.
 */
void print_clusters(struct cluster_t *carr, int narr){
	printf("Clusters:\n");
	for(int i = 0; i < narr; i++) {
		printf("cluster %d: ", i);
		print_cluster(&carr[i]);
	}
}
//endregion
//endregion

//region Math
/**
 * Calculate Euclidean distance between two objects.
 *
 * @param o1 First object.
 * @param o2 Second object.
 *
 * @see https://en.wikipedia.org/wiki/Euclidean_distance#Two_dimensions
 *
 * @return Euclidean distance between two objects.
 */
float obj_distance(struct obj_t *o1, struct obj_t *o2){
	assert(o1 != NULL);
	assert(o2 != NULL);

	return sqrtf(powf((o2->x - o1->x), 2) + powf((o2->y - o1->y), 2));
}

/**
 * Calculate distance between two clusters.
 *
 * @param c1 First cluster.
 * @param c2 Second cluster.
 *
 * @see https://en.wikipedia.org/wiki/Complete-linkage_clustering - D(X,Y) = max d(x,y)
 *
 * @return Distance between two clusters.
 */
float cluster_distance(struct cluster_t *c1, struct cluster_t *c2){
	assert(c1 != NULL);
	assert(c1->size > 0);
	assert(c2 != NULL);
	assert(c2->size > 0);

	float biggest_distance = 0, current_distance;

	for(int i = 0; i < c1->size; i++) {
		for(int j = 0; j < c2->size; j++) {
			current_distance = obj_distance(&c1->obj[i], &c2->obj[j]);
			if(current_distance > biggest_distance){
				biggest_distance = current_distance;
			}
		}
	}

	return biggest_distance;
}

/**
 * Find <i>two</i> nearest clusters in array of clusters.
 *
 * @details Found clusters will be saved to memory on address 'c1' ('c2').
 *
 * @param carr Array of clusters.
 * @param narr Size of array.
 * @param c1 Pointer to first cluster.
 * @param c2 Pointer to second cluster.
 */
void find_neighbours(struct cluster_t *carr, int narr, int *c1, int *c2){
	assert(narr > 0);

	float   smallest_distance = INT_MAX, current_distance = 0;
	for(int i                 = 0; i < narr - 1; i++) {
		for(int j = i + 1; j < narr; j++) {
			/*if j = i => same element
			if j = i+1 => out of narr => narr -1*/
			current_distance = cluster_distance(&carr[i], &carr[j]);
			if(current_distance < smallest_distance){
				smallest_distance = current_distance;
				*c1 = i;
				*c2 = j;
			}
		}
	}
}
//endregion

//region Main
/**
 * Handle program arguments.
 *
 * @param argc Quantity of arguments.
 * @param argv Array of arguments.
 */
void handle_input(int argc, char **argv, char **fileName, int *number){
	if(argc <= 1) die(FLAG_ERROR, NULL);
	*fileName = argv[1];

	if(file_exists(*fileName) == FALSE){ die(INVALID_FILE, NULL); }
	else if(argc == 2){ *number = 1; }
	else if(argc == 3){
		int error = sscanf(argv[2], "%d", &*number);
		if((error != 1) || (*number <= 0)) die(INVALID_NUMBER, NULL);
	} else {
		die(FLAG_ERROR, NULL);
	}
}

/**
 * Load objects form file.
 *
 * @details For each object will be created cluster ==> Cluster will be saved to array of clusters.
 * Allocate space for array of all clusters.
 * Pointer to first item of array will be saved to memory on 'arr'.
 * When error occurred NULL will be saved to array of clusters.
 *
 * @param filename File for input.
 * @param arr Array of clusters.
 *
 * @return Quantity of loaded clusters.
 */
int load_clusters(char *filename, struct cluster_t **arr, int *number){
	assert(arr != NULL);

	FILE  *fp   = fopen(filename, "r");
	int   count = 0, lines = count_lines(filename);
	int   id    = 0, error = 0;
	float x     = 0, y = 0;

	if(!fp) die(OPEN_FILE, NULL);
	if(is_empty(fp) == 1) die(EMPTY_FILE, fp);

	//Line with: count=x
	error = fscanf(fp, "count=%d\n", &count);
	if(error != 1) die(INVALID_COUNT, fp);
	if(count <= 0) die(NULL_COUNT, fp);
	if(count > lines) die(LINES, fp);

	*arr = (struct cluster_t *) malloc(sizeof(struct cluster_t) * count);

	//Cluster lines
	for(int j = 0; j < count; j++) {
		error = fscanf(fp, "%d %f %f\n", &id, &x, &y); //Convert
		if(x >= 1000 || y >= 1000) die(ABOVE_1000, fp);
		if(error != 3) die(VALUES_INT, fp);

		struct cluster_t *cluster = &*(*arr + j);
		init_cluster(cluster, 1);
		cluster->size = 1;
		init_object(id, x, y, cluster->obj);
	}

	if(*number > count) die(BIGGER_N, fp);
	fclose(fp);

	return count;
}
//endregion

int main(int argc, char *argv[]){
	struct cluster_t *clusters;
	char             *fileName;
	int              n;

	handle_input(argc, argv, &fileName, &n);

	int count = load_clusters(fileName, &clusters, &n);

	while(count != n){
		int some = -258258, some_other = -258;
		find_neighbours(clusters, count, &some, &some_other);
		merge_clusters(&clusters[some], &clusters[some_other]);
		count = remove_cluster(clusters, count, some_other);
	}

	print_clusters(clusters, count);
	//Final clearing
	clear_clusters(clusters, count);
	return 0;
}
