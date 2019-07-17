#include <stdio.h>

int is_cmov_aval(void) {
    // Test if the CPU supports `cmov` (Conditional move and FCMOV instructions)
    register int truth;
    __asm__ (
        "movl $0x01,%%eax;"
        "cpuid;"
        "andl $0b00000000000000001000000000000000,%%edx;"
        "sarl $15,%%edx;"
        "movl %%edx,%0;"
        : "=r" ( truth )  // Output C variable
    );
    return truth;
}
int is_sse3_aval(void) {
    // Test if the CPU supports `sse3` (Prescott New Instructions-SSE3 (PNI))
    register int truth;
    __asm__ (
        "movl $0x01,%%eax;"
        "cpuid;"
        "andl $0b00000000000000000000000000000001,%%edx;"
        "movl %%edx,%0;"
        : "=r" ( truth )  // Output C variable
    );
    return truth;
}

signed int get_cpu_stepping(void) {
    // Get the stepping value of the CPU
    register signed int stepping;
    __asm__ (
        "movl $0x01,%%eax;"
        "cpuid;"
        "andl $0b00000000000000000000000000001111,%%eax;"
        "movl %%eax,%0;"
        : "=r" ( stepping )  // Output C variable
    );
    return stepping;
}

int is_pse_aval(void) {
    // Test if the CPU supports `pse` (Page Size Extension)
    register int truth;
    __asm__ (
        "movl $0x01,%%eax;"
        "cpuid;"
        "andl $0b00000000000000000000000000001000,%%edx;"
        "sarl $3,%%edx;"
        "movl %%edx,%0;"
        : "=r" ( truth )  // Output C variable
    );
    return truth;
}

int is_fpu_aval(void) {
    // Test if the CPU supports `fpu`
    register int truth;
    __asm__ (
        "movl $0x01,%%eax;"
        "cpuid;"
        "andl $0b00000000000000000000000000000001,%%edx;"
        "movl %%edx,%0;"
        : "=r" ( truth )  // Output C variable
    );
    return truth;
}

int is_sse_aval(void) {
    // Test if the CPU supports `pse` (Page Size Extension)
    register int truth;
    __asm__ (
        "movl $0x01,%%eax;"
        "cpuid;"
        "andl $0b00000010000000000000000000000000,%%edx;"
        "sarl $25,%%edx;"
        "movl %%edx,%0;"
        : "=r" ( truth )  // Output C variable
    );
    return truth;
}
int is_sse2_aval(void) {
    // Test if the CPU supports `pse` (Page Size Extension)
    register int truth;
    __asm__ (
        "movl $0x01,%%eax;"
        "cpuid;"
        "andl $0b00000100000000000000000000000000,%%edx;"
        "sarl $26,%%edx;"
        "movl %%edx,%0;"
        : "=r" ( truth )  // Output C variable
    );
    return truth;
}
int is_ss_aval(void) {
    // Test if the CPU supports `pse` (Page Size Extension)
    register int truth;
    __asm__ (
        "movl $0x01,%%eax;"
        "cpuid;"
        "andl $0b00001000000000000000000000000000,%%edx;"
        "sarl $27,%%edx;"
        "movl %%edx,%0;"
        : "=r" ( truth )  // Output C variable
    );
    return truth;
}

int is_tm_aval(void) {
    // Test if the CPU supports `pse` (Page Size Extension)
    register int truth;
    __asm__ (
        "movl $0x01,%%eax;"
        "cpuid;"
        "andl $0b00100000000000000000000000000000,%%edx;"
        "sarl $29,%%edx;"
        "movl %%edx,%0;"
        : "=r" ( truth )  // Output C variable
    );
    return truth;
}
int is_mmx_aval(void) {
    // Test if the CPU supports `pse` (Page Size Extension)
    register int truth;
    __asm__ (
        "movl $0x01,%%eax;"
        "cpuid;"
        "andl $0b00000000100000000000000000000000,%%edx;"
        "sarl $23,%%edx;"
        "movl %%edx,%0;"
        : "=r" ( truth )  // Output C variable
    );
    return truth;
}

int main(void)
{
	int op, eax, ebx, ecx, edx, i;

	op = 0;
	__asm__("cpuid" \
			: "=a"(eax), \
			"=b"(ebx), \
			"=c"(ecx), \
			"=d"(edx) \
			: "0"(op));
	printf("Vendor ID: ");
    printf("%c%c%c%c", eax & 0xff, (eax >> 8) & 0xff, (eax >> 16) & 0xff,
           (eax >> 24) & 0xff);
	printf("%c%c%c%c", ebx & 0xff, (ebx >> 8) & 0xff, (ebx >> 16) & 0xff,
			(ebx >> 24) & 0xff);
	printf("%c%c%c%c", edx & 0xff, (edx >> 8) & 0xff, (edx >> 16) & 0xff,
			(edx >> 24) & 0xff);
	printf("%c%c%c%c", ecx & 0xff, (ecx >> 8) & 0xff, (ecx >> 16) & 0xff,
			(ecx >> 24) & 0xff);
	printf("\n");

	printf("Processor brand: ");
	for(op = 0x80000002; op < 0x80000005; op++) {
 		__asm__("cpuid" \
 				: "=a"(eax), \
 				"=b"(ebx), \
 				"=c"(ecx), \
 				"=d"(edx) \
 				: "0"(op));
 		printf("%c%c%c%c", eax & 0xff, (eax >> 8) & 0xff, (eax >> 16) & 0xff,
				(eax >> 24) & 0xff);
		printf("%c%c%c%c", ebx & 0xff, (ebx >> 8) & 0xff, (ebx >> 16) & 0xff,
				(ebx >> 24) & 0xff);
		printf("%c%c%c%c", ecx & 0xff, (ecx >> 8) & 0xff, (ecx >> 16) & 0xff,
				(ecx >> 24) & 0xff);
		printf("%c%c%c%c", edx & 0xff, (edx >> 8) & 0xff, (edx >> 16) & 0xff,
				(edx >> 24) & 0xff);
	}
	printf("\n");

printf("\n");
printf("Test if the CPU Supports SSE1 %d\n", is_sse_aval());
printf("Test if the CPU Supports SSE2 %d\n", is_sse2_aval());
printf("Test if the CPU Supports SSE3 %d\n", is_sse3_aval());
printf("Test if the CPU Supports Self-Snoop %d\n", is_ss_aval());
printf("Test if the CPU Supports TM %d\n", is_tm_aval());
printf("Test if the CPU Supports MMX %d\n", is_mmx_aval());
printf("Test if the CPU Supports CMOV %d\n",is_cmov_aval());
printf("Test if the CPU supports PSE %d\n",is_pse_aval());
printf("Test if the x86 CPU has a FPU %d\n",is_fpu_aval());
printf("Get CPU Stepping %d\n", get_cpu_stepping());
return 0;
}