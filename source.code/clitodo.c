#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<time.h>
//lwk learned this from an indian 1000 questions in C website pretty neat to be able to use it
#ifdef _WIN32
    #include <direct.h>
    #include <windows.h>
    #define mkdir(path, mode) _mkdir(path)
#else
    #include <sys/stat.h>
    #include <sys/types.h>
    #include <unistd.h>
#endif
//ill add ANSI color system learned this in 30min found a list in github
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define PURPLE "\033[1;35m"
#define CYAN "\033[1;36m"
#define WHITE "\033[1;37m"
#define DIM "\033[2;90m"
#define BOLD "\033[1m"
#define RESET "\033[0m"

//this is the struct that im gonna use for tasks
typedef struct {
    int ID;
    bool completion;
    bool quick;
    char description[500];
} Task;

int main(int argc, char *argv[]){
    srand(time(NULL));
    char *home;
#ifdef _WIN32
    home = getenv("USERPROFILE");
#else
    home = getenv("HOME");
#endif
     if (home == NULL) {
        fprintf(stderr, "Error: Could not find Home directory.\n");
        return 1;
    }
    char folder_path[512];
    snprintf(folder_path, sizeof(folder_path), "%s/.clitodo", home);
    mkdir(folder_path, 0700); 
    char todo_file[1024];
    char temp_file[1024];
    char streak_file[1024];
    char pick_file[1024];
    char dump_file[1024];
    snprintf(todo_file, sizeof(todo_file), "%s/todo.txt", folder_path);
    snprintf(temp_file, sizeof(temp_file), "%s/temp.txt", folder_path);
    snprintf(streak_file, sizeof(streak_file), "%s/streak.txt", folder_path);
    snprintf(pick_file, sizeof(pick_file), "%s/lastpick.txt", folder_path);
    snprintf(dump_file, sizeof(dump_file), "%s/dump.txt", folder_path);
    //here ill give a help menu
  if (argc == 2 && (strcmp(argv[1],"--help") == 0 || strcmp(argv[1],"help") == 0)){
    printf("CLITODO\n\n");
    printf("Usage:\n");
    printf("  clitodo add <description>[--quick] - Add a new task(use the flag for fast wins\n");
    printf("  clitodo list                      - View all tasks\n"); 
    printf("  clitodo done <id>                 - Mark task as complete (increases streak!!)\n");
    printf("  clitodo pick                      - Let the app choose your focus\n");
    printf("  clitodo delete <id>               - Remove a task\n");
    printf("  clitodo dump <text>               - Quickly record a thought/memory\n");
    printf("  clitodo dump list                 - review your thoughts history\n\n");

 return 0;
  }
//this condition is for adding tasks
    else if (argc >= 3 && strcmp(argv[1],"add") == 0){
    Task task;//instance name is task
   int quick = 0; 
    FILE *f = fopen(todo_file,"r");
   int lastid = 0;
   if (f != NULL){
      char line[600];
    while (fgets(line, sizeof(line), f) != NULL) {
            int id, done,&tempquick;
            char desc[500];

          sscanf(line, "%d|%d|%d|%[^\n]", &id, &done,&tempquick, desc);
          if (id>lastid) lastid = id;} //this so it can automatically update the id for each new task 
        fclose(f); }
  task.ID = lastid + 1;  
   task.completion = false;
   task.description[0] = '\0';
   for (int i = 2; i < argc; i++) {
    if (strcmp(argv[i], "--quick") == 0) {
        quick = 1;
        continue;
    }
    size_t remaining = sizeof(task.description) - strlen(task.description) - 1;
    strncat(task.description, argv[i],remaining);
    if (i < argc - 1) strcat(task.description, " ");
}
FILE *ext = fopen(todo_file,"a");
if (ext ==NULL){
    perror("error opening file.\n");
    return 1;}
        fprintf(ext,"%d|%d|%d|%s\n", task.ID, task.completion,quick, task.description);
   fclose(ext);
   printf("Task %d added: %s\n",task.ID,task.description);} 
else if (argc == 2 && strcmp(argv[1],"list") == 0){ //this so it can list the tasks by reading from the txt file 
   char line[600];
       FILE *f =fopen(todo_file,"r");
  if (f == NULL){
      printf ("No tasks yet.\n");
      return 0;}
  while(fgets(line,sizeof(line),f) != NULL){
      int id , done,quick;
      char desc[500];
      if (sscanf(line, "%d|%d|%d|%[^\n]", &id, &done,&quick, desc) == 4) {
    if (done) {
    printf(DIM "[✓] %d  %s\n" RESET, id, desc);
}
else if (quick) {
    printf(PURPLE "[Q] %d  %s\n" RESET, id, desc);
}
else {
    printf("[•] %d  %s\n", id, desc);
}
         printf(RESET); }
  }
 fclose(f);
 }
else if (argc == 3 && strcmp(argv[1],"done") == 0){//this for marking tasks done 
    int targetid = atoi(argv[2]);
    FILE *d = fopen(todo_file,"r");
    if (d == NULL){
        printf("No tasks found.\n");
        return 0;}
    FILE *temp = fopen(temp_file,"w");
    if (temp == NULL){
        perror("Errpr creating temporarry file");
        fclose(d);
    return 1;
    }
    char line[600];
    int found = 0;
    while(fgets(line,sizeof(line),d) != NULL){
        int id , done,quick ;
        char desc[500];
        if (sscanf(line,"%d|%d|%d|%[^\n]",&id,&done,&quick,desc) == 4){
            if( id ==targetid){
                done = 1;
                found = 1;}
            fprintf(temp, "%d|%d|%d|%s\n",id ,done,quick,desc);
        }
    }
    fclose(d);
    fclose(temp);
    remove(todo_file);
    rename(temp_file,todo_file);
    if (found){
        printf(GREEN"Task %d marked as done.\n"RESET,targetid);
    //streak thingie here
       FILE *streak = fopen(streak_file, "r");

    char stored_date[64] = "";
    int count = 0;
    char today[64];

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    snprintf(today,sizeof(today), "%04d-%02d-%02d",
            tm.tm_year + 1900,
            tm.tm_mon + 1,
            tm.tm_mday);

    if (streak != NULL) {
        fscanf(streak, "%63[^|]|%d", stored_date, &count);
        fclose(streak);
    }

    if (strcmp(stored_date, today) != 0) {
        count = 0;
    }

    count++;

    streak = fopen(streak_file, "w");
    if (streak != NULL) {
        fprintf(streak, "%s|%d", today, count);
        fclose(streak);
    }

    printf(CYAN "[STREAK] %d\n" RESET, count);
}
    else
        printf("Task not found.\n");
}
else if (argc == 3 && strcmp(argv[1],"delete") == 0){
   // will use this for delete feature so it'll be similar to done
int targetid = atoi(argv[2]);
FILE *rm = fopen(todo_file,"r");
if (rm == NULL){
    printf("no tasks found.\n");
    return 0;}
FILE *temp = fopen(temp_file,"w");
if (temp == NULL){
    perror("cant create a temporarry file");
fclose(rm);
return 1;
}
char line[600];
int found = 0;
while(fgets(line,sizeof(line),rm) != NULL){
    int id,done,quick;
    char desc[500];
    if (sscanf(line,"%d|%d|%d|%[^\n]",&id,&done,&quick,desc) == 4){
        if (id == targetid){
            found = 1;
            continue;}
        fprintf(temp,"%d|%d|%d|%s\n",id,done,quick,desc);
    }
}
fclose(rm);
fclose(temp);
remove(todo_file);
rename(temp_file,todo_file);
if (found)
    printf("Task %d deleted.\n",targetid);
else
    printf("Task not found.\n");
    }    
else if(argc==2 && strcmp(argv[1],"pick") == 0){
    FILE *p = fopen(todo_file,"r");
    if (p == NULL){
        printf("No tasks found.\n");
        return 0;}
    int lastid=-1;
    FILE *s = fopen(pick_file,"r");
    if (s != NULL){
        fscanf(s,"%d",&lastid);
        fclose(s);}
    Task *pool = NULL;
    int poolcount = 0;
    int poolcap = 0;
    char line[600];
   while (fgets(line, sizeof(line), p)) {

    int id, done, quick;
    char desc[500];

    if (sscanf(line, "%d|%d|%d|%[^\n]", &id, &done, &quick, desc) == 4) {

        if (!done && id != lastid) {

            int weight = quick ? 3 : 1;

            for (int i = 0; i < weight; i++) {

                if (poolcount == poolcap) {
                    poolcap = poolcap ? poolcap * 2 : 20;

                    Task *tmp = realloc(pool, poolcap * sizeof(Task));
                    if (tmp == NULL) {
                        printf("memory problem\n");
                        free(pool);
                        fclose(p);
                        return 1;
                    }

                    pool = tmp;
                }

                pool[poolcount].ID = id;
                pool[poolcount].completion = done;
                pool[poolcount].quick = quick;
                strcpy(pool[poolcount].description, desc);

                poolcount++;
            }
        }
    }
}
    if (poolcount == 0){
    printf("No available tasks.\n");
    free(pool);
    fclose(p);
    return 0;
    }
    int r = rand()%poolcount;
    FILE *h = fopen(pick_file,"w");
    if (h != NULL){
        fprintf(h,"%d",pool[r].ID);
        fclose(h);
    }
        printf(BOLD PURPLE "\n>>> FOCUS TASK <<<\n" RESET);
        printf(BOLD "%s\n" RESET, pool[r].description);
        printf(BOLD PURPLE " >>>>>>>>><<<<<<<<<< \n\n" RESET);
free(pool);
}else if (argc == 3 && strcmp(argv[1], "dump") == 0 && strcmp(argv[2], "list") == 0) {FILE *read = fopen(dump_file, "r");

if (read == NULL) {
    printf("No dumps yet.\n");
    return 0;
}

char line[600];

while (fgets(line, sizeof(line), read) != NULL) {

    char date[20];
    char text[500];

    if (sscanf(line, "%19[^|]|%[^\n]", date, text) == 2) {
        printf(DIM "> %s  " RESET "%s\n", date, text);
    }

}fclose(read);}
else if(argc >= 3 && strcmp(argv[1],"dump") == 0){
    FILE *dmp = fopen(dump_file,"a");
    if (dmp == NULL){
        perror("dump error.");
        return 1;}
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    fprintf(dmp,"%04d-%02d-%02d|",tm.tm_year + 1900,tm.tm_mon + 1, tm.tm_mday);
    for (int i = 2; i < argc; i++){
        fprintf(dmp,"%s%s",argv[i],(i<argc-1)?" ": ""); }
    fprintf(dmp, "\n");
    fclose(dmp);
    printf(DIM"thoughts dumped successfully:>\n"RESET);
}else if(argc == 2 && strcmp(argv[1],"update") == 0){
printf(CYAN"Checking for updates...\n"RESET);
#ifdef _WIN32
char cmd[1024];
snprintf(cmd,sizeof(cmd),"powershell -ExecutionPolicy Bypass -File %s/update.ps1", folder_path);
system(cmd);
#else
char cmd[1024];
snprintf(cmd, sizeof(cmd), "sh %s/update.sh",folder_path);
system(cmd);
#endif 
return 0;
}
else {
    printf("unknown command\n");
    printf("Run 'clitodo --help' for usage manual.\n");}
return 0;
}
