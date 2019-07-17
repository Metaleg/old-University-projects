#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>


struct task {
    int id;
    int period;
    int lead_time;
    int deadline;
};

struct task_status {
    int job;
    int relative_deadline;
    int relative_lead_time;
    bool skip_deadline;
};

struct processor {
    int num_tasks;
    int simulation_time;
    struct task *tasks;
    struct task_status *status;
};

int gcd(int a, int b);
int lcm(int a, int b);
int lcm_arr(struct task *tasks, int size);
struct task *tasks_init(int tasks_num);
struct processor processor_init(struct task *tsks, int tasks_num);
void show(struct processor *proc);
void simulate(struct processor *proc);



int main() {
    srand((unsigned int)time(NULL));

//    printf("Enter number of tasks (3 <= N <= 10): ");
    int N;
    N = 2;
//    scanf("%d", &N);
   /* if (N < 3 || N > 10){
        perror("invalid number of tasks\n");
        return EXIT_FAILURE;
    }*/

    struct task *tasks = tasks_init(N);
    struct processor proc = processor_init(tasks, N);

    simulate(&proc);

    return 0;
}



int gcd(int a, int b) {
    return abs(b ? gcd(b, a % b) : a);
}

int lcm(int a, int b) {
    return a / gcd(a, b) * b;
}

int lcm_arr(struct task *tasks, int size) {
    int last_lcm = lcm(tasks[0].period, tasks[1].period);
    for (size_t i = 2; i < size; ++i)
        last_lcm = lcm(last_lcm, tasks[i].period);
    return last_lcm;
}

struct task *tasks_init(int tasks_num){
    struct task *tasks = malloc(sizeof(struct task) * tasks_num);
    for (size_t i = 0; i < tasks_num; ++i){
        tasks[i].id = (int) i;
       /* tasks[i].period = 3 + rand() % 10;
        tasks[i].deadline = tasks[i].period;
        tasks[i].lead_time = 1 + rand() % 5;*/
    }
    tasks[0].period = 5;
    tasks[0].deadline = tasks[0].period;
    tasks[0].lead_time = 2;

    tasks[1].period = 7;
    tasks[1].deadline = tasks[1].period;
    tasks[1].lead_time = 4;

    return tasks;
}

struct processor processor_init(struct task *tsks, int tasks_num){
    struct processor proc;
    proc.num_tasks = tasks_num;
    proc.simulation_time = lcm_arr(tsks, tasks_num);
    proc.tasks = tsks;
    proc.status = malloc(sizeof(struct task_status) * tasks_num);
    for (size_t i = 0; i < tasks_num; ++i){
        proc.status[i].job = 0;
        proc.status[i].relative_deadline = proc.tasks[i].deadline;
        proc.status[i].relative_lead_time = 0;
        proc.status[i].skip_deadline = false;
    }
    return proc;
}


void show(struct processor *proc){
    for (size_t i = 0; i < proc->num_tasks; ++i) {
        printf(" ID = %d, JOB = %2d, T = D = %2d, C = %2d, RD = %2d ||", proc->tasks[i].id, proc->status[i].job,
                proc->tasks[i].deadline, proc->tasks[i].lead_time, proc->status[i].relative_deadline);
    }
    printf("\n");
}

void simulate(struct processor *proc){
    printf("           ");
    show(proc);
    printf("\n");
    for (size_t i = 0; i < proc->simulation_time; ++i) {
        int temp_index = 0;
        int releative_deadline = 100;   //TODO: magic number
        for (size_t j = 0; j < proc->num_tasks; ++j) {
            if (proc->status[j].relative_deadline == 0 &&
            proc->status[j].relative_lead_time < proc->tasks[j].lead_time) {
                proc->status[j].skip_deadline = true;
                printf("ID %d skipped deadline!\n", proc->tasks[j].id);
                return;
            }
            if (i != 0 && proc->status[j].relative_deadline == 0){
                proc->status[j].job++;
                proc->status[j].relative_lead_time = 0;
                proc->status[j].relative_deadline = proc->tasks[j].deadline;
            }

            if (proc->status[j].relative_lead_time < proc->tasks[j].lead_time &&
                    proc->status[j].relative_deadline < releative_deadline) {
                    releative_deadline = proc->status[j].relative_deadline;
                    temp_index = (int) j;
            }
        }
        proc->status[temp_index].relative_lead_time++;

        for (size_t k = 0; k < proc->num_tasks; ++k)
            proc->status[k].relative_deadline--;

        printf("%3d tact | ", (int) i + 1);
        show(proc);
    }
    free(proc->status);
    free(proc->tasks);
}