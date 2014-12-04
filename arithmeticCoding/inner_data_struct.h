#ifndef INNER_CODING_STRUCT
#define INNER_CODING_STRUCT

#include <cmath>

#define data_t unsigned long long 
const unsigned int MAX_CHAR_NUM = 257U ; // 256 chars + 1 EOF
const unsigned int EOF_CODE = MAX_CHAR_NUM -1 ; 
const unsigned long long INIT_INTERVAL_MIN_VAL = 0UL ;
const unsigned long long INIT_INTERVAL_MAX_VAL = -1 ; // it is : 1111111...
const unsigned long long UPDATE_TOTAL_FREQ_MAX = 1000UL ;

typedef struct Inner_coding_t{
    unsigned long long char_freq[MAX_CHAR_NUM] ;
    unsigned long long interval_range[MAX_CHAR_NUM + 1] ;
    unsigned long long total_freq ;
    unsigned int max_freq_ite ;
    unsigned long interval_len ;
} Inner_coding_t ;


void update_interval_range(Inner_coding_t * inner_data , unsigned long long low , unsigned long long high) ;
void update_max_freq_ite(Inner_coding_t *inner_coding_data) ;
void init_inner_coding_data(Inner_coding_t  *inner_coding_data) ;
void normalize_inner_coding_data(Inner_coding_t *inner_coding_data) ;

#endif
