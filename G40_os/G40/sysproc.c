#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "processInfo.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int
sys_draw(void)
{
  void* buf;
  uint size;

  argptr(0, (void*)&buf, sizeof(buf));
  argptr(1, (void*)&size, sizeof(size));

  char text[] = "DRAW :- \n\
                                 ,ood8888booo,\n\
                              ,od8           8bo,\n\
                           ,od                   bo,\n\
                         ,d8                       8b,\n\
                        ,o                           o,    ,a8b\n\
                       ,8                             8,,od8  8\n\
                       8'                             d8'     8b\n\
                       8                           d8'ba     aP'\n\
                       Y,                       o8'         aP'\n\
                        Y8,                      YaaaP'    ba\n\
                         Y8o                   Y8'         88\n\
                          `Y8               ,8\"           `P\n\
                            Y8o        ,d8P'              ba\n\
                       ooood8888888P\"\"\"'                  P'\n\
                    ,od                                  8\n\
                 ,dP     o88o                           o'\n\
                ,dP          8                          8\n\
               ,d'   oo       8                       ,8\n\
               $    d$\"8      8           Y    Y  o   8\n\
              d    d  d8    od  \"\"zeus<3nezu   d\"\" 8   8\n\
              $    8  d   ood' ,   8        b  8   '8  b\n\
              $   $  8  8     d  d8        `b  d    '8  b\n\
               $  $ 8   b    Y  d8          8 ,P     '8  b\n\
               `$$  Yb  b     8b 8b         8 8,      '8  o,\n\
                    `Y  b      8o  $$o      d  b        b   $o\n\
                     8   '$     8$,,$\"      $   $o      '$o$$\n\
                      $o$$P\"                 $$o$\n\n";
  if(sizeof(text)>size)
    return -1;

  strncpy((char *)buf, text, size);
  return sizeof(text);
}

int sys_getNumProc(void) 
{
   return getNumProc();
}
int sys_getMaxPid(void) 
{
   return getMaxPid();
}
int sys_getProcInfo(void) 
{
  int pid;
  struct processInfo *p;
  
  // storing the process id into pid from the user stack to the kernel space
  // 0 signifies that the first command line argument value is used for storing the value into pid 
   
  argptr(0,(void *)&pid,sizeof(pid));

  // storing the processInfo into struct p from the user stack to the kernel space
  // 1 signifies that the second command line argument value is used for storing the value into p
  
  argptr(1,(void *)&p,sizeof(p));
	
  return getProcInfo(pid, p);
}

int sys_set_burst_time(void)
{
        // get the burst time from the user space to the kernel space
	int BurstTime;
  
        if(argint(0,&BurstTime)<0)  // if the pointer doesn't lie within the process address space, return -1
	 return -1;

	return set_burst_time(BurstTime);
}

int sys_get_burst_time(void)
{
    // function is called from proc.c from which the kernel code returns the burst time of currently running process                         
    return get_burst_time();                                                        
}
int sys_yield(void) 
{
    yield();  // puts a process from RUNNING to RUNNABLE
    return 0;
}
int sys_pstate(void)
{
    // returns the processes and their status
    return pstate();
}




