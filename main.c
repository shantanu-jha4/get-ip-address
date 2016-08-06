//
//  main.c
//  socket
//
//  Created by Shantanu Jha on 7/9/16.
//  Copyright © 2016 BlueBall. All rights reserved.
//

#include "socket.h"

int main(int argc, const char * argv[]) {
    struct addrinfo hints, *res, *p;
    int status;
    char ipstrng[INET6_ADDRSTRLEN];
    
    if(argc != 2) {
        printf("usage: showip hostname\n");
        return 1;
    }
    
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    status = getaddrinfo(argv[1], NULL, &hints, &res);
    if (status != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        return 1;
    }
    
    printf("IP Address for %s: \n\n", argv[1]);
    
    for(p = res; p != NULL; p= p->ai_next) {
        void* addr;
        char* ipver;
        if (p->ai_family == AF_INET) {
            struct sockaddr_in* ipv4 = (struct sockaddr_in*) p->ai_addr;
            addr = &(ipv4->sin_addr);
            ipver = "IPv4";
        }
        if (p->ai_family == AF_INET6) {
            struct sockaddr_in6* ipv6 = (struct sockaddr_in6*) p->ai_addr;
            addr = &(ipv6->sin6_addr);
            ipver = "IPv6";
        }
        inet_ntop(p->ai_family, addr, ipstrng, sizeof(ipstrng));
        printf("  %s: %s\n", ipver, ipstrng);
    }
    freeaddrinfo(res);
    return 0;
}
