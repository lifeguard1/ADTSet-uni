//////////////////////////////////////////////////////////////////
//
// Unit tests για το set_utils.
// Οποιαδήποτε υλοποίηση οφείλει να περνάει όλα τα tests.
//
//////////////////////////////////////////////////////////////////
#include <stdlib.h>
#include "acutest.h"			// Απλή βιβλιοθήκη για unit testing
#include "ADTVector.h"
#include "ADTSet.h"

#include "set_utils.h"

int compare_ints(Pointer a, Pointer b) {
	return *(int*)a - *(int*)b;
}

void traverse_func(Set set, Pointer value){
	printf("%d", *(int*)value);
}

void test_set_from_vector(void) {
    Vector vec = vector_create(0,free);
	  for(int i=0; i<10; i++){
		int* num=malloc(sizeof(int));
		*num=i%5;
		vector_insert_last(vec, num);
	  }
	  Set set = set_from_vector(vec, compare_ints);

      TEST_ASSERT(set_size(set)==5);
	  for(int i=0; i<5; i++){
		int* num=malloc(sizeof(int));
		*num=i;
		TEST_ASSERT(set_find(set, num)!=NULL);
		free(num);
	  }
	  set_destroy(set);
	  vector_destroy(vec);
}

void test_set_to_vector(void) {
      Vector vec = vector_create(0,free);
	  for(int i=0; i<10; i++){
		 int* num=malloc(sizeof(int));
		 *num=i%5;
		vector_insert_last(vec, num);
	  }
	  Set set = set_from_vector(vec, compare_ints);
	   Vector new_vec=set_to_vector(set);

	   TEST_ASSERT(vector_size(new_vec)==5);
		for(int i=0; i<5; i++){
			 int* num=vector_get_at(new_vec, i);
			 TEST_ASSERT(*num==i);
		}
	   vector_destroy(vec);
       set_destroy(set);
       vector_destroy(new_vec);
}

void test_set_traverse(void) {
      Vector vec = vector_create(0, free);
	  for(int i=0; i<5; i++){
		int* num =  malloc(sizeof(int));
		*num=i;
		vector_insert_last(vec, num);
	  }
	  Set set = set_from_vector(vec, compare_ints);

	  set_traverse(set, traverse_func);
	  printf("\n");
	  set_destroy(set);
	  vector_destroy(vec);
}

void test_set_merge(void) {
    Vector vec1 = vector_create(0, free);
    Vector vec2 = vector_create(0, free);\

	for(int i=0; i<5; i++){
		int* num1=malloc(sizeof(int));
         *num1=i;
         vector_insert_last(vec1, num1);

         int* num2=malloc(sizeof(int));
         *num2=i+3;
        vector_insert_last(vec2, num2);
	}

	 Set set1=set_from_vector(vec1, compare_ints);
     Set set2=set_from_vector(vec2, compare_ints);

     Set merged_set=set_merge(set1, set2, compare_ints);

     TEST_ASSERT(set_size(merged_set)==8);
      for (int i=0; i<8; i++) {
         int* num=malloc(sizeof(int));
        *num=i;
        TEST_ASSERT(set_find(merged_set, num)!=NULL);
        free(num);
    }

      set_destroy(set1);
     set_destroy(set2);
     set_destroy(merged_set);
     vector_destroy(vec1);
     vector_destroy(vec2);
}	

void test_set_find_k_smallest(void) {
    Vector vec = vector_create(0, free);
	for(int i=0; i<10; i++){
		int* num=malloc(sizeof(int));
		*num=i;
		vector_insert_last(vec, num);
    }

	Set set = set_from_vector(vec, compare_ints);

	for(int k=1; k<10; k++){
       int*value=(int*)set_find_k_smallest(set, k);
	   TEST_ASSERT(*value==k);
	   free(value);
	}
	set_destroy(set);
	vector_destroy(vec);
}

// Λίστα με όλα τα tests προς εκτέλεση
TEST_LIST = {
	{ "test_set_import_from_vector",	test_set_from_vector },
	{ "test_set_export_to_vector",		test_set_to_vector },
	{ "test_set_traverse",				test_set_traverse },
	{ "test_set_merge",					test_set_merge },
	{ "test_set_find_k_smallest",		test_set_find_k_smallest },

	{ NULL, NULL } // τερματίζουμε τη λίστα με NULL
}; 
