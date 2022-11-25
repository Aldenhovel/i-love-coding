#include <iostream>
#include <string>

using namespace std;

template<class K, class V>
class Pair {
private:
	K key;
	V value;
public:
	Pair(const K &key, const V &value) : key(key), value(value) {};
	Pair() {};
	K& Key();
	V& Value();
	K Key() const { return key; }
	V Value() const { return value; }
};

template<class K, class V>
K& Pair<K, V>::Key() {
	return key;
}

template<class K, class V>
V& Pair<K, V>::Value() {
	return value;
}

int main() {
	Pair<string, int> ratings[] = {
		Pair<string, int>("aa", 2),
		Pair<string, int>("bb", 6),
		Pair<string, int>("cc", 12)
	};
	for (auto item : ratings) {
		cout << "Key: " << item.Key << " Value: " << item.Value << endl;
	}
	return 0;
}