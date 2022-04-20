#include "platform.h"


/* Supported address families. */
#define AF_UNSPEC	0
#define AF_UNIX		1	/* Unix domain sockets 		*/
#define AF_INET		2	/* Internet IP Protocol 	*/
#define AF_AX25		3	/* Amateur Radio AX.25 		*/
#define AF_IPX		4	/* Novell IPX 			*/
#define AF_APPLETALK	5	/* Appletalk DDP 		*/
#define	AF_NETROM	6	/* Amateur radio NetROM 	*/
#define AF_BRIDGE	7	/* Multiprotocol bridge 	*/
#define AF_AAL5		8	/* Reserved for Werner's ATM 	*/
#define AF_X25		9	/* Reserved for X.25 project 	*/
#define AF_INET6	10	/* IP version 6			*/
#define AF_MAX		12	/* For now.. */

#define SOCK_STREAM	1		/* stream (connection) socket	*/
#define SOCK_DGRAM	2		/* datagram (conn.less) socket	*/
#define SOCK_RAW	3		/* raw socket			*/
#define SOCK_RDM	4		/* reliably-delivered message	*/
#define SOCK_SEQPACKET	5		/* sequential packet socket	*/
#define SOCK_PACKET	10		/* linux specific way of	*/
					/* getting packets at the dev	*/
					/* level.  For writing rarp and	*/
					/* other similar things on the	*/
					/* user level.			*/


enum
{
    SYS_SOCKET = 1,
    SYS_BIND,
    SYS_CONNECT,
    SYS_LISTEN,
    SYS_ACCEPT,
    SYS_GETSOCKNAME,
    SYS_GETPEERNAME,
    SYS_SOCKETPAIR,
    SYS_SEND,
    SYS_RECV,
    SYS_SENDTO,
    SYS_RECVFROM,
    SYS_SHUTDOWN,
    SYS_SETSOCKOPT,
    SYS_GETSOCKOPT,
    SYS_SENDMSG,
    SYS_RECVMSG
};

#define __socketcall socketcall
typedef unsigned short int sa_family_t;
typedef unsigned int socklen_t;

#define        __SOCKADDR_COMMON(sa_prefix) \
  sa_family_t sa_prefix##family


struct sockaddr
  {
    __SOCKADDR_COMMON (sa_);        /* Common data: address family and length.  */
    char sa_data[14];                /* Address data.  */
  };

struct in_addr {
    unsigned long s_addr;  // load with inet_aton()
};

struct sockaddr_in {
    short            sin_family;   // e.g. AF_INET
    unsigned short   sin_port;     // e.g. htons(3490)
    struct in_addr   sin_addr;     // see struct in_addr, below
    char             sin_zero[8];  // zero this if you want to
};

struct sockaddr_storage {
    short            sin_family;   // e.g. AF_INET
    char             ss_data[26];
};



int socket(int domain, int type, int protocol) {
  unsigned long  t[3];
  t[0] = (unsigned long) domain;
  t[1] = (unsigned long) type;
  t[2] = (unsigned long) protocol;
  return (int) __socketcall( SYS_SOCKET, t );
}

int bind(int sockfd, const struct sockaddr *my_addr, socklen_t addrlen)
{
    unsigned long  t[3];
    t[0] = (unsigned long) sockfd;
    t[1] = (unsigned long) my_addr;
    t[2] = (unsigned long) addrlen;
    return (int) __socketcall( SYS_BIND, t );
}

int listen(int s, int backlog)
{
    unsigned long  t[2];
    t[0] = (unsigned long) s;
    t[1] = (unsigned long) backlog;
    return (int) __socketcall( SYS_LISTEN, t );
}

int accept(int sock, struct sockaddr *adresse, socklen_t *longueur)
{
    unsigned long  t[3];
    t[0] = (unsigned long) sock;
    t[1] = (unsigned long) adresse;
    t[2] = (unsigned long) longueur;
    return (int) __socketcall( SYS_ACCEPT, t );
}

#define SOL_SOCKET        1
#define SO_REUSEADDR        2

int  setsockopt( int  s, int  level, int  optname, const void*  optval, socklen_t  optlen )
{
    unsigned long  t[5];
    t[0] = (unsigned long) s;
    t[1] = (unsigned long) level;
    t[2] = (unsigned long) optname;
    t[3] = (unsigned long) optval;
    t[4] = (unsigned long) optlen;
   return (int) __socketcall( SYS_SETSOCKOPT, t );
}
