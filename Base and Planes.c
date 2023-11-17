// Carlyon Jones-Armour 620157742

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

int p1[2];
int fuelTank = 100;


void death(int id){
    printf("SoS! Plane %d is going to crash", id);
    exit(0);
}

int launch () {
    return fork();

}

int planeAdder (int num){
    num = num + 1;
    return num;
}



int inIdgetter(){
    int id;
    printf("enter Id");
    scanf(" %d", &id);
    fflush(stdout); 
    return id;

}




int spentFuel(int id, int fuel) {
    fuelTank = fuelTank - 5;
    if (fuelTank <= 0){
        death(id);
        return 0;

    }
    
    return 1;
}

int updateMessage(int id, int fuel){
    printf("Bomber %d to base, #%d of fuel left \n", id, fuel) ;
    return 1;
}



int childAwayMsg(int id){
    printf("Bomber %d to base, bombs away!", id);
    return 1;
}

void signalHandler(int signum) {
    printf("!0000000000000000000000");
    int x;
    if (signum == SIGUSR1) {
        close(p1[1]);
    
        if (read(p1[0], &x, sizeof(x)) == -1)
        {printf("bom");}
        if (getpid() == x){
            printf("Bomber %d to base, bombs away!", getpid());

        }
        close(p1[0]);
        // Handle the signal or perform some action
    } else if (signum == SIGUSR2){
        
        close(p1[1]);
        if (read(p1[0], &x, sizeof(x)) == -1)
        {printf("bom");}
        printf("0000000000000000000000%d", x);

        if (getpid() == x){
            
            fuelTank = 100;
            printf("Plane %d has been refueled", getpid());

        }
        close(p1[0]);



    }
}


int cildRunnging (int childPid) {
        int status;
        pid_t result = waitpid(childPid, &status, WNOHANG);

        if (result == 0) {
            printf("Child process is still running.\n");
        } else if (result == -1) {
            perror("waitpid");
            return 1;
        } else {
            printf("Child process has exited with status: %d\n", status);
        }
}

int decider (char key, int num) {
    switch (key) {
        case 'l':
            return launch();
            break;
        case 'r':
            if (num > 0) {
                
                int x = inIdgetter();

                close(p1[0]);
                
                if (write(p1[1], &x, sizeof(x)) == -1) 
                {return 8;}
                close(p1[1]);


                kill(x, SIGUSR2);
                printf("000000000000000000000022222222");

            } else {
                printf("No planes are flying, caln t drop a bomb!");
            }

            break;
        case 'b':
            if (num > 0) {
                int x = inIdgetter();
                close(p1[0]);
                if (write(p1[1], &x, sizeof(x)) == -1) 
                {return 8;}
                
                close(p1[1]);
                kill(x, SIGUSR1);
                printf("000000000000000000000022222222");

            } else {
                printf("No planes are flying, can t drop a bomb!");
            }

            break;
        case 'q':
        
            return 99;
            break;
        default:
            
            printf("Invalid choice.\n");
            return 4;

    }

    return 1;

}

int main (){
    if (pipe(p1) == -1) {
        printf("sds0000000000000000000");
        return 9;
        }


    char userInput;
    char serInput;
    int decideCecker;
    int planeFork = 1;
    int planeNum = 0;  
    int i = 20;
    

     // C => P


    // Prompt the user for input
 

    //parent/base code
    do {
        printf("Enter a command l,r,b or q: ");
        scanf(" %c", &userInput);



        if(userInput == 'l'){
            planeNum = planeNum + 1;
        }

        decideCecker = decider(userInput, planeNum);

        //child/plane code
        if (decideCecker == 0){
            
            struct sigaction sa = { 0 };
            sa.sa_flags=  SA_RESTART;
            sa.sa_handler = &signalHandler;
            sigaction(SIGUSR2, &sa, NULL);
            
            while (i > 0)
            {
                i = i - 1;
                sleep(1);
                spentFuel(getpid(), fuelTank);
                sleep(1);
                spentFuel(getpid(), fuelTank);
                sleep(1);
                spentFuel(getpid(), fuelTank);
                updateMessage(getpid(), fuelTank);
                fflush(stdout); 

            }



        }








    } while (decideCecker != 99);


    

}
