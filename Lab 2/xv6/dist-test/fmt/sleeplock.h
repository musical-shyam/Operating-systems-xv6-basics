3400 // Long-term locks for processes
3401 struct sleeplock {
3402   uint locked;       // Is the lock held?
3403   struct spinlock lk; // spinlock protecting this sleep lock
3404 
3405   // For debugging:
3406   char *name;        // Name of lock.
3407   int pid;           // Process holding lock
3408 };
3409 
3410 
3411 
3412 
3413 
3414 
3415 
3416 
3417 
3418 
3419 
3420 
3421 
3422 
3423 
3424 
3425 
3426 
3427 
3428 
3429 
3430 
3431 
3432 
3433 
3434 
3435 
3436 
3437 
3438 
3439 
3440 
3441 
3442 
3443 
3444 
3445 
3446 
3447 
3448 
3449 
