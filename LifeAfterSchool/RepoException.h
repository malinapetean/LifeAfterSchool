#pragma once
#include <exception>
#include<string>
using namespace std;

class FileException :public std::exception
{
protected:
	string message;
public:
	FileException(const string& msg);
	virtual const char* what();
};

class RepositoryException :public exception
{
protected:
	string message;
public:
	RepositoryException();
	RepositoryException(const string& msg);
	virtual const char* what();
};