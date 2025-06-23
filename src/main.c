

extern void run(void);
extern void start_timer(void);

void systick_handler(void) {
    int m = 10;
    while (m < 100)
    {
        m++;
    }
}

int main(void) {
    int a = 20;
    int b = 30;
    start_timer(); // Initialize the system timer
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