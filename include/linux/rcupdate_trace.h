/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Read-Copy Update mechanism for mutual exclusion, adapted for tracing.
 *
 * Copyright (C) 2020 Paul E. McKenney.
 */

#ifndef __LINUX_RCUPDATE_TRACE_H
#define __LINUX_RCUPDATE_TRACE_H

#include <linux/sched.h>
#include <linux/rcupdate.h>

#ifdef CONFIG_DEBUG_LOCK_ALLOC

extern struct lockdep_map rcu_trace_lock_map;

static inline int rcu_read_lock_trace_held(void)
{
	return lock_is_held(&rcu_trace_lock_map);
}

#else /* #ifdef CONFIG_DEBUG_LOCK_ALLOC */

static inline int rcu_read_lock_trace_held(void)
{
	return 1;
}

#endif /* #else #ifdef CONFIG_DEBUG_LOCK_ALLOC */

static inline void rcu_read_lock_trace(void)
{
	rcu_read_lock();
}

static inline void rcu_read_unlock_trace(void)
{
	rcu_read_unlock();
}

#ifdef CONFIG_TASKS_TRACE_RCU
void call_rcu_tasks_trace(struct rcu_head *rhp, rcu_callback_t func);
void synchronize_rcu_tasks_trace(void);
void rcu_barrier_tasks_trace(void);
#else
static inline void call_rcu_tasks_trace(struct rcu_head *rhp, rcu_callback_t func)
{
	call_rcu(rhp, func);
}
static inline void synchronize_rcu_tasks_trace(void)
{
	synchronize_rcu();
}
static inline void rcu_barrier_tasks_trace(void)
{
	rcu_barrier();
}
#endif

#endif /* __LINUX_RCUPDATE_TRACE_H */
