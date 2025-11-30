#include <iostream>
#include <stdlib.h>
#include <cctype>

namespace kudaev
{
	size_t getline(std::istream&, char*, size_t, size_t);
	size_t strlen(const char*);
	char* getstr(char*);
	size_t has_same(const char*, const char*);
	char* lat_rmv(const char*);
}

int main()
{
	char* str1 = nullptr;
	char* str2 = nullptr;
	char* str3 = nullptr;
	try
	{
		str1 = kudaev::getstr(str1);
		if (!str1)
		{
			throw std::bad_alloc();
		}
		str2 = kudaev::getstr(str2);
		if (!str2)
		{
			throw std::bad_alloc();
		}
		str3 = kudaev::getstr(str3);
		if (!str3)
		{
			throw std::bad_alloc();
		}
	}
	catch (std::exception& ex)
	{
		std::cerr << ex.what() << '\n';
		if (str1)
		{
			free(str1);
		}
		if (str2)
		{
			free(str2);
		}
		if (str3)
		{
			free(str3);
		}
		return 1;
	}
	std::cout << str1 << '\n';
	std::cout << str2 << '\n';
	std::cout << str3 << '\n';
	std::cout << kudaev::has_same(str1, str2) << '\n';
	std::cout << kudaev::lat_rmv(str3) << '\n';
	free(str1);
	free(str2);
	free(str3);
}

size_t kudaev::getline(std::istream& in, char* str, size_t length, size_t capacity)
{
	in >> std::noskipws;
	char ch;
	while (in >> ch)
	{
		if (ch == '\n')
		{
			break;
		}
		str[length++] = ch;
		if (length >= capacity - 1)
		{
			return length;
		}
	}
	str[length] = '\0';
	return length;
}

size_t kudaev::strlen(const char* str)
{
	if (str == nullptr)
	{
		return 0;
	}
	size_t length = 0;
	while (str[length] != '\0')
	{
		length++;
	}
	return length;
}

char* kudaev::getstr(char* str)
{
	size_t capacity = 2, length = 0;
	try
	{
		str = (char*)malloc(capacity * sizeof(char));
		if (!str)
		{
			throw;
		}
		while (true)
		{
			length = getline(std::cin, str, length, capacity);
			if (length < capacity - 1 || std::cin.eof())
			{
				break;
			}
			capacity *= 2;
			char* new_str = (char*)malloc(capacity * sizeof(char));
			if (!new_str)
			{
				free(str);
				throw;
			}
			for (size_t i = 0; i < length; ++i)
			{
				new_str[i] = str[i];
			}
			free(str);
			str = new_str;
		}
	}
	catch (...)
	{
		if (str)
		{
			free(str);
			str = nullptr;
		}
		return nullptr;
	}
	return str;
}

size_t kudaev::has_same(const char* str1, const char* str2)
{
	if (str1 == nullptr || str2 == nullptr)
	{
		return 0;
	}
	size_t count = 0;
	size_t len1 = strlen(str1);
	size_t len2 = strlen(str2);
	for (size_t i = 0; i < len1; ++i)
	{
		for (size_t j = 0; j < len2; ++j)
		{
			if (str1[i] == str2[j])
			{
				count++;
			}
		}
	}
	return count;
}

char* kudaev::lat_rmv(const char* str)
{
	if (str == nullptr)
	{
		return nullptr;
	}
	size_t count = 0;
	for (size_t i = 0; str[i] != '\0'; ++i)
	{
		if (!isalpha(str[i]))
		{
			count++;
		}
	}
	char* new_str = (char*)malloc((count + 1) * sizeof(char));
	if (!new_str)
	{
		return nullptr;
	}
	size_t j = 0;
	for (size_t i = 0; str[i] != '\0'; ++i)
	{
		if (!isalpha(str[i]))
		{
			new_str[j++] = str[i];
		}
	}
	new_str[j] = '\0';
	return new_str;
}
