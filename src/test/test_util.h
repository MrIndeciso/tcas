#ifndef TEST_UTIL_H
#define TEST_UTIL_H

#define result(A) if (A) psuccess(__func__); else perror(__func__)

void psuccess(const char *msg);

void perror(const char *msg);

#endif
