#include "worker.h"

using namespace std;

Worker::~Worker() {};

void Worker::Data() const {
	cout << "Name: " << fullname << endl;
	cout << "Employee ID: " << id << endl;
}

void Worker::Get() {
	getline(cin, fullname);
	cout << "Enter worker's ID: ";
	cin >> id;
	while (cin.get() != '\n') continue;
}

void Worker::Set() {
	/*
	* cin, cin.get(), cin.getline(), getline() 介绍
	*
	* 1. cin
	* cin接收一个字符串，遇到空格、回车、TAB 都中断，如：
	*	char a[20];
	*	cin >> a;
	*
	* 2. cin.get()
	* cin.get() 读入一个字符，也可以放在最后当作 system("pause") 使用，带参数可用
	* 规定输入字符数：
	*	char c;
	*	cin.get(c);
	*	cin.get();
	*	char cs[20];
	*	cin.get(cs, 20);
	*
	* 3. cin.getline()
	* 可以读取一个字符串，中间可以有空格或 TAB ，也可以规定输入字符数量和结束符（默认'\0'）：
	*	char cs[20];
	*	cin.getline(cs, 20);
	*/
	cout << "Enter worker's name: " << endl;
	getline(cin, fullname);
	cout << "Enter worker's ID: " << endl;
	cin >> id;
	// 清空缓存区
	while (cin.get() != '\n') continue;
}

void Worker::Show() const {
	cout << "Name: " << fullname << endl;
	cout << "ID: " << id << endl;
}

void Waiter::Set() {
	Worker::Set();
	cout << "Enter waiter's panache rating: " << endl;
	cin >> panache;
	while (cin.get() != '\n') continue;
}

void Waiter::Show() const {
	cout << "Category: waiter" << endl;
	Worker::Show();
	cout << "Panache rating: " << panache << endl;
}

void Waiter::Data() const{
	cout << "Panache rating: " << panache << endl;
}

void Waiter::Get() {
	cout << "Enter waiter's panache rating: ";
	cin >> panache;
	while (cin.get() != '\n') continue;
}

char *Singer::pv[] = { "other", "alto", "contralto", "soprano", "bass", "baritone", "tenor" };

void Singer::Set() {
	cout << "Enter number for singer's vocal range: " << endl;
	int i;
	for (i = 0; i < Vtype; i++) {
		cout << i << ": " << pv[i] << " ";
		if (i % 4 == 3) cout << endl;
	}
	if (i % 4 != 0) cout << endl;
	// 使用 cin 读取数字传给变量 voice 的同时对数字做判断，让它在 0~7 以内
	while (cin >> voice && (voice < 0 || voice >= Vtype)) {
		cout << "Please enter a value >=0 and < " << Vtype << endl;
	}
	// 清空缓存区
	while (cin.get() != '\n') continue;
}

void Singer::Show() const {
	cout << "Category: singer" << endl;
	Worker::Show();
	cout << "Vocal range: " << pv[voice] << endl;
}

void Singer::Data() const {
	cout << "Vocal range: " << pv[voice] << endl;
}

void Singer::Get() {
	cout << "Enter number for singer's vocal range:\n";
	int i;
	// 以每行4个的格式输出所有的 Vtype
	for (i = 0; i < Vtype; i++) {
		cout << i << ": " << pv[i] << " ";
		if (i % 4 == 3) cout << endl;
	}
	// endl 和 '\n' 都表换行，但是 endl 可以保证换行立刻刷新
	// 在屏幕上， '\n' 不提供这种保证
	if (i % 4 != 3) cout << '\n';
	while (cin.get() != '\n') continue;
}

void SingingWaiter::Data() const {
	Waiter::Data();
	Singer::Data();
}

void SingingWaiter::Get() {
	Waiter::Get();
	Singer::Get();
}

void SingingWaiter::Set() {
	cout << "Enter singing waiter's name: ";
	Worker::Get();
	Get();
}

void SingingWaiter::Show() const{
	cout << "Category: Singing Waiter\n";
	Worker::Data();
	Data();
}

int main() {
	Singer s = Singer("Tom", 12);
	s.Set();
	s.Show();

	SingingWaiter s1 = SingingWaiter(s, 1);
	s1.Show();
}