#include "TennisPlayer.h"

using namespace Demos;

// TennisPlayer ��̬���� intro ������
string TennisPlayer::intro = "This is a competetive sport.";

// TennisPlater ���캯��
TennisPlayer::TennisPlayer(const string fn, const string ln, bool ht)
	: firstName(fn), lastName(ln), hasTable(ht) {};

string TennisPlayer::Name() const {
	return firstName + " " + lastName;
}

bool TennisPlayer::HasTable() const { return hasTable; }

void TennisPlayer::ResetTable(bool ht) { hasTable = ht; }

TennisPlayer::~TennisPlayer() {};

void TennisPlayer::Grettings() { cout << "Welcone P." << endl; }

void TennisPlayer::Intro() { cout << intro << endl; }

// �������� operator ������֮�ⶨ��ģ���Ҫָ������ std ���� Demos �����������
// �����Ҫд Demos::operator ��������� std::operator ��������
ostream& Demos::operator<<(ostream& os, TennisPlayer &tp) {
	return os << tp.Name() << " "  << endl;
}



// ������ RatedPlayer �����
RatedPlayer::RatedPlayer(const string fn, const string ln, bool ht, int r)
	: TennisPlayer(fn, ln, ht) {
	rating = r;
}

RatedPlayer::RatedPlayer(TennisPlayer &tp, int r)
	: TennisPlayer(tp), rating(r) {};

int RatedPlayer::Rating() const { return rating; }

void RatedPlayer::resetRating(int r) { rating = r; }

RatedPlayer::~RatedPlayer() {};

void RatedPlayer::Greetings() { cout << "Welcome R.P." << endl; }

ostream& Demos::operator<<(ostream& os, RatedPlayer &rp) {
	return os << rp.Name() << " " << endl;
}


int main() {
	TennisPlayer tp = TennisPlayer("Tomds", "casc", true);
	RatedPlayer rp = RatedPlayer("Jasiv", "wvsaa", false);

	TennisPlayer::Intro();

	cout << tp << rp << endl;
}