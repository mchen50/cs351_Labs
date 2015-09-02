#include <stdlib.h>
#include <string.h>
#include "graph.h"

/* implement the functions you declare in graph.h here */
vertex_t *make_vertex(char *name, vertex_t *next){
  vertex_t *newVertex;
  newVertex = malloc(sizeof(vertex_t));
  newVertex->name = name;
  newVertex->next = next;
  
  return newVertex;
}

vertex_t *find_vertex(vertex_t *head, char *name){
  vertex_t *temp;
  char *temChar;
  for (temp = head; temp!=NULL; temp = temp->next){
    temChar = temp->name;
    if(strcmp(temChar,name)==0){
      return temp;
    }
  }
  return NULL;
}

void add_adj_vertex(adj_vertex_t **head, vertex_t *to, int weight){
  adj_vertex_t *adj_v = *head;
  if(adj_v  == NULL){/*if the head is empty*/ //assume Null after malloc
    adj_v = malloc(sizeof(adj_vertex_t));
    adj_v->vertex = to;
    adj_v->edge_weight = weight;
    adj_v->next = NULL;
    *head = adj_v;
  }
  else{//if not empty, must have an exiting adj_vertex_t
    while(adj_v->next !=NULL){
      adj_v = adj_v->next;
    }
    adj_v = adj_v->next = malloc(sizeof(adj_vertex_t)); //create new adj_vertex_t after the last exiting one
    adj_v->vertex = to;
    adj_v->edge_weight = weight;
    adj_v->next = NULL;
    *head = adj_v;
  }
  
}

void add_edge (vertex_t **vtxhead, char *v1_name, char *v2_name, int weight) {
	/* add your implementation here */
  vertex_t *head = *vtxhead;
  vertex_t *v1, *v2, *vt;
  adj_vertex_t *adj_v;

  if(head==NULL){
    head =  v1 = malloc(sizeof(vertex_t));
    *vtxhead = head;
    v1->name = v1_name;
    v2 = malloc(sizeof(vertex_t));
    v2->name = v2_name;
    
    v1->next = v2;
    v2->next = NULL;
    
    adj_v = v1->adj_list;
    add_adj_vertex(&adj_v, v2, weight);
    v1->adj_list = adj_v;
    
    adj_v = v2->adj_list;
    add_adj_vertex(&adj_v, v1, weight);
    v2->adj_list = adj_v;
    
  }
  else{
    v1 = find_vertex(head, v1_name);
    v2 = find_vertex(head, v2_name);

    if(v1 == NULL){//v1 is a new vertex
      v1 = make_vertex(v1_name, NULL);
      
      /*find the last of vertex in the vertex list*/
      vt = v2;
      while(vt->next != NULL){
	vt = vt->next;
      }
      vt->next = v1; //put new vertex v1 after it
      
      adj_v = v1->adj_list;
      add_adj_vertex(&adj_v, v2, weight);
      v1->adj_list = adj_v;

      adj_v = v2->adj_list;
      add_adj_vertex(&adj_v, v1, weight);
    }
    else if(v2 == NULL){//v2 is a new vertex
      v2 = make_vertex(v2_name, NULL);

      vt = v1;
      while(vt->next != NULL){
	vt = vt->next;
      }
      vt->next = v2;

      adj_v = v1->adj_list;
      add_adj_vertex(&adj_v, v2, weight);

      adj_v = v2->adj_list;
      add_adj_vertex(&adj_v, v1, weight);
      v2->adj_list = adj_v;
    }
    else{//both of v1, v2 are exiting in the graph
      adj_v = v1->adj_list;
      add_adj_vertex(&adj_v, v2, weight);
      adj_v = v2->adj_list;
      add_adj_vertex(&adj_v, v1, weight);
    }/*both are already in the graph*/
  
  }
  
}


int find_tour(vertex_t *start, vertex_t *visited[], int num_city, int num_remain){
  if(num_remain == 1){
    visited[num_city-1] = start;
    return 0;
  }
  else{
    int i, length;
    adj_vertex_t *adj;
    char *cur_name;
    for(adj = start->adj_list; adj != NULL; adj = adj->next){
      cur_name = adj->vertex->name;
      for(i = 0; i<(num_city-num_remain) ; i++){
	if(strcmp(cur_name, visited[i]->name)==0){
	  break;//have visited, go to next adj	
	}
      }
    
      if(i >= (num_city-num_remain)){
	visited[num_city-num_remain] = start;
	length = find_tour(adj->vertex, visited, num_city, num_remain-1);
	if(length != 0){
	  return adj->edge_weight + length;
	}
	else{
	  if(num_remain-1 == 1){
	    return adj->edge_weight;
	  }
	  else{
	    return 0;
	  }
	}
      }
    }
    return 0;
  }
}


void free_stuff(vertex_t *v){
  vertex_t *v_temp;
  adj_vertex_t *adj, *a_temp;
  
  while(v != NULL){
    adj = v->adj_list;
    while(adj != NULL){
      a_temp = adj->next;
      free(adj);
      adj = a_temp;
    }

    v_temp = v->next;
    free(v);
    v = v_temp;
  }
}
