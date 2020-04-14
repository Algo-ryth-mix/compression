#pragma once
#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

#include "common.hpp"
#include "file.hpp"

namespace pixl
{
	class compressor_base
	{
	//Preamble	
	public:
		using data_type_t = std::vector<uint8_t>;
		using data_ptr_t  = std::vector<uint8_t>*;
		using const_data_type_t = const std::vector<uint8_t>;
		using const_data_ptr_t  = const std::vector<uint8_t>*;
		
		using byte = std::uint8_t;
		using hunk = byte*;
		using hunk_size_t = std::size_t;

		
	
		virtual ~compressor_base() = default;
		compressor_base() = default;
		compressor_base(const compressor_base& other) = default;
		compressor_base(compressor_base&& other) noexcept = default;
		compressor_base& operator=(const compressor_base& other) = default;
		compressor_base& operator=(compressor_base&& other) noexcept = default;


		compressor_base& select(const std::string& filename) noexcept
		{
			PIXL_GUARD_BAD_ALLOC(m_path = filename);	
			return *this;
		}

		
		compressor_base& read()
		{
			if(m_path.empty()) throw std::logic_error("this compressor has no associated file!");
			m_in_compressed = read_file(m_path);
			if(m_in_compressed.size() == 0) __debugbreak();
			m_out_compressed = m_in_compressed;
			m_read_dirty = true;
			return *this;
		}

		compressor_base& read(const std::string& filename)
		{
			select(filename);
			return read();
		}

		compressor_base& write()
		{
			if(m_path.empty()) throw std::logic_error("this compressor has no associated file!");
			if(m_set_dirty) m_out_compressed = compress(&m_raw);
			write_file(m_path,m_out_compressed);
			return *this;
		}
		
		compressor_base& write(const std::string& filename)
		{
			select(filename);
			return write();
		}


		const_data_ptr_t get() const
		{
			if(!m_in_compressed.empty() && m_read_dirty)
			{
				m_raw = decompress(&m_in_compressed);
			}
			return &m_raw;
		}

		void set(const_data_ptr_t data)
		{
			m_raw = *data;
			m_set_dirty = true;
		}

		
	protected:
		std::string get_path() const { return m_path;}
		virtual data_type_t compress(const_data_ptr_t) const = 0;
		virtual data_type_t decompress(const_data_ptr_t) const = 0;

	private:
		bool m_set_dirty;
		bool m_read_dirty;
		std::string m_path;
		data_type_t m_in_compressed;
		mutable data_type_t m_raw;
		data_type_t m_out_compressed;
	};
}
