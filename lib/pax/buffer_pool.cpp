//
// Copyright 2011,2014 Ettus Research LLC
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#include <buffer_pool.hpp>
#include <zero_copy.hpp>
#include <boost/shared_array.hpp>
#include <vector>
#include <bounded_buffer.hpp>

using namespace pax::transport;

#ifdef UHD_TXRX_DEBUG_PRINTS
/*
 * This is the implementation for the static variable 's_buffer_count'
 * located in uhd/transport/zero_copy.hpp.
 * It is used in the managed_buffer class.
 */
boost::detail::atomic_count managed_buffer::s_buffer_count(0);
#endif // UHD_TXRX_DEBUG_PRINTS

//! pad the byte count to a multiple of alignment
static size_t pad_to_boundary(const size_t bytes, const size_t alignment){
    return bytes + (alignment - bytes)%alignment;
}

buffer_pool::~buffer_pool(void){
    /* NOP */
}

/***********************************************************************
 * Buffer pool implementation
 **********************************************************************/
class buffer_pool_impl : public buffer_pool{
public:
    buffer_pool_impl(
        const std::vector<ptr_type> &ptrs,
        boost::shared_array<char> mem
    ): _ptrs(ptrs), _mem(mem){
        /* NOP */
    }

    ptr_type at(const size_t index) const{
        return _ptrs.at(index);
    }

    size_t size(void) const{
        return _ptrs.size();
    }

private:
    std::vector<ptr_type> _ptrs;
    boost::shared_array<char> _mem;
};

/***********************************************************************
 * Buffer pool factor function
 **********************************************************************/
buffer_pool::sptr buffer_pool::make(
    const size_t num_buffs,
    const size_t buff_size,
    const size_t alignment
){
    //1) pad the buffer size to be a multiple of alignment
    //2) pad the overall memory size for room after alignment
    //3) allocate the memory in one block of sufficient size
    const size_t padded_buff_size = pad_to_boundary(buff_size, alignment);
    boost::shared_array<char> mem(new char[padded_buff_size*num_buffs + alignment-1]);

    //Fill a vector with boundary-aligned points in the memory
    const size_t mem_start = pad_to_boundary(size_t(mem.get()), alignment);
    std::vector<ptr_type> ptrs(num_buffs);
    for (size_t i = 0; i < num_buffs; i++){
        ptrs[i] = ptr_type(mem_start + padded_buff_size*i);
    }

    //Create a new buffer pool implementation with:
    // - the pre-computed pointers, and
    // - the reference to allocated memory.
    return sptr(new buffer_pool_impl(ptrs, mem));
}

