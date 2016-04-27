#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const long long N_MAX = 1000010;
typedef pair<int, int> pii;

long long gcd(long long a, long long b) {
    if (b > a) {
	return gcd(b, a);
    } else if (b == 0) {
	return a;
    } else {
	return gcd(b, a % b);
    }
}

class Fraction {
public:
    long long n;
    long long d;

    Fraction(long long a, long long b) {
	if (a == 0) {
	    n = 0;
	    d = 1;
	    return;
	}

	if (b == 0) {
	    n = 0;
	    d = 0;
	    return;
	}
   
	// getting rid of a negative denom
	if (b < 0) {
	    a = -a;
	    b = -b;
	}

	long long x = gcd(abs(a), abs(b));
	n = a / x;
	d = b / x;
    }

    Fraction(long long a) {
	n = a;
	d = 1;
    }

    bool operator==(const Fraction & other) const {
	return n == other.n && other.d;
    }

    bool operator>=(const Fraction & other) const {
	return n * other.d >= other.n * d;
    }

    bool operator>(const Fraction & other) const {
	return n * other.d > other.n * d;
    }

    bool operator<(const Fraction & other) const {
	return n * other.d < other.n * d;
    }

    bool operator<=(const Fraction & other) const {
	return n * other.d <= other.n * d;
    }


    bool operator <(const long long x) const {
	return *this < Fraction(x, 1);
    }

    bool operator <=(const long long x) const {
	return *this <= Fraction(x, 1);
    }

    bool operator>(const long long x) const {
	return *this > Fraction(x, 1);
    }

    bool operator>=(const long long x) const {
	return *this >= Fraction(x, 1);
    }

    Fraction operator+(const Fraction & other) const {
	return Fraction(
	    n * other.d + other.n * d,
	    d * other.d
	);
    }
};

Fraction x_intercept(const pii & l1, const pii & l2) {
    return Fraction(l2.second - l1.second, l1.first - l2.first);
}

// assumes a < b
bool diff_over_integer(const Fraction & a, const Fraction & b) {
    long long x = a.n / a.d;
    long long y = b.n / b.d;

    return x < y;
}

long long N;
pii all[N_MAX];
vector<int> candidate;
vector<int> good;
vector<int> bad;
// first is grad, second is y intercept
// the soln is to sort the lines according to slope, smallest slope to biggest slope. Then insert the first line and second line. From the third line onwards, check the x-interception of the new line with the second last line and the last line with the second last line. If the formal being the smaller, then the second last line is irrelevant, we remove it

int main() {
    cin >> N;
    for (long long i = 0 ; i < N ; i++) {
	long long a ,b;
	cin >> a >> b;
	all[i].first = b;
	all[i].second = -a * b;
    }

    sort(all, all + N);

    for (long long i = 1 ; i < N  ; i++) {
	if (all[i].first == all[i-1].first) {
	    bad.push_back(i - 1);
	} else {
	    candidate.push_back(i - 1);
	}
    }
    candidate.push_back(N - 1);

    if (candidate.size() == 1) {
	cout << 1 << "\n";
	return 0;
    }

    for (long long i = 0 ; i < candidate.size() ; ) {
	if (good.size() <= 1) {
	    good.push_back(candidate[i]); 
	    i++;
	    // cout << "______________________" << endl << endl;
	    continue;
	}

	Fraction x = x_intercept(all[good[good.size() - 2]], all[candidate[i]]); // new and second last
	Fraction y = x_intercept(all[good[good.size() - 2]], all[good[good.size() - 1]]);  // last and second last

	if (x <= y) {
	    good.pop_back();
	} else {
	    good.push_back(candidate[i]);
	    i++;
	}
    }

    long long ans_inverse = 0;

    {
	Fraction a = x_intercept(all[good[0]], all[good[1]]);
	Fraction b = x_intercept(all[good[0]], make_pair(0, 0));
	Fraction c = max(a, b);

	if (c >= Fraction(b.n, b.d) + Fraction(1)) {
	    ans_inverse += 1;
	}
    }

    for (long long i = 1 ; i < good.size() - 1; i++) {

	Fraction a = x_intercept(all[good[i-1]], all[good[i]]);
	Fraction b = x_intercept(all[good[i+1]], all[good[i]]);
	Fraction c = x_intercept(all[good[i]], make_pair(0, 0));

	if (diff_over_integer(max(a, c), max(b, c))) {
	    ans_inverse += 1;
	}
    }

    // the last line is guranteed to be good
    ans_inverse += 1;
    cout << N - ans_inverse << endl;

    return 0;
}
