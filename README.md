# Server-Multiple-Client-Chat
Chat application using TCP written in C. Server can handle multiple clients

This project is for Internet & Mobile Programming Courses at Dankook University
- Adeliana Yuwono (32179096)
- Diaz (32179097)
- Triladias Puteri Heryadi (32179093)

Server :
- socket()
- bind()
- listen()
- accept()
- using fork() for handle multiple clients
- recv()
- send the message to client back with send()
- close()

Client :
- socket()
- connect()
- send()
- recv()
- close()

Build Environment :
Linux OS
C programming language
to compile the file :

1. - Open Linux terminal
   - type: gcc server.c -o server
   - type: ./server

2. - Add new terminal
   - type: gcc client.c -o client
   - type: ./client

Repeat step number 2 if want to add another client (max.4)
