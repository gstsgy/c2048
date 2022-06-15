#include <stdio.h>
#include "Table.h"

int charIsLegal(char c);

int main() {
    Table table = init();
    rand1(table);
    table->direction = DOWN;
    int score = 0;
    while (1) {
        // 清屏
        char c;
        printf("------------c语言2048(版权所有--追寻)-----------\n");
        printf("------------------分 数： %d-------------------\n", score);
        show(table);
        printf("--输入0退出游戏，输入 2468或者wasd进行操作---------\n");
        while (1) {
            scanf(" %c", &c);
            if (charIsLegal(c)) {
                if (c == '2' || c == 's' || c == 'S') {
                    table->direction = DOWN;
                }
                if (c == '8' || c == 'w' || c == 'W') {
                    table->direction = UP;
                }
                if (c == 'A' || c == '4' || c == 'a') {
                    table->direction = LEFT;
                }
                if (c == '6' || c == 'D' || c == 'd') {
                    table->direction = RIGHT;
                }

                break;
            }
        }

        if (c == '0') {
            break;
        }
        int tmp = transform(table);
        score += tmp;
        if (isEnd(table)) {
            if (tmp > 0) {
                rand1(table);
            }
        } else {
            printf("--游戏结束，请重新开始---------\n");
            break;
        }

    }
    destroy(table);
    return 0;
}

int charIsLegal(char c) {
    if (c == '2' || c == '4' || c == '6' || c == '8' || c == 'w' || c == 'a' || c == 's' || c == 'd' || c == '0'
        || c == 'W' || c == 'A' || c == 'S' || c == 'D') {
        return 1;
    }
    return 0;
}