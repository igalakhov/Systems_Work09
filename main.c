#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h> // open
#include <unistd.h> // close
#include <time.h>


/*
  File reading and writing goes here
  1. write some random number to fd_write
  2. close fd_write
  3. open fd_read with reading
  4. read from fd_read and print the number out
  5. close fd_read
*/

int main(){
  srand(time(NULL));
  int fd_write, fd_read;

  // open file that doesn't exist
  printf("\nAttemting to open [missing_file.txt] for writing only\n");
  fd_write = open("missing_file.txt", O_WRONLY);

  if(fd_write == -1)
    printf(" File not found (file descriptor: %d)\n", fd_write);
  else
    printf(" File found! (file descriptor: %d)\n", fd_write);

  // open file that we know exists
  printf("\nAttemting to open [file] for writing\n");
  fd_write = open("file.txt", O_WRONLY | O_CREAT);

  if(fd_write == -1)
    printf(" File not found (file descriptor: %d)\n", fd_write);
  else
    printf(" File found! (file descriptor: %d)\n", fd_write);

  //write a random number to fd_write
  int rand_num = rand();
  printf("\nWriting [secret] random number to [file.txt]");

  size_t num_written = write(fd_write, &rand_num, sizeof(rand_num));
  printf("\n Secret number written (%zu bytes written)\n", num_written);
  if(num_written == -1){
    printf("Something went wrong...\n");
    exit(1);
  }

  //close fd_write
  printf("\nClosing writing of [file.txt]\n");
  if(!close(fd_write))
    printf(" File closed!\n");
  else
    printf(" Something went wrong!\n");

  // open fd_read with reading
  printf("\nAttemting to open [file.txt] for reading\n");
  fd_read = open("file.txt", O_RDONLY | O_CREAT);

  if(fd_read == -1)
    printf(" File not found (file descriptor: %d)\n", fd_read);
  else
    printf(" File found! (file descriptor: %d)\n", fd_read);


  // read from fd_read and print stuff out
  printf("\nAttempting to retrieve secret number from [file.txt]\n");
  int retrieved_rand_num;
  size_t num_read = read(fd_read, &retrieved_rand_num, sizeof(retrieved_rand_num));
  if(num_read == -1){
    printf("Something went wrong...\n");
    exit(1);
  }

  printf(" %zu bytes read succesfully! Verifying...\n", num_read);
  printf(" Original secret number: [%d]\n", rand_num);
  printf(" Retrieved secret number: [%d]\n", retrieved_rand_num);
  if(rand_num == retrieved_rand_num)
    printf(" Both numbers are the same! Great!\n");
  else
    printf(" Something went very wrong...\n");


  // close fd_read
  printf("\nClosing reading of [file.txt]\n");
  if(!close(fd_read))
    printf(" File closed!\n");
  else
    printf(" Something went wrong!\n");

  return 0;
}
