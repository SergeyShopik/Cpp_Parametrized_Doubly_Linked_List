#include"DualList.h"

struct Bank
{
    string accountNumber;
    size_t code;
    string lastName;
    double sum;
    string openingDate;
    double percent;
};
std::istream& operator>>(std::istream& in, const Bank& )
{

}

int main()
{
    DualList<Bank>list;
    list.pushBack(1);
    list.pushBack(2);
    list.pushBack(3);
    list.pushBack(4);
    list.pushBack(5);
    list.pushBack(6);
    //list.erase(list.begin() + 2, list.begin() + 4);

    std::cout << list.find(2);

    return 0;
}