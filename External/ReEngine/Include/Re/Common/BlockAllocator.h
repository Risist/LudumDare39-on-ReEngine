#pragma once
#include <Re\Common\Settings.h>

class T
{

};

//template <typename T>
class BlockAllocator
{
public:
	BlockAllocator() noexcept = default;
	BlockAllocator(const BlockAllocator&) noexcept {}
	template <typename U>
	BlockAllocator(const FreelistAllocator<U>&) noexcept {}
	BlockAllocator(BlockAllocator&& other) noexcept :  list(other.list) {
		other.list = nullptr;
	}

	BlockAllocator& operator = (const FreelistAllocator&) noexcept {
		// noop
		return *this;
	}

	BlockAllocator();

	void allocate();

	b2BlockAllocator *allocator;
};

