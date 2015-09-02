/* Header file of cachesim.c */
typedef struct cache cache_t;
typedef struct cache_set set_t;
typedef struct cache_line line_t;


struct cache{
  int num_sets;
  int lines_per_set;
  int block_size;
  set_t *sets;
};

struct cache_set{
  line_t *lines;
};

struct cache_line{
  int valid_bit;
  int tag;
  int last_used;
}; 

int search(cache_t *cache, long addr_req);
