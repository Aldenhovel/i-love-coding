#include <iostream>
#include <exception>

using namespace std;

// 比较基础的 exception ，习惯上会使用 const char* what() 来存储提示信息
// public 继承 exception 类，需要先在 #include 中导入 <exception>
class Ex1 : public exception {
public:
    const char* what() {
        return "This is a normal Exception!";
    }
};

// 带有内部成员，变量或函数
class Ex2 : public exception {
public:
    const char* what() {
        return "This is a Exception.";
    }

    void info() {
        cout << "This is Exception info.";
    }
};

// 可以接受参数来初始化的 exception
class ExWithMsg : public exception {
private:
    const char* msg;
public:
    ExWithMsg(const char* msg) : msg(msg) {};
    const char* what() {
        return msg;
    }
};

int main() {
    
    for (int i = 0; i < 5; i++) {
        try {
            // 尝试抛出各个异常
            if (i == 0) throw "This is a const char* Exception!";
            if (i == 1) throw Ex1();
            if (i == 2) throw Ex2();
            if (i == 3) throw ExWithMsg("This is Expection!");
            if (i == 4) throw 1;
        }
        catch (const char* e) {
            cout << e << endl;
        }
        catch (Ex1& e) {
            cout << e.what() << endl;
        }
        catch (Ex2& e) {
            cout << e.what() << endl;;
            e.info();
        }
        catch (ExWithMsg& e) {
            cout << e.what() << endl;
        }
        catch (...) {
            cout << "Unknown Exception.";
        }
    }
}