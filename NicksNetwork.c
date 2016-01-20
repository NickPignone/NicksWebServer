#include <netinet/in.h>    
#include <stdio.h> 
#include <string.h>   
#include <stdlib.h>    
#include <sys/socket.h>    
#include <sys/stat.h>    
#include <sys/types.h>  
#include <sys/uio.h>  
#include <unistd.h>  
#include <fcntl.h>  
    
int main() {    
   //variables used for socket and buffer
   int create_socket, new_socket;    
   socklen_t addrlen;    
   int bufsize = 1024;    
   char *buffer = malloc(bufsize);    
   struct sockaddr_in address;    
   
   //Creates the socket
   if ((create_socket = socket(AF_INET, SOCK_STREAM, 0)) > 0){    
      printf("The socket was created\n");
   }
   //setting up the address type, and port number for server
   address.sin_family = AF_INET;    
   address.sin_addr.s_addr = INADDR_ANY;    
   address.sin_port = htons(4000); 
   
   //binding to the socket
   if (bind(create_socket, (struct sockaddr *) &address, sizeof(address)) == 0){    
      printf("Binding Socket\n");
   }
    
   //loop through until server is terminated 
   while (1) {
      //listening to socket    
      if (listen(create_socket, 10) < 0) {    
         perror("server: listen");    
         exit(1);    
      }    
      //accepting the socket
      if ((new_socket = accept(create_socket, (struct sockaddr *) &address, &addrlen)) < 0) {    
         perror("server: accept");   
         exit(1);    
      }    
      //verifying to the server that the client has successfully connected
      if (new_socket > 0)    
         printf("The Client is connected...\n");

      FILE *fd; //Used for opening image and audio files
      int fsize, nbytes; //used for finding the file size for the content-length
      char *buf; //buffer
      char *token; //used for tokenizing 

      recv(new_socket, buffer, bufsize, 0);   
      printf("%s\n", buffer);  
      token = strtok(buffer, " ");
      token = strtok(NULL, " ");
      //if user requests GET /test.jpg HTTP/1.1 route user to image
      if (strcmp(token, "/test.jpg") == 0){

         fd = fopen("Test.jpg", "rb");

         fseek(fd, 0, SEEK_END);
         fsize = ftell(fd); 
         rewind(fd);
         //setting up header
         bufsize = sprintf(buffer, "HTTP/1.1 200 OK\r\n"
                           "Content-Length: %d\r\n"
                           "Content-Type: image/jpeg\r\n"
                           "Content-Transfer-Encoding: binary\r\n"
                           "Accept-Ranges: bytes\r\n"
                           "Connection: keep-alive\r\n\r\n", fsize);  
         //writing the header
         write(new_socket, buffer, bufsize);
         buf = (char*)malloc(bufsize);
         //writing the image to be displayed to user
         while((nbytes = fread(buf, sizeof(char), bufsize, fd)) > 0)
            write(new_socket, buf, nbytes);
         //freeing buffer
         free(buf);
         //freeing socket
         close(new_socket);
         //closing file
         fclose(fd);
      }
      else if (strcmp(token, "/test.html") == 0){

         fd = fopen("test.html", "rb");

         fseek(fd, 0, SEEK_END);
         fsize = ftell(fd); 
         rewind(fd);
         //setting up header
         bufsize = sprintf(buffer, "HTTP/1.1 200 OK\r\n"
                           "Content-Length: %d\r\n"
                           "Content-Type: text/html\r\n"
                           "Content-Transfer-Encoding: binary\r\n"
                           "Accept-Ranges: bytes\r\n"
                           "Connection: keep-alive\r\n\r\n", fsize);  
         //writing the header
         write(new_socket, buffer, bufsize);
         buf = (char*)malloc(bufsize);
         //writing the image to be displayed to user
         while((nbytes = fread(buf, sizeof(char), bufsize, fd)) > 0)
            write(new_socket, buf, nbytes);
         //freeing buffer
         free(buf);
         //freeing socket
         close(new_socket);
         //closing file
         fclose(fd);
      }
      //if user requests GET /test.mp3 HTTP/1.1 route user to image
      else if(strcmp(token, "/test.mp3") == 0){
         fd = fopen("test.mp3", "rb");  
         fseek(fd, 0, SEEK_END);
         fsize = ftell(fd); 
         rewind(fd);
         //setting up header
         bufsize = sprintf(buffer, "HTTP/1.1 200 OK\r\n"
                           "Content-Length: %d\r\n"
                           "Content-Type: audio/mpeg\r\n"
                           "Content-Transfer-Encoding: binary\r\n"
                           "Accept-Ranges: bytes\r\n"
                           "Connection: keep-alive\r\n\r\n", fsize);  
         //Writing header file
         write(new_socket, buffer, bufsize);
         buf = (char*)malloc(bufsize);
         //writing the audio file to the server
         while((nbytes = fread(buf, sizeof(char), bufsize, fd)) > 0)
            write(new_socket, buf, nbytes);

         //freeing the buffer
         free(buf);
         //closing socket
         close(new_socket);
         //closing file
         fclose(fd);
      }
      //else if user is on main page, display main page response
      else{
         //setting up header
         write(new_socket, "HTTP/1.1 200 OK\n", 16);
         write(new_socket, "Content-length: 195\n", 20);
         write(new_socket, "Content-Type: text/html\n\n", 25);
         //writing actuall html code to be displayed
         write(new_socket, "<html><head><style>body{background-color: #f00</style></head><body><H1>Welcome To Nick Pignone's Server</H1><div>Type /test.jpg for image or /test.mp3 for mp3 in address line.</div></body></html>",195);
         //closing socket
         close(new_socket);  
      }
   }    
   //close socket
   close(create_socket);    
   return 0;    
}