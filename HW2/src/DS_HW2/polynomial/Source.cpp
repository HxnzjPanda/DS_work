#include<iostream> 
#define debug false 
using namespace std;

double START, END;

void runTime(bool start = false) {
	if (debug) {
		if (start) {
			START = clock();
		}
		else {
			END = clock();
			//cout << endl << "�{������Ҫ�O�G" << (double)clock() / CLOCKS_PER_SEC << " S";
			cout << endl << "�i��B��Ҫ�O���ɶ��G" << (double)(END - START) <<" mS" << endl;
		}
	}
}

class Term {
	friend class Polynomial;
	friend ostream& operator<<(ostream& os, Polynomial& poly); //friend��X�h���� ���M�|�L�k�s���Y�ƻP����

private:
	float coef;	// �Y��
	int exp;	// ���� 
};

class Polynomial {
public:
	friend ostream& operator<<(ostream& os, Polynomial& poly);
	friend Polynomial operator>>(istream & is, Polynomial & poly);

	Polynomial() {
		termArray = new Term[10];
		capacity = 10;
		terms = 0;
	};

	Polynomial Add(Polynomial poly) { //�h�����ۥ[ 
		Polynomial tempPoly;
		int aPos = 0, bPos = 0;
		while ((aPos < terms) && (bPos < poly.terms)) {
			if (termArray[aPos].exp == poly.termArray[bPos].exp) { //���ƬۦP�]�ۥ[
				float t = termArray[aPos].coef + poly.termArray[bPos].coef;//�Y�Ƭۥ[ 
				if (t) tempPoly.NewTerm(t, termArray[aPos].exp); //�Y�Ƥ���0�~�s�W����
				aPos++;
				bPos++;
			}
			else  if (termArray[aPos].exp < poly.termArray[bPos].exp) {
				tempPoly.NewTerm(poly.termArray[bPos].coef, poly.termArray[bPos].exp);
				bPos++;
			}
			else {
				tempPoly.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
				aPos++;
			}
		}

		for (; aPos < terms; aPos++) {
			tempPoly.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
		}
		for (; bPos < poly.terms; bPos++) {
			tempPoly.NewTerm(poly.termArray[bPos].coef, poly.termArray[bPos].exp);
		}
		return tempPoly;
	};

	Polynomial Mult(Polynomial poly) {
		Polynomial tempPoly;
		if (terms == 0 || poly.terms == 0) return tempPoly; //�Y��0�h�^�ǪŦh����
		tempPoly.capacity = terms * poly.terms;    //�p��һݪŶ�
		tempPoly.termArray = new Term[tempPoly.capacity]; //�t�m�Ŷ� 
		for (int i = 0; i < terms; i++) {
			for (int j = 0; j < poly.terms; j++) {
				int c = termArray[i].coef * poly.termArray[j].coef; //�Y�Ƭۭ� 
				int e = termArray[i].exp + poly.termArray[j].exp; //���Ƭۥ[ 
				tempPoly.NewTerm(c, e);
			}
		}
		return tempPoly;
	};

	float Eval(float f) { //�a�Jf�p��h�������� 
		float result = 0;
		for (int i = 0; i < terms; i++) {
			float temp = 1;
			for (int j = 0; j < termArray[i].exp; j++) {
				temp *= termArray[i].coef;
			}
			result += temp * f;
		}
		return result;
	};

	void NewTerm(float coef, int exp) { //�s�W����
		if (terms == capacity) {
			capacity *= 2; //�X�R2�����Ŷ� 
			Term* temp = new Term[capacity];
			copy(termArray, termArray + terms, temp);
			delete[] termArray;
			termArray = temp;
		}
		termArray[terms].coef = coef;
		termArray[terms++].exp = exp;
	};

private:
	Term* termArray;
	int capacity; // ���h�֪Ŷ� 
	int terms;  // �D�s�� 
};

Polynomial operator>>(istream& is, Polynomial& poly) {
	float coef;
	int exp;
	is >> coef >> exp; //�̧ǿ�J�Y�ƻP���� 
	while (coef != 0 || exp != 0) {
		poly.NewTerm(coef, exp); //�s�W���� 
		is >> coef >> exp;
	}
	return poly;
}

ostream& operator<<(ostream& os, Polynomial& poly) {
	for (int i = 0; i < poly.terms; i++) {
		if (poly.termArray[i].coef > 0) { //�P�_���t�� 
			if (i != 0) os << "+";
		}
		else {
			os << "-";
		}

		if (poly.termArray[i].exp == 0) { //�P�_���ƿ�X�r��
			os << poly.termArray[i].coef;
		}
		else if (poly.termArray[i].exp == 1) {
			os << poly.termArray[i].coef << "x";
		}
		else {
			os << poly.termArray[i].coef << "x^" << poly.termArray[i].exp;
		}
	}
	return os;
}

int main() {
	class Polynomial poly1, poly2, poly3;
	float f; //�p��� 
	int coef, exp; //��J�����ƻP�Y�� 

	cout << "�п�J�Y�ƩM���ơA��J0 0�����G\n";
	cin >> coef >> exp;
	while (coef != 0 || exp != 0) {
		poly1.NewTerm(coef, exp);
		cin >> coef >> exp;
	}
	runTime(true);
	cout << poly1 << endl << endl;
	runTime();

	cout << "�п�J�@�ӼƦr(��J0���L)�G\n";
	cin >> f;
	runTime(true);
	if (f != 0)
		cout << "poly1(" << f << ") = " << poly1.Eval(f) << endl;
	runTime();
	cout << endl;



	cout << "�п�J�Y�ƩM���ơA��J0 0�����G\n";
	cin >> coef >> exp;
	while (coef != 0 || exp != 0) {
		poly2.NewTerm(coef, exp);
		cin >> coef >> exp;
	}
	runTime(true);
	cout << poly2 << endl << endl;
	runTime();

	cout << "�п�J�@�ӼƦr(��J0���L)�G\n";
	cin >> f;
	runTime(true);
	if (f != 0)
		cout << "poly2(" << f << ") = " << poly2.Eval(f) << endl;
	runTime();
	cout << endl;

	cout << "poly1 + poly2 = ";
	runTime(true);
	poly3 = poly1.Add(poly2);
	cout << poly3 << endl;
	runTime();

	cout << "poly1 * poly2 = ";
	runTime(true);
	poly3 = poly1.Mult(poly2);
	cout << poly3 << endl;
	runTime();

	return 0;
}