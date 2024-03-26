7900 // Shell.
7901 
7902 #include "types.h"
7903 #include "user.h"
7904 #include "fcntl.h"
7905 
7906 // Parsed command representation
7907 #define EXEC  1
7908 #define REDIR 2
7909 #define PIPE  3
7910 #define LIST  4
7911 #define BACK  5
7912 
7913 #define MAXARGS 10
7914 
7915 struct cmd {
7916   int type;
7917 };
7918 
7919 struct execcmd {
7920   int type;
7921   char *argv[MAXARGS];
7922   char *eargv[MAXARGS];
7923 };
7924 
7925 struct redircmd {
7926   int type;
7927   struct cmd *cmd;
7928   char *file;
7929   char *efile;
7930   int mode;
7931   int fd;
7932 };
7933 
7934 struct pipecmd {
7935   int type;
7936   struct cmd *left;
7937   struct cmd *right;
7938 };
7939 
7940 struct listcmd {
7941   int type;
7942   struct cmd *left;
7943   struct cmd *right;
7944 };
7945 
7946 struct backcmd {
7947   int type;
7948   struct cmd *cmd;
7949 };
7950 int fork1(void);  // Fork but panics on failure.
7951 void panic(char*);
7952 struct cmd *parsecmd(char*);
7953 
7954 // Execute cmd.  Never returns.
7955 void
7956 runcmd(struct cmd *cmd)
7957 {
7958   int p[2];
7959   struct backcmd *bcmd;
7960   struct execcmd *ecmd;
7961   struct listcmd *lcmd;
7962   struct pipecmd *pcmd;
7963   struct redircmd *rcmd;
7964 
7965   if(cmd == 0)
7966     exit();
7967 
7968   switch(cmd->type){
7969   default:
7970     panic("runcmd");
7971 
7972   case EXEC:
7973     ecmd = (struct execcmd*)cmd;
7974     if(ecmd->argv[0] == 0)
7975       exit();
7976     exec(ecmd->argv[0], ecmd->argv);
7977     printf(2, "exec %s failed\n", ecmd->argv[0]);
7978     break;
7979 
7980   case REDIR:
7981     rcmd = (struct redircmd*)cmd;
7982     close(rcmd->fd);
7983     if(open(rcmd->file, rcmd->mode) < 0){
7984       printf(2, "open %s failed\n", rcmd->file);
7985       exit();
7986     }
7987     runcmd(rcmd->cmd);
7988     break;
7989 
7990   case LIST:
7991     lcmd = (struct listcmd*)cmd;
7992     if(fork1() == 0)
7993       runcmd(lcmd->left);
7994     wait();
7995     runcmd(lcmd->right);
7996     break;
7997 
7998 
7999 
8000   case PIPE:
8001     pcmd = (struct pipecmd*)cmd;
8002     if(pipe(p) < 0)
8003       panic("pipe");
8004     if(fork1() == 0){
8005       close(1);
8006       dup(p[1]);
8007       close(p[0]);
8008       close(p[1]);
8009       runcmd(pcmd->left);
8010     }
8011     if(fork1() == 0){
8012       close(0);
8013       dup(p[0]);
8014       close(p[0]);
8015       close(p[1]);
8016       runcmd(pcmd->right);
8017     }
8018     close(p[0]);
8019     close(p[1]);
8020     wait();
8021     wait();
8022     break;
8023 
8024   case BACK:
8025     bcmd = (struct backcmd*)cmd;
8026     if(fork1() == 0)
8027       runcmd(bcmd->cmd);
8028     break;
8029   }
8030   exit();
8031 }
8032 
8033 int
8034 getcmd(char *buf, int nbuf)
8035 {
8036   printf(2, "$ ");
8037   memset(buf, 0, nbuf);
8038   gets(buf, nbuf);
8039   if(buf[0] == 0) // EOF
8040     return -1;
8041   return 0;
8042 }
8043 
8044 
8045 
8046 
8047 
8048 
8049 
8050 int
8051 main(void)
8052 {
8053   static char buf[100];
8054   int fd;
8055 
8056   // Ensure that three file descriptors are open.
8057   while((fd = open("console", O_RDWR)) >= 0){
8058     if(fd >= 3){
8059       close(fd);
8060       break;
8061     }
8062   }
8063 
8064   // Read and run input commands.
8065   while(getcmd(buf, sizeof(buf)) >= 0){
8066     if(buf[0] == 'c' && buf[1] == 'd' && buf[2] == ' '){
8067       // Chdir must be called by the parent, not the child.
8068       buf[strlen(buf)-1] = 0;  // chop \n
8069       if(chdir(buf+3) < 0)
8070         printf(2, "cannot cd %s\n", buf+3);
8071       continue;
8072     }
8073     if(fork1() == 0)
8074       runcmd(parsecmd(buf));
8075     wait();
8076   }
8077   exit();
8078 }
8079 
8080 void
8081 panic(char *s)
8082 {
8083   printf(2, "%s\n", s);
8084   exit();
8085 }
8086 
8087 int
8088 fork1(void)
8089 {
8090   int pid;
8091 
8092   pid = fork();
8093   if(pid == -1)
8094     panic("fork");
8095   return pid;
8096 }
8097 
8098 
8099 
8100 // Constructors
8101 
8102 struct cmd*
8103 execcmd(void)
8104 {
8105   struct execcmd *cmd;
8106 
8107   cmd = malloc(sizeof(*cmd));
8108   memset(cmd, 0, sizeof(*cmd));
8109   cmd->type = EXEC;
8110   return (struct cmd*)cmd;
8111 }
8112 
8113 struct cmd*
8114 redircmd(struct cmd *subcmd, char *file, char *efile, int mode, int fd)
8115 {
8116   struct redircmd *cmd;
8117 
8118   cmd = malloc(sizeof(*cmd));
8119   memset(cmd, 0, sizeof(*cmd));
8120   cmd->type = REDIR;
8121   cmd->cmd = subcmd;
8122   cmd->file = file;
8123   cmd->efile = efile;
8124   cmd->mode = mode;
8125   cmd->fd = fd;
8126   return (struct cmd*)cmd;
8127 }
8128 
8129 struct cmd*
8130 pipecmd(struct cmd *left, struct cmd *right)
8131 {
8132   struct pipecmd *cmd;
8133 
8134   cmd = malloc(sizeof(*cmd));
8135   memset(cmd, 0, sizeof(*cmd));
8136   cmd->type = PIPE;
8137   cmd->left = left;
8138   cmd->right = right;
8139   return (struct cmd*)cmd;
8140 }
8141 
8142 
8143 
8144 
8145 
8146 
8147 
8148 
8149 
8150 struct cmd*
8151 listcmd(struct cmd *left, struct cmd *right)
8152 {
8153   struct listcmd *cmd;
8154 
8155   cmd = malloc(sizeof(*cmd));
8156   memset(cmd, 0, sizeof(*cmd));
8157   cmd->type = LIST;
8158   cmd->left = left;
8159   cmd->right = right;
8160   return (struct cmd*)cmd;
8161 }
8162 
8163 struct cmd*
8164 backcmd(struct cmd *subcmd)
8165 {
8166   struct backcmd *cmd;
8167 
8168   cmd = malloc(sizeof(*cmd));
8169   memset(cmd, 0, sizeof(*cmd));
8170   cmd->type = BACK;
8171   cmd->cmd = subcmd;
8172   return (struct cmd*)cmd;
8173 }
8174 // Parsing
8175 
8176 char whitespace[] = " \t\r\n\v";
8177 char symbols[] = "<|>&;()";
8178 
8179 int
8180 gettoken(char **ps, char *es, char **q, char **eq)
8181 {
8182   char *s;
8183   int ret;
8184 
8185   s = *ps;
8186   while(s < es && strchr(whitespace, *s))
8187     s++;
8188   if(q)
8189     *q = s;
8190   ret = *s;
8191   switch(*s){
8192   case 0:
8193     break;
8194   case '|':
8195   case '(':
8196   case ')':
8197   case ';':
8198   case '&':
8199   case '<':
8200     s++;
8201     break;
8202   case '>':
8203     s++;
8204     if(*s == '>'){
8205       ret = '+';
8206       s++;
8207     }
8208     break;
8209   default:
8210     ret = 'a';
8211     while(s < es && !strchr(whitespace, *s) && !strchr(symbols, *s))
8212       s++;
8213     break;
8214   }
8215   if(eq)
8216     *eq = s;
8217 
8218   while(s < es && strchr(whitespace, *s))
8219     s++;
8220   *ps = s;
8221   return ret;
8222 }
8223 
8224 int
8225 peek(char **ps, char *es, char *toks)
8226 {
8227   char *s;
8228 
8229   s = *ps;
8230   while(s < es && strchr(whitespace, *s))
8231     s++;
8232   *ps = s;
8233   return *s && strchr(toks, *s);
8234 }
8235 
8236 
8237 
8238 
8239 
8240 
8241 
8242 
8243 
8244 
8245 
8246 
8247 
8248 
8249 
8250 struct cmd *parseline(char**, char*);
8251 struct cmd *parsepipe(char**, char*);
8252 struct cmd *parseexec(char**, char*);
8253 struct cmd *nulterminate(struct cmd*);
8254 
8255 struct cmd*
8256 parsecmd(char *s)
8257 {
8258   char *es;
8259   struct cmd *cmd;
8260 
8261   es = s + strlen(s);
8262   cmd = parseline(&s, es);
8263   peek(&s, es, "");
8264   if(s != es){
8265     printf(2, "leftovers: %s\n", s);
8266     panic("syntax");
8267   }
8268   nulterminate(cmd);
8269   return cmd;
8270 }
8271 
8272 struct cmd*
8273 parseline(char **ps, char *es)
8274 {
8275   struct cmd *cmd;
8276 
8277   cmd = parsepipe(ps, es);
8278   while(peek(ps, es, "&")){
8279     gettoken(ps, es, 0, 0);
8280     cmd = backcmd(cmd);
8281   }
8282   if(peek(ps, es, ";")){
8283     gettoken(ps, es, 0, 0);
8284     cmd = listcmd(cmd, parseline(ps, es));
8285   }
8286   return cmd;
8287 }
8288 
8289 
8290 
8291 
8292 
8293 
8294 
8295 
8296 
8297 
8298 
8299 
8300 struct cmd*
8301 parsepipe(char **ps, char *es)
8302 {
8303   struct cmd *cmd;
8304 
8305   cmd = parseexec(ps, es);
8306   if(peek(ps, es, "|")){
8307     gettoken(ps, es, 0, 0);
8308     cmd = pipecmd(cmd, parsepipe(ps, es));
8309   }
8310   return cmd;
8311 }
8312 
8313 struct cmd*
8314 parseredirs(struct cmd *cmd, char **ps, char *es)
8315 {
8316   int tok;
8317   char *q, *eq;
8318 
8319   while(peek(ps, es, "<>")){
8320     tok = gettoken(ps, es, 0, 0);
8321     if(gettoken(ps, es, &q, &eq) != 'a')
8322       panic("missing file for redirection");
8323     switch(tok){
8324     case '<':
8325       cmd = redircmd(cmd, q, eq, O_RDONLY, 0);
8326       break;
8327     case '>':
8328       cmd = redircmd(cmd, q, eq, O_WRONLY|O_CREATE, 1);
8329       break;
8330     case '+':  // >>
8331       cmd = redircmd(cmd, q, eq, O_WRONLY|O_CREATE, 1);
8332       break;
8333     }
8334   }
8335   return cmd;
8336 }
8337 
8338 
8339 
8340 
8341 
8342 
8343 
8344 
8345 
8346 
8347 
8348 
8349 
8350 struct cmd*
8351 parseblock(char **ps, char *es)
8352 {
8353   struct cmd *cmd;
8354 
8355   if(!peek(ps, es, "("))
8356     panic("parseblock");
8357   gettoken(ps, es, 0, 0);
8358   cmd = parseline(ps, es);
8359   if(!peek(ps, es, ")"))
8360     panic("syntax - missing )");
8361   gettoken(ps, es, 0, 0);
8362   cmd = parseredirs(cmd, ps, es);
8363   return cmd;
8364 }
8365 
8366 struct cmd*
8367 parseexec(char **ps, char *es)
8368 {
8369   char *q, *eq;
8370   int tok, argc;
8371   struct execcmd *cmd;
8372   struct cmd *ret;
8373 
8374   if(peek(ps, es, "("))
8375     return parseblock(ps, es);
8376 
8377   ret = execcmd();
8378   cmd = (struct execcmd*)ret;
8379 
8380   argc = 0;
8381   ret = parseredirs(ret, ps, es);
8382   while(!peek(ps, es, "|)&;")){
8383     if((tok=gettoken(ps, es, &q, &eq)) == 0)
8384       break;
8385     if(tok != 'a')
8386       panic("syntax");
8387     cmd->argv[argc] = q;
8388     cmd->eargv[argc] = eq;
8389     argc++;
8390     if(argc >= MAXARGS)
8391       panic("too many args");
8392     ret = parseredirs(ret, ps, es);
8393   }
8394   cmd->argv[argc] = 0;
8395   cmd->eargv[argc] = 0;
8396   return ret;
8397 }
8398 
8399 
8400 // NUL-terminate all the counted strings.
8401 struct cmd*
8402 nulterminate(struct cmd *cmd)
8403 {
8404   int i;
8405   struct backcmd *bcmd;
8406   struct execcmd *ecmd;
8407   struct listcmd *lcmd;
8408   struct pipecmd *pcmd;
8409   struct redircmd *rcmd;
8410 
8411   if(cmd == 0)
8412     return 0;
8413 
8414   switch(cmd->type){
8415   case EXEC:
8416     ecmd = (struct execcmd*)cmd;
8417     for(i=0; ecmd->argv[i]; i++)
8418       *ecmd->eargv[i] = 0;
8419     break;
8420 
8421   case REDIR:
8422     rcmd = (struct redircmd*)cmd;
8423     nulterminate(rcmd->cmd);
8424     *rcmd->efile = 0;
8425     break;
8426 
8427   case PIPE:
8428     pcmd = (struct pipecmd*)cmd;
8429     nulterminate(pcmd->left);
8430     nulterminate(pcmd->right);
8431     break;
8432 
8433   case LIST:
8434     lcmd = (struct listcmd*)cmd;
8435     nulterminate(lcmd->left);
8436     nulterminate(lcmd->right);
8437     break;
8438 
8439   case BACK:
8440     bcmd = (struct backcmd*)cmd;
8441     nulterminate(bcmd->cmd);
8442     break;
8443   }
8444   return cmd;
8445 }
8446 
8447 
8448 
8449 
