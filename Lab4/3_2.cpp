#include <iostream>
#include <sys/ipc.h>
#include <sys/msg.h>
using namespace std;

struct message_buffer {
    long message_type;
    char message_text[100];
};

int main() {
    key_t key;
    int msgid;

    // Generate a unique key
    key = ftok("progfile", 65);

    // Create a message queue and return identifier
    msgid = msgget(key, 0666 | IPC_CREAT);

    message_buffer message;

    // Receive message
    msgrcv(msgid, &message, sizeof(message), 1, 0);

    cout << "Message received: " << message.message_text << endl;

    // To destroy the message queue
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}
