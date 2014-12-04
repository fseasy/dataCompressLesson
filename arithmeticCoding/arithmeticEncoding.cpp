#include "encoding.h"


int main(int argc , char *argv[])
{
    if(argc <= 2)
    {
        cerr << "usage : " << argv[0] << " [encode_file] [output_file]" << endl ;
        return -1 ;
    }
    ifstream ori_file(argv[1] , ios::binary) ;
    ofstream out_file(argv[2] , ios::binary) ;
    if(!ori_file || !out_file)
    {
        cerr << "failed to open file named '" << argv[1] << "' or '"
             << argv[2] <<"'" << endl ;
        return -1 ;
    }
    
    Inner_coding_t * inner_data = new Inner_coding_t ;
    init_inner_coding_data(inner_data) ;

    char read_char ;
    while(ori_file.read(&read_char , 1))
    {
        unsigned char ori_code = (unsigned char) read_char ;
        //cout << (int)ori_code << endl ; 
        encode(ori_code , inner_data , out_file) ;
    }
    encode(EOF_CODE ,inner_data , out_file ) ;
    delete inner_data ;
    ori_file.close() ;
    out_file.close() ;
    return 0 ;
}

bool should_end_encode(Inner_coding_t * inner_coding_data)
{
    if(inner_coding_data->interval_len  < inner_coding_data->total_freq)
    {
        return true ;
    }
    else
    {
        return false ;
    }
}
/**
output the coding result
  */
void output_coding_rst(Inner_coding_t *inner_coding_data , ostream &fs)
{
    data_t rst = inner_coding_data->interval_range[0] + inner_coding_data->interval_len/2 ;
    
    //fs << rst << endl ;
    fs.write((char *)&rst , sizeof(rst)) ;
}
/**
    end a encode progress
  */
void end_encode(Inner_coding_t *inner_coding_data , ostream &fs )
{
    //output the encoding num
    output_coding_rst(inner_coding_data , fs) ;
    normalize_inner_coding_data(inner_coding_data) ;    
}
/**
   arithmetic  encode 
   the [ori_code]  can be the char code or the EOF code ! 
   firstly , we should judge if we should_end_encode ? if so :
            call end_encode
                                                        else :
            encode the code : if the code is char code  , just encode it !
                              else , that means the code is EOF code ! we should not only encode it, but also output it !
  */
bool encode(unsigned int ori_code , Inner_coding_t * inner_coding_data , ostream &output_fs)
{
    if(ori_code > MAX_CHAR_NUM -1 )
    {
        cerr << "FATAL : the origin code read error [value is " << ori_code << "]" << endl ;
        return false ;
    }
    if(!should_end_encode(inner_coding_data))
    {
        inner_coding_data->total_freq ++ ;
        inner_coding_data->char_freq[ori_code] ++ ;
        update_max_freq_ite(inner_coding_data) ;
        update_interval_range(inner_coding_data,inner_coding_data->interval_range[ori_code],inner_coding_data->interval_range[ori_code+1]) ;
        //cerr << "encode" << (char)ori_code << endl ;
        if(ori_code == EOF_CODE)
        {
            output_coding_rst(inner_coding_data , output_fs) ;
        }
    }
    else
    {
        //cerr << "has end a encode process" << endl ;
        //cerr << inner_coding_data->interval_len << endl ;
        //cerr << inner_coding_data->total_freq << endl ;
        end_encode(inner_coding_data , output_fs) ;
        encode(ori_code , inner_coding_data , output_fs) ;
    }
    return true ;
}
/**
    encode the EOF
  */

