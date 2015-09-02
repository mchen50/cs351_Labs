#include <stdio.h>
#include <stdlib.h>
#include "cachesim.h"

int main (int argc, char *argv[]) {
    int num_lines = atoi(argv[1]),
        lines_per_set = atoi(argv[2]),
        bytes_per_block = atoi(argv[3]);

    char line[80];

    long addr_req;

    int hit = 0,total_req = 0;

    double rate = 0;

    printf("Simulating cache with:\n");
    printf(" - Total lines   = %d\n", num_lines);
    printf(" - Lines per set = %d\n", lines_per_set);
    printf(" - Block size    = %d bytes\n", bytes_per_block);
    
    /* initilize the cache */
    int num_sets = num_lines/lines_per_set;
    cache_t *cache = malloc(sizeof(cache_t));
    cache->num_sets = num_sets;
    cache->lines_per_set = lines_per_set;
    cache->block_size = bytes_per_block;
    cache->sets = malloc(num_sets*sizeof(set_t));

    int i;
    for(i=0;i<num_sets;i++){
      cache->sets[i].lines = malloc(lines_per_set*sizeof(line_t));
    }
    
    while (fgets(line, 80, stdin)) {
        addr_req = strtol(line, NULL, 0);

        /* simulate cache fetch with address `addr_req` */
        //printf("Processing request: 0x%lX\n", addr_req);
	
	/* search in our cache simulator */
	if(search(cache, addr_req)){
	  hit++;
	}

	total_req++;
    }

    rate = 100.0*((double)hit/total_req);

    printf("Hit rate: %0.2f%% | Miss rate: %0.2f%%\n",rate,100-rate );
    return 0;
}

int search(cache_t *cache, long addr_req){
  /* return 1 if the addr is in the cache, otherwise return 0 */
  int hit_miss = 0;
  int lines_per_set = cache->lines_per_set;
  int block_size = cache->block_size;
  int num_sets = cache->num_sets;

  int set_index = (addr_req/block_size)%num_sets;
  int tag = addr_req/(block_size*num_sets);

  set_t *set = cache->sets + set_index;

  int i;

  for(i=0; i < lines_per_set;i++){
    if((set->lines[i].valid_bit == 1)&&(set->lines[i].tag==tag)){
      hit_miss = 1;

      break;
    }
  }

  if(hit_miss){
    set->lines[i].last_used = set->lines[i].last_used + 1;
    return hit_miss;
  }
  else{
    int last_used_t = set->lines[0].last_used;
    int tmp_line = 0;

    for(i=1; i < lines_per_set;i++){
      if(set->lines[i].last_used <= last_used_t){
	last_used_t = set->lines[i].last_used;
	tmp_line = i;
      }
    }
    
    /*line_t *line_evict = set->lines[tmp_line];
    line_evict->valid_bit = 1;
    line_evict->tag = tag;
    line_evict->last_used=0;*/

    set->lines[tmp_line].valid_bit = 1;
    set->lines[tmp_line].tag = tag;
    set->lines[tmp_line].last_used=0;
    return hit_miss;
  }
}
