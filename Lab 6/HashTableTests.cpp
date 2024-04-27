#include "pch.h"
#include "CppUnitTest.h"
#include"..\\Lab 6\HashTable.h"
#include"..\\Lab 6\Menu.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HashTableTests
{
	TEST_CLASS(HashTableTests)
	{
	public:
		
        TEST_METHOD(TestInsert)
        {
            HashTable ht(2); 
            Assert::IsTrue(ht.insert("key1", "value1"));
            Assert::IsTrue(ht.insert("key2", "value2"));
            Assert::IsTrue(ht.insert("key1", "value1"));
        }

        TEST_METHOD(TestSearch)
        {
            HashTable ht(10);
            ht.insert("key1", "value1");
            ht.insert("key1", "value2");
            auto result = ht.search("key1");
            Assert::AreEqual(size_t(2), result.size());
            Assert::IsTrue(std::find(result.begin(), result.end(), "value1") != result.end());
        }

        TEST_METHOD(TestUpdate)
        {
            HashTable ht(10);
            ht.insert("key1", "value1");
            ht.printTable();
            Assert::IsTrue(ht.update("key1", "newValue"));
            auto result = ht.search("key1");
            Assert::AreEqual(std::string("newValue"), result[0]);
            Assert::IsFalse(ht.update("key2", "newValue2")); 
        }

        TEST_METHOD(TestRemove)
        {
            HashTable ht(10);
            ht.insert("key1", "value1");
            Assert::IsTrue(ht.remove("key1"));
            Assert::IsFalse(ht.remove("key1")); 
            auto result = ht.search("key1");
            Assert::IsTrue(result.empty());
        }
	};
}
