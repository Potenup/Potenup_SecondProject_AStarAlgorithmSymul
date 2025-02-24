#pragma once
#include <errno.h>
#include <string>

namespace soun
{
	class ErrorController
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
			ErrorController();

			static ErrorController &Get();

			std::string GetErrorMessage(const std::string& s);

		private :
			static ErrorController* instance;

			void GetErrorMessageToErrno(std::string& errorMessage);
	};
}