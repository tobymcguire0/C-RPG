/*By Toby McGuire*/
#ifndef ENEMY_H
#define ENEMY_H
typedef struct{
    char name[100];
    int damage;
    int maxHealth;
    int currentHealth;
    int xp;
    int gold;
} Enemy;
#endif
