int main(void) {
    int average_array[5];
    int size;
    int index;
    int sum;
    size = 5;
    index = 0;
    sum = 0;
    average_array[0] = 10;
    average_array[1] = 20;
    average_array[2] = 30;
    average_array[3] = 40;
    average_array[4] = 50;
    
    while( index < size ) {
        sum = sum + average_array[index];
        index = index + 1;
    }
    sum = sum / size;

    output(sum);
}
