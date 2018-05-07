#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>

int main(int argc, char**argv)
{
   int listenfd,connfd,n;
   struct sockaddr_in servaddr,cliaddr;
   socklen_t clilen;
   pid_t     childpid;
   char mesg[1000];

   listenfd=socket(AF_INET,SOCK_STREAM,0);

   bzero(&servaddr,sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
   servaddr.sin_port=htons(8899);
   bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr));

   listen(listenfd,1024);
  
   clilen=sizeof(cliaddr);
   connfd = accept(listenfd,(struct sockaddr *)&cliaddr,&clilen);

   close (listenfd);

   n = recvfrom(connfd,mesg,1000,0,(struct sockaddr *)&cliaddr,&clilen);
   mesg[n] = '\0';
            
   printf("%s\n",mesg);
       
   close(connfd);   
}
