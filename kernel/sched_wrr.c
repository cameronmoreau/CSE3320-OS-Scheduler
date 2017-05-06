/*
 * Weighted Round Robin Scheduling Class (mapped to the SCHED_WRR
 * policy)
 */


/* My shitty code begins here */

static void enqueue_task_wrr(struct rq *rq, struct task_struct *p, int wakeup)
{
	printk(KERN_EMERG "[WRR] Enqueue Task\n\t=> task: %ld\n\t=> n: %d", (unsigned long int)p, rq->wrr.num_running);
	
	//if(wakeup) &(p->wrr->timeout) = 0;

	list_add_tail(&(p->wrr.run_list), &(rq->wrr.ready_list));
	rq->wrr.num_running++;
}

static void dequeue_task_wrr(struct rq *rq, struct task_struct *p, int sleep)
{
	printk(KERN_EMERG "[WRR] Dequeue Task\n\t=> task: %ld\n\t=> n: %d", (unsigned long int)p, rq->wrr.num_running);

	list_del(&(p->wrr.run_list));
	rq->wrr.num_running--;
}

static void
requeue_wrr_entity(struct wrr_rq *wrr_rq, struct sched_wrr_entity *wrr_se, int head)
{
	printk(KERN_EMERG "[WRR] Requeue Entity\n");
}

static void requeue_task_wrr(struct rq *rq, struct task_struct *p, int head)
{
	printk(KERN_EMERG "[WRR] Requeue Task\n");
	
	list_move_tail(&(p->wrr.run_list), &(rq->wrr.ready_list));
}

static void yield_task_wrr(struct rq *rq)
{
	printk(KERN_EMERG "[WRR] Yield Task\n");
}
static void check_preempt_curr_wrr(struct rq *rq, struct task_struct *p, int flags)
{
	printk(KERN_EMERG "[WRR] Check Preempt Current\n");
}

static struct task_struct *pick_next_task_wrr(struct rq *rq)
{
	printk(KERN_EMERG "[WRR] Pick Next Task\n");
}

static void put_prev_task_wrr(struct rq *rq, struct task_struct *p)
{
	printk(KERN_EMERG "[WRR] Put Prev Task\n");
}

#ifdef CONFIG_SMP
static int select_task_rq_wrr(struct task_struct *p, int sd_flag, int flags)
{
	return task_cpu(p);
}

static unsigned long
load_balance_wrr(struct rq *this_rq, int this_cpu, struct rq *busiest,
                unsigned long max_load_move,
                struct sched_domain *sd, enum cpu_idle_type idle,
                int *all_pinned, int *this_best_prio)
{
        /* don't touch WRR tasks */
        return 0;
}

static int
move_one_task_wrr(struct rq *this_rq, int this_cpu, struct rq *busiest,
                 struct sched_domain *sd, enum cpu_idle_type idle)
{
	printk(KERN_EMERG "[WRR] Move one task\n");
	return 0;
}


#endif
static void set_curr_task_wrr(struct rq *rq)
{
	struct task_struct *p = rq->curr;

	p->se.exec_start = rq->clock;
}

static void task_tick_wrr(struct rq *rq, struct task_struct *p, int queued)
{
	printk(KERN_EMERG "[WRR] Task Tick\n");
}

unsigned int get_rr_interval_wrr(struct task_struct *task)
{
        /*
 *          * Time slice is 0 for SCHED_FIFO tasks
 *                   */
        if (task->policy == SCHED_WRR)
                return DEF_TIMESLICE;
        else
                return 0;
}
/* added by Jia Rao: No preemption, so we leave this function empty */
static void prio_changed_wrr(struct rq *rq, struct task_struct *p,
                              int oldprio, int running)
{
}

static void switched_to_wrr(struct rq *rq, struct task_struct *p,
                           int running)
{
	printk(KERN_EMERG "[WRR] Switched to WRR\n");
}

static const struct sched_class wrr_sched_class = {
	.next			= &fair_sched_class,
	.enqueue_task		= enqueue_task_wrr,
	.dequeue_task		= dequeue_task_wrr,
	.yield_task		= yield_task_wrr,

	.check_preempt_curr	= check_preempt_curr_wrr,

	.pick_next_task		= pick_next_task_wrr,
	.put_prev_task		= put_prev_task_wrr,

#ifdef CONFIG_SMP
	.select_task_rq		= select_task_rq_wrr,

	.load_balance		= load_balance_wrr,
	.move_one_task		= move_one_task_wrr,
#endif

	.set_curr_task          = set_curr_task_wrr,
	.task_tick		= task_tick_wrr,

	.get_rr_interval	= get_rr_interval_wrr,

//	.prio_changed		= prio_changed_wrr,
	.switched_to		= switched_to_wrr,
};

