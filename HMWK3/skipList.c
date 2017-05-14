#include "skipList.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* ************************************************************************
Main Function
 ************************************************************************ */
/* Test function:
 param: no parameters
 pre:	no parameres
 post: prints out the contents of the skip list */

void test() {
    int i, j;
    int M;
    struct skipList *slst;
    test();

    srand(time(NULL));

    slst = (struct skipList *)malloc(sizeof(struct skipList)); /*2*/
    assert(slst);

    /*  Initialize the skip list */

    /*  FIXME */

    /*  Add to the skip list  M = 20 random integers in [0,100] */

    /*  FIXME */

    /*  Print out the contents of the skip list in the breadth-first order,
        starting from top.
        While printing the elements,
        move to a new line every time you reach the end of one level,
        and move down to the lower level of the skip list.
        For example, the print out of a skip list with 5 elements
        should look like

        7
        7 14 29
        3 7 9 14 20
     */

    /*  FIXME */

    /* Develop 3 test cases for printing out the contents of skip list
       after remove function:
             int removeSkipList(struct skipList *slst, TYPE e)
     */

    /*  FIXME */

    /* Develop 3 test cases corresponding to the above 3 test cases
       for printing out the output of contains function when e is equal to
       the elements you removed above:
             int containsSkipList(struct skipList *slst, TYPE e)
    */

    /*  FIXME */
}

/* ************************************************************************
Internal Functions
 ************************************************************************ */

/* Coin toss function:
 param: no parameters
 pre: no parameres
 post: output is a random intiger number in {0,1} */
int flipSkipLink(void) {
    return rand() % 2;
}

/* Move to the right as long as the next element is smaller than the input
 value: param: 	current -- pointer to a place in the list from where we
 need to slide to the right param:	e --  input value pre:	current is
 not NULL post: returns one link before the link that contains the input value e
 */
struct skipLink *slideRightSkipList(struct skipLink *current, TYPE e) {
    while ((current->next != 0) && LT(current->next->value, e))
        current = current->next;
    return current;
}

/* Create a new skip link for a value
        param: e	 -- the value to create a link for
        param: nextLnk	 -- the new link's next should point to nextLnk
        param: downLnk -- the new link's down should point to downLnk
        pre:	none
        post:	a link to store the value */
struct skipLink *newSkipLink(TYPE e, struct skipLink *nextLnk,
                             struct skipLink *downLnk) {
    struct skipLink *tmp = (struct skipLink *)malloc(sizeof(struct skipLink));
    assert(tmp != 0);
    tmp->value = e;
    tmp->next = nextLnk;
    tmp->down = downLnk;
    return tmp;
}

/* *** TODO: LinkAdd *** */
/* Add a new skip link recursively
 param: current -- pointer to a place in the list where the new element should
 be inserted param: e	 -- the value to create a link for pre:	current is
 not NULL post: a link to store the value */
struct skipLink *skipLinkAdd(struct skipLink *current, TYPE e) {
    /* FIXME */
}

/* ************************************************************************
Public Functions
 ************************************************************************ */

/* Initialize skip list:
 param:  slst -- pointer to the skip list
 pre:	slst is not null
 post: the sentinels are allocated, the pointers are set, and the list size
 equals zero */
void initSkipList(struct skipList *slst) {
    slst->size = 0;
    slst->topSentinel = (struct skipLink *)malloc(sizeof(struct skipLink));
    assert(slst->topSentinel);
    slst->topSentinel->next = NULL;
    slst->topSentinel->down = NULL;
}

/* Checks if an element is in the skip list:
 param: slst -- pointer to the skip list
 param: e -- element to be checked
 pre:	slst is not null
 post: returns true or false  */
int containsSkipList(struct skipList *slst, TYPE e) {
    struct skipLink *tmp = slst->topSentinel;
    while (tmp != 0) {                                   /* 2pts */
        tmp = slideRightSkipList(tmp, e);                /* 1pt */
        if ((tmp->next != 0) && EQ(e, tmp->next->value)) /* 2pts */
            return 1;
        tmp = tmp->down; /* 1pt */
    }
    return 0;
}

/* Remove an element from the skip list:
 param: slst -- pointer to the skip list
 param: e -- element to be removed
 pre:	slst is not null
 post: the new element is removed from all internal sorted lists */
void removeSkipList(struct skipList *slst, TYPE e) {
    struct skipLink *current, *tmp;
    current = slst->topSentinel; /* 1pts */
    while (current != 0) {       /* 2pts */
        current = slideRightSkipList(current, e);
        if (current->next != 0 && EQ(e, current->next->value)) { /* 2pts */
            tmp = current->next;                                 /* 2pts */
            current->next = current->next->next;
            free(tmp); /* 2pts */
            if (current->down == NULL)
                slst->size--; /* 2pts */
        }
        current = current->down; /* 1pt */
    }
}

int recurseSkipList(struct skipLink *currNode, TYPE e, int depth) {
    while (currNode->next->value <= e) {
        currNode = currNode->next;
    }

    if (currNode->down != NULL) {
        recurseSkipList(currNode->down, e, depth);
    }

    if (depth >= 1) {
        skipLinkAdd(currNode, e);
        depth -= 1;
    }

    return depth;
}

/* *** TODO: Add *** */
/* Add a new element to the skip list:
 * param: slst -- pointer to the skip list
 * param: e -- element to be added
 * pre: slst is not null
 * post: e is added to the lowest list and randomly to higher-level lists
 */
void addSkipList(struct skipList *slst, TYPE e) {
    assert(slst != NULL);
    struct skipLink *currNode = slst->topSentinel;
    int depth = 1;

    while (flipSkipLink()) {
        depth += 1;
    }

    recurseSkipList(currNode, e, depth);
}

/* Find the number of elements in the skip list:
 param: slst -- pointer to the skip list
 pre: slst is not null
 post: the number of elements */
int sizeSkipList(struct skipList *slst) {
    return slst->size;
}

struct skipLink *linkedList(struct skipLink *node) {
    while (node->down != NULL) {
        node = node->down;
    }
    return node;
}

TYPE maxSkipList(struct skipLink *list) {
    TYPE max = 0;
    while (list != NULL) {
        if (max < list->value) {
            max = list->value;
        }
        list = list->next;
    }

    return max;
}

int widthType(TYPE num) {
    int width = 1;
    while (num / 10 > 0) {
        width += 1;
    }

    return width;
}

void printSep(int max, int modifier) {
    int i, count = max - modifier;
    for (i = 0; i < count; i++) {
        printf("%s", "-");
    }
}

/* *** TODO: Print *** */
/* Print the links in the skip list:
 * param: slst -- pointer to the skip list
 * pre: slst is not null and slst is not empty
 * post: the links in the skip list are printed breadth-first, top-down
 */
void printSkipList(struct skipList *slst) {
    assert(slst != NULL && slst->size > 0);
    struct skipLink *firstNode = slst->topSentinel;
    struct skipLink *currNode = firstNode;
    TYPE max = maxSkipList(linkedList(firstNode));
    int maxWidth = 2 + widthType(max);
    int currWidth;

    while (firstNode != NULL) {
        printf("%s", "|");
        currWidth = 1;
        printSep(maxWidth, currWidth);
        while (currNode != NULL) {
            printf("%f", currNode->value);
            currWidth = widthType(currNode->value);
            printSep(max, currWidth);
            currNode = currNode->next;
        }
        firstNode = firstNode->down;
    }

    return;
}

/* Merge two skip lists:
 * param: slst1 -- pointer to the skip list 1.
 * param: slst2 -- pointer to the skip list 2.
 * pre: slst1 and slst2 != null, and skip list 1 and skip list 2 are not
 * post: slst1 points to the merger skip list, slst2 is null.
 */
void mergeSkipList(struct skipList *slst1, struct skipList *slst2) {
    assert((slst1 != NULL) && (slst2 != NULL));
    struct skipLink *currNode = linkedList(slst2->topSentinel);

    while (currNode->next != NULL) {
        addSkipList(slst1, currNode->value);
        currNode = currNode->next;
    }
} /* end of the function */
