#pragma once
#include "CustomDeleter.h"
#include <memory>

template<typename T>
class SdlWrapper
{
protected:
	typedef std::unique_ptr<T, CustomDeleter> SmartPtr;
	SmartPtr _pointer;
public:
	explicit SdlWrapper(T* value) : _pointer(SmartPtr(value))
	{
	}

	// TODO We do not ever want to use this, just convenience for default init
	SdlWrapper() : SdlWrapper(nullptr)
	{
	}

	// Only use when you have to directly use the raw pointer
	T* GetPointer() const
	{
		return _pointer.get();
	}
};
