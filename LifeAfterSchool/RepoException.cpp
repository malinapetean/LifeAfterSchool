#include "RepoException.h"

FileException::FileException(const string& msg) : message(msg)
{
}

const char* FileException::what()
{
	return message.c_str();
}

RepositoryException::RepositoryException() :exception{}, message{ "" }
{
}

RepositoryException::RepositoryException(const string& msg) :message{ msg }
{
}

const char* RepositoryException::what()
{
	return this->message.c_str();
}


