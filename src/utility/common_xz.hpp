#pragma once
#include <cstdint>
#include <vector>
#include <lzma.h>

namespace detail {

	inline bool code(lzma_stream* stream,const std::vector<uint8_t>& in,std::vector<uint8_t>* out)
	{
		int INCREMENT_STEPS = 512;
		
		lzma_action action = LZMA_RUN;

		std::vector<uint8_t>& output = *out;
		output.resize(in.size());

		stream->next_in = in.data();
		stream->avail_in = in.size();
		stream->next_out = output.data();
		stream->avail_out = output.size();

		lzma_ret ret = lzma_code(stream,action);

		while(ret == LZMA_OK )
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
				action = LZMA_FINISH;
			}

			ret = lzma_code(stream,action);
		}
		if(ret != LZMA_OK && ret != LZMA_STREAM_END) __debugbreak();

		
		if(ret == LZMA_STREAM_END)
		{
			const std::size_t overhang = stream->avail_out;
			output.resize(output.size()-overhang);
			return true;
		}
		return false;
	}
}
