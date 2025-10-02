#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define DATA_SIZE (1 << 16)  //65536 elements
int numbers[DATA_SIZE];      //global array




void process_array(int workers) {
  if (workers <= 0 || workers >= 16) {
    printf("Invalid worker count. Must be between 1 and 15.\n");
    return;
  }
  int worker_pids[16];  // Array to store worker PIDs
  //initialize array 
  for (int i = 0; i < DATA_SIZE; i++) {
    numbers[i] = i;
  }
  //create worker processes
  int result = forkn(workers, worker_pids);
  if (result == -1) {
    printf("Failed to create worker processes.\n");
    return;
  }
  //child worker process - compute partial sum
  if (result >= 1) {
    int worker_id = result;
    int chunk_size = DATA_SIZE / workers;
    int start_idx = (worker_id - 1) * chunk_size;
    int end_idx;
    //handle uneven division - distribute remainder elements
    if (worker_id == workers) {
      end_idx = DATA_SIZE;  //last worker gets remaining elements
    } else {
      end_idx = start_idx + chunk_size;
    }
    //calculate partial sum
    int partial_sum = 0;
    for (int i = start_idx; i < end_idx; i++) {
      partial_sum += numbers[i];
    }
    //add small delay for readability
    sleep(worker_id * 10);
    printf("Worker %d processed elements %d to %d, sum = %d\n", 
           worker_id, start_idx, end_idx - 1, partial_sum);   
    //return sum as exit status
    exit(partial_sum, "");
  }
  //parent process code
  printf("Parent created %d workers:\n", workers);
  for (int i = 0; i < workers; i++) {
    printf("  Worker %d: PID %d\n", i+1, worker_pids[i]);
  }
  //wait for all workers to complete
  int finished_count;
  int exit_values[16];
  if (waitall(&finished_count, exit_values) != 0) {
    printf("Error waiting for worker processes\n");
    exit(1, "Processing failed");
  }
  //ensure we got results from all workers
  if (finished_count != workers) {
    printf("Expected %d results but got %d\n", workers, finished_count);
    exit(1, "Incomplete results");
  }
  //sum all partial sums
  int total = 0;
  for (int i = 0; i < finished_count; i++) {
    total += exit_values[i];
  }
  printf("Total sum of all elements: %d\n", total);
  //verify with formula: sum of 0 to n-1 = n*(n-1)/2
  long expected = ((long)DATA_SIZE * (DATA_SIZE - 1)) / 2;
  if (total == expected) {
    printf("Result verified correct! (Formula = %ld)\n", expected);
  } else {
    printf("Result mismatch! Expected: %ld\n", expected);
  }
}


int main(int argc, char *argv[]) {
  int worker_count = 4;  //default is 4 workers
  //optional: Use command line argument for worker count
  if (argc > 1) {
    worker_count = atoi(argv[1]);
  }
  process_array(worker_count);
  exit(0, "Process completed");
}
