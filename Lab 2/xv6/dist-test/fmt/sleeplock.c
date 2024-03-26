4050 // Sleeping locks
4051 
4052 #include "types.h"
4053 #include "defs.h"
4054 #include "param.h"
4055 #include "x86.h"
4056 #include "memlayout.h"
4057 #include "mmu.h"
4058 #include "proc.h"
4059 #include "spinlock.h"
4060 #include "sleeplock.h"
4061 
4062 void
4063 initsleeplock(struct sleeplock *lk, char *name)
4064 {
4065   initlock(&lk->lk, "sleep lock");
4066   lk->name = name;
4067   lk->locked = 0;
4068   lk->pid = 0;
4069 }
4070 
4071 void
4072 acquiresleep(struct sleeplock *lk)
4073 {
4074   acquire(&lk->lk);
4075   while (lk->locked) {
4076     sleep(lk, &lk->lk);
4077   }
4078   lk->locked = 1;
4079   lk->pid = proc->pid;
4080   release(&lk->lk);
4081 }
4082 
4083 void
4084 releasesleep(struct sleeplock *lk)
4085 {
4086   acquire(&lk->lk);
4087   lk->locked = 0;
4088   lk->pid = 0;
4089   wakeup(lk);
4090   release(&lk->lk);
4091 }
4092 
4093 
4094 
4095 
4096 
4097 
4098 
4099 
4100 int
4101 holdingsleep(struct sleeplock *lk)
4102 {
4103   int r;
4104 
4105   acquire(&lk->lk);
4106   r = lk->locked;
4107   release(&lk->lk);
4108   return r;
4109 }
4110 
4111 
4112 
4113 
4114 
4115 
4116 
4117 
4118 
4119 
4120 
4121 
4122 
4123 
4124 
4125 
4126 
4127 
4128 
4129 
4130 
4131 
4132 
4133 
4134 
4135 
4136 
4137 
4138 
4139 
4140 
4141 
4142 
4143 
4144 
4145 
4146 
4147 
4148 
4149 
