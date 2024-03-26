4150 #include "types.h"
4151 #include "defs.h"
4152 #include "param.h"
4153 #include "spinlock.h"
4154 #include "sleeplock.h"
4155 #include "fs.h"
4156 #include "buf.h"
4157 
4158 // Simple logging that allows concurrent FS system calls.
4159 //
4160 // A log transaction contains the updates of multiple FS system
4161 // calls. The logging system only commits when there are
4162 // no FS system calls active. Thus there is never
4163 // any reasoning required about whether a commit might
4164 // write an uncommitted system call's updates to disk.
4165 //
4166 // A system call should call begin_op()/end_op() to mark
4167 // its start and end. Usually begin_op() just increments
4168 // the count of in-progress FS system calls and returns.
4169 // But if it thinks the log is close to running out, it
4170 // sleeps until the last outstanding end_op() commits.
4171 //
4172 // The log is a physical re-do log containing disk blocks.
4173 // The on-disk log format:
4174 //   header block, containing block #s for block A, B, C, ...
4175 //   block A
4176 //   block B
4177 //   block C
4178 //   ...
4179 // Log appends are synchronous.
4180 
4181 // Contents of the header block, used for both the on-disk header block
4182 // and to keep track in memory of logged block# before commit.
4183 struct logheader {
4184   int n;
4185   int block[LOGSIZE];
4186 };
4187 
4188 struct log {
4189   struct spinlock lock;
4190   int start;
4191   int size;
4192   int outstanding; // how many FS sys calls are executing.
4193   int committing;  // in commit(), please wait.
4194   int dev;
4195   struct logheader lh;
4196 };
4197 
4198 
4199 
4200 struct log log;
4201 
4202 static void recover_from_log(void);
4203 static void commit();
4204 
4205 void
4206 initlog(int dev)
4207 {
4208   if (sizeof(struct logheader) >= BSIZE)
4209     panic("initlog: too big logheader");
4210 
4211   struct superblock sb;
4212   initlock(&log.lock, "log");
4213   readsb(dev, &sb);
4214   log.start = sb.logstart;
4215   log.size = sb.nlog;
4216   log.dev = dev;
4217   recover_from_log();
4218 }
4219 
4220 // Copy committed blocks from log to their home location
4221 static void
4222 install_trans(void)
4223 {
4224   int tail;
4225 
4226   for (tail = 0; tail < log.lh.n; tail++) {
4227     struct buf *lbuf = bread(log.dev, log.start+tail+1); // read log block
4228     struct buf *dbuf = bread(log.dev, log.lh.block[tail]); // read dst
4229     memmove(dbuf->data, lbuf->data, BSIZE);  // copy block to dst
4230     bwrite(dbuf);  // write dst to disk
4231     brelse(lbuf);
4232     brelse(dbuf);
4233   }
4234 }
4235 
4236 // Read the log header from disk into the in-memory log header
4237 static void
4238 read_head(void)
4239 {
4240   struct buf *buf = bread(log.dev, log.start);
4241   struct logheader *lh = (struct logheader *) (buf->data);
4242   int i;
4243   log.lh.n = lh->n;
4244   for (i = 0; i < log.lh.n; i++) {
4245     log.lh.block[i] = lh->block[i];
4246   }
4247   brelse(buf);
4248 }
4249 
4250 // Write in-memory log header to disk.
4251 // This is the true point at which the
4252 // current transaction commits.
4253 static void
4254 write_head(void)
4255 {
4256   struct buf *buf = bread(log.dev, log.start);
4257   struct logheader *hb = (struct logheader *) (buf->data);
4258   int i;
4259   hb->n = log.lh.n;
4260   for (i = 0; i < log.lh.n; i++) {
4261     hb->block[i] = log.lh.block[i];
4262   }
4263   bwrite(buf);
4264   brelse(buf);
4265 }
4266 
4267 static void
4268 recover_from_log(void)
4269 {
4270   read_head();
4271   install_trans(); // if committed, copy from log to disk
4272   log.lh.n = 0;
4273   write_head(); // clear the log
4274 }
4275 
4276 // called at the start of each FS system call.
4277 void
4278 begin_op(void)
4279 {
4280   acquire(&log.lock);
4281   while(1){
4282     if(log.committing){
4283       sleep(&log, &log.lock);
4284     } else if(log.lh.n + (log.outstanding+1)*MAXOPBLOCKS > LOGSIZE){
4285       // this op might exhaust log space; wait for commit.
4286       sleep(&log, &log.lock);
4287     } else {
4288       log.outstanding += 1;
4289       release(&log.lock);
4290       break;
4291     }
4292   }
4293 }
4294 
4295 
4296 
4297 
4298 
4299 
4300 // called at the end of each FS system call.
4301 // commits if this was the last outstanding operation.
4302 void
4303 end_op(void)
4304 {
4305   int do_commit = 0;
4306 
4307   acquire(&log.lock);
4308   log.outstanding -= 1;
4309   if(log.committing)
4310     panic("log.committing");
4311   if(log.outstanding == 0){
4312     do_commit = 1;
4313     log.committing = 1;
4314   } else {
4315     // begin_op() may be waiting for log space.
4316     wakeup(&log);
4317   }
4318   release(&log.lock);
4319 
4320   if(do_commit){
4321     // call commit w/o holding locks, since not allowed
4322     // to sleep with locks.
4323     commit();
4324     acquire(&log.lock);
4325     log.committing = 0;
4326     wakeup(&log);
4327     release(&log.lock);
4328   }
4329 }
4330 
4331 // Copy modified blocks from cache to log.
4332 static void
4333 write_log(void)
4334 {
4335   int tail;
4336 
4337   for (tail = 0; tail < log.lh.n; tail++) {
4338     struct buf *to = bread(log.dev, log.start+tail+1); // log block
4339     struct buf *from = bread(log.dev, log.lh.block[tail]); // cache block
4340     memmove(to->data, from->data, BSIZE);
4341     bwrite(to);  // write the log
4342     brelse(from);
4343     brelse(to);
4344   }
4345 }
4346 
4347 
4348 
4349 
4350 static void
4351 commit()
4352 {
4353   if (log.lh.n > 0) {
4354     write_log();     // Write modified blocks from cache to log
4355     write_head();    // Write header to disk -- the real commit
4356     install_trans(); // Now install writes to home locations
4357     log.lh.n = 0;
4358     write_head();    // Erase the transaction from the log
4359   }
4360 }
4361 
4362 // Caller has modified b->data and is done with the buffer.
4363 // Record the block number and pin in the cache with B_DIRTY.
4364 // commit()/write_log() will do the disk write.
4365 //
4366 // log_write() replaces bwrite(); a typical use is:
4367 //   bp = bread(...)
4368 //   modify bp->data[]
4369 //   log_write(bp)
4370 //   brelse(bp)
4371 void
4372 log_write(struct buf *b)
4373 {
4374   int i;
4375 
4376   if (log.lh.n >= LOGSIZE || log.lh.n >= log.size - 1)
4377     panic("too big a transaction");
4378   if (log.outstanding < 1)
4379     panic("log_write outside of trans");
4380 
4381   acquire(&log.lock);
4382   for (i = 0; i < log.lh.n; i++) {
4383     if (log.lh.block[i] == b->blockno)   // log absorbtion
4384       break;
4385   }
4386   log.lh.block[i] = b->blockno;
4387   if (i == log.lh.n)
4388     log.lh.n++;
4389   b->flags |= B_DIRTY; // prevent eviction
4390   release(&log.lock);
4391 }
4392 
4393 
4394 
4395 
4396 
4397 
4398 
4399 
