/*
 * Defines functions for linked lists.
 * CSC 225, Assignment 8
 * Given code, Spring '21
 */

#include <stdlib.h>
#include <stdio.h>
#include "list.h"

/* lstcreate: Creates an empty linked list. */
List *lstcreate() {
    /* TODO: Complete this function, given no arguments:
     * ...return a pointer to a new, dynamically allocated List structure. */
	List *lst = (List *)malloc(sizeof(List) * 1);
	lst->head = NULL;  
        lst->size = 0;  
	return lst;  
}

/* lstdestroy: Destroys an existing linked list. */
void lstdestroy(List *lst) {
    /* TODO: Complete this function, given:
     *  lst - A pointer to a List structure
     * ...deallocate all memory associated with "lst". */
        Node *nd, *nxt; 
	
	if (lst == NULL) {
		return; 
	}
	nd = lst->head;  
	while (nd != NULL) {
		nxt = nd->next;
		free(nd);   
		nd = nxt;  
	}
	free(lst);
	lst = NULL; 
}

/* lstsize: Computes the size of a linked list. */
unsigned int lstsize(List *lst) {
    /* TODO: Complete this function, given:
     *  lst - A pointer to a List structure
     * ...return the number of nodes in "lst". */
	if(lst == NULL) { 
		return 0; 
	}
	return lst->size;
}

/* lstget: Gets an element in a linked list at an index. */
void *lstget(List *lst, unsigned int idx) {
    /* TODO: Complete this function, given:
     *  lst - A pointer to a List structure
     *  idx - A non-negative index
     * ...return a pointer to element "idx" of "lst", NULL if "idx" outside
     * the range [0, size - 1] */
	int count;
	Node *nd; 
	void *value;
 
	if(idx >= lstsize(lst) || idx < 0) {
		return NULL;   	
	} else { 
		nd = lst->head; 
		value = nd->value; 
		count = 0; 
		while(count < idx) { 
			nd = nd->next;
			value = nd->value;
			count += 1;    
		}
		return value; 
	}

}

/* lstset: Sets an element in a linked list at an index. */
int lstset(List *lst, unsigned int idx, void *value) {
    /* TODO: Complete this function, given:
     *  lst   - A pointer to a List structure
     *  idx   - A non-negative index
     *  value - A pointer to a desired element
     * ...set element "idx" of "lst" to "value"; return 0 on success, 1 if
     *  "idx" outside the range [0, size - 1]. */
	Node *nd; 
	int count;  
	if(idx >= lstsize(lst) || idx < 0) {
		return 1;
	} else {
		nd = lst->head; 
		count = 0; 
		while(count < idx) {
			nd = nd->next;
			count += 1; 
		}	
		nd->value = value;  
		return 0;  
	}
}

/* lstadd: Adds an element to a linked list at an index. */
int lstadd(List *lst, unsigned int idx, void *value) { 
    /* TODO: Complete this function, given:
     *  lst   - A pointer to a List structure
     *  idx   - A non-negative index
     *  value - A pointer to a desired element
     * ...add "value" as element "idx" of "lst"; return 0 on success, 1 if
     * "idx" outside the range [0, size]. */
	Node *nd;
	Node *nxt, *prev; 
	int count;   
	if( idx > lstsize(lst) + 1 || idx < 0) {
		return 1;
	} else {
		nd = (Node *)malloc(sizeof(Node) * 1);
 		nd->next = NULL; 
                nd->value = NULL;
		lst->size += 1; 
		if(idx == 0) { 
			nxt = lst->head; 
			lst->head = nd;
			nd->value = value;
			lst->head->next = nxt;    
			return 0;  
		}  else { 
			nxt = lst->head;
			count = 0; 
			while(count < idx) {
                                prev = nxt;  
				nxt = nxt->next; 
				count += 1; 
			} 	
                        nd->next = nxt; 
		        prev->next = nd; 
			nd->value = value; 	 
			return 0;
		} 
	}  	 
}

/* lstremove: Removes an element from a linked list at an index. */
void *lstremove(List *lst, unsigned int idx) {
    /* TODO: Complete this function, given:
     *  lst - A pointer to a List structure
     *  idx - A non-negative index
     * ...remove element "idx" of "lst"; return a pointer to the removed
     * element, NULL if "idx" outside the range [0, size - 1]. */
	int count; 
	Node *nd;  
	Node  *nxt; 
	void *elem;
	Node *prev;   
	if(idx >= lstsize(lst) || idx < 0) {
		return NULL; 
	} else { 
		if(idx == 0) { 
			nd = lst->head;
			elem = nd->value;
  			nxt = nd->next;   
			lst->head = nxt; 
		} else {
			nd = lst->head;    
			count = 0; 
			while(count < idx) {
				prev = nd;  
				nd = nd->next;
				count += 1;
			} 
			elem = nd->value; 
			nxt = nd->next;   
			prev->next = nxt;  
		}
		free(nd);   
		nd = NULL; 
		lst->size -= 1; 
		return elem; 
	}
}

/* lsttoarr: Creates an array from a linked list. */
void **lsttoarr(List *lst) {
    /* TODO: Complete this function, given:
     *  lst - A pointer to a List structure
     * ...return a dynamically allocated array of void pointers containing the
     * elements of "lst", in the same order. */
	int sz;  
	void **arr;
	int i;
	Node *nd;    
	if(lst == NULL) {
		return NULL; 
	}
	if(lst->size == 0) {
        	arr = NULL;
                lst->head = NULL; 
                lst->size = 0; 
                /*lstdestroy(lst); */
                return arr; 
        }
	sz = lst->size;
	arr = (void *)malloc(sizeof(void *) * (sz+1));
	nd = lst->head;
	arr[0] = nd->value; 
	for(i = 1; i < sz; i++) {
		nd = nd->next; 
		arr[i] = nd->value; 
		free(nd); 				
 	}
	/*lstdestroy(lst);*/  
	return arr; 		
	
}

/* arrtolst: Creates a linked list from an array. */
List *arrtolst(void **arr, unsigned int n) {
    /* TODO: Complete this function, given:
     *  arr - An array of void pointers
     *  n   - The length of the given array
     * ...return a pointer to a new, dynamically allocated list containing the
     * elements of "arr", in the same order. */
     int i; 
     List *lst = lstcreate(); 
	
     if(arr == NULL) { 
         return NULL; 
     }

     for(i = 0; i < n; i++) {
     	lstadd(lst, i, arr[i]); 
     }
     free(arr); 
     arr = NULL; 
     return lst; 
}
