#include <iostream>
#include <fstream>
#include <cmath>
#include "inner_data_struct.h"

using namespace std ;



bool should_end_encode(Inner_coding_t * inner_coding_data) ;
void output_coding_rst(Inner_coding_t *inner_coding_data , ostream &fs) ;
void end_encode(Inner_coding_t *inner_coding_data , ostream &fs ) ;
bool encode(unsigned int ori_code , Inner_coding_t * inner_coding_data , ostream &output_fs) ;
