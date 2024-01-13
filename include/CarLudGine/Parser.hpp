
#pragma once

#include <functional>

namespace clg_parserfilescpp
{
	template<typename T1, typename T2>
	T1 readFile(const std::function<T2()>& functionReadInFile,
		const std::function<T1(T2)>& functionReadFromAFile)
	{
		return functionReadFromAFile(functionReadInFile());
	}

	inline void writeFile(const std::function<void()>& function)
	{
		function();
	}
	inline void closeFile(const std::function<void()>& function)
	{
		function();
	}
}
