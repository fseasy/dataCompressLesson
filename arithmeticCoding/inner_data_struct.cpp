#include "inner_data_struct.h"

/**
    normalize the inner_coding_data 
        when the interval length less than a threshold , do it
  */
void normalize_inner_coding_data(Inner_coding_t *inner_coding_data)
{
    //cerr << "update" << endl ;
    if(inner_coding_data->total_freq > INIT_INTERVAL_MAX_VAL >> 2)
    {
        cerr << "update inner_coding" << endl ;
        // get the rate to update the char_freq
        double update_rate = 1/8 ;   
        //update char_freq 
        data_t freq_sum = 0 ;
        for(unsigned i = 0 ; i < MAX_CHAR_NUM ; ++i)
        {
            inner_coding_data->char_freq[i] = (data_t)ceil(inner_coding_data->char_freq[i] * update_rate) ;
            freq_sum += inner_coding_data->char_freq[i] ;
        }
        //update total freq
        inner_coding_data->total_freq = freq_sum ;
    }
    //update max
    update_max_freq_ite(inner_coding_data) ;
    //update interval range
    update_interval_range(inner_coding_data , INIT_INTERVAL_MIN_VAL , INIT_INTERVAL_MAX_VAL) ;

}

/**
  update the interval range [ length ] ;
  and set the interval [ range ]
 */
void update_interval_range(Inner_coding_t * inner_data , unsigned long long low , unsigned long long high)
{
    //total range [low , high )
    //update the length
    inner_data->interval_len = high - low ; 
    double interval = inner_data->interval_len / (double)inner_data->total_freq ;
    inner_data->interval_range[0] = low ;
    for(unsigned int i = 0 ; i < MAX_CHAR_NUM ; i++)
    {
        inner_data->interval_range[i+1] = inner_data->interval_range[i] + (unsigned long long)(interval * inner_data->char_freq[i]) ;
    }
    //make up the gap between the high and the interval_range[MAX_CHAR_NUM]
    unsigned long long gap = high - inner_data->interval_range[MAX_CHAR_NUM] ;
    if(gap)
    {
        for(unsigned int i = MAX_CHAR_NUM  ; i > inner_data->max_freq_ite ; --i)
        {
            inner_data->interval_range[i] += gap ;
        }
    }
}
/**
update the max freqency pointer
  */
void update_max_freq_ite(Inner_coding_t *inner_coding_data)
{
    unsigned long long max_freq = inner_coding_data->char_freq[inner_coding_data->max_freq_ite] ;
    for(unsigned i = 0 ; i < MAX_CHAR_NUM ; ++i)
    {
        if(inner_coding_data->char_freq[i] > max_freq)
        {
            inner_coding_data->max_freq_ite = i ;
            max_freq = inner_coding_data->char_freq[i] ;
        }
    }
}
/**
  init the inner coding data struct
  */
void init_inner_coding_data(Inner_coding_t  *inner_coding_data)
{
    //init total freq : let it be the MAX_CHAT_NUM
    inner_coding_data->total_freq = MAX_CHAR_NUM ;
    //init every char freq : let every char freq equals 1
    for(unsigned int  i = 0 ; i < MAX_CHAR_NUM ; i++)
    {
        inner_coding_data->char_freq[i] = 1UL ;
    }
    //init max freqency iterator : let it point to the last char
    inner_coding_data->max_freq_ite = MAX_CHAR_NUM -1 ;
    //update the range
    update_interval_range(inner_coding_data , INIT_INTERVAL_MIN_VAL , INIT_INTERVAL_MAX_VAL) ;
    
}
/**
  give the decesion : should end the encode progress ?
  */

