# Crypto_Messenger
UF Intro to Cryptology Fall 2017 

Description:

The users of the app will get a text-based messaging service, where they will see their unencrypted outgoing and incoming messages in their client, and the app will apply end-to-end encryption and transport the messages, so that only the users in the current conversation can view the unencrypted messages. This functionality should be in the background process; the user will just open a connection and type. The user can type person-to-person or in a group chat.

Plan to implement:

Build encryption software in Java (we can always change if need be)
First a DES encryption will be built to transfer on the server via a known key (this will be symmetric). This is to test the validity of our bulk data encryption system.
Second a RSA encryption system will be built to transfer session keys for the system in order to keep the DES key secret for each session.
Build app framework via Python/Node.js to send the encrypted messages
This framework will only handle sending/receiving messages, the encryption/decryption will be handled separately by our DES encryption software.
When entering a chat, the final implementation will create and send a session key via RSA system for DES system to use in encryption/decryption.
The messaging application will use websockets to send messages between clients. (We could do websockets within browsers so we wouldn’t have to worry about Windows vs Linux compatibility)
This will all be in the background for the user.
Integrate the encryption software and messaging app
Import functions and source code
Debugging
Testing


Resources:
Example Encrypted Messaging:
https://signal.org/#page-top
https://github.com/WhisperSystems/Signal-Desktop
https://github.com/sweis/crypto-might-not-suck

Encryption Resources:
https://en.wikipedia.org/wiki/Public-key_cryptography
https://en.wikipedia.org/wiki/End-to-end_encryption

DES in C:
http://page.math.tu-berlin.de/~kant/teaching/hess/krypto-ws2006/des.htm

Python Chat Client:
https://github.com/keyan/python-socket-chat
https://cryptography.io/en/latest/hazmat/primitives/asymmetric/rsa/
https://stackoverflow.com/questions/4241415/import-c-function-into-python-program

In-browser Websockets:
https://developer.mozilla.org/en-US/docs/Web/API/WebSocket
https://developer.mozilla.org/en-US/docs/Web/API/WebSockets_API/Writing_WebSocket_client_applications
https://github.com/websockets/ws

Chatting through Websockets:
https://spring.io/guides/gs/messaging-stomp-websocket/
http://www.codingdevil.com/2014/02/simple-chat-application-using-java-socket-programming-2.html
https://docs.oracle.com/javase/tutorial/networking/sockets/index.html

The program will allow the user to use a basic python programming chat. The chat uses end-to-end encryption to keep users' messages safe.

python-socket-chat:

A super basic chat room in python using the low level socket library. Run chat_server.py then run as many instances of the client as desired. Currently only works between instances run on the localhost or over the same network.

Run command make before opening the server.

python chat_server.py

python chat_client.py localhost 8000



