#include <iostream>

int main(){

    int n = -1;
    char ch = 'a';
    double dle = 0.1;

    // ʹ�� C ������ʽת��
    dle = n;

    // C++ ��ʹ�� static_cast<> �������ʽת��
    // �����Ѻá���ִ������ʱ���
    dle = static_cast<double>(n);
    n = static_cast<int>(ch);

    std::cout << dle << std::endl; //-1
    std::cout << n << std::endl;  //97
    return 0;
}

