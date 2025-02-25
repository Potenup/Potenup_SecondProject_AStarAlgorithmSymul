#include "ErrorDeliver.h"
#include <cstdio>

namespace soun
{
	ErrorDeliver::ErrorDeliver(const char* errorMessage)
		: errorMessage_(errorMessage)
	{
		this->MakeErrorMessage();
	}

	ErrorDeliver::~ErrorDeliver()
	{
	}

	const std::string& ErrorDeliver::GetErrorMessage() const
	{
		return (this->errorMessage_);
	}

	void ErrorDeliver::MakeErrorMessage()
	{
		if (errno != 0)
		{
			char buf[256];
			strerror_s(buf, sizeof(buf), errno);
			this->errorMessage_ = this->errorMessage_ + " (" + buf + ")";
		}
	}
}