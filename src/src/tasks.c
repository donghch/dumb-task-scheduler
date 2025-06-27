

void idle_task(void** args) {
    int a = 0;
    while (a < 10000) {
        a++;
    }

    while (1) {
        a = a;
    }
}

void dumb_task(void **args) {
    int b = 10;
    while (b < 10000) {
        b++;
    }
    while (1) {
        b = b;
    }
}
