#include <iostream>
#include <unistd.h>
using namespace std;

int main()
{
  pid_t p =fork();
  if( p < 0 )
  {
    perror("Fork Failed!");
    exit(1);
  }
  cout << "Hello World, process_id(pid) = " << getpid() << endl;
  return 0;
}
