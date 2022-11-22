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
	* cin, cin.get(), cin.getline(), getline() ����
	*
	* 1. cin
	* cin����һ���ַ����������ո񡢻س���TAB ���жϣ��磺
	*	char a[20];
	*	cin >> a;
	*
	* 2. cin.get()
	* cin.get() ����һ���ַ���Ҳ���Է�������� system("pause") ʹ�ã�����������
	* �涨�����ַ�����
	*	char c;
	*	cin.get(c);
	*	cin.get();
	*	char cs[20];
	*	cin.get(cs, 20);
	*
	* 3. cin.getline()
	* ���Զ�ȡһ���ַ������м�����пո�� TAB ��Ҳ���Թ涨�����ַ������ͽ�������Ĭ��'\0'����
	*	char cs[20];
	*	cin.getline(cs, 20);
	*/
	cout << "Enter worker's name: " << endl;
	getline(cin, fullname);
	cout << "Enter worker's ID: " << endl;
	cin >> id;
	// ��ջ�����
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
	// ʹ�� cin ��ȡ���ִ������� voice ��ͬʱ���������жϣ������� 0~7 ����
	while (cin >> voice && (voice < 0 || voice >= Vtype)) {
		cout << "Please enter a value >=0 and < " << Vtype << endl;
	}
	// ��ջ�����
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
	// ��ÿ��4���ĸ�ʽ������е� Vtype
	for (i = 0; i < Vtype; i++) {
		cout << i << ": " << pv[i] << " ";
		if (i % 4 == 3) cout << endl;
	}
	// endl �� '\n' �����У����� endl ���Ա�֤��������ˢ��
	// ����Ļ�ϣ� '\n' ���ṩ���ֱ�֤
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