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
 * To check for memleaks
 * valgrind --leak-check=full ./proc_manager < cmds.txt
 *
 * To execute
 * ./proc_manager < cmds.txt
 */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>

/**
 * Define structure for hashtable node
 *
 * Size: 32 bytes
 */
struct nlist
{
    struct nlist *nextProc;
    double startTime;
    double endTime;
    int lineIndex;
    pid_t procPID;
    char *command;
};

#define HASHSIZE 101
static struct nlist *hashtab[HASHSIZE]; /* pointer table */

// Reference hashing function
unsigned hash(int pid)
{
    return pid % HASHSIZE;
}

/**
 * Looks for a node in the hash table that matches the provided pid
 */
struct nlist *lookup(int pid)
{
    struct nlist *np;
    for (np = hashtab[hash(pid)]; np != NULL; np = np->nextProc)
        if (np->procPID == pid) // Predicate to verify if
        {
            return np;
        }
        else
            return NULL;
}

char *strdup(char *); // Diego Note: What is this line meant to accomplish?

/**
 * Inserts a new node into the hashtable
 *
 * @param   command Pointer to a string which will be copied into the node
 * @param   pid     The pid which will be assigned to this node, used for lookup
 * @param   index   The index number of the command, used for formatted output
 */
struct nlist *insert(char *command, int pid, int index)
{
    struct nlist *np;
    unsigned hashval;
    // TODO change to lookup by pid. There are 2 cases:
    if ((np = lookup(pid)) == NULL)
    { /* case 1: the pid is not found, so you have to create it with malloc. Then you want to set the pid, command and index */
        np = (struct nlist *)malloc(sizeof(*np));
        if (np == NULL || (np->command = strdup(command)) == NULL)
            return NULL;
        hashval = hash(pid);
        if ((np->lineIndex = index) == NULL)
            return NULL;
        np->command = strdup(command);
        np->procPID = pid;
        np->lineIndex = index;
        np->nextProc = hashtab[hashval];
        hashtab[hashval] = np;
    }
    else
    {
        /**
         * case 2: the pid is already there in the hashslot, i.e. lookup found the pid.
         * In this case you can either do nothing, or you may want to set again the command  and index (depends on your implementation).
         */
    }
    // free((void *) np->defn); /*free previous defn */
    // Diego Note: This warrants further investigation, if the output isn't as expected
    return np;
}

/**
 * You might need to duplicate the command string to ensure you don't overwrite
 * the previous command each time a new line is read from the input file.
 * Or you might not need to duplicate it. It depends on your implementation.
 */
char *strdup(char *str2cpy)
{
    char *p;
    p = (char *)malloc(strlen(str2cpy) + 1); /* +1 for ’\0’ */
    if (p != NULL)
        strcpy(p, str2cpy);
    return p;
}