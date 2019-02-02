#ifndef __GET_IP_H__
#define __GET_IP_H__

#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>


char *get_ip(char *);


#endif
