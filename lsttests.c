/*
 * Tests functions for linked lists.
 * CSC 225, Assignment 8
 * Given tests, Spring '21
 */

#include <stddef.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h> 
#include "list.h"

/* test01empty: Tests empty lists. */
void test01empty() {
    List *lst = lstcreate();

    assert(lst != NULL);
    assert(lst->head == NULL);
    assert(lst->size == 0);
	
    assert(lstsize(lst) == 0);	 

    lstdestroy(lst);
}

/* test01empty2: Test my other functions on empty lists */
void test01empty2() {
    int work, x = 2; 
    void *val;
    void **arr;
    List *lst = lstcreate();
    
    val = lstremove(lst, 0);    
    assert(val == NULL);
    val = lstremove(lst, 5);
    assert(val == NULL); 

    val = lstget(lst, 0); 
    assert(val == NULL); 
    val = lstget(lst, 3); 
    assert(val == NULL);

    work = lstset(lst, 0, &x); 
    assert(work == 1); 
    work =  lstset(lst, 7, &x); 
    assert(work == 1); 

    assert(lst->size == 0); 

    arr = lsttoarr(lst); 
    assert(arr == NULL); 
    /* can't try to access elements from an empty arr, ex. arr[0] results in a seg fault */ 

    lst = arrtolst(arr, 0); 
    assert(lst == NULL);   
    
    lstdestroy(lst);
}

/* tes01empty3: Tests having a list and then it becoming empty */ 
void test01empty3() { 
    int work;  
    int x = 2, y = 4, z = 6;
    void *val;  
    List *lst = lstcreate(); 

    work = lstadd(lst, 3, &x); 
    assert(work == 1);

    work = lstadd(lst, 0, &x); 
    assert(work == 0); 
    assert(lst->head->value == &x); 

    val = lstremove(lst, 0); 
    assert(val == &x); 

    assert(lst->size == 0);  
    assert(lst->head == NULL);

    work = lstadd(lst, 0, &x);
    assert(work == 0); 
    assert(lst->head->value == &x); 
    work = lstadd(lst, 1, &y); 
    assert(work == 0); 
    assert(lst->head->next->value == &y); 
    work = lstadd(lst, 2, &z); 
    assert(work == 0);  
    assert(lst->head->next->next->value == &z); 
    assert(lst->size == 3); 
    
    val = lstremove(lst, 2); 
    assert(val == &z); 
    assert(lst->head->next->next == NULL); 
    assert(lst->size == 2); 

    work = lstadd(lst, 5, &z); 
    assert(work == 1); 
    work = lstadd(lst, 2, &z);
    assert(work == 0);
    val = lstget(lst, 2); 
    assert(val == &z); 

    val = lstremove(lst, 0); 
    assert(val == &x); 
    assert(lst->head->value == &y); 
    assert(lst->head->next->value == &z);  
    assert(lst->head->next->next == NULL);

    val = lstget(lst, 0); 
    assert(val == &y); 
 
    lstdestroy(lst);  
}

/* test02add: Tests adding to lists. */
void test02add() {
    List *lst = lstcreate();
    int work, x = 1, y = 2, z = 9, q = 4;
    void *val;  

    lstadd(lst, 0, &x);
    lstadd(lst, 1, &y); 
    lstadd(lst, 2, &z);    

    assert(lst->head != NULL);
    assert(lst->head->value == &x);
    assert(lst->head->next->value == &y);
    assert(lst->head->next->next->value == &z);
    assert(lst->head->next->next->next == NULL);
    assert(lst->size == 3); 

    val = lstget(lst, 0);
    assert(val == &x);
    val = lstget(lst, 1); 
    assert(val == &y); 
    val = lstget(lst, 2); 
    assert(val == &z);  

    lstset(lst, 0, &z);
    val = lstget(lst, 0); 
    assert(val == &z); 

    work = lstset(lst, 2, &y); 
    assert(work == 0); 
    val = lstget(lst, 2); 
    assert(val == &y); 

    lstadd(lst, 0, &q);  
    assert(lst->head->value == &q);
    assert(lst->head->next->value == &z);
    assert(lst->head->next->next->value == &y); 
    assert(lst->head->next->next->next->value == &y);  
    assert(lst->head->next->next->next->next  == NULL); 

    lstremove(lst, 2);  
    lstadd(lst, 0, &x); 
    lstadd(lst, 2, &x);
    assert(lst->size == 5); 

    assert(lst->head->value == &x);
    assert(lst->head->next->value == &q); 
    assert(lst->head->next->next->value == &x); 
    assert(lst->head->next->next->next->value == &z); 
    assert(lst->head->next->next->next->next->value == &y); 
    assert(lst->head->next->next->next->next->next == NULL);

    lstadd(lst, 3, &q); 
    assert(lst->head->next->next->next->value == &q); 

    lstdestroy(lst);
}

/* test03remove: Tests removing from lists. */
void test03remove() {
    List *lst = lstcreate();
    int x = 1, y = 2, z = 5;
    void *elem;
     
    lstadd(lst, 0, &x);
    lstadd(lst, 1, &y);
    assert(lst->size == 2);  

    elem = lstremove(lst, 0);
    assert(elem == &x);  

    elem = lstget(lst, 0);   
    assert(elem == &y); 
    assert(lst->size == 1);   

    lstadd(lst, 1, &z); 
    assert(lst->size == 2);

    assert(lst->head != NULL);
    assert(lst->head->value == &y);
    assert(lst->head->next->value == &z);
    assert(lst->head->next->next == NULL);

    lstdestroy(lst);
}

/* test04lsttoarr: Test changing list to array. */ 
void test04lsttoarr() {
   List *lst = lstcreate(); 
   int x = 7, y = 8, z = 2; 
   void **test;
   void **arr; 

   test = (void *)malloc(sizeof(void *) * 3); 
   test[0] = &y;
   test[1] = &x; 
   test[2] = &z; 

   lstadd(lst, 0, &y); 
   lstadd(lst, 1, &x); 
   lstadd(lst, 2, &z);
   
   arr = lsttoarr(lst);
     
   assert(arr[0] == test[0]);
   assert(arr[1] == test[1]); 
   assert(arr[2] == test[2]); 

   free(arr); 
   free(test);  
}

/* test05arrtolst: Test changing array to list. */ 
void test05arrtolst() {
    List *lst = lstcreate(); 
    List *test = lstcreate();
    List *other = lstcreate();  
    int x = 3, y = 6, z = 4, n = 3; 
    void **arr; 
    void *val1;
    void *val2;   
 
    /*arr = (void *)malloc(sizeof(void *) * (n+1)); 
    arr[0] = &x; 
    arr[1] = &y; 
    arr[2] = &z; 
    printf("XX %d\n", *((int *)(arr[1])));*/

    lstadd(test, 0, &x); 
    lstadd(test, 1, &y); 
    lstadd(test, 2, &z); 

    lstadd(other, 0, &x); 
    lstadd(other, 1, &y); 
    lstadd(other, 2, &z); 

    arr = lsttoarr(other); 

    lst = arrtolst(arr, n); 

    val1 = lstget(lst, 0); 
    val2 = lstget(test, 0); 
    assert(val1 == val2);

    val1 = lstget(lst, 1);
    val2 = lstget(test, 1); 
    assert(val1 == val2); 

    val1 = lstget(lst, 2); 
    val2 = lstget(test, 2);
    assert(val1  == val2);   

    val1 = lstget(lst, 3); 
    assert(val1 == NULL); 
    val2 = lstget(test, 3); 
    assert(val2 == NULL); 
 
    lstdestroy(lst); 
   
}

/* test06setlst(): check the setlst function */ 
void test06setlst() { 
	List *lst = lstcreate(); 
	int work, x = 7, y = 13; 
        void *val; 

        work = lstset(lst, 0, &x); 
	assert(work == 1); 

	lstadd(lst, 0, &x); 
        lstadd(lst, 1, &x); 
        lstadd(lst, 2, &x); 

        work = lstset(lst, 2, &x); 
	assert(work == 0); 

	work = lstset(lst, 0, &y); 
        assert(work == 0);	

	val = lstget(lst, 0); 
	assert(val == &y); 
	val = lstget(lst, 2);
	assert(val == &x); 
	val = lstget(lst, 1); 
	assert(val == &x);

	lstdestroy(lst);  
}

int main(void) {
    test01empty();
    test01empty2(); 
    test01empty3(); 
    test02add();
    test03remove();
    test04lsttoarr();
    test05arrtolst();
    test06setlst();

    return 0;
}
