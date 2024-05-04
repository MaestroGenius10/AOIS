#include "pch.h"
#include "CppUnitTest.h"
#include "..\\associativeMemory\Matrix.h"
#include <numeric>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace associativeMemoryTest
{
	TEST_CLASS(associativeMemoryTest)
	{
	public:
        TEST_METHOD(TestSetAndGet)
        {
            Matrix m;
            m.set(1, 1, 5);
            Assert::AreEqual(5, m.get(1, 1));
        }
        TEST_METHOD(TestGetWord)
        {
            Matrix m;
            m.set(0, 0, 1);
            m.set(1, 0, 0);
            m.set(2, 0, 1);
            std::string expected = "1010000000000000";
            Assert::AreEqual(expected, m.getWord(0));   
        }
  
        TEST_METHOD(TestGetAddressRow)
        {
            Matrix m;
            m.set(0, 0, 1);
            m.set(1, 0, 0);
            m.set(2, 0, 1);
            std::string expected = "1000000000000000";
            Assert::AreEqual(expected, m.getAddressRow(0));
        }
        TEST_METHOD(TestSetColummWord)
        {
            Matrix m;
            std::string expected = "1010101010101010";
            m.setColumnWord(expected, 0);
            Assert::AreEqual(expected, m.getWord(0));
        }
        TEST_METHOD(TestConstZero)
        {
            Matrix m;
            std::string expected = "0000000000000000";
            std::string result = m.constZero(expected);
            Assert::AreEqual(expected, result);
        }
        TEST_METHOD(TestConstOne)
        {
            Matrix m;
            m.setWordsInColumns({ "0000000000000000" });
            std::string expected = "1111111111111111";
            std::string result = m.constOne(expected);            
            Assert::AreEqual(expected, result);
        }
       
        TEST_METHOD(TestRepeatAndNegSecond)
        {
            Matrix m;
            std::string test = "1010101010101010";
            std::string expected = "0101010101010101";
            std::string result = m.repeatAndNegSecond(expected, test);
            Assert::AreEqual(expected, result);
        }
        TEST_METHOD(TestFindWordsByPrefix)
        {
            Matrix m;
            m.set(3, 1, 1);
            m.set(4, 1, 0);
            m.set(5, 1, 0);
            m.set(6, 1, 1);
            m.set(7, 1, 1);
            m.set(8, 1, 0);
            m.set(9, 1, 1);
            m.set(10, 1, 0);
            m.printMatrix();
            std::vector<std::string> resulting = m.findMaxClose("0101010101010111");
            std::vector<std::string> foundWords = m.findWordsByPrefix("001");
            std::string expected =  "0010011010000000";
            std::string result;   
            result = std::accumulate(foundWords.begin(), foundWords.end(), std::string());
            Assert::AreEqual(expected, result);
        } 
        TEST_METHOD(TestProcessWords)
        {
            Matrix m;
            m.set(3, 1, 1);
            m.set(4, 1, 0);
            m.set(5, 1, 0);
            m.set(6, 1, 1);
            m.set(7, 1, 1);
            m.set(8, 1, 0);
            m.set(9, 1, 1);
            m.set(10, 1, 0);
            m.printMatrix();
            std::vector<std::string> foundWords = m.findWordsByPrefix("001");
            std::vector<std::string> results = m.processWords(foundWords);
            m.printWord(0);
            m.printAddressRow(0);
            std::string expected = "0010011010000111";
            std::string result;
            result = std::accumulate(results.begin(), results.end(), std::string());
            Assert::AreEqual(expected, result);
        }
    };
}
