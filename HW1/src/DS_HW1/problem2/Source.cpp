#include<iostream>
#include<cstdlib>
#include<cmath>
using namespace std;
void P(string S, int m, int n, int i)
{
	if (i == 0)//�P�_i�O�_����0
	{
		cout << "{ }" << endl;//��X{ }
		i += 1;//++
		P(S, m, n, i);//�i�J�禡
	}
	else
	{
		cout << "{�@";//��X{ 
		for (int j = 0; j < n; j++)//�i�Jfor�j��
		{
			if (i & (1 << j))//�H�G�i��P�_�O�_���l���X
				cout << S[j] << " ";//��X�ƭ�
		}
		cout << "}" << endl;//��X}
		i += 1;//i++
		if (i != m)//�P�_�O�_�I�s�禡
			P(S, m, n, i);
		else//�禡����
			cout << "end" << endl;
	}
}
int main(void) {
	string S;//�]�w�ܼ�
	cin >> S;//��J�r��
	int n = S.length(), m = pow(2, n), i = 0;//�]�w�ܼ�n�Mm�An���r����סAm���l���X���ƥ�
	cout << "m(�l���X���ƥ�)=" << m << endl << "n(�r�����)=" << n << endl;//��Jm�Mn�ƭ�
	P(S, m, n, i);//�i�J�禡
	system("pause");
	return 0;
}