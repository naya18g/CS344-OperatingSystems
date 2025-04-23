#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char* argv[])
{	
	// argv[1] contains the burst time which needs to be set for the currently running process
	int n = atoi(argv[1]);
 
	// used from user.h which returns 0 if the burst time is set successfully; returns -1 otherwise
	int t = set_burst_time(n);

	if(t == -1) 
	 printf(1, "The Burst Time cannot be set \n");
	else 
	 printf(1, "The Burst Time has been set \n");
	exit();
}
