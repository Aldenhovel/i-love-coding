#include <iostream>
#include <exception>

using namespace std;

// �Ƚϻ����� exception ��ϰ���ϻ�ʹ�� const char* what() ���洢��ʾ��Ϣ
// public �̳� exception �࣬��Ҫ���� #include �е��� <exception>
class Ex1 : public exception {
public:
    const char* what() {
        return "This is a normal Exception!";
    }
};

// �����ڲ���Ա����������
class Ex2 : public exception {
public:
    const char* what() {
        return "This is a Exception.";
    }

    void info() {
        cout << "This is Exception info.";
    }
};

// ���Խ��ܲ�������ʼ���� exception
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
            // �����׳������쳣
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