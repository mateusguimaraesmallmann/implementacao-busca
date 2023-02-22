#include <stdlib.h>
#include <stdio.h>

typedef struct t_time{
    int hour;
    int min;
    int sec;
} Time;

typedef struct t_timeTable {
    Time key;
    void *value;
    struct TimetableNode *left;
    struct TimetableNode *right;
} TimetableNode;

typedef struct Timetable {
    TimetableNode *root;
} Timetable;

int compare(Time key1, Time key2) {

    if (key1->hour != key2->hour) {
        return key1->hour - key2->hour;
    } else if (key1->min != key2->min) {
        return key1->min - key2->min;
    } else {
        return key1->sec - key2->sec;
    }
}

Timetable *createTimetable() {
    Timetable *table = (Timetable *)malloc(sizeof(Timetable));
    table->root = NULL;
    return table;
}

TimetableNode *insert(TimetableNode *root, Time key, void *value) {

    if (root == NULL) {
        TimetableNode *nova = (TimetableNode *)malloc(sizeof(TimetableNode));
        nova->key = key;
        nova->value = value;
        nova->left = NULL;
        nova->right = NULL;
        return nova;
    }

    int comparison = compare(key, root->key);

    if (comparison < 0) {
        root->left = insert(root->left, key, value);
    } else if (comparison > 0) {
        root->right = insert(root->right, key, value);
    } else {
        root->value = value;
    }

    return root;
}

void put(Timetable *table, Time key, void *value) {
    table->root = insert(table->root, key, value);
}

void *search(TimetableNode *root, Time key) {

    if (root == NULL) {
        return NULL;
    }

    int comparison = compare(key, root->key);

    if (comparison < 0) {
        return search(root->left, key);
    } else if (comparison > 0) {
        return search(root->right, key);
    } else {
        return root->value;
    }
}

void *get(Timetable *table, Time key) {
    return search(table->root, key);
}

TimetableNode *min(TimetableNode *root) {

    if (root == NULL) {
        return NULL;
    }

    while (root->left != NULL) {
        root = root->left;
    }

    return root;
}

Time firstTime(Timetable *table) {
    TimetableNode *node = min(table->root);
    return node->key;
}

TimetableNode *max(TimetableNode *root) {

    if (root == NULL) {
        return NULL;
    }

    while (root->right != NULL) {
        root = root->right;
    }

    return root;
}
