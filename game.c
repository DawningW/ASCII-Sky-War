#include "game.h"

#if defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
#else
#include <unistd.h>
#endif

#define DEFAULT_FPS 20
#define GAME_WIDTH 60
#define GAME_HEIGHT 40
#define RESPAWN_TIME 50
#define MAX_HEALTH 100
#define MAX_ENERGY 100
#define MAX_NAME_LENGTH 16

#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))
#define randInt(a, b) a + rand() % (b - a)
static clock_t getCurrentTime();
static void mysleep(clock_t);
static void setWindowTitle(const char*);
static void openBrowser(const char*);

// 是否在运行
char running;
// 当前界面
enum Gui
{
    GUI_MENU,
    GUI_GAME,
    GUI_RANK,
    GUI_SETTINGS,
    GUI_HELP,

    GUI_PAUSE,
    GUI_SUBMIT,
    GUI_RESULT,

    GUI_COUNT
} gui;
// 界面所对应的函数
void (*guiupdaters[GUI_COUNT])();
// 帧率
int fps;
// 当前帧
long frame;
// 选中的按钮
char button;
// 游戏的难度
char difficulty;
// 游戏的得分
int score;
// 玩家
struct
{
    // 飞机的字符画
    struct StrObject* obj;
    // 飞机的坐标
    int x;
    int y;
    // 飞机的等级
    short level;
    // 飞机的血量
    short health;
    // 飞机的能量
    short energy;
    // 飞机的必杀
    char skill;
    // 飞机必杀技动画
    struct StrObject* animation;
    // 飞机必杀技的帧计时器
    long timer;
} player;
// 敌机
struct
{
    struct StrObject* obj;
    int x;
    int y;
    int countdown;
} planes[16];
// BOSS
struct
{
    struct StrObject* obj;
    int x;
    int y;
    struct StrObject* animation;
    long timer;
} boss;
// 子弹 (0空, |玩家的子弹(只会向上), o敌机的子弹(只会向下))
char bullets[GAME_HEIGHT][GAME_WIDTH]; // 先y后x哦
// 道具 ($钱(加分), L升级, X必杀)
char items[GAME_HEIGHT][GAME_WIDTH];
// 玩家名
char playername[MAX_NAME_LENGTH + 1]; // 末尾有'\0'
// 后端返回的玩家提交id
int playerid;
// 玩家该次提交的数据
cJSON* playerdata;

// 排行榜
cJSON* rank;

static void openGui(enum Gui id)
{
    if (gui == GUI_RANK) cJSON_Delete(rank);
    else if (gui == GUI_RESULT) cJSON_Delete(playerdata);
    gui = id;
    fps = DEFAULT_FPS;
    frame = 0;
    button = 0;
    if (id == GUI_GAME)
    {
        srand((unsigned) time(NULL));
        difficulty = 0;
        score = 0;
        player.obj = res_get(PLANE);
        player.x = GAME_WIDTH / 2;
        player.y = GAME_HEIGHT - player.obj->height / 2;
        player.level = 1;
        player.health = MAX_HEALTH;
        player.energy = MAX_ENERGY / 2;
        player.skill = 0;
        player.animation = NULL;
        player.timer = frame;
        struct StrObject* obj = res_get(PLANE2);
        for (int i = 0; i < length(planes); ++i)
        {
            planes[i].obj = obj;
            planes[i].x = 0;
            planes[i].y = 0;
            planes[i].countdown = 20 + i * 30;
        }
        boss.obj = NULL;
        boss.x = 0;
        boss.y = 0;
        boss.animation = NULL;
        boss.timer = frame;
        memset(bullets, ' ', GAME_WIDTH * GAME_HEIGHT);
        memset(items, ' ', GAME_WIDTH * GAME_HEIGHT);
        memset(playername, '\0', MAX_NAME_LENGTH + 1);
        playerid = -1;
        playerdata = NULL;
    }
    else if (id == GUI_RANK)
    {
        char* content = util_httpget(res_get(WEBSITE)->str[0]);
        rank = cJSON_Parse(content);
        free(content);
    }
    else if (id == GUI_RESULT)
    {
        if (playerid >= 0)
        {
            char url[50];
            strcpy(url, res_get(WEBSITE)->str[0]);
            sprintf(url + strlen(url), "?id=%d", playerid);
            char* str = util_httpget(url);
            playerdata = cJSON_Parse(str);
            free(str);
            if (playerdata != NULL && cJSON_IsArray(playerdata)) return;
        }
        gui = GUI_MENU;
    }
}

static void updateMenu(char size)
{
    if (key.down == 1 || key.right == 1)
    {
        ++button;
        if (button >= size) button -= size;
    }
    else if (key.up == 1 || key.left == 1)
    {
        --button;
        if (button < 0) button += size;
    }
}

static void updateGuiMenu()
{
    struct StrObject* obj = res_get(TITLE);
    struct StrObject* obj2 = res_get(MENU);
    struct StrObject* obj3 = res_get(STRINGS);
    updateMenu((char) obj2->height);
    if (key.enter == 1)
    {
        if (button == obj2->height - 1) running = 0;
        openGui(button + 1);
        return;
    }
    renderer_drawStrObjCenter(COLS / 2, obj->height / 2 + 2, obj);
    for (int i = 0; i < obj2->height; ++i)
    {
        renderer_drawButton(COLS / 2 - 8, obj->height + 6 + i * 2, obj2->str[i], button == i);
    }
    renderer_drawStrCenter(COLS / 2, obj->height + 7 + obj2->height * 2, obj3->str[2]);
    renderer_drawStr(8, LINES - 5, obj3->str[0]);
    renderer_drawStr(8, LINES - 4, obj3->str[1]);
}

static void updateGuiGame()
{
    struct StrObject* obj = res_get(STRINGS);
    if (key.esc == 1)
    {
        gui = GUI_PAUSE;
        return;
    }
    if (key.w || key.up)
    {
        --player.y;
        player.y = max(player.y, 0 + player.obj->height / 2);
    }
    if (key.a || key.left)
    {
        int speed = 1;
        if (key.a >= 2 || key.left >= 2) speed = 2;
        if (key.a >= 12 || key.left >= 12) speed = 3;
        player.x -= speed;
        player.x = max(player.x, 0 + player.obj->width / 2);
    }
    if (key.s || key.down)
    {
        ++player.y;
        player.y = min(player.y, GAME_HEIGHT - player.obj->height / 2);
    }
    if (key.d || key.right)
    {
        int speed = 1;
        if (key.d >= 2 || key.right >= 2) speed = 2;
        if (key.d >= 12 || key.right >= 12) speed = 3;
        player.x += speed;
        player.x = min(player.x, GAME_WIDTH - player.obj->width / 2);
    }
    if (key.j)
    {
        if (player.energy > 1)
        {
            player.energy -= 2;
            bullets[player.y - player.obj->height / 2][player.x - 1] = '|';
            bullets[player.y - player.obj->height / 2][player.x] = '|';
            if (player.level > 5)
            {
                bullets[player.y - player.obj->height / 2 + 1][player.x - 2] = '|';
                bullets[player.y - player.obj->height / 2 + 1][player.x + 1] = '|';
            }
        }
    }
    if (key.k == 1)
    {
        if (player.energy >= 50)
        {
            player.energy -= 50;
            player.health = min(player.health + 50, MAX_HEALTH);
        }
    }
    if (key.space == 1)
    {
        if (player.skill > 0)
        {
            --player.skill;
            player.animation = res_get(WCNB);
            player.timer = frame;
        }
    }
    // 每两帧(0.1秒)执行一次逻辑
    if (frame % (fps / 10) == 0)
    {
        // 随机生成道具
        if (frame % (fps * 3) == 0) // 每三秒生成一个道具
        {
            int x = randInt(6, GAME_WIDTH - 6);
            int y = randInt(8, GAME_HEIGHT - 8);
            int chance = randInt(0, 20);
            char item = ' ';
            if (chance < 16) item = '$';
            else if (chance < 19) item = 'X';
            else if (chance < 20) item = 'L';
            items[y][x] = item;
        }
        // 让飞机的子弹飞
        for (int y = 0; y < GAME_HEIGHT; ++y)
        {
            for (int x = 0; x < GAME_WIDTH; ++x)
            {
                if (bullets[y][x] == '|')
                {
                    if (y > 0)
                    {
                        if (bullets[y - 1][x] == 'o')
                            bullets[y - 1][x] = ' ';
                        else
                            bullets[y - 1][x] = bullets[y][x];
                    }
                    bullets[y][x] = ' ';
                }
            }
        }
        // 让敌机的子弹飞
        for (int y = GAME_HEIGHT - 1; y >= 0; --y)
        {
            for (int x = 0; x < GAME_WIDTH; ++x)
            {
                if (bullets[y][x] == 'o')
                {
                    if (y < GAME_HEIGHT - 1)
                    {
                        if (bullets[y + 1][x] == '|')
                            bullets[y + 1][x] = ' ';
                        else
                            bullets[y + 1][x] = bullets[y][x];
                    }
                    bullets[y][x] = ' ';
                }
            }
        }
        // 飞机大招
        if (player.animation)
        {
            int line = (frame - player.timer) / (fps / 10);
            if (line < player.animation->height)
            {
                int x = (GAME_WIDTH - player.animation->width) / 2;
                const char* p = player.animation->str[line];
                for (int i = 0; i < player.animation->width; ++i)
                {
                    if (p[i] != ' ')
                        bullets[GAME_HEIGHT - 1][x + i] = p[i];
                }
            }
            else player.animation = NULL;
        }
        // BOSS技能
        if (boss.obj)
        {
            // TODO BOSS 算了, 不写了
        }
        // 获取一下飞机的碰撞箱
        struct AABB box = getAABB(player.x, player.y, player.obj);
        // 让敌机飞
        for (int i = 0; i < length(planes); ++i)
        {
            if (planes[i].countdown > 0)
            {
                // 敌机已坠毁
                --planes[i].countdown;
                if (planes[i].countdown == 0)
                {
                    // 敌机已复活
                    planes[i].x = randInt(2, GAME_WIDTH - 2);
                    planes[i].y = planes[i].obj->height / 2;
                }
            }
            else
            {
                // 敌机还在场上
                struct AABB box2 = getAABB(planes[i].x, planes[i].y, planes[i].obj);
                char flag = 0; // 敌机是否死亡
                if (checkBullet(bullets, &box2, '|'))
                {
                    // 敌机被击中
                    flag = 1;
                    score += 100;
                }
                else if (checkCollision(&box, &box2))
                {
                    // 敌机撞上飞机(划掉)飞机撞上敌机
                    flag = 1;
                    player.health -= 20;
                }
                else
                {
                    if (frame % (fps * 2) == 0) // 两秒一次
                    {
                        // 敌机发射子弹
                        bullets[planes[i].y + planes[i].obj->height / 2][planes[i].x] = 'o';
                    }
                    if (frame % (fps / 2) == 0) // 半秒一次
                    {
                        // 敌机飞出屏幕
                        ++planes[i].y;
                        if (planes[i].y >= GAME_HEIGHT) flag = 1;
                    }
                }
                if (flag)
                {
                    // 敌机死亡
                    int respawn = RESPAWN_TIME - frame / fps / 6;
                    if (respawn < 1) respawn = 1;
                    planes[i].countdown = respawn;
                }
            }
        }
        // 飞机碰道具
        int count = checkBullet(items, &box, '$');
        score += count * 1000;
        count = checkBullet(items, &box, 'L');
        player.level += count;
        count = checkBullet(items, &box, 'X');
        player.skill = min(player.skill + count, 3);
        // 飞机碰子弹
        count = checkBullet(bullets, &box, 'o');
        player.health -= 5 * count;
        // 更新飞机数据
        if (player.health <= 0)
        {
            player.health = 0;
            openGui(GUI_SUBMIT);
            return;
        }
        else
        {
            player.energy += 1 + player.level / 2;
            if (player.energy > MAX_ENERGY) player.energy = MAX_ENERGY;
        }
    }
    // 渲染道具
    for (int y = 0; y < GAME_HEIGHT; ++y)
    {
        for (int x = 0; x < GAME_WIDTH; ++x)
        {
            if (items[y][x] != ' ')
                renderer_drawChar(x, y, items[y][x]);
        }
    }
    // 渲染子弹
    for (int y = 0; y < GAME_HEIGHT; ++y)
    {
        for (int x = 0; x < GAME_WIDTH; ++x)
        {
            if (bullets[y][x] != ' ')
                renderer_drawChar(x, y, bullets[y][x]);
        }
    }
    // 渲染飞机
    for (int i = 0; i < length(planes); ++i)
    {
        if (planes[i].countdown == 0)
            renderer_drawStrObjCenter(planes[i].x, planes[i].y, planes[i].obj);
    }
    renderer_drawStrObjCenter(player.x, player.y, player.obj);
    // 渲染HUD
    renderer_drawVerticalLine(GAME_WIDTH, 0, GAME_HEIGHT);
    renderer_drawStr(GAME_WIDTH + 4, 3, obj->str[3]);
    renderer_printStr(GAME_WIDTH + 4, 5, obj->str[4], frame);
    renderer_printStr(GAME_WIDTH + 4, 8, obj->str[5], res_get(DIFFICULTY)->str[difficulty]);
    renderer_printStr(GAME_WIDTH + 4, 10, obj->str[6], frame / fps);
    renderer_printStr(GAME_WIDTH + 4, 12, obj->str[7], score);
    renderer_drawStrObj(GAME_WIDTH + 4 + player.obj->width / 2, LINES - 16 - player.obj->height / 2, player.obj);
    renderer_printStr(GAME_WIDTH + 4, LINES - 12, obj->str[8], player.level);
    renderer_printStr(GAME_WIDTH + 4, LINES - 10, obj->str[9], player.health);
    int color;
    if (player.health > 60) color = 1;
    else if (player.health > 30) color = 2;
    else color = 3;
    attron(A_BOLD | COLOR_PAIR(color));
    renderer_drawProgress(GAME_WIDTH + 4, LINES - 9, 12, player.health / (double) MAX_HEALTH);
    attroff(A_BOLD | COLOR_PAIR(color));
    renderer_printStr(GAME_WIDTH + 4, LINES - 7, obj->str[10], player.energy);
    attron(A_BOLD | COLOR_PAIR(4));
    renderer_drawProgress(GAME_WIDTH + 4, LINES - 6, 12, player.energy / (double) MAX_ENERGY);
    attroff(A_BOLD | COLOR_PAIR(4));
    renderer_printStr(GAME_WIDTH + 4, LINES - 4, obj->str[11], player.skill);
}

static void updateGuiRank()
{
    struct StrObject* obj = res_get(BUTTONS);
    struct StrObject* obj2 = res_get(STRINGS);
    struct StrObject* obj3 = res_get(WEBSITE);
    updateMenu(2);
    if (key.esc == 1)
    {
        openGui(GUI_MENU);
        return;
    }
    if (key.enter == 1)
    {
        if (button == 0)
        {
            openGui(GUI_MENU);
            return;
        }
        else if (button == 1)
        {
            openBrowser(obj3->str[1]);
        }
    }
    renderer_drawStr(12, 7, obj2->str[21]);
    if (rank != NULL)
    {
        cJSON* item = rank->child;
        for (int i = 1; i <= 10; ++i)
        {
            if (item)
            {
                cJSON* json_name = cJSON_GetObjectItem(item, "name");
                cJSON* json_score = cJSON_GetObjectItem(item, "score");
                renderer_printStr(16, 8 + i * 2, obj2->str[22], i, json_name->valuestring, json_score->valueint);
                item = item->next;
            }
            else
            {
                renderer_printStr(16, 8 + i * 2, obj2->str[23], i);
            }
        }
    }
    else
    {
        renderer_drawStr(16, 10, obj2->str[24]);
    }
    renderer_drawButtonCenter(COLS / 2 - 10, LINES - 8, obj->str[4], button == 0);
    renderer_drawButtonCenter(COLS / 2 + 6, LINES - 8, obj->str[9], button == 1);
}

static void updateGuiSettings()
{
    openGui(GUI_MENU);
    return;
}

static void updateGuiHelp()
{
    struct StrObject* obj = res_get(BUTTONS);
    struct StrObject* obj2 = res_get(STRINGS);
    struct StrObject* obj3 = res_get(HELP);
    struct StrObject* obj4 = res_get(ABOUT);
    struct StrObject* obj5 = res_get(WEBSITE);
    updateMenu(2);
    if (key.esc == 1)
    {
        openGui(GUI_MENU);
        return;
    }
    if (key.enter == 1)
    {
        if (button == 0)
        {
            openGui(GUI_MENU);
            return;
        }
        else if (button == 1)
        {
            openBrowser(obj5->str[2]);
        }
    }
    renderer_drawStr(8, 4, obj2->str[25]);
    renderer_drawStrObj(12, 6, obj3);
    renderer_drawStr(8, 6 + obj3->height + 2, obj2->str[26]);
    renderer_drawStrObj(12, 6 + obj3->height + 4, obj4);
    renderer_drawButtonCenter(COLS / 2 - 10, LINES - 5, obj->str[4], button == 0);
    renderer_drawButtonCenter(COLS / 2 + 6, LINES - 5, obj->str[10], button == 1);
}

static void updateGuiPause()
{
    struct StrObject* obj = res_get(BUTTONS);
    struct StrObject* obj2 = res_get(STRINGS);
    updateMenu(2);
    if (key.esc == 1)
    {
        gui = GUI_GAME;
        return;
    }
    if (key.enter == 1)
    {
        if (button == 0) gui = GUI_GAME;
        else if (button == 1) openGui(GUI_MENU);
        return;
    }
    renderer_drawStrCenter(COLS / 2, LINES / 2 - 6, obj2->str[12]);
    renderer_drawButtonCenter(COLS / 2, LINES / 2, obj->str[5], button == 0);
    renderer_drawButtonCenter(COLS / 2, LINES / 2 + 2, obj->str[6], button == 1);
}

static void updateGuiSubmit()
{
    struct StrObject* obj = res_get(BUTTONS);
    struct StrObject* obj2 = res_get(STRINGS);
    struct StrObject* obj3 = res_get(GAMEOVER);
    updateMenu(2);
    if (key.enter == 1)
    {
        if ((button == 0 && strlen(playername) > 0) || button == 1)
        {
            if (button == 1) strcpy(playername, obj2->str[16]);
            cJSON* json = cJSON_CreateObject();
            cJSON_AddItemToObject(json, "name", cJSON_CreateString(playername));
            cJSON_AddItemToObject(json, "score", cJSON_CreateNumber(score));
            char* request = cJSON_PrintUnformatted(json);
            char* response = util_httppost(res_get(WEBSITE)->str[0], request);
            cJSON_Delete(json);
            free(request);
            if (response)
            {
                json = cJSON_Parse(response);
                if (cJSON_HasObjectItem(json, "id"))
                    playerid = cJSON_GetObjectItem(json, "id")->valueint;
                cJSON_Delete(json);
            }
            free(response);
            openGui(GUI_RESULT);
            return;
        }
    }
    if (key.backspace)
    {
        for (int i = 1; i < MAX_NAME_LENGTH + 1; ++i)
        {
            if (playername[i] == '\0')
            {
                playername[i - 1] = '\0';
                break;
            }
        }
    }
    int lastkey = input_getch();
    if ((lastkey >= 'a' && lastkey <= 'z') || (lastkey >= '0' && lastkey <= '9'))
    {
        for (int i = 0; i < MAX_NAME_LENGTH; ++i)
        {
            if (playername[i] == '\0')
            {
                playername[i] = lastkey;
                break;
            }
        }
    }
    renderer_drawStrObjCenter(COLS / 2, obj3->height / 2 + 6, obj3);
    char formattedstr[30];
    sprintf(formattedstr, obj2->str[13], score);
    renderer_drawStrCenter(COLS / 2, obj3->height + 8, formattedstr);
    renderer_drawStr(12, LINES / 2, obj2->str[14]);
    renderer_printStr(12, LINES / 2 + 2, obj2->str[15], playername);
    renderer_drawButtonCenter(COLS / 2, LINES / 2 + 6, obj->str[7], button == 0);
    renderer_drawButtonCenter(COLS / 2, LINES / 2 + 8, obj->str[8], button == 1);
#ifdef _DEBUG
    renderer_printStr(0, LINES - 1, "TEST Key: %d", lastkey); // Only for test
#endif
}

static void updateGuiResult()
{
    struct StrObject* obj = res_get(BUTTONS);
    struct StrObject* obj2 = res_get(STRINGS);
    if (key.enter == 1)
    {
        openGui(GUI_MENU);
        return;
    }
    cJSON* item = playerdata->child;
    renderer_drawStr(12, 8, obj2->str[17]);
    renderer_printStr(16, 12, obj2->str[18], cJSON_GetObjectItem(item, "name")->valuestring);
    renderer_printStr(16, 14, obj2->str[13], cJSON_GetObjectItem(item, "score")->valueint);
    int rank = cJSON_GetObjectItem(item, "rank")->valueint;
    double percent = 1 - rank / cJSON_GetObjectItem(item, "total")->valuedouble;
    renderer_printStr(16, 16, obj2->str[19], rank);
    renderer_printStr(16, 18, obj2->str[20], percent * 100);
    renderer_drawButtonCenter(COLS / 2, LINES / 2 + 8, obj->str[2], TRUE);
}

void game_run()
{
    running = 1;
    game_init();
    game_loop();
    game_exit();
}

void game_init()
{
    guiupdaters[GUI_MENU] = updateGuiMenu;
    guiupdaters[GUI_GAME] = updateGuiGame;
    guiupdaters[GUI_RANK] = updateGuiRank;
    guiupdaters[GUI_SETTINGS] = updateGuiSettings;
    guiupdaters[GUI_HELP] = updateGuiHelp;
    guiupdaters[GUI_PAUSE] = updateGuiPause;
    guiupdaters[GUI_SUBMIT] = updateGuiSubmit;
    guiupdaters[GUI_RESULT] = updateGuiResult;
    setWindowTitle(res_get(STRINGS)->str[0]);
    input_init();
    renderer_init();
}

void game_loop()
{
    openGui(GUI_MENU);
    while (running)
    {
        clock_t t = getCurrentTime();
        input_handle();
        renderer_clear();
        if (gui >= GUI_MENU && gui < GUI_COUNT)
        {
            guiupdaters[gui]();
        }
        else
        {
            openGui(GUI_MENU);
            continue;
        }
        renderer_refresh();
        if (gui != GUI_PAUSE) ++frame;
        clock_t wait = 1000 / fps - (getCurrentTime() - t);
        if (wait < 0)
        {
            fprintf(stderr, "Warning: slow renderer: %ld ms.\n", -wait);
            wait = 0;
        }
        mysleep(wait);
    }
}

void game_exit()
{
    renderer_end();
}

// 毫秒
static clock_t getCurrentTime()
{
    return 1000 * clock() / CLOCKS_PER_SEC;
}

// 毫秒
static void mysleep(clock_t time)
{
#if defined(_WIN32) || defined(_WIN64)
    Sleep(time);
#else
    usleep(time * 1000);
#endif
}

// 目前仅在Windows平台起作用
static void setWindowTitle(const char *title)
{
#if defined(_WIN32) || defined(_WIN64)
    PDC_set_title(title);
#endif
}

static void openBrowser(const char* url)
{
#if defined(_WIN32) || defined(_WIN64)
    // ShellExecuteA(NULL, "open", url, NULL, NULL, SW_SHOWNORMAL);
    char command[50] = "start ";
#else
    // system("/bin/sh -c chromium-browser");
    char command[50] = "xdg-open ";
#endif
    system(strcat(command, url));
}
