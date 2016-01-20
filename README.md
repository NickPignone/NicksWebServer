# NicksWebServer

I created my own webserver using the C language type. This was for an assignment in CS 2240. 
Use the included Makefile to compile and run this program. Then connect to your localhost
As follows are the specs for this program:

1) The server can handle multiple clients.

2) The server can manage GET Http requests and serve image and audio files. 

3) The server will attempt to notice multiple requests from the same IP address, implementing a security policy that attempts to defeat some crude DDOS attack. 


The Unix system calls you build with are those that allow a 'socket' to be created for something you might think of as a networked pipe. On top of this flow of data you must implement the simplest HTTP protocol so that GET requests can be managed. 

We will assume that for each client you will spin off a thread that handles the server / client interaction. I don't know if forking processes is any easier, but a threaded server would use fewer system resources, and thus I make the assumption.
