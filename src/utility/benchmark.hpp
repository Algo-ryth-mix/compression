#pragma once

#include <chrono>
#include <iomanip>
#include <iostream>


namespace pixl
{
	static std::ostream* logstream = &std::cout;
	static std::int64_t last_duration = 0;
	
	class benchmark
	{
	public:
		benchmark(const std::string& name, bool print_to_cout = false) : print_cout(print_to_cout)
		{
			using hres = std::chrono::high_resolution_clock;
			
			if(print_cout){
				std::cout << "[pixl] >>>>>>>>>>>>>>>>>>>>>>>" <<std::endl;
				std::cout << "starting benchmark: " << name <<std::endl;

				auto tp = hres::now();
				std::cout << "it is: " << tp.time_since_epoch().count() << std::endl;
			}
			if(logstream){
				*logstream << "[pixl] >>>>>>>>>>>>>>>>>>>>>>>" <<std::endl;
				*logstream << "starting benchmark: " << name <<std::endl;

				auto tp = hres::now();
				*logstream << "it is: " << tp.time_since_epoch().count() << std::endl;
			}
			start = std::chrono::high_resolution_clock::now();
		}

		~benchmark()
		{
			using hres = std::chrono::high_resolution_clock;
			
			auto stop = hres::now();

			if(print_cout){
				
				auto tp = hres::now();
				std::cout << "it is: " << tp.time_since_epoch().count() << std::endl;
				std::cout << "the benchmark took: " << std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count() << "ns" <<std::endl;
				std::cout << "[pixl] <<<<<<<<<<<<<<<<<<<<<<<" <<std::endl;

				
			}
			if(logstream){
				auto tp = hres::now();
				*logstream << "it is: " << tp.time_since_epoch().count() << std::endl;
				*logstream << "the benchmark took: " << std::chrono::duration_cast<std::chrono::nanoseconds>( stop - start).count() << "ns" <<std::endl;
				*logstream << "[pixl] <<<<<<<<<<<<<<<<<<<<<<<" <<std::endl;
				
			}

			last_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
		}



	private:

		bool print_cout;
		std::chrono::high_resolution_clock::time_point start;
		
	};
}


