int main(void) {
    int index;
    int instruction;
    int BASH_STOP;
    int check_health;

    lcd(10); /*BIOS starting*/

    check_health = input();
    check_health = check_health + 2;
    output(check_health);

    /*checks system health*/


    index = 0;

    while(index != 1024){
        instruction = lhd(index);
        smem(instruction, index);
        index = index + 1;
    }
    
    
    lcd(11); /*BIOS ending*/
    BASH_STOP = input();
    /*output(index);
    output(99);*/
}
