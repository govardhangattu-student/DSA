#include <stdio.h>
#include <string.h>

#define DAYS 30

struct Member {
    char name[50];
    int steps[DAYS];
};

void analyzeSteps(struct Member members[], int n) {
    for (int i = 0; i < n; i++) {
        int count = 0;
        int maxSteps = 0;
        for (int j = 0; j < DAYS; j++) {
            if (members[i].steps[j] > 10000)
                count++;
            if (members[i].steps[j] > maxSteps)
                maxSteps = members[i].steps[j];
        }
        printf("Member: %s\n", members[i].name);
        printf("Days exceeded 10000 steps: %d\n", count);
        printf("Maximum steps in month: %d\n\n", maxSteps);
    }
}

int main() {
    struct Member members[2] = {
        {"Tanzeel", {12000, 9000, 15000, 8000, 11000, 7000, 5000, 13000, 10000, 9000,
                     11000, 12000, 8000, 7000, 10000, 15000, 9000, 8500, 9500, 10500,
                     11000, 12000, 13000, 14000, 12500, 13500, 14500, 15000, 15500, 16000}},
        {"oman", {5000, 6000, 7000, 8000, 9000, 10000, 11000, 12000, 13000, 14000,
                 9000, 8000, 7000, 6000, 5000, 4000, 3000, 2000, 1000, 5000,
                 6000, 7000, 8000, 9000, 10000, 11000, 12000, 13000, 14000, 15000}}
    };
    
    analyzeSteps(members, 2);
    return 0;
}
