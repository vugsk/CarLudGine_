
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
  			{ return readFromFile<T>(key, readInFile(name)); }

		template<typename T>
		void write(const char* key, T&& data)
  			{ add(_dataWriteInFile, key, data); }

		void close(const char* name);

	private:
		nlohmann::json			   _dataWriteInFile;
		std::stack<const char*>    st_key;
		std::stack<nlohmann::json> st_data;

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
		T getValue( const char *key, const nlohmann::json &data ) {
			if (st_data.top().is_object() && st_data.top().empty())
			{
				st_data.pop();
				st_data.top().erase(st_key.top());
				st_key.pop();
				return readFromFile<T>(key, st_data.top());
			}
			return data[key];
		}


		template<typename T>
		T readFromFile(const char*			  key,
						  const nlohmann::json& data,
						  const bool			  test = false)
		{
			if (!test) { st_data.push(data); }

			for (auto& i : data.items())
			{
				if (i.key() == key) break;
				if (i.key() != key && !st_data.top().empty()
								&& !i.value().is_object())
					st_data.top().erase(i.key());
				if (i.value().is_object())
				{
					st_key.push(i.key().c_str());
					return readFromFile<T>(key, i.value());
				}
			}

			if (st_data.top().is_object() && st_data.top().empty())
			{
				st_data.pop();
				st_data.top().erase(st_key.top());
				st_key.pop();
				return readFromFile<T>(key, st_data.top(), true);
			}
			return data[key];
		}
	};
}

