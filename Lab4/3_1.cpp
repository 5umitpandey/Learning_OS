#include <iostream>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>
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
    message.message_type = 1;

    cout << "Enter message to send: ";
    cin.getline(message.message_text, 100);

    // Send message
    msgsnd(msgid, &message, sizeof(message), 0);

    cout << "Message sent: " << message.message_text << endl;

    return 0;
}

