#pragma once

#include <SFML/Graphics.h>
#include <stdbool.h>

#pragma region STRUCT

typedef struct flt_Slot {
    sfSprite* sprite;
    sfVector2f position;
    sfFloatRect bounds;
} flt_Slot;

typedef enum flt_WeaponType {
    EPEE = 1,
    LANCE,
    ARC,
    BATON_MAGIC,
    DAGUE
} flt_WeaponType;

// define max items : Item items[MAX_ITEMS];
typedef struct flt_Item {
    char name[21];
    int weaponType;
    int quantity;
    sfSprite* sprite;
    sfTexture* texture;
} flt_Item;

typedef struct flt_Inventory {
    flt_Item items[31];
    int nbItems;
} flt_Inventory;

typedef struct flt_Player {
    char name[17];
    int level;
    int pv;
    int atk;
    int def;
    flt_Inventory inventaire;
} flt_Player;

#pragma endregion

#pragma region CREATE

sfConvexShape* flt_CreateConvex(sfVector2f* points, int pointCount, sfColor color, float posX, float posY);
sfCircleShape* flt_CreateCircle(float radius, sfColor color, float posX, float posY);
sfRectangleShape* flt_CreateRectangle(float width, float height, sfColor color, float posX, float posY);
sfRenderWindow* flt_CreateWindow(const char* titre, int largeur, int hauteur, int qualite_graphique);
sfText* flt_CreateText(const char* texts, sfFont* font, sfColor color, int taille, float posX, float posY);
sfSprite* flt_CreateSpriteOnScreen(const sfTexture* texture, float posX, float posY, sfBool istrue);
sfSprite* flt_CreateSprite(const sfTexture* texture, sfBool istrue);
flt_Player flt_CreatePlayerRPG(char name[17], int level, int pv, int atk, int def, flt_Inventory inventory);

#pragma endregion

#pragma region TIME/TOOLS

void flt_InitTools();
void flt_RestartClock();
float flt_GetDeltaTime();
void flt_ResizeSprite(sfSprite* sprite, const sfTexture* texture, unsigned int width, unsigned int height);

#pragma endregion

#pragma region INVENTORY

void flt_DebugInventory(flt_Inventory inventaire);
void flt_AddItem(flt_Inventory* inventaire, flt_Item item);
void flt_InitAllItems(flt_Item items[31]);
void flt_InitSlotGrill(flt_Slot slots[5][6], sfTexture* slotTexture, int columns, int rows, int posX, int posY, unsigned int slotWidth, unsigned int slotHeight, unsigned int spacing);
void flt_CreateSlotsOnScreen(sfRenderWindow* window, flt_Slot slots[5][6], int columns, int rows);
void flt_DestroySlots(flt_Slot slots[5][6], int columns, int rows);


#pragma endregion

#pragma region INPUT

int flt_isSpriteHovered(sfSprite* sprite, sfVector2i mousePos);
int flt_isSpriteClicked(sfSprite* sprite, sfVector2i mousePos);
void flt_BasicMovement(sfSprite* gameSprite, bool* keys);
void flt_AvancedMovement(sfSprite* gameSprite, bool* keys, sfVector2f Velocity, float  moveSpeed, float accel /* normal: 1, ice = .25, sticky = .1 */, float friction /* normal: 1, ice : .05, sticky = 2 */);
sfVector2f flt_Normalize(sfVector2f v);
const float flt_Sign(const float val);
float flt_MoveToward(float from, float to, float step);

#pragma endregion
