int errno;
typedef char uint8_t;
typedef char bool;
#define true 1
#define false 0
#include "platform.h"
#include "socket.h"

int strlen(char* str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

void print(char* str) {
    write(1, str, strlen(str));
}

int max(int a, int b) {
  if (a > b) {
    return a;
  }
  return b;
}

bool allhexletters(char* buf, int size) {
  for (int i = 0; i < size; i++) {
    if (!(('0' <= buf[i] && buf[i] <= '9') || ('a' <= buf[i] && buf[i] <= 'f') || ('A' <= buf[i] && buf[i] <= 'F'))) {
      return false;
    }
  }
  return true;
}

bool allletters(char* buf, int size) {
  for (int i = 0; i < size; i++) {
    if (!(('a' <= buf[i] && buf[i] <= 'z') || ('A' <= buf[i] && buf[i] <= 'Z'))) {
      return false;
    }
  }
  return true;
}

// Standard memset
void* memset(void * ptr, int value, int num) {
  for (int i = 0; i < num; i++) {
    ((char*)ptr)[i] = (char)value;
  }
  return ptr;
}

// Checks if content of buffers up to len `num` is equal
bool memeq(const char* a, const char* b, int num) {
  while (num > 0) {
    if (*a != *b) {
      return false;
    }
    a++;
    b++;
    num--;
  }
  return true;
}

// Responds to a HTTP request
int respond(int fd) {
  char buf[1024] = {0};
  int r = read(fd, buf, 5);
  if (r != 5) {
    print("Read less than 5 bytes?\n");
    return -1;
  }
  // Check if GET request
  if (!memeq(buf, "GET /", 5)) {
    read(fd, buf, 1024); // read remaining incoming packet
    char* response = "HTTP/1.1 405 Method Not Allowed\r\n\r\n";
    write(fd, response, strlen(response));
    return 0;
  }

  int size = 0;
  char color[32];
  // Read URL path up to space, in oversized buffer
  while (size < 20) {
    int s = read(fd, color + size, 1);
    if (color[size] == ' ') {
      break;
    }
    size++;
  }
  char repcolor[32] = {0};
  
  if ((size == 3 || size == 6) && allhexletters(color, size)) {
    // Hex color
    repcolor[0] = '#';
    for (int i = 0; i < size; i++) {
      repcolor[1+i] = color[i];
    }
  } else if (size == 4 && memeq(color, "zeus", 4)) {
    // Zeus color
    for (int i = 0; i < 7; i++) {
      repcolor[i] = ("#ff7f00")[i];
    }
  } else if (size > 0 && allletters(color, size)) {
    // Color name
    for (int i = 0; i < size; i++) {
      repcolor[i] = color[i];
    }
  } else {
    // Default to black
    for (int i = 0; i < 7; i++) {
      repcolor[i] = ("#000000")[i];
    }
  }
  read(fd, buf, 1024); // read remaining incoming packet

  char* response = "HTTP/1.1 200 OK\r\nContent-type: image/svg+xml\r\n\r\n";
  write(fd, response, strlen(response));
  char* firstpart = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n<svg\n   xmlns:dc=\"http://purl.org/dc/elements/1.1/\"\n   xmlns:cc=\"http://creativecommons.org/ns#\"\n   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n   xmlns:svg=\"http://www.w3.org/2000/svg\"\n   xmlns=\"http://www.w3.org/2000/svg\"\n   viewBox=\"0 0 899.59998 557.83002\"\n   height=\"557.83002\"\n   width=\"899.59998\"\n   xml:space=\"preserve\"\n   version=\"1.1\"\n   id=\"svg2\"><metadata\n     id=\"metadata8\"><rdf:RDF><cc:Work\n         rdf:about=\"\"><dc:format>image/svg+xml</dc:format><dc:type\n           rdf:resource=\"http://purl.org/dc/dcmitype/StillImage\" /></cc:Work></rdf:RDF></metadata><defs\n     id=\"defs6\"><clipPath\n       id=\"clipPath16\"\n       clipPathUnits=\"userSpaceOnUse\"><path\n         id=\"path18\"\n         d=\"m 0,446.264 719.68,0 L 719.68,0 0,0 0,446.264 Z\" /></clipPath></defs><g\n     transform=\"matrix(1.25,0,0,-1.25,0,557.83)\"\n     id=\"g10\"><g\n       id=\"g12\"><g\n         clip-path=\"url(#clipPath16)\"\n         id=\"g14\"><g\n           transform=\"translate(2.1416,386.5537)\"\n           id=\"g20\"><path\n             id=\"path22\"\n             style=\"fill:";
  write(fd, firstpart, strlen(firstpart));
  write(fd, repcolor, strlen(repcolor));
  char* secondpart = ";fill-opacity:1;fill-rule:nonzero;stroke:none\"\n             d=\"m 0,0 159.742,0 -162.886,-195.099 0,-46.891 263.987,0 0,59.714 -167.631,0 164.49,195.098 0,46.889 L 0,59.711 0,0 Z m 609.684,-336.269 40.855,0 0,131.994 -40.855,0 0,-131.994 z m -72.188,103.709 c 9.177,0 16.151,-3.236 20.962,-9.68 4.808,-6.411 7.228,-15.745 7.228,-28.032 0,-12.29 -2.42,-21.653 -7.228,-28.097 -4.811,-6.409 -11.785,-9.616 -20.962,-9.616 -9.146,0 -16.153,3.237 -21.058,9.711 -4.871,6.505 -7.321,15.808 -7.321,28.002 0,12.192 2.45,21.496 7.321,28.001 4.905,6.474 11.913,9.711 21.058,9.711 m -28.378,-84.852 c 5.906,-7.543 12.414,-13.073 19.548,-16.655 7.134,-3.554 15.336,-5.345 24.639,-5.345 16.467,0 29.981,6.441 40.509,19.357 10.593,12.887 15.871,29.48 15.871,49.782 0,20.302 -5.278,36.895 -15.871,49.778 -10.526,12.918 -24.042,19.359 -40.509,19.359 -9.303,0 -17.505,-1.791 -24.639,-5.342 -7.134,-3.584 -13.642,-9.113 -19.548,-16.656 l 0,18.856 -40.855,0 0,-182.278 40.855,0 0,69.144 z m -207.514,-18.857 45.664,0 21.937,90.762 22.062,-90.762 45.664,0 34.477,131.993 -40.667,0 -22.03,-90.069 -21.968,90.069 -34.946,0 -22.062,-90.981 -21.937,90.983 -40.667,0 34.473,-131.995 z M 703.965,-12.57 c -13.388,3.236 -25.802,5.625 -37.21,7.133 -11.408,1.541 -22.281,2.294 -32.621,2.294 -26.367,0 -45.946,-4.557 -58.738,-13.639 -12.758,-9.081 -19.138,-23.035 -19.138,-41.861 0,-17.41 5.248,-30.39 15.714,-38.968 10.465,-8.549 28.755,-14.426 54.81,-17.6 l 9.333,-1.227 c 10.748,-1.319 17.944,-3.206 21.56,-5.625 3.613,-2.419 5.437,-6.097 5.437,-11 0,-5.907 -2.797,-10.339 -8.358,-13.324 -5.562,-2.985 -13.828,-4.463 -24.827,-4.463 -12.194,0 -24.199,1.321 -36.016,3.929 -11.785,2.608 -23.287,6.537 -34.508,11.785 l 0,-43.998 c 13.105,-3.144 25.864,-5.5 38.311,-7.072 12.445,-1.569 24.45,-2.355 36.078,-2.355 27.467,0 48.115,4.684 61.974,14.079 13.859,9.429 20.773,23.506 20.773,42.208 0,17.851 -4.902,30.986 -14.739,39.314 -9.773,8.359 -28.881,14.361 -57.26,18.039 l -9.334,1.353 c -9.585,1.193 -16.248,3.017 -19.956,5.467 -3.708,2.452 -5.562,5.972 -5.562,10.561 0,5.688 2.482,9.898 7.479,12.602 4.966,2.734 12.57,4.085 22.814,4.085 9.556,0 19.737,-1.319 30.485,-3.927 10.779,-2.609 21.936,-6.537 33.501,-11.785 l -0.002,43.995 z M 380.267,-117.16 c 0,-23.256 5.248,-40.948 15.776,-53.142 10.528,-12.162 25.833,-18.26 45.946,-18.26 11.281,0 21.652,2.545 31.05,7.668 9.396,5.092 18.259,13.012 26.649,23.759 l 0,-28.285 56.568,0 0,175.992 -56.568,0 0,-87.116 c 0,-16.06 -3.3,-28.63 -9.867,-37.648 -6.537,-9.021 -15.59,-13.515 -27.122,-13.515 -4.714,0 -8.895,1.005 -12.57,2.984 -3.614,2.012 -6.568,4.841 -8.831,8.518 -1.729,2.828 -2.954,7.386 -3.677,13.576 -0.725,6.254 -1.069,16.468 -1.069,30.643 0,4.87 0.032,14.487 0.126,28.943 0.094,14.425 0.157,26.431 0.157,35.983 l 0,17.632 -56.568,0 0,-107.732 z m -128.223,41.736 c 1.696,11.155 6.034,19.705 13.011,25.645 6.979,5.939 16.061,8.925 27.216,8.925 10.277,0 18.605,-3.174 24.985,-9.522 6.379,-6.35 9.585,-14.708 9.585,-25.048 l -74.797,0 z M 383.41,-94.029 c 0,27.592 -8.297,49.654 -24.891,66.122 -16.562,16.53 -38.654,24.764 -66.248,24.764 -30.358,0 -54.181,-8.233 -71.497,-24.764 -17.285,-16.468 -25.928,-39.127 -25.928,-67.945 0,-29.32 8.769,-52.105 26.272,-68.353 17.506,-16.248 42.051,-24.355 73.666,-24.355 13.168,0 26.366,1.318 39.565,3.991 13.23,2.64 26.432,6.536 39.63,11.722 l 0,43.997 c -13.043,-7.384 -25.708,-12.917 -38.059,-16.562 -12.352,-3.613 -24.419,-5.438 -36.172,-5.438 -14.614,0 -25.99,3.395 -34.13,10.214 -8.14,6.82 -12.853,17.033 -14.205,30.642 l 131.995,0 0,15.965 0.002,0 z\" /></g></g></g></g></svg>";
  write(fd, secondpart, strlen(secondpart));
}

int main(void)
{
    print("Starting Zeus In Numereous CPU's\n");
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    int yes = 1;
    setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

    struct sockaddr_in listen_addr;
    listen_addr.sin_family = AF_INET;
    listen_addr.sin_port = 0x8888; // port 34952 
    listen_addr.sin_addr.s_addr = 0; // host 0.0.0.0, so all interfaces
    bind(socketfd, (struct sockaddr *)&listen_addr, sizeof(listen_addr));

    int listenfd = listen(socketfd, 5); // accept max 5 connections at once

    while(1) {
        struct sockaddr_storage their_addr;
        socklen_t addrlen = sizeof(their_addr);
        int acceptfd = accept(socketfd, (struct sockaddr *)&their_addr, &addrlen);
        if (acceptfd == -1) {
            print("accept failed");
            continue;
        }

        if (!fork()) { // this is the child process
            close(socketfd); // child doesn't need the listener
            respond(acceptfd);
            close(acceptfd);
            _exit(0);
        }
        close(acceptfd);  // parent doesn't need this
    }
    _exit(0);
}
