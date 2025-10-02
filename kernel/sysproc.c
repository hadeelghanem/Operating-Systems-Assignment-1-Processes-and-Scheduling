#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
#include "syscall.h"

extern struct proc proc[NPROC];

uint64
sys_exit(void)
{
  int n;
  char exitmsg[32];
  argint(0, &n);
  if(argstr(1, exitmsg, sizeof(exitmsg)) < 0) {
    exitmsg[0] = '\0';
  }
  exit(n,exitmsg);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  uint64 msg; // added ,Task 3
  argaddr(0, &p);
  argaddr(1,&msg);
  return wait(p, msg);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int n;

  argint(0, &n);
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(killed(myproc())){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

//added,Task2 
uint64
sys_memsize(void)
{
  return myproc() ->sz;  // Return memsize
}


//task 4
uint64
sys_forkn(void)
{
  int x;
  uint64 pids_addr;
  argint(0, &x);
  argaddr(1, &pids_addr);
  
  
  //validate parameters
  if(x < 1 || x > 16 || pids_addr == 0)
    return -1;
    
  return forkn(x, (int*)pids_addr);
}

//task 4
uint64
sys_waitall(void)
{
  uint64 n_addr;
  uint64 statuses_addr;
  argaddr(0, &n_addr);
  argaddr(1, &statuses_addr);
  
    
  return waitall(n_addr, statuses_addr);
}