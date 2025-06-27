

extern void run(void);
extern void scheduler_start(void);
extern void schedler_init(void);

int mm = 300;
int nn;

int main(void) {
    int a = 20;
    int b = 30;
    b = mm;
    b = nn;
    schedler_init();
    scheduler_start();
    run();
    return 0;
}

void run(void) {
    // This function is intentionally left empty.
    // It serves as a placeholder for potential future functionality.
    int b = 60;
    while (1)
        ;
}