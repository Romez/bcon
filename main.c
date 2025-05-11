#include <stdio.h>
#include <stdint.h>
// #include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// Kilobytes, Megabytes, Gigabytes
// B, KiB, MiB, GiB, TiB, PiB, , EiB

#define BYTE_IN_KIB 1024
#define BYTE_IN_MIB (1024 * 1024)

typedef enum {
    Byte,
    KiB,
    MiB
} unit_t; 

uint64_t parse_num(char* s) {    
    uint64_t result = 0;

    for (size_t i = 0; '0' <= s[i] && s[i] <= '9'; i++) {
	result *= 10;
	result += s[i] - '0';
    }

    return result;
}

unit_t parse_unit(char* s) {
    if (strncmp(s, "B", 1) == 0) {
	return Byte;
    } else if (strncmp(s, "KiB", 3) == 0) {
	return KiB;
    } else if (strncmp(s, "MiB", 3) == 0) {
	return MiB;
    } else {
	fprintf(stderr, "Unknown unit: %s\n", s);
	exit(1);
    }
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
	printf("Usage: bcon 1 B MiB\n");
	exit(1);
    }
    
    // char* from_s_size = "1";
    // char* from_s_unit = "B";
    //char* to_s_uint = "MiB";

    uint64_t unit_size = parse_num(argv[1]);
    unit_t src_unit = parse_unit(argv[2]);
    unit_t dest_unit = parse_unit(argv[3]);
    
    printf("Unit Size: %lld\n", unit_size);

    if (src_unit == Byte) {
	if (dest_unit == KiB) {
	    double result = (double)unit_size / BYTE_IN_KIB;
	    printf("%lld Bytes = %lf KiB\n", unit_size, result);
	    exit(0);
	} else if (dest_unit == MiB) {
	    double result = (double)unit_size / BYTE_IN_MIB;
	    printf("%lld Bytes = %lf MiB\n", unit_size, result);
	    exit(0);
	} else {
	    fprintf(stderr, "Unit %s is not supported\n", argv[3]);
	    exit(1);
	}
    } else {
	fprintf(stderr, "Unit %s is not supported\n", argv[2]);
	exit(1);
    }

    assert(NULL && "Unreachable");
    
    return 0;
}
