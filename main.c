#define _CRT_SECURE_NO_WARNINGS
// Raiti Project
// ������ : asdarwin03



/*
�� ���α׷��� Z,XŰ�� ���� ��鼭 ������ ��� �����Դϴ�. ������ �ð����� ���� �����Ͽ� ������ ��Ģ���� �Ѿ��� ��µ�, ������ ��� �Ѿ��� ��� ���ϸ� �ڽ��� �Ѿ��� �� ���߾�� ���� ���� �� �ֽ��ϴ�.
�̵�Ű�� ȭ��ǥ ����, ����, ������, �Ʒ����̰�, ����Ű�� Z�� X�Դϴ�. ó������ Z������ �Ϸ������� ZŰ�� �����⿡�� '�ʹ� ��� �����'��� �ǰ��� �ݿ��Ͽ� Z�Ӹ� �ƴ϶� XŰ�� ������ �Ѿ��� �߻�ǵ��� �Ͽ����ϴ�.

�� ���α׷����� ����(��������)�� �����մϴ�. 1,2,3���� ������µ�, 4���ʹ� ����⵵ ������, �÷��̾ ��������� �������� ���� ���̶�� �Ǵܿ� ���� 4������ ���ݽ��ϴ�.

�� ���α׷����� '���� �ð�'�̶�� ���� �ִµ�, �̴� ����(��������) ���� ���� �ο��Ǹ�, '���� �ð�' �ȿ� �ش� ���� �ȿ� �ִ� ���� ��� �׿��� �ش� ������ Ŭ����ǰ� ���� ������ �Ѿ�ϴ�.

���ѽð� ���� ���� ���� ���� ��� '���� ����' ó���Ǹ�, �ٽ� �ش� �������� �絵���� �� �ֽ��ϴ�.

�����Դ� ü���� �ִµ�, �� ��ġ�� ��Ȯ�� Ȯ���� �� �����ϴ�. Raiden�̶�� ������ �� �� ������� �����ε�, �� ���ӿ����� ��Ȯ�� ���� ü�� ��ġ�� ������ �ʽ��ϴ�.
��� ���� ������ �׽��ϴ�. �׶����� �������ּ���.

�����, �÷��̾�� �� �߸� �¾Ƶ� �׽��ϴ�.

���� ȭ�鿡�� ������ ���ø� ����, ����, ���� ��, ���� �ð� ���� �����µ���, ������ 1������ ǥ�õ˴ϴ�(ó�� ���� ����).

�Ѿ��̳� ���� �ε��� ������ ���, ���ӿ��� ȭ������ �Ѿ�ϴ�. �� ȭ���� ���� �� �絵���� �Ͻ÷��� Y��, ������ �����Ͻ÷��� N�� �Է��� �ּ���.(�빮�� �ʼ�)

������ ���̵��� �����Ͽ��µ�, 1������ ���ݸ� �غ��ø� �ݹ� Ŭ������ �� �ִ� ���̵��̸�, 2������ ���� �� �ؾ��ϰ�, 3������ ���� ��ư� ��������ϴ�.
��� ���� ���ݴµ��� ���ѽð��� ���Ҵٸ� �׵��� ���� Ǯ���ּ���. ���� ���Ŀ�.


���� �ڵ带 �����ϰ� �����Ͽ� ����ڰ� ���ϴ� ����� ���¸� ����� �����ų �� �ֽ��ϴ�. �� ������ �Ʒ��� �ֽ��ϴ�. ���� �ڵ忡�� '�𵨸�'�� �˻��Ͻø� ���� �̴ϴ�.


*/



#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <math.h>
#include <conio.h>

/*
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#include "Digitalv.h"


MCI_OPEN_PARMS m_mciOpenParms;
MCI_PLAY_PARMS m_mciPlayParms;
DWORD m_dwDeviceID;
MCI_OPEN_PARMS mciOpen;
MCI_PLAY_PARMS mciPlay;

*/
int dwID;

int _count = 0;



#define MAX_X 70	// �ܼ��� ũ��
#define MAX_Y 46

#define LEFT 1		// ����Ⱑ ������ ����.
#define UP 3
#define RIGHT 2
#define DOWN 4

#define SHOTKEY 0x5A // 'Z'
#define SHOTKEY2 0x58 // 'X'
#define SHOTKEY_CHECK 0x0001

#define BLOCK 101
#define EMPTY -75

#define SHOTBLOCK 103 // '��'
#define R_SHOTBLOCK 104 // '��'
#define RIGHT_SHOTBLOCK 105 // '��'
#define LEFT_SHOTBLOCK 106 // '��'


// �ʿ� ������Ʈ �ϴ� �뵵�� ����ϴ� ����.
#define MY_BULLET -50
#define ENEMY_BULLET -70

// �ʿ���, ���� ������ �����س��� ����.
#define WALL -11
#define BLANK -5


//����� ũ���� �ִ�.
#define PLANE_MAX_X 30
#define PLANE_MAX_Y 4


//�Ѿ��� ����.
#define BULLET_DEFAULT '*'               // ������ �Ѿ�.
#define BULLET_SPECIAL '*'               // �÷��̾��� �Ѿ�.



#define PLAYER_BULLET_MAX 30               // �÷��̾��� �Ѿ� ���� ����
#define PLAYER_BULLET_DELAY 7               // �Ѿ��� �� ���� �ð� ����. 10 - 0.1�ʱ⺻ : 7 
#define SHOOTING_BULLET_SPEED 2                //2~10 ���̿��� �����ϴ°��� ��õ. 1�� ���� �� ���� ���� �߻�(�ʹ� ���� �Ѿ��� ���ư���)

#define PLAYER_MAX_ATTACKBLOCK 1         //���� ���� ����� ����! ���� ���� �� ����� ATTACKBLOCK�� ������ ��Ȯ�� ���� ����.






#define PLANE_MAX_ATTACKBLOCK 10
#define MAX_DISPLAYED_BULLET 100            //���� �Ѿ��� ȭ�鿡 ǥ�õǴ� �ִ� �ѵ�, 30���� �ʰ��� ��� ������ �Ѿ��� �߻����� �ʴ´�.

#define ENEMY_REGULAR 80                //�¿�-�̵�Ÿ��
#define ENEMY_REVERSE 60                //����-�̵�Ÿ��
#define ENEMY_MOVESPEED 20              //�����̴� �ӵ� �⺻����
#define ENEMY_NUM 50                    //�����ϴ� ���� �� �ִ�
#define ENEMY_DEFAULT_HP 5              // ������ �⺻ ü��

#define PLAYER -3						//�÷��̾��� ID.
#define ENEMY 2							//

#define PLAYER_COLOR 10 // 10 - �ʷϱ׸���
#define ENEMY_COLOR 12 // 12 - ������
#define ENEMY_BULLET_COLOR 15 // 15 �Ͼ��
#define PLAYER_BULLET_COLOR 14 // 6 �����

#define REPLAY 0x59 // ���� ������ ��� YŰ�� ������ �ٽ� ���۵ȴ�.
#define GAME_QUIT 0x4E // ���ӿ����� �� NŰ�� ������ �ܼ��� ����ȴ�.

#pragma comment(lib, "winmm.lib")			// PlaySound()�� ����ϱ� ����.

int count = 0;                              // ���ο� �ִ� �ݺ����� �ݺ� Ƚ���� ���� ������ �ڵ带 �ۼ��ϱ� ����.
int player_onBullet = 0;                    // player_onBullet�� �÷��̾ ���� ��� �ִ� �������� �ƴ����� �˻��ϱ� ���Ͽ� ���� ����������, ���� ī��Ʈ�� ������ �÷��̾ ���� �� �� �ְ� �ȴ�.
int map[MAX_Y][MAX_X + 1];					// �� ������ �÷��̾��� ��ġ�� �����Ͽ� �Ѿ��� �¾Ҵ��� �ƴ��� �Ǵ��ϱ� ���Ͽ� ����.
int lev;									// �ð��� ������ �������� ������ �������µ�, 3�������� �������. ������ ���������� ��ư� ���� ������. �׾ 1�������� �ٽ� ������ �ƴ� ���� �ش� �������� �����Ѵ�.
int score = 0;								// ���� óġ�Ҷ����� score�� 1���� ����. �װų� ������ ������ ��� ȭ�鿡 �ڽ��� score�� ���� �ٽý����� �� score�� �ʱ�ȭ�ȴ�.,
int displayed_enemy = 0;					// �� ���� ������ ����� �� ����Ⱑ �� �� ���� ȭ�鿡 �����ִ��� ǥ�����ֱ� ���� �������. �� displayed_enemy�� '���� �ִ� ���� ��'�� �ǹ��Ѵ�. ���ѽð��� �Ѿ� ���� ������ �Ѿ �� �� ������ �˻��Ͽ� �����ִ� ���� ���� 1��� ������ ���ӿ����̴�.
int levelTimeLimit[6]; // ���� �� �ð������� �����Ѵ�. 1������� 5������� ���� �����̱� ������.
int _time = 0;           //�ð������� �α� ���� �ð��� �����ϱ� ���� ������ ����.
int clearrr = 0;		//�÷��̾ ��� Ŭ���� �ߴ��� ����

typedef struct _Bullet {
	char type;	// �Ѿ��� Ÿ������, �̰��� �����ϸ� ���� ��� �Ѿ��� ���¸� �ٲ� �� �ִ�.
	int x, y;	// �Ѿ��� x,y��ǥ�� �����Ѵ�.
	int speed;	// �Ѿ��� ���ư��� �ӵ��� �ǹ��Ѵ�.
	int isSpawned;	// �Ѿ��� �߻� �Ǿ����� ���θ� �˻��� �� �̿�Ǵ� �����̴�.
	int dir;		// �Ѿ��� ���ư��� ������ �ǹ��Ѵ�.
	int owner;		// �Ѿ��� ��������, PLAYER�� ENEMY�� ������.
} Bullet;


typedef struct _Plane {
	int id;			// Plane�� ������ȣ. '��' ������ �⺻ ��ȣ�� -3�̴�. ������� �Ϳ� ���ǰ� �ִµ�, ������ ������ȣ�� 0 �̻��̴�. �̷��� �Ͽ� ���� �� �ִ� ������ �ִ�.
	int model[PLANE_MAX_Y][PLANE_MAX_X];		// ������� ���, ���� 2���� �迭�̴�.
	int x, y;									// ������� x,y��ǥ
	int max_x;									// ����⿡�� ������ ���� �� ��ǥ
	int max_y;									// ����⿡�� ���� �Ʒ��� ��ǥ
	int attack_x[PLANE_MAX_ATTACKBLOCK];		// ����� �𵨿����� SHOTBLOCK ��ǥ
	int attack_y[PLANE_MAX_ATTACKBLOCK];		// ''
	int maxShotBlock;							// �ִ� SHOTBLOCK, �� ���� �� �� �ֵ��� ���� ���� ����
	int bulletSelector;							// �Ѿ� �߻� ����. SHOTBLOCK�� 1���϶��� �ǹ̰� ������, 2�� �̻��� ��� ������ ������� �Ѿ��� �߻�ȴ�.
	int isDead;									// ���� ����
	int isDisplayed; // //ȭ�鿡 ǥ�� �Ǿ����� �ƴ����� ǥ��

					 // �� ����⸦ ���� ����
	int type; // �÷��̾�Դ� �ش�X, ���� ������� �̵�Ư�� ����
	int dir; // ������ �����̴� ����.
	int bulletdelay; // �Ѿ��� ��� �ӵ�.
	int movespeed; // ���� �����̴� �ӵ�.
	int bulletspeed; // ���� ��� �Ѿ��� �ӵ�. 2 - ���� ����
	int bulletdir; // ��� �Ѿ��� ����
	int hp;			// ������� ü��
} Plane;



Plane enemy[ENEMY_NUM];			// define���� ������ ��� enemy ����ü�� ����. ENEMY_NUM�� �ִ� �� ���� �ǹ���.
Plane Me;
Bullet myBullet[PLAYER_BULLET_MAX];	// define���� ������ ��� myBullet ����ü�� ����. ���� �� �� �ִ� �Ѿ��� �ǹ���.
Bullet enemyBullet[MAX_DISPLAYED_BULLET]; // // define���� ������ ��� enemyBullet ����ü�� ����. ������ �� �� �ִ� �Ѿ��� �ǹ���.


/*
void playMCI(char * a)//mp3 ���
{
	mciOpen.lpstrElementName = a; // ���� ���
	mciOpen.lpstrDeviceType = "mpegvideo";

	mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&mciOpen );

	dwID = mciOpen.wDeviceID;

	mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&m_mciPlayParms);// play & repeat
}
void playMCI_noRepeat(char * a)//mp3��� - �ݺ�x
{
	mciOpen.lpstrElementName = a; // ���� ��� �Է�
	mciOpen.lpstrDeviceType = "mpegvideo";

	mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&mciOpen);

	dwID = mciOpen.wDeviceID;

	mciSendCommand(dwID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&m_mciPlayParms);// play
}
void stopMCI()//mp3 ��� ����
{
	mciSendCommandW(dwID, MCI_CLOSE, 0, NULL); // stop
}


*/


void gotoxy(int x, int y) // �ܼ��� x,y��ǥ�� Ŀ���� �̵�
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}



int checkBlocked(Plane *p, int key)			// ����Ⱑ ���� ��Ҵ��� �ȴ�Ҵ��� �� ������ �Ǵ����ִ� �Լ�
{
	if (key == UP)          // ȭ��ǥ ���� ����Ű�� ������ ��
	{
		if (p->y < 3 + 1 + 2)  // �Ѿ��� �߻����� �� ���� ȭ���� �����ϴ� ���� ������� �ʰ� �ϱ� ���� ������� �̵� ���� ������ ���� �ڷ� �̷� ������ �����Ͽ���.
			return 1;


	}
	else if (key == DOWN) {			//ȭ��ǥ �Ʒ��� ����Ű�� ������ ��

		if (p->y + p->max_y >= MAX_Y - 1)	//����Ⱑ �Ʒ��� ���� ������
			return 1;						// 1�� ��ȯ�Ѵ�.

	}
	else if (key == LEFT) {			//ȭ��ǥ ���� ����Ű�� ������ ��

		if (p->x < 2 + 1)			// ����Ⱑ ���� ���� ������
			return 1;				// 1�� ��ȯ.


	}
	else if (key == RIGHT) {		//ȭ��ǥ ������ ����Ű�� ������ ��

		if (p->x + p->max_x >= MAX_X - 2 - 1) // ����Ⱑ ������ ���� ������
			return 1;				// 1�� ��ȯ
	}



	return 0;					// �� ������ ��� �������� ���� ��� ���� �ε����� ���� ������ ����, 0�� ��ȯ�Ѵ�.
}
void displayBullet(Bullet *b)    // Bullet ���� Struct�� �����̴� ���� ����ϴ� �Լ���.
{
	gotoxy(b->x, b->y);			// Bullet�� ����ϱ����� �ܼ� Ŀ���� Bullet�� ��ġ�� �̵���.
	if (b->owner == PLAYER)		// �Ѿ��� ��� ���� PLAYER���
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), PLAYER_BULLET_COLOR); // ���� PLAYER_BULLET_COLOR�� �ٲ۴�.
	else if (b->owner == ENEMY) // �Ѿ��� ��� ���� ENEMY���
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ENEMY_BULLET_COLOR);	// ���� ENEMY_BULLET_COLOR�� �ٲ۴�.
	printf("%c", b->type);		// �Ѿ��� ����Ѵ�. b->type�� �Ѿ��� ������ �ǹ��ϴµ�, �⺻������ '*'�̴�.


}
void initCursor()	// Ŀ���� ������ �ʰ� �ϱ� ���� ����.
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}
void resizeConsole()	// �ܼ��� ũ�⸦ ����.
{
	char chTemp[50];
	sprintf(chTemp, "Mode con cols=%d lines=%d", MAX_X, MAX_Y);
	system(chTemp);
}

void clearGame()			//���� 3���� Ŭ���� �� ������ ������ Ŭ���� ȭ��.
{
	resizeConsole();

	gotoxy(20, 1);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("��������������");
	gotoxy(14, 2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("��������������������");
	gotoxy(14, 3);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("��������������������");
	gotoxy(14, 4);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("��������������������");
	gotoxy(14, 5);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("��������������������");
	gotoxy(18, 5);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("�����");
	gotoxy(32, 5);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("���");
	gotoxy(42, 5);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("����");
	gotoxy(8, 6);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("��������������������������");
	gotoxy(18, 6);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("��");
	gotoxy(42, 6);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("��");
	gotoxy(48, 6);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("��");
	gotoxy(36, 6);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("��");
	gotoxy(30, 6);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("��");





	gotoxy(8, 7);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("��������������������������");
	gotoxy(48, 7);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("��");
	gotoxy(42, 7);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("��");

	gotoxy(36, 7);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("��");
	gotoxy(30, 7);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("��");
	gotoxy(18, 7);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("��");
	gotoxy(8, 8);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("��������������������������");
	gotoxy(42, 8);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("����");

	gotoxy(36, 8);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("��");
	gotoxy(18, 8);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("����");
	gotoxy(30, 8);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("��");
	gotoxy(6, 9);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("����������������������������");
	gotoxy(42, 9);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("��");
	gotoxy(46, 9);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("���");
	gotoxy(36, 9);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("��");
	gotoxy(30, 9);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("��");
	gotoxy(18, 9);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("��");
	gotoxy(6, 10);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("����������������������������");
	gotoxy(48, 10);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("��");
	gotoxy(42, 10);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("��");
	gotoxy(30, 10);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("��");

	gotoxy(36, 10);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("��");

	gotoxy(18, 10);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("��");


	gotoxy(6, 11);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("����������������������������");
	gotoxy(32, 11);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("���");
	gotoxy(42, 11);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("��");
	gotoxy(48, 11);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("��");
	gotoxy(18, 11);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("��");
	gotoxy(6, 12);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("����������������������������");

	gotoxy(6, 13);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("����������������������������");
	gotoxy(6, 14);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("����������������������������");
	gotoxy(6, 15);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("����������������������������");
	gotoxy(6, 16);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("����������������������������");
	gotoxy(28, 16);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("!!WINNER!!");
	gotoxy(6, 17);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("����������������������������");
	gotoxy(28, 17);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("!!WINNER!!");
	gotoxy(6, 18);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("����������������������������");
	gotoxy(28, 18);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("!!WINNER!!");

	gotoxy(6, 19);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("����������������������������");
	gotoxy(28, 19);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("!!WINNER!!");
	gotoxy(8, 20);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("��������������������������");
	gotoxy(8, 21);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("��������������������������");
	gotoxy(8, 22);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("��������������������������");
	gotoxy(14, 23);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("��������������������");
	gotoxy(14, 24);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("��������������������");
	gotoxy(14, 25);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("��������������������");
	gotoxy(14, 26);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("��������������������");
	gotoxy(14, 27);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("��������������������");
	gotoxy(24, 28);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("����������");
	gotoxy(24, 29);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("����������");
	gotoxy(24, 30);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("����������");
	gotoxy(24, 31);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("����������");
	gotoxy(24, 32);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("����������");
	gotoxy(24, 33);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("����������");
	gotoxy(24, 34);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("����������");
	gotoxy(24, 35);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("����������");
	gotoxy(24, 36);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("����������");
	gotoxy(22, 37);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("�ܡ����  �ء����");
	gotoxy(20, 38);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("�ܡܡܡܡ�      �ܡܡܡܡ�");
	gotoxy(20, 39);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("�ܡܡܡ�          �ܡܡܡ�");
	gotoxy(22, 40);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("�ܡ�              �ܡ�");
}



void displayStart()		// ���� ȭ��.
{
	char ch;			// ���� �ϳ��� �޾� �ƹ� Ű�� �Է��Ͽ��� ��� �ι�° ȭ������ ���� ���� �� ������ ����.
	while (1)
	{


		gotoxy(4, 1);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);		//ù��° ȭ�� �ٹ̱� - ���� �̸�
		printf("��������\n    ���������\n    ����      ����\n    ����       ����\n    ����      ����\n    ����     ����\n    ����    ����\n    ���������\n    ���������\n    ����    ����\n    ����     ����\n    ����      ����\n    ����       ����\n");

		gotoxy(25, 8);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
		printf("������");
		gotoxy(23, 9);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
		printf("����������");
		gotoxy(22, 10);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
		printf("����    ����");
		gotoxy(22, 11);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
		printf("����    ����");
		gotoxy(23, 12);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
		printf("������������");
		gotoxy(25, 13);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
		printf("������ ����");

		gotoxy(37, 7);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		printf("������");
		gotoxy(37, 8);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		printf("������");
		gotoxy(37, 9);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		printf("������");
		gotoxy(37, 10);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		printf("        ");
		gotoxy(37, 11);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		printf("������");
		gotoxy(37, 12);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		printf("������");
		gotoxy(37, 13);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		printf("������");

		gotoxy(48, 5);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		printf("������");
		gotoxy(48, 6);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		printf("������");
		gotoxy(44, 7);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		printf("��������������");
		gotoxy(44, 8);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		printf("��������������");
		gotoxy(44, 9);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		printf("��������������");
		gotoxy(48, 10);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		printf("������");
		gotoxy(48, 11);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		printf("������");
		gotoxy(48, 12);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		printf("������");
		gotoxy(48, 13);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		printf("������");


		gotoxy(60, 7);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
		printf("������");
		gotoxy(60, 8);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
		printf("������");
		gotoxy(60, 9);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
		printf("������");
		gotoxy(60, 10);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
		printf("        ");
		gotoxy(60, 11);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
		printf("������");
		gotoxy(60, 12);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
		printf("������");
		gotoxy(60, 13);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
		printf("������");




		gotoxy(MAX_X / 2 - 1, 17);		//ù��° ȭ�� �ٹ̱� - �����
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		printf("��");
		gotoxy(MAX_X / 2 - 2, 18);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		printf("���");
		gotoxy(MAX_X / 2 - 3, 19);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		printf("����");
		gotoxy(MAX_X / 2 - 4, 20);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		printf("�����");
		gotoxy(MAX_X / 2 - 19, 21);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		printf("��������������������������ᢺ��������������");
		gotoxy(MAX_X / 2 - 28, 22);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		printf("�ס���������������������������");
		gotoxy(MAX_X / 2 - 30, 23);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		printf("�ס�����������������������������");
		gotoxy(MAX_X / 2 - 32, 24);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
		printf("�ס�������������������������������");
		gotoxy(MAX_X / 2 - 30, 25);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		printf("�ء�����������������������������");
		gotoxy(MAX_X / 2 - 4, 26);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		printf("�����");
		gotoxy(MAX_X / 2 - 4, 27);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		printf("�����");
		gotoxy(MAX_X / 2 - 4, 28);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		printf("�����");
		gotoxy(MAX_X / 2 - 4, 29);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		printf("�����");
		gotoxy(MAX_X / 2 - 4, 30);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		printf("�����");
		gotoxy(MAX_X / 2 - 14, 31);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		printf("�ס�������������");
		gotoxy(MAX_X / 2 - 16, 32);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		printf("�ס���������������");
		gotoxy(MAX_X / 2 - 18, 33);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		printf("�ס�����������������");
		gotoxy(MAX_X / 2 - 16, 34);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		printf("�ء���������������");
		gotoxy(MAX_X / 2 - 14, 35);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		printf("�ء�������������");


		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
		gotoxy(MAX_X / 2 - 15, 40);
		printf("�����Ϸ��� �ƹ� Ű�� ��������!");
		Sleep(300);

		if (_kbhit())			//�ƹ� Ű�� ������ �����Ѵ�.
		{
			ch = _getch();
			break;
		}
		gotoxy(MAX_X / 2 - 15, 44);
		printf("                                      ");
		Sleep(300);
		if (_kbhit())
		{
			ch = _getch();
			if (_kbhit())
				break;
		}
	}
	system("cls");	//ȭ���� ���
}
void displaySecond()			//ù��° ȭ�鿡�� �ƹ�Ű�� ���� �� ������ �ι�° ȭ��
{
	char ch;		//���ڸ� �Է¹ޱ� ���� ���� ����
	while (1)		//���� -
	{


		gotoxy(18, 7);
		printf("��            <����>            �� ");
		gotoxy(18, 8);
		printf("��                                ��");
		gotoxy(18, 9);
		printf("��    ��: ��Ʈ�� �����̵�         ��");
		gotoxy(18, 10);
		printf("��    ��: ��Ʈ�� �Ʒ����̵�       ��");
		gotoxy(18, 11);
		printf("��    ��: ��Ʈ�� ���������̵�     ��");
		gotoxy(18, 12);
		printf("��    ��: ��Ʈ�� �����������̵�   ��");
		gotoxy(18, 13);
		printf("��       zŰ   :   �ѽ��         ��");
		gotoxy(18, 14);
		printf("��                                ��");
		gotoxy(18, 15);
		printf("��������������������������������������������������������������������");


		gotoxy(24, 25);
		printf("��    TIP    �� ");
		gotoxy(24, 26);
		printf("��           ��");
		gotoxy(24, 27);
		printf("���ڵ带���� ��");
		gotoxy(24, 28);
		printf("���ϸ� ����̦�");
		gotoxy(24, 29);
		printf("��  �ʹ����� ��");
		gotoxy(24, 30);
		printf("��������������������������");








		gotoxy(20, 35);
		printf("!!!!!!������ ���ӽ���!!!!!!");
		fflush(stdin);
		Sleep(300);
		while (1)
			if (_kbhit())		// �ٽý��� �� �ش� ȭ������ �Ѿ�� �ʰ� �ٷ� ����� ȭ������ ���� ������ �ذ��ϱ� ���� ����.
			{
				ch = _getch();
				break;
			}
		gotoxy(20, 35);
		printf("                                      ");
		Sleep(300);

		if (_kbhit())		//�Է��� �޾� ����.
		{
			ch = _getch();
			break;
		}
	}
	system("cls");
}
void printBound()	//���� ��� ���� �� map 2���� �迭�� �ʱ�ȭ�� ����ϴ� �Լ�
{
	int x, y;
	for (y = 0; y < MAX_Y; y++)
	{
		for (x = 0; x < MAX_X; x += 2)
		{
			if (y < 2)
			{
				printf("  ");
				map[y][x] = BLANK;
				map[y][x + 1] = BLANK;

			}
			else if (y == 2 || y == MAX_Y - 1 || x == 0 || x == MAX_X - 2) {
				printf("��");		//2����Ʈ
				map[y][x] = WALL;
				map[y][x + 1] = WALL;
			}
			else {
				if (map[y][x] != WALL)
				{
					printf("  ");
					map[y][x] = BLANK;
					map[y][x + 1] = BLANK;
				}


			}
		}
	}
}
void displayLevel(int level)			// Level�� ����Ͽ� �����ִ� �Լ�.
{
	gotoxy(0, 0);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("Level : %d", level);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
}
void displayEnemyNum(int num)			//���� �� ���� �����ִ� ����� ����ϴ� �Լ�.
{
	gotoxy(20, 0);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("���� �� : %d", num);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);

}
void displayTimer(int dest, int sec)	// '���� �ð�'�� �����ִ� ����� ����ϴ� �Լ�.
{
	sec = dest - sec;
	int min;
	min = sec / 60;
	sec = sec % 60;
	gotoxy(20, 1);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("���ѽð� : %02d�� %02d�� ����", min, sec);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
}
void displayScore(int sc)	// ������ �����ִ� ����� ����ϴ� �Լ�.
{
	gotoxy(0, 1);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("Score : %d", sc);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
}
void clearReadBuffer_2() {
	fseek(stdin, 0, SEEK_END);
}
void displayEndScreen(int score)	//���ӿ���ȭ�� �Լ�
{


	system("cls");			//�ܼ�â ����
	clearReadBuffer_2();

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);	//���ӿ���ȭ�� �� - ���� ����, - FAIL ����
	gotoxy(5, 3);
	printf("�ءءءءءء�\n     �ءءءءءء�\n     �ءءءءءء�\n     �ءء�\n     �ءء�\n     �ءء�\n     �ءءءءءء�\n     �ءءءءءء�\n     �ءءءءءء�\n     �ءء�\n     �ءء�\n     �ءء�\n     �ءء�\n");
	gotoxy(29, 3);
	printf("��\n");
	gotoxy(28, 4);
	printf("�ء�\n");
	gotoxy(27, 5);
	printf("�ءء�\n");
	gotoxy(26, 6);
	printf("�ءءء�\n");
	gotoxy(25, 7);
	printf("�ء�  �ء�\n");
	gotoxy(24, 8);
	printf("�ء�    �ء�\n");
	gotoxy(23, 9);
	printf("�ءءءءءء�\n");
	gotoxy(22, 10);
	printf("�ءءءءءءء�\n");
	gotoxy(21, 11);
	printf("�ءء�      �ءء�\n");
	gotoxy(20, 12);
	printf("�ءء�        �ءء�\n");
	gotoxy(19, 13);
	printf("�ءء�          �ءء�\n");
	gotoxy(18, 14);
	printf("�ءء�            �ءء�\n");
	gotoxy(17, 15);
	printf("�ءء�              �ءء�\n");
	gotoxy(44, 3);
	printf("�ءءءء�\n");
	gotoxy(44, 4);
	printf("�ءءءء�\n");
	gotoxy(44, 5);
	printf("�ءءءء�\n");
	gotoxy(46, 6);
	printf("�ءء�\n");
	gotoxy(46, 7);
	printf("�ءء�\n");
	gotoxy(46, 8);
	printf("�ءء�\n");
	gotoxy(46, 9);
	printf("�ءء�\n");
	gotoxy(46, 10);
	printf("�ءء�\n");
	gotoxy(46, 11);
	printf("�ءء�\n");
	gotoxy(46, 12);
	printf("�ءء�\n");
	gotoxy(44, 13);
	printf("�ءءءء�\n");
	gotoxy(44, 14);
	printf("�ءءءء�\n");
	gotoxy(44, 15);
	printf("�ءءءء�\n");
	gotoxy(55, 3);
	printf("�ءء�\n");
	gotoxy(55, 4);
	printf("�ءء�\n");
	gotoxy(55, 5);
	printf("�ءء�\n");
	gotoxy(55, 6);
	printf("�ءء�\n");
	gotoxy(55, 7);
	printf("�ءء�\n");
	gotoxy(55, 8);
	printf("�ءء�\n");
	gotoxy(55, 9);
	printf("�ءء�\n");
	gotoxy(55, 10);
	printf("�ءء�\n");
	gotoxy(55, 11);
	printf("�ءء�\n");
	gotoxy(55, 12);
	printf("�ءء�\n");
	gotoxy(55, 13);
	printf("�ءءءءءء�\n");
	gotoxy(55, 14);
	printf("�ءءءءءء�\n");
	gotoxy(55, 15);
	printf("�ءءءءءء�\n");


	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);		//�Ͼ��
	gotoxy(MAX_X / 2 - 10, MAX_Y / 2);									//���ӿ��� ȭ�鿡���� ���ȭ��. Y/N�� ���� main�Լ����� �޴´�.
	printf("���� ���� : %d", score);
	gotoxy(MAX_X / 2 - 10, MAX_Y / 2 + 10);
	printf("(���� �ձ��ڸ� �ν��մϴ�.)");
	gotoxy(MAX_X / 2 - 10, MAX_Y / 2 + 20);
	printf("�ٽ� �Ͻðڽ��ϱ�? (Y/N) : ");


}
void shootBullet(Bullet * b, Plane * p, int angle)	//�Ѿ��� �� �� �����ϴ� �Լ�.
{


	p->bulletSelector = p->bulletSelector%p->maxShotBlock;	//bulletSelector�� �󸶳� �ö󰬴� 0~maxShotBlock ���̿��� �����ֵ��� �����ش�.



	b->isSpawned = 1;										//�Ѿ��� ��ȯ�Ǿ����� ����

	b->x = p->x + p->attack_x[p->bulletSelector];			//�Ѿ��� ��ǥ�� �켱������ attack_x[bulleteSelector],  attack_y[bulleteSelector]�� ����.
	b->y = p->y + p->attack_y[p->bulletSelector];

	if (angle == 0)
		b->y = p->y + p->attack_y[p->bulletSelector] - 1;	//�Ѿ��� ����� ��ǥ. SHOTBLOCK���� 1ĭ ������ �߻�.


	if (angle == 180)
		b->y = p->y + p->attack_y[p->bulletSelector] + 1;	//�Ѿ��� ����� ��ǥ. SHOTBLOCK���� 1ĭ �Ʒ����� �߻�.

	if (angle == 90)
		b->x = p->x + p->attack_x[p->bulletSelector] + 2;	//�Ѿ��� ����� ��ǥ. SHOTBLOCK���� 2ĭ �����ʿ��� �߻�.

	if (angle == 270)
		b->x = p->x + p->attack_x[p->bulletSelector] - 2;	//�Ѿ��� ����� ��ǥ. SHOTBLOCK���� 2ĭ ���ʿ��� �߻�.


	p->bulletSelector++;	// bulletSelector�� ���� �����Ͽ� �ٸ� SHOTBLOCK���� ����ϱ� ������.

	if (p->bulletSelector >= p->maxShotBlock)	// maxShotBlock�� ������ �ִ��̱� ������ bulletSelector�� �� �̻��� �Ǿ������ ������ �߻��Ѵ�. �׷��Ƿ� maxShotBlock �ȿ��� bulletSelector ������ ���ؾ� �Ѵ�.
	{
		p->bulletSelector = p->bulletSelector - p->maxShotBlock; // �Լ��� Ư�� �� �� if������ ������ ���� p->bulletSelector = p->maxShotBlock�� ����̹Ƿ� �� ���� ���ָ� 0�� �Ǵµ� �̷� �ٽ� bulletSelector�� �����Ѵ�.
	}	//��� �� if���� ������ �̹� Selector�� ����ְ� �ֱ� ������ ������ �ʴ´�. ������ ������ �� ��츦 ����Ͽ� ���ܳ��� �ִ�.

	if (p->id == PLAYER)		//p�� �÷��̾��� ���
	{

		//PlaySound(TEXT("gun2.wav"), NULL, SND_FILENAME | SND_ASYNC); // �÷��̾ �� �� ��� ȿ����(�ѼҸ�) ����
	}


	displayBullet(b);	//�Ѿ��� ȭ�鿡 ��Ÿ���� ��

}
void deleteEntity(Plane *p) // �ؼ� �״�� p��� ����⸦ ȭ�鿡�� �����ִ� ������ �Ѵ�. ������ �� ����Ⱑ �÷��̾��� ����Ⱑ �浹�ߴ��� ���ߴ��� �˻��� �ִ� �Լ��̱⵵ �ϴ�.
{
	int i, j;
	for (i = 0; i<p->max_y; i++)		//p�� ����� �ִ� y��ǥ - p->max_y
	{
		for (j = 0; j<p->max_x; j++)	//p�� ����� �ִ� x��ǥ - p->max_x
		{
			gotoxy(p->x + j, p->y + i);	//�ܼ� �󿡼��� ������� �ش� gotoxy�� �̵���.
			if (p->model[i][j] == BLOCK || p->model[i][j] == SHOTBLOCK || p->model[i][j] == R_SHOTBLOCK || p->model[i][j] == RIGHT_SHOTBLOCK || p->model[i][j] == LEFT_SHOTBLOCK)	// �𵨿� �� ������ �ƴ� ���
			{
				if (p->id == PLAYER)	//���� �÷��̾���(Move���� �˴ٽ���, �� deleteEntity�� �밳 ����Ⱑ ������ �� ���δ�. ��, PLAYER�� ������ �� p�� �÷��̾ �ǰ�, ENEMY�� ������ �� p�� ENEMY�� �ȴ�.)
				{
					if (map[p->y + i][p->x + j] >= 0)	// ���� �÷��̾��� ����� ��ǥ�� ���� ����Ⱑ �ɷ����� ���
					{
						Me.isDead = 1;					//�÷��̾�� ���� ������ ó��
						Me.isDisplayed = 0;				//ǥ�õ��� �ʵ��� ��
					}
				}
				else {					//���� �÷��̾ �ƴҰ��, �� ���ϰ��
					if (map[p->y + i][p->x + j] == PLAYER)	// �ش� ���� ����� ��ǥ�� �÷��̾��� ����Ⱑ �ɷ����� ���
					{
						Me.isDead = 1;					// �÷��̾�� ���� ������ ó��
						Me.isDisplayed = 0;				//ǥ�õ��� �ʵ��� ��
					}
				}
				map[p->y + i][p->x + j] = BLANK;		//�ʻ󿡼��� �ش� ��ǥ�� BLANK�� ��. �� ������ map�󿡼���, ���� ȭ��󿡼��� ��������.
				map[p->y + i][p->x + j + 1] = BLANK;	//map���� ����� 2����Ʈ�� �����Ͽ��� ������ �̷� ������� ������ �Ͽ����µ�, ��ǥ�� BLANK�� ä�� ���� ������ �̸� ó���ؾ���.
				printf("  ");		//ȭ�� �󿡼� �ش� ��ǥ�� ���.
			}
		}
	}
}
void displayPlane(Plane * p)	//����⸦ ȭ�鿡 ǥ�����ִ� �Լ�. ���� �ʻ� ������� ��ġ�� ��������ִ� �Լ��̱⵵ �ϴ�.
{
	int i, j;


	if (p->id == PLAYER)	//p�� �÷��̾��� �������
	{

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), PLAYER_COLOR);	//PLAYER_COLOR�� �ش��ϴ� ������ ����� ���� �����ϰ�
	}
	else {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ENEMY_COLOR);	//ENEMY_COLOR�� �ش��ϴ� ������ ����� ���� �����Ѵ�.
	}

	for (i = 0; i<PLANE_MAX_Y; i++)		//�� �ݺ����� ����� ���� �������� �ϳ��ϳ� �˻��Ͽ� Ư�� ����� �����ϱ� �����̴�.
	{
		for (j = 0; j<PLANE_MAX_X; j++)
		{
			gotoxy(p->x + j, p->y + i);		//���� ��ġ�� map�� Ư�� ��ǥ�� �̵�

			if (p->model[i][j] == BLOCK)	//����� �� �� BLOCK�� ��ġ�ؾ� �� ��ǥ�� ���
			{
				printf("��");				//BLOCK�� ��ġ��Ŵ.
				map[p->y + i][p->x + j] = p->id;		//p ������� ������ȣ�� �ʿ� �����Ŵ
				map[p->y + i][p->x + j + 1] = p->id;	//p ������� ������ȣ�� �ʿ� �����Ŵ, �ϳ��� ���� 2����Ʈ�� �����ϱ� ������ map[p->y + i][p->x + j + 1]�� ������ȣ�� ������Ѿ� �Ѵ�.
			}
			else if (p->model[i][j] == SHOTBLOCK) {		//����� �� �� SHOTBLOCK�� ��ġ�ؾ� �� ��ǥ�� ���
				printf("��");				//SHOTBLOCK�� ��ġ��Ŵ
				map[p->y + i][p->x + j] = p->id;		//p ������� ������ȣ�� �ʿ� �����Ŵ
				map[p->y + i][p->x + j + 1] = p->id;	//p ������� ������ȣ�� �ʿ� �����Ŵ, �ϳ��� ���� 2����Ʈ�� �����ϱ� ������ map[p->y + i][p->x + j + 1]�� ������ȣ�� ������Ѿ� �Ѵ�.
			}
			else if (p->model[i][j] == R_SHOTBLOCK) {	//����� �� �� R_SHOTBLOCK�� ��ġ�ؾ� �� ��ǥ�� ���
				printf("��");				//R_SHOTBLOCK�� ��ġ��Ŵ
				map[p->y + i][p->x + j] = p->id;		//p ������� ������ȣ�� �ʿ� �����Ŵ
				map[p->y + i][p->x + j + 1] = p->id;	//p ������� ������ȣ�� �ʿ� �����Ŵ, �ϳ��� ���� 2����Ʈ�� �����ϱ� ������ map[p->y + i][p->x + j + 1]�� ������ȣ�� ������Ѿ� �Ѵ�.
			}
			else if (p->model[i][j] == RIGHT_SHOTBLOCK) {	//����� �� �� RIGHT_SHOTBLOCK�� ��ġ�ؾ� �� ��ǥ�� ���
				printf("��");				//RIGHT_SHOTBLOCK�� ��ġ��Ŵ
				map[p->y + i][p->x + j] = p->id;		//p ������� ������ȣ�� �ʿ� �����Ŵ
				map[p->y + i][p->x + j + 1] = p->id;	//p ������� ������ȣ�� �ʿ� �����Ŵ, �ϳ��� ���� 2����Ʈ�� �����ϱ� ������ map[p->y + i][p->x + j + 1]�� ������ȣ�� ������Ѿ� �Ѵ�.
			}
			else if (p->model[i][j] == LEFT_SHOTBLOCK) {	//����� �� �� LEFT_SHOTBLOCK�� ��ġ�ؾ� �� ��ǥ�� ���
				printf("��");				//LEFT_SHOTBLOCK�� ��ġ��Ŵ
				map[p->y + i][p->x + j] = p->id;		//p ������� ������ȣ�� �ʿ� �����Ŵ
				map[p->y + i][p->x + j + 1] = p->id;	//p ������� ������ȣ�� �ʿ� �����Ŵ, �ϳ��� ���� 2����Ʈ�� �����ϱ� ������ map[p->y + i][p->x + j + 1]�� ������ȣ�� ������Ѿ� �Ѵ�.
			}
		}
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);	//�� ������� ������

	p->isDisplayed = 1;		//����Ⱑ ȭ�鿡 ��Ÿ������ ��.
}
void Move(Plane *p, int key)				//�÷��̾ �� ����⸦ �̵���Ű�� �Լ� UP, RIGHT, LEFT, DOWN ���� key�� �޾� key�� ���� �����̵��� �Ѵ�.
{
	switch (key)							//switch�� ��� - UP�� ���, - DOWN�� ���, - RIGHT�� ���, -LEFT�� ���
	{

	case UP:
		if (checkBlocked(p, UP) == FALSE)		//���� ���� ���� ������ ���ٸ�
		{
			deleteEntity(p);					//��� ����⸦ �����(�Ⱥ��̰� �ϰ�)
			p->y -= 1;							//�������� 1ĭ �̵�
		}
		break;
	case DOWN:
		if (checkBlocked(p, DOWN) == FALSE)		// �Ʒ��� ���� ���� ������ ���ٸ�
		{
			deleteEntity(p);					//��� ����⸦ �����(�Ⱥ��̰� �ϰ�)
			p->y += 1;							//�Ʒ������� 1ĭ �̵�
		}
		break;
	case LEFT:
		if (checkBlocked(p, LEFT) == FALSE)		// ���� ���� ���� ������ ���ٸ�
		{
			deleteEntity(p);					//��� ����⸦ �����(�Ⱥ��̰� �ϰ�)
			p->x -= 1;							//�������� 1ĭ �̵�
		}
		break;
	case RIGHT:
		if (checkBlocked(p, RIGHT) == FALSE)	// ������ ���� ���� ������ ���ٸ�
		{
			deleteEntity(p);					//��� ����⸦ �����(�Ⱥ��̰� �ϰ�)
			p->x += 1;							// ���������� 1ĭ �̵�
		}
		break;

	}


	displayPlane(p);	//�ٽ� ����⸦ ��Ÿ����
}
void PlayerControl(Plane *p)			//�÷��̾ ��� Ű�� �������� �Ǵ��Ͽ� �����̵��� �����ִ� �Լ�
{

	if (p->id == PLAYER && p->isDead == 0)		// ������� ������ȣ�� Player�� ������ȣ�̰� �� ����Ⱑ ���� �ʾҴٸ�
	{

		if (GetAsyncKeyState(VK_LEFT)) {		// ���� Ű�� ������

			Move(p, LEFT);						// �������� �����δ�

		}
		else if (GetAsyncKeyState(VK_RIGHT)) {	// ������ Ű�� ������

			Move(p, RIGHT);						// ���������� �����δ�

		}

		if (GetAsyncKeyState(VK_UP)) {			// ���� Ű�� ������
			Move(p, UP);						// �������� �����δ�

		}
		else if (GetAsyncKeyState(VK_DOWN)) {	// �Ʒ��� Ű�� ������

			Move(p, DOWN);						// �Ʒ������� �����δ�

		}


	}



}
void eraseBullet(Bullet * b) // �Ѿ��� ����� �Լ�
{
	gotoxy(b->x, b->y);		//�Ѿ��� ��ġ�� Ŀ���� �Ű�
	printf(" ");			// �����
	map[b->y][b->x] = BLANK;	// map �󿡼��� �ƹ��͵� ���� ���·� �����.

}
void moveBullet(Bullet * b, int dir) // �Ѿ��� �����̴� �Լ�
{
	int id;							//������ȣ ����� ���� ����
	eraseBullet(b);  // ��ġ �缳���� ���� �Ѿ��� ��� ȭ�鿡�� �����

	if (dir == 0)					//�Ѿ��� ���� 0���϶�
	{
		b->y = b->y - 1;  // �Ѿ��� ��ǥ�� �������� �̵���Ŵ



		if (map[b->y][b->x] >= 0) // ������ ������� id�� �� ������� ��ǥ �� ��ġ�� �����Ͽ���. ������ ID �̿� �ٸ� ������ Map ������ ��� ������ �Ͽ��� ������ �̷��� ������ ����� �� �־���.
		{
			id = map[b->y][b->x];			// map���� ���� ��ġ�� �� ���� id�� ����Ǿ� �ִ�. �׷��Ƿ� �̸� �޴´�.
			enemy[id].hp = enemy[id].hp - 1;   // �� �� �¾��� ��� ���� ü���� 1 ��´�.
			if (enemy[id].hp <= 0)              // ���� ü���� 0 �����ϰ��
			{
				score++;               //���� 1�� ȹ��.
				displayScore(score);	//���� ������Ʈ
				enemy[id].isDead = 1; // ���� ������ �˸�.
				enemy[id].isDisplayed = 0;	// ���̻� ȭ���� ǥ�õ��� �ʵ��� ��������
				deleteEntity(&enemy[id]);	// ȭ�鿡�� ����.
				displayed_enemy--;			//�����ִ� �� ������ id������ȣ�� ����⸦ ����
			}
			b->isSpawned = 0;				//�Ѿ��� ǥ�õ��� �ʵ��� ��������
			eraseBullet(b);					//�Ѿ��� ����
			return;							//�Լ� ����


		}

		if (b->y < 3 + 1)					// 0���� �����̹Ƿ� �Ѿ��� �� ������ Ƣ����� �ȵǱ� ������ �̸� �������� ����. ���� ���� �� ���� �Ѿ��� ������
		{

			b->isSpawned = 0;				// �Ѿ��� ǥ�õ��� �ʵ��� ����
			eraseBullet(b);					//�Ѿ��� ����
			return;							//�Լ� ����

		}
	}

	if (dir == 180)	// ���� ������ �����̳� ���鿡�Ը� �ش��. 180���� �Ѿ��� �߻��� �� �ִ� ������ ���� ���̴�. �Ʒ� 90��, 270���� ����������.
	{

		b->y = b->y + 1;	// �Ѿ��� ��ǥ�� �Ʒ������� �̵���Ŵ

		if (map[b->y][b->x] == Me.id)	//map���� �Ѿ��� ��ġ�� ��ǥ�� �ִ� ���� PLAYER�� ���
		{
			Me.isDead = 1;				// PLAYER�� ����
			Me.isDisplayed = 0;			// ���̻� ȭ�鿡 ǥ�õ��� �ʵ��� ����
			deleteEntity(&Me);			// PLAYER�� ȭ�鿡�� ����
			b->isSpawned = 0;			// �Ѿ��� ǥ�õ��� �ʵ��� ����
			eraseBullet(b);				//�Ѿ��� ����
			return;						//�Լ� ����
		}
		if (b->y >= MAX_Y - 2)			// �Ѿ��� �ٴ� ���� ���� �� �� ���
		{
			b->isSpawned = 0;			//�Ѿ��� ǥ�õ��� �ʵ��� ����
			eraseBullet(b);				//�Ѿ��� ����
			return;
		}
	}

	if (dir == 90)						//�� ���������� �߻��� ���
	{

		b->x = b->x + 1;
		if (map[b->y][b->x] == Me.id)
		{
			Me.isDead = 1;
			Me.isDisplayed = 0;
			deleteEntity(&Me);
			b->isSpawned = 0;
			eraseBullet(b);
			return;
		}
		if (b->x >= MAX_X - 3)		//�Ѿ��� ���� ������ ���� �հ� ���� �� ���� ���
		{
			b->isSpawned = 0;
			eraseBullet(b);

			return;
		}
	}

	if (dir == 270)							// �� �������� �߻��� ���
	{

		b->x = b->x - 1;
		if (map[b->y][b->x] == Me.id)		//�ش� �Ѿ��� �÷��̾�� ����� ���
		{
			Me.isDead = 1;					//����
			Me.isDisplayed = 0;				//�÷��̾ ȭ�鿡�� ǥ�õ��� �ʵ��� ����
			deleteEntity(&Me);				//����⸦ �����
			b->isSpawned = 0;				//�Ѿ��� ǥ�õ��� �ʵ��� ����
			eraseBullet(b);
			return;
		}


		if (b->x <= 3)			//�Ѿ��� ���� ���� ���� �հ� ���� �� ���� ���
		{
			b->isSpawned = 0;	//�Ѿ��� ǥ�õ��� �ʵ��� ����
			eraseBullet(b);		//�Ѿ��� �����

			return;
		}
	}

	displayBullet(b);		//�Ѿ��� ȭ�鿡 ��Ÿ����
}
void autoPlaneMaxPatch(Plane * p)   //����⸦ ���� ���� �� �ڵ����� ����� ���� �����ʰ� ���� ������ ��ǥ�� ����Ͽ� �����ϴ� �Լ��̴�.
{
	int maxX = 0, maxY = 0;			// ���� �ִ�, ���� �ִ��� ������ �� ���� ����.
	int i, j;
	for (i = 0; i<PLANE_MAX_Y; i++)	// �ִ�� ������ �� �ִ� ����� ũ��� ���� �ϳ��ϳ� ã��.
	{
		for (j = 0; j<PLANE_MAX_X; j++)
		{
			if (p->model[i][j] == BLOCK || p->model[i][j] == SHOTBLOCK || p->model[i][j] == R_SHOTBLOCK || p->model[i][j] == RIGHT_SHOTBLOCK || p->model[i][j] == LEFT_SHOTBLOCK)	//�� ������ �ƴ� ��� ���̶� �ִٸ�
			{
				if (j > maxX)
				{
					maxX = j;         //���� ������ �κ��� X��ǥ�� maxX�� ����
				}

				if (i > maxY)
				{
					maxY = i;         //���� �Ʒ��� �κ��� Y��ǥ�� maxY�� ����
				}
			}
		}
	}


	p->max_x = maxX + 1;      // ������� ������ ���� ��, �� 2����Ʈ�̹Ƿ� + 1�� �ٿ��־� ������ ���� �پ��� �� ���� �ѼյǴ� ��Ȳ�� ����.
	p->max_y = maxY + 1;      // maxY�� 0���� �����ϴ� ��ǥ �� ��ġ�̱� ������ �Ʒ��� ���� ���� �ʰ� �ϱ� ���ؼ��� ������� ���� '����'�� �����ؾ� �ϹǷ� +1�� �ٿ��ش�.

}

void enemyControl(Plane *p)		//���� ���� �ε����� �� �̵������� �缳����.
{
	if (p->id != PLAYER && p->isDisplayed == 1)		// ���� ID�� �÷��̾ �ƴϰ� ȭ�鿡 ��Ÿ�� �ִٸ�
	{
		if (p->type == ENEMY_REGULAR) // ���� type�� ���η� �߻��ϴ� Ÿ���� ��� LEFT-RIGHT
		{
			if (checkBlocked(p, p->dir) == 0)	//
			{
				return;
			}
			else {
				p->dir = p->dir % 2 + 1;	//RIGHT�̸� LEFT��, LEFT�̸� RIGHT��
			}
		}

		if (p->type == ENEMY_REVERSE)		//���� type�� ���η� �߻��ϴ� Ÿ���ΰ�� UP-DOWN
		{
			if (checkBlocked(p, p->dir) == 0)	//���� �ε����� �ʾҴٸ�
			{
				return;			// �� ���� �����ϰ� ����
			}
			else {
				p->dir = p->dir % 2 + 3; // UP�̸� DOWN����, DOWN�̸� UP����
			}
		}
	}
}
void planeShotBlockSet(Plane * p)		//����� �𵨿��� SHOTBLOCK�� ã�� �� ������ �Ѿ��� ���� �� �ֵ��� �������ִ� �Լ�
{
	int i, j, k;

	for (k = 0; k<p->maxShotBlock; )      //k�� �ݺ������� ������ ���� �����Ҽ� �ִ� SHOTBLOCK�� ��ȣ(k)���� x,y�� ���� ������ �־�� �ϱ� ����..
	{

		for (i = 0; i<PLANE_MAX_Y; i++)            // i�� ����� �� 2���� �迭���� y(����)�� �ǹ���.
		{
			for (j = 0; j<PLANE_MAX_X; j++)         // j�� ����� �� 2���� �迭���� x(����)�� �ǹ���.
			{
				if ((p->id == PLAYER && p->model[i][j] == SHOTBLOCK) || (p->id != PLAYER && p->model[i][j] == R_SHOTBLOCK) || (p->id != PLAYER && p->model[i][j] == RIGHT_SHOTBLOCK) || (p->id != PLAYER && p->model[i][j] == LEFT_SHOTBLOCK) || (p->id != PLAYER && p->model[i][j] == SHOTBLOCK))     // ����� �� 2���� �迭 �� SHOTBLOCK�� ã�� ���� �����ϵ��� �ڵ��������ش�.
				{

					p->attack_x[k] = j + 1;         // ���� x,y�� �Ѿ��� �߻� �� �� �ִ� ���� ��ġ������ �����Ѵ�.
					p->attack_y[k] = i;
					k++;                     // k++�� �������� maxShotBlock���� ShotBlock�� ã�� �� ���������� �����ش�.
				}
			}
		}
	}
}
void clearPlane(Plane * p)	//����� �� ������ ��� ��� '�ʱ�ȭ' �ϴ� �Լ�. ������ �� ����.
{
	int i, j;
	for (i = 0; i<PLANE_MAX_Y; i++)	//�ݺ��� ���, �ش� ����� �𵨿� �ִ� '���' ���� �� �񵵷� ����.
	{
		for (j = 0; j<PLANE_MAX_X; j++)
		{
			p->model[i][j] = EMPTY;
		}
	}
}
void enemyConfigure(int id, int _x, int _y, int delay, int _mspeed, int _bspeed, int direction, int hp)
{
	enemy[id].x = _x;			// ���� x��ǥ
	enemy[id].y = _y;			//���� y��ǥ
	enemy[id].bulletdelay = delay;	// ���� �Ѿ� ������(�Ѿ��� '���' �ӵ�)
	enemy[id].movespeed = _mspeed;	// ���� �����̴� �ӵ�
	enemy[id].bulletspeed = _bspeed;	// ���� �Ѿ� �ӵ�(�Ѿ��� '���ư���' �ӵ�)
	autoPlaneMaxPatch(&enemy[id]);		//�ش� �� ������� �ִ� y��ǥ, �ִ� x��ǥ�� ���� �����ϴ� �Լ� ����.
	planeShotBlockSet(&enemy[id]);		// ShotBlock�� �����Ͽ� ���� �Ѿ��� �߻��� �� �ְ� ��.
	enemy[id].dir = direction;			// ���� �����̴� ����. UP, DOWN, RIGHT, LEFT�� �ִ�.
	enemy[id].hp = hp;					// ���� ü��.
	enemy[id].isDead = 0;				// ���� ������ ����.
}
void enemySpawnAsCount(int count) // ���� ���ϴ� Ư�� �ð��� ���� �����ϵ��� �����ִ� �Լ�. ��������� ȭ�� �⿬ ����, �� ������� �ʱ� ��ǥ�� �� ������� ���, �Ѿ��� ��� �ӵ��� �����ϴ� �� �������� �缳���� �Ѵ�.
{


	if (lev == 1) // 1�ܰ� �ð� = 15�� �� count�� ȯ�� �� 15 * 200 count
	{

		if (count == 200)		//������ 1�̸� �� ī��Ʈ�� 200�� ���
		{
			enemy[1].isDisplayed = 1;	//���� ���̵��� ��.
			enemyConfigure(1, MAX_X / 2 + 10, MAX_Y / 3, 20, 10, 10, RIGHT, 3);		//�� �⺻������ �ٲ�.

			displayed_enemy++;				//���� ������ �ش� ���� �߰���.
		}



		if (count == 300)	// ���� ������ ����, count == 300�� ���
		{
			enemy[2].isDisplayed = 1;	// ���� ����
			enemyConfigure(2, MAX_X / 2 - 16, MAX_Y / 3, 20, 10, 10, LEFT, 3);

			displayed_enemy++;
		}

		if (count == 500)		//...���� ������ ����
		{
			enemy[3].isDisplayed = 1;		//...
			enemyConfigure(3, MAX_X / 2 + 5, MAX_Y / 4, 20, 10, 9, LEFT, 5);

			displayed_enemy++;
		}

		if (count == 600)		//���� ������ ����
		{
			enemy[4].isDisplayed = 1;
			enemyConfigure(4, MAX_X / 2 - 5, MAX_Y / 4, 20, 8, 10, RIGHT, 5);

			displayed_enemy++;		//...
		}
		if (count == 800)		//1���� ���� �����, �� ������ �����ϳ� ���� �ٸ�
		{
			enemy[5].isDisplayed = 1;	//���̵��� ����.
			clearPlane(&enemy[5]);		//�� ������� �⺻ ���� ����.
			enemy[5].model[0][0] = BLOCK;	// ���� ���� ����.
			enemy[5].model[0][4] = BLOCK;
			enemy[5].model[1][0] = BLOCK;
			enemy[5].model[1][2] = BLOCK;
			enemy[5].model[1][4] = BLOCK;
			enemy[5].model[2][0] = R_SHOTBLOCK;
			enemy[5].model[2][2] = R_SHOTBLOCK;
			enemy[5].model[2][4] = R_SHOTBLOCK;
			enemy[5].maxShotBlock = 3;		// �ش� �� ����Ⱑ ����� �� �ִ� ShotBlock�� ������ ����. R_SHOTBLOCK�� 3�� �����Ƿ� 3�� ���´�.
			enemyConfigure(5, MAX_X / 2, MAX_Y / 6, 20, 10, 10, LEFT, 50);	//...

			displayed_enemy++;		//...
		}

	}

	if (lev == 2)			//������ 2�� �Ǿ��� ���
	{
		if (count == 50)		//������ 2�̸� count�� 50�� ���
		{
			enemy[6].isDisplayed = 1;		//���� ���̰� �Ѵ�.
			enemyConfigure(6, MAX_X / 2 + 27, MAX_Y / 6, 15, 7, 4, LEFT, 5); // ���� �⺻ ������ �缳��.

			displayed_enemy++;		// �����ִ� ���� ���� �ش� ����⸦ �߰�.
		}
		if (count == 50)				//���� ������ ����
		{
			enemy[7].isDisplayed = 1;
			enemyConfigure(7, MAX_X / 2 - 27, MAX_Y / 6, 15, 7, 4, RIGHT, 5);

			displayed_enemy++;
		}
		if (count == 150)			//���� ������ ����
		{
			enemy[8].isDisplayed = 1;
			enemyConfigure(8, MAX_X / 2 + 22, MAX_Y / 5, 15, 7, 4, LEFT, 7);

			displayed_enemy++;
		}
		if (count == 150)			//���� ������ ����
		{
			enemy[9].isDisplayed = 1;
			enemyConfigure(9, MAX_X / 2 - 22, MAX_Y / 5, 15, 7, 4, RIGHT, 7);

			displayed_enemy++;
		}
		if (count == 500)			//�� ���� 1 ���� ������ ������ ����
		{
			clearPlane(&enemy[10]);
			enemy[10].model[0][0] = BLOCK;
			enemy[10].model[1][0] = RIGHT_SHOTBLOCK;
			enemy[10].model[2][0] = BLOCK;
			enemy[10].maxShotBlock = 1;
			enemy[10].isDisplayed = 1;


			enemy[10].type = ENEMY_REVERSE;			//Ư�̻��� : �� ������ �Ѿ��� ���������� �߻��ϹǷ� type�� bulletdir�� ����.
			enemy[10].bulletdir = 90;				// �⺻ = 180 - �Ʒ���, 90 - ������  270 - ����

			enemyConfigure(10, 2, MAX_Y / 6, 35, 6, 6, DOWN, 20);

			displayed_enemy++;
		}


		if (count == 500)					//���� ������ ����.
		{
			clearPlane(&enemy[11]);
			enemy[11].model[0][0] = BLOCK;
			enemy[11].model[1][0] = LEFT_SHOTBLOCK;
			enemy[11].model[2][0] = BLOCK;
			enemy[11].maxShotBlock = 1;
			enemy[11].isDisplayed = 1;


			enemy[11].type = ENEMY_REVERSE;
			enemy[11].bulletdir = 270;				// �̹����� �������� �Ѿ��� �߻��ϴ� �����.

			enemyConfigure(11, MAX_X - 4, MAX_Y / 6, 35, 6, 6, DOWN, 20);

			displayed_enemy++;
		}

		if (count == 1300)						//������ ����
		{
			enemy[12].isDisplayed = 1;			//ȭ�鿡 �����ش�. 2������ ���� �����.
			clearPlane(&enemy[12]);
			enemy[12].model[0][0] = SHOTBLOCK;
			enemy[12].model[0][4] = SHOTBLOCK;
			enemy[12].model[1][0] = BLOCK;
			enemy[12].model[1][2] = BLOCK;
			enemy[12].model[1][4] = BLOCK;
			enemy[12].model[2][0] = R_SHOTBLOCK;
			enemy[12].model[2][2] = R_SHOTBLOCK;
			enemy[12].model[2][4] = R_SHOTBLOCK;
			enemy[12].maxShotBlock = 3;
			enemyConfigure(12, MAX_X / 2 + 10, MAX_Y / 6, 20, 6, 4, LEFT, 100);

			displayed_enemy++;
		}
	}
	if (lev == 3)			//������ 3�� ���
	{
		if (count == 100)	// ������ 3�̰�, count�� 100�̸�
		{
			clearPlane(&enemy[13]);		// ������� �⺻ ���� �����.
			enemy[13].model[0][0] = BLOCK;
			enemy[13].model[1][0] = RIGHT_SHOTBLOCK;
			enemy[13].model[2][0] = BLOCK;
			enemy[13].maxShotBlock = 1;
			enemy[13].isDisplayed = 1;


			enemy[13].type = ENEMY_REVERSE;
			enemy[13].bulletdir = 90;		//���������� �Ѿ��� �߻��ϴ� ����.

			enemyConfigure(13, 2, MAX_Y / 6, 35, 6, 6, DOWN, 5);

			displayed_enemy++;
		}

		if (count == 100)			//���� ��� ������ ����
		{
			clearPlane(&enemy[14]);
			enemy[14].model[0][0] = BLOCK;
			enemy[14].model[1][0] = LEFT_SHOTBLOCK;
			enemy[14].model[2][0] = BLOCK;
			enemy[14].maxShotBlock = 1;
			enemy[14].isDisplayed = 1;


			enemy[14].type = ENEMY_REVERSE;
			enemy[14].bulletdir = 270;

			enemyConfigure(14, MAX_X - 4, MAX_Y / 6 + 23, 30, 6, 6, UP, 5);

			displayed_enemy++;
		}

		if (count == 200)
		{
			enemy[15].isDisplayed = 1;
			enemyConfigure(15, MAX_X / 2 + 10, MAX_Y / 6, 14, 5, 4, RIGHT, 10);
			displayed_enemy++;
		}

		if (count == 200)
		{
			enemy[16].isDisplayed = 1;
			enemyConfigure(16, MAX_X / 2 - 16, MAX_Y / 6, 14, 5, 4, LEFT, 10);
			displayed_enemy++;
		}

		if (count == 800)
		{
			enemy[17].isDisplayed = 1;
			enemyConfigure(17, MAX_X / 2 - 6, MAX_Y / 6 + 3, 10, 4, 5, RIGHT, 7);
			displayed_enemy++;
		}

		if (count == 1000)
		{
			clearPlane(&enemy[18]);
			enemy[18].model[0][0] = R_SHOTBLOCK;
			enemy[18].maxShotBlock = 1;
			enemy[18].isDisplayed = 1;
			enemyConfigure(18, 2, 3, 30, 6, 6, RIGHT, 3);
			displayed_enemy++;
		}

		if (count == 1100)
		{
			clearPlane(&enemy[19]);
			enemy[19].model[0][0] = R_SHOTBLOCK;
			enemy[19].maxShotBlock = 1;
			enemy[19].isDisplayed = 1;
			enemyConfigure(19, MAX_X - 4, 3, 27, 4, 6, LEFT, 3);
			displayed_enemy++;
		}

		if (count == 1400)
		{
			clearPlane(&enemy[20]);
			enemy[20].model[0][0] = R_SHOTBLOCK;
			enemy[20].model[0][2] = BLOCK;
			enemy[20].model[0][4] = R_SHOTBLOCK;
			enemy[20].model[0][6] = BLOCK;
			enemy[20].model[0][8] = R_SHOTBLOCK;

			enemy[20].maxShotBlock = 3;
			enemy[20].isDisplayed = 1;

			enemyConfigure(20, MAX_X / 2 - 5, 3, 15, 3, 3, RIGHT, 20);

			displayed_enemy++;
		}

		if (count == 1400)
		{
			clearPlane(&enemy[21]);
			enemy[21].model[0][0] = RIGHT_SHOTBLOCK;
			enemy[21].model[1][0] = BLOCK;
			enemy[21].model[2][0] = RIGHT_SHOTBLOCK;
			enemy[21].model[3][0] = BLOCK;
			enemy[21].model[4][0] = RIGHT_SHOTBLOCK;

			enemy[21].maxShotBlock = 3;
			enemy[21].isDisplayed = 1;
			enemy[21].bulletdir = 90;
			enemy[21].type = ENEMY_REVERSE;

			enemyConfigure(21, 2, 3, 8, 3, 3, DOWN, 30);

			displayed_enemy++;
		}

		if (count == 1800)
		{
			enemy[22].isDisplayed = 1;
			clearPlane(&enemy[22]);
			enemy[22].model[0][0] = SHOTBLOCK;
			enemy[22].model[0][4] = SHOTBLOCK;
			enemy[22].model[1][0] = BLOCK;
			enemy[22].model[1][2] = BLOCK;
			enemy[22].model[1][4] = BLOCK;
			enemy[22].model[2][0] = R_SHOTBLOCK;
			enemy[22].model[2][2] = R_SHOTBLOCK;
			enemy[22].model[2][4] = R_SHOTBLOCK;
			enemy[22].maxShotBlock = 3;
			enemyConfigure(22, MAX_X / 2 - 6, MAX_Y / 2 - 6, 17, 6, 3, LEFT, 50);

			displayed_enemy++;
		}

		if (count == 1800)
		{
			enemy[23].isDisplayed = 1;
			enemy[23].model[1][2] = R_SHOTBLOCK;
			enemy[23].maxShotBlock = 3;
			enemyConfigure(23, MAX_X / 2 - 6, MAX_Y / 2 - 9, 17, 6, 3, LEFT, 7);

			displayed_enemy++;
		}

		if (count == 2000)
		{
			enemy[24].isDisplayed = 1;
			clearPlane(&enemy[24]);
			enemy[24].model[0][0] = BLOCK;
			enemy[24].model[1][0] = R_SHOTBLOCK;
			enemy[24].model[0][5] = BLOCK;
			enemy[24].model[1][5] = R_SHOTBLOCK;
			enemy[24].model[0][10] = BLOCK;
			enemy[24].model[1][10] = R_SHOTBLOCK;
			enemy[24].model[0][16] = BLOCK;
			enemy[24].model[1][16] = R_SHOTBLOCK;
			enemy[24].model[0][21] = BLOCK;
			enemy[24].model[1][21] = R_SHOTBLOCK;
			enemy[24].model[0][26] = BLOCK;
			enemy[24].model[1][26] = R_SHOTBLOCK;
			enemy[24].maxShotBlock = 6;
			enemyConfigure(24, MAX_X / 2 - 6, MAX_Y / 2 - 9, 7, 2, 7, LEFT, 300);

		}


	}

	displayEnemyNum(displayed_enemy);		//���� �� ���� ������Ʈ�Ͽ� �����ش�.
}


// MAINNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN
int main()
{

	lev = 1;					//ó�� ������ 1�� ��. ���� ���� ����! 
	levelTimeLimit[1] = 15;    // 1���� �ð�����. ������ (��)
	levelTimeLimit[2] = 25;    // 2���� �ð�����. ������ (��)
	levelTimeLimit[3] = 30;    // 3����.. ���ϵ���


	int PLAYER_CAN_SHOT = 0;		//�÷��̾ Z�� XŰ�� ������ ��� 1�� �Ǵ� �Լ�.
	int i, j;						// �ݺ��� ����� ���� ����
	char cha;						//���ӿ��� ȭ�鿡�� ���ڸ� �Է¹��� ����
	int ReplayOrQuit;				// ���ӿ��� ȭ�鿡��, ������� ������ ���� ������ �����Ͽ� �ݺ����� ���������� ���ִ� ����.



									//-----------------------------------------------------





	while (1)
	{
		player_onBullet = 0;                    // player_onBullet�� �÷��̾ ���� ��� �ִ� �������� �ƴ����� �˻��ϱ� ���Ͽ� ���� ���������̴�. (���� ���ݸ��� ���� �� �� �ְ� ���ش�)
		score = 0;								//������ 0������
		displayed_enemy = 0;					//���� ǥ�õ� ���� 0������
		count = 0;								// ���� count(�ð�)�� 0����
		clearPlane(&Me);						// Me�� ����� ���� ����.
		Me.id = PLAYER;       // �÷��̾��� ����� id�� 1�� ����.
		Me.isDead = 0;			// �÷��̾ ���� ���� - 0, ���� - 1
		Me.isDisplayed = 1;		// �÷��̾ ȭ�� �� ��Ÿ�� �� �ְ� ���ִ� ����. 1 - ǥ�� 0 - ��ǥ��

		for (i = 0; i < ENEMY_NUM; i++) //�� ������� �⺻���� �����Ѵ�. Ư�� ������� ������ �ٽ� �ϱ� ���ؼ��� enemySpawnAsCount �Լ��� �̿��Ѵ�.
		{
			clearPlane(&enemy[i]); //�� ����� ���� ����.
			enemy[i].id = i;		//������ȣ ����
			enemy[i].type = ENEMY_REGULAR;		// ��-�Ʒ� �̵� ������, ��-������ �̵� ������ �˷��ش�. ENEMY_REGULAR - ��-������ ENEMY_REVERSE - ��-�Ʒ�
			enemy[i].dir = LEFT;				// ���� ������ ����
			enemy[i].isDisplayed = 0;			//���� ȭ�鿡 ǥ�� X
			enemy[i].model[0][0] = BLOCK;	//���� �⺻ ��
			enemy[i].model[0][2] = BLOCK;
			enemy[i].model[0][4] = BLOCK;
			enemy[i].model[1][0] = R_SHOTBLOCK;
			enemy[i].model[1][4] = R_SHOTBLOCK;
			enemy[i].maxShotBlock = 2;				//model �� ShotBlock�� ����
			enemy[i].bulletdelay = 100;				//�Ѿ��� �� ���� ������.
			enemy[i].movespeed = ENEMY_MOVESPEED;	// ENEMY_MOVESPEED�� �ӵ��� ������
			enemy[i].bulletspeed = 5;			//�⺻ �Ѿ˼ӵ� ����
			enemy[i].isDead = 0;				//���� ����
			enemy[i].hp = ENEMY_DEFAULT_HP;		//���� �⺻ ü�� ����
			enemy[i].bulletdir = 180;


			autoPlaneMaxPatch(&enemy[i]);
			planeShotBlockSet(&enemy[i]);
		}




		// ���� - ������ �迭���� ù��°�� y��(����), �ι�°�� x��(����)�̴�. �׷���, �� �ϳ� �� 2����Ʈ�� �����ϹǷ� ���� ���� �� y�� 1ĭ �� 1�� �ٴ� �ݸ� x�� ��ĭ �� 2ĭ�� �ڴ�.
		// ����: SHOTBLOCK�� ������ n�� ��� "#define PLAYER_MAX_ATTACKBLOCK n" ���� ������ �ش�. ������!!!


		//-------------------------------------------------------------- �𵨸� ����

		// SHOTBLOCK - �Ѿ��� �� �� �ִ� ��. �� ���
		// BLOCK - ����⸦ �����ϴ� ��. �� ���
		// R_SHOTBLOCK - �÷��̾� ���鿡���� ���ְ� �ٸ��ִ� �뵵, ������ �־�� �Ѿ��� ��� �÷��̾ ���� �� �ִ� ���̴�. �� ���
		// �� �̿ܿ��� LEFT_SHOTBLOCK, RIGHT_SHOTBLOCK ���� �ִ�.





		Me.model[0][0] = SHOTBLOCK;
		Me.model[1][0] = BLOCK;
		Me.model[2][0] = R_SHOTBLOCK;











		//--------------------------------------------------------------- �𵨸� ��


		Me.maxShotBlock = PLAYER_MAX_ATTACKBLOCK;	//�Ʒ� planeShotBlockSet �Լ��� �����ִ� ����.
		planeShotBlockSet(&Me);					//�Ѿ��� �� �� �ְ� ��������.







		Me.x = MAX_X / 2;
		Me.y = MAX_Y - 10;
		autoPlaneMaxPatch(&Me);                           //  �𵨸��� �����ѵ� �� ��ü�� ����, ���� ���̴� �ڵ����� �������� �Ѵٰ� �����ؼ� �������. �̰��� �̿��Ͽ� ��� ũ��� �𵨸��� �ϴ��� ���� �΋H������ �հ� ������ ���׸� ���Ҵ�.

		for (i = 0; i < PLAYER_BULLET_MAX; i++)		// �÷��̾��� �Ѿ˿� ���� �⺻ ����
		{
			myBullet[i].type = BULLET_SPECIAL;		// BULLET_SPECIAL - '*'
			myBullet[i].isSpawned = 0;
			myBullet[i].speed = SHOOTING_BULLET_SPEED;  // �Ѿ��� �ӵ��� SHOOTING_BULLET_SPEED�� Ŭ���� ������.
			myBullet[i].dir = 0;						// �Ѿ��� ������� ��
			myBullet[i].owner = PLAYER;				//�Ѿ��� ����, �÷��̾�
		}

		for (i = 0; i < MAX_DISPLAYED_BULLET; i++)	// ���� �Ѿ˿� ���� �⺻ ����
		{
			enemyBullet[i].type = BULLET_DEFAULT;	// BULLET_DEFAULT - '*'
			enemyBullet[i].isSpawned = 0;			//���� ����
			enemyBullet[i].speed = 5;
			enemyBullet[i].dir = 180;
			enemyBullet[i].owner = ENEMY;			//�Ѿ��� ����, ��
		}
		//PlaySound(NULL, NULL, NULL);
		initCursor();						// Ŀ���� �Ⱥ��̵���
		resizeConsole();					//�ܼ��� ������ ����



		//playMCI("vapor.wav");						//vapor.wav ���� ���
		displayStart();						//ù���� ȭ��
		displaySecond();					//�ι�° ȭ��


		//stopMCI();							//���� ����
		printBound();						//�� �׵θ� ����
		displayLevel(lev);					//���� ��Ÿ��
		displayPlane(&Me);					// �÷��̾� ����� ǥ��
		score = 0;							// ���� = 0

		//playMCI("main.wav");

		while (1)
		{
			enemySpawnAsCount(count);
			if ((GetAsyncKeyState(SHOTKEY) & SHOTKEY_CHECK) || (GetAsyncKeyState(SHOTKEY2) & SHOTKEY_CHECK)) // ZŰ �Ǵ� XŰ�� ������ ���
			{
				PLAYER_CAN_SHOT = 1;			// �÷��̾ ���� ��⸦ ���Ѵٴ� ���� ������ ���� �ٲ����ν� �˷���.
			}

			if (Me.isDisplayed = 0 && Me.isDead == 1) // �÷��̾ �׾��� ���
			{

				break;							// �ݺ����� �������� ���ӿ��� ȭ���� ���.

			}


			if (count % 3 == 0)			//�÷��̾��� �̵� �ӵ�. ������ �������� �ε巴��, ������ ���� �����δ�. �׷��� �ʹ� ��������, ���������� ���� 3���� ����.
			{
				PlayerControl(&Me);		// �÷��̾��� �̵��� �������ִ� �Լ� ����
			}

			if (player_onBullet && PLAYER_CAN_SHOT)		// �÷��̾ ZŰ �Ǵ� XŰ�� ������ �ְ�(PLAYER_CAN_SHOT), ���� �ð��� ���� �Ѿ��� �߻��� �� �ִ� ���(player_onBullet)
			{
				for (i = 0; i < PLAYER_BULLET_MAX; i++)		//�÷��̾��� ��� �Ѿ��� �˻�
				{
					if (myBullet[i].isSpawned == 0)		//�Ѿ˵� �߿� �߻���� ���� �Ѿ��� �ִٸ�
					{
						PLAYER_CAN_SHOT = 0;		//������� �ٲ۴�
						player_onBullet = 0;		//������� �ٲ۴�
						shootBullet(&myBullet[i], &Me, myBullet[i].dir);		//�� �Ѿ��� ���
						break;	// �ݺ����� �������´�
					}

				}
			}

			if (count % (PLAYER_BULLET_DELAY - PLAYER_MAX_ATTACKBLOCK) == 0) // �÷��̾ ���� �� �� �ִ� ������. �� �ð��� ������ �÷��̾�� ���� �� �� ������, Z �Ǵ� X Ű�� ������ �Ѿ��� �߻�ȴ�.
			{
				player_onBullet = 1;		//���� �� �� �ֵ��� ����
			}


			for (i = 0; i < PLAYER_BULLET_MAX; i++)		//�߻�� �Ѿ˿� ���� �ݺ���
			{
				if (myBullet[i].isSpawned == 1)			//�Ѿ��� �߻�� ���·� ȭ�鿡�� �������� �� ���
				{
					if (count%myBullet[i].speed == 0)	// �Ѿ˺� Ư�� �ӵ��� ���� ���߾�
					{
						moveBullet(&myBullet[i], myBullet[i].dir);	//�Ѿ��� �����δ�
					}
				}
			}


			for (i = 0; i < MAX_DISPLAYED_BULLET; i++)	//��_�߻�� �Ѿ˿� ���� �ݺ���
			{
				if (enemyBullet[i].isSpawned == 1)		//���� ����.
				{
					if (count%enemyBullet[i].speed == 0)	//�Ѿ˺� Ư�� �ӵ��� ���� ���߾�
					{
						moveBullet(&enemyBullet[i], enemyBullet[i].dir);	//�Ѿ��� �����δ�
					}
				}
			}



			for (i = 0; i < ENEMY_NUM; i++)		//���� ��
			{
				if (enemy[i].isDisplayed == 1 && count % enemy[i].bulletdelay == 0)		// Ư�� ���� ȭ�鿡�� ��ȯ�Ǿ��� �ְ� �ش� ���� �Ѿ��� �� Ÿ�̹��� ����
				{
					for (j = 0; j < MAX_DISPLAYED_BULLET; j++)		//������ �Ѿ˵� ��
					{

						if (enemyBullet[j].isSpawned == 0)			//�߻���� ���� �Ѿ���
						{
							enemyBullet[j].speed = enemy[i].bulletspeed;
							enemyBullet[j].dir = enemy[i].bulletdir;	//���� ������ ���߾�
							shootBullet(&enemyBullet[j], &enemy[i], enemyBullet[j].dir);	//�Ѿ��� �߻��Ѵ�.

							break;
						}
					}
				}
			}


			for (i = 0; i < ENEMY_NUM; i++)		//������ �����̵��� �����ִ� �ݺ���
			{
				if (enemy[i].isDisplayed == 1)
				{

					if (count % enemy[i].movespeed == 0) // ������ �����̴� �ӵ�, �� Ư�� ī��Ʈ�� �Ǹ� ������.
					{

						enemyControl(&enemy[i]);		// ������ ���� ����. ���� �ε��� �� ���� ��� �ݴ� �������� ��ȯ���ִ� �Լ�
						Move(&enemy[i], enemy[i].dir);	// ����⸦ �����̵��� �����ִ� �Լ� ����
					}
				}
			}
			Sleep(5);	// 1000 - 1���̹Ƿ� 5 - 1/200��
			count++;	//ī��Ʈ�� ����
			if (count / 200 == levelTimeLimit[lev])		// count�� Sleep(5)���� +1�ǹǷ� count / 200�� 1�ʰ� ���������� 1�� �ö�. �̸� ���� �� ���� �ð��� ��
			{
				if (displayed_enemy != 0)			// ���� ���� ���� 0�� �ƴϸ�
				{
					break;							//���ӿ���ȭ������ ����.
				}
				lev++;								//0�̸� ������ �ö󰣴�.

				if (lev > 3)						//���� 3 �ʰ� ��
				{
					clearrr = 1;					//Ŭ���� �� ���� ����
					break;							//�ݺ����� ���� ����
				}

				displayLevel(lev);					//������ ������Ʈ�Ѵ�.
				count = 0;							// count�� �ٽ� 0���� �Ͽ� ������ �ö� ���·� ó������ ���� �Ѵ�.
			}

			if (count % 200 == 0)					// 1�ʸ���
			{
				displayTimer(levelTimeLimit[lev], count / 200);	//���ѽð��� ������Ʈ�Ѵ�.
			}

			if (Me.isDead == 1)	//�Ѿ��̳� ������ �¾� �׾��ٸ�
			{
				break;		//�ݺ����� �������´�
			}

		}


		Sleep(500);	//0.5��

		system("cls");	//�ܼ�â ����

		//stopMCI();	//������� ����


		if (clearrr == 1)		//������ Ŭ���� ���� ��
		{
			clearGame();		//ġŲ�׸� �����ֱ�
			Sleep(1000000);		//1000�ʵ��� ġŲ�׸��� ������
			return 0;			//���� ����
		}



		//playMCI("last.wav"); // �ٸ� ������� ��� - ���ӿ���ȭ��



		displayEndScreen(score);	//���ӿ��� ȭ�� �Լ�


		while (1)
		{
			cha = getchar();		//���� �Է¹ޱ�
			if (cha == 'N')			// N�� �Է¹޾��� ���(+����)
			{
				//stopMCI();			//�뷡 ����
				ReplayOrQuit = 0;	//������ ������ �� �ֵ��� ���� ����
				break;				//�ݺ����� ���´�
			}
			else if (cha == 'Y') {	//Y�� �Է¹޾��� ���(+����)
				//stopMCI();			//�뷡 ����
				ReplayOrQuit = 1;	//���÷��� �� �� �ֵ��� ���� ����
				break;
			}
			else {
				ReplayOrQuit = 2;	//�� �� �ƹ��� ���ڵ� �ƴ� ��� ���ǹ��� ���� ����
				gotoxy(MAX_X / 2 - 10, MAX_Y / 2 + 2);
				printf("�ٽ� �Է��� �ֽʽÿ�.                                             ");	// �ٽ� �Է��϶�� �޽����� ��
				Sleep(1000);		//1�ʸ� ��ٸ�
				displayEndScreen(score);	//�ٽ� ���� ȭ���� ���
			}


		}

		if (ReplayOrQuit == 0)	//���������� �� �ֵ��� ������ �����ߴٸ�
		{
			break;		//������
		}
		if (ReplayOrQuit == 1)		// �ٽ� �����ϱ�� �����ߴٸ�
		{
			continue;			//�ٽ� �ݺ����� ó������
		}

	}
	return 0;
}





