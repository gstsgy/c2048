//
// Created by gstsgy on 2022/6/15.
//
#include "Table.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

Node newNode(int val) {
    Node node = (Node) (Node *) malloc(sizeof(struct Node));
    node->right = NULL;
    node->left = NULL;
    node->up = NULL;
    node->down = NULL;
    node->val = val;
    node->isTransform = 0;
    return node;
}

Table init() {
    int VAL = 0;
    Table table = (Table) (Table *) malloc(sizeof(struct Table));
    table->direction = RIGHT;
    table->root = NULL;
    table->last = NULL;
    Node curlRow = table->root;
    for (int i = 0; i < 4; i++) {
        // 先创建一行
        Node row = newNode(VAL);
        // 获取当前行
        if (curlRow == NULL) {
            curlRow = row;
            table->root = curlRow;
        } else {
            curlRow->down = row;
            row->up = curlRow;
        }
        Node curlColumn = row;
        for (int j = 0; j < 3; j++) {
            //创建一列
            Node column = newNode(VAL);
            curlColumn->right = column;
            column->left = curlColumn;
            // 下次当前列为最新列
            curlColumn = column;
            if (i == 3 && j == 2) {
                table->last = column;
            }
        }
        // 下次当前行为最新行
        curlRow = row;
    }

    // 剩余链 的关联
    for (int i = 2; i < 5; i++) {
        Node top = get(table, 1, i);
        for (int j = 2; j < 5; j++) {
            Node tmp = get(table, j, i);
            top->down = tmp;
            tmp->up = top;
            top = tmp;
        }
    }
    return table;
}

Node get(Table table, unsigned int x, unsigned int y) {
    if (x > 4 || y > 4) {
        return NULL;
    }
    int indexX = 1;
    int indexY = 1;

    Node tmp = table->root;
    while (indexX < x) {
        tmp = tmp->down;
        indexX++;
    }
    while (indexY < y) {
        tmp = tmp->right;
        indexY++;
    }
    return tmp;
}

void rand1(Table table) {
    srand((unsigned) time(NULL));
    while (1) {
        int x = rand() % 4 + 1;
        int y = rand() % 4 + 1;
        Node node = get(table, x, y);
        if (node->val == 0) {
            node->val = (rand() % 2 + 1) * 2;
            break;
        }
    }
}

void show(Table table) {
    Node curlRow = table->root;
    while (curlRow) {
        Node curlColumn = curlRow;
        printf("\t");

        while (curlColumn) {
            printf("%d\t", curlColumn->val);
            curlColumn = curlColumn->right;
        }
        printf("\n");
        curlRow = curlRow->down;
    }
}

int transform(Table table) {
    int score = 0;
    Node curlRow = table->last;
    if (table->direction == UP || table->direction == LEFT) {
        curlRow = table->root;
    }
    while (curlRow) {
        // 去 0
        Node curlColumn = curlRow;
        while (curlColumn) {
            if (curlColumn->val == 0) {
                Node tmp = table->direction == UP ? curlColumn->down : table->direction == LEFT ? curlColumn->right :
                                                                       table->direction == RIGHT ? curlColumn->left
                                                                                                 : curlColumn->up;
                while (tmp) {
                    if (tmp->val != 0) {
                        score += 2;
                        curlColumn->val = tmp->val;
                        tmp->val = 0;
                        break;
                    }
                    tmp = table->direction == UP ? tmp->down : table->direction == LEFT ? tmp->right :
                                                               table->direction == RIGHT ? tmp->left : tmp->up;
                }
            }
            curlColumn = table->direction == UP ? curlColumn->down : table->direction == LEFT ? curlColumn->right :
                                                                     table->direction == RIGHT ? curlColumn->left
                                                                                               : curlColumn->up;
        }


        // 合并
        curlColumn = curlRow;
        while (curlColumn) {
            Node tmp = table->direction == UP ? curlColumn->down : table->direction == LEFT ? curlColumn->right :
                                                                   table->direction == RIGHT ? curlColumn->left
                                                                                             : curlColumn->up;

            if (tmp == NULL) {
                break;
            }
            if (curlColumn->val == tmp->val) {
                curlColumn->val = curlColumn->val * 2;
                score += (curlColumn->val*2);
                tmp->val = 0;
                curlColumn =
                        table->direction == UP ? tmp->down : table->direction == LEFT ? tmp->right : table->direction ==
                                                                                                     RIGHT ? tmp->left
                                                                                                           : tmp->up;
            } else {
                curlColumn = tmp;
            }
        }

        // 再去 0
        curlColumn = curlRow;
        while (curlColumn) {
            if (curlColumn->val == 0) {
                Node tmp = table->direction == UP ? curlColumn->down : table->direction == LEFT ? curlColumn->right :
                                                                       table->direction == RIGHT ? curlColumn->left
                                                                                                 : curlColumn->up;
                while (tmp) {
                    if (tmp->val != 0) {
                        score += 2;
                        curlColumn->val = tmp->val;
                        tmp->val = 0;
                        break;
                    }
                    tmp = table->direction == UP ? tmp->down : table->direction == LEFT ? tmp->right :
                                                               table->direction == RIGHT ? tmp->left : tmp->up;
                }
            }
            curlColumn = table->direction == UP ? curlColumn->down : table->direction == LEFT ? curlColumn->right :
                                                                     table->direction == RIGHT ? curlColumn->left
                                                                                               : curlColumn->up;
        }
        if (table->direction == DOWN) {
            curlRow = curlRow->left;
        }
        if (table->direction == UP) {
            curlRow = curlRow->right;
        }
        if (table->direction == RIGHT) {
            curlRow = curlRow->up;
        }
        if (table->direction == LEFT) {
            curlRow = curlRow->down;
        }
    }
    return score;
}

int isEnd(Table table) {
    int i = 0;
    Node curlRow = table->root;
    while (curlRow) {
        Node curlColumn = curlRow;


        while (curlColumn) {
            if (curlColumn->val == 0) {
                i = 1;
                break;
            }
            curlColumn = curlColumn->right;
        }
        if (i == 1) {
            break;
        }

        curlRow = curlRow->down;
    }
    return i;
}

void destroy(Table table) {
    Node curlRow = table->root;
    while (curlRow) {
        Node curlColumn = curlRow;
        Node tmp = curlColumn;
        while (curlColumn) {
            curlColumn = curlColumn->right;
            free(tmp);
            tmp = curlColumn;
        }
        curlRow = curlRow->down;
    }
    free(table);
}