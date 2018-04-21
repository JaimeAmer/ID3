#ifndef NODO_H_
#define NODO_H_

#include <cmath>
#include <utility>
#include <unordered_map>
#include <string>

using namespace std;

class Nodo {
public:
	Nodo(int p, int n) : _p(p), _n(n), _a(p + n) {}
	Nodo() : _p(0), _n(0), _a(0) {}

	class Comparador {
	public:
		bool operator()(pair<string, unordered_map<string, Nodo> > &a, pair<string, unordered_map<string, Nodo> > &b) const {
			return calcularMerito(a.second) < calcularMerito(b.second);
		}
	private:
		float calcularMerito(unordered_map<string, Nodo> &key) const {
			float merito = 0.0f;
			int N = 0;
			for (unordered_map<string, Nodo>::const_iterator values = key.cbegin(); values != key.cend(); values++) N += values->second.a();
			for (unordered_map<string, Nodo>::const_iterator values = key.cbegin(); values != key.cend(); values++) {
				merito += values->second.a()/N * values->second.infor();
			}
			return merito;
		}
	};

	float infor() const {
		return (float) -_p * log2f(_p) - _n * log2f(_n);
	}
	void sumP() {
		_p++;
		_a++;
	}
	void sumN() {
		_n++;
		_a++;
	}
	//float r() const { return (float)(_a / _n) * 1.0f; }
	int a() const { return _a; }
	int p() const { return _p; }
	int n() const { return _n; }

private:
	int _p;
	int _n;
	int _a;
};

#endif // !NODO_H_

