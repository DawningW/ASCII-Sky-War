#ifndef __INPUT_H__
#define __INPUT_H__

// ����״̬�ṹ��
struct Key
{
    unsigned int esc;
    unsigned int enter;
    unsigned int backspace;
    unsigned int up;
    unsigned int left;
    unsigned int down;
    unsigned int right;
    unsigned int space;
    unsigned int w;
    unsigned int a;
    unsigned int s;
    unsigned int d;
    unsigned int j;
    unsigned int k;
};

// ��ǰ����״̬
extern struct Key key;

void input_init();
void input_handle();
int input_getch();

#endif // __INPUT_H__
