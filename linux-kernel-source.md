Linux Kernel Source Code
------------------------

Getting It
==========

* Git
  * https://github.com/torvalds/linux
  * Clone Command: `git clone https://github.com/torvalds/linux.git`
* Download
  * `curl -LO https://github.com/torvalds/linux/archive/v4.4.zip`
  * Unzip it using the command `unzip v4.4.zip`

Searching It
============

* Linux Cross Reference (LXR)
  * http://lxr.free-electrons.com/

Key Locations
=============

* `task_struct`: Generic thread information struct, used on all platforms.
  * include/linux/sched.h
* `thread_info`: Architecture specific thread information struct. Essentially a subclass of `task_struct`.
  * arch/x86/include/asm/thread_info.h
* `do_fork(...)`: Primary forking function.
  * kernel/fork.c
* `forget_original_parent(...)`: Reparents a task after its parent task has exited.
  * kernel/exit.c
* `context_switch(...)`: Main context switch function.
  * kernel/sched/core.c
