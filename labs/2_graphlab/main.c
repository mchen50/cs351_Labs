#include <stdlib.h>
#include <stdio.h>
#include "graph.h"

int main (int argc, char *argv[]) {
  vertex_t *vlist_head = NULL,*vp;
  adj_vertex_t *adj_v;

  int i;
  for(i=1;i <= argc-1;i+=3){
    add_edge(&vlist_head, argv[i], argv[i+1], atoi(argv[i+2]));
  }
  
  int x = 0; //used for counting how many actual cities we have
  printf("Adjacency list:\n");
  for (vp = vlist_head; vp != NULL; vp = vp->next) {
    printf("  %s: ", vp->name);
    for (adj_v = vp->adj_list; adj_v != NULL; adj_v = adj_v->next) {
      printf("%s(%d) ", adj_v->vertex->name, adj_v->edge_weight);
    }
    printf("\n");
    x++;
  }
  
  int length;//for distance summing
  vertex_t *tour[x];
  
  for (vp = vlist_head; vp != NULL; vp = vp->next){
   
    for(i = 0; i<x;i++){
      tour[i] = NULL;
    }//initialize

    length = find_tour(vp, tour, x, x);
    
    if (length != 0){
      printf("\nA tour is found:\n");
      for (i = 0;i < x;i++){
	printf("%s ", tour[i]->name);
      }
      printf("\n\nThe total distance is:\n");
      printf("%d\n",length);

      free_stuff(vp);
      return 0;
    }
    else{
      printf("\nNo tour found starting at %s\n", vp->name);
    }
  }
  
  free_stuff(vp);
  printf("\nThere isn't a tour");
  /*
  vlist_head= v1 = malloc(sizeof(vertex_t));
  v1->name = argv[1];
  v2 = malloc(sizeof(vertex_t));
  v2->name = argv[2];
  
  v1->next = v2;
  v2->next = NULL;

  adj_v = v1->adj_list = malloc(sizeof(adj_vertex_t));
  adj_v->vertex = v2;
  adj_v->edge_weight = atoi(argv[3]);
  adj_v->next = NULL;

  adj_v = v2->adj_list = malloc(sizeof(adj_vertex_t));
  adj_v->vertex=v1;
  adj_v->edge_weight = atoi(argv[3]);
  adj_v->next=NULL;

  printf("Adjacency list:\n");
  for (vp = vlist_head; vp != NULL; vp = vp->next) {
    printf("  %s: ", vp->name);
    for (adj_v = vp->adj_list; adj_v != NULL; adj_v = adj_v->next) {
      printf("%s(%d) ", adj_v->vertex->name, adj_v->edge_weight);
    }
    printf("\n");
  }
  */
  /* note, I'm not free-ing here, but you should! */
  /* free(v1);
  free(v2);
  free(adj_v);
  */
  /* 
	 * Programatically constructing the following simple graph:
	 *
	 *     10         5
	 * A <-----> B <-----> C
	 *
	 * Delete this code and add your own!
	 */
	/*vertex_t *v1, *v2, *v3, *vlist_head, *vp;
	adj_vertex_t *adj_v;

	vlist_head = v1 = malloc(sizeof(vertex_t));
	v1->name = "A";
	v2 = malloc(sizeof(vertex_t));
	v2->name = "B";
	v3 = malloc(sizeof(vertex_t));
	v3->name = "C";

	v1->next = v2;
	v2->next = v3;
	v3->next = NULL;

	adj_v = v1->adj_list = malloc(sizeof(adj_vertex_t));
	adj_v->vertex = v2;
	adj_v->edge_weight = 10;
	adj_v->next = NULL;

	adj_v = v2->adj_list = malloc(sizeof(adj_vertex_t));
	adj_v->vertex = v1;
	adj_v->edge_weight = 10;
	adj_v = adj_v->next = malloc(sizeof(adj_vertex_t));
	adj_v->vertex = v3;
	adj_v->edge_weight = 5;
	adj_v->next = NULL;

	adj_v = v3->adj_list = malloc(sizeof(adj_vertex_t));
	adj_v->vertex = v2;
	adj_v->edge_weight = 5;
	adj_v->next = NULL;*/
  
 
	/* print out our adjacency list */
	/*printf("Adjacency list:\n");
	for (vp = vlist_head; vp != NULL; vp = vp->next) {
		printf("  %s: ", vp->name);
		for (adj_v = vp->adj_list; adj_v != NULL; adj_v = adj_v->next) {
			printf("%s(%d) ", adj_v->vertex->name, adj_v->edge_weight);
		}
		printf("\n");
	}
	*/
	/* note, I'm not free-ing here, but you should! */
	/*free(v1);
	free(v2);
	free(v3);
	free(adj_v);
	*/
	return 0;
}
