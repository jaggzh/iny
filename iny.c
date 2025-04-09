#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <fcntl.h>

void usage(const char *progname) {
	fprintf(stderr,
		"Usage: %s [-t SECONDS] [-f FD]\n"
		"  -t, --timeout-s SECONDS   Timeout in seconds (can be fractional). Default: 0 (non-blocking)\n"
		"  -f, --fd FD               File descriptor to check. Default: 0 (stdin)\n"
		"  -v                        Increment verbosity\n",
		"  -h, --help                Show this help message\n",
		progname
	);
}

int is_valid_float(const char *s) {
	char *endptr;
	strtod(s, &endptr);
	return (s[0] != '\0' && *endptr == '\0');
}

int is_fd_valid(int fd) {
	return fcntl(fd, F_GETFL) != -1 || errno != EBADF;
}

int main(int argc, char *argv[]) {
	int fd         = 0;
	int timeout_ms = 0;
	int verbose    = 0;

	for (int i = 1; i < argc; ++i) {
		if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help")) {
			usage(argv[0]);
			return 0;
		} else if (!strcmp(argv[i], "-v")) {
			verbose++;
		} else if ((!strcmp(argv[i], "-t") || !strcmp(argv[i], "--timeout-s")) && i + 1 < argc) {
			if (!is_valid_float(argv[i + 1])) {
				fprintf(stderr, "Invalid timeout value: %s\n", argv[i + 1]);
				return 2;
			}
			timeout_ms = (int)(atof(argv[++i]) * 1000.0);
		} else if ((!strcmp(argv[i], "-f") || !strcmp(argv[i], "--fd")) && i + 1 < argc) {
			fd = atoi(argv[++i]);
			if (!is_fd_valid(fd)) {
				fprintf(stderr, "Invalid file descriptor: %d\n", fd);
				return 2;
			}
		} else {
			fprintf(stderr, "Unknown or incomplete argument: %s\n", argv[i]);
			usage(argv[0]);
			return 2;
		}
	}

	struct pollfd pfd = { .fd = fd, .events = POLLIN };

	int ret = poll(&pfd, 1, timeout_ms);

	if (verbose) {
		fprintf(stderr, "POLLIN: %d\n", pfd.revents & POLLIN);
		fprintf(stderr, "POLLHUP (unused): %d\n", pfd.revents & POLLHUP);
	}
	if (ret > 0) {
		if (pfd.revents & POLLIN) return 0;
		else return 1;
	} else {
		return 1;
	}
}
