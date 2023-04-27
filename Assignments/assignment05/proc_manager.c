/**
 * Description:
 * Build upon AS3 and AS4 code to develop a program that resembles
 * a system daemon that restarts processes that got killed
 *
 * Author Names:
 * Diego Cruz
 * Saim Sheikh
 *
 * Author emails:
 * diego.cruz@sjsu.edu
 * saim.sheikh@sjsu.edu
 *
 * Last Modified: 04/24/2023
 * Creation Date: 04/22/2023
 *
 * To compile with warnings and errors
 * gcc -o proc_manager proc_manager.c -Wall -W
 *
 * To execute
 * ./proc_manager < cmds.txt
 *
 * To check for memleaks
 * valgrind --leak-check=full ./proc_manager < cmds.txt
 */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <time.h>
#define UTIL_MAX_LENGTH 100

typedef struct Node
{
    int i;
    int pid;
    struct timespec time;
    char *comm;

    struct Node *next;
} Node;

void InitializeNode(
    Node *node,
    struct timespec time,
    int pid, int i,
    char *comm,
    Node *next);

Node *find(
    Node *head,
    int pid);

// Find the node in the linkedlist by its pid
Node *find(Node *head, int pid)
{
    Node *temp = head;
    // Traverse Through List and Compare Each Node With PID
    while (temp != NULL)
    {
        if (temp->pid == pid)
        {
            return temp;
        }

        temp = temp->next;
    }
    return NULL;
}

void InitializeNode(Node *node, struct timespec time, int pid, int i, char *comm, Node *next)
{
    // Assign Values Passed To The Function - New Created Node
    node->comm = malloc(UTIL_MAX_LENGTH * sizeof(char));
    node->time = time;
    node->pid = pid;
    node->i = i;
    strcpy(node->comm, comm);
    node->next = next;
}

void FreeNodes(Node *refNode)
{
    if (refNode != NULL) // Quick check to see if not nullpointer
    {
        // Push Function To Stack
        FreeNodes(refNode->next); // Recursive call to each node until the last one is called
        free(refNode->comm);      // frees memory allotted to the string inside the struct
        free(refNode);            // frees mem occupied by rest of node
    }
}

int main(int argc, char *argv[])
{

    int proc_num = 0;
    char cmds[UTIL_MAX_LENGTH][UTIL_MAX_LENGTH];
    char currentLine[UTIL_MAX_LENGTH];
    // read input and put in each command as seperate string in array until eof
    while (fgets(currentLine, UTIL_MAX_LENGTH, stdin) != NULL)
    {
        currentLine[strcspn(currentLine, "\r\n")] = 0;
        strcpy(cmds[proc_num], currentLine);
        proc_num++;
    };

    // create linked list to store info about child proc.
    Node *head = (Node *)malloc(sizeof(Node));

    struct timespec dummy;
    clock_gettime(CLOCK_MONOTONIC, &dummy);
    InitializeNode(head, dummy, -1, -1, "dummy", NULL);

    Node *temp = head;

    int pids[proc_num];
    // create chiuld proc for each command in cmd array using fork.
    for (int i = 0; i < proc_num; i++)
    {
        pids[i] = fork();

        // if fork call return 0, child proc is successfully made and execute command with execvp
        if (pids[i] == 0)
        {

            char *array[50];

            int j = 0;
            array[j] = strtok(cmds[i], " ");
            while (array[j] != NULL)
                array[++j] = strtok(NULL, " ");
            array[j] = NULL;

            char out[25];
            char err[25];

            sprintf(out, "%d", getpid());
            sprintf(err, "%d", getpid());
            strcat(out, ".out");
            strcat(err, ".err");

            int fdout = open(out, O_RDWR | O_CREAT | O_APPEND, 0777);
            int fderr = open(err, O_RDWR | O_CREAT | O_APPEND, 0777);

            dup2(fdout, 1);
            dup2(fderr, 2);

            dprintf(1, "Starting command %d: child %d pid of parent %d\n", i + 1, getpid(), getppid());

            execvp(array[0], array);

            fprintf(stderr, "Unable to execute a command!\n");
            return 2;
        }
        // PARENT PROCESS IF greater than 0, create new node in linked list
        else if (pids[i] > 0)
        {
            // Create New Node - LinkedList
            Node *nextNode = malloc(sizeof(Node));

            struct timespec start;
            clock_gettime(CLOCK_MONOTONIC, &start);

            // set val of Node struct
            InitializeNode(nextNode, start, pids[i], i, cmds[i], NULL);
            temp->next = nextNode;
            temp = nextNode;
        }
    }

    int pid;
    int status;

    while ((pid = wait(&status)) >= 0)
    {
        if (pid > 0)
        {
            char out[25];
            char err[25];
            // Set File Descriptors
            sprintf(out, "%d", pid);
            strcat(out, ".out");

            int fdout = open(out, O_RDWR | O_CREAT | O_APPEND, 0777);
            dup2(fdout, 1);

            sprintf(err, "%d", pid);
            strcat(err, ".err");

            int fderr = open(err, O_RDWR | O_CREAT | O_APPEND, 0777);
            dup2(fderr, 2);

            dprintf(1, "Finished child %d pid of parent %d\n", pid, getpid());

            // Specify Exit Code In .ERR File - If Success
            if (WIFEXITED(status))
            {
                dprintf(2, "Exited with exitcode = %d\n", status);
            }

            // Specify Signal Code In .ERR File - If Killed
            else if (WIFSIGNALED(status))
            {
                dprintf(2, "spawning too fast\n");
                dprintf(2, "Killed with signal %d\n", status);
            }
            // Find Node By PID
            Node *node = find(head->next, pid);

            if (node != NULL)
            {
                // Create Finish Timetamp
                struct timespec finish;
                clock_gettime(CLOCK_MONOTONIC, &finish);
                // Elapsed Time Of command - Calculate
                double elapsed = finish.tv_sec - node->time.tv_sec;
                elapsed += (finish.tv_nsec - node->time.tv_sec) / 1000000000.0;
                dprintf(1, "Finished at %ld, runtime duration %f\n", finish.tv_sec, elapsed);
                if (elapsed <= 2)
                {
                    dprintf(2, "spawning too fast\n");
                }
                // Restart Process if Time > 2s
                else
                {
                    int id = fork();
                    // Child Process
                    if (id == 0)
                    {
                        // [] command Splitted By Space
                        char *array[UTIL_MAX_LENGTH];
                        // Split command To Get List Of Arguments
                        int j = 0;
                        array[j] = strtok(node->comm, " ");
                        while (array[j] != NULL)
                            array[++j] = strtok(NULL, " ");
                        array[j] = NULL;
                        char out[25];
                        char err[25];
                        // Concatenate Process IDs With Extension
                        sprintf(out, "%d", getpid());
                        sprintf(err, "%d", getpid());
                        strcat(out, ".out");
                        strcat(err, ".err");
                        // Create Both Out and Err Files
                        int fdout = open(out, O_RDWR | O_CREAT | O_APPEND, 0777);
                        int fderr = open(err, O_RDWR | O_CREAT | O_APPEND, 0777);
                        // Specify File Handler
                        dup2(fdout, 1);
                        dup2(fderr, 2);
                        // Print Message To .OUT File
                        dprintf(1, "RESTARTING\n");
                        dprintf(2, "RESTARTING\n");
                        dprintf(1, "Starting command %d: child %d pid of parent %d\n", node->i, getpid(), getppid());
                        // Execute command
                        execvp(array[0], array);

                        fprintf(stderr, "Unable to execute a command!\n");
                        return 2;
                    }
                    else if (id > 0)
                    {
                        // Create a new node
                        Node *nextNode = malloc(sizeof(Node));
                        // Create Start Timestamp
                        struct timespec start;
                        clock_gettime(CLOCK_MONOTONIC, &start);
                        // Assign Values To New Created Node
                        InitializeNode(nextNode, start, id, node->i, node->comm, NULL);
                        temp->next = nextNode;
                        temp = nextNode;
                    }
                }
            }
        }
    }

    FreeNodes(head);

    return 0;
}