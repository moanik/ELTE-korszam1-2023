#include "matrix.h"
#include <iostream>
using namespace std;

int main()
{
	auto err = [](auto str){ std::cout << "Matrix.h error in: " << str << "\n"; std::exit(-1); };


	//Test default constructor:
	{
		Matrix<double> u;
		if(u.size() != 0)         { err("default contructor test [size]");           }
		if(u.begin() != u.end())  { err("default contructor test [begin == end]");   }
		if(u.cbegin() != u.cend()){ err("default contructor test [cbegin == cend]"); }
	}

	//Test list initialization and indexing:
	{
		vector<double> v{3.1, 5.2, 9.3, 3.1, 5.2, 9.3, 3.1, 5.2, 9.3};
		Matrix<double> a = v;
		if(a.size() != 3)                            { err("initializer list constructor test [size]");               }
		if(a[0] != 3.1 || a[1] != 5.2 || a[2] != 9.3){ err("initializer list constructor test [indexing with []]");   }
		if(a(0, 0) != 3.1 || a(1, 1) != 5.2 || a(2, 2) != 9.3){ err("initializer list constructor test [indexing with ()]");   }
	}
	//Test copy constructor:
	{
		vector<double> v{3.1, 5.2, 9.3, 3.1, 5.2, 9.3, 3.1, 5.2, 9.3};
		Matrix<double> a = v;
		Matrix<double> b{a};
		if(b.size() != 3)                            { err("copy constructor test [size]");               }
		if(b[0] != 3.1 || b[1] != 5.2 || b[2] != 9.3){ err("copy constructor test [elements]");           }
		if(a.size() != 3)                            { err("copy constructor test [src size]");           }
		if(a[0] != 3.1 || a[1] != 5.2 || a[2] != 9.3){ err("copy constructor test [src elements]");       }
	}
	//Test move constructor:
	{
		vector<double> v{3.1, 5.2, 9.3, 3.1, 5.2, 9.3, 3.1, 5.2, 9.3};
		Matrix<double> a = v;
		Matrix<double> b{ std::move(a) };
		if(b.size() != 3)                            { err("move constructor test [size]");                 }
		if(b[0] != 3.1 || b[1] != 5.2 || b[2] != 9.3){ err("move constructor test [elements]");             }
	}
	//Test indexible function constructor:
	{
		Matrix<int> a{ Idx1{}, [](int i){ return 100*i*i+20*i+5; }, 2};
		if(a.size() != 2)                                         { err("constructor from indexible test [size]");     }
		if(a[0] != 5 || a[1] != 125 || a[2] != 445 || a[3] != 965){ err("constructor from indexible test [elements]"); }
	}
	//Test assignment:
	{
		vector<double> v{3.1, 5.2, 9.3, 3.1, 5.2, 9.3, 3.1, 5.2, 9.3};
		Matrix<double> a = v;
		Matrix<double> b;
		b = a;
		if(b.size() != 3)                            { err("assignment test [size]");         }
		if(b[0] != 3.1 || b[1] != 5.2 || b[2] != 9.3){ err("assignment test [elements]");     }
		if(a.size() != 3)                            { err("assignment test [src size]");     }
		if(a[0] != 3.1 || a[1] != 5.2 || a[2] != 9.3){ err("assignment test [src elements]"); }
	}

	//Test self assignment:
	{
		vector<double> v{3.1, 5.2, 9.3, 3.1, 5.2, 9.3, 3.1, 5.2, 9.3};
		Matrix<double> c = v;
		c = c;
		if(c.size() != 3)                            { err("self assignment test [size]");     }
		if(c[0] != 3.1 || c[1] != 5.2 || c[2] != 9.3){ err("self assignment test [elements]"); }
	}
	//Test move assignment:
	{
		vector<double> v{3.1, 5.2, 9.3, 3.1, 5.2, 9.3, 3.1, 5.2, 9.3};
		Matrix<double> a = v;
		Matrix<double> b;
		b = std::move(a);
		if(b.size() != 3)                            { err("assignment test [size]");                 }
		if(b[0] != 3.1 || b[1] != 5.2 || b[2] != 9.3){ err("assignment test [elements]");             }
	}

	//Test self move assignment:
	{
		vector<double> v{3.1, 5.2, 9.3, 3.1, 5.2, 9.3, 3.1, 5.2, 9.3};
		Matrix<double> c = v;
		c = std::move(c);
		if(c.size() != 3)                            { err("self assignment test [size]");     }
		//if(c[0] != 3.1 || c[1] != 5.2 || c[2] != 9.3){ err("self assignment test [elements]"); }
	}

	//Test operator+ (l-value, l-value)
	{
		Matrix<double> a   = vector<double>{3.1, 5.2, 9.3, 3.1, 5.2, 9.3, 3.1, 5.2, 9.3};
		Matrix<double> b   = vector<double>{7.1, 15.2, 11.3,7.1, 15.2, 11.3,7.1, 15.2, 11.3};
		Matrix<double> ref = vector<double>{10.2, 20.4, 20.6,10.2, 20.4, 20.6,10.2, 20.4, 20.6};
		Matrix<double> res = a + b;
		if(a.size() != 3)                              { err("operator+ test (l-value, l-value) [src size]");     }
		if(b.size() != 3)                              { err("operator+ test (l-value, l-value) [src size]");     }
		if(res.size() != 3)                            { err("operator+ test (l-value, l-value) [size]");         }
		if(a[0] != 3.1 || a[1] !=  5.2 || a[2] !=  9.3){ err("operator+ test (l-value, l-value) [src elements]"); }
		if(b[0] != 7.1 || b[1] != 15.2 || b[2] != 11.3){ err("operator+ test (l-value, l-value) [src elements]"); }
	}

	//Test operator+ (r-value, l-value)
	{
		Matrix<double> a   = vector<double>{3.1, 5.2, 9.3, 3.1, 5.2, 9.3, 3.1, 5.2, 9.3};
		Matrix<double> b   = vector<double>{7.1, 15.2, 11.3,7.1, 15.2, 11.3,7.1, 15.2, 11.3};
		Matrix<double> ref = vector<double>{10.2, 20.4, 20.6,10.2, 20.4, 20.6,10.2, 20.4, 20.6};
		Matrix<double> res = std::move(a) + b;
		if(b.size() != 3)                              { err("operator+ test (r-value, l-value) [src size]");     }
		if(res.size() != 3)                            { err("operator+ test (r-value, l-value) [size]");         }
		if(b[0] != 7.1 || b[1] != 15.2 || b[2] != 11.3){ err("operator+ test (r-value, l-value) [src elements]"); }
	}

	//Test operator+ (l-value, r-value)
	{
		Matrix<double> a   = vector<double>{3.1, 5.2, 9.3, 3.1, 5.2, 9.3, 3.1, 5.2, 9.3};
		Matrix<double> b   = vector<double>{7.1, 15.2, 11.3,7.1, 15.2, 11.3,7.1, 15.2, 11.3};
		Matrix<double> ref = vector<double>{10.2, 20.4, 20.6,10.2, 20.4, 20.6,10.2, 20.4, 20.6};
		Matrix<double> res = a + std::move(b);
		if(a.size() != 3)                              { err("operator+ test (l-value, r-value) [src size]");     }
		if(res.size() != 3)                            { err("operator+ test (l-value, r-value) [size]");         }
		if(a[0] != 3.1 || a[1] !=  5.2 || a[2] !=  9.3){ err("operator+ test (l-value, r-value) [src elements]"); }
	}

	//Test operator+ (r-value, r-value)
	{
		Matrix<double> a   = vector<double>{3.1, 5.2, 9.3, 3.1, 5.2, 9.3, 3.1, 5.2, 9.3};
		Matrix<double> b   = vector<double>{7.1, 15.2, 11.3,7.1, 15.2, 11.3,7.1, 15.2, 11.3};
		Matrix<double> ref = vector<double>{10.2, 20.4, 20.6,10.2, 20.4, 20.6,10.2, 20.4, 20.6};
		Matrix<double> res = std::move(a) + std::move(b);
		if(b.size() != 3)            { err("operator+ test (r-value, r-value) [src size]"); }//this argument was not reused!
		if(res.size() != 3)          { err("operator+ test (r-value, r-value) [size]");     }
	}

	//Test operator- (l-value, l-value) (more detailed test, since later tests depend on it)
	{
		Matrix<double> a   = vector<double>{3.1, 5.2, 9.3, 3.1, 5.2, 9.3, 3.1, 5.2, 9.3};
		Matrix<double> b   = vector<double>{7.1, 15.2, 11.3,7.1, 15.2, 11.3,7.1, 15.2, 11.3};
		Matrix<double> ref = vector<double>{4.0, 10.0, 2.0, 4.0, 10.0, 2.0, 4.0, 10.0, 2.0};
		Matrix<double> res = b - a;
		if(a.size() != 3)                              { err("operator- test (l-value, l-value) [src size]");     }
		if(a[0] != 3.1 || a[1] != 5.2 || a[2] != 9.3)  { err("operator- test (l-value, l-value) [src elements]"); }
		if(b.size() != 3)                              { err("operator- test (l-value, l-value) [src size]");     }
		if(b[0] != 7.1 || b[1] != 15.2 || b[2] != 11.3){ err("operator- test (l-value, l-value) [src elements]"); }
		if(res.size() != 3)                            { err("operator- test (l-value, l-value) [size]");         }
		if(std::abs(ref[0]-res[0]) > 1e-15 ||
		   std::abs(ref[1]-res[1]) > 1e-15 || 
		   std::abs(ref[2]-res[2]) > 1e-15    ){ err("operator- test (l-value, l-value) [elements]"); }
	}

	//Test operator- (r-value, l-value)
	{
		Matrix<double> a   = vector<double>{3.1, 5.2, 9.3, 3.1, 5.2, 9.3, 3.1, 5.2, 9.3};
		Matrix<double> b   = vector<double>{7.1, 15.2, 11.3,7.1, 15.2, 11.3,7.1, 15.2, 11.3};
		Matrix<double> ref = vector<double>{4.0, 10.0, 2.0, 4.0, 10.0, 2.0, 4.0, 10.0, 2.0};
		Matrix<double> res = std::move(b) - a;
		if(a.size() != 3)                              { err("operator- test (r-value, l-value) [src size]");     }
		if(res.size() != 3)                            { err("operator- test (r-value, l-value) [size]");         }
		if(a[0] != 3.1 || a[1] !=  5.2 || a[2] !=  9.3){ err("operator- test (r-value, l-value) [src elements]"); }
	}

	//Test operator- (l-value, r-value)
	{
		Matrix<double> a   = vector<double>{3.1, 5.2, 9.3, 3.1, 5.2, 9.3, 3.1, 5.2, 9.3};
		Matrix<double> b   = vector<double>{7.1, 15.2, 11.3,7.1, 15.2, 11.3,7.1, 15.2, 11.3};
		Matrix<double> ref = vector<double>{4.0, 10.0, 2.0, 4.0, 10.0, 2.0, 4.0, 10.0, 2.0};
		Matrix<double> res = b - std::move(a);
		if(b.size() != 3)                              { err("operator- test (l-value, r-value) [src size]");     }
		if(res.size() != 3)                            { err("operator- test (l-value, r-value) [size]");         }
		if(b[0] != 7.1 || b[1] != 15.2 || b[2] != 11.3){ err("operator- test (l-value, r-value) [src elements]"); }
	}

	//Test operator- (r-value, r-value)
	{
		Matrix<double> a   = vector<double>{3.1, 5.2, 9.3, 3.1, 5.2, 9.3, 3.1, 5.2, 9.3};
		Matrix<double> b   = vector<double>{7.1, 15.2, 11.3,7.1, 15.2, 11.3,7.1, 15.2, 11.3};
		Matrix<double> ref = vector<double>{4.0, 10.0, 2.0, 4.0, 10.0, 2.0, 4.0, 10.0, 2.0};
		Matrix<double> res = std::move(b) - std::move(a);
		if(a.size() != 3)            { err("operator- test (r-value, r-value) [src size]"); }//this argument was not reused!
		if(res.size() != 3)          { err("operator- test (r-value, r-value) [size]");     }
	}

	//Test operator* (l-value, scalar)
	{
		Matrix<double> a   = vector<double>{3.1, -5.2,  9.3, 3.1, -5.2,  9.3, 3.1, -5.2,  9.3};
		Matrix<double> ref = vector<double>{6.2, -10.4, 18.6, 6.2, -10.4, 18.6, 6.2, -10.4, 18.6};
		Matrix<double> res = a * 2.0;
		if(a.size()   != 3)                           { err("operator* test (l-value, scalar) [src size]");     }
		if(res.size() != 3)                           { err("operator* test (l-value, scalar) [size]");         }
		if(a[0] != 3.1 || a[1] != -5.2 || a[2] != 9.3){ err("operator* test (l-value, scalar) [src elements]"); }
	}

	//Test operator* (r-value, scalar)
	{
		Matrix<double> a   = vector<double>{3.1, -5.2,  9.3, 3.1, -5.2,  9.3, 3.1, -5.2,  9.3};
		Matrix<double> ref = vector<double>{6.2, -10.4, 18.6, 6.2, -10.4, 18.6, 6.2, -10.4, 18.6};
		Matrix<double> res = std::move(a) * 2.0;
		if(res.size() != 3)          { err("operator* test (r-value, scalar) [size]");         }
	}

	//Test operator* (scalar, l-value)
	{
		Matrix<double> a   = vector<double>{3.1, -5.2,  9.3, 3.1, -5.2,  9.3, 3.1, -5.2,  9.3};
		Matrix<double> ref = vector<double>{6.2, -10.4, 18.6, 6.2, -10.4, 18.6, 6.2, -10.4, 18.6};
		Matrix<double> res = 2.0 * a;
		if(a.size()   != 3)                           { err("operator* test (scalar, l-value) [src size]");     }
		if(res.size() != 3)                           { err("operator* test (scalar, l-value) [size]");         }
		if(a[0] != 3.1 || a[1] != -5.2 || a[2] != 9.3){ err("operator* test (scalar, l-value) [src elements]"); }
	}

	//Test operator* (scalar, r-value)
	{
		Matrix<double> a   = vector<double>{3.1, -5.2,  9.3, 3.1, -5.2,  9.3, 3.1, -5.2,  9.3};
		Matrix<double> ref = vector<double>{6.2, -10.4, 18.6, 6.2, -10.4, 18.6, 6.2, -10.4, 18.6};
		Matrix<double> res = 2.0 * std::move(a);
		if(res.size() != 3)          { err("operator* test (scalar, r-value) [size]");         }
	}

	//Test operator/ (l-value, scalar)
	{
		Matrix<double> ref   = vector<double>{3.1, -5.2,  9.3, 3.1, -5.2,  9.3, 3.1, -5.2,  9.3};
		Matrix<double> a = vector<double>{6.2, -10.4, 18.6, 6.2, -10.4, 18.6, 6.2, -10.4, 18.6};
		Matrix<double> res = a / 2.0;
		if(a.size()   != 3)                             { err("operator/ test (l-value, scalar) [src size]");     }
		if(res.size() != 3)                             { err("operator/ test (l-value, scalar) [size]");         }
		if(a[0] != 6.2 || a[1] != -10.4 || a[2] != 18.6){ err("operator/ test (l-value, scalar) [src elements]"); }
	}

	//Test operator/ (r-value, scalar)
	{
		Matrix<double> ref   = vector<double>{3.1, -5.2,  9.3, 3.1, -5.2,  9.3, 3.1, -5.2,  9.3};
		Matrix<double> a = vector<double>{6.2, -10.4, 18.6, 6.2, -10.4, 18.6, 6.2, -10.4, 18.6};
		Matrix<double> res = std::move(a) / 2.0;
		if(res.size() != 3)          { err("operator/ test (r-value, scalar) [size]");     }
	}

	//Test operator* (Matrix, Matrix)
	{
		Matrix<int> b   = vector<int>{1, 2, 1, 2};
		Matrix<int> a = vector<int>{1, 2, 1, 2};
		Matrix<int> res = a * b;
		//if(res.size() != 2)          { err("operator* test (Matrix, Matrix) [size]");     }
		//if(res(0, 0) != 3)          { err("operator* test (Matrix, Matrix) [value]");     }
	}

	std::cout << "All tests are successful!\n";
	return 0;

}