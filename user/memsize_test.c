#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int cur_size, size_after, last_size;
  char *memo;
  
  // a-current memory usage
  cur_size = memsize();
  printf("Current  process memory size is: %d bytes\n", cur_size);
  
  // b-Allocate 20K of memory
  memo = malloc(20480);
  if (memo == 0) {
    printf("malloc failed\n");
    exit(1,"");
  }
  
  // Write to the memory to ensure it's actually allocated
  for (int i = 0; i < 20480; i++) {
    memo[i] = 1;
  }
  // c-Print memory usage after allocation
  size_after = memsize();
  printf("Memory size after allocation is: %d bytes\n", size_after);
  // d-Free the allocated memory
  free(memo);
  // (e) Print memory usage after freeing
  last_size  = memsize();
  printf("Memory size after free: %d bytes\n", last_size);
  exit(0,"");
}