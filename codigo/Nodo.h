#ifndef NODO_H_
#define NODO_H_

#include <cmath>

using namespace std;

class Nodo {
public:
	Nodo(int p, int n) : _p(p), _n(n) {}
	Nodo() : _p(0), _n(0) {}

	float infor() const {
		float p = (_p*1.0f) / a();
		float n = (_n*1.0f) / a();
		return -p * log2f(p) -n * log2f(n);
	}
	void sumP() {
		_p++;
	}
	void sumN() {
		_n++;
	}

	int a() const { return _p+_n; }
	int p() const { return _p; }
	int n() const { return _n; }

private:
	int _p;
	int _n;
};

#endif // !NODO_H_

