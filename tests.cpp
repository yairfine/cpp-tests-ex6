//
// Created by Yair on 14/09/2020.
//

#include "HashMap.hpp"
#include "ProgressBar.hpp"
#include "InputIterator.hpp"
#include <iostream>
#include <cassert>
#include <cmath>
#include <unordered_map>
#include <vector>
#include <chrono>

#define KeyString std::string
#define KeyInt int
#define ValueInt int

#define INITIAL_CAPACITY 16
#define INITIAL_SIZE 0


#ifdef VAL

#define ITERATIONS 8
#define I_UPPER_BOUND 100
#define TOTAL_WORK 57

#else

#define ITERATIONS 17
#define I_UPPER_BOUND 1000
#define TOTAL_WORK 93

#endif


void testDefaultConstructor();
void testAt();
void testConstructor1();
void testConstructor1Capacity();
void testConstructor1Dereferencing();
void testInsert();
void testErase();
void testCapacityAndSizeResizeMap();
void testClear();
void testOperatorSubscript();
void testOperatorSubscriptConst();
void testOperatorEqualsAndNotEquals();
void testOperatorEqualsUnOrderedInteranlLists();
void testBucketSize();
void testBucketIndex();
void testContainsKey();
void testIteratorsEmpty();
void testIterators1();
void testIterators2();
void testIterators3();
void testIterators4();


ProgressBar myProgressBar(TOTAL_WORK);

int main()
{
    std::cout << "~~~~~~ Starting tests ~~~~~~" << std::endl << std::endl;
    auto start = std::chrono::steady_clock::now();


    testDefaultConstructor();
    testAt();
    testConstructor1();
    testConstructor1Capacity();
    testConstructor1Dereferencing();
    testInsert();
    testErase();
    testCapacityAndSizeResizeMap();
    testClear();
    testOperatorSubscript();
    testOperatorSubscriptConst();
    testOperatorEqualsAndNotEquals();
    testOperatorEqualsUnOrderedInteranlLists();
    testBucketSize();
    testBucketIndex();
    testContainsKey();
    testIteratorsEmpty();
    testIterators1();
    testIterators2();
    testIterators3();
    testIterators4();


    auto finish = std::chrono::steady_clock::now();
    auto elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double> >(finish - start).count();
    
    std::cout << std::endl << std::endl << "Time elapsed: " << elapsed_seconds << " seconds" << std::endl;
    std::cout << std::endl << "~~~~~~ All tests were PASSED ~~~~~~" << std::endl;

    return 0;
}

void testDefaultConstructor()
{
    HashMap<KeyString, ValueInt> map;

    assert(map.size() == INITIAL_SIZE);
    assert(map.capacity() == INITIAL_CAPACITY);
    assert(map.empty() == true);

    #ifndef VAL
    myProgressBar.addToOutputMsg("PASS - testDefaultConstructor");
    myProgressBar++;
    #endif
}

void testAt()
{
    std::vector<KeyString> keys = {"a", "b", "c", "d", "e"};
    std::vector<ValueInt> values = {1, 2, 3, 4, 5};

    HashMap<KeyString, ValueInt> map(keys.begin(), keys.end(), values.begin(), values.end());

    assert(map.at("a") == 1);
    assert(map.at("b") == 2);
    assert(map.at("c") == 3);
    assert(map.at("d") == 4);
    assert(map.at("e") == 5);

    // checking func 'at' is assinable:
    map.at("a") = 100;
    assert(map.at("a") == 100);
    assert (map.size() == 5);

    // checking non-existing key:
    try
    {
        map.at("f") = 6;
        assert(!" ~~~ function '.at' should not allow search for a non-existent key ~~~ ");
    }
    catch (const std::exception &e)
    {
    }

    try
    {
        map.at("f");
        assert(!" ~~~ function '.at' should not allow search for a non-existent key ~~~ ");
    }
    catch (const std::exception &e)
    {
    }

    assert (map.size() == 5);

    #ifndef VAL
    myProgressBar.addToOutputMsg("PASS - testAt");
    myProgressBar++;
    #endif
}

void testConstructor1()
{
    std::vector<KeyString> keys = {"a", "b", "c", "d", "e", "f", "g", "h", "i"};
    std::vector<ValueInt> values = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    HashMap<KeyString, ValueInt> map(keys.begin(), keys.end(), values.begin(), values.end());

    assert(map.size() == 9);
    assert(map.at("a") == 1);
    assert(map.at("b") == 2);
    assert(map.at("c") == 3);
    assert(map.at("d") == 4);
    assert(map.at("e") == 5);
    assert(map.at("f") == 6);
    assert(map.at("g") == 7);
    assert(map.at("h") == 8);
    assert(map.at("i") == 9);

    std::vector<KeyString> keys2 = {"a", "b", "c", "d", "e", "f", "g", "a", "b", "h", "i"};
    std::vector<ValueInt> values2 = {1, 2, 3, 4, 5, 6, 7, 100, 200, 8, 9};

    HashMap<KeyString, ValueInt> map2(keys2.begin(), keys2.end(), values2.begin(), values2.end());

    assert(map.size() == 9);
    assert(map2.at("a") == 100);
    assert(map2.at("b") == 200);
    assert(map2.at("c") == 3);
    assert(map2.at("d") == 4);
    assert(map2.at("e") == 5);
    assert(map2.at("f") == 6);
    assert(map2.at("g") == 7);
    assert(map2.at("h") == 8);
    assert(map2.at("i") == 9);

    try
    {
        auto it = keys.begin();
        it++;
        HashMap<KeyString, ValueInt> map(it, keys.end(), values.begin(), values.end());
        assert(!" ~~~ Constructor1 should throw an exception if iterators are not at the same "
                "length ~~~ ");
    }
    catch (std::exception &e)
    {
    }

    try
    {
        auto it = keys.end();
        it--;
        HashMap<KeyString, ValueInt> map(keys.begin(), it, values.begin(), values.end());
        assert(!" ~~~ Constructor1 should throw an exception if iterators are not at the same "
                "length ~~~ ");
    }
    catch (std::exception &e)
    {
    }

    try
    {
        auto it = values.begin();
        it++;
        HashMap<KeyString, ValueInt> map(keys.begin(), keys.end(), it, values.end());
        assert(!" ~~~ Constructor1 should throw an exception if iterators are not at the same "
                "length ~~~ ");
    }
    catch (std::exception &e)
    {
    }

    try
    {
        auto it = values.end();
        it--;
        HashMap<KeyString, ValueInt> map(keys.begin(), keys.end(), values.begin(), it);
        assert(!" ~~~ Constructor1 should throw an exception if iterators are not at the same "
                "length ~~~ ");
    }
    catch (std::exception &e)
    {
    }

    #ifndef VAL
    myProgressBar.addToOutputMsg("PASS - testConstructor1");
    myProgressBar++;
    #endif
}

void testConstructor1Capacity()
{
    std::vector<KeyInt> keysInt = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    std::vector<ValueInt> values = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

    HashMap<KeyInt, ValueInt> map(keysInt.cbegin(), keysInt.cend(),
                                  values.cbegin(), values.cend());

    assert(map.capacity() == 2 * INITIAL_CAPACITY);


    #ifndef VAL
    myProgressBar.addToOutputMsg("PASS - testConstructor1Capacity");
    myProgressBar++;
    #endif
}

void testConstructor1Dereferencing()
{
    std::vector<int> vector;

    for (int i = 0; i < I_UPPER_BOUND; i++)
    {
        vector.push_back(i);
    }

    InputIterator<int> inputIter(vector);

    auto keys_input_iterator_begin = inputIter.begin();
    auto keys_input_iterator_end = inputIter.end();

    auto values_input_iterator_begin = inputIter.begin();
    auto values_input_iterator_end = inputIter.end();

    try
    {
        HashMap<int, int> map(inputIter.begin(), inputIter.end(),
                              inputIter.begin(), inputIter.end());
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        assert(!"Your Ctor1 is de-referencing the input-iterator twice");
    }


    #ifndef VAL
    myProgressBar.addToOutputMsg("PASS - testConstructor1Dereferencing");
    myProgressBar++;
    #endif
}

void testInsert()
{
    HashMap<KeyString, ValueInt> map;
    
    assert(map.empty() == true);  
    assert(map.capacity() == INITIAL_CAPACITY);

    bool b = map.insert("a", 10);
    assert(b == true);
    assert(map.size() == 1);
    assert(map.empty() == false);

    b = map.insert("a", 100);
    assert(b == false);
    assert(map.size() == 1);
    assert(map.empty() == false);

    b = map.insert("a", 10);
    assert(b == false);
    assert(map.size() == 1);
    assert(map.empty() == false);

    #ifndef VAL
    myProgressBar.addToOutputMsg("PASS - testInsert");
    myProgressBar++;
    #endif
}

void testErase()
{
    std::vector<KeyInt> keysInt = {0, 1, 2, 3, 4, 5, 6, 15};
    std::vector<ValueInt> values = {0, 1, 2, 3, 4, 5, 6, 15};

    HashMap<KeyInt, ValueInt> map(keysInt.cbegin(), keysInt.cend(),
                                  values.cbegin(), values.cend());

    bool b = map.erase(0);
    assert(b == true);
    assert(map.size() == 7);

    b = map.erase(4);
    assert(b == true);
    assert(map.size() == 6);

    b = map.erase(10);
    assert(b == false);
    assert(map.size() == 6);

    #ifndef VAL
    myProgressBar.addToOutputMsg("PASS - testErase");
    myProgressBar++;
    #endif
}

void testCapacityAndSizeResizeMap()
{
    HashMap<KeyInt, ValueInt> map;

    int i = 1;

    for (int n = 0; n <= ITERATIONS; n++)
    {
        while (i <= INITIAL_CAPACITY * pow(2, n) * 0.75)
        {
            map.insert(i, i);

            assert(map.size() == i);
            assert(map.capacity() == INITIAL_CAPACITY * pow(2, n));

            i++;

        }
        #ifndef VAL
        myProgressBar++;
        #endif
    }

    i--;

    for (int n = ITERATIONS; n >= 0; n--)
    {
        while (i >= INITIAL_CAPACITY * pow(2, n) * 0.25)
        {
            assert(map.size() == i);
            assert(map.capacity() == INITIAL_CAPACITY * pow(2, n));

            map.erase(i);
            i--;
        }
        #ifndef VAL
        myProgressBar++;
        #endif
    }


    #ifndef VAL
    myProgressBar.addToOutputMsg("PASS - testCapacityAndSizeResize");
    myProgressBar++;
    #endif
}

void testClear()
{
    HashMap<KeyInt, ValueInt> map;

    // Insert elements to the Hash map

    int i = 1;

    for (int n = 0; n <= ITERATIONS; n++)
    {
        while (i <= INITIAL_CAPACITY * pow(2, n) * 0.75)
        {
            map.insert(i, i);
            i++;

        }
        #ifndef VAL
        myProgressBar ++;
        #endif
    }
    i--;

    // checking 'clear' methods

    assert(map.size() == i);
    assert(map.capacity() == INITIAL_CAPACITY * pow(2, ITERATIONS));

    map.clear();

    assert(map.size() == INITIAL_SIZE);
    assert(map.capacity() == INITIAL_CAPACITY * pow(2, ITERATIONS));

    map.insert(1, 1);

    // checking capacity resizing rules

    // after every insert, the capacity should maintain the rule: [ 0.25 * capacity <= size <= 0.75 * capacity ].
    assert(map.size() == 1);
    assert(map.capacity() == INITIAL_CAPACITY * pow(2, ITERATIONS));

    map.erase(1);

    // after every erase, the capacity should maintain the rule: [ 0.25 * capacity <= size <= 0.75 * capacity ].
    assert(map.size() == INITIAL_SIZE);
    assert(map.capacity() == INITIAL_CAPACITY);

    
    #ifndef VAL
    myProgressBar.addToOutputMsg("PASS - testClear");
    myProgressBar++;
    #endif
}

void testOperatorSubscript()
{
    std::vector<KeyString> keys = {"a", "b", "c"};
    std::vector<ValueInt> values = {1, 2, 3};

    HashMap<KeyString, ValueInt> map(keys.cbegin(), keys.cend(), values.cbegin(), values.cend());

    assert(map.size() == 3);

    try
    {

        int a = map["a"];
        assert(a == 1);
        a = 10;
        assert(map["a"] == 1);

        int b = map["b"];
        assert(b == 2);
        b = 20;
        assert(map["b"] == 2);

        int c = map["c"];
        assert(c == 3);
        c = 30;
        assert(map["c"] == 3);

        assert(map.size() == 3);

        map["a"] = 111;
        assert(map["a"] == 111);

        map["b"] = 222;
        assert(map["b"] == 222);

        map["c"] = 333;
        assert(map["c"] == 333);

        assert(map.size() == 3);

        map["d"] = 444;
        assert(map["d"] == 444);

        assert(map.size() == 4);

        map["e"];

        assert(map.size() == 5);
    }
    catch (std::exception &e)
    {
        assert(!" ~~~ Operator [] should NOT throw any exception ~~~ ");
    }


    #ifndef VAL
    myProgressBar.addToOutputMsg("PASS - testOperatorSubscript");
    myProgressBar++;
    #endif
}

void testOperatorSubscriptConst()
{
    std::vector<KeyString> keys = {"a", "b", "c"};
    std::vector<ValueInt> values = {1, 2, 3};

    const HashMap<KeyString, ValueInt> constMap(keys.cbegin(), keys.cend(),
                                                values.cbegin(), values.cend());

    assert(constMap.size() == 3);

    try
    {
        int aa = constMap["a"];
        assert(aa == 1);
        aa = 10;
        assert(constMap["a"] == 1);

        int bb = constMap["b"];
        assert(bb == 2);

        int cc = constMap["c"];
        assert(cc == 3);

        assert(constMap.size() == 3);

        constMap["d"]; // should be an undefined behavior
    }
    catch (std::exception &e)
    {
        assert(!" ~~~ Operator [] should NOT throw any exception ~~~ ");
    }


    #ifndef VAL
    myProgressBar.addToOutputMsg("PASS - testOperatorSubscriptConst");
    myProgressBar++;
    #endif
}

void testOperatorEqualsAndNotEquals()
{
    HashMap<KeyInt, ValueInt> emptyMap1;
    HashMap<KeyInt, ValueInt> emptyMap2;

    std::vector<KeyString> keysString = {"1", "2", "3"};
    std::vector<ValueInt> values = {1, 2, 3};

    HashMap<KeyString, ValueInt> mapString1(keysString.cbegin(), keysString.cend(),
                                            values.cbegin(), values.cend());
    HashMap<KeyString, ValueInt> mapString2(keysString.cbegin(), keysString.cend(),
                                            values.cbegin(), values.cend());

    assert(emptyMap1 == emptyMap2);
    assert(!(emptyMap1 != emptyMap2));

    assert(mapString1 == mapString2);
    assert(!(mapString1 != mapString2));

    mapString1["4"];

    assert(mapString1 != mapString2);
    assert(!(mapString1 == mapString2));

    mapString1["4"] = 4;
    mapString2.insert("4", 4);

    assert(mapString1 == mapString2);
    assert(!(mapString1 != mapString2));

    mapString1.clear();
    mapString2.clear();

    assert(mapString1 == mapString2);
    assert(!(mapString1 != mapString2));

    HashMap<KeyInt, ValueInt> map;

    int i = 1;
    for (int n = 0; n <= ITERATIONS; n++)
    {
        while (i <= INITIAL_CAPACITY * pow(2, n) * 0.75)
        {
            map.insert(i, i);
            i++;

        }
        #ifndef VAL
        myProgressBar++;
        #endif
    }

    map.clear();

    assert(map != emptyMap1);
    assert(!(map == emptyMap1));


    #ifndef VAL
    myProgressBar.addToOutputMsg("PASS - testOperatorEqualsAndNotEquals");
    myProgressBar++;
    #endif
}

void testOperatorEqualsUnOrderedInteranlLists()
{
    std::vector<KeyInt> keys1 = {0, 1, 2, 3, 16, 17, 18, 19, 35};
    std::vector<ValueInt> values1 = {0, 1, 2, 3,16, 17, 18, 19, 35};

    std::vector<KeyInt> keys2 = {0, 17, 18, 35, 16, 1, 2, 3, 19};
    std::vector<ValueInt> values2 = {0, 17, 18, 35, 16, 1, 2, 3, 19};

    HashMap<KeyInt, ValueInt> map1(keys1.begin(), keys1.end(),
                                   values1.begin(), values1.end());

    HashMap<KeyInt, ValueInt> map2(keys2.begin(), keys2.end(),
                                   values2.begin(), values2.end());


    assert(map1 == map2);


    #ifndef VAL
    myProgressBar.addToOutputMsg("PASS - testOperatorEqualsUnOrderedInteranlLists");
    myProgressBar++;
    #endif
}

void testBucketSize()
{
    std::vector<KeyString> keys = {"a", "b", "c", "d", "e", "f", "g", "h", "i"};
    std::vector<ValueInt> values = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    HashMap<KeyString, ValueInt> map(keys.begin(), keys.end(), values.begin(), values.end());

    try
    {
        for (auto it = keys.begin(); it != keys.end(); it++)
        {
            size_t bucketSize = map.bucket_size(*it);
            assert(bucketSize >= 0);
        }
    }
    catch(const std::exception& e)
    {
        assert(!" ~~~~ There should be NO EXCEPTION here! ~~~~ ");
    }

    try
    {
        map.bucket_size("x");
        assert(!" ~~~ function '.bucket_size' should throw an exception for a non-existent key ~~~ ");

    }
    catch(const std::exception& e)
    {
    }


    #ifndef VAL
    myProgressBar.addToOutputMsg("PASS - testBucketSize");
    myProgressBar++;
    #endif
}

void testBucketIndex()
{
    std::vector<KeyString> keys = {"a", "b", "c", "d", "e", "f", "g", "h", "i"};
    std::vector<ValueInt> values = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    HashMap<KeyString, ValueInt> map(keys.begin(), keys.end(), values.begin(), values.end());

    try
    {
        for (auto it = keys.begin(); it != keys.end(); it++)
        {
            size_t bucketIndex = map.bucket_index(*it);
            assert((bucketIndex >= 0) && (bucketIndex <= map.capacity() - 1));
        }
    }
    catch(const std::exception& e)
    {
        assert(!" ~~~~ There should be NO EXCEPTION here! ~~~~ ");
    }

    try
    {
        map.bucket_index("x");
        assert(!" ~~~ function '.bucket_index' should throw an exception for a non-existent key ~~~ ");

    }
    catch(const std::exception& e)
    {
    }


    #ifndef VAL
    myProgressBar.addToOutputMsg("PASS - testBucketIndex");
    myProgressBar++;
    #endif
}

void testContainsKey()
{
    std::vector<KeyString> keys = {"a", "b", "c", "d", "e", "f", "g", "h", "i"};
    std::vector<ValueInt> values = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    HashMap<KeyString, ValueInt> map(keys.begin(), keys.end(), values.begin(), values.end());

    for (auto it = keys.begin(); it != keys.end(); it++)
    {
        assert(map.contains_key(*it));
    }

    assert(!map.contains_key("x"));


    #ifndef VAL
    myProgressBar.addToOutputMsg("PASS - testContainsKey");
    myProgressBar++;
    #endif
}

void testIteratorsEmpty()
{
    // this unordered_map part is only for demonstrating..
    std::unordered_map<KeyString, ValueInt> emptyStdMap;

    auto beginStdMap = emptyStdMap.begin();
    auto endStdMap = emptyStdMap.end();

    assert(beginStdMap == beginStdMap);
    assert(endStdMap == endStdMap);
    assert(beginStdMap == endStdMap);

    for (const auto &j : emptyStdMap)
    {
        assert(!" ~~~ In empty unordered_map there should not be any iterations here ~~~ ");
    }

    // this is the real test here:
    HashMap<KeyString, ValueInt> emptyMap;

    auto iterBegin = emptyMap.begin();
    auto iterEnd = emptyMap.end();

    assert(iterBegin == iterBegin);
    assert(iterEnd == iterEnd);
    assert(iterBegin == iterEnd);

    for (const auto &i : emptyMap)
    {
        assert(!" ~~~ In empty HashMap there should not be any iterations here ~~~ ");
    }


    #ifndef VAL
    myProgressBar.addToOutputMsg("PASS = testIteratorsEmprty");
    myProgressBar++;
    #endif
}

void testIterators1()
{
    std::vector<KeyInt> keysInt = {0, 1, 2, 3, 4, 5, 6, 15};
    std::vector<ValueInt> values = {0, 1, 2, 3, 4, 5, 6, 15};

    HashMap<KeyInt, ValueInt> map(keysInt.cbegin(), keysInt.cend(),
                                  values.cbegin(), values.cend());

    std::vector<int>::const_iterator vecIter = values.begin();

    for (auto it = map.begin(); it != map.end(); it++)
    {
        assert(it->first == *vecIter && it->second == *vecIter);
        assert(it->first == (*it).first && it->second == (*it).second);

        vecIter++;
    }

    vecIter = values.begin();

    for (auto it = map.cbegin(); it != map.cend(); it++)
    {
        assert(it->first == *vecIter && it->second == *vecIter);
        assert(it->first == (*it).first && it->second == (*it).second);

        vecIter++;
    }


    #ifndef VAL
    myProgressBar.addToOutputMsg("PASS = testIterators1");
    myProgressBar++;
    #endif
}

void testIterators2()
{

    std::vector<KeyInt> keysInt = {3, 4, 5, 6, 15};
    std::vector<ValueInt> values = {3, 4, 5, 6, 15};

    HashMap<KeyInt, ValueInt> map(keysInt.cbegin(), keysInt.cend(),
                                  values.cbegin(), values.cend());

    const HashMap<KeyInt, ValueInt> constMap(keysInt.cbegin(), keysInt.cend(),
                                             values.cbegin(), values.cend());

    std::vector<int>::const_iterator vecIter = values.begin();

    for (auto it = map.begin(); it != map.end(); it++)
    {
        assert(it->first == *vecIter && it->second == *vecIter);
        assert(it->first == (*it).first && it->second == (*it).second);

        vecIter++;
    }

    vecIter = values.begin();

    for (auto it = map.cbegin(); it != map.cend(); it++)
    {
        assert(it->first == *vecIter && it->second == *vecIter);
        assert(it->first == (*it).first && it->second == (*it).second);

        vecIter++;
    }

    vecIter = values.begin();

    for (auto it = constMap.begin(); it != constMap.end(); it++)
    {
        assert(it->first == *vecIter && it->second == *vecIter);
        assert(it->first == (*it).first && it->second == (*it).second);

        vecIter++;
    }

    vecIter = values.begin();

    for (auto it = constMap.cbegin(); it != constMap.cend(); it++)
    {
        assert(it->first == *vecIter && it->second == *vecIter);
        assert(it->first == (*it).first && it->second == (*it).second);

        vecIter++;
    }


    #ifndef VAL
    myProgressBar.addToOutputMsg("PASS = testIterators2");
    myProgressBar++;
    #endif
}

void testIterators3()
{

    std::vector<KeyInt> keysInt = {1, 4, 5, 6, 9, 14};
    std::vector<ValueInt> values = {1, 4, 5, 6, 9, 14};

    HashMap<KeyInt, ValueInt> map(keysInt.cbegin(), keysInt.cend(),
                                  values.cbegin(), values.cend());

    std::vector<int>::const_iterator vecIter = values.begin();

    for (auto it = map.begin(); it != map.end(); it++)
    {
        assert(it->first == *vecIter && it->second == *vecIter);
        assert(it->first == (*it).first && it->second == (*it).second);

        vecIter++;
    }


    #ifndef VAL
    myProgressBar.addToOutputMsg("PASS = testIterators3");
    myProgressBar++;
    #endif
}

void testIterators4()
{

    std::vector<KeyInt> keysInt = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    std::vector<ValueInt> values = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

    HashMap<KeyInt, ValueInt> map(keysInt.cbegin(), keysInt.cend(),
                                  values.cbegin(), values.cend());

    std::vector<int>::const_iterator vecIter = values.begin();

    for (auto it = map.begin(); it != map.end(); it++)
    {
        assert(it->first == *vecIter && it->second == *vecIter);
        assert(it->first == (*it).first && it->second == (*it).second);

        vecIter++;
    }
    

    #ifndef VAL
    myProgressBar.addToOutputMsg("PASS = testIterators4                            \n");
    myProgressBar++;
    #endif
}