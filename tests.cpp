//
// Created by Yuser on 14/09/2020.
//
#include <iostream>
#include "HashMap.hpp"
#include <cassert>
#include <vector>

#define KeyT1 std::string
#define ValueT1 int

#define INITIAL_CAPACITY 16
#define INITIAL_SIZE 0

void testDefaultConstruct()
{
    HashMap<KeyT1, ValueT1> map;

    assert(map.getSize() == INITIAL_SIZE);
    assert(map.getCapacity() == INITIAL_CAPACITY);
    assert(map.empty() == true);

    map.insert("a", 1);

    assert(map.getSize() == 1);
    assert(map.getCapacity() == INITIAL_CAPACITY);
    assert(map.empty() == false);


    std::cout << "PASS - testDefaultConstruct" << std::endl;
}



int main()
{
    std::cout << "~~~~~ Starting tests ~~~~~" << std::endl;

    testDefaultConstruct();

//
//
//    std::vector<std::string> names = {"a", "b", "c", "d", "e", "f", "g", "a", "b"};
//    std::vector<int> grades = {1, 2, 3, 4, 5, 6, 7, 100, 200};
//
//    HashMap<std::string, int> map1(names.begin(), names.end(), grades.begin(), grades.end());
//
//    map1.print();
//
//    std::cout << map1.bucket_index("a") << std::endl;
//    std::cout << map1.bucket_index("b") << std::endl;
//    std::cout << map1.bucket_index("c") << std::endl;



//    HashMap<std::string, int> map;
//
//    map.insert("tatiana", 222);
//    map.insert("hasgjkhaskdgjsdgy", 15);
//    map.insert("yairrr", 100);
//    map.insert("lobo", 50);
//    map.insert("Dor", 0);
//    map.insert("Nina", 100);
//    map.insert("eden", 60);
//    map.insert("Tol", 84);
//
////    map.print();


//    map1.at("e") = 767;


//    std::cout << map.bucket_size("Nina") << " " << map.bucket_size("Tol") << std::endl;
//
//    std::string search = "tatiana";
//
//    std::cout << "contains key? " << map.contains_key(search) << std::endl;
//
//    try
//    {
//        std::cout << "tatiana key? " << map.at(search) << std::endl;
//    }
//    catch (std::exception &e)
//    {
//        std::cout << e.what() << std::endl;
//    }

    return 0;
}
