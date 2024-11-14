#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "flatorte.h"

#pragma region CREATE

sfConvexShape* flt_CreateConvex(sfVector2f* points, int pointCount, sfColor color, float posX, float posY) {
    sfConvexShape* convex = sfConvexShape_create();
    sfConvexShape_setPointCount(convex, pointCount);

    for (int i = 0; i < pointCount; i++) {
        sfConvexShape_setPoint(convex, i, points[i]);
    }

    sfConvexShape_setPosition(convex, (sfVector2f) { posX, posY });
    sfConvexShape_setFillColor(convex, color);

    return convex;
}

sfCircleShape* flt_CreateCircle(float radius, sfColor color, float posX, float posY) {
    sfCircleShape* circle = sfCircleShape_create();
    sfCircleShape_setRadius(circle, radius);
    sfCircleShape_setPosition(circle, (sfVector2f) { posX, posY });
    sfCircleShape_setFillColor(circle, color);
    return circle;
}

sfRectangleShape* flt_CreateRectangle(float width, float height, sfColor color, float posX, float posY) {
    sfRectangleShape* rectangle = sfRectangleShape_create();
    sfRectangleShape_setSize(rectangle, (sfVector2f) { width, height });
    sfRectangleShape_setPosition(rectangle, (sfVector2f) { posX, posY });
    sfRectangleShape_setFillColor(rectangle, color);
    return rectangle;
}

sfRenderWindow* flt_CreateWindow(const char* titre, int largeur, int hauteur, int qualite_graphique)
{
    if (qualite_graphique <= 0) {
        qualite_graphique = 32;
    }

    sfVideoMode mode = { largeur, hauteur, qualite_graphique };
    return sfRenderWindow_create(mode, titre, sfResize | sfClose, NULL);
}

sfText* flt_CreateText(const char* texts, sfFont* font, sfColor color, int taille, float posX, float posY)
{
    if (!font) {
        return -1;
    }

    sfText* text = sfText_create();
    sfText_setString(text, texts);
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, taille);
    sfText_setFillColor(text, color);
    sfText_setPosition(text, (sfVector2f) { posX, posY });
    return text;
}

sfSprite* flt_CreateSpriteOnScreen(const sfTexture* texture, float posX, float posY, sfBool istrue) {
    if (!texture) {
        printf("Erreur lors du chargement de la texture.\n");
        return NULL;
    }

    sfSprite* sprite = sfSprite_create();
    sfSprite_setTexture(sprite, texture, istrue);
    sfSprite_setPosition(sprite, (sfVector2f) { posX, posY });

    return sprite;
}

sfSprite* flt_CreateSprite(const sfTexture* texture, sfBool istrue) {
    if (!texture) {
        printf("Erreur lors du chargement de la texture.\n");
        return NULL;
    }

    sfSprite* sprite = sfSprite_create();
    sfSprite_setTexture(sprite, texture, istrue);
    return sprite;
}

flt_Player flt_CreatePlayerRPG(char name[17], int level, int pv, int atk, int def, flt_Inventory inventory)
{
    flt_Player player;
    strncpy(player.name, name, 16);
    player.name[17] = '\0';
    player.level = level;
    player.pv = pv;
    player.atk = atk;
    player.def = def;
    player.inventaire = inventory;

    return player; 
}

#pragma endregion

#pragma region TIME/TOOLS

sfTime sftime;
sfClock* sfclock;

void flt_RestartClock()
{
    sftime = sfClock_restart(sfclock);
}

float flt_GetDeltaTime()
{
    return sfTime_asSeconds(sftime);
}

void flt_InitTools()
{
    sfclock = sfClock_create();
    srand(time(NULL));
}

void flt_ResizeSprite(sfSprite* sprite, const sfTexture* texture, unsigned int width, unsigned int height) {
    if (!sprite || !texture) {
        printf("Erreur : sprite ou texture est NULL.\n");
        return;
    }

    sfVector2u textureSize = sfTexture_getSize(texture);
    float scaleX = (float)width / textureSize.x;
    float scaleY = (float)height / textureSize.y;
    sfSprite_setScale(sprite, (sfVector2f) { scaleX, scaleY });
}

#pragma endregion

#pragma region INVENTORY

void flt_DebugInventory(flt_Inventory inventaire)
{
    printf("\nInventaire du joueur :\n\n");

    if (inventaire.nbItems == 0) {
        printf("L'inventaire est vide.\n");
    }
    else
    {
        for (int i = 0; i < inventaire.nbItems; i++)
        {
            flt_Item item = inventaire.items[i];
            // V�rifie si l'item a un sprite et une texture
            printf("Item %d: %s (Quantite: %d)  |  ", i + 1, item.name, item.quantity);

            if (item.sprite != NULL) {
                printf("Sprite: %p  |  ", (void*)item.sprite);
            }
            else
            {
                printf("Sprite: NULL  |  ");
            }

            if (item.texture != NULL) {
                printf("Texture: %p \n", (void*)item.texture);
            }
            else
            {
                printf("Texture: NULL \n");
            }
        }
    }
}

void flt_AddItem(flt_Inventory* inventaire, flt_Item item)
{
    if (inventaire->nbItems < 31)
    {
        inventaire->items[inventaire->nbItems] = item;
        inventaire->nbItems++;
    }
    else
    {
        printf("L'inventaire est plein, impossible d'ajouter plus d'items.\n");
    }
}

void flt_InitSlotGrill(flt_Slot slots[5][6], sfTexture* slotTexture, int columns, int rows, int posX, int posY, unsigned int slotWidth, unsigned int slotHeight, unsigned int spacing) {
    for (int col = 0; col < columns; col++) {
        posY = 190; // R�initialiser la position Y pour chaque colonne
        for (int row = 0; row < rows; row++) {
            slots[col][row].sprite = sfSprite_create();
            if (!slots[col][row].sprite) {
                printf("Erreur lors de la cr�ation du sprite pour le slot [%d][%d].\n", col, row);
                return; // Sortir si l'allocation �choue
            }

            sfSprite_setTexture(slots[col][row].sprite, slotTexture, sfTrue);
            slots[col][row].position = (sfVector2f){ posX, posY };
            sfSprite_setPosition(slots[col][row].sprite, slots[col][row].position);
            flt_ResizeSprite(slots[col][row].sprite, slotTexture, slotWidth, slotHeight); // Redimensionner le sprite

            slots[col][row].bounds = sfSprite_getGlobalBounds(slots[col][row].sprite);

            posY += slotHeight + spacing; // D�placer vers le bas pour le prochain slot, avec espacement
        }
        posX += slotWidth + spacing; // D�placer vers la droite pour la prochaine colonne, avec espacement
    }
}

void flt_CreateSlotsOnScreen(sfRenderWindow* window, flt_Slot slots[5][6], int columns, int rows) {
    for (int col = 0; col < columns; col++) {
        for (int row = 0; row < rows; row++) {
            sfRenderWindow_drawSprite(window, slots[col][row].sprite, NULL);
        }
    }
}

void flt_DestroySlots(flt_Slot slots[5][6], int columns, int rows) {
    for (int col = 0; col < columns; col++) {
        for (int row = 0; row < rows; row++) {
            if (slots[col][row].sprite) {
                sfSprite_destroy(slots[col][row].sprite);
                slots[col][row].sprite = NULL; // �viter d'acc�der � un pointeur invalide
            }
        }
    }
}

void flt_InitAllItems(flt_Item items[31])
{
    /* EXEMPLE:

       D'ABORD, INITIALISEZ VOS ITEMS : void flt_InitAllItems(flt_Item items[HERE_MAX_ITEMS])

       Exemple d'initialisation d'un item :

       items[0] = (flt_Item){ "SWORD", 1, 1, sfSprite_create(), sfTexture_createFromFile("IMAGE.PNG", NULL) };
       sfSprite_setTexture(items[0].sprite, items[0].texture, sfTrue);

       OU

       items[0] = (flt_Item){ "SWORD", 1, 1, flt_CreateSprite(sfTexture_createFromFile("IMAGE.PNG", NULL), sfTrue) };

       FACULTATIF :
       POUR AJOUTER UNE TEXTURE BRUTE :
       items[0].texture = sfTexture_createFromFile("images/items/epee.PNG", NULL);

    */

    // PLACEZ VOS ITEMS CI-DESSOUS :

    items[0] = (flt_Item){ "SWORD", 1, 1, flt_CreateSprite(sfTexture_createFromFile("images/items/epee.PNG", NULL),sfTrue) };
    items[0].texture = sfTexture_createFromFile("images/items/epee.PNG", NULL);
}

#pragma endregion

#pragma region INPUT

// V�rifie si le sprite est survol�
int flt_isSpriteHovered(sfSprite* sprite, sfVector2i mousePos) {
    sfFloatRect spriteBounds = sfSprite_getGlobalBounds(sprite);
    return sfFloatRect_contains(&spriteBounds, (float)mousePos.x, (float)mousePos.y);
}

int flt_isSpriteClicked(sfSprite* sprite, sfVector2i mousePos)
{
    sfFloatRect spriteBounds = sfSprite_getGlobalBounds(sprite);
    return sfFloatRect_contains(&spriteBounds, mousePos.x, mousePos.y);
}

void flt_BasicMovement(sfSprite* gameSprite, bool* keys) {
    static float animationTime = 0.0f;
    static int frameY = 0;
    static int frameX = 0;

    sfIntRect playerAnimationRect = { 0, 0, 45, 48 };
    float moveSpeed = 150.0f;
    sfVector2f position = sfSprite_getPosition(gameSprite);

    animationTime += flt_GetDeltaTime();

    if (keys[sfKeyLeft]) {
        position.x -= moveSpeed * flt_GetDeltaTime();
        frameY = 1;
    }
    else if (keys[sfKeyRight]) {
        position.x += moveSpeed * flt_GetDeltaTime();
        frameY = 2;
    }
    else if (keys[sfKeyUp]) {
        position.y -= moveSpeed * flt_GetDeltaTime();
        frameY = 3;
    }
    else if (keys[sfKeyDown]) {
        position.y += moveSpeed * flt_GetDeltaTime();
        frameY = 0;
    }
    else {
        frameX = 1;
    }

    // l'animation
    if (animationTime >= 0.1) {
        animationTime = 0.0f;
        frameX = (frameX + 1) % 3;
    }

    playerAnimationRect.left = frameX * playerAnimationRect.width;
    playerAnimationRect.top = frameY * playerAnimationRect.height;
    sfSprite_setTextureRect(gameSprite, playerAnimationRect);

    //if (position.x < 0) position.x = 0;
    //if (position.x > 1600 - 32) position.x = 1600 - 32;
    //if (position.y < 0) position.y = 0;
    //if (position.y > 900 - 48) position.y = 900 - 48;

    // Mettre � jour la position du sprite
    sfSprite_setPosition(gameSprite, position);
}

void flt_AvancedMovement(sfSprite* gameSprite, bool* keys, sfVector2f Velocity, float  moveSpeed, float accel /* normal: 1, ice = .25, sticky = .1 */, float friction /* normal: 1, ice : .05, sticky = 2 */)
{
    static float animationTime = 0.0f;
    static int frameY = 0;
    static int frameX = 0;
    sfIntRect playerAnimationRect = { 0, 0, 45, 48 };
    sfVector2f position = sfSprite_getPosition(gameSprite);

    animationTime += flt_GetDeltaTime();

    sfVector2f InputVector = { keys[sfKeyRight] - keys[sfKeyLeft], keys[sfKeyDown] - keys[sfKeyUp] };
    InputVector = flt_Normalize(InputVector);

    if (InputVector.x != 0 || InputVector.y != 0)
    {
        frameY = (InputVector.x < 0) ? 1 : ((InputVector.y < 0) ? 3 : (InputVector.y > 0) ? 0 : 2);
        Velocity.x = flt_MoveToward(Velocity.x, InputVector.x * moveSpeed, accel);
        Velocity.y = flt_MoveToward(Velocity.y, InputVector.y * moveSpeed, accel);
    }
    else
    {
        frameX = 1;
        Velocity.x = flt_MoveToward(Velocity.x, 0.f, friction);
        Velocity.y = flt_MoveToward(Velocity.y, 0.f, friction);
    }

    position.x += Velocity.x * flt_GetDeltaTime();
    position.y += Velocity.y * flt_GetDeltaTime();

    // l'animation
    if (animationTime >= 0.1) {
        animationTime = 0.0f;
        frameX = (frameX + 1) % 3;
    }

    playerAnimationRect.left = frameX * playerAnimationRect.width;
    playerAnimationRect.top = frameY * playerAnimationRect.height;
    sfSprite_setTextureRect(gameSprite, playerAnimationRect);

    if (position.x < 0) position.x = 0;
    if (position.x > 1600 - 32) position.x = 1600 - 32;
    if (position.y < 0) position.y = 0;
    if (position.y > 900 - 48) position.y = 900 - 48;

    // Mettre � jour la position du sprite
    sfSprite_setPosition(gameSprite, position);
}

sfVector2f flt_Normalize(sfVector2f v)
{
    float w = sqrt(v.x * v.x + v.y * v.y);

    if (!(w))
    {
        return v;
    }
    else
    {
        v.x /= w; v.y /= w;
        return v;
    }
}

const float flt_Sign(const float val)
{
    return val > 0 ? +1.0f : (val < 0 ? -1.0f : 0.0f);
}

float flt_MoveToward(float from, float to, float step) // step is always absolute
{
    return abs(to - from) <= step ? to : from + flt_Sign(to - from) * step;
}

#pragma endregion
