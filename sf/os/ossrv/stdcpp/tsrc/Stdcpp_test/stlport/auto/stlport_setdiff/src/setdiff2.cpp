 
// STLport regression testsuite component.
// To compile as a separate example, please #define MAIN.

#include <algorithm>
#include <iostream>
#include <cstring>
#include <iterator>
#include <functional>

#ifdef MAIN 
#define setdiff2_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif
int setdiff2_test(int, char**)
{
  int failures=0;
  
  cout<<"Results of setdiff2_test:"<<endl;
char* word1 = "ABCDEFGHIJKLMNO";
char* word2 = "LMNOPQRSTUVWXYZ";
char word3[12];
  ostream_iterator <char> iter(cout, " ");
  cout << "word1: ";
  copy(word1, word1 + ::strlen(word1), iter);
  
  if(strcmp(word1,"ABCDEFGHIJKLMNO"))
     failures++;
  
  cout << "\nword2: ";
  copy(word2, word2 + ::strlen(word2), iter);
  cout << endl;
 
  if(strcmp(word2,"LMNOPQRSTUVWXYZ"))
     failures++;
     
  set_difference(word1, word1 + ::strlen(word1),
                  word2, word2 + ::strlen(word2),
                  word3,
                  less<char>());
  
  word3[11]='\0';
  int x=strcmp(word3,"ABCDEFGHIJK");
  if(x)
     failures++;
    
  copy(word3,word3 + ::strlen(word3),iter);  
  
  cout << endl;
  
  if(failures)
    return 1;
  else
    return 0;
}

