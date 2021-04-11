#include <ftl/forward_list>
#include <iostream>

int main(int argc, char** argv)
{
    using namespace ftl;
    forward_list<int> xs { 1, 2, 3, 4, 5, 6, 7, 8 };
    xs.push_front(5);
    xs.push_front(5);
    xs.push_front(5);
    xs.push_front(5);
    xs.push_front(5);
    xs.push_front(5);
    xs.push_front(5);
    xs.push_front(5);

    for (int x : xs) std::cout << x << std::endl;
}
