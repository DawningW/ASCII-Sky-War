#include "game.h"

/**
 * ASCII SKY WAR
 * 飞机大战
 */
int main(int argc, char* argv[])
{
    printf("Loading game, please wait...\n");
    // 初始化日志
    log_init();
    // 处理命令行参数
    for (int i = 0; i < argc; ++i)
    {
        // TODO 把参数读取到命令行参数结构体中
    }
    // 读取配置文件
    // 加载资源
    res_load();
    // 联网
    curl_global_init(CURL_GLOBAL_ALL);
    // 开始游戏
    game_run();
    // 清理
    curl_global_cleanup();
    res_unload();
    return 0;
}
