#include "ErrorController.h"
#include <cstring>
#include <cstdio>
#include <iostream>

namespace soun
{
	ErrorController* ErrorController::instance = nullptr;

	ErrorController::ErrorController()
	{
		ErrorController::instance = this;
		errno = 0;
	}

	ErrorController& ErrorController::Get()
	{
		return (*ErrorController::instance);
	}


	std::string ErrorController::GetErrorMessage(const std::string& s)
	{
		std::cout << "herror" << std::endl;
		std::string errorMessage;
		GetErrorMessageToErrno(errorMessage);
		return (s + " " + errorMessage);
	}

	void ErrorController::GetErrorMessageToErrno(std::string& errorMessage)
	{
		char buf[256];
		strerror_s(buf, sizeof(buf), errno);
		errorMessage = buf;
	}
}