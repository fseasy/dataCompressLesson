encode : encode.o inner_data_struct.o
	g++ -o encode encode.o inner_data_struct.o
encode.o : arithmeticEncoding.cpp
	g++ -c -o  encode.o arithmeticEncoding.cpp
inner_data_struct.o : inner_data_struct.cpp
	g++ -c -o inner_data_struct.o inner_data_struct.cpp

decode : decode.o inner_data_struct.o
	g++ -o decode decode.o inner_data_struct.o
decode.o : arithmeticDecoding.cpp
	g++ -c -o decode.o arithmeticDecoding.cpp
inner_data_struct.o : inner_data_struct.cpp
	g++ -c -o inner_data_struct.o inner_data_struct.cpp
