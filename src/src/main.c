

extern void scheduler_start(void);
extern void schedler_init(void);


int main(void) {
    schedler_init();
    scheduler_start();
    while (1) {
        ;
    }
    return 0;
}