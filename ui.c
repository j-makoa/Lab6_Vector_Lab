/*
 * ui.c
 * CPE-2600 Lab 5 - Vector Calculator
 * Date: 9/29/2026
 * Author: Jim Luzano-Belfield
 *
 * Reads a line with fgets, splits it into tokens with strtok, then
 * decides what to do based on the number and kind of tokens.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ui.h"
#include "vectstore.h"
#include "vect.h"

#define LINE_LEN 256
#define DELIMS " ,\t\n"

/* helper methods for the loop */

// Checks if a string represents a number and stores it in *value if true. Returns 1 if true, 0 otherwise.
static int is_number(const char *str, double *value)
{
    char *endptr;
    *value = strtod(str, &endptr);
    if (*endptr != '\0' || str == endptr) {
        return 0;
    }
    return 1;
}

// Prints a vector in the format "name = x y z"
static void print_vect(vect v)
{
    printf("%s = %g %g %g\n", v.name, v.x, v.y, v.z);
}

/* helper methods for commands */

// Handles the "list" command by printing all stored vectors.
static void handle_list(void)
{
    for (int i = 0; i < MAX_VECTS-1; i++) {
        vect v = store_get(i);
        print_vect(v);
    }
}

// Handles the "display" command by printing a specific vector.
static void handle_display(const char *name)
{
    vect v = {0, 0, 0};
    if (store_find(name, v) == 1) {
        print_vect(v);
    }
    else {
        printf("Vector '%s' not found.\n", name);
    }
}

/*
* varname = x y z (n = 5)
* varname = x y   (n = 4, z = 0)
*/
static void handle_assign(const char *name, const char *xs, const char *ys, const char *zs)
{
    double x = 0, y = 0, z = 0;
    if (is_number(xs, &x)) {
        if (is_number(ys, &y)) {
            if (zs && is_number(zs, &z)) {
                vect v = {name, x, y, z};
                store_add(v);
                print
            } else {
                vect v = {name, x, y, 0};
                store_add(v);
            }
        } else {
            vect v = {name, x, 0, 0};
            store_add(v);
        }
    } else {
        printf("Invalid number: %s\n", xs);
    }
}

/*
* evalutate: lhs op rhs where op is +, -, * (dot product), x (cross product)
*/
static int do_operation(const char *lhs, const char *op, const char *rhs, vect *result)
{
    vect lhs_vect = {0, 0, 0};
    vect rhs_vect = {0, 0, 0};
    if (store_find(lhs, &lhs_vect) == 1 && store_find(rhs, &rhs_vect) == 1) {
        if (strcmp(op, "+") == 0) {
            
        }
    }
}

static int handle_line(const char *t1, const char *t2, const char *t3, const char *t4, const char *t5, int n)
{
    if (n == 0) 
    {
        return 0;
    }

    if (n == 1) {
        if(strcmp(t1, "quit") == 0)
        {
            return 1;
        }
        else if(strcmp(t1, "clear") == 0)
        {
            store_clear();
        }
        else if(strcmp(t1, "list") == 0)
        {
            handle_list();
        }
        else {
            handle_display(t1);
        }
        return 0;
    }
    if (n == 3)
    {
        vect result;
        if (do_operation(t1, t2, t3, &result) == 1) {
            
        }
        return 0;
    }

}

/* public methods */

void ui_run(void)
{
    char line[LINE_LEN];

    while (1) {
        printf("myvectorcalc> ");
        fflush(stdout);

        if (fgets(line, sizeof line, stdin) == NULL)
        {
            printf("\n"); // end of line
            break;
        }

        char *t1 = strtok(line, DELIMS);
        char *t2 = strtok(NULL, DELIMS);
        char *t3 = strtok(NULL, DELIMS);
        char *t4 = strtok(NULL, DELIMS);
        char *t5 = strtok(NULL, DELIMS);
        char *extra = strtok(NULL, DELIMS);

        if (extra != NULL) {
            printf("Extra input detected: %s\n", extra);
            continue;
        }

        int n = (t1 != NULL) + (t2 != NULL) + (t3 != NULL) + (t4 != NULL) + (t5 != NULL);
        if (handle_line(t1, t2, t3, t4, t5, n))
        {
            break;
        }
    }
}

void ui_help(void)
{
    printf("Usage: <command> [arguments]\n");
    printf("Commands:\n");
    printf("  add <vector> <vector>       Add two vectors\n");
    printf("  sub <vector> <vector>       Subtract two vectors\n");
    printf("  dot <vector> <vector>       Compute the dot product of two vectors\n");
    printf("  print <vector>              Print a vector\n");
    printf("  help                        Show this help message\n");
}