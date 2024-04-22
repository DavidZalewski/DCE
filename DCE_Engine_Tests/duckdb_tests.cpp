#include "pch.h"
#include "CppUnitTest.h"

#include <duckdb.hpp>
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace EngineTests
{
	TEST_CLASS(DUCKDB_TESTS)
	{
	public:

		TEST_METHOD(MODEL_A_TEST)
		{
			duckdb::DuckDB db(":memory:"); // Create an in-memory database
			duckdb::Connection con(db);

			// Data Definition Language (DDL) - No results
			con.Query("CREATE TABLE integers(i INTEGER, j INTEGER)");

			// Insert statements
			con.Query("INSERT INTO integers VALUES (3, 4), (5, 6), (7, NULL)");

			// Data Manipulation Language (DML) - Returns results
			auto result = con.Query("SELECT * FROM integers WHERE i > 4");

			// Print results in a console-friendly format
			result->Print();

			// Access results more directly (example):
			if (!result->HasError()) {
				auto chunk = result->Fetch(); // Fetch a chunk of data
				if (chunk) {
					// Process the result data (access by column index or name)
				}
			}
			else {
				std::cerr << "Query Error: " << result->GetError() << std::endl;
			}

		}

		TEST_METHOD(DUCKDB_Test2) 
		{
			duckdb::DuckDB db(":memory:");
			duckdb::Connection con(db);

			// Create a table
			con.Query("CREATE TABLE weather(city VARCHAR, temperature INTEGER)");

			// Insert data
			con.Query("INSERT INTO weather VALUES ('New York', 75), ('Los Angeles', 80), ('London', 65)");

			// Query and process results
			auto result = con.Query("SELECT city, temperature FROM weather WHERE temperature > 70");
			if (!result->HasError()) {
				for (size_t i = 0; i < result->RowCount(); i++) {
					std::string city = result->GetValue(0, i).ToString();
					int temperature = result->GetValue(1, i).GetValue<int32_t>();
					std::cout << city << ": " << temperature << std::endl;
				}
			}
			else {
				std::cerr << "Query Error: " << result->GetError() << std::endl;
			}


		}
	};
}
