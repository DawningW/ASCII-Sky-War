#include "game.h"

/**
 * ASCII SKY WAR
 * �ɻ���ս
 */
int main(int argc, char* argv[])
{
    printf("Loading game, please wait...\n");
    // ��ʼ����־
    log_init();
    // ���������в���
    for (int i = 0; i < argc; ++i)
    {
        // TODO �Ѳ�����ȡ�������в����ṹ����
    }
    // ��ȡ�����ļ�
    // ������Դ
    res_load();
    // ����
    curl_global_init(CURL_GLOBAL_ALL);
    // ��ʼ��Ϸ
    game_run();
    // ����
    curl_global_cleanup();
    res_unload();
    return 0;
}
