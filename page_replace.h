#include <stdio.h>
#include <stdbool.h>
#define ARRAY_LEN(XS)  sizeof(XS)/sizeof(XS[0])
#define QUEUE_SZ 4

#define INVALID 9777559956

typedef struct {
	size_t pg_n;
	size_t age;
} q_cell;

q_cell page_q[QUEUE_SZ];
size_t q_i = 0;

void print_q() {
	printf("\t");
	for (size_t i =0; i<q_i; i++) printf("%lu ",page_q[i].pg_n);
	printf("\n");
}
bool pg_n_in_q(size_t ele)  {
	for (size_t i=0; i<QUEUE_SZ; i++ ) {
		if (page_q[i].pg_n == ele) {
			return true;
		}
	}
	return false;
}

bool lt(size_t a, size_t b) {return a<b;}
bool gt(size_t a, size_t b) {return a>b;}
size_t extreme_by_age(bool func(size_t,size_t)) {
	size_t ext_i = 0;
	for (size_t i = 0; i<QUEUE_SZ; i++) {
		if( func( page_q[i].age, page_q[ext_i].age ) ) {
			ext_i = i;
		}
	}
	return ext_i;
}
size_t page_replace_by_age(size_t n, size_t *page_request_seq, bool func(size_t,size_t)) {
    size_t fault_count = 0;
    for (size_t i=0; i<n; i++) {
    	size_t current_page = page_request_seq[i];
    	printf("\t%lu",current_page);
		if(!pg_n_in_q(current_page)) {
			if (q_i < QUEUE_SZ) {
				page_q[q_i++].pg_n = current_page;
			}else {
				page_q[extreme_by_age(func)].pg_n = current_page;
				page_q[extreme_by_age(func)].age = 0;
			}
			fault_count++;
			print_q();
		} // end of if 1
		for(size_t j=0; j<q_i; j++) page_q[j].age++;
		printf("\n");
	} // end of for 
	return fault_count;
}

size_t distance(size_t *arr, size_t start, size_t end, size_t ele) { // end exclusive 
	for (size_t i=start; i<end; i++) {
		if(arr[i] == ele) return i - start;	// returns distance
	}
	return INVALID;
}
size_t furthest_from_here(size_t n, size_t *page_request_seq, size_t start) { 
/*
	`start` and `end` are parameters for `page_request_seq`.
	This function checks in `page_request_seq` starting from `start`, ending at `n`,
	which of the elements in `page_q` is furthest.
	Returns its index in `page_q`

	invalids[] stores the indices in `page_q` where `distance()` returns INVALID
	tie of INVALIDs is broken by thier age.

					ITS NOT DIFFICULT, ITS COMPLICATED.
*/
    size_t invalids[QUEUE_SZ]; size_t invalid_i = 0;
    size_t furthest_i = 0;
    size_t furthest_dist = distance(page_request_seq,start,n, page_q[0].pg_n);
    for (size_t i = 1; i<q_i; i++) {
    	size_t cur  = distance(page_request_seq,start,n,page_q[i].pg_n);
    	if (cur == INVALID) {
    		invalids[invalid_i++] = i;
    		continue;
    	}
    	if(cur  > furthest_dist) {
    		furthest_i = i;
    		furthest_dist = cur;
    	}
    }
    if (invalid_i > 0) { // tie breaking
		size_t ext_i = 0;
		for (size_t i = 0; i<invalid_i; i++) {
			if( page_q[invalids[i]].age > page_q[invalids[ext_i]].age ) {
				ext_i = i;
			}
		}
		return invalids[ext_i];
    }else {
    	return furthest_i;
    }
    
}
size_t page_replace_by_distance(size_t n, size_t *page_request_seq) {
    size_t fault_count = 0;
    for (size_t i=0; i<n; i++) {
    	size_t current_page = page_request_seq[i];
		printf("\t%lu ",current_page);
		if(!pg_n_in_q(current_page)) {
			if (q_i < QUEUE_SZ) {
				page_q[q_i++].pg_n = current_page;
			}else {
				size_t index  = furthest_from_here(n, page_request_seq, i);
				page_q[index].pg_n = current_page; 
				page_q[index].age  = 0; 
			}
			fault_count++;
			print_q();
		} // end of if 1
		printf("\n");
		for(size_t j=0; j<q_i; j++) page_q[j].age++;
		
	} // end of for 
	return fault_count;	
}

