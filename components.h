typedef struct Comp {
	int prevlen;
	int pos;
	int period;
	int t;
	int sig;

	void (*init)();
	void (*update)();
	const int (*len)();
	void (*print)(char *dest);
	void (*reprint)(char *dest);
} Comp;
