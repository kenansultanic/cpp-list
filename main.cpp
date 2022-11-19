#include <iostream>
#include "list.h"

int main()
{
    List<int> list_1;
    list_1.push_back(0);
    list_1.push_back(1);
    list_1.push_back(3);
    list_1.push_front(10);
    list_1 += List<int>{7, 8, 9, 10};

    List<int> list_2{1, 2, 3, 4, 5, 42, 101};
    List<int> list_3(list_1.begin(), --list_1.end());

    list_3 += list_2;
    list_3.insert(++list_3.begin(), std::move(list_2));
    list_3.rotate(3);
    list_3.remove(42);
    list_3.remove_if([](int element) { return element > 100; });

    List<int>::swap(list_1, list_3);

    list_1.sort();
    list_1.unique();

    for (auto it = list_1.begin(); it != list_1.end(); it++)
        std::cout << *it << " ";
    std::cout << std::endl;

    for (auto it = list_1.rbegin(); it != list_1.rend(); it++)
        std::cout << *it << " ";
    std::cout << std::endl;

    return 0;
}
