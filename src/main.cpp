#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <fstream>
#include <set>
#include <thread>


#include "utility/benchmark.hpp"
#include "utility/buffer_match.hpp"
#include "utility/filesize.hpp"

#ifdef TEST_ZIP_INSTEAD
#include "utility/zip_compressor.hpp"
#define COMPRESSOR_TO_TEST zip_compressor
#else
#include "utility/xz_compressor.hpp"
#define COMPRESSOR_TO_TEST xz_compressor
#endif


std::pair<long long,long long> test_compressor(const std::string& filename,std::uint32_t compressor_preset,bool extreme,bool print_to_cout = false);

int main(int argc,char ** argv)
{
	if(argc != 4) return 0;


	std::uint32_t preset = atoi(argv[1]);
	bool extreme = atoi(argv[2]) != 0;
	std::string filename = argv[3];
	

	std::ofstream logfile("logfile.txt");

	pixl::logstream = &logfile;

	long long CompressionAvg =0;
	long long DecompressionAvg =0;

	
	for(std::size_t i = 0;i < 10;++i){
		std::cout << preset << (extreme>0) <<std::endl;
		auto [comp,decomp] = test_compressor(filename,preset+1,(extreme>0),true);

		CompressionAvg += comp;
		DecompressionAvg += decomp;
		
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}


	auto uncompressed_len = pixl::filesize(filename);
	auto compressed_len = pixl::filesize(filename+".xz");


	CompressionAvg /= 10;
	DecompressionAvg /= 10;
	std::ofstream res("result"+std::to_string(preset)+std::to_string(extreme)+filename+"res.txt");
	res << CompressionAvg << std::endl << DecompressionAvg <<std::endl <<  static_cast<double>(compressed_len) / static_cast<double>(uncompressed_len);
	res.close();

	
	pixl::logstream = &std::cout;
	
}

inline std::pair<long long,long long> test_compressor(const std::string& filename,std::uint32_t compressor_preset,bool extreme,bool print_to_cout)
{
	const auto uncomp = read_file(filename);
	const std::vector<uint8_t>* decomp;
	std::vector<uint8_t> perm_decomp;

	{
		COMPRESSOR_TO_TEST compressor(compressor_preset,extreme);
		compressor.select(filename+".xz");
		compressor.set(&uncomp);
		
		pixl::benchmark bench("compressing file",print_to_cout);
		compressor.write();
	}

	long long A = pixl::last_duration;

	{
		COMPRESSOR_TO_TEST de_compressor;
		de_compressor.select(filename + ".xz");
		de_compressor.read();
		{
			pixl::benchmark bench("decompressing file",print_to_cout);
			decomp = de_compressor.get();
		}
		perm_decomp.resize(decomp->size());
		memcpy(perm_decomp.data(),decomp->data(),decomp->size());
		
	}

	long long B = pixl::last_duration;
	
	{
		std::cout << "probing" <<std::endl;
		auto uncompressed_len = pixl::filesize(filename);
		auto compressed_len = pixl::filesize(filename+".xz");

		if(compressed_len == 0 || uncompressed_len == 0) __debugbreak();

		
		if(uncompressed_len == -1) std::cerr << "compressor failed, uncompressed data-set missing" <<std::endl;
		if(compressed_len == -1) std::cerr << "compressor failed, no output!"<<std::endl;
		std::cout << "compression ratio " << static_cast<double>(compressed_len) / static_cast<double>(uncompressed_len) <<std::endl;
	}
	{
		std::cout << "match-check" <<std::endl;
		std::cout << "result: " << pixl::buffer_match(uncomp,perm_decomp) <<std::endl;
		
	}

	return std::make_pair(A,B);
	
	
}