
#pragma once

#include <iostream>
#include <stack>
#include <nlohmann/json.hpp>
#include <yaml-cpp/node/detail/iterator_fwd.h>


namespace clg_parserfilescpp
{
	class ParserJsonFiles
	{
	public:
		ParserJsonFiles();
		~ParserJsonFiles();
		ParserJsonFiles(const ParserJsonFiles& other)	  = delete;
		ParserJsonFiles(ParserJsonFiles&& other) noexcept = delete;

		template<typename T>
		T read(const char* name, const char* key)
  			{ return readFromFile<T>(key, readInFile(name), false); }

		template<typename T>
		void write(const char* key, T&& data)
  			{ add(_dataWriteInFile, key, data); }

		void close(const char* name);

	private:
		nlohmann::json			   _dataWriteInFile;
		std::stack<const char*>    st_key;
		std::stack<nlohmann::json> st_data;
		bool test_bool;

	protected:
		[[nodiscard]] nlohmann::json getDataWriteInFile() const;

		static nlohmann::json readInFile(const char* name);

		void writeInFile(const char* name) const;

		static void	add(const nlohmann::json& whereFromData,
			nlohmann::json& whereData);

		template<typename T>
		static void add(nlohmann::json& data, const char* key, T&& value)
			{ data[key] = value; }


		template <typename T>
		bool getValue2( const char *key, T &value,
			const nlohmann::detail::iteration_proxy_value<
				nlohmann::detail::iter_impl<const nlohmann::basic_json<>>> &i )
		{
			if (i.value().is_object())
			{
				st_key.push(i.key().c_str());
				value = readFromFile<T>(key, i.value(), false);
				return false;
			}
			return true;
		}


		template <typename T>
		bool getValue1( const char *key, const nlohmann::json &data, T &value )
		{
			for (auto&i : data.items())
			{
				if (i.key() == key)
					break;
				if (i.key() != key && !st_data.top().empty() && !i.value().is_object())
					st_data.top().erase(i.key());
				if (const bool valueb = getValue2<T>(key, value, i); !valueb)
					return valueb;
			}
			return true;
		}

		template <typename T > bool getValue(const char *key, T &value)
		{
			if (st_data.top().is_object() && st_data.top().empty())
			{
				st_data.pop();
				st_data.top().erase(st_key.top());
				st_key.pop();
				value = readFromFile<T>(key, st_data.top(), true);
				return true;
			}
			return false;
		}

		template<typename T>
		T readFromFile(const char* key, const nlohmann::json& data, const bool test)
		{
			if (!test)
				st_data.push(data);
			if (T value; !getValue1<T>(key, data, value)
					|| getValue<T>(key, value))
				return value;
			return data[key];
		}
	};
}

