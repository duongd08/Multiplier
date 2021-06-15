/* Daniel Duong
   017002737
   9/16/20
*/


#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <stdio.h>
#include <cstring>

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main (int argc, char *argv[]) {
  int myqueue; // first queue
  key_t theKey;
  int status;

  string multiplicand; // 1st number in the equaiton
  string multiplier; // 2nd number in the equation

  struct myBuffer {
    long mtype;
    char mtext[100]; // refers a c style string
  };

  struct myBuffer buffer;

  theKey = ftok("banana" , 'a');
  cout << "theKey value: " << theKey << endl;

  myqueue = msgget(theKey, IPC_CREAT | 0600);
  cout << "myqueue value: " << myqueue << endl;

  if (myqueue == -1) {
    cout << "myqueue has an error" << endl << endl;
    return 0;
  }

 else {
 cout << "myqueue was successul" << endl << endl;
}

int theSecondKey = ftok("strawberries", 'b'); // second key required hopefully not mess up the first queue
cout << "The second key value: " << theSecondKey << endl;

int mySecondQueue = msgget(theSecondKey, IPC_CREAT | 0600); // create the second queue
cout << "The second queue value: " << mySecondQueue << endl;

  if (mySecondQueue == -1) {
   cout << "My secondQueue has an error" << endl << endl;
    return 0;
}

 else {
   cout << "My secondQueue was successful" << endl << endl;
 }

//status =  msgrcv(mySecondQueue, (struct msgbuf *)&buffer, 100, 0, 0);
//int product = atoi (buffer.mtext); // recieving the product and parsing into an integer

 /* no special instructions */
  buffer.mtype = 1;

//strcpy wants pointer to the characters
//.c_str() converts a string into a c style string

  for (int i = 0; i < 5; i++) { // loop through 5 times

     // send multiplicand first: 1st send

     cout << "Enter a multiplicand: ";
     //cin >> multiplicand;
     getline(cin, multiplicand);
     strcpy(buffer.mtext, multiplicand.c_str()); // convert multiplicand into a c string
     status = msgsnd(myqueue, (struct msgbuf *)&buffer, 100, 0); // sendng the multiplicand
     cout << "Status for multiplicand: " << status << endl;

        if (status == -1) {

       cout << "Muiltpilicand failed to send" << endl << endl;
     }

        else {
         cout << "Multiplicand sent successfully" << endl << endl;
       }
     // Before hitting the multiplier, make sure you send the message of the multiplicand first
     // because if not, you will override the buffer!

     // send multiplier next: 2nd send

     cout << "Enter a multiplier: ";
     //cin >> multiplier;
     getline(cin, multiplier);
     strcpy(buffer.mtext, multiplier.c_str()); // convert the multiplier into a c string
     status = msgsnd(myqueue, (struct msgbuf *)&buffer, 100, 0); // sending the multilpier
     cout << "Status for multiplier: " << status << endl;

      if (status == -1) {

       cout << "Multiplier failed to send" << endl << endl;
    }

     else {

       cout << "Multiplier sent successfully" << endl << endl;
   }

    status =  msgrcv(mySecondQueue, (struct msgbuf *)&buffer, 100, 0, 0);

    int product = atoi (buffer.mtext); // recieving the product and parsing into an integer

     cout << "Status for the recieving the product: " << status << endl;

     if (status == -1) {
        cout << "The Product did not recieved successfully" << endl;
     }

     else {
         cout << "The Product was recieved successfully" << endl;
      }

    // cout << "Data Content: " << buffer.mtext << endl;
     cout << "Product: " << product << endl << endl;

 }  // end of for loop

 //strcpy(buffer.mtext , "Hello"); // example of a strcpy statement

}