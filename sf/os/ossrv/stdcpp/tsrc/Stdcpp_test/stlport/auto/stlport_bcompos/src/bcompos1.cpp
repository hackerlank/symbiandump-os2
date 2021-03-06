
// STLport regression testsuite component.
// To compile as a separate example, please #define MAIN.

#include <algorithm>
#include <iostream>

#include "unary.h"


#ifdef MAIN
#define bcompos1_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif
int bcompos1_test(int, char**)
{

	cout<<"Results of bcompos1_test:"<<endl;

	int array [6] = { -2, -1, 0, 1, 2, 3 };

	binary_compose<logical_and<bool>, odd, positive> b =
	binary_compose<logical_and<bool>, odd, positive>(logical_and<bool>(), odd(), positive());
	int* p = find_if((int*)array, (int*)array + 6, b);
	if(p != array + 6)
	cout << *p << " is odd and positive" << endl;

    if (*p == 1)
       return 0;
  else
  return 1;
}
