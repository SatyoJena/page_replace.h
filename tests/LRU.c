#include "page_replace.h"

int main() {
	for (size_t i=0; i<QUEUE_SZ; i++) page_q[i].pg_n = INVALID;

	size_t page_request_seq[] = {7,0,1,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1};
	size_t n = ARRAY_LEN(page_request_seq);

	size_t fault_count =  page_replace_by_age(n, page_request_seq, lt);
	printf("Total page faults = %lu, when queue size is %d.\n", fault_count, QUEUE_SZ );

	return 0;
}
