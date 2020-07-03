#include "cachelab.h"
#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>

// my BU ID: 13430513                                                                 
// Divya Gowravaram                                                                   
// worked with Olivia Pope                                                            

char *trace_file = NULL;

int verbose = 0;
int count;
int accesses;
int hit;
int miss;
int evict;
int flag;

struct Cache * makeCache(){

  return NULL;
}

typedef struct CacheSets{
  struct CacheLines *my_set;
  unsigned int index;
} set;

set *my_cache; // this is an array of sets                                            

typedef struct CacheLines{
  int valid;
  int lastUsed;
  int tag;
} line;

struct Cache{
  struct CacheSets *set;
  struct CacheLines *line;
};

int set_bits;
int associativity;
int offset_bits;


void create_cache(int set_bits, int associativity, int offset_bits){
  // create a cache data structure                                                    
  // cache = array (pointer) of sets                                                  
  // set = array of blocks. has an index                                              
  // block = array of bytes. block = tag, valid bit, least recently used index        
  int num_sets = 1 << set_bits;
  int assoc = associativity;
  int bytes = 1 << offset_bits;

  printf("sets: %d, assoc: %d, bytes: %d\n", num_sets, assoc, bytes);

  my_cache = (set *) malloc(num_sets * sizeof(set));
  int i;
  int j;

  for(i=0; i<num_sets; i++){
    my_cache[i].index = i;
    my_cache[i].my_set = (line *) malloc(assoc * sizeof(line));
    for(j=0; j<assoc; j++){
      my_cache[i].my_set[j].valid = -1;
      my_cache[i].my_set[j].lastUsed = -1;
      my_cache[i].my_set[j].tag = -1;
    }
  }


}

int evictCache(int set_index, int tag){
  int myLRU = my_cache[set_index].my_set[0].lastUsed;
  int LRUindex;
  int k;

  for(k=0; k<associativity; k++){
    if(myLRU > my_cache[set_index].my_set[k].lastUsed){
      LRUindex = k;
      myLRU = my_cache[set_index].my_set[k].lastUsed;
    }
  }
  return LRUindex;
}

int isFull(int set_index){

  for(int j = 0; j<associativity; j++){
    if(my_cache[set_index].my_set[j].valid!=1){
      return 0;
    }
  }
  return 1;
}

void access_cache(unsigned int set_index, int tag, int E){


  printf("this is inital tag %d\n", my_cache[set_index].my_set[1].tag);
  for(int k = 0; k<E; k++){
    if(my_cache[set_index].my_set[k].valid!=1){
      miss++;
      printf("MISS\n");
      my_cache[set_index].my_set[k].valid = 1;
      my_cache[set_index].my_set[k].tag = tag;
      my_cache[set_index].my_set[k].lastUsed = k;

      break;
    }

    else{
      if(my_cache[set_index].my_set[k].tag == tag)
	{
	  hit++;
	  printf("HIT!!\n");

	  my_cache[set_index].my_set[k].lastUsed = k;

	  break;
	}

      else {
	miss++;
	printf("isFull = %d\n", isFull(set_index));
	my_cache[set_index].my_set[k].lastUsed = k;

	if(isFull(set_index)!=0){

	  evictCache(set_index, tag);
	  evict++;
	  printf("EVICTION!!\n");
	  my_cache[set_index].my_set[k].tag=tag;
	  break;
	}
	break;

      }

    }



  }
}

int main(int argc, char ** argv){


  int set_bits = 0;
  int associativity = 0;
  int offset_bits = 0;


  char opt;

  while(1){
    opt = getopt(argc, argv, "vhs:E:b:t:");
    if(opt == -1) break;


    switch(opt){
    case 's':
      set_bits = atoi(optarg);
      break;
    case 'E':
      associativity = atoi(optarg);
      break;
    case 'b':
      offset_bits = atoi(optarg);
      break;
    case 't':
      trace_file = optarg;
      break;
    case 'v':
      verbose = 1;
      break;
    }}

  if(verbose){
    printf("set_bits: %d, associativity: %d, offset_bits: %d, trace_file: %s\n", set_\
	   bits,
           associativity, offset_bits, trace_file);
  }

  if(set_bits == 0 || associativity == 0 || offset_bits == 0 || trace_file == 0){
    fprintf(stderr, "ERROR: must specify s, E, b, and trace file\n");
    return 0;
  }

  // create the cache:                                                                
  create_cache(set_bits, associativity, offset_bits);

  // open trace file                                                                    
  FILE *tfile;
  tfile = fopen(trace_file, "r");
  if(tfile==NULL){
    fprintf(stderr, "ERROR: fopen failed\n");
    return(0);
  }

  // read from trace file                                                             
  char op;
  unsigned int addr;
  unsigned int size;
  unsigned int set_index;
  int tag;


  // loop thru file:                                                                    
  int rc;
  while(1){
    rc = fscanf(tfile, " %c %x, %d\n", &op, &addr, &size);
    if(rc==EOF) break;
    printf("\n op: %c, addr: %x, size: %d\n", op, addr, size);

    // grab set_index and tag from addr                                           

    set_index = (addr >> offset_bits) & ((1 << set_bits)-1);
    printf("this is set_index %d\n", set_index);
    tag = addr >> (set_bits + offset_bits);

    printf("set index: %d, tag: %d\n", set_index, tag);
    // access cache based on file command                                         

    if(op=='M'){
      // access cache twice                                                 
      access_cache(set_index, tag, associativity);
      access_cache(set_index, tag, associativity);
    }
    else{

      if(op=='L'){

	access_cache(set_index, tag, associativity);
      }


      if(op=='S'){
	access_cache(set_index, tag, associativity);

      }
    }


  }


  printSummary(hit, miss, evict);
  return 0;
}



