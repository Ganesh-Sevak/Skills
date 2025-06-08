/*
 * partners: ksali
 *
 * In this lab, we were tasked to use a sparse matric to store only the non-zero elements
 * to improve efficiency. Utilizing a data structure called a list of tuples that stores
 * sparse matrices more efficiently that a 2-D array, we implement the functions load_tuples,
 * gv_tuples, set_tuples, save_tuples, add_tuples, and destroy_tuples.
 *
 * The load_tuples function opens a file with the name input_file, reads the data from the
 * file, and returns a matrix of the list of tuples type. The function first reads the file
 * using fscanf and populates three dynamically allocated arrays called rows, cols, and vals,
 * which store every row, column, and value respectively of each tuple in the input file. The
 * arrays are then sorted in row-major order using an insertion sort, ensuring that any change
 * made to one array (rows, cols, or vals) happens to the rest. After it has been sorted, the
 * function then creates a new node for every element in the arrays, setting the new node's row
 * member to rows[m], col member to cols[m], and value member to vals[m], where m is the current index.
 * The nodes are linked using a pointer called prev, which always points to the next node, allowing
 * linkage between each newly made node. After the linked list has been created, the function calls
 * the helper functions removeDuplicates to remove any duplicate nodes in the list and removeZeroes
 * to remove any zero-valued nodes in the list. The function then returns a pointer to the list of
 * tuples struct.
 *
 * The gv_tuples function returns the value of the element at the given row and column within the matrix.
 * It first checks if the matrix is valid (not NULL) and if the row and column index are valid. If
 * they are all valid, the function traverses the linked list and looks for a node with the given
 * row and column. When it is found, the value of the node is returned.
 *
 * The set_tuples function sets the element at row and col to value, where row, col, and value are
 * inputs to the function. The function utilizes gv_tuples to check whether a node with row and col
 * index exists. If the value is zero and the node does not exist, the function does nothing. If
 * the value is zero and the node does exist, the function deletes the node from the list. If the
 * value is non-zero and the node does exist, the function overwrites the value currently stored at
 * the node. If the value is non-zero and the node does not exist, the function dynamically allocates
 * memory for a new node and inserts it in the correct place in the list.
 *
 * The save_tuples function writes the data in the given sparse matrix structure to the given text file.
 *
 * The add_tuples function performs matrix addition with input matrices matA and matB and returns their
 * sum in a new list of tuples struct. The function first checks if the matrices are valid then if
 * addition between them is possible (same dimensions). If so, the function creates a new list of
 * tuples struct called matC and initializes its members. The contents of matA is copied into matC,
 * and the sum of matC and matB are overwritten into matC. If the row and column of B and C match,
 * the function calls set_tuples on the sum of their values. If B is less than C, the function calls
 * set_tuples on only B. If matB is longer than matC, the rest of matB is appended into matC. The
 * function then returns matC.
 *
 * The destroy_tuples function frees all memory associated with the given matrix.
 */

#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>

/*
 * removeDuplicates --  A helper function that removes any duplicates in a linked list, keeping only the first occurence
 * INPUTS:              head -- pointer to the first node of a linked list of sp_tuples_node structs
 * RETURN:              ret -- the number of deleted nodes
 */
int removeDuplicates(sp_tuples_node* head)
{
    /* initialize ret to 0 */
    int ret = 0;

    /* create temp ptr for freeing duplicate nodes */
    sp_tuples_node *temp;

    /* traverse linked list */
    while (head != NULL && head->next != NULL) {
        /* if the current node's row and col index is equal to the next node's row and col index */
        if (head->row == head->next->row && head->col == head->next->col) {
            /* set temp to second duplicate node */
            temp = head->next;
            /* update head */
            head->next = head->next->next;
            /* free duplicate */
            free(temp);
            /* increment ret */
            ret++;
        }
        else {
            /* update head */
            head = head->next;
        }
    }
    return ret;
}

/*
 * removeZeroes --  A helper function that removes any sp_tuples_node structs that have a value of zero
 * INPUTS:          head -- pointer to a pointer to the first node of a linked list of sp_tuples_node structs
 * RETURN:          ret -- the number of deleted nodes
 */
int removeZeroes(sp_tuples_node** tuples_head)
{
    /* initialize ret to 0 */
    int ret = 0;

    /* copy tuples_head into head ptr, create temp ptr for freeing zero nodes and prev ptr for redirection */
    sp_tuples_node *head = *tuples_head;
    sp_tuples_node *temp = NULL;
    sp_tuples_node *prev = NULL;

    /* traverse linked list */
    while (head != NULL) {
        /* if the value of the node is zero */
        if (head->value == 0) {
            /* if it is the first node */
            if (head == *tuples_head) {
                /* update tuples_head */
                *tuples_head = head->next;
                /* set temp to head */
                temp = head;
                /* update head */
                head = head->next;
                /* free zero node */
                free(temp);
                /* increment ret */
                ret++;
            }
            else {
                /* set temp to head */
                temp = head;
                /* update head */
                head = head->next;
                /* delete zero node from list */
                prev->next = head;
                free(temp);
                /* increment ret */
                ret++;
            }
        }
        else {
            /* update prev and head */
            prev = head;
            head = head->next;
        }
    }
    return ret;
}

sp_tuples * load_tuples(char* input_file)
{
    /* open file */
    FILE *file = fopen(input_file, "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return NULL;
    }

    /* allocate memory for a sp_tuples struct and check if successfull */
    sp_tuples *tuples = (sp_tuples *)malloc(sizeof(sp_tuples));
    if (tuples == NULL) {
        printf("Malloc failed!\n");
        return NULL;
    }
   
    /* read dimensions from the file and check if successfull */
    int result;
    result = fscanf(file, "%d%d", &tuples->m, &tuples->n);
    if (result != 2) {
        printf("Invalid dimensions!\n");
        free(tuples);
        return NULL;
    }

    /* initialize non-zero entries to zero */
    tuples->nz = 0;

    /* declare rows, cols, and vals arrays to hold tuples */
    int *rows = (int *)malloc(sizeof(int));
    int *cols = (int *)malloc(sizeof(int));
    double *vals = (double *)malloc(sizeof(double));

    /* declare row, col, val to temporarily hold values read from file */
    int row, col;
    double val;

    /* read first tuple */
    result = fscanf(file, "%d%d%lf", &row, &col, &val);

    /* while tuples are still being read */
    for (int i = 0; result == 3; i++) {

        /* if it is not the first iteration */
        if (i != 0) {
            /* increase size of rows, cols, and vals arrays by one */
            rows = (int *)realloc(rows, (i + 1) * sizeof(int));
            cols = (int *)realloc(cols, (i + 1) * sizeof(int));
            vals = (double *)realloc(vals, (i + 1) * sizeof(double));
        }

        /* populate the arrays */
        rows[i] = row;
        cols[i] = col;
        vals[i] = val;

        /* increment non-zero entries member in tuples */
        tuples->nz++;

        /* read next tuple */
        result = fscanf(file, "%d%d%lf", &row, &col, &val);
    }

    /* declare row_temp, col_temp, and val_temp to temporarily hold values of the current tuple */
    int row_temp, col_temp, empty_index;
    double val_temp;

    /* sort rows, cols, and vals arrays using insertion sort */
    /* for each element in the unsorted region of the rows, cols, and vals arrays */
    for (int j = 1; j < tuples->nz; j++) {

        /* fill temp variables and initialize empty index to j */
        row_temp = rows[j];
        col_temp = cols[j];
        val_temp = vals[j];
        empty_index = j;

        /* for each element in the sorted region of the rows, cols, and vals arrays */
        for (int k = j - 1; k >= 0; k--) {

            /* if the current row and col index is less than or equal to the row and col index of an element in the sorted region */
            if ((row_temp * tuples->n + col_temp) <= (rows[k] * tuples->n + cols[k])) {
                /* store the greater element into the empty index and update empty index */
                rows[empty_index] = rows[k];
                cols[empty_index] = cols[k];
                vals[empty_index] = vals[k];
                empty_index = k;
            }
            else {
                break;
            }
            /* store temp variables in empty index */
            rows[empty_index] = row_temp;
            cols[empty_index] = col_temp;
            vals[empty_index] = val_temp;
        }
    }

    /* declare prev pointer that points to the previous node in the linked list */
    sp_tuples_node *prev = NULL;

    /* iterate through tuples in reverse order and link them starting from tail to head */
    for (int m = tuples->nz - 1; m >= 0; m--) {

        /* allocate memory for a sp_tuples_node struct and check if successfull */
        sp_tuples_node *node = (sp_tuples_node *)malloc(sizeof(sp_tuples_node));
        if (node == NULL) {
            printf("Malloc failed!\n");
            return NULL;
        }

        /* initialize node's members */
        node->row = rows[m];
        node->col = cols[m];
        node->value = vals[m];
        node->next = prev;

        /* update prev */
        prev = node;
    }

    /* initialize tuples_head to prev */
    tuples->tuples_head = prev;

    /* remove duplicates from list */
    tuples->nz -= removeDuplicates(tuples->tuples_head);

    /* remove zeroes from list */
    tuples->nz -= removeZeroes(&tuples->tuples_head);

    /* free rows, cols, and vals arrays */
    free(rows);
    free(cols);
    free(vals);

    /* close file */
    fclose(file);
    return tuples;
}

double gv_tuples(sp_tuples * mat_t, int row, int col)
{
    /* check if mat_t is NULL */
    if (mat_t == NULL) {
        return 0;
    }
    /* check if row and col index is out of bounds */
    if (row < 0 || row >= mat_t->m || col < 0 || col >= mat_t->n) {
        return 0;
    }

    /* copy tuples head into curr */
    sp_tuples_node *curr = mat_t->tuples_head;
   
    /* traverse the list of tuples */
    while (curr != NULL) {

        /* if tuple row and col match row and col */
        if (curr->row == row && curr->col == col) {
            /* return value */
            return curr->value;
        }

        /* update curr */
        curr = curr->next;
    }
    return 0;
}



void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{
    /* check if mat_t is NULL */
    if (mat_t == NULL) {
        return;
    }
    /* check if row and col index is out of bounds */
    if (row < 0 || row >= mat_t->m || col < 0 || col >= mat_t->n) {
        return;
    }
   
    /* if value is zero and the node at row and col does not exist */
    if (value == 0 && gv_tuples(mat_t, row, col) == 0) {
        return;
    }

    /* if value is zero and the node at row and col does exist */
    if (value == 0 && gv_tuples(mat_t, row, col) != 0) {

        /* copy tuples head into curr and declare prev ptr */
        sp_tuples_node *curr = mat_t->tuples_head;
        sp_tuples_node *prev = mat_t->tuples_head;

        /* traverse the list of tuples */
        while (curr != NULL) {
            /* if tuple row and col match row and col */
            if (curr->row == row && curr->col == col) {
                /* if it is the first node */
                if (curr == mat_t->tuples_head) {
                    /* delete node from list, update tuples_head, and free */
                    mat_t->tuples_head = curr->next;
                    free(curr);
                   
                    /* decrement non-zero entries member in tuples */
                    mat_t->nz--;
                    return;
                }
                else {
                    /* delete node from list and free */
                    if (prev != NULL) {
                        prev->next = curr->next;
                        free(curr);
           
                        /* increment non-zero entries member in tuples */
                        mat_t->nz--;
                        return;
                    }
                }
            }
            else {
                /* update prev and curr */
                prev = curr;
                curr = curr->next;
            }
        }
        return;
    }

    /* if value is non-zero and the node at row and col does exist */
    if (gv_tuples(mat_t, row, col) != 0) {

        /* copy tuples head into curr */
        sp_tuples_node *curr = mat_t->tuples_head;

        /* traverse the list of tuples */
        while (curr != NULL) {
            /* if tuple row and col match row and col */
            if (curr->row == row && curr->col == col) {
                /* set node's value to new value */
                curr->value = value;
                return;
            }
            else {
                /* update curr */
                curr = curr->next;
            }
        }
        return;
    }

    /* if value is non-zero and the node at row and col does not exist */
    if (gv_tuples(mat_t, row, col) == 0) {

        /* allocate memory for a new sp_tuples_node struct and check if successfull */
        sp_tuples_node *new_node = (sp_tuples_node *)malloc(sizeof(sp_tuples_node));
        if (new_node == NULL) {
            printf("Malloc failed!\n");
            return;
        }

        /* initialize new_node's members */
        new_node->value = value;
        new_node->row = row;
        new_node->col = col;

        /* copy tuples head into curr and declare prev ptr */
        sp_tuples_node *curr = mat_t->tuples_head;
        sp_tuples_node *prev = mat_t->tuples_head;

        /* if the linked list is empty */
        if (mat_t->tuples_head == NULL) {

            /* set head to new_node and set new_node's next to NULL */
            mat_t->tuples_head = new_node;
            new_node->next = NULL;

            /* increment non-zero entries member in tuples */
            mat_t->nz++;
            return;
        }
       
        /* traverse the list of tuples */
        while (curr != NULL) {
            /* if current node's row and col is greater than row and col */
            if (curr->row * mat_t->n + curr->col > row * mat_t->n + col) {
                /* if node is the first node */
                if (curr == mat_t->tuples_head) {
                    /* set new_node's next to curr and update tuples_head to new_node */
                    new_node->next = curr;
                    mat_t->tuples_head = new_node;
                   
                    /* increment non-zero entries member in tuples */
                    mat_t->nz++;
                    return;
                }
                else {
                    /* set new_node's next to curr and update prev's next to new_node */
                    new_node->next = curr;
                    prev->next = new_node;

                    /* increment non-zero entries member in tuples */
                    mat_t->nz++;
                    return;
                }
            }
            /* update prev and curr */
            prev = curr;
            curr = curr->next;
        }

        /* place new_node at the end of the tuples list */
        if (prev != NULL) {
            prev->next = new_node;
            new_node->next = NULL;

            /* increment non-zero entries member in tuples */
            mat_t->nz++;
        }
    }
    return;
}



void save_tuples(char * file_name, sp_tuples * mat_t)
{
    /* check if mat_t is NULL */
    if (mat_t == NULL) {
        return;
    }

    /* open file for writing */
    FILE *file = fopen(file_name, "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    /* write dimensions into file */
    fprintf(file, "%d %d\n", mat_t->m, mat_t->n);

    /* copy tuples head into curr */
    sp_tuples_node *curr = mat_t->tuples_head;

    /* traverse the list of tuples */
    while (curr != NULL) {
        /* write tuples into file */
        fprintf(file, "%d %d %f\n", curr->row, curr->col, curr->value);

        /* update curr */
        curr = curr->next;
    }

    /* close file */
    fclose(file);
}



sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB)
{
    /* check if matA or matB is NULL */
    if (matA == NULL || matB == NULL) {
        return NULL;
    }

    /* check if addition between matA and matB is possible */
    if (matA->m != matB->m || matA->n != matB->n) {
        printf("Matrix addition is not possible.\n");
        return NULL;
    }

    /* allocate memory for a sp_tuples struct and check if successfull */
    sp_tuples *matC = (sp_tuples *)malloc(sizeof(sp_tuples));
    if (matC == NULL) {
        printf("Malloc failed!\n");
        return NULL;
    }

    /* initialize matC's members */
    matC->m = matA->m;
    matC->n = matA->n;
    matC->nz = 0;
    matC->tuples_head = NULL;

    /* copy matA head and matB head into headA and headB respectively */
    sp_tuples_node *headA = matA->tuples_head;
    sp_tuples_node *headB = matB->tuples_head;

    /* copy matA into matC */
    while (headA != NULL) {
        set_tuples(matC, headA->row, headA->col, headA->value);
        headA = headA->next;
    }

    /* copy matC head into headC */
    sp_tuples_node *headC = matC->tuples_head;

    /* traverse matC and matB */
    while (headB != NULL && headC != NULL) {
        /* if the row and col index of matB is equal to the row and col index of matC */
        if ((headB->row * matC->n + headB->col) == (headC->row * matC->n + headC->col)) {
            /* store the sum of their values into row and col of matC */
            set_tuples(matC, headB->row, headB->col, headC->value + headB->value);

            /* update headB and headC */
            headB = headB->next;
            headC = headC->next;
        }
        /* else if the row and col index of matB is less than the row and col index of matC */
        else if ((headB->row * matC->n + headB->col) < (headC->row * matC->n + headC->col)) {
            /* store the value of matB with its respective row and col into matC */
            set_tuples(matC, headB->row, headB->col, headB->value);

            /* set headC to matC's new head and update headB */
            headC = matC->tuples_head;
            headB = headB->next;
        }
        else if ((headB->row * matC->n + headB->col) > (headC->row * matC->n + headC->col)) {
            /* update headC */
            headC = headC->next;
        }
    }

    /* append the rest of matB into matC if possible */
    while (headB != NULL) {
        set_tuples(matC, headB->row, headB->col, headB->value);
        headB = headB->next;
    }

    return matC;
}

sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB)
{
    return NULL;
}
   
void destroy_tuples(sp_tuples * mat_t)
{
    /* check if mat_t is NULL */
    if (mat_t == NULL) {
        return;
    }

    /* declare temp ptr for freeing nodes */
    sp_tuples_node *temp = NULL;

    /* traverse the list of tuples */
    while (mat_t->tuples_head != NULL) {
        /* free each node in the linked list  */
        temp = mat_t->tuples_head;
        mat_t->tuples_head = mat_t->tuples_head->next;
        free(temp);
    }

    /* free sp_tuples struct */
    free(mat_t);
}  