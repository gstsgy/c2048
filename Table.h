//
// Created by gstsgy on 2022/6/15.
//

#ifndef C2048_TABLE_H
#define C2048_TABLE_H

typedef struct Node *Node;
typedef struct Table *Table;
typedef enum Direction Direction;
enum Direction {
    LEFT, RIGHT, UP, DOWN
};
struct Node {
    int val;
    int isTransform;
    Node left;
    Node right;
    Node up;
    Node down;
};
struct Table {
    Node root;
    Node last;
    Direction direction;
};
Table init();
Node get(Table table,unsigned int x,unsigned int y);
void rand1(Table table);
int transform(Table table);
void show(Table table);
int isEnd(Table table);
void destroy(Table table);
#endif //C2048_TABLE_H
