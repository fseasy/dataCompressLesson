#include <iostream>
#include <fstream>
#include <cmath>
#include "inner_data_struct.h"

using namespace std ;

unsigned int get_interval_ite(data_t read_data , Inner_coding_t * inner_data) ;
bool should_end_decode(Inner_coding_t *inner_data) ;
void output_decode_rst(char decode_code , ostream &os) ;
bool decode(data_t read_data , Inner_coding_t * inner_data , ostream &os) ;

int main(int argc , char *argv[])
{
    if(argc < 3)
    {
        cerr << "usage : " << argv[0] << " [bz file] [output_file]" << endl ;
        return -1 ;
    }
    ifstream bz_file(argv[1] , ios::binary) ;
    ofstream out_file(argv[2] , ios::binary) ;
    if(!bz_file || !out_file)
    {
        cerr << "failed to open file named '" << argv[1] <<"' or '" 
             << argv[2] << "'" << endl ;
        return -1 ;
    }
    Inner_coding_t * inner_data = new Inner_coding_t ;
    init_inner_coding_data(inner_data) ;
    

    data_t read_data ;
    
    while( bz_file.read((char *)&read_data , sizeof(read_data)))
    {
        decode(read_data , inner_data , out_file) ;
    }
   
    delete inner_data ;
    out_file.close() ;
    bz_file.close() ;
    return 0 ;
}
/**
    get the interval index which the read_data belongs to 
    if error , return MAX_CHAR_NUM
  */
unsigned int get_interval_ite(data_t read_data , Inner_coding_t * inner_data)
{
    for(unsigned int i = 0 ; i < MAX_CHAR_NUM + 1 ; ++i)
    {
        if(read_data < inner_data->interval_range[i])
        {
            return i - 1  ;
        }
    }
    // if error , return MAX_CHAR_NUM
    return MAX_CHAR_NUM ;
}
/**
  get the decision is should end the decode
  */
bool should_end_decode(Inner_coding_t *inner_data)
{
    if(inner_data->interval_len < inner_data->total_freq)
    {
        return true ;
    }
    else
    {
        return false ;
    }
}
void output_decode_rst(char decode_code , ostream &os)
{
    os << decode_code ;
}
/**
    decode the read data
  */
bool decode(data_t read_data , Inner_coding_t * inner_data , ostream &os)
{
    while(!should_end_decode(inner_data))
    {
        //decode out one char or end
        unsigned int decode_code = get_interval_ite(read_data , inner_data) ;
        if(decode_code == EOF_CODE)
        {
            return true ;
        }
        else if(decode_code == MAX_CHAR_NUM)
        {
            cerr << "FATAL : decode code (code value is [" << decode_code << "])is too large ." ;
            return false ;
        }
        else
        {
            //char code
            char code = (char)decode_code ;
            output_decode_rst(code , os) ;
            //if decode out a char , update the interval
            inner_data->total_freq ++ ;
            inner_data->char_freq[decode_code] ++ ;
            update_max_freq_ite(inner_data) ;
            update_interval_range(inner_data , inner_data->interval_range[decode_code] , inner_data->interval_range[decode_code + 1]) ;
        }
        
    }
    normalize_inner_coding_data(inner_data) ;
}
