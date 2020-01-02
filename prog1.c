void main(void) {
    int number;
    int result;

    result = 1;
    number = input();

    while (number > 0) {
        result = number * number;
        number = number - 1;
    }
    output(result);
}
