#include <iostream>
#include <cstdlib>
#include <cstring>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

int main()
{
  int fd1[2]; //Parent
  int fd2[2]; //Child
  
  const char fixed_str[] = "Pandey";
  char input_str[100];
  pid_t p;
  
  if( pipe(fd1) == -1 )
  {
    cout << "Pipe Failed" << endl;
    return 1;
  }
  
  if( pipe(fd2) == -1 )
  {
    cout << "Pipe Failed" << endl;
    return 1;
  }
  
  cout << "Enter 'Sumit'";
  cin >> input_str;
  p.fork();
  
  if( p < 0 )
  {
    cout << "Fork Failed" << endl;
  }
  
  else if( p > 0 ) //Parent Process
  {
    char concat_str[100];
    close(fd1[0]); //Close read of fd1
    
    write(fd[1], input_str, strlen(input_str) + 1); //write input string
    close(fd1[1]);
    
    wait(NULL); //Wait for child to send string
    
    close(fd2[1]; //Close read of fd2
    
    read( fd2[0], concat_str, 100 );  //Read from child
    cout << "Concatenated String: " << concat_str << endl;
    
    close( fd2[0] );
  }
  
  else  //Child Process
  {
    close( fd1[1];  //Close Parent's writing
    
    char concat_str[100];
    read( fd1[0], concat_str, 100;  //Read from Parent
    
    int k = strlen( concat_str );
    
    for( int i=0; i<strlen(fixed_str); i++ )
    {
      concat_str[k++] = fized_str[i];
    }
    
    concat_str[k] = '\0'; //string ends with '\0'
    
    //Close both reading ends
    close( fd1[0] );
    close( fd2[0] );
    
    write( fd2[1], concat_str, strlen(concat_str) + 1);
    close( fd2[1] );
    
    exit(0);
  }
  
  return 0;
  
}
