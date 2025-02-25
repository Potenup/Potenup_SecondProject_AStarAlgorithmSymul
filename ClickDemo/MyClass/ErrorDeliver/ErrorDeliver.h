#pragma once
#include <errno.h>
#include <string>

namespace soun
{
	class ErrorDeliver
	{
		//struct ErrorMessage
		//{
		//	ErrorMessage(int errno)
		//	{
		//		this->errorMessage = std::strerror(errno);
		//		this->errNumber = errno;
		//	}
		//	std::string errorMessage;
		//	int errNumber;
		//};

		public :
			ErrorDeliver(const char* errorMessage);

			~ErrorDeliver();

			const std::string &GetErrorMessage() const;

		private :
			void MakeErrorMessage();

		private :
			std::string errorMessage_;
	};
}