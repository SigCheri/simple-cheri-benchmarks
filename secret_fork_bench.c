#include<machine/riscvreg.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include<stdio.h>
#include<stdint.h>
#include<assert.h>

typedef struct secret_buffer {
    uint64_t secret_buffer[2];
} secret_t;

uint64_t load_secret(secret_t secret){
    uint64_t low = dec_low_skey(secret.secret_buffer[0], &secret.secret_buffer[0]);
    uint64_t high = dec_high_skey(secret.secret_buffer[1], &secret.secret_buffer[1]);
    return high | low;
}

secret_t store_secret(uint64_t text){
    secret_t sb;
    sb.secret_buffer[0] = enc_low_skey(text, &sb.secret_buffer[0]);
    sb.secret_buffer[1] = enc_high_skey(text, &sb.secret_buffer[1]);
    return sb;
}

int main(){
    uint64_t text = 0x12345678deadbeef;
    secret_t sb = store_secret(text);
    printf("secret value: 0x%lx 0x%lx\n", sb.secret_buffer[0], sb.secret_buffer[1]);
    
    pid_t pid = fork();
    if(pid == 0){
        // child
        for(int i=0; i<10; i++){
            uint64_t child_recovered = load_secret(sb);
            assert(child_recovered == text);
            printf("Child recovered secret: 0x%lx\n", child_recovered);
            sleep(1);
        }
    }else if(pid > 0){
        // parent
        for(int i=0; i<10; i++){
            uint64_t parent_recovered = load_secret(sb);
            assert(parent_recovered == text);
            printf("Parent recovered secret: 0x%lx\n", parent_recovered);
            sleep(1);
        }
        int status;
        waitpid(pid, &status, 0);
    }else{
        perror("fork failed");
        return 1;
    }
}