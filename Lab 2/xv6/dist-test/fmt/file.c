5150 //
5151 // File descriptors
5152 //
5153 
5154 #include "types.h"
5155 #include "defs.h"
5156 #include "param.h"
5157 #include "fs.h"
5158 #include "spinlock.h"
5159 #include "sleeplock.h"
5160 #include "file.h"
5161 
5162 struct devsw devsw[NDEV];
5163 struct {
5164   struct spinlock lock;
5165   struct file file[NFILE];
5166 } ftable;
5167 
5168 void
5169 fileinit(void)
5170 {
5171   initlock(&ftable.lock, "ftable");
5172 }
5173 
5174 // Allocate a file structure.
5175 struct file*
5176 filealloc(void)
5177 {
5178   struct file *f;
5179 
5180   acquire(&ftable.lock);
5181   for(f = ftable.file; f < ftable.file + NFILE; f++){
5182     if(f->ref == 0){
5183       f->ref = 1;
5184       release(&ftable.lock);
5185       return f;
5186     }
5187   }
5188   release(&ftable.lock);
5189   return 0;
5190 }
5191 
5192 
5193 
5194 
5195 
5196 
5197 
5198 
5199 
5200 // Increment ref count for file f.
5201 struct file*
5202 filedup(struct file *f)
5203 {
5204   acquire(&ftable.lock);
5205   if(f->ref < 1)
5206     panic("filedup");
5207   f->ref++;
5208   release(&ftable.lock);
5209   return f;
5210 }
5211 
5212 // Close file f.  (Decrement ref count, close when reaches 0.)
5213 void
5214 fileclose(struct file *f)
5215 {
5216   struct file ff;
5217 
5218   acquire(&ftable.lock);
5219   if(f->ref < 1)
5220     panic("fileclose");
5221   if(--f->ref > 0){
5222     release(&ftable.lock);
5223     return;
5224   }
5225   ff = *f;
5226   f->ref = 0;
5227   f->type = FD_NONE;
5228   release(&ftable.lock);
5229 
5230   if(ff.type == FD_PIPE)
5231     pipeclose(ff.pipe, ff.writable);
5232   else if(ff.type == FD_INODE){
5233     begin_op();
5234     iput(ff.ip);
5235     end_op();
5236   }
5237 }
5238 
5239 
5240 
5241 
5242 
5243 
5244 
5245 
5246 
5247 
5248 
5249 
5250 // Get metadata about file f.
5251 int
5252 filestat(struct file *f, struct stat *st)
5253 {
5254   if(f->type == FD_INODE){
5255     ilock(f->ip);
5256     stati(f->ip, st);
5257     iunlock(f->ip);
5258     return 0;
5259   }
5260   return -1;
5261 }
5262 
5263 // Read from file f.
5264 int
5265 fileread(struct file *f, char *addr, int n)
5266 {
5267   int r;
5268 
5269   if(f->readable == 0)
5270     return -1;
5271   if(f->type == FD_PIPE)
5272     return piperead(f->pipe, addr, n);
5273   if(f->type == FD_INODE){
5274     ilock(f->ip);
5275     if((r = readi(f->ip, addr, f->off, n)) > 0)
5276       f->off += r;
5277     iunlock(f->ip);
5278     return r;
5279   }
5280   panic("fileread");
5281 }
5282 
5283 // Write to file f.
5284 int
5285 filewrite(struct file *f, char *addr, int n)
5286 {
5287   int r;
5288 
5289   if(f->writable == 0)
5290     return -1;
5291   if(f->type == FD_PIPE)
5292     return pipewrite(f->pipe, addr, n);
5293   if(f->type == FD_INODE){
5294     // write a few blocks at a time to avoid exceeding
5295     // the maximum log transaction size, including
5296     // i-node, indirect block, allocation blocks,
5297     // and 2 blocks of slop for non-aligned writes.
5298     // this really belongs lower down, since writei()
5299     // might be writing a device like the console.
5300     int max = ((LOGSIZE-1-1-2) / 2) * 512;
5301     int i = 0;
5302     while(i < n){
5303       int n1 = n - i;
5304       if(n1 > max)
5305         n1 = max;
5306 
5307       begin_op();
5308       ilock(f->ip);
5309       if ((r = writei(f->ip, addr + i, f->off, n1)) > 0)
5310         f->off += r;
5311       iunlock(f->ip);
5312       end_op();
5313 
5314       if(r < 0)
5315         break;
5316       if(r != n1)
5317         panic("short filewrite");
5318       i += r;
5319     }
5320     return i == n ? n : -1;
5321   }
5322   panic("filewrite");
5323 }
5324 
5325 
5326 
5327 
5328 
5329 
5330 
5331 
5332 
5333 
5334 
5335 
5336 
5337 
5338 
5339 
5340 
5341 
5342 
5343 
5344 
5345 
5346 
5347 
5348 
5349 
