class bignum
{
public:
	bignum(void);

	__declspec(dllexport) bignum(int length, int dotpos, int sign);

	//void copy(bignum *source);

	__declspec(dllexport) void setnum(long long num, int pos);

	__declspec(dllexport) void setsign(int sign);

	__declspec(dllexport) void changelength();

	__declspec(dllexport) int getlength();

	__declspec(dllexport) int getdotpos();

	__declspec(dllexport) int getsign();

	__declspec(dllexport) long long getnumber(int i);

	__declspec(dllexport) void multi(bignum *src1, bignum *src2);

	__declspec(dllexport) void add(bignum *src1, bignum *src2);

private:
	long long *data;

	int _length;

	int _dotpos;

	int _sign;
};

void computesqrt(bignum *ans, int N);

void computereciprocal(bignum *q, bignum *t, bignum *ans, int N);

void computepqt(int n, bignum *p, bignum *q, bignum *t);

void computePQT(int n, int m, bignum *p, bignum *q, bignum *t);

void chudnovsky(int N);