#include <stdio.h>
#include <signal.h>
#include <unistd.h>

// Hàm xử lý tín hiệu SIGINT
void signalHandler(int signal) {
    printf("Signal SIGINT received.\n");
}

int main() {
    // Đăng ký hàm xử lý tín hiệu SIGINT
    signal(SIGINT, signalHandler);

    printf("Program is running. Press Ctrl+C to send SIGINT.\n");

    // Vòng lặp vô hạn để giữ chương trình chạy
    while(1) {
        sleep(1);
    }

    return 0;
}
