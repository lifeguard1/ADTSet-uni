///////////////////////////////////////////////////////////
//
// Υλοποίηση του set_utils με γενικό τρόπο, χρησιμοποιώντας
// μια οποιαδήποτε υλοποίηση του ADT Set.
//
///////////////////////////////////////////////////////////

#include <stdlib.h>

#include "set_utils.h"
#include "ADTVector.h"
#include "ADTSet.h"

Set set_from_vector(Vector vec, CompareFunc compare) {
	
	Set new_set = set_create(compare, NULL);

    int size = vector_size(vec);
	for(int i=0; i<size; i++){
		Pointer value = vector_get_at(vec, i);
		set_insert(new_set, value);
	}
	return new_set;
}

Vector set_to_vector(Set set) {
	
	Vector new_vector = vector_create(0, NULL);

	for(SetNode node=set_first(set); node!=SET_EOF;  node=set_next(set, node)){
         Pointer value=set_node_value(set, node);
		 vector_insert_last(new_vector, value);
	}
	return new_vector;
}

void set_traverse(Set set, TraverseFunc f) {
      for(SetNode node=set_first(set); node!=SET_EOF;  node=set_next(set, node)){
         Pointer value=set_node_value(set, node);
		 f(set, value);
	  }
}

Set set_merge(Set set1, Set set2, CompareFunc compare) {
    Set merged_set = set_create(compare, NULL);

	for(SetNode node=set_first(set1); node!=SET_EOF;  node=set_next(set1, node)){
         Pointer value=set_node_value(set1, node);
		 set_insert(merged_set, value);
	}

	for(SetNode node=set_first(set2); node!=SET_EOF;  node=set_next(set2, node)){
         Pointer value=set_node_value(set2, node);
		 set_insert(merged_set, value);
	}
	return merged_set;
}

Pointer set_find_k_smallest(Set set, int k) {
	SetNode node = set_first(set);
	 for(int i=0; i<k && node!=SET_EOF; i++){
		node = set_next(set, node);
	 }
	 return set_node_value(set, node);
}