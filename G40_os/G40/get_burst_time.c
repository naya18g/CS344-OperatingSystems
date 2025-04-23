#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char *argv[])
{
	// used from user.h which returns the burst time of the currently running process

	int t;
	t = get_burst_time();

	if (t < 1)
		printf(1, "The Burst Time cannot be set \n");
	else
		printf(1, "Burst Time = %d\n", t);

	exit();
}
