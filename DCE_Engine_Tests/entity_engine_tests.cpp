#include "pch.h"
#include "CppUnitTest.h"
#include "../DCE_Engine/entity.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DCEEngineTests
{
	TEST_CLASS(DCEEngineTests)
	{
	public:
		
		TEST_METHOD(Entity_Construct_Success)
		{
			char* fileName = "file.csv";
			Entity entity = Entity(fileName);
			Assert::AreEqual(fileName, entity.getFileName());
		}
	};
}
