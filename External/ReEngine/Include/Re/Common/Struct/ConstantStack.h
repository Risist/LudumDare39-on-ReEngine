#pragma once
#include <Re\Common\Settings.h>
#include <array>

//constexpr const size_t size = 10;

template<typename Ty, const size_t _size = 10>
class ConstantStack
{
public:
	void push(const Ty& value)
	{
		assert( _actualSize+1 <= _size);
		_actualSize++;
		_ar[_actualSize] = value;
	}
	Ty pop()
	{
		assert(_actualSize > 0);
		_actualSize--;
		return _ar[_actualSize+1];
	}

	size_t max_size() const { return _ar.size(); };
	size_t size() const { return _actualSize;  }



private:
	size_t _actualSize {0};
	/// array on which is stored stack;
	Ty _ar[_size];
};