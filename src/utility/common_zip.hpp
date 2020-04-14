#pragma once
#define MINIZ_NO_ZLIB_COMPATIBLE_NAMES
#include "../zip/miniz.h"
#include <vector>



namespace detail
{
	using coder_func = decltype(mz_inflate);

	
	inline bool code(coder_func func, mz_stream* stream,const std::vector<uint8_t>& in,std::vector<uint8_t>* out)
	{
		int INCREMENT_STEPS = 512;
		
		auto action = MZ_NO_FLUSH;

		std::vector<uint8_t>& output = *out;
		output.resize(in.size());

		stream->next_in = in.data();
		stream->avail_in = in.size();
		stream->next_out = output.data();
		stream->avail_out = output.size();

		auto ret = func(stream,action);

		while(ret == MZ_OK )
		{
			if(stream->avail_out == 0)
			{
				const std::size_t previous_size = output.size();
				output.resize(previous_size + INCREMENT_STEPS);
				stream->next_out = output.data() + previous_size;
				stream->avail_out = INCREMENT_STEPS;			
			}
			else if(stream->avail_in == 0)
			{
				action = MZ_FINISH;
			}

			ret = func(stream,action);
		}
		if(ret != MZ_OK && ret != MZ_STREAM_END) __debugbreak();

		
		if(ret == MZ_STREAM_END)
		{
			const std::size_t overhang = stream->avail_out;
			output.resize(output.size()-overhang);
			return true;
		}
		return false;
	}

	
}
