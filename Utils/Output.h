#include <iostream>
#include <string>

#define OUTPUT

using namespace std;

class Output
{
public:
  static void showError(string, bool fatal = true);
  static void showSuccess(string);
};

void Output::showError(string err, bool fatal)
{
  if (fatal){
    cout << "\x1B[31mError: " + err + "\033[0m\n";
    exit(1);
  }

  cout << "\x1B[33mWarn: " + err + "\033[0m\n";
}

void Output::showSuccess(string msg)
{
  cout << "\x1B[32m" + msg + "\033[0m\n";
}