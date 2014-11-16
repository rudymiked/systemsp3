#define LINE = 20;
#define JOB_MAX = 20;
int job_number;

struct job {
	int pid;
	int job_id;
    int state;
    char cmdline[LINE];
};



int addjob(struct job *run, int pid, int state) 
{
    int status = 1;
    if (pid < 1)
	status = 0;

    for (i = 0; i < JOB_NUM; i++) {
	if (run[i].pid == 0) {
	    run[i].pid = pid;
	    run[i].state = state;
	    run[i].job_id = job_number;
		job_number++;}

    return status;
}

