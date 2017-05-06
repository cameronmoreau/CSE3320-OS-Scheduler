#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/pid.h>

asmlinkage int sys_get_wrr_weight(int pid) {
	struct task_struct *task = find_task_by_vpid(pid);
	if(task == NULL) return -1;
	return task->wrr.weight;
}
