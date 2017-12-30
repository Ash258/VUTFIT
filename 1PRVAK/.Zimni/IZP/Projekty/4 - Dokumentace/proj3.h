/**
 * @mainpage Third project to IZP.
 *
 * Complete-linkage clustering is one of several methods of agglomerative hierarchical clustering.
 *
 * At the beginning of the process, each element is in a cluster of its own. The clusters are then sequentially combined into larger clusters until all elements end up being in the same cluster. At each step, the two clusters separated by the shortest distance are combined. The definition of 'shortest distance' is what differentiates between the different agglomerative clustering methods. In complete-linkage clustering, the link between two clusters contains all element pairs, and the distance between clusters equals the distance between those two elements (one in each cluster) that are farthest away from each other. The shortest of these links that remains at any step causes the fusion of the two clusters whose elements are involved. The method is also known as farthest neighbour clustering.
 *
 * @see http://is.muni.cz/th/172767/fi_b/5739129/web/web/clsrov.html
 * @file proj3.h
 * @author Ash258 <cabera.jakub@gmail.com> <xcaber00@stud.fit.vutbr.cz>
 * @date 28.11.2016
 */

/**
 * Chunk of cluster objects.
 * @details Value recommended for reallocation.
 */
const int CLUSTER_CHUNK = 10;

/**
 * Enumeration for error status codes.
 */
enum errors{
	FLAG_ERROR     = 0,        /**< Incorrect arguments passed to program. */
	INVALID_FILE   = 1,     /**< Incorrect file. */
	INVALID_NUMBER = 2,     /**< Invalid file passed to program. */
	OPEN_FILE      = 3,     /**< Cannot open file. */
	EMPTY_FILE     = 4,        /**< File is empty. */
	SAME_CLUSTER   = 5,     /**< Cannot calculate distance of one object.  */
	ABOVE_1000     = 6,     /**< Coordinates cannot be more than 1000. */
	INVALID_COUNT  = 7,     /**< "Count" in file is invalid. */
	BIGGER_N       = 8,     /**< Given number is bigger than count in file. */
	VALUES_INT     = 9,     /**< Cluster value is not integer. */
	LINES          = 10,    /**< Count cannot be bigger than line count. */
	NULL_COUNT     = 11    /**< Count is null. */
};

/**
 * @brief Structure object.
 */
struct obj_t{
	int   id;	/**< Identifier of object. */
	float x;    /**< X Coordinate. */
	float y;    /**< Y Coordinate. */
};

/**
 * @brief Cluster.
 */
struct cluster_t{
	int          size;      /**< Actual size of cluter. */
	int          capacity;  /**< Maximum capacity of cluster. */
	struct obj_t *obj;      /**< Array of objects. */
};

//region Helpers
/** @defgroup Helpers
 *
 * @brief Helper functions
 *
 * Helper functions for security purpose.
 */

/** @addtogroup Helpers */
/*@{*/

/**
 * Print error message and exit program with given status code.
 *
 * @post
 *      - Exit program
 *      - File stream will be closed.
 *
 * @param statusCode Status code to exit.
 * @param fp File for closing before exit program.
 */
void die(int statusCode, FILE *fp);

/**
 * Check if given file exists.
 *
 * @param filename Name of file.
 *
 * @return 1 If file exists.
 */
int file_exists(char *filename);

/**
 * Check if file is empty.
 *
 * @param file File to check.
 *
 * @see http://stackoverflow.com/a/30133993
 *
 * @return 1 If file is empty
 */
int is_empty(FILE *file);

/**
 * Count lines in file.
 *
 * @param fp File to check.
 *
 * @see http://stackoverflow.com/a/12733630
 *
 * @return Quantity of lines in file.
 */
int count_lines(char *filename);
/*@}*/
//endregion

/**
 * Compare two clusters by their ids.
 *
 * @param a Cluster a.
 * @param b Cluster b.
 *
 * @return -1 If id of first object is lower than id of second cluster.
 * 			0 If ids are same.
 * 			1 If id of first object is bigger than id of second cluster.
 */
static int obj_sort_compare(const void *a, const void *b);

/**
 * Ascending sort objects in cluster by object identifiers.
 *
 * @param c Cluster where to sort objects.
 */
void sort_cluster(struct cluster_t *c);

/**
 * Initialize cluster. Allocate memory for object capacity.
 *
 * @param c Cluster.
 * @param cap Object capacity.
 *
 * @pre
 *      - c cannot be NULL.
 *      - cap must be bigger than 0.
 *
 * @post
 *      - If capacity is 0 cluster object pointer will be NULL
 */
void init_cluster(struct cluster_t *c, int cap);

/**
 * Initialize object.
 *
 * @param id Object ID.
 * @param x Object x coordinate.
 * @param y Object y coordinate.
 * @param obj Pointer to object for creating.
 */
void init_object(int id, float x, float y, struct obj_t *obj);

/**
 * Remove all objects from cluster ==> Initialize empty cluster.
 *
 * @post
 *      - All objects will be freed.
 *      - Cluster is reinitialized with zero count of objects.
 *
 * @param c Cluster to clear.
 */
void clear_cluster(struct cluster_t *c);

/**
 * Change cluster capacity.
 *
 * @pre
 *      - c cannot be null.
 *      - new_cap is greater than 0.
 *      - c capacity is greater or equal 0.
 *
 * @param c Cluster for capacity change.
 * @param new_cap New capacity.
 *
 * @return Changed cluster.
 */
struct cluster_t *resize_cluster(struct cluster_t *c, int new_cap);

/**
 * Final clearing before program quit.
 *
 * @post Given array will be freed.
 *
 * @param cluster Pointer to clusters array.
 * @param count Number of clusters to clear.
 */
void clear_clusters(struct cluster_t *cluster, int count);

/**
 * Add object to end of cluster.
 *
 * @details Enlarge cluster, if there is full capacity.
 *
 * @param c Cluster, where to add object.
 * @param obj Object which will be added.
 */
void append_cluster(struct cluster_t *c, struct obj_t obj);

/**
 * Merge two clusters.
 *
 * @details Append first cluster by second clusters objects. First cluster will be enlarged if there is no available space.
 * Objects in first cluster will be ascending sorted by identifiers.
 * Second cluster will not be changed.
 *
 * @post Cluster 1 will be resized, if won't have enough capacity and it's objects will be
 *
 * @param c1 Cluster, where to add objects.
 * @param c2 Cluster with objects to merge.
 */
void merge_clusters(struct cluster_t *c1, struct cluster_t *c2);

/**
 * Remove cluster from array of clusters.
 *
 * @details Array of clusters contains 'narr' clusters.
 * Cluster for deletions is located at 'idx' index.
 *
 * @pre
 *      - idx must be smaller than narr.
 *      - narr must be bigger than 0.
 *
 * @param carr Array of clusters.
 * @param narr Quantity of clusters in array.
 * @param idx Index of cluster for deletion.
 *
 * @return New capacity of array.
 */
int remove_cluster(struct cluster_t *carr, int narr, int idx);

/**
 * Print cluster to stdout.
 *
 * @param c Cluster to be printed.
 */
void print_cluster(struct cluster_t *c);

/**
 * Print specific number of clusters.
 *
 * @param carr Pointer to first cluster.
 * @param narr Which clusters will be printed.
 */
void print_clusters(struct cluster_t *carr, int narr);

/**
 * Calculate Euclidean distance between two objects.
 *
 * @param o1 First object.
 * @param o2 Second object.
 *
 * @pre
 *      - o1 must be different from NULL.
 *      - o2 must be different from NULL.
 *
 * @see https://en.wikipedia.org/wiki/Euclidean_distance#Two_dimensions
 *
 * @return Euclidean distance between two objects.
 */
float obj_distance(struct obj_t *o1, struct obj_t *o2);

/**
 * Calculate distance between two clusters.
 *
 * @param c1 First cluster.
 * @param c2 Second cluster.
 *
 * @pre
 *      - c1 must be different from NULL.
 *      - c2 must be different from NULL.
 *      - Size of c1 must be bigger than 0.
 *      - Size of c2 must be bigger than 0.
 *
 * @see https://en.wikipedia.org/wiki/Complete-linkage_clustering - D(X,Y) = max d(x,y)
 *
 * @return Distance between two clusters.
 */
float cluster_distance(struct cluster_t *c1, struct cluster_t *c2);

/**
 * Find <i>two</i> nearest clusters in array of clusters.
 *
 * @details Found clusters will be saved to memory on address 'c1' ('c2').
 *
 * @pre
 *      - narr must be bigger than 0.
 *
 * @post Neighbours will be saved to c1, c2.
 *
 * @param carr Array of clusters.
 * @param narr Size of array.
 * @param c1 Pointer to first cluster.
 * @param c2 Pointer to second cluster.
 */
void find_neighbours(struct cluster_t *carr, int narr, int *c1, int *c2);

/**
 * Handle program arguments.
 *
 * @post
 *      - fileName will be set.
 *      - number will be set.
 *
 * @param argc Quantity of arguments.
 * @param argv Array of arguments.
 */
void handle_input(int argc, char **argv, char **fileName, int *number);

/**
 * Load objects form file.
 *
 * @details For each object will be created cluster ==> Cluster will be saved to array of clusters.
 * Allocate space for array of all clusters.
 * Pointer to first item of array will be saved to memory on 'arr'.
 * When error occurred NULL will be saved to array of clusters.
 *
 * @post
 *      -
 *
 * @pre
 *      - arr must be different from NULL.
 *
 * @param filename File for input.
 * @param arr Array of clusters.
 *
 * @return Quantity of loaded clusters.
 */
int load_clusters(char *filename, struct cluster_t **arr, int *number);