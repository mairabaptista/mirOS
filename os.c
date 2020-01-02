/* Global variables declaration */
int MAX_PROCESS; /*maximum number of processes*/
int MEM_SIZE; /*size of memory page*/

int BASH_STOP;

int PROCESS_QUEUE[10]; /*the queue for process swapping*/
int FILE_ID[10]; /*stores file ids*/
int FILE_MAX_SIZES[10]; /*stores the maximum size for each file*/
int PROC_PCS[10]; /*store program counters for each proc */
int STATE_PROC[10]; /*stores execution state - 1: finished, 0: ready to be executed*/


void store_proc_context(int proc_index){
    int transfer_index;   
    proc_index = proc_index + 1;
    transfer_index = proc_index * MEM_SIZE;
    store_reg( 1, transfer_index, 1 ); 
    store_reg( 2, transfer_index, 2 ); 
    store_reg( 3, transfer_index, 3 ); 
    store_reg( 4, transfer_index, 4 ); 
    store_reg( 5, transfer_index, 5 ); 
    store_reg( 6, transfer_index, 6 ); 
    store_reg( 7, transfer_index, 7 ); 
    store_reg( 8, transfer_index, 8 ); 
    store_reg( 9, transfer_index, 9 ); 
    store_reg( 10, transfer_index, 10 ); 
    store_reg( 11, transfer_index, 11 ); 
    store_reg( 12, transfer_index, 12 ); 
    store_reg( 13, transfer_index, 13 ); 
    store_reg( 14, transfer_index, 14 ); 
    store_reg( 15, transfer_index, 15 ); 
    store_reg( 16, transfer_index, 16 ); 
    store_reg( 17, transfer_index, 17 ); 
    store_reg( 18, transfer_index, 18 ); 
    store_reg( 19, transfer_index, 19 ); 
    store_reg( 20, transfer_index, 20 ); 
    store_reg( 21, transfer_index, 21 );
    store_reg( 22, transfer_index, 22 );
    store_reg( 23, transfer_index, 23 );
    store_reg( 24, transfer_index, 24 );
    store_reg( 25, transfer_index, 25 );
    store_reg( 26, transfer_index, 26 );
    store_reg( 27, transfer_index, 27 );
    store_reg( 28, transfer_index, 28 );
    store_reg( 29, transfer_index, 29 );
    store_reg( 30, transfer_index, 30 );
    store_reg( 31, transfer_index, 31 );

    /*output(69);*/

    return;
}


void load_proc_context(int proc_index){
    int transfer_iterations;
    int transfer_index;
    int instruction;
    int hd_address;


    /*output(89);*/
    transfer_iterations = FILE_MAX_SIZES[proc_index];
    transfer_index = 0;
    hd_address = MEM_SIZE * proc_index;

    output(hd_address);
    

    while( transfer_index < transfer_iterations ) {
        instruction = lhd(hd_address);
        smemproc(instruction, transfer_index);
        transfer_index = transfer_index + 1;
        hd_address= hd_address + 1;     
    }

    proc_index = proc_index + 1;
    transfer_index = proc_index * MEM_SIZE;
    load_reg( 1, transfer_index, 1 ); 
    load_reg( 2, transfer_index, 2 ); 
    load_reg( 3, transfer_index, 3 ); 
    load_reg( 4, transfer_index, 4 ); 
    load_reg( 5, transfer_index, 5 ); 
    load_reg( 6, transfer_index, 6 ); 
    load_reg( 7, transfer_index, 7 ); 
    load_reg( 8, transfer_index, 8 ); 
    load_reg( 9, transfer_index, 9 ); 
    load_reg( 10, transfer_index, 10 ); 
    load_reg( 11, transfer_index, 11 ); 
    load_reg( 12, transfer_index, 12 ); 
    load_reg( 13, transfer_index, 13 ); 
    load_reg( 14, transfer_index, 14 ); 
    load_reg( 15, transfer_index, 15 ); 
    load_reg( 16, transfer_index, 16 ); 
    load_reg( 17, transfer_index, 17 ); 
    load_reg( 18, transfer_index, 18 ); 
    load_reg( 19, transfer_index, 19 ); 
    load_reg( 20, transfer_index, 20 ); 
    load_reg( 21, transfer_index, 21 );
    load_reg( 22, transfer_index, 22 );
    load_reg( 23, transfer_index, 23 );
    load_reg( 24, transfer_index, 24 );
    load_reg( 25, transfer_index, 25 );
    load_reg( 26, transfer_index, 26 );
    load_reg( 27, transfer_index, 27 );
    load_reg( 28, transfer_index, 28 );
    load_reg( 29, transfer_index, 29 );
    load_reg( 30, transfer_index, 30 );
    load_reg( 31, transfer_index, 31 );

    

    /*output(99);

    output(123);*/
  
    return;
}


void circular_queue(int amount){
    
    int proc_ID;
    int finished_procs;
    int queue_index;
    int proc_index;
    int io_aux;
    int proc_pc;
    int INTERRUPTION;

    finished_procs = 0;
    queue_index = 0;
    proc_pc = 0;

    lcd(4); /*Running processes*/

    BASH_STOP = input();

    while (finished_procs < amount){
        /*output(12);*/
        lcd(4); /*Running processes*/
        BASH_STOP = input(); 
        
        proc_ID = PROCESS_QUEUE[queue_index];
        proc_index = proc_ID; 
        if( STATE_PROC[proc_index] == 0 ) {
            output( proc_index );
            proc_pc = PROC_PCS[proc_index];
            set_proc_pc( proc_pc );
            load_proc_context(proc_index);
            swap_process(proc_index);
            recover_os();
            /*output(70);*/
            INTERRUPTION = get_interruption();
            output(INTERRUPTION);
            PROC_PCS[proc_index] = get_proc_pc();
            
            if( INTERRUPTION == 1 ) {
                lcd(12); /*Interruption caused by sysin*/
                output(INTERRUPTION);
                io_aux = input();
                output(io_aux);
                move_OS_to_proc(io_aux); 
            }
            
            if(INTERRUPTION == 2) {
                lcd(8); /*Interruption caused by sysout*/
                output(INTERRUPTION);
                io_aux = move_proc_to_OS(); 
                output(io_aux);
            }
            
            if(INTERRUPTION == 3) {
                lcd(9); /*Interruption caused by sysend*/
                output(INTERRUPTION);
                output(proc_index);
                STATE_PROC[proc_index] = 1;
                finished_procs = finished_procs + 1;
            }
            store_proc_context(proc_index);
        }
        
        if(queue_index < amount - 1) {             
            queue_index = queue_index + 1;
        }
        else {
            queue_index = 0;
        }
    }
    lcd(5); /*All processes finished running*/
    BASH_STOP = input();

    return;
}

void reset_queue(void){
    int i;
    lcd(6); /*Queue is being reset*/
    BASH_STOP = input();
    while(i < 10){
        PROCESS_QUEUE[i] = 0;
        i = i + 1;
    }
    /*output(87);*/
    return;
}

void reset_pcs(void){
    int i;
    lcd(7); /*PCs are being reset*/
    BASH_STOP = input();
    while(i < 10){
        PROC_PCS[i] = 0;
        i = i + 1;
    }
    /*output(47);*/
    return;
}

void process_handling(void){
    int amount;
    int inqueue;
    int proc_ID;

    lcd(2); /*how many files to execute? */
    amount = input();
    output(amount);

    inqueue = 0;
    lcd(3); /*Insert file IDs*/
    while (inqueue < amount){
        proc_ID = input();
        output(proc_ID);
        PROCESS_QUEUE[inqueue] = proc_ID;
        STATE_PROC[inqueue] = 0;
        inqueue = inqueue + 1;
    }

    circular_queue(amount);
    reset_queue();
    reset_pcs();
    return;
}

void bash(void){
    int choice;

    lcd(1); /*make your choice: 1 - process*/
    choice = input();
    output(choice);
    if (choice == 1){
        process_handling();
    }
    return;
}

void init_os(void){
    int i;

    i = 0;
    MAX_PROCESS = 10;
    MEM_SIZE = 1024;

    FILE_MAX_SIZES[1] = 50;
    FILE_MAX_SIZES[2] = 50;
    FILE_MAX_SIZES[3] = 50;

    while (i < 10){
        PROCESS_QUEUE[i] = 0;
        STATE_PROC[i] = 0;
        PROC_PCS[i] = 0;
        FILE_ID[i] = i;
        i = i + 1;
    }    
    return;
}

int main(void){

    init_os();
    
    lcd(0); /***Welcome to mirOS***/

    BASH_STOP = input();

    while(1 < 2){
        bash();
    }
}
