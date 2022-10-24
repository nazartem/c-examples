/* принимает на вход имя хоста и печатает в стандартный поток вывода
каноническое имя, тип и длину адреса, список IP-адресов */

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>

int main(int argc, char **argv) {
  int i = 0;

  if (argc != 2)
    return -1;

  struct hostent *h;
  h = gethostbyname(argv[1]);

  if (h == NULL) {
    printf("Error\n");
    return -1;
  }

  printf("Canonical name %s\n", h->h_name);
  printf("Type = %s len = %d\n", (h->h_addrtype == AF_INET) ? "ipv4" : "ipv6", h->h_length);

  while (h->h_addr_list[i] != NULL) {
    struct in_addr *a = (struct in_addr*) h->h_addr_list[i];
    printf("%s\n", inet_ntoa(*a));
    i++;
  }

  return 0;
}
