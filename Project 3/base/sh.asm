
_sh:     file format elf32-i386


Disassembly of section .text:

00000000 <main>:
  return 0;
}

int
main(void)
{
       0:	8d 4c 24 04          	lea    0x4(%esp),%ecx
       4:	83 e4 f0             	and    $0xfffffff0,%esp
       7:	ff 71 fc             	push   -0x4(%ecx)
       a:	55                   	push   %ebp
       b:	89 e5                	mov    %esp,%ebp
       d:	57                   	push   %edi
       e:	56                   	push   %esi
       f:	53                   	push   %ebx
      10:	51                   	push   %ecx
      11:	83 ec 08             	sub    $0x8,%esp
  static char buf[100];
  int fd;

  // Ensure that three file descriptors are open.
  while((fd = open("console", O_RDWR)) >= 0){
      14:	eb 13                	jmp    29 <main+0x29>
      16:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
      1d:	8d 76 00             	lea    0x0(%esi),%esi
    if(fd >= 3){
      20:	83 f8 02             	cmp    $0x2,%eax
      23:	0f 8f 4e 02 00 00    	jg     277 <main+0x277>
  while((fd = open("console", O_RDWR)) >= 0){
      29:	83 ec 08             	sub    $0x8,%esp
      2c:	6a 02                	push   $0x2
      2e:	68 f9 14 00 00       	push   $0x14f9
      33:	e8 eb 0f 00 00       	call   1023 <open>
      38:	83 c4 10             	add    $0x10,%esp
      3b:	85 c0                	test   %eax,%eax
      3d:	79 e1                	jns    20 <main+0x20>
        printf(2, "cannot cd %s\n", buf+3);
      continue;
    }
    if (!(buf[0] == 'h' && buf[1] == 'i' && buf[2] == 's' && buf[3] == 't' && buf[4] == ' ' ) && buf[0] != '\n') {
        strcpy(history[current_index], buf);
        current_index = (current_index + 1) % HISTORY_SIZE;
      3f:	bb 67 66 66 66       	mov    $0x66666667,%ebx
      44:	eb 31                	jmp    77 <main+0x77>
      46:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
      4d:	8d 76 00             	lea    0x0(%esi),%esi
    if (!(buf[0] == 'h' && buf[1] == 'i' && buf[2] == 's' && buf[3] == 't' && buf[4] == ' ' ) && buf[0] != '\n') {
      50:	3c 68                	cmp    $0x68,%al
      52:	0f 84 88 01 00 00    	je     1e0 <main+0x1e0>
      58:	3c 0a                	cmp    $0xa,%al
      5a:	75 6c                	jne    c8 <main+0xc8>
int
fork1(void)
{
  int pid;

  pid = fork();
      5c:	e8 7a 0f 00 00       	call   fdb <fork>
  if(pid == -1)
      61:	83 f8 ff             	cmp    $0xffffffff,%eax
      64:	0f 84 94 02 00 00    	je     2fe <main+0x2fe>
      if(fork1() == 0)
      6a:	85 c0                	test   %eax,%eax
      6c:	0f 84 16 02 00 00    	je     288 <main+0x288>
          wait();
      72:	e8 74 0f 00 00       	call   feb <wait>
  printf(2, "$ ");
      77:	83 ec 08             	sub    $0x8,%esp
      7a:	68 68 14 00 00       	push   $0x1468
      7f:	6a 02                	push   $0x2
      81:	e8 ba 10 00 00       	call   1140 <printf>
  memset(buf, 0, nbuf);
      86:	83 c4 0c             	add    $0xc,%esp
      89:	6a 64                	push   $0x64
      8b:	6a 00                	push   $0x0
      8d:	68 c0 1f 00 00       	push   $0x1fc0
      92:	e8 c9 0d 00 00       	call   e60 <memset>
  gets(buf, nbuf);
      97:	58                   	pop    %eax
      98:	5a                   	pop    %edx
      99:	6a 64                	push   $0x64
      9b:	68 c0 1f 00 00       	push   $0x1fc0
      a0:	e8 1b 0e 00 00       	call   ec0 <gets>
  if(buf[0] == 0) // EOF
      a5:	0f b6 05 c0 1f 00 00 	movzbl 0x1fc0,%eax
      ac:	83 c4 10             	add    $0x10,%esp
      af:	84 c0                	test   %al,%al
      b1:	0f 84 bb 01 00 00    	je     272 <main+0x272>
    if(buf[0] == 'c' && buf[1] == 'd' && buf[2] == ' '){
      b7:	3c 63                	cmp    $0x63,%al
      b9:	75 95                	jne    50 <main+0x50>
      bb:	80 3d c1 1f 00 00 64 	cmpb   $0x64,0x1fc1
      c2:	0f 84 58 01 00 00    	je     220 <main+0x220>
        strcpy(history[current_index], buf);
      c8:	6b 05 a4 1b 00 00 64 	imul   $0x64,0x1ba4,%eax
      cf:	83 ec 08             	sub    $0x8,%esp
      d2:	68 c0 1f 00 00       	push   $0x1fc0
      d7:	05 c0 1b 00 00       	add    $0x1bc0,%eax
      dc:	50                   	push   %eax
      dd:	e8 be 0c 00 00       	call   da0 <strcpy>
        current_index = (current_index + 1) % HISTORY_SIZE;
      e2:	a1 a4 1b 00 00       	mov    0x1ba4,%eax
        if (total_commands < HISTORY_SIZE) total_commands++;
      e7:	83 c4 10             	add    $0x10,%esp
        current_index = (current_index + 1) % HISTORY_SIZE;
      ea:	8d 48 01             	lea    0x1(%eax),%ecx
      ed:	89 c8                	mov    %ecx,%eax
      ef:	f7 eb                	imul   %ebx
      f1:	89 c8                	mov    %ecx,%eax
      f3:	c1 f8 1f             	sar    $0x1f,%eax
      f6:	c1 fa 02             	sar    $0x2,%edx
      f9:	29 c2                	sub    %eax,%edx
      fb:	8d 04 92             	lea    (%edx,%edx,4),%eax
      fe:	01 c0                	add    %eax,%eax
     100:	29 c1                	sub    %eax,%ecx
        if (total_commands < HISTORY_SIZE) total_commands++;
     102:	a1 a0 1b 00 00       	mov    0x1ba0,%eax
        current_index = (current_index + 1) % HISTORY_SIZE;
     107:	89 0d a4 1b 00 00    	mov    %ecx,0x1ba4
        if (total_commands < HISTORY_SIZE) total_commands++;
     10d:	83 f8 09             	cmp    $0x9,%eax
     110:	7f 08                	jg     11a <main+0x11a>
     112:	83 c0 01             	add    $0x1,%eax
     115:	a3 a0 1b 00 00       	mov    %eax,0x1ba0
    if (buf[0] == 'h' && buf[1] == 'i' && buf[2] == 's' && buf[3] == 't' && buf[4] == ' ' ) {
     11a:	80 3d c0 1f 00 00 68 	cmpb   $0x68,0x1fc0
     121:	0f 85 35 ff ff ff    	jne    5c <main+0x5c>
     127:	80 3d c1 1f 00 00 69 	cmpb   $0x69,0x1fc1
     12e:	0f 85 28 ff ff ff    	jne    5c <main+0x5c>
     134:	80 3d c2 1f 00 00 73 	cmpb   $0x73,0x1fc2
     13b:	0f 85 1b ff ff ff    	jne    5c <main+0x5c>
     141:	80 3d c3 1f 00 00 74 	cmpb   $0x74,0x1fc3
     148:	0f 85 0e ff ff ff    	jne    5c <main+0x5c>
     14e:	80 3d c4 1f 00 00 20 	cmpb   $0x20,0x1fc4
     155:	0f 85 01 ff ff ff    	jne    5c <main+0x5c>
      if (buf[5] == 'p' && buf[6] == 'r' && buf[7] == 'i' && buf[8] == 'n' && buf[9] == 't') {
     15b:	80 3d c5 1f 00 00 70 	cmpb   $0x70,0x1fc5
     162:	0f 85 35 01 00 00    	jne    29d <main+0x29d>
     168:	80 3d c6 1f 00 00 72 	cmpb   $0x72,0x1fc6
     16f:	0f 85 28 01 00 00    	jne    29d <main+0x29d>
     175:	80 3d c7 1f 00 00 69 	cmpb   $0x69,0x1fc7
     17c:	0f 85 1b 01 00 00    	jne    29d <main+0x29d>
     182:	80 3d c8 1f 00 00 6e 	cmpb   $0x6e,0x1fc8
     189:	0f 85 0e 01 00 00    	jne    29d <main+0x29d>
     18f:	80 3d c9 1f 00 00 74 	cmpb   $0x74,0x1fc9
     196:	0f 85 01 01 00 00    	jne    29d <main+0x29d>
        for (int i = 0; i < total_commands; i++) {
     19c:	31 ff                	xor    %edi,%edi
            int idx = (current_index - i - 1 + HISTORY_SIZE) % HISTORY_SIZE;
     19e:	be 0a 00 00 00       	mov    $0xa,%esi
     1a3:	eb 29                	jmp    1ce <main+0x1ce>
     1a5:	a1 a4 1b 00 00       	mov    0x1ba4,%eax
     1aa:	29 f8                	sub    %edi,%eax
            printf(2, "Previous command %d: %s", i + 1, history[idx]);
     1ac:	83 c7 01             	add    $0x1,%edi
            int idx = (current_index - i - 1 + HISTORY_SIZE) % HISTORY_SIZE;
     1af:	83 c0 09             	add    $0x9,%eax
     1b2:	99                   	cltd
     1b3:	f7 fe                	idiv   %esi
            printf(2, "Previous command %d: %s", i + 1, history[idx]);
     1b5:	6b c2 64             	imul   $0x64,%edx,%eax
     1b8:	05 c0 1b 00 00       	add    $0x1bc0,%eax
     1bd:	50                   	push   %eax
     1be:	57                   	push   %edi
     1bf:	68 0f 15 00 00       	push   $0x150f
     1c4:	6a 02                	push   $0x2
     1c6:	e8 75 0f 00 00       	call   1140 <printf>
     1cb:	83 c4 10             	add    $0x10,%esp
        for (int i = 0; i < total_commands; i++) {
     1ce:	39 3d a0 1b 00 00    	cmp    %edi,0x1ba0
     1d4:	7f cf                	jg     1a5 <main+0x1a5>
     1d6:	e9 9c fe ff ff       	jmp    77 <main+0x77>
     1db:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
     1df:	90                   	nop
    if (!(buf[0] == 'h' && buf[1] == 'i' && buf[2] == 's' && buf[3] == 't' && buf[4] == ' ' ) && buf[0] != '\n') {
     1e0:	80 3d c1 1f 00 00 69 	cmpb   $0x69,0x1fc1
     1e7:	0f 85 db fe ff ff    	jne    c8 <main+0xc8>
     1ed:	80 3d c2 1f 00 00 73 	cmpb   $0x73,0x1fc2
     1f4:	0f 85 ce fe ff ff    	jne    c8 <main+0xc8>
     1fa:	80 3d c3 1f 00 00 74 	cmpb   $0x74,0x1fc3
     201:	0f 85 c1 fe ff ff    	jne    c8 <main+0xc8>
     207:	80 3d c4 1f 00 00 20 	cmpb   $0x20,0x1fc4
     20e:	0f 85 b4 fe ff ff    	jne    c8 <main+0xc8>
     214:	e9 1b ff ff ff       	jmp    134 <main+0x134>
     219:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
    if(buf[0] == 'c' && buf[1] == 'd' && buf[2] == ' '){
     220:	80 3d c2 1f 00 00 20 	cmpb   $0x20,0x1fc2
     227:	0f 85 9b fe ff ff    	jne    c8 <main+0xc8>
      buf[strlen(buf)-1] = 0;  // chop \n
     22d:	83 ec 0c             	sub    $0xc,%esp
     230:	68 c0 1f 00 00       	push   $0x1fc0
     235:	e8 f6 0b 00 00       	call   e30 <strlen>
      if(chdir(buf+3) < 0)
     23a:	c7 04 24 c3 1f 00 00 	movl   $0x1fc3,(%esp)
      buf[strlen(buf)-1] = 0;  // chop \n
     241:	c6 80 bf 1f 00 00 00 	movb   $0x0,0x1fbf(%eax)
      if(chdir(buf+3) < 0)
     248:	e8 06 0e 00 00       	call   1053 <chdir>
     24d:	83 c4 10             	add    $0x10,%esp
     250:	85 c0                	test   %eax,%eax
     252:	0f 89 1f fe ff ff    	jns    77 <main+0x77>
        printf(2, "cannot cd %s\n", buf+3);
     258:	51                   	push   %ecx
     259:	68 c3 1f 00 00       	push   $0x1fc3
     25e:	68 01 15 00 00       	push   $0x1501
     263:	6a 02                	push   $0x2
     265:	e8 d6 0e 00 00       	call   1140 <printf>
     26a:	83 c4 10             	add    $0x10,%esp
     26d:	e9 05 fe ff ff       	jmp    77 <main+0x77>
  exit();
     272:	e8 6c 0d 00 00       	call   fe3 <exit>
      close(fd);
     277:	83 ec 0c             	sub    $0xc,%esp
     27a:	50                   	push   %eax
     27b:	e8 8b 0d 00 00       	call   100b <close>
      break;
     280:	83 c4 10             	add    $0x10,%esp
     283:	e9 b7 fd ff ff       	jmp    3f <main+0x3f>
        runcmd(parsecmd(buf));
     288:	83 ec 0c             	sub    $0xc,%esp
     28b:	68 c0 1f 00 00       	push   $0x1fc0
     290:	e8 9b 0a 00 00       	call   d30 <parsecmd>
     295:	89 04 24             	mov    %eax,(%esp)
     298:	e8 f3 00 00 00       	call   390 <runcmd>
        int cmd_number = atoi(buf + 5); // Convert the command number to an index
     29d:	83 ec 0c             	sub    $0xc,%esp
     2a0:	68 c5 1f 00 00       	push   $0x1fc5
     2a5:	e8 c6 0c 00 00       	call   f70 <atoi>
        if (cmd_number > 0 && cmd_number <= total_commands) {
     2aa:	83 c4 10             	add    $0x10,%esp
        int cmd_number = atoi(buf + 5); // Convert the command number to an index
     2ad:	89 c6                	mov    %eax,%esi
        if (cmd_number > 0 && cmd_number <= total_commands) {
     2af:	85 c0                	test   %eax,%eax
     2b1:	0f 8e c0 fd ff ff    	jle    77 <main+0x77>
     2b7:	39 05 a0 1b 00 00    	cmp    %eax,0x1ba0
     2bd:	0f 8c b4 fd ff ff    	jl     77 <main+0x77>
          int idx = (current_index - cmd_number + HISTORY_SIZE) % HISTORY_SIZE; 
     2c3:	8b 3d a4 1b 00 00    	mov    0x1ba4,%edi
          if(fork1() == 0){
     2c9:	e8 a2 00 00 00       	call   370 <fork1>
     2ce:	85 c0                	test   %eax,%eax
     2d0:	0f 85 9c fd ff ff    	jne    72 <main+0x72>
          int idx = (current_index - cmd_number + HISTORY_SIZE) % HISTORY_SIZE; 
     2d6:	89 f8                	mov    %edi,%eax
     2d8:	b9 0a 00 00 00       	mov    $0xa,%ecx
            runcmd(parsecmd(history[idx]));
     2dd:	83 ec 0c             	sub    $0xc,%esp
          int idx = (current_index - cmd_number + HISTORY_SIZE) % HISTORY_SIZE; 
     2e0:	29 f0                	sub    %esi,%eax
     2e2:	83 c0 0a             	add    $0xa,%eax
     2e5:	99                   	cltd
     2e6:	f7 f9                	idiv   %ecx
            runcmd(parsecmd(history[idx]));
     2e8:	6b c2 64             	imul   $0x64,%edx,%eax
     2eb:	05 c0 1b 00 00       	add    $0x1bc0,%eax
     2f0:	50                   	push   %eax
     2f1:	e8 3a 0a 00 00       	call   d30 <parsecmd>
     2f6:	89 04 24             	mov    %eax,(%esp)
     2f9:	e8 92 00 00 00       	call   390 <runcmd>
    panic("fork");
     2fe:	83 ec 0c             	sub    $0xc,%esp
     301:	68 6b 14 00 00       	push   $0x146b
     306:	e8 45 00 00 00       	call   350 <panic>
     30b:	66 90                	xchg   %ax,%ax
     30d:	66 90                	xchg   %ax,%ax
     30f:	90                   	nop

00000310 <getcmd>:
{
     310:	55                   	push   %ebp
     311:	89 e5                	mov    %esp,%ebp
     313:	56                   	push   %esi
     314:	53                   	push   %ebx
     315:	8b 5d 08             	mov    0x8(%ebp),%ebx
     318:	8b 75 0c             	mov    0xc(%ebp),%esi
  printf(2, "$ ");
     31b:	83 ec 08             	sub    $0x8,%esp
     31e:	68 68 14 00 00       	push   $0x1468
     323:	6a 02                	push   $0x2
     325:	e8 16 0e 00 00       	call   1140 <printf>
  memset(buf, 0, nbuf);
     32a:	83 c4 0c             	add    $0xc,%esp
     32d:	56                   	push   %esi
     32e:	6a 00                	push   $0x0
     330:	53                   	push   %ebx
     331:	e8 2a 0b 00 00       	call   e60 <memset>
  gets(buf, nbuf);
     336:	58                   	pop    %eax
     337:	5a                   	pop    %edx
     338:	56                   	push   %esi
     339:	53                   	push   %ebx
     33a:	e8 81 0b 00 00       	call   ec0 <gets>
  if(buf[0] == 0) // EOF
     33f:	83 c4 10             	add    $0x10,%esp
     342:	80 3b 01             	cmpb   $0x1,(%ebx)
     345:	19 c0                	sbb    %eax,%eax
}
     347:	8d 65 f8             	lea    -0x8(%ebp),%esp
     34a:	5b                   	pop    %ebx
     34b:	5e                   	pop    %esi
     34c:	5d                   	pop    %ebp
     34d:	c3                   	ret
     34e:	66 90                	xchg   %ax,%ax

00000350 <panic>:
{
     350:	55                   	push   %ebp
     351:	89 e5                	mov    %esp,%ebp
     353:	83 ec 0c             	sub    $0xc,%esp
  printf(2, "%s\n", s);
     356:	ff 75 08             	push   0x8(%ebp)
     359:	68 f5 14 00 00       	push   $0x14f5
     35e:	6a 02                	push   $0x2
     360:	e8 db 0d 00 00       	call   1140 <printf>
  exit();
     365:	e8 79 0c 00 00       	call   fe3 <exit>
     36a:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi

00000370 <fork1>:
{
     370:	55                   	push   %ebp
     371:	89 e5                	mov    %esp,%ebp
     373:	83 ec 08             	sub    $0x8,%esp
  pid = fork();
     376:	e8 60 0c 00 00       	call   fdb <fork>
  if(pid == -1)
     37b:	83 f8 ff             	cmp    $0xffffffff,%eax
     37e:	74 02                	je     382 <fork1+0x12>
  return pid;
}
     380:	c9                   	leave
     381:	c3                   	ret
    panic("fork");
     382:	83 ec 0c             	sub    $0xc,%esp
     385:	68 6b 14 00 00       	push   $0x146b
     38a:	e8 c1 ff ff ff       	call   350 <panic>
     38f:	90                   	nop

00000390 <runcmd>:
{
     390:	55                   	push   %ebp
     391:	89 e5                	mov    %esp,%ebp
     393:	53                   	push   %ebx
     394:	83 ec 14             	sub    $0x14,%esp
     397:	8b 5d 08             	mov    0x8(%ebp),%ebx
  if(cmd == 0)
     39a:	85 db                	test   %ebx,%ebx
     39c:	74 32                	je     3d0 <runcmd+0x40>
  switch(cmd->type){
     39e:	83 3b 05             	cmpl   $0x5,(%ebx)
     3a1:	0f 87 d3 00 00 00    	ja     47a <runcmd+0xea>
     3a7:	8b 03                	mov    (%ebx),%eax
     3a9:	ff 24 85 28 15 00 00 	jmp    *0x1528(,%eax,4)
    if(ecmd->argv[0] == 0)
     3b0:	8b 43 04             	mov    0x4(%ebx),%eax
     3b3:	85 c0                	test   %eax,%eax
     3b5:	74 19                	je     3d0 <runcmd+0x40>
    exec(ecmd->argv[0], ecmd->argv);
     3b7:	83 c3 04             	add    $0x4,%ebx
     3ba:	51                   	push   %ecx
     3bb:	51                   	push   %ecx
     3bc:	53                   	push   %ebx
     3bd:	50                   	push   %eax
     3be:	e8 58 0c 00 00       	call   101b <exec>
    break;
     3c3:	83 c4 10             	add    $0x10,%esp
     3c6:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
     3cd:	8d 76 00             	lea    0x0(%esi),%esi
    exit();
     3d0:	e8 0e 0c 00 00       	call   fe3 <exit>
    if(fork1() == 0)
     3d5:	e8 96 ff ff ff       	call   370 <fork1>
     3da:	85 c0                	test   %eax,%eax
     3dc:	75 f2                	jne    3d0 <runcmd+0x40>
     3de:	e9 8c 00 00 00       	jmp    46f <runcmd+0xdf>
    if(pipe(p) < 0)
     3e3:	83 ec 0c             	sub    $0xc,%esp
     3e6:	8d 45 f0             	lea    -0x10(%ebp),%eax
     3e9:	50                   	push   %eax
     3ea:	e8 04 0c 00 00       	call   ff3 <pipe>
     3ef:	83 c4 10             	add    $0x10,%esp
     3f2:	85 c0                	test   %eax,%eax
     3f4:	0f 88 a2 00 00 00    	js     49c <runcmd+0x10c>
    if(fork1() == 0){
     3fa:	e8 71 ff ff ff       	call   370 <fork1>
     3ff:	85 c0                	test   %eax,%eax
     401:	0f 84 a2 00 00 00    	je     4a9 <runcmd+0x119>
    if(fork1() == 0){
     407:	e8 64 ff ff ff       	call   370 <fork1>
     40c:	85 c0                	test   %eax,%eax
     40e:	0f 84 c3 00 00 00    	je     4d7 <runcmd+0x147>
    close(p[0]);
     414:	83 ec 0c             	sub    $0xc,%esp
     417:	ff 75 f0             	push   -0x10(%ebp)
     41a:	e8 ec 0b 00 00       	call   100b <close>
    close(p[1]);
     41f:	58                   	pop    %eax
     420:	ff 75 f4             	push   -0xc(%ebp)
     423:	e8 e3 0b 00 00       	call   100b <close>
    wait();
     428:	e8 be 0b 00 00       	call   feb <wait>
    wait();
     42d:	e8 b9 0b 00 00       	call   feb <wait>
    break;
     432:	83 c4 10             	add    $0x10,%esp
     435:	eb 99                	jmp    3d0 <runcmd+0x40>
    if (fork1() == 0){
     437:	e8 34 ff ff ff       	call   370 <fork1>
     43c:	85 c0                	test   %eax,%eax
     43e:	74 2f                	je     46f <runcmd+0xdf>
    wait();
     440:	e8 a6 0b 00 00       	call   feb <wait>
    runcmd(lcmd->right);
     445:	83 ec 0c             	sub    $0xc,%esp
     448:	ff 73 08             	push   0x8(%ebx)
     44b:	e8 40 ff ff ff       	call   390 <runcmd>
    close (rcmd->fd); // close current stdout/stdin
     450:	83 ec 0c             	sub    $0xc,%esp
     453:	ff 73 14             	push   0x14(%ebx)
     456:	e8 b0 0b 00 00       	call   100b <close>
    fd = open(rcmd->file, rcmd->mode); // Open or create the file for writing
     45b:	58                   	pop    %eax
     45c:	5a                   	pop    %edx
     45d:	ff 73 10             	push   0x10(%ebx)
     460:	ff 73 08             	push   0x8(%ebx)
     463:	e8 bb 0b 00 00       	call   1023 <open>
      if (fd < 0) {
     468:	83 c4 10             	add    $0x10,%esp
     46b:	85 c0                	test   %eax,%eax
     46d:	78 18                	js     487 <runcmd+0xf7>
      runcmd(bcmd->cmd);
     46f:	83 ec 0c             	sub    $0xc,%esp
     472:	ff 73 04             	push   0x4(%ebx)
     475:	e8 16 ff ff ff       	call   390 <runcmd>
    panic("runcmd");
     47a:	83 ec 0c             	sub    $0xc,%esp
     47d:	68 70 14 00 00       	push   $0x1470
     482:	e8 c9 fe ff ff       	call   350 <panic>
          printf(2, "cannot open %s\n", rcmd->file);
     487:	51                   	push   %ecx
     488:	ff 73 08             	push   0x8(%ebx)
     48b:	68 77 14 00 00       	push   $0x1477
     490:	6a 02                	push   $0x2
     492:	e8 a9 0c 00 00       	call   1140 <printf>
          exit();
     497:	e8 47 0b 00 00       	call   fe3 <exit>
      panic("pipe");
     49c:	83 ec 0c             	sub    $0xc,%esp
     49f:	68 87 14 00 00       	push   $0x1487
     4a4:	e8 a7 fe ff ff       	call   350 <panic>
      close(1);
     4a9:	83 ec 0c             	sub    $0xc,%esp
     4ac:	6a 01                	push   $0x1
     4ae:	e8 58 0b 00 00       	call   100b <close>
      dup(p[1]);
     4b3:	58                   	pop    %eax
     4b4:	ff 75 f4             	push   -0xc(%ebp)
     4b7:	e8 9f 0b 00 00       	call   105b <dup>
      close(p[0]);
     4bc:	58                   	pop    %eax
     4bd:	ff 75 f0             	push   -0x10(%ebp)
     4c0:	e8 46 0b 00 00       	call   100b <close>
      close(p[1]);
     4c5:	58                   	pop    %eax
     4c6:	ff 75 f4             	push   -0xc(%ebp)
     4c9:	e8 3d 0b 00 00       	call   100b <close>
      runcmd(pcmd->left);
     4ce:	5a                   	pop    %edx
     4cf:	ff 73 04             	push   0x4(%ebx)
     4d2:	e8 b9 fe ff ff       	call   390 <runcmd>
      close(0);
     4d7:	83 ec 0c             	sub    $0xc,%esp
     4da:	6a 00                	push   $0x0
     4dc:	e8 2a 0b 00 00       	call   100b <close>
      dup(p[0]);
     4e1:	5a                   	pop    %edx
     4e2:	ff 75 f0             	push   -0x10(%ebp)
     4e5:	e8 71 0b 00 00       	call   105b <dup>
      close(p[0]);
     4ea:	59                   	pop    %ecx
     4eb:	ff 75 f0             	push   -0x10(%ebp)
     4ee:	e8 18 0b 00 00       	call   100b <close>
      close(p[1]);
     4f3:	58                   	pop    %eax
     4f4:	ff 75 f4             	push   -0xc(%ebp)
     4f7:	e8 0f 0b 00 00       	call   100b <close>
      runcmd(pcmd->right);
     4fc:	58                   	pop    %eax
     4fd:	ff 73 08             	push   0x8(%ebx)
     500:	e8 8b fe ff ff       	call   390 <runcmd>
     505:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
     50c:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi

00000510 <execcmd>:
//PAGEBREAK!
// Constructors

struct cmd*
execcmd(void)
{
     510:	55                   	push   %ebp
     511:	89 e5                	mov    %esp,%ebp
     513:	53                   	push   %ebx
     514:	83 ec 10             	sub    $0x10,%esp
  struct execcmd *cmd;

  cmd = malloc(sizeof(*cmd));
     517:	6a 54                	push   $0x54
     519:	e8 62 0e 00 00       	call   1380 <malloc>
  memset(cmd, 0, sizeof(*cmd));
     51e:	83 c4 0c             	add    $0xc,%esp
     521:	6a 54                	push   $0x54
  cmd = malloc(sizeof(*cmd));
     523:	89 c3                	mov    %eax,%ebx
  memset(cmd, 0, sizeof(*cmd));
     525:	6a 00                	push   $0x0
     527:	50                   	push   %eax
     528:	e8 33 09 00 00       	call   e60 <memset>
  cmd->type = EXEC;
     52d:	c7 03 01 00 00 00    	movl   $0x1,(%ebx)
  return (struct cmd*)cmd;
}
     533:	89 d8                	mov    %ebx,%eax
     535:	8b 5d fc             	mov    -0x4(%ebp),%ebx
     538:	c9                   	leave
     539:	c3                   	ret
     53a:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi

00000540 <redircmd>:

struct cmd*
redircmd(struct cmd *subcmd, char *file, char *efile, int mode, int fd)
{
     540:	55                   	push   %ebp
     541:	89 e5                	mov    %esp,%ebp
     543:	53                   	push   %ebx
     544:	83 ec 10             	sub    $0x10,%esp
  struct redircmd *cmd;

  cmd = malloc(sizeof(*cmd));
     547:	6a 18                	push   $0x18
     549:	e8 32 0e 00 00       	call   1380 <malloc>
  memset(cmd, 0, sizeof(*cmd));
     54e:	83 c4 0c             	add    $0xc,%esp
     551:	6a 18                	push   $0x18
  cmd = malloc(sizeof(*cmd));
     553:	89 c3                	mov    %eax,%ebx
  memset(cmd, 0, sizeof(*cmd));
     555:	6a 00                	push   $0x0
     557:	50                   	push   %eax
     558:	e8 03 09 00 00       	call   e60 <memset>
  cmd->type = REDIR;
  cmd->cmd = subcmd;
     55d:	8b 45 08             	mov    0x8(%ebp),%eax
  cmd->type = REDIR;
     560:	c7 03 02 00 00 00    	movl   $0x2,(%ebx)
  cmd->cmd = subcmd;
     566:	89 43 04             	mov    %eax,0x4(%ebx)
  cmd->file = file;
     569:	8b 45 0c             	mov    0xc(%ebp),%eax
     56c:	89 43 08             	mov    %eax,0x8(%ebx)
  cmd->efile = efile;
     56f:	8b 45 10             	mov    0x10(%ebp),%eax
     572:	89 43 0c             	mov    %eax,0xc(%ebx)
  cmd->mode = mode;
     575:	8b 45 14             	mov    0x14(%ebp),%eax
     578:	89 43 10             	mov    %eax,0x10(%ebx)
  cmd->fd = fd;
     57b:	8b 45 18             	mov    0x18(%ebp),%eax
     57e:	89 43 14             	mov    %eax,0x14(%ebx)
  return (struct cmd*)cmd;
}
     581:	89 d8                	mov    %ebx,%eax
     583:	8b 5d fc             	mov    -0x4(%ebp),%ebx
     586:	c9                   	leave
     587:	c3                   	ret
     588:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
     58f:	90                   	nop

00000590 <pipecmd>:

struct cmd*
pipecmd(struct cmd *left, struct cmd *right)
{
     590:	55                   	push   %ebp
     591:	89 e5                	mov    %esp,%ebp
     593:	53                   	push   %ebx
     594:	83 ec 10             	sub    $0x10,%esp
  struct pipecmd *cmd;

  cmd = malloc(sizeof(*cmd));
     597:	6a 0c                	push   $0xc
     599:	e8 e2 0d 00 00       	call   1380 <malloc>
  memset(cmd, 0, sizeof(*cmd));
     59e:	83 c4 0c             	add    $0xc,%esp
     5a1:	6a 0c                	push   $0xc
  cmd = malloc(sizeof(*cmd));
     5a3:	89 c3                	mov    %eax,%ebx
  memset(cmd, 0, sizeof(*cmd));
     5a5:	6a 00                	push   $0x0
     5a7:	50                   	push   %eax
     5a8:	e8 b3 08 00 00       	call   e60 <memset>
  cmd->type = PIPE;
  cmd->left = left;
     5ad:	8b 45 08             	mov    0x8(%ebp),%eax
  cmd->type = PIPE;
     5b0:	c7 03 03 00 00 00    	movl   $0x3,(%ebx)
  cmd->left = left;
     5b6:	89 43 04             	mov    %eax,0x4(%ebx)
  cmd->right = right;
     5b9:	8b 45 0c             	mov    0xc(%ebp),%eax
     5bc:	89 43 08             	mov    %eax,0x8(%ebx)
  return (struct cmd*)cmd;
}
     5bf:	89 d8                	mov    %ebx,%eax
     5c1:	8b 5d fc             	mov    -0x4(%ebp),%ebx
     5c4:	c9                   	leave
     5c5:	c3                   	ret
     5c6:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
     5cd:	8d 76 00             	lea    0x0(%esi),%esi

000005d0 <listcmd>:

struct cmd*
listcmd(struct cmd *left, struct cmd *right)
{
     5d0:	55                   	push   %ebp
     5d1:	89 e5                	mov    %esp,%ebp
     5d3:	53                   	push   %ebx
     5d4:	83 ec 10             	sub    $0x10,%esp
  struct listcmd *cmd;

  cmd = malloc(sizeof(*cmd));
     5d7:	6a 0c                	push   $0xc
     5d9:	e8 a2 0d 00 00       	call   1380 <malloc>
  memset(cmd, 0, sizeof(*cmd));
     5de:	83 c4 0c             	add    $0xc,%esp
     5e1:	6a 0c                	push   $0xc
  cmd = malloc(sizeof(*cmd));
     5e3:	89 c3                	mov    %eax,%ebx
  memset(cmd, 0, sizeof(*cmd));
     5e5:	6a 00                	push   $0x0
     5e7:	50                   	push   %eax
     5e8:	e8 73 08 00 00       	call   e60 <memset>
  cmd->type = LIST;
  cmd->left = left;
     5ed:	8b 45 08             	mov    0x8(%ebp),%eax
  cmd->type = LIST;
     5f0:	c7 03 04 00 00 00    	movl   $0x4,(%ebx)
  cmd->left = left;
     5f6:	89 43 04             	mov    %eax,0x4(%ebx)
  cmd->right = right;
     5f9:	8b 45 0c             	mov    0xc(%ebp),%eax
     5fc:	89 43 08             	mov    %eax,0x8(%ebx)
  return (struct cmd*)cmd;
}
     5ff:	89 d8                	mov    %ebx,%eax
     601:	8b 5d fc             	mov    -0x4(%ebp),%ebx
     604:	c9                   	leave
     605:	c3                   	ret
     606:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
     60d:	8d 76 00             	lea    0x0(%esi),%esi

00000610 <backcmd>:

struct cmd*
backcmd(struct cmd *subcmd)
{
     610:	55                   	push   %ebp
     611:	89 e5                	mov    %esp,%ebp
     613:	53                   	push   %ebx
     614:	83 ec 10             	sub    $0x10,%esp
  struct backcmd *cmd;

  cmd = malloc(sizeof(*cmd));
     617:	6a 08                	push   $0x8
     619:	e8 62 0d 00 00       	call   1380 <malloc>
  memset(cmd, 0, sizeof(*cmd));
     61e:	83 c4 0c             	add    $0xc,%esp
     621:	6a 08                	push   $0x8
  cmd = malloc(sizeof(*cmd));
     623:	89 c3                	mov    %eax,%ebx
  memset(cmd, 0, sizeof(*cmd));
     625:	6a 00                	push   $0x0
     627:	50                   	push   %eax
     628:	e8 33 08 00 00       	call   e60 <memset>
  cmd->type = BACK;
  cmd->cmd = subcmd;
     62d:	8b 45 08             	mov    0x8(%ebp),%eax
  cmd->type = BACK;
     630:	c7 03 05 00 00 00    	movl   $0x5,(%ebx)
  cmd->cmd = subcmd;
     636:	89 43 04             	mov    %eax,0x4(%ebx)
  return (struct cmd*)cmd;
}
     639:	89 d8                	mov    %ebx,%eax
     63b:	8b 5d fc             	mov    -0x4(%ebp),%ebx
     63e:	c9                   	leave
     63f:	c3                   	ret

00000640 <gettoken>:
char whitespace[] = " \t\r\n\v";
char symbols[] = "<|>&;()";

int
gettoken(char **ps, char *es, char **q, char **eq)
{
     640:	55                   	push   %ebp
     641:	89 e5                	mov    %esp,%ebp
     643:	57                   	push   %edi
     644:	56                   	push   %esi
     645:	53                   	push   %ebx
     646:	83 ec 0c             	sub    $0xc,%esp
  char *s;
  int ret;

  s = *ps;
     649:	8b 45 08             	mov    0x8(%ebp),%eax
{
     64c:	8b 5d 0c             	mov    0xc(%ebp),%ebx
     64f:	8b 75 10             	mov    0x10(%ebp),%esi
  s = *ps;
     652:	8b 38                	mov    (%eax),%edi
  while(s < es && strchr(whitespace, *s))
     654:	39 df                	cmp    %ebx,%edi
     656:	72 0f                	jb     667 <gettoken+0x27>
     658:	eb 25                	jmp    67f <gettoken+0x3f>
     65a:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
    s++;
     660:	83 c7 01             	add    $0x1,%edi
  while(s < es && strchr(whitespace, *s))
     663:	39 fb                	cmp    %edi,%ebx
     665:	74 18                	je     67f <gettoken+0x3f>
     667:	0f be 07             	movsbl (%edi),%eax
     66a:	83 ec 08             	sub    $0x8,%esp
     66d:	50                   	push   %eax
     66e:	68 7c 1b 00 00       	push   $0x1b7c
     673:	e8 08 08 00 00       	call   e80 <strchr>
     678:	83 c4 10             	add    $0x10,%esp
     67b:	85 c0                	test   %eax,%eax
     67d:	75 e1                	jne    660 <gettoken+0x20>
  if(q)
     67f:	85 f6                	test   %esi,%esi
     681:	74 02                	je     685 <gettoken+0x45>
    *q = s;
     683:	89 3e                	mov    %edi,(%esi)
  ret = *s;
     685:	0f b6 07             	movzbl (%edi),%eax
  switch(*s){
     688:	3c 3c                	cmp    $0x3c,%al
     68a:	0f 8f d0 00 00 00    	jg     760 <gettoken+0x120>
     690:	3c 3a                	cmp    $0x3a,%al
     692:	0f 8f bc 00 00 00    	jg     754 <gettoken+0x114>
     698:	84 c0                	test   %al,%al
     69a:	75 44                	jne    6e0 <gettoken+0xa0>
     69c:	31 f6                	xor    %esi,%esi
    ret = 'a';
    while(s < es && !strchr(whitespace, *s) && !strchr(symbols, *s))
      s++;
    break;
  }
  if(eq)
     69e:	8b 4d 14             	mov    0x14(%ebp),%ecx
     6a1:	85 c9                	test   %ecx,%ecx
     6a3:	74 05                	je     6aa <gettoken+0x6a>
    *eq = s;
     6a5:	8b 45 14             	mov    0x14(%ebp),%eax
     6a8:	89 38                	mov    %edi,(%eax)

  while(s < es && strchr(whitespace, *s))
     6aa:	39 df                	cmp    %ebx,%edi
     6ac:	72 09                	jb     6b7 <gettoken+0x77>
     6ae:	eb 1f                	jmp    6cf <gettoken+0x8f>
    s++;
     6b0:	83 c7 01             	add    $0x1,%edi
  while(s < es && strchr(whitespace, *s))
     6b3:	39 fb                	cmp    %edi,%ebx
     6b5:	74 18                	je     6cf <gettoken+0x8f>
     6b7:	0f be 07             	movsbl (%edi),%eax
     6ba:	83 ec 08             	sub    $0x8,%esp
     6bd:	50                   	push   %eax
     6be:	68 7c 1b 00 00       	push   $0x1b7c
     6c3:	e8 b8 07 00 00       	call   e80 <strchr>
     6c8:	83 c4 10             	add    $0x10,%esp
     6cb:	85 c0                	test   %eax,%eax
     6cd:	75 e1                	jne    6b0 <gettoken+0x70>
  *ps = s;
     6cf:	8b 45 08             	mov    0x8(%ebp),%eax
     6d2:	89 38                	mov    %edi,(%eax)
  return ret;
}
     6d4:	8d 65 f4             	lea    -0xc(%ebp),%esp
     6d7:	89 f0                	mov    %esi,%eax
     6d9:	5b                   	pop    %ebx
     6da:	5e                   	pop    %esi
     6db:	5f                   	pop    %edi
     6dc:	5d                   	pop    %ebp
     6dd:	c3                   	ret
     6de:	66 90                	xchg   %ax,%ax
  switch(*s){
     6e0:	79 66                	jns    748 <gettoken+0x108>
    while(s < es && !strchr(whitespace, *s) && !strchr(symbols, *s))
     6e2:	39 df                	cmp    %ebx,%edi
     6e4:	72 39                	jb     71f <gettoken+0xdf>
  if(eq)
     6e6:	8b 55 14             	mov    0x14(%ebp),%edx
     6e9:	85 d2                	test   %edx,%edx
     6eb:	0f 84 b3 00 00 00    	je     7a4 <gettoken+0x164>
    *eq = s;
     6f1:	8b 45 14             	mov    0x14(%ebp),%eax
     6f4:	89 38                	mov    %edi,(%eax)
  while(s < es && strchr(whitespace, *s))
     6f6:	e9 a9 00 00 00       	jmp    7a4 <gettoken+0x164>
     6fb:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
     6ff:	90                   	nop
    while(s < es && !strchr(whitespace, *s) && !strchr(symbols, *s))
     700:	0f be 07             	movsbl (%edi),%eax
     703:	83 ec 08             	sub    $0x8,%esp
     706:	50                   	push   %eax
     707:	68 74 1b 00 00       	push   $0x1b74
     70c:	e8 6f 07 00 00       	call   e80 <strchr>
     711:	83 c4 10             	add    $0x10,%esp
     714:	85 c0                	test   %eax,%eax
     716:	75 1f                	jne    737 <gettoken+0xf7>
      s++;
     718:	83 c7 01             	add    $0x1,%edi
    while(s < es && !strchr(whitespace, *s) && !strchr(symbols, *s))
     71b:	39 fb                	cmp    %edi,%ebx
     71d:	74 77                	je     796 <gettoken+0x156>
     71f:	0f be 07             	movsbl (%edi),%eax
     722:	83 ec 08             	sub    $0x8,%esp
     725:	50                   	push   %eax
     726:	68 7c 1b 00 00       	push   $0x1b7c
     72b:	e8 50 07 00 00       	call   e80 <strchr>
     730:	83 c4 10             	add    $0x10,%esp
     733:	85 c0                	test   %eax,%eax
     735:	74 c9                	je     700 <gettoken+0xc0>
    ret = 'a';
     737:	be 61 00 00 00       	mov    $0x61,%esi
     73c:	e9 5d ff ff ff       	jmp    69e <gettoken+0x5e>
     741:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
  switch(*s){
     748:	3c 26                	cmp    $0x26,%al
     74a:	74 08                	je     754 <gettoken+0x114>
     74c:	8d 48 d8             	lea    -0x28(%eax),%ecx
     74f:	80 f9 01             	cmp    $0x1,%cl
     752:	77 8e                	ja     6e2 <gettoken+0xa2>
  ret = *s;
     754:	0f be f0             	movsbl %al,%esi
    s++;
     757:	83 c7 01             	add    $0x1,%edi
    break;
     75a:	e9 3f ff ff ff       	jmp    69e <gettoken+0x5e>
     75f:	90                   	nop
  switch(*s){
     760:	3c 3e                	cmp    $0x3e,%al
     762:	75 1c                	jne    780 <gettoken+0x140>
    if(*s == '>'){
     764:	80 7f 01 3e          	cmpb   $0x3e,0x1(%edi)
     768:	74 1f                	je     789 <gettoken+0x149>
    s++;
     76a:	83 c7 01             	add    $0x1,%edi
  ret = *s;
     76d:	be 3e 00 00 00       	mov    $0x3e,%esi
     772:	e9 27 ff ff ff       	jmp    69e <gettoken+0x5e>
     777:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
     77e:	66 90                	xchg   %ax,%ax
  switch(*s){
     780:	3c 7c                	cmp    $0x7c,%al
     782:	74 d0                	je     754 <gettoken+0x114>
     784:	e9 59 ff ff ff       	jmp    6e2 <gettoken+0xa2>
      s++;
     789:	83 c7 02             	add    $0x2,%edi
      ret = '+';
     78c:	be 2b 00 00 00       	mov    $0x2b,%esi
     791:	e9 08 ff ff ff       	jmp    69e <gettoken+0x5e>
  if(eq)
     796:	8b 45 14             	mov    0x14(%ebp),%eax
     799:	85 c0                	test   %eax,%eax
     79b:	74 05                	je     7a2 <gettoken+0x162>
    *eq = s;
     79d:	8b 45 14             	mov    0x14(%ebp),%eax
     7a0:	89 18                	mov    %ebx,(%eax)
      s++;
     7a2:	89 df                	mov    %ebx,%edi
    ret = 'a';
     7a4:	be 61 00 00 00       	mov    $0x61,%esi
     7a9:	e9 21 ff ff ff       	jmp    6cf <gettoken+0x8f>
     7ae:	66 90                	xchg   %ax,%ax

000007b0 <peek>:

int
peek(char **ps, char *es, char *toks)
{
     7b0:	55                   	push   %ebp
     7b1:	89 e5                	mov    %esp,%ebp
     7b3:	57                   	push   %edi
     7b4:	56                   	push   %esi
     7b5:	53                   	push   %ebx
     7b6:	83 ec 0c             	sub    $0xc,%esp
     7b9:	8b 7d 08             	mov    0x8(%ebp),%edi
     7bc:	8b 75 0c             	mov    0xc(%ebp),%esi
  char *s;

  s = *ps;
     7bf:	8b 1f                	mov    (%edi),%ebx
  while(s < es && strchr(whitespace, *s))
     7c1:	39 f3                	cmp    %esi,%ebx
     7c3:	72 12                	jb     7d7 <peek+0x27>
     7c5:	eb 28                	jmp    7ef <peek+0x3f>
     7c7:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
     7ce:	66 90                	xchg   %ax,%ax
    s++;
     7d0:	83 c3 01             	add    $0x1,%ebx
  while(s < es && strchr(whitespace, *s))
     7d3:	39 de                	cmp    %ebx,%esi
     7d5:	74 18                	je     7ef <peek+0x3f>
     7d7:	0f be 03             	movsbl (%ebx),%eax
     7da:	83 ec 08             	sub    $0x8,%esp
     7dd:	50                   	push   %eax
     7de:	68 7c 1b 00 00       	push   $0x1b7c
     7e3:	e8 98 06 00 00       	call   e80 <strchr>
     7e8:	83 c4 10             	add    $0x10,%esp
     7eb:	85 c0                	test   %eax,%eax
     7ed:	75 e1                	jne    7d0 <peek+0x20>
  *ps = s;
     7ef:	89 1f                	mov    %ebx,(%edi)
  return *s && strchr(toks, *s);
     7f1:	0f be 03             	movsbl (%ebx),%eax
     7f4:	31 d2                	xor    %edx,%edx
     7f6:	84 c0                	test   %al,%al
     7f8:	75 0e                	jne    808 <peek+0x58>
}
     7fa:	8d 65 f4             	lea    -0xc(%ebp),%esp
     7fd:	89 d0                	mov    %edx,%eax
     7ff:	5b                   	pop    %ebx
     800:	5e                   	pop    %esi
     801:	5f                   	pop    %edi
     802:	5d                   	pop    %ebp
     803:	c3                   	ret
     804:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
  return *s && strchr(toks, *s);
     808:	83 ec 08             	sub    $0x8,%esp
     80b:	50                   	push   %eax
     80c:	ff 75 10             	push   0x10(%ebp)
     80f:	e8 6c 06 00 00       	call   e80 <strchr>
     814:	83 c4 10             	add    $0x10,%esp
     817:	31 d2                	xor    %edx,%edx
     819:	85 c0                	test   %eax,%eax
     81b:	0f 95 c2             	setne  %dl
}
     81e:	8d 65 f4             	lea    -0xc(%ebp),%esp
     821:	5b                   	pop    %ebx
     822:	89 d0                	mov    %edx,%eax
     824:	5e                   	pop    %esi
     825:	5f                   	pop    %edi
     826:	5d                   	pop    %ebp
     827:	c3                   	ret
     828:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
     82f:	90                   	nop

00000830 <parseredirs>:
  return cmd;
}

struct cmd*
parseredirs(struct cmd *cmd, char **ps, char *es)
{
     830:	55                   	push   %ebp
     831:	89 e5                	mov    %esp,%ebp
     833:	57                   	push   %edi
     834:	56                   	push   %esi
     835:	53                   	push   %ebx
     836:	83 ec 2c             	sub    $0x2c,%esp
     839:	8b 75 0c             	mov    0xc(%ebp),%esi
     83c:	8b 5d 10             	mov    0x10(%ebp),%ebx
  int tok;
  char *q, *eq;

  while(peek(ps, es, "<>")){
     83f:	90                   	nop
     840:	83 ec 04             	sub    $0x4,%esp
     843:	68 a9 14 00 00       	push   $0x14a9
     848:	53                   	push   %ebx
     849:	56                   	push   %esi
     84a:	e8 61 ff ff ff       	call   7b0 <peek>
     84f:	83 c4 10             	add    $0x10,%esp
     852:	85 c0                	test   %eax,%eax
     854:	0f 84 f6 00 00 00    	je     950 <parseredirs+0x120>
    tok = gettoken(ps, es, 0, 0);
     85a:	6a 00                	push   $0x0
     85c:	6a 00                	push   $0x0
     85e:	53                   	push   %ebx
     85f:	56                   	push   %esi
     860:	e8 db fd ff ff       	call   640 <gettoken>
     865:	89 c7                	mov    %eax,%edi
    if(gettoken(ps, es, &q, &eq) != 'a')
     867:	8d 45 e4             	lea    -0x1c(%ebp),%eax
     86a:	50                   	push   %eax
     86b:	8d 45 e0             	lea    -0x20(%ebp),%eax
     86e:	50                   	push   %eax
     86f:	53                   	push   %ebx
     870:	56                   	push   %esi
     871:	e8 ca fd ff ff       	call   640 <gettoken>
     876:	83 c4 20             	add    $0x20,%esp
     879:	83 f8 61             	cmp    $0x61,%eax
     87c:	0f 85 d9 00 00 00    	jne    95b <parseredirs+0x12b>
      panic("missing file for redirection");
    switch(tok){
     882:	83 ff 3c             	cmp    $0x3c,%edi
     885:	74 69                	je     8f0 <parseredirs+0xc0>
     887:	83 ff 3e             	cmp    $0x3e,%edi
     88a:	74 05                	je     891 <parseredirs+0x61>
     88c:	83 ff 2b             	cmp    $0x2b,%edi
     88f:	75 af                	jne    840 <parseredirs+0x10>
      break;
    case '>':
      cmd = redircmd(cmd, q, eq, O_WRONLY|O_CREATE, 1);
      break;
    case '+':  // >>
      cmd = redircmd(cmd, q, eq, O_WRONLY|O_CREATE, 1);
     891:	8b 55 e4             	mov    -0x1c(%ebp),%edx
     894:	8b 4d e0             	mov    -0x20(%ebp),%ecx
  cmd = malloc(sizeof(*cmd));
     897:	83 ec 0c             	sub    $0xc,%esp
      cmd = redircmd(cmd, q, eq, O_WRONLY|O_CREATE, 1);
     89a:	89 55 d0             	mov    %edx,-0x30(%ebp)
     89d:	89 4d d4             	mov    %ecx,-0x2c(%ebp)
  cmd = malloc(sizeof(*cmd));
     8a0:	6a 18                	push   $0x18
     8a2:	e8 d9 0a 00 00       	call   1380 <malloc>
  memset(cmd, 0, sizeof(*cmd));
     8a7:	83 c4 0c             	add    $0xc,%esp
     8aa:	6a 18                	push   $0x18
  cmd = malloc(sizeof(*cmd));
     8ac:	89 c7                	mov    %eax,%edi
  memset(cmd, 0, sizeof(*cmd));
     8ae:	6a 00                	push   $0x0
     8b0:	50                   	push   %eax
     8b1:	e8 aa 05 00 00       	call   e60 <memset>
  cmd->type = REDIR;
     8b6:	c7 07 02 00 00 00    	movl   $0x2,(%edi)
  cmd->cmd = subcmd;
     8bc:	8b 45 08             	mov    0x8(%ebp),%eax
      break;
     8bf:	83 c4 10             	add    $0x10,%esp
  cmd->cmd = subcmd;
     8c2:	89 47 04             	mov    %eax,0x4(%edi)
  cmd->file = file;
     8c5:	8b 4d d4             	mov    -0x2c(%ebp),%ecx
     8c8:	89 4f 08             	mov    %ecx,0x8(%edi)
  cmd->efile = efile;
     8cb:	8b 55 d0             	mov    -0x30(%ebp),%edx
  cmd->mode = mode;
     8ce:	c7 47 10 01 02 00 00 	movl   $0x201,0x10(%edi)
  cmd->efile = efile;
     8d5:	89 57 0c             	mov    %edx,0xc(%edi)
  cmd->fd = fd;
     8d8:	c7 47 14 01 00 00 00 	movl   $0x1,0x14(%edi)
      break;
     8df:	89 7d 08             	mov    %edi,0x8(%ebp)
     8e2:	e9 59 ff ff ff       	jmp    840 <parseredirs+0x10>
     8e7:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
     8ee:	66 90                	xchg   %ax,%ax
      cmd = redircmd(cmd, q, eq, O_RDONLY, 0);
     8f0:	8b 55 e4             	mov    -0x1c(%ebp),%edx
     8f3:	8b 4d e0             	mov    -0x20(%ebp),%ecx
  cmd = malloc(sizeof(*cmd));
     8f6:	83 ec 0c             	sub    $0xc,%esp
      cmd = redircmd(cmd, q, eq, O_RDONLY, 0);
     8f9:	89 55 d0             	mov    %edx,-0x30(%ebp)
     8fc:	89 4d d4             	mov    %ecx,-0x2c(%ebp)
  cmd = malloc(sizeof(*cmd));
     8ff:	6a 18                	push   $0x18
     901:	e8 7a 0a 00 00       	call   1380 <malloc>
  memset(cmd, 0, sizeof(*cmd));
     906:	83 c4 0c             	add    $0xc,%esp
     909:	6a 18                	push   $0x18
  cmd = malloc(sizeof(*cmd));
     90b:	89 c7                	mov    %eax,%edi
  memset(cmd, 0, sizeof(*cmd));
     90d:	6a 00                	push   $0x0
     90f:	50                   	push   %eax
     910:	e8 4b 05 00 00       	call   e60 <memset>
  cmd->cmd = subcmd;
     915:	8b 45 08             	mov    0x8(%ebp),%eax
  cmd->file = file;
     918:	8b 4d d4             	mov    -0x2c(%ebp),%ecx
      break;
     91b:	89 7d 08             	mov    %edi,0x8(%ebp)
  cmd->efile = efile;
     91e:	8b 55 d0             	mov    -0x30(%ebp),%edx
  cmd->type = REDIR;
     921:	c7 07 02 00 00 00    	movl   $0x2,(%edi)
      break;
     927:	83 c4 10             	add    $0x10,%esp
  cmd->cmd = subcmd;
     92a:	89 47 04             	mov    %eax,0x4(%edi)
  cmd->file = file;
     92d:	89 4f 08             	mov    %ecx,0x8(%edi)
  cmd->efile = efile;
     930:	89 57 0c             	mov    %edx,0xc(%edi)
  cmd->mode = mode;
     933:	c7 47 10 00 00 00 00 	movl   $0x0,0x10(%edi)
  cmd->fd = fd;
     93a:	c7 47 14 00 00 00 00 	movl   $0x0,0x14(%edi)
      break;
     941:	e9 fa fe ff ff       	jmp    840 <parseredirs+0x10>
     946:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
     94d:	8d 76 00             	lea    0x0(%esi),%esi
    }
  }
  return cmd;
}
     950:	8b 45 08             	mov    0x8(%ebp),%eax
     953:	8d 65 f4             	lea    -0xc(%ebp),%esp
     956:	5b                   	pop    %ebx
     957:	5e                   	pop    %esi
     958:	5f                   	pop    %edi
     959:	5d                   	pop    %ebp
     95a:	c3                   	ret
      panic("missing file for redirection");
     95b:	83 ec 0c             	sub    $0xc,%esp
     95e:	68 8c 14 00 00       	push   $0x148c
     963:	e8 e8 f9 ff ff       	call   350 <panic>
     968:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
     96f:	90                   	nop

00000970 <parseexec>:
  return cmd;
}

struct cmd*
parseexec(char **ps, char *es)
{
     970:	55                   	push   %ebp
     971:	89 e5                	mov    %esp,%ebp
     973:	57                   	push   %edi
     974:	56                   	push   %esi
     975:	53                   	push   %ebx
     976:	83 ec 30             	sub    $0x30,%esp
     979:	8b 5d 08             	mov    0x8(%ebp),%ebx
     97c:	8b 75 0c             	mov    0xc(%ebp),%esi
  char *q, *eq;
  int tok, argc;
  struct execcmd *cmd;
  struct cmd *ret;

  if(peek(ps, es, "("))
     97f:	68 ac 14 00 00       	push   $0x14ac
     984:	56                   	push   %esi
     985:	53                   	push   %ebx
     986:	e8 25 fe ff ff       	call   7b0 <peek>
     98b:	83 c4 10             	add    $0x10,%esp
     98e:	85 c0                	test   %eax,%eax
     990:	0f 85 aa 00 00 00    	jne    a40 <parseexec+0xd0>
  cmd = malloc(sizeof(*cmd));
     996:	83 ec 0c             	sub    $0xc,%esp
     999:	89 c7                	mov    %eax,%edi
     99b:	6a 54                	push   $0x54
     99d:	e8 de 09 00 00       	call   1380 <malloc>
  memset(cmd, 0, sizeof(*cmd));
     9a2:	83 c4 0c             	add    $0xc,%esp
     9a5:	6a 54                	push   $0x54
     9a7:	6a 00                	push   $0x0
     9a9:	89 45 d0             	mov    %eax,-0x30(%ebp)
     9ac:	50                   	push   %eax
     9ad:	e8 ae 04 00 00       	call   e60 <memset>
  cmd->type = EXEC;
     9b2:	8b 45 d0             	mov    -0x30(%ebp),%eax

  ret = execcmd();
  cmd = (struct execcmd*)ret;

  argc = 0;
  ret = parseredirs(ret, ps, es);
     9b5:	83 c4 0c             	add    $0xc,%esp
  cmd->type = EXEC;
     9b8:	c7 00 01 00 00 00    	movl   $0x1,(%eax)
  ret = parseredirs(ret, ps, es);
     9be:	56                   	push   %esi
     9bf:	53                   	push   %ebx
     9c0:	50                   	push   %eax
     9c1:	e8 6a fe ff ff       	call   830 <parseredirs>
  while(!peek(ps, es, "|)&;")){
     9c6:	83 c4 10             	add    $0x10,%esp
  ret = parseredirs(ret, ps, es);
     9c9:	89 45 d4             	mov    %eax,-0x2c(%ebp)
  while(!peek(ps, es, "|)&;")){
     9cc:	eb 15                	jmp    9e3 <parseexec+0x73>
     9ce:	66 90                	xchg   %ax,%ax
    cmd->argv[argc] = q;
    cmd->eargv[argc] = eq;
    argc++;
    if(argc >= MAXARGS)
      panic("too many args");
    ret = parseredirs(ret, ps, es);
     9d0:	83 ec 04             	sub    $0x4,%esp
     9d3:	56                   	push   %esi
     9d4:	53                   	push   %ebx
     9d5:	ff 75 d4             	push   -0x2c(%ebp)
     9d8:	e8 53 fe ff ff       	call   830 <parseredirs>
     9dd:	83 c4 10             	add    $0x10,%esp
     9e0:	89 45 d4             	mov    %eax,-0x2c(%ebp)
  while(!peek(ps, es, "|)&;")){
     9e3:	83 ec 04             	sub    $0x4,%esp
     9e6:	68 c3 14 00 00       	push   $0x14c3
     9eb:	56                   	push   %esi
     9ec:	53                   	push   %ebx
     9ed:	e8 be fd ff ff       	call   7b0 <peek>
     9f2:	83 c4 10             	add    $0x10,%esp
     9f5:	85 c0                	test   %eax,%eax
     9f7:	75 5f                	jne    a58 <parseexec+0xe8>
    if((tok=gettoken(ps, es, &q, &eq)) == 0)
     9f9:	8d 45 e4             	lea    -0x1c(%ebp),%eax
     9fc:	50                   	push   %eax
     9fd:	8d 45 e0             	lea    -0x20(%ebp),%eax
     a00:	50                   	push   %eax
     a01:	56                   	push   %esi
     a02:	53                   	push   %ebx
     a03:	e8 38 fc ff ff       	call   640 <gettoken>
     a08:	83 c4 10             	add    $0x10,%esp
     a0b:	85 c0                	test   %eax,%eax
     a0d:	74 49                	je     a58 <parseexec+0xe8>
    if(tok != 'a')
     a0f:	83 f8 61             	cmp    $0x61,%eax
     a12:	75 62                	jne    a76 <parseexec+0x106>
    cmd->argv[argc] = q;
     a14:	8b 45 e0             	mov    -0x20(%ebp),%eax
     a17:	8b 55 d0             	mov    -0x30(%ebp),%edx
     a1a:	89 44 ba 04          	mov    %eax,0x4(%edx,%edi,4)
    cmd->eargv[argc] = eq;
     a1e:	8b 45 e4             	mov    -0x1c(%ebp),%eax
     a21:	89 44 ba 2c          	mov    %eax,0x2c(%edx,%edi,4)
    argc++;
     a25:	83 c7 01             	add    $0x1,%edi
    if(argc >= MAXARGS)
     a28:	83 ff 0a             	cmp    $0xa,%edi
     a2b:	75 a3                	jne    9d0 <parseexec+0x60>
      panic("too many args");
     a2d:	83 ec 0c             	sub    $0xc,%esp
     a30:	68 b5 14 00 00       	push   $0x14b5
     a35:	e8 16 f9 ff ff       	call   350 <panic>
     a3a:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
    return parseblock(ps, es);
     a40:	89 75 0c             	mov    %esi,0xc(%ebp)
     a43:	89 5d 08             	mov    %ebx,0x8(%ebp)
  }
  cmd->argv[argc] = 0;
  cmd->eargv[argc] = 0;
  return ret;
}
     a46:	8d 65 f4             	lea    -0xc(%ebp),%esp
     a49:	5b                   	pop    %ebx
     a4a:	5e                   	pop    %esi
     a4b:	5f                   	pop    %edi
     a4c:	5d                   	pop    %ebp
    return parseblock(ps, es);
     a4d:	e9 ae 01 00 00       	jmp    c00 <parseblock>
     a52:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
  cmd->argv[argc] = 0;
     a58:	8b 45 d0             	mov    -0x30(%ebp),%eax
     a5b:	c7 44 b8 04 00 00 00 	movl   $0x0,0x4(%eax,%edi,4)
     a62:	00 
  cmd->eargv[argc] = 0;
     a63:	c7 44 b8 2c 00 00 00 	movl   $0x0,0x2c(%eax,%edi,4)
     a6a:	00 
}
     a6b:	8b 45 d4             	mov    -0x2c(%ebp),%eax
     a6e:	8d 65 f4             	lea    -0xc(%ebp),%esp
     a71:	5b                   	pop    %ebx
     a72:	5e                   	pop    %esi
     a73:	5f                   	pop    %edi
     a74:	5d                   	pop    %ebp
     a75:	c3                   	ret
      panic("syntax");
     a76:	83 ec 0c             	sub    $0xc,%esp
     a79:	68 ae 14 00 00       	push   $0x14ae
     a7e:	e8 cd f8 ff ff       	call   350 <panic>
     a83:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
     a8a:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi

00000a90 <parsepipe>:
{
     a90:	55                   	push   %ebp
     a91:	89 e5                	mov    %esp,%ebp
     a93:	57                   	push   %edi
     a94:	56                   	push   %esi
     a95:	53                   	push   %ebx
     a96:	83 ec 14             	sub    $0x14,%esp
     a99:	8b 75 08             	mov    0x8(%ebp),%esi
     a9c:	8b 7d 0c             	mov    0xc(%ebp),%edi
  cmd = parseexec(ps, es);
     a9f:	57                   	push   %edi
     aa0:	56                   	push   %esi
     aa1:	e8 ca fe ff ff       	call   970 <parseexec>
  if(peek(ps, es, "|")){
     aa6:	83 c4 0c             	add    $0xc,%esp
     aa9:	68 c8 14 00 00       	push   $0x14c8
  cmd = parseexec(ps, es);
     aae:	89 c3                	mov    %eax,%ebx
  if(peek(ps, es, "|")){
     ab0:	57                   	push   %edi
     ab1:	56                   	push   %esi
     ab2:	e8 f9 fc ff ff       	call   7b0 <peek>
     ab7:	83 c4 10             	add    $0x10,%esp
     aba:	85 c0                	test   %eax,%eax
     abc:	75 12                	jne    ad0 <parsepipe+0x40>
}
     abe:	8d 65 f4             	lea    -0xc(%ebp),%esp
     ac1:	89 d8                	mov    %ebx,%eax
     ac3:	5b                   	pop    %ebx
     ac4:	5e                   	pop    %esi
     ac5:	5f                   	pop    %edi
     ac6:	5d                   	pop    %ebp
     ac7:	c3                   	ret
     ac8:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
     acf:	90                   	nop
    gettoken(ps, es, 0, 0);
     ad0:	6a 00                	push   $0x0
     ad2:	6a 00                	push   $0x0
     ad4:	57                   	push   %edi
     ad5:	56                   	push   %esi
     ad6:	e8 65 fb ff ff       	call   640 <gettoken>
    cmd = pipecmd(cmd, parsepipe(ps, es));
     adb:	58                   	pop    %eax
     adc:	5a                   	pop    %edx
     add:	57                   	push   %edi
     ade:	56                   	push   %esi
     adf:	e8 ac ff ff ff       	call   a90 <parsepipe>
  cmd = malloc(sizeof(*cmd));
     ae4:	c7 04 24 0c 00 00 00 	movl   $0xc,(%esp)
    cmd = pipecmd(cmd, parsepipe(ps, es));
     aeb:	89 c7                	mov    %eax,%edi
  cmd = malloc(sizeof(*cmd));
     aed:	e8 8e 08 00 00       	call   1380 <malloc>
  memset(cmd, 0, sizeof(*cmd));
     af2:	83 c4 0c             	add    $0xc,%esp
     af5:	6a 0c                	push   $0xc
  cmd = malloc(sizeof(*cmd));
     af7:	89 c6                	mov    %eax,%esi
  memset(cmd, 0, sizeof(*cmd));
     af9:	6a 00                	push   $0x0
     afb:	50                   	push   %eax
     afc:	e8 5f 03 00 00       	call   e60 <memset>
  cmd->left = left;
     b01:	89 5e 04             	mov    %ebx,0x4(%esi)
  cmd->right = right;
     b04:	83 c4 10             	add    $0x10,%esp
     b07:	89 f3                	mov    %esi,%ebx
  cmd->type = PIPE;
     b09:	c7 06 03 00 00 00    	movl   $0x3,(%esi)
}
     b0f:	89 d8                	mov    %ebx,%eax
  cmd->right = right;
     b11:	89 7e 08             	mov    %edi,0x8(%esi)
}
     b14:	8d 65 f4             	lea    -0xc(%ebp),%esp
     b17:	5b                   	pop    %ebx
     b18:	5e                   	pop    %esi
     b19:	5f                   	pop    %edi
     b1a:	5d                   	pop    %ebp
     b1b:	c3                   	ret
     b1c:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi

00000b20 <parseline>:
{
     b20:	55                   	push   %ebp
     b21:	89 e5                	mov    %esp,%ebp
     b23:	57                   	push   %edi
     b24:	56                   	push   %esi
     b25:	53                   	push   %ebx
     b26:	83 ec 24             	sub    $0x24,%esp
     b29:	8b 75 08             	mov    0x8(%ebp),%esi
     b2c:	8b 7d 0c             	mov    0xc(%ebp),%edi
  cmd = parsepipe(ps, es);
     b2f:	57                   	push   %edi
     b30:	56                   	push   %esi
     b31:	e8 5a ff ff ff       	call   a90 <parsepipe>
  while(peek(ps, es, "&")){
     b36:	83 c4 10             	add    $0x10,%esp
  cmd = parsepipe(ps, es);
     b39:	89 c3                	mov    %eax,%ebx
  while(peek(ps, es, "&")){
     b3b:	eb 3b                	jmp    b78 <parseline+0x58>
     b3d:	8d 76 00             	lea    0x0(%esi),%esi
    gettoken(ps, es, 0, 0);
     b40:	6a 00                	push   $0x0
     b42:	6a 00                	push   $0x0
     b44:	57                   	push   %edi
     b45:	56                   	push   %esi
     b46:	e8 f5 fa ff ff       	call   640 <gettoken>
  cmd = malloc(sizeof(*cmd));
     b4b:	c7 04 24 08 00 00 00 	movl   $0x8,(%esp)
     b52:	e8 29 08 00 00       	call   1380 <malloc>
  memset(cmd, 0, sizeof(*cmd));
     b57:	83 c4 0c             	add    $0xc,%esp
     b5a:	6a 08                	push   $0x8
     b5c:	6a 00                	push   $0x0
     b5e:	50                   	push   %eax
     b5f:	89 45 e4             	mov    %eax,-0x1c(%ebp)
     b62:	e8 f9 02 00 00       	call   e60 <memset>
  cmd->type = BACK;
     b67:	8b 55 e4             	mov    -0x1c(%ebp),%edx
  cmd->cmd = subcmd;
     b6a:	83 c4 10             	add    $0x10,%esp
  cmd->type = BACK;
     b6d:	c7 02 05 00 00 00    	movl   $0x5,(%edx)
  cmd->cmd = subcmd;
     b73:	89 5a 04             	mov    %ebx,0x4(%edx)
     b76:	89 d3                	mov    %edx,%ebx
  while(peek(ps, es, "&")){
     b78:	83 ec 04             	sub    $0x4,%esp
     b7b:	68 ca 14 00 00       	push   $0x14ca
     b80:	57                   	push   %edi
     b81:	56                   	push   %esi
     b82:	e8 29 fc ff ff       	call   7b0 <peek>
     b87:	83 c4 10             	add    $0x10,%esp
     b8a:	85 c0                	test   %eax,%eax
     b8c:	75 b2                	jne    b40 <parseline+0x20>
  if(peek(ps, es, ";")){
     b8e:	83 ec 04             	sub    $0x4,%esp
     b91:	68 c6 14 00 00       	push   $0x14c6
     b96:	57                   	push   %edi
     b97:	56                   	push   %esi
     b98:	e8 13 fc ff ff       	call   7b0 <peek>
     b9d:	83 c4 10             	add    $0x10,%esp
     ba0:	85 c0                	test   %eax,%eax
     ba2:	75 0c                	jne    bb0 <parseline+0x90>
}
     ba4:	8d 65 f4             	lea    -0xc(%ebp),%esp
     ba7:	89 d8                	mov    %ebx,%eax
     ba9:	5b                   	pop    %ebx
     baa:	5e                   	pop    %esi
     bab:	5f                   	pop    %edi
     bac:	5d                   	pop    %ebp
     bad:	c3                   	ret
     bae:	66 90                	xchg   %ax,%ax
    gettoken(ps, es, 0, 0);
     bb0:	6a 00                	push   $0x0
     bb2:	6a 00                	push   $0x0
     bb4:	57                   	push   %edi
     bb5:	56                   	push   %esi
     bb6:	e8 85 fa ff ff       	call   640 <gettoken>
    cmd = listcmd(cmd, parseline(ps, es));
     bbb:	58                   	pop    %eax
     bbc:	5a                   	pop    %edx
     bbd:	57                   	push   %edi
     bbe:	56                   	push   %esi
     bbf:	e8 5c ff ff ff       	call   b20 <parseline>
  cmd = malloc(sizeof(*cmd));
     bc4:	c7 04 24 0c 00 00 00 	movl   $0xc,(%esp)
    cmd = listcmd(cmd, parseline(ps, es));
     bcb:	89 c7                	mov    %eax,%edi
  cmd = malloc(sizeof(*cmd));
     bcd:	e8 ae 07 00 00       	call   1380 <malloc>
  memset(cmd, 0, sizeof(*cmd));
     bd2:	83 c4 0c             	add    $0xc,%esp
     bd5:	6a 0c                	push   $0xc
  cmd = malloc(sizeof(*cmd));
     bd7:	89 c6                	mov    %eax,%esi
  memset(cmd, 0, sizeof(*cmd));
     bd9:	6a 00                	push   $0x0
     bdb:	50                   	push   %eax
     bdc:	e8 7f 02 00 00       	call   e60 <memset>
  cmd->left = left;
     be1:	89 5e 04             	mov    %ebx,0x4(%esi)
  cmd->right = right;
     be4:	83 c4 10             	add    $0x10,%esp
     be7:	89 f3                	mov    %esi,%ebx
  cmd->type = LIST;
     be9:	c7 06 04 00 00 00    	movl   $0x4,(%esi)
}
     bef:	89 d8                	mov    %ebx,%eax
  cmd->right = right;
     bf1:	89 7e 08             	mov    %edi,0x8(%esi)
}
     bf4:	8d 65 f4             	lea    -0xc(%ebp),%esp
     bf7:	5b                   	pop    %ebx
     bf8:	5e                   	pop    %esi
     bf9:	5f                   	pop    %edi
     bfa:	5d                   	pop    %ebp
     bfb:	c3                   	ret
     bfc:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi

00000c00 <parseblock>:
{
     c00:	55                   	push   %ebp
     c01:	89 e5                	mov    %esp,%ebp
     c03:	57                   	push   %edi
     c04:	56                   	push   %esi
     c05:	53                   	push   %ebx
     c06:	83 ec 10             	sub    $0x10,%esp
     c09:	8b 5d 08             	mov    0x8(%ebp),%ebx
     c0c:	8b 75 0c             	mov    0xc(%ebp),%esi
  if(!peek(ps, es, "("))
     c0f:	68 ac 14 00 00       	push   $0x14ac
     c14:	56                   	push   %esi
     c15:	53                   	push   %ebx
     c16:	e8 95 fb ff ff       	call   7b0 <peek>
     c1b:	83 c4 10             	add    $0x10,%esp
     c1e:	85 c0                	test   %eax,%eax
     c20:	74 4a                	je     c6c <parseblock+0x6c>
  gettoken(ps, es, 0, 0);
     c22:	6a 00                	push   $0x0
     c24:	6a 00                	push   $0x0
     c26:	56                   	push   %esi
     c27:	53                   	push   %ebx
     c28:	e8 13 fa ff ff       	call   640 <gettoken>
  cmd = parseline(ps, es);
     c2d:	58                   	pop    %eax
     c2e:	5a                   	pop    %edx
     c2f:	56                   	push   %esi
     c30:	53                   	push   %ebx
     c31:	e8 ea fe ff ff       	call   b20 <parseline>
  if(!peek(ps, es, ")"))
     c36:	83 c4 0c             	add    $0xc,%esp
     c39:	68 e8 14 00 00       	push   $0x14e8
  cmd = parseline(ps, es);
     c3e:	89 c7                	mov    %eax,%edi
  if(!peek(ps, es, ")"))
     c40:	56                   	push   %esi
     c41:	53                   	push   %ebx
     c42:	e8 69 fb ff ff       	call   7b0 <peek>
     c47:	83 c4 10             	add    $0x10,%esp
     c4a:	85 c0                	test   %eax,%eax
     c4c:	74 2b                	je     c79 <parseblock+0x79>
  gettoken(ps, es, 0, 0);
     c4e:	6a 00                	push   $0x0
     c50:	6a 00                	push   $0x0
     c52:	56                   	push   %esi
     c53:	53                   	push   %ebx
     c54:	e8 e7 f9 ff ff       	call   640 <gettoken>
  cmd = parseredirs(cmd, ps, es);
     c59:	83 c4 0c             	add    $0xc,%esp
     c5c:	56                   	push   %esi
     c5d:	53                   	push   %ebx
     c5e:	57                   	push   %edi
     c5f:	e8 cc fb ff ff       	call   830 <parseredirs>
}
     c64:	8d 65 f4             	lea    -0xc(%ebp),%esp
     c67:	5b                   	pop    %ebx
     c68:	5e                   	pop    %esi
     c69:	5f                   	pop    %edi
     c6a:	5d                   	pop    %ebp
     c6b:	c3                   	ret
    panic("parseblock");
     c6c:	83 ec 0c             	sub    $0xc,%esp
     c6f:	68 cc 14 00 00       	push   $0x14cc
     c74:	e8 d7 f6 ff ff       	call   350 <panic>
    panic("syntax - missing )");
     c79:	83 ec 0c             	sub    $0xc,%esp
     c7c:	68 d7 14 00 00       	push   $0x14d7
     c81:	e8 ca f6 ff ff       	call   350 <panic>
     c86:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
     c8d:	8d 76 00             	lea    0x0(%esi),%esi

00000c90 <nulterminate>:

// NUL-terminate all the counted strings.
struct cmd*
nulterminate(struct cmd *cmd)
{
     c90:	55                   	push   %ebp
     c91:	89 e5                	mov    %esp,%ebp
     c93:	53                   	push   %ebx
     c94:	83 ec 04             	sub    $0x4,%esp
     c97:	8b 5d 08             	mov    0x8(%ebp),%ebx
  struct execcmd *ecmd;
  struct listcmd *lcmd;
  struct pipecmd *pcmd;
  struct redircmd *rcmd;

  if(cmd == 0)
     c9a:	85 db                	test   %ebx,%ebx
     c9c:	0f 84 7e 00 00 00    	je     d20 <nulterminate+0x90>
    return 0;

  switch(cmd->type){
     ca2:	83 3b 05             	cmpl   $0x5,(%ebx)
     ca5:	77 20                	ja     cc7 <nulterminate+0x37>
     ca7:	8b 03                	mov    (%ebx),%eax
     ca9:	ff 24 85 40 15 00 00 	jmp    *0x1540(,%eax,4)
    nulterminate(pcmd->right);
    break;

  case LIST:
    lcmd = (struct listcmd*)cmd;
    nulterminate(lcmd->left);
     cb0:	83 ec 0c             	sub    $0xc,%esp
     cb3:	ff 73 04             	push   0x4(%ebx)
     cb6:	e8 d5 ff ff ff       	call   c90 <nulterminate>
    nulterminate(lcmd->right);
     cbb:	58                   	pop    %eax
     cbc:	ff 73 08             	push   0x8(%ebx)
     cbf:	e8 cc ff ff ff       	call   c90 <nulterminate>
    break;
     cc4:	83 c4 10             	add    $0x10,%esp
    return 0;
     cc7:	89 d8                	mov    %ebx,%eax
    bcmd = (struct backcmd*)cmd;
    nulterminate(bcmd->cmd);
    break;
  }
  return cmd;
}
     cc9:	8b 5d fc             	mov    -0x4(%ebp),%ebx
     ccc:	c9                   	leave
     ccd:	c3                   	ret
     cce:	66 90                	xchg   %ax,%ax
    nulterminate(bcmd->cmd);
     cd0:	83 ec 0c             	sub    $0xc,%esp
     cd3:	ff 73 04             	push   0x4(%ebx)
     cd6:	e8 b5 ff ff ff       	call   c90 <nulterminate>
    break;
     cdb:	83 c4 10             	add    $0x10,%esp
     cde:	eb e7                	jmp    cc7 <nulterminate+0x37>
    for(i=0; ecmd->argv[i]; i++)
     ce0:	8b 4b 04             	mov    0x4(%ebx),%ecx
     ce3:	8d 43 08             	lea    0x8(%ebx),%eax
     ce6:	85 c9                	test   %ecx,%ecx
     ce8:	74 dd                	je     cc7 <nulterminate+0x37>
     cea:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
      *ecmd->eargv[i] = 0;
     cf0:	8b 50 24             	mov    0x24(%eax),%edx
    for(i=0; ecmd->argv[i]; i++)
     cf3:	83 c0 04             	add    $0x4,%eax
      *ecmd->eargv[i] = 0;
     cf6:	c6 02 00             	movb   $0x0,(%edx)
    for(i=0; ecmd->argv[i]; i++)
     cf9:	8b 50 fc             	mov    -0x4(%eax),%edx
     cfc:	85 d2                	test   %edx,%edx
     cfe:	75 f0                	jne    cf0 <nulterminate+0x60>
     d00:	eb c5                	jmp    cc7 <nulterminate+0x37>
     d02:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
    nulterminate(rcmd->cmd);
     d08:	83 ec 0c             	sub    $0xc,%esp
     d0b:	ff 73 04             	push   0x4(%ebx)
     d0e:	e8 7d ff ff ff       	call   c90 <nulterminate>
    *rcmd->efile = 0;
     d13:	8b 43 0c             	mov    0xc(%ebx),%eax
    break;
     d16:	83 c4 10             	add    $0x10,%esp
    *rcmd->efile = 0;
     d19:	c6 00 00             	movb   $0x0,(%eax)
    break;
     d1c:	eb a9                	jmp    cc7 <nulterminate+0x37>
     d1e:	66 90                	xchg   %ax,%ax
    return 0;
     d20:	31 c0                	xor    %eax,%eax
     d22:	eb a5                	jmp    cc9 <nulterminate+0x39>
     d24:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
     d2b:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
     d2f:	90                   	nop

00000d30 <parsecmd>:
{
     d30:	55                   	push   %ebp
     d31:	89 e5                	mov    %esp,%ebp
     d33:	57                   	push   %edi
     d34:	56                   	push   %esi
  cmd = parseline(&s, es);
     d35:	8d 7d 08             	lea    0x8(%ebp),%edi
{
     d38:	53                   	push   %ebx
     d39:	83 ec 18             	sub    $0x18,%esp
  es = s + strlen(s);
     d3c:	8b 5d 08             	mov    0x8(%ebp),%ebx
     d3f:	53                   	push   %ebx
     d40:	e8 eb 00 00 00       	call   e30 <strlen>
  cmd = parseline(&s, es);
     d45:	59                   	pop    %ecx
     d46:	5e                   	pop    %esi
  es = s + strlen(s);
     d47:	01 c3                	add    %eax,%ebx
  cmd = parseline(&s, es);
     d49:	53                   	push   %ebx
     d4a:	57                   	push   %edi
     d4b:	e8 d0 fd ff ff       	call   b20 <parseline>
  peek(&s, es, "");
     d50:	83 c4 0c             	add    $0xc,%esp
     d53:	68 f8 14 00 00       	push   $0x14f8
  cmd = parseline(&s, es);
     d58:	89 c6                	mov    %eax,%esi
  peek(&s, es, "");
     d5a:	53                   	push   %ebx
     d5b:	57                   	push   %edi
     d5c:	e8 4f fa ff ff       	call   7b0 <peek>
  if(s != es){
     d61:	8b 45 08             	mov    0x8(%ebp),%eax
     d64:	83 c4 10             	add    $0x10,%esp
     d67:	39 d8                	cmp    %ebx,%eax
     d69:	75 13                	jne    d7e <parsecmd+0x4e>
  nulterminate(cmd);
     d6b:	83 ec 0c             	sub    $0xc,%esp
     d6e:	56                   	push   %esi
     d6f:	e8 1c ff ff ff       	call   c90 <nulterminate>
}
     d74:	8d 65 f4             	lea    -0xc(%ebp),%esp
     d77:	89 f0                	mov    %esi,%eax
     d79:	5b                   	pop    %ebx
     d7a:	5e                   	pop    %esi
     d7b:	5f                   	pop    %edi
     d7c:	5d                   	pop    %ebp
     d7d:	c3                   	ret
    printf(2, "leftovers: %s\n", s);
     d7e:	52                   	push   %edx
     d7f:	50                   	push   %eax
     d80:	68 ea 14 00 00       	push   $0x14ea
     d85:	6a 02                	push   $0x2
     d87:	e8 b4 03 00 00       	call   1140 <printf>
    panic("syntax");
     d8c:	c7 04 24 ae 14 00 00 	movl   $0x14ae,(%esp)
     d93:	e8 b8 f5 ff ff       	call   350 <panic>
     d98:	66 90                	xchg   %ax,%ax
     d9a:	66 90                	xchg   %ax,%ax
     d9c:	66 90                	xchg   %ax,%ax
     d9e:	66 90                	xchg   %ax,%ax

00000da0 <strcpy>:
#include "user.h"
#include "x86.h"

char*
strcpy(char *s, char *t)
{
     da0:	55                   	push   %ebp
  char *os;

  os = s;
  while((*s++ = *t++) != 0)
     da1:	31 c0                	xor    %eax,%eax
{
     da3:	89 e5                	mov    %esp,%ebp
     da5:	53                   	push   %ebx
     da6:	8b 4d 08             	mov    0x8(%ebp),%ecx
     da9:	8b 5d 0c             	mov    0xc(%ebp),%ebx
     dac:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
  while((*s++ = *t++) != 0)
     db0:	0f b6 14 03          	movzbl (%ebx,%eax,1),%edx
     db4:	88 14 01             	mov    %dl,(%ecx,%eax,1)
     db7:	83 c0 01             	add    $0x1,%eax
     dba:	84 d2                	test   %dl,%dl
     dbc:	75 f2                	jne    db0 <strcpy+0x10>
    ;
  return os;
}
     dbe:	8b 5d fc             	mov    -0x4(%ebp),%ebx
     dc1:	89 c8                	mov    %ecx,%eax
     dc3:	c9                   	leave
     dc4:	c3                   	ret
     dc5:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
     dcc:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi

00000dd0 <strcmp>:

int
strcmp(const char *p, const char *q)
{
     dd0:	55                   	push   %ebp
     dd1:	89 e5                	mov    %esp,%ebp
     dd3:	53                   	push   %ebx
     dd4:	8b 55 08             	mov    0x8(%ebp),%edx
     dd7:	8b 4d 0c             	mov    0xc(%ebp),%ecx
  while(*p && *p == *q)
     dda:	0f b6 02             	movzbl (%edx),%eax
     ddd:	84 c0                	test   %al,%al
     ddf:	75 17                	jne    df8 <strcmp+0x28>
     de1:	eb 3a                	jmp    e1d <strcmp+0x4d>
     de3:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
     de7:	90                   	nop
     de8:	0f b6 42 01          	movzbl 0x1(%edx),%eax
    p++, q++;
     dec:	83 c2 01             	add    $0x1,%edx
     def:	8d 59 01             	lea    0x1(%ecx),%ebx
  while(*p && *p == *q)
     df2:	84 c0                	test   %al,%al
     df4:	74 1a                	je     e10 <strcmp+0x40>
    p++, q++;
     df6:	89 d9                	mov    %ebx,%ecx
  while(*p && *p == *q)
     df8:	0f b6 19             	movzbl (%ecx),%ebx
     dfb:	38 c3                	cmp    %al,%bl
     dfd:	74 e9                	je     de8 <strcmp+0x18>
  return (uchar)*p - (uchar)*q;
     dff:	29 d8                	sub    %ebx,%eax
}
     e01:	8b 5d fc             	mov    -0x4(%ebp),%ebx
     e04:	c9                   	leave
     e05:	c3                   	ret
     e06:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
     e0d:	8d 76 00             	lea    0x0(%esi),%esi
  return (uchar)*p - (uchar)*q;
     e10:	0f b6 59 01          	movzbl 0x1(%ecx),%ebx
     e14:	31 c0                	xor    %eax,%eax
     e16:	29 d8                	sub    %ebx,%eax
}
     e18:	8b 5d fc             	mov    -0x4(%ebp),%ebx
     e1b:	c9                   	leave
     e1c:	c3                   	ret
  return (uchar)*p - (uchar)*q;
     e1d:	0f b6 19             	movzbl (%ecx),%ebx
     e20:	31 c0                	xor    %eax,%eax
     e22:	eb db                	jmp    dff <strcmp+0x2f>
     e24:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
     e2b:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
     e2f:	90                   	nop

00000e30 <strlen>:

uint
strlen(char *s)
{
     e30:	55                   	push   %ebp
     e31:	89 e5                	mov    %esp,%ebp
     e33:	8b 55 08             	mov    0x8(%ebp),%edx
  int n;

  for(n = 0; s[n]; n++)
     e36:	80 3a 00             	cmpb   $0x0,(%edx)
     e39:	74 15                	je     e50 <strlen+0x20>
     e3b:	31 c0                	xor    %eax,%eax
     e3d:	8d 76 00             	lea    0x0(%esi),%esi
     e40:	83 c0 01             	add    $0x1,%eax
     e43:	80 3c 02 00          	cmpb   $0x0,(%edx,%eax,1)
     e47:	89 c1                	mov    %eax,%ecx
     e49:	75 f5                	jne    e40 <strlen+0x10>
    ;
  return n;
}
     e4b:	89 c8                	mov    %ecx,%eax
     e4d:	5d                   	pop    %ebp
     e4e:	c3                   	ret
     e4f:	90                   	nop
  for(n = 0; s[n]; n++)
     e50:	31 c9                	xor    %ecx,%ecx
}
     e52:	5d                   	pop    %ebp
     e53:	89 c8                	mov    %ecx,%eax
     e55:	c3                   	ret
     e56:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
     e5d:	8d 76 00             	lea    0x0(%esi),%esi

00000e60 <memset>:

void*
memset(void *dst, int c, uint n)
{
     e60:	55                   	push   %ebp
     e61:	89 e5                	mov    %esp,%ebp
     e63:	57                   	push   %edi
     e64:	8b 55 08             	mov    0x8(%ebp),%edx
}

static inline void
stosb(void *addr, int data, int cnt)
{
  asm volatile("cld; rep stosb" :
     e67:	8b 4d 10             	mov    0x10(%ebp),%ecx
     e6a:	8b 45 0c             	mov    0xc(%ebp),%eax
     e6d:	89 d7                	mov    %edx,%edi
     e6f:	fc                   	cld
     e70:	f3 aa                	rep stos %al,%es:(%edi)
  stosb(dst, c, n);
  return dst;
}
     e72:	8b 7d fc             	mov    -0x4(%ebp),%edi
     e75:	89 d0                	mov    %edx,%eax
     e77:	c9                   	leave
     e78:	c3                   	ret
     e79:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi

00000e80 <strchr>:

char*
strchr(const char *s, char c)
{
     e80:	55                   	push   %ebp
     e81:	89 e5                	mov    %esp,%ebp
     e83:	8b 45 08             	mov    0x8(%ebp),%eax
     e86:	0f b6 4d 0c          	movzbl 0xc(%ebp),%ecx
  for(; *s; s++)
     e8a:	0f b6 10             	movzbl (%eax),%edx
     e8d:	84 d2                	test   %dl,%dl
     e8f:	75 12                	jne    ea3 <strchr+0x23>
     e91:	eb 1d                	jmp    eb0 <strchr+0x30>
     e93:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
     e97:	90                   	nop
     e98:	0f b6 50 01          	movzbl 0x1(%eax),%edx
     e9c:	83 c0 01             	add    $0x1,%eax
     e9f:	84 d2                	test   %dl,%dl
     ea1:	74 0d                	je     eb0 <strchr+0x30>
    if(*s == c)
     ea3:	38 d1                	cmp    %dl,%cl
     ea5:	75 f1                	jne    e98 <strchr+0x18>
      return (char*)s;
  return 0;
}
     ea7:	5d                   	pop    %ebp
     ea8:	c3                   	ret
     ea9:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
  return 0;
     eb0:	31 c0                	xor    %eax,%eax
}
     eb2:	5d                   	pop    %ebp
     eb3:	c3                   	ret
     eb4:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
     ebb:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
     ebf:	90                   	nop

00000ec0 <gets>:

char*
gets(char *buf, int max)
{
     ec0:	55                   	push   %ebp
     ec1:	89 e5                	mov    %esp,%ebp
     ec3:	57                   	push   %edi
     ec4:	56                   	push   %esi
  int i, cc;
  char c;

  for(i=0; i+1 < max; ){
    cc = read(0, &c, 1);
     ec5:	8d 75 e7             	lea    -0x19(%ebp),%esi
{
     ec8:	53                   	push   %ebx
  for(i=0; i+1 < max; ){
     ec9:	31 db                	xor    %ebx,%ebx
{
     ecb:	83 ec 1c             	sub    $0x1c,%esp
  for(i=0; i+1 < max; ){
     ece:	eb 27                	jmp    ef7 <gets+0x37>
    cc = read(0, &c, 1);
     ed0:	83 ec 04             	sub    $0x4,%esp
     ed3:	6a 01                	push   $0x1
     ed5:	56                   	push   %esi
     ed6:	6a 00                	push   $0x0
     ed8:	e8 1e 01 00 00       	call   ffb <read>
    if(cc < 1)
     edd:	83 c4 10             	add    $0x10,%esp
     ee0:	85 c0                	test   %eax,%eax
     ee2:	7e 1d                	jle    f01 <gets+0x41>
      break;
    buf[i++] = c;
     ee4:	0f b6 45 e7          	movzbl -0x19(%ebp),%eax
     ee8:	8b 55 08             	mov    0x8(%ebp),%edx
     eeb:	88 44 1a ff          	mov    %al,-0x1(%edx,%ebx,1)
    if(c == '\n' || c == '\r')
     eef:	3c 0a                	cmp    $0xa,%al
     ef1:	74 10                	je     f03 <gets+0x43>
     ef3:	3c 0d                	cmp    $0xd,%al
     ef5:	74 0c                	je     f03 <gets+0x43>
  for(i=0; i+1 < max; ){
     ef7:	89 df                	mov    %ebx,%edi
     ef9:	83 c3 01             	add    $0x1,%ebx
     efc:	3b 5d 0c             	cmp    0xc(%ebp),%ebx
     eff:	7c cf                	jl     ed0 <gets+0x10>
     f01:	89 fb                	mov    %edi,%ebx
      break;
  }
  buf[i] = '\0';
     f03:	8b 45 08             	mov    0x8(%ebp),%eax
     f06:	c6 04 18 00          	movb   $0x0,(%eax,%ebx,1)
  return buf;
}
     f0a:	8d 65 f4             	lea    -0xc(%ebp),%esp
     f0d:	5b                   	pop    %ebx
     f0e:	5e                   	pop    %esi
     f0f:	5f                   	pop    %edi
     f10:	5d                   	pop    %ebp
     f11:	c3                   	ret
     f12:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
     f19:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi

00000f20 <stat>:

int
stat(char *n, struct stat *st)
{
     f20:	55                   	push   %ebp
     f21:	89 e5                	mov    %esp,%ebp
     f23:	56                   	push   %esi
     f24:	53                   	push   %ebx
  int fd;
  int r;

  fd = open(n, O_RDONLY);
     f25:	83 ec 08             	sub    $0x8,%esp
     f28:	6a 00                	push   $0x0
     f2a:	ff 75 08             	push   0x8(%ebp)
     f2d:	e8 f1 00 00 00       	call   1023 <open>
  if(fd < 0)
     f32:	83 c4 10             	add    $0x10,%esp
     f35:	85 c0                	test   %eax,%eax
     f37:	78 27                	js     f60 <stat+0x40>
    return -1;
  r = fstat(fd, st);
     f39:	83 ec 08             	sub    $0x8,%esp
     f3c:	ff 75 0c             	push   0xc(%ebp)
     f3f:	89 c3                	mov    %eax,%ebx
     f41:	50                   	push   %eax
     f42:	e8 f4 00 00 00       	call   103b <fstat>
  close(fd);
     f47:	89 1c 24             	mov    %ebx,(%esp)
  r = fstat(fd, st);
     f4a:	89 c6                	mov    %eax,%esi
  close(fd);
     f4c:	e8 ba 00 00 00       	call   100b <close>
  return r;
     f51:	83 c4 10             	add    $0x10,%esp
}
     f54:	8d 65 f8             	lea    -0x8(%ebp),%esp
     f57:	89 f0                	mov    %esi,%eax
     f59:	5b                   	pop    %ebx
     f5a:	5e                   	pop    %esi
     f5b:	5d                   	pop    %ebp
     f5c:	c3                   	ret
     f5d:	8d 76 00             	lea    0x0(%esi),%esi
    return -1;
     f60:	be ff ff ff ff       	mov    $0xffffffff,%esi
     f65:	eb ed                	jmp    f54 <stat+0x34>
     f67:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
     f6e:	66 90                	xchg   %ax,%ax

00000f70 <atoi>:

int
atoi(const char *s)
{
     f70:	55                   	push   %ebp
     f71:	89 e5                	mov    %esp,%ebp
     f73:	53                   	push   %ebx
     f74:	8b 55 08             	mov    0x8(%ebp),%edx
  int n;

  n = 0;
  while('0' <= *s && *s <= '9')
     f77:	0f be 02             	movsbl (%edx),%eax
     f7a:	8d 48 d0             	lea    -0x30(%eax),%ecx
     f7d:	80 f9 09             	cmp    $0x9,%cl
  n = 0;
     f80:	b9 00 00 00 00       	mov    $0x0,%ecx
  while('0' <= *s && *s <= '9')
     f85:	77 1e                	ja     fa5 <atoi+0x35>
     f87:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
     f8e:	66 90                	xchg   %ax,%ax
    n = n*10 + *s++ - '0';
     f90:	83 c2 01             	add    $0x1,%edx
     f93:	8d 0c 89             	lea    (%ecx,%ecx,4),%ecx
     f96:	8d 4c 48 d0          	lea    -0x30(%eax,%ecx,2),%ecx
  while('0' <= *s && *s <= '9')
     f9a:	0f be 02             	movsbl (%edx),%eax
     f9d:	8d 58 d0             	lea    -0x30(%eax),%ebx
     fa0:	80 fb 09             	cmp    $0x9,%bl
     fa3:	76 eb                	jbe    f90 <atoi+0x20>
  return n;
}
     fa5:	8b 5d fc             	mov    -0x4(%ebp),%ebx
     fa8:	89 c8                	mov    %ecx,%eax
     faa:	c9                   	leave
     fab:	c3                   	ret
     fac:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi

00000fb0 <memmove>:

void*
memmove(void *vdst, void *vsrc, int n)
{
     fb0:	55                   	push   %ebp
     fb1:	89 e5                	mov    %esp,%ebp
     fb3:	57                   	push   %edi
     fb4:	56                   	push   %esi
     fb5:	8b 45 10             	mov    0x10(%ebp),%eax
     fb8:	8b 55 08             	mov    0x8(%ebp),%edx
     fbb:	8b 75 0c             	mov    0xc(%ebp),%esi
  char *dst, *src;

  dst = vdst;
  src = vsrc;
  while(n-- > 0)
     fbe:	85 c0                	test   %eax,%eax
     fc0:	7e 13                	jle    fd5 <memmove+0x25>
     fc2:	01 d0                	add    %edx,%eax
  dst = vdst;
     fc4:	89 d7                	mov    %edx,%edi
     fc6:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
     fcd:	8d 76 00             	lea    0x0(%esi),%esi
    *dst++ = *src++;
     fd0:	a4                   	movsb  %ds:(%esi),%es:(%edi)
  while(n-- > 0)
     fd1:	39 f8                	cmp    %edi,%eax
     fd3:	75 fb                	jne    fd0 <memmove+0x20>
  return vdst;
}
     fd5:	5e                   	pop    %esi
     fd6:	89 d0                	mov    %edx,%eax
     fd8:	5f                   	pop    %edi
     fd9:	5d                   	pop    %ebp
     fda:	c3                   	ret

00000fdb <fork>:
  name: \
    movl $SYS_ ## name, %eax; \
    int $T_SYSCALL; \
    ret

SYSCALL(fork)
     fdb:	b8 01 00 00 00       	mov    $0x1,%eax
     fe0:	cd 40                	int    $0x40
     fe2:	c3                   	ret

00000fe3 <exit>:
SYSCALL(exit)
     fe3:	b8 02 00 00 00       	mov    $0x2,%eax
     fe8:	cd 40                	int    $0x40
     fea:	c3                   	ret

00000feb <wait>:
SYSCALL(wait)
     feb:	b8 03 00 00 00       	mov    $0x3,%eax
     ff0:	cd 40                	int    $0x40
     ff2:	c3                   	ret

00000ff3 <pipe>:
SYSCALL(pipe)
     ff3:	b8 04 00 00 00       	mov    $0x4,%eax
     ff8:	cd 40                	int    $0x40
     ffa:	c3                   	ret

00000ffb <read>:
SYSCALL(read)
     ffb:	b8 05 00 00 00       	mov    $0x5,%eax
    1000:	cd 40                	int    $0x40
    1002:	c3                   	ret

00001003 <write>:
SYSCALL(write)
    1003:	b8 10 00 00 00       	mov    $0x10,%eax
    1008:	cd 40                	int    $0x40
    100a:	c3                   	ret

0000100b <close>:
SYSCALL(close)
    100b:	b8 15 00 00 00       	mov    $0x15,%eax
    1010:	cd 40                	int    $0x40
    1012:	c3                   	ret

00001013 <kill>:
SYSCALL(kill)
    1013:	b8 06 00 00 00       	mov    $0x6,%eax
    1018:	cd 40                	int    $0x40
    101a:	c3                   	ret

0000101b <exec>:
SYSCALL(exec)
    101b:	b8 07 00 00 00       	mov    $0x7,%eax
    1020:	cd 40                	int    $0x40
    1022:	c3                   	ret

00001023 <open>:
SYSCALL(open)
    1023:	b8 0f 00 00 00       	mov    $0xf,%eax
    1028:	cd 40                	int    $0x40
    102a:	c3                   	ret

0000102b <mknod>:
SYSCALL(mknod)
    102b:	b8 11 00 00 00       	mov    $0x11,%eax
    1030:	cd 40                	int    $0x40
    1032:	c3                   	ret

00001033 <unlink>:
SYSCALL(unlink)
    1033:	b8 12 00 00 00       	mov    $0x12,%eax
    1038:	cd 40                	int    $0x40
    103a:	c3                   	ret

0000103b <fstat>:
SYSCALL(fstat)
    103b:	b8 08 00 00 00       	mov    $0x8,%eax
    1040:	cd 40                	int    $0x40
    1042:	c3                   	ret

00001043 <link>:
SYSCALL(link)
    1043:	b8 13 00 00 00       	mov    $0x13,%eax
    1048:	cd 40                	int    $0x40
    104a:	c3                   	ret

0000104b <mkdir>:
SYSCALL(mkdir)
    104b:	b8 14 00 00 00       	mov    $0x14,%eax
    1050:	cd 40                	int    $0x40
    1052:	c3                   	ret

00001053 <chdir>:
SYSCALL(chdir)
    1053:	b8 09 00 00 00       	mov    $0x9,%eax
    1058:	cd 40                	int    $0x40
    105a:	c3                   	ret

0000105b <dup>:
SYSCALL(dup)
    105b:	b8 0a 00 00 00       	mov    $0xa,%eax
    1060:	cd 40                	int    $0x40
    1062:	c3                   	ret

00001063 <getpid>:
SYSCALL(getpid)
    1063:	b8 0b 00 00 00       	mov    $0xb,%eax
    1068:	cd 40                	int    $0x40
    106a:	c3                   	ret

0000106b <sbrk>:
SYSCALL(sbrk)
    106b:	b8 0c 00 00 00       	mov    $0xc,%eax
    1070:	cd 40                	int    $0x40
    1072:	c3                   	ret

00001073 <sleep>:
SYSCALL(sleep)
    1073:	b8 0d 00 00 00       	mov    $0xd,%eax
    1078:	cd 40                	int    $0x40
    107a:	c3                   	ret

0000107b <uptime>:
SYSCALL(uptime)
    107b:	b8 0e 00 00 00       	mov    $0xe,%eax
    1080:	cd 40                	int    $0x40
    1082:	c3                   	ret

00001083 <shutdown>:
SYSCALL(shutdown)
    1083:	b8 16 00 00 00       	mov    $0x16,%eax
    1088:	cd 40                	int    $0x40
    108a:	c3                   	ret

0000108b <cps>:
SYSCALL(cps)
    108b:	b8 17 00 00 00       	mov    $0x17,%eax
    1090:	cd 40                	int    $0x40
    1092:	c3                   	ret

00001093 <chpr>:
SYSCALL(chpr)
    1093:	b8 18 00 00 00       	mov    $0x18,%eax
    1098:	cd 40                	int    $0x40
    109a:	c3                   	ret
    109b:	66 90                	xchg   %ax,%ax
    109d:	66 90                	xchg   %ax,%ax
    109f:	90                   	nop

000010a0 <printint>:
  write(fd, &c, 1);
}

static void
printint(int fd, int xx, int base, int sgn)
{
    10a0:	55                   	push   %ebp
    10a1:	89 e5                	mov    %esp,%ebp
    10a3:	57                   	push   %edi
    10a4:	56                   	push   %esi
    10a5:	53                   	push   %ebx
    10a6:	89 cb                	mov    %ecx,%ebx
  uint x;

  neg = 0;
  if(sgn && xx < 0){
    neg = 1;
    x = -xx;
    10a8:	89 d1                	mov    %edx,%ecx
{
    10aa:	83 ec 3c             	sub    $0x3c,%esp
    10ad:	89 45 c0             	mov    %eax,-0x40(%ebp)
  if(sgn && xx < 0){
    10b0:	85 d2                	test   %edx,%edx
    10b2:	0f 89 80 00 00 00    	jns    1138 <printint+0x98>
    10b8:	f6 45 08 01          	testb  $0x1,0x8(%ebp)
    10bc:	74 7a                	je     1138 <printint+0x98>
    x = -xx;
    10be:	f7 d9                	neg    %ecx
    neg = 1;
    10c0:	b8 01 00 00 00       	mov    $0x1,%eax
  } else {
    x = xx;
  }

  i = 0;
    10c5:	89 45 c4             	mov    %eax,-0x3c(%ebp)
    10c8:	31 f6                	xor    %esi,%esi
    10ca:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
  do{
    buf[i++] = digits[x % base];
    10d0:	89 c8                	mov    %ecx,%eax
    10d2:	31 d2                	xor    %edx,%edx
    10d4:	89 f7                	mov    %esi,%edi
    10d6:	f7 f3                	div    %ebx
    10d8:	8d 76 01             	lea    0x1(%esi),%esi
    10db:	0f b6 92 b8 15 00 00 	movzbl 0x15b8(%edx),%edx
    10e2:	88 54 35 d7          	mov    %dl,-0x29(%ebp,%esi,1)
  }while((x /= base) != 0);
    10e6:	89 ca                	mov    %ecx,%edx
    10e8:	89 c1                	mov    %eax,%ecx
    10ea:	39 da                	cmp    %ebx,%edx
    10ec:	73 e2                	jae    10d0 <printint+0x30>
  if(neg)
    10ee:	8b 45 c4             	mov    -0x3c(%ebp),%eax
    10f1:	85 c0                	test   %eax,%eax
    10f3:	74 07                	je     10fc <printint+0x5c>
    buf[i++] = '-';
    10f5:	c6 44 35 d8 2d       	movb   $0x2d,-0x28(%ebp,%esi,1)
    buf[i++] = digits[x % base];
    10fa:	89 f7                	mov    %esi,%edi
    10fc:	8d 5d d8             	lea    -0x28(%ebp),%ebx
    10ff:	8b 75 c0             	mov    -0x40(%ebp),%esi
    1102:	01 df                	add    %ebx,%edi
    1104:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi

  while(--i >= 0)
    putc(fd, buf[i]);
    1108:	0f b6 07             	movzbl (%edi),%eax
  write(fd, &c, 1);
    110b:	83 ec 04             	sub    $0x4,%esp
    110e:	88 45 d7             	mov    %al,-0x29(%ebp)
    1111:	8d 45 d7             	lea    -0x29(%ebp),%eax
    1114:	6a 01                	push   $0x1
    1116:	50                   	push   %eax
    1117:	56                   	push   %esi
    1118:	e8 e6 fe ff ff       	call   1003 <write>
  while(--i >= 0)
    111d:	89 f8                	mov    %edi,%eax
    111f:	83 c4 10             	add    $0x10,%esp
    1122:	83 ef 01             	sub    $0x1,%edi
    1125:	39 d8                	cmp    %ebx,%eax
    1127:	75 df                	jne    1108 <printint+0x68>
}
    1129:	8d 65 f4             	lea    -0xc(%ebp),%esp
    112c:	5b                   	pop    %ebx
    112d:	5e                   	pop    %esi
    112e:	5f                   	pop    %edi
    112f:	5d                   	pop    %ebp
    1130:	c3                   	ret
    1131:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
  neg = 0;
    1138:	31 c0                	xor    %eax,%eax
    113a:	eb 89                	jmp    10c5 <printint+0x25>
    113c:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi

00001140 <printf>:

// Print to the given fd. Only understands %d, %x, %p, %s.
void
printf(int fd, char *fmt, ...)
{
    1140:	55                   	push   %ebp
    1141:	89 e5                	mov    %esp,%ebp
    1143:	57                   	push   %edi
    1144:	56                   	push   %esi
    1145:	53                   	push   %ebx
    1146:	83 ec 2c             	sub    $0x2c,%esp
  int c, i, state;
  uint *ap;

  state = 0;
  ap = (uint*)(void*)&fmt + 1;
  for(i = 0; fmt[i]; i++){
    1149:	8b 75 0c             	mov    0xc(%ebp),%esi
{
    114c:	8b 7d 08             	mov    0x8(%ebp),%edi
  for(i = 0; fmt[i]; i++){
    114f:	0f b6 1e             	movzbl (%esi),%ebx
    1152:	83 c6 01             	add    $0x1,%esi
    1155:	84 db                	test   %bl,%bl
    1157:	74 67                	je     11c0 <printf+0x80>
    1159:	8d 4d 10             	lea    0x10(%ebp),%ecx
    115c:	31 d2                	xor    %edx,%edx
    115e:	89 4d d0             	mov    %ecx,-0x30(%ebp)
    1161:	eb 34                	jmp    1197 <printf+0x57>
    1163:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
    1167:	90                   	nop
    1168:	89 55 d4             	mov    %edx,-0x2c(%ebp)
    c = fmt[i] & 0xff;
    if(state == 0){
      if(c == '%'){
        state = '%';
    116b:	ba 25 00 00 00       	mov    $0x25,%edx
      if(c == '%'){
    1170:	83 f8 25             	cmp    $0x25,%eax
    1173:	74 18                	je     118d <printf+0x4d>
  write(fd, &c, 1);
    1175:	83 ec 04             	sub    $0x4,%esp
    1178:	8d 45 e7             	lea    -0x19(%ebp),%eax
    117b:	88 5d e7             	mov    %bl,-0x19(%ebp)
    117e:	6a 01                	push   $0x1
    1180:	50                   	push   %eax
    1181:	57                   	push   %edi
    1182:	e8 7c fe ff ff       	call   1003 <write>
    1187:	8b 55 d4             	mov    -0x2c(%ebp),%edx
      } else {
        putc(fd, c);
    118a:	83 c4 10             	add    $0x10,%esp
  for(i = 0; fmt[i]; i++){
    118d:	0f b6 1e             	movzbl (%esi),%ebx
    1190:	83 c6 01             	add    $0x1,%esi
    1193:	84 db                	test   %bl,%bl
    1195:	74 29                	je     11c0 <printf+0x80>
    c = fmt[i] & 0xff;
    1197:	0f b6 c3             	movzbl %bl,%eax
    if(state == 0){
    119a:	85 d2                	test   %edx,%edx
    119c:	74 ca                	je     1168 <printf+0x28>
      }
    } else if(state == '%'){
    119e:	83 fa 25             	cmp    $0x25,%edx
    11a1:	75 ea                	jne    118d <printf+0x4d>
      if(c == 'd'){
    11a3:	83 f8 25             	cmp    $0x25,%eax
    11a6:	0f 84 24 01 00 00    	je     12d0 <printf+0x190>
    11ac:	83 e8 63             	sub    $0x63,%eax
    11af:	83 f8 15             	cmp    $0x15,%eax
    11b2:	77 1c                	ja     11d0 <printf+0x90>
    11b4:	ff 24 85 60 15 00 00 	jmp    *0x1560(,%eax,4)
    11bb:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
    11bf:	90                   	nop
        putc(fd, c);
      }
      state = 0;
    }
  }
}
    11c0:	8d 65 f4             	lea    -0xc(%ebp),%esp
    11c3:	5b                   	pop    %ebx
    11c4:	5e                   	pop    %esi
    11c5:	5f                   	pop    %edi
    11c6:	5d                   	pop    %ebp
    11c7:	c3                   	ret
    11c8:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
    11cf:	90                   	nop
  write(fd, &c, 1);
    11d0:	83 ec 04             	sub    $0x4,%esp
    11d3:	8d 55 e7             	lea    -0x19(%ebp),%edx
    11d6:	c6 45 e7 25          	movb   $0x25,-0x19(%ebp)
    11da:	6a 01                	push   $0x1
    11dc:	52                   	push   %edx
    11dd:	89 55 d4             	mov    %edx,-0x2c(%ebp)
    11e0:	57                   	push   %edi
    11e1:	e8 1d fe ff ff       	call   1003 <write>
    11e6:	83 c4 0c             	add    $0xc,%esp
    11e9:	88 5d e7             	mov    %bl,-0x19(%ebp)
    11ec:	6a 01                	push   $0x1
    11ee:	8b 55 d4             	mov    -0x2c(%ebp),%edx
    11f1:	52                   	push   %edx
    11f2:	57                   	push   %edi
    11f3:	e8 0b fe ff ff       	call   1003 <write>
        putc(fd, c);
    11f8:	83 c4 10             	add    $0x10,%esp
      state = 0;
    11fb:	31 d2                	xor    %edx,%edx
    11fd:	eb 8e                	jmp    118d <printf+0x4d>
    11ff:	90                   	nop
        printint(fd, *ap, 16, 0);
    1200:	8b 5d d0             	mov    -0x30(%ebp),%ebx
    1203:	83 ec 0c             	sub    $0xc,%esp
    1206:	b9 10 00 00 00       	mov    $0x10,%ecx
    120b:	8b 13                	mov    (%ebx),%edx
    120d:	6a 00                	push   $0x0
    120f:	89 f8                	mov    %edi,%eax
        ap++;
    1211:	83 c3 04             	add    $0x4,%ebx
        printint(fd, *ap, 16, 0);
    1214:	e8 87 fe ff ff       	call   10a0 <printint>
        ap++;
    1219:	89 5d d0             	mov    %ebx,-0x30(%ebp)
    121c:	83 c4 10             	add    $0x10,%esp
      state = 0;
    121f:	31 d2                	xor    %edx,%edx
    1221:	e9 67 ff ff ff       	jmp    118d <printf+0x4d>
    1226:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
    122d:	8d 76 00             	lea    0x0(%esi),%esi
        s = (char*)*ap;
    1230:	8b 45 d0             	mov    -0x30(%ebp),%eax
    1233:	8b 18                	mov    (%eax),%ebx
        ap++;
    1235:	83 c0 04             	add    $0x4,%eax
    1238:	89 45 d0             	mov    %eax,-0x30(%ebp)
        if(s == 0)
    123b:	85 db                	test   %ebx,%ebx
    123d:	0f 84 9d 00 00 00    	je     12e0 <printf+0x1a0>
        while(*s != 0){
    1243:	0f b6 03             	movzbl (%ebx),%eax
      state = 0;
    1246:	31 d2                	xor    %edx,%edx
        while(*s != 0){
    1248:	84 c0                	test   %al,%al
    124a:	0f 84 3d ff ff ff    	je     118d <printf+0x4d>
    1250:	8d 55 e7             	lea    -0x19(%ebp),%edx
    1253:	89 75 d4             	mov    %esi,-0x2c(%ebp)
    1256:	89 de                	mov    %ebx,%esi
    1258:	89 d3                	mov    %edx,%ebx
    125a:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
  write(fd, &c, 1);
    1260:	83 ec 04             	sub    $0x4,%esp
    1263:	88 45 e7             	mov    %al,-0x19(%ebp)
          s++;
    1266:	83 c6 01             	add    $0x1,%esi
  write(fd, &c, 1);
    1269:	6a 01                	push   $0x1
    126b:	53                   	push   %ebx
    126c:	57                   	push   %edi
    126d:	e8 91 fd ff ff       	call   1003 <write>
        while(*s != 0){
    1272:	0f b6 06             	movzbl (%esi),%eax
    1275:	83 c4 10             	add    $0x10,%esp
    1278:	84 c0                	test   %al,%al
    127a:	75 e4                	jne    1260 <printf+0x120>
      state = 0;
    127c:	8b 75 d4             	mov    -0x2c(%ebp),%esi
    127f:	31 d2                	xor    %edx,%edx
    1281:	e9 07 ff ff ff       	jmp    118d <printf+0x4d>
    1286:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
    128d:	8d 76 00             	lea    0x0(%esi),%esi
        printint(fd, *ap, 10, 1);
    1290:	8b 5d d0             	mov    -0x30(%ebp),%ebx
    1293:	83 ec 0c             	sub    $0xc,%esp
    1296:	b9 0a 00 00 00       	mov    $0xa,%ecx
    129b:	8b 13                	mov    (%ebx),%edx
    129d:	6a 01                	push   $0x1
    129f:	e9 6b ff ff ff       	jmp    120f <printf+0xcf>
    12a4:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
        putc(fd, *ap);
    12a8:	8b 5d d0             	mov    -0x30(%ebp),%ebx
  write(fd, &c, 1);
    12ab:	83 ec 04             	sub    $0x4,%esp
    12ae:	8d 55 e7             	lea    -0x19(%ebp),%edx
        putc(fd, *ap);
    12b1:	8b 03                	mov    (%ebx),%eax
        ap++;
    12b3:	83 c3 04             	add    $0x4,%ebx
        putc(fd, *ap);
    12b6:	88 45 e7             	mov    %al,-0x19(%ebp)
  write(fd, &c, 1);
    12b9:	6a 01                	push   $0x1
    12bb:	52                   	push   %edx
    12bc:	57                   	push   %edi
    12bd:	e8 41 fd ff ff       	call   1003 <write>
        ap++;
    12c2:	89 5d d0             	mov    %ebx,-0x30(%ebp)
    12c5:	83 c4 10             	add    $0x10,%esp
      state = 0;
    12c8:	31 d2                	xor    %edx,%edx
    12ca:	e9 be fe ff ff       	jmp    118d <printf+0x4d>
    12cf:	90                   	nop
  write(fd, &c, 1);
    12d0:	83 ec 04             	sub    $0x4,%esp
    12d3:	88 5d e7             	mov    %bl,-0x19(%ebp)
    12d6:	8d 55 e7             	lea    -0x19(%ebp),%edx
    12d9:	6a 01                	push   $0x1
    12db:	e9 11 ff ff ff       	jmp    11f1 <printf+0xb1>
    12e0:	b8 28 00 00 00       	mov    $0x28,%eax
          s = "(null)";
    12e5:	bb 58 15 00 00       	mov    $0x1558,%ebx
    12ea:	e9 61 ff ff ff       	jmp    1250 <printf+0x110>
    12ef:	90                   	nop

000012f0 <free>:
static Header base;
static Header *freep;

void
free(void *ap)
{
    12f0:	55                   	push   %ebp
  Header *bp, *p;

  bp = (Header*)ap - 1;
  for(p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
    12f1:	a1 24 20 00 00       	mov    0x2024,%eax
{
    12f6:	89 e5                	mov    %esp,%ebp
    12f8:	57                   	push   %edi
    12f9:	56                   	push   %esi
    12fa:	53                   	push   %ebx
    12fb:	8b 5d 08             	mov    0x8(%ebp),%ebx
  bp = (Header*)ap - 1;
    12fe:	8d 4b f8             	lea    -0x8(%ebx),%ecx
  for(p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
    1301:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
    1308:	89 c2                	mov    %eax,%edx
    if(p >= p->s.ptr && (bp > p || bp < p->s.ptr))
    130a:	8b 00                	mov    (%eax),%eax
  for(p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
    130c:	39 ca                	cmp    %ecx,%edx
    130e:	73 30                	jae    1340 <free+0x50>
    1310:	39 c1                	cmp    %eax,%ecx
    1312:	72 04                	jb     1318 <free+0x28>
    if(p >= p->s.ptr && (bp > p || bp < p->s.ptr))
    1314:	39 c2                	cmp    %eax,%edx
    1316:	72 f0                	jb     1308 <free+0x18>
      break;
  if(bp + bp->s.size == p->s.ptr){
    1318:	8b 73 fc             	mov    -0x4(%ebx),%esi
    131b:	8d 3c f1             	lea    (%ecx,%esi,8),%edi
    131e:	39 f8                	cmp    %edi,%eax
    1320:	74 2e                	je     1350 <free+0x60>
    bp->s.size += p->s.ptr->s.size;
    bp->s.ptr = p->s.ptr->s.ptr;
    1322:	89 43 f8             	mov    %eax,-0x8(%ebx)
  } else
    bp->s.ptr = p->s.ptr;
  if(p + p->s.size == bp){
    1325:	8b 42 04             	mov    0x4(%edx),%eax
    1328:	8d 34 c2             	lea    (%edx,%eax,8),%esi
    132b:	39 f1                	cmp    %esi,%ecx
    132d:	74 38                	je     1367 <free+0x77>
    p->s.size += bp->s.size;
    p->s.ptr = bp->s.ptr;
    132f:	89 0a                	mov    %ecx,(%edx)
  } else
    p->s.ptr = bp;
  freep = p;
}
    1331:	5b                   	pop    %ebx
  freep = p;
    1332:	89 15 24 20 00 00    	mov    %edx,0x2024
}
    1338:	5e                   	pop    %esi
    1339:	5f                   	pop    %edi
    133a:	5d                   	pop    %ebp
    133b:	c3                   	ret
    133c:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
    if(p >= p->s.ptr && (bp > p || bp < p->s.ptr))
    1340:	39 c1                	cmp    %eax,%ecx
    1342:	72 d0                	jb     1314 <free+0x24>
    1344:	eb c2                	jmp    1308 <free+0x18>
    1346:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
    134d:	8d 76 00             	lea    0x0(%esi),%esi
    bp->s.size += p->s.ptr->s.size;
    1350:	03 70 04             	add    0x4(%eax),%esi
    1353:	89 73 fc             	mov    %esi,-0x4(%ebx)
    bp->s.ptr = p->s.ptr->s.ptr;
    1356:	8b 02                	mov    (%edx),%eax
    1358:	8b 00                	mov    (%eax),%eax
    135a:	89 43 f8             	mov    %eax,-0x8(%ebx)
  if(p + p->s.size == bp){
    135d:	8b 42 04             	mov    0x4(%edx),%eax
    1360:	8d 34 c2             	lea    (%edx,%eax,8),%esi
    1363:	39 f1                	cmp    %esi,%ecx
    1365:	75 c8                	jne    132f <free+0x3f>
    p->s.size += bp->s.size;
    1367:	03 43 fc             	add    -0x4(%ebx),%eax
  freep = p;
    136a:	89 15 24 20 00 00    	mov    %edx,0x2024
    p->s.size += bp->s.size;
    1370:	89 42 04             	mov    %eax,0x4(%edx)
    p->s.ptr = bp->s.ptr;
    1373:	8b 4b f8             	mov    -0x8(%ebx),%ecx
    1376:	89 0a                	mov    %ecx,(%edx)
}
    1378:	5b                   	pop    %ebx
    1379:	5e                   	pop    %esi
    137a:	5f                   	pop    %edi
    137b:	5d                   	pop    %ebp
    137c:	c3                   	ret
    137d:	8d 76 00             	lea    0x0(%esi),%esi

00001380 <malloc>:
  return freep;
}

void*
malloc(uint nbytes)
{
    1380:	55                   	push   %ebp
    1381:	89 e5                	mov    %esp,%ebp
    1383:	57                   	push   %edi
    1384:	56                   	push   %esi
    1385:	53                   	push   %ebx
    1386:	83 ec 0c             	sub    $0xc,%esp
  Header *p, *prevp;
  uint nunits;

  nunits = (nbytes + sizeof(Header) - 1)/sizeof(Header) + 1;
    1389:	8b 45 08             	mov    0x8(%ebp),%eax
  if((prevp = freep) == 0){
    138c:	8b 15 24 20 00 00    	mov    0x2024,%edx
  nunits = (nbytes + sizeof(Header) - 1)/sizeof(Header) + 1;
    1392:	8d 78 07             	lea    0x7(%eax),%edi
    1395:	c1 ef 03             	shr    $0x3,%edi
    1398:	83 c7 01             	add    $0x1,%edi
  if((prevp = freep) == 0){
    139b:	85 d2                	test   %edx,%edx
    139d:	0f 84 8d 00 00 00    	je     1430 <malloc+0xb0>
    base.s.ptr = freep = prevp = &base;
    base.s.size = 0;
  }
  for(p = prevp->s.ptr; ; prevp = p, p = p->s.ptr){
    13a3:	8b 02                	mov    (%edx),%eax
    if(p->s.size >= nunits){
    13a5:	8b 48 04             	mov    0x4(%eax),%ecx
    13a8:	39 f9                	cmp    %edi,%ecx
    13aa:	73 64                	jae    1410 <malloc+0x90>
  if(nu < 4096)
    13ac:	bb 00 10 00 00       	mov    $0x1000,%ebx
    13b1:	39 df                	cmp    %ebx,%edi
    13b3:	0f 43 df             	cmovae %edi,%ebx
  p = sbrk(nu * sizeof(Header));
    13b6:	8d 34 dd 00 00 00 00 	lea    0x0(,%ebx,8),%esi
    13bd:	eb 0a                	jmp    13c9 <malloc+0x49>
    13bf:	90                   	nop
  for(p = prevp->s.ptr; ; prevp = p, p = p->s.ptr){
    13c0:	8b 02                	mov    (%edx),%eax
    if(p->s.size >= nunits){
    13c2:	8b 48 04             	mov    0x4(%eax),%ecx
    13c5:	39 f9                	cmp    %edi,%ecx
    13c7:	73 47                	jae    1410 <malloc+0x90>
        p->s.size = nunits;
      }
      freep = prevp;
      return (void*)(p + 1);
    }
    if(p == freep)
    13c9:	89 c2                	mov    %eax,%edx
    13cb:	39 05 24 20 00 00    	cmp    %eax,0x2024
    13d1:	75 ed                	jne    13c0 <malloc+0x40>
  p = sbrk(nu * sizeof(Header));
    13d3:	83 ec 0c             	sub    $0xc,%esp
    13d6:	56                   	push   %esi
    13d7:	e8 8f fc ff ff       	call   106b <sbrk>
  if(p == (char*)-1)
    13dc:	83 c4 10             	add    $0x10,%esp
    13df:	83 f8 ff             	cmp    $0xffffffff,%eax
    13e2:	74 1c                	je     1400 <malloc+0x80>
  hp->s.size = nu;
    13e4:	89 58 04             	mov    %ebx,0x4(%eax)
  free((void*)(hp + 1));
    13e7:	83 ec 0c             	sub    $0xc,%esp
    13ea:	83 c0 08             	add    $0x8,%eax
    13ed:	50                   	push   %eax
    13ee:	e8 fd fe ff ff       	call   12f0 <free>
  return freep;
    13f3:	8b 15 24 20 00 00    	mov    0x2024,%edx
      if((p = morecore(nunits)) == 0)
    13f9:	83 c4 10             	add    $0x10,%esp
    13fc:	85 d2                	test   %edx,%edx
    13fe:	75 c0                	jne    13c0 <malloc+0x40>
        return 0;
  }
}
    1400:	8d 65 f4             	lea    -0xc(%ebp),%esp
        return 0;
    1403:	31 c0                	xor    %eax,%eax
}
    1405:	5b                   	pop    %ebx
    1406:	5e                   	pop    %esi
    1407:	5f                   	pop    %edi
    1408:	5d                   	pop    %ebp
    1409:	c3                   	ret
    140a:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
      if(p->s.size == nunits)
    1410:	39 cf                	cmp    %ecx,%edi
    1412:	74 4c                	je     1460 <malloc+0xe0>
        p->s.size -= nunits;
    1414:	29 f9                	sub    %edi,%ecx
    1416:	89 48 04             	mov    %ecx,0x4(%eax)
        p += p->s.size;
    1419:	8d 04 c8             	lea    (%eax,%ecx,8),%eax
        p->s.size = nunits;
    141c:	89 78 04             	mov    %edi,0x4(%eax)
      freep = prevp;
    141f:	89 15 24 20 00 00    	mov    %edx,0x2024
}
    1425:	8d 65 f4             	lea    -0xc(%ebp),%esp
      return (void*)(p + 1);
    1428:	83 c0 08             	add    $0x8,%eax
}
    142b:	5b                   	pop    %ebx
    142c:	5e                   	pop    %esi
    142d:	5f                   	pop    %edi
    142e:	5d                   	pop    %ebp
    142f:	c3                   	ret
    base.s.ptr = freep = prevp = &base;
    1430:	c7 05 24 20 00 00 28 	movl   $0x2028,0x2024
    1437:	20 00 00 
    base.s.size = 0;
    143a:	b8 28 20 00 00       	mov    $0x2028,%eax
    base.s.ptr = freep = prevp = &base;
    143f:	c7 05 28 20 00 00 28 	movl   $0x2028,0x2028
    1446:	20 00 00 
    base.s.size = 0;
    1449:	c7 05 2c 20 00 00 00 	movl   $0x0,0x202c
    1450:	00 00 00 
    if(p->s.size >= nunits){
    1453:	e9 54 ff ff ff       	jmp    13ac <malloc+0x2c>
    1458:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
    145f:	90                   	nop
        prevp->s.ptr = p->s.ptr;
    1460:	8b 08                	mov    (%eax),%ecx
    1462:	89 0a                	mov    %ecx,(%edx)
    1464:	eb b9                	jmp    141f <malloc+0x9f>
