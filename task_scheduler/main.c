#include "header.h"
volatile sig_atomic_t flag=0;
volatile sig_atomic_t keep_running = 1; 
void my_isr(int n) {
flag=TRUE;
}
void sigint_handler(int sig) {
    keep_running = 0;
    flag = TRUE; 
}
int tick=0;
void TaskA() {
    printf(COLOR_RED "This is Task A for tick=%d" COLOR_RESET "\n", tick);
}
void TaskB() {
    printf(COLOR_GREEN "This is Task B for tick=%d" COLOR_RESET "\n", tick);
}
void TaskC() {
    printf(COLOR_YELLOW "This is Task C for tick=%d" COLOR_RESET "\n", tick);
}
TskSchedulerStruct arr[3]={
        {TaskA,1,0},// for 1 seconds
        {TaskB,2,1},//for every 2 seconds
        {TaskC,4,0},// for every 4 seconds
};

void scheduler(void)
{
        tick++;
        for(int i=0;i<TotalSize;i++){
                if(arr[i].timerCounter%arr[i].interval==0){
                        if(arr[i].functionAddr){
                                arr[i].functionAddr();
                        }
                        arr[i].timerCounter=0;
                }
                arr[i].timerCounter++;
        } 
}
int main(){

        struct itimerval timer;
        signal(SIGALRM, my_isr);
        signal(SIGINT, sigint_handler); 
        timer.it_value.tv_sec = 1;       
        timer.it_value.tv_usec = 0;  
        timer.it_interval.tv_sec = 1;    
        timer.it_interval.tv_usec = 0;   
        if (setitimer(ITIMER_REAL, &timer, NULL) == -1) {
                perror("setitimer failed");
                return 1;
        }
        printf("\n=================================================\n");
        printf("Task scheduler started. Press [Ctrl+C] to exit.\n");
        printf("=================================================\n\n");
        while(keep_running) {
                if(flag && keep_running) {                        
                        flag = FALSE;
                        scheduler();
                }
                if(keep_running) pause(); 
        }
        
        // 5. Final output before exit
        printf("\nScheduler shutting down gracefully. Final tick: %d\n", tick);
        return 0;
        return 0;
}