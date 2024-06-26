///////////////////////////////////////////////////////////
//
// Υλοποίηση του set_utils για Sets βασισμένα σε Binary Search Tree.
//
///////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include "set_utils.h"
#include "ADTSet.h"
#include "ADTVector.h"



// Χρησιμοποιούμε τη συγκεκριμένη υλοποίηση του UsingBinarySearchTree/ADTSet.c,
// οπότε γνωρίζουμε την ακριβή δομή για την αναπαράσταση των δεδομένων.
// Αντιγράφουμε εδώ τον ορισμό των structs ώστε να μπορούμε να προσπελάσουμε
// τα περιεχόμενά τους.

struct set {
	SetNode root;				// η ρίζα, NULL αν είναι κενό δέντρο
	int size;					// μέγεθος, ώστε η set_size να είναι Ο(1)
	CompareFunc compare;		// η διάταξη
	DestroyFunc destroy_value;	// Συνάρτηση που καταστρέφει ένα στοιχείο του set
};

struct set_node {
	SetNode left, right;		// Παιδιά
	Pointer value;
	int size;
};

CompareFunc comp;

void update_size(SetNode node) {
    if(node==NULL)return;
    node->size=1;
      if(node->left!=NULL) node->size+=node->left->size;
      if(node->right!=NULL)node->size+= node->right->size;
}

int qsort_compare(const void *a, const void *b){
       Pointer ptr_a=*(Pointer*)a;
      Pointer ptr_b=*(Pointer*)b;
      return comp(ptr_a, ptr_b);
}

SetNode sorted_array_to_bst(Pointer* array, int start, int end){
	if(start>end) return NULL;

	int mid = (start+end)/2;
	SetNode node=malloc(sizeof(*node));
	node->value=array[mid];
	
	node->left = sorted_array_to_bst(array, start, mid-1);
	node->right= sorted_array_to_bst(array, mid+1, end);
    update_size(node);
	return node;
}

Pointer* merge_sorted_arrays(Pointer* arr1, Pointer* arr2, int size1, int size2, CompareFunc compare){
	Pointer* merged = malloc((size1+size2)*sizeof(Pointer));
	int i=0, j=0, k=0;

	while(i<size1 && j<size2){
		if(compare(arr1[i], arr2[j])<=0){
			merged[k]=arr1[i];
			k++;
			i++;
		}else{
			merged[k]=arr2[j];
			k++;
			j++;
		}
	}
	while(i<size1){
		merged[k]=arr1[i];
		k++;
		i++;
	}
	while(j<size2){
		merged[k]=arr2[j];
		k++;
		j++;
	}
	return merged;
}

void inordertraversal(SetNode node, TraverseFunc f, Set set){
    if(node==NULL) return;
	  inordertraversal(node->left, f, set);
	  f(set, node->value);
	  inordertraversal(node->right, f, set);
}

void inorder_vector(SetNode node, Vector vector){
     if(node==NULL) return;
	  inorder_vector(node->left, vector);
	  vector_insert_last(vector, node->value);
	  inorder_vector(node->right, vector);
}

Set set_from_vector(Vector vec, CompareFunc compare) {
	int size = vector_size(vec);
	if(size==0) return set_create(compare, NULL);

	Pointer* array = malloc(size*sizeof(Pointer));
	Pointer* unsorted_array = malloc(size*sizeof(Pointer));
    int count=0;

	for(int i=0; i<size; i++){
		array[i]=vector_get_at(vec, i);
		if(compare(array[i-1], array[i])>0){
			unsorted_array[count]=array[i];
			count++;
		}
	}

    Set set = set_create(compare, NULL);
	if(count>0){
		qsort(unsorted_array, count, sizeof(Pointer), qsort_compare);

		Pointer* merged_array = merge_sorted_arrays(array, unsorted_array, size-count, count, compare);

		set->root =sorted_array_to_bst(merged_array, 0, size-1);
		set->size=size;
		free(merged_array);
	}else{
		set->root = sorted_array_to_bst(array, 0, size-1);
		set->size=size;
	}
     free(array);
	 free(unsorted_array);
	 
	 return set;
}

Vector set_to_vector(Set set) {
	Vector new_vector = vector_create(0, free);
	inorder_vector(set->root, new_vector);
	return new_vector;
}

void set_traverse(Set set, TraverseFunc f) {
   inordertraversal(set->root, f, set);
}

void bst_to_array(SetNode node, Pointer* array, int* index){
	if(node==NULL) return; 

	bst_to_array(node->left, array, index);
	array[(*index++)]=node->value;
	bst_to_array(node->right, array, index);
}

Set set_merge(Set set1, Set set2, CompareFunc compare) {
	int size1=set_size(set1);
	int size2=set_size(set2);

    Pointer* array1=malloc(size1*sizeof(Pointer));
	Pointer* array2=malloc(size2*sizeof(Pointer));

	int index1=0;
	bst_to_array(set1->root, array1, &index1);

	int index2=0;
	bst_to_array(set2->root, array2, &index2);

	Pointer* merged_array = merge_sorted_arrays(array1, array2, size1, size2, compare);

	Set merged_set = set_create(compare, NULL);
	merged_set->root = sorted_array_to_bst(merged_array, 0, size1+size2-1);
	merged_set->size = size1+size2;

	free(array1);
	free(array2);
	free(merged_array);
	
	return merged_set;
}

Pointer set_find_k_smallest(Set set, int k) {
	SetNode node = set->root;
	while(node!=NULL){
	  int left_size=(node->left != NULL) ? node->left->size : 0;
	     if(left_size+1==k){
			return node->value;
		 }else if(left_size>=k){
			node=node->left;
		 }else{
			k-=left_size+1;
            node=node->right;
		 }
    }
	return NULL;
}
