/*Daniel Duong
  017002737
  9/16/20
*/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>

#include <iostream>
#include <string>
#include <sstream> //needed to convert the number to a string, then convert that string into a c type string
#include <cstring> // needed for strcpy
#include <algorithm>
using namespace std;

int main (int argc, char *argv[]) {
  int myqueue;
  key_t theKey;
  int status;

  struct myBuffer { // important!
    long mtype;
    char mtext[100];
  };

// if you send the message twice, you recieve it twice!
// NOTE: Sender and Reciever is a Pair!!!

  struct myBuffer buffer;

  theKey = ftok("banana" , 'a'); // NOTE: if the file is missing within the directory of the code, -1 will appear
  cout << "theKey value: " << theKey << endl;

  myqueue = msgget(theKey, IPC_CREAT | 0600);
  cout << "myqueue: " << myqueue << endl;

  if (myqueue == -1) {
    cout << "myqueue has an error" << endl << endl;
    return 0;
  }

  else {
    cout << "myqueue was successful" << endl << endl;
 }

  /* no special instructions, no flags */
  bool running = true;

  while (running) {

  // recieving multiplicand

  status = msgrcv(myqueue, (struct msgbuf *)&buffer, 100, 0, 0); // 1st message recieved

  int multiplicand = atoi (buffer.mtext); // pass in buffer.mtext because the queue that recieved this message was saved in the buffer

  cout << "multiplicand : " << multiplicand << endl;

  cout << "Status for multiplicand: " << status << endl;

   if (status == -1) {
     cout << "Multiplicand was not successfully recieved" << endl << endl;
     return 0;
}

  else {
      cout << "Muliplicand was successfuly recieved" << endl << endl;
  }

  // recieving multiplier

  status = msgrcv(myqueue, (struct msgbuf *)&buffer, 100, 0, 0); // 2nd message recieved

  int multiplier = atoi (buffer.mtext); // atoi converts the c string into an integer

  cout << "multiplier : " << multiplier << endl;

  cout << "Status for multiplier: " << status << endl;

  if (status == -1) {
    cout << "Multiplier was not successfully recieved" << endl << endl;
    return 0;
  }


 else {
    cout << "Multiplier was successfully recieved" << endl << endl;
  }

  int product = multiplicand * multiplier;

  stringstream ss; // initialize into a string stream
  ss << product;

  string result = ss.str(); // converts the product into a string

  strcpy(buffer.mtext, result.c_str()); // copies the string result as a c string into the buffer

  //cout << "Data: " << buffer.mtext << endl;
  //cout << "The result is: " << result << endl; // making sure that the product works
  cout << endl;

 // Declare the buffer type hopefully not to confuse it with the other buffer's data
 buffer.mtype = 1;

 int theSecondKey = ftok("strawberries", 'b');
 cout << "theSecondKey value: " << theSecondKey << endl;

 // DO NOT ERASE THE DATA FROM THE SECOND QUEUE YET bc both the sender and the reciever will run at the same time!!!

 int mySecondQueue = msgget(theSecondKey, IPC_CREAT | 0600); //second queue
 cout << "mySecondQueue: " << mySecondQueue << endl;

 if (mySecondQueue == -1) {
    cout << "My secondQueue has an error" << endl << endl;
    return 0;                                                                                                             }

  else {
    cout << "My secondQueue was successful" << endl << endl;
 }

 status = msgsnd(mySecondQueue, (struct msgbuf *)&buffer, 100, 0); //ready to send the product back to the sender
 cout << "Status for sending the product: " << status << endl;

 if (status == -1) {
    cout << "The product was not able to send" << endl << endl;
    return 0;
  }

  else {
    cout << "The product was successfully sent" << endl << endl;
  }

 } // end of while loop

}