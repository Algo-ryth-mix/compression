#pragma once

#include "compressor.hpp"
#include "common_zip.hpp"
#include "compress_zip.hpp"
#include "decompress_zip.hpp"



class zip_compressor final : public pixl::compressor_base
{
public:
	zip_compressor(std::uint32_t level = 5,bool = false) :m_level(level){}

	
protected:
	data_type_t compress(const_data_ptr_t in) const override
	{
		mz_stream stream{};
		detail::init_encoder(&stream,m_level);
		return detail::compress(&stream,*in);
	}
	data_type_t decompress(const_data_ptr_t data) const override
	{
		mz_stream stream{};
		detail::init_decoder(&stream);
		return detail::decompress(&stream,*data);
	}
	
private:
	std::uint32_t m_level;
	
};

