#pragma once
#include <iostream>
#include <string>

using namespace std;
namespace Demos {
	
	// ����
	class TennisPlayer {
	private:
		// ��̬����
		static string intro;

		// һ�����
		string firstName;
		string lastName;
		bool hasTable;
	public:

		// ���캯��
		TennisPlayer(const string fn = "none", const string ln = "none", bool ht = false);
		
		// ��ͨ����
		string Name() const;
		bool HasTable() const;
		void ResetTable(bool ht);

		// �麯��
		virtual ~TennisPlayer();
		virtual void Grettings();

		// ��̬����
		static void Intro();

		// ��Ԫ���������
		friend ostream& operator<<(ostream& os, TennisPlayer &tp);
	};

	// public �̳� TennisPalyer �� RatedPlater ��
	class RatedPlayer : public TennisPlayer {
	private:
		int rating;
	public:
		// ���캯�������ƹ��캯��
		RatedPlayer(const string fn = "none", const string ln = "none", bool ht = false, int r = 0);
		RatedPlayer(TennisPlayer &tp, int r);
		
		// ��ͨ����
		int Rating() const;
		void resetRating(int r);

		// �麯��
		// �麯������ʵ������������أ���������麯���������ָ������õĺ���
		// ���ʹ���麯������ʼ�յ���ָ����౾��ķ������磺
		// A a = A()
		// B:A *b = &a
		// b->fn is B::fn if fn is not virtual, because b is a B point
		// b->fn is A::fn if fn is virtual, because b point to class A
		virtual ~RatedPlayer();
		virtual void Greetings();

		// ��Ԫ
		friend ostream& operator<<(ostream& os, RatedPlayer &tp);

	};
}