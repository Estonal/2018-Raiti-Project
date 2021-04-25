#define _CRT_SECURE_NO_WARNINGS
// Raiti Project
// 제작자 : asdarwin03



/*
이 프로그램은 Z,X키로 총을 쏘면서 적들을 잡는 게임입니다. 일정한 시간마다 적이 출현하여 일정한 규칙으로 총알을 쏘는데, 적들이 쏘는 총알을 모두 피하며 자신의 총알을 잘 맞추어야 적을 잡을 수 있습니다.
이동키는 화살표 왼쪽, 위쪽, 오른쪽, 아래쪽이고, 공격키는 Z와 X입니다. 처음에는 Z만으로 하려했지만 Z키만 누르기에는 '너무 잡기 힘들다'라는 의견을 반영하여 Z뿐만 아니라 X키를 눌러도 총알이 발사되도록 하였습니다.

이 프로그램에는 레벨(스테이지)이 존재합니다. 1,2,3까지 만들었는데, 4부터는 만들기도 벅차고, 플레이어도 여기까지는 도달하지 못할 것이라는 판단에 의해 4레벨은 없앴습니다.

이 프로그램에는 '제한 시간'이라는 것이 있는데, 이는 레벨(스테이지) 마다 차등 부여되며, '제한 시간' 안에 해당 레벨 안에 있는 적을 모두 죽여야 해당 레벨이 클리어되고 다음 레벨로 넘어갑니다.

제한시간 내에 적을 잡지 못할 경우 '게임 오버' 처리되며, 다시 해당 레벨부터 재도전할 수 있습니다.

적에게는 체력이 있는데, 이 수치는 정확히 확인할 수 없습니다. Raiden이라는 게임을 본 따 만들었기 때문인데, 이 게임에서도 정확한 적의 체력 수치는 나오지 않습니다.
모든 적은 언젠가 죽습니다. 그때까지 공격해주세요.

참고로, 플레이어는 한 발만 맞아도 죽습니다.

게임 화면에서 위쪽을 보시면 레벨, 점수, 남은 적, 남은 시간 등이 나오는데요, 점수는 1점부터 표시됩니다(처음 시작 기준).

총알이나 적에 부딪혀 죽으실 경우, 게임오버 화면으로 넘어갑니다. 이 화면이 떴을 때 재도전을 하시려면 Y를, 게임을 종료하시려면 N을 입력해 주세요.(대문자 필수)

레벨별 난이도를 조정하였는데, 1레벨은 조금만 해보시면 금방 클리어할 수 있는 난이도이며, 2레벨은 조금 더 해야하고, 3레벨은 정말 어렵게 만들었습니다.
모든 적을 없앴는데도 제한시간이 남았다면 그동안 손을 풀어주세요. 손이 아파요.


또한 코드를 간단하게 수정하여 사용자가 원하는 비행기 형태를 만들어 적용시킬 수 있습니다. 이 설정은 아래에 있습니다. 현재 코드에서 '모델링'을 검색하시면 나올 겁니다.


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



#define MAX_X 70	// 콘솔의 크기
#define MAX_Y 46

#define LEFT 1		// 비행기가 움직일 방향.
#define UP 3
#define RIGHT 2
#define DOWN 4

#define SHOTKEY 0x5A // 'Z'
#define SHOTKEY2 0x58 // 'X'
#define SHOTKEY_CHECK 0x0001

#define BLOCK 101
#define EMPTY -75

#define SHOTBLOCK 103 // '▲'
#define R_SHOTBLOCK 104 // '▼'
#define RIGHT_SHOTBLOCK 105 // '▶'
#define LEFT_SHOTBLOCK 106 // '◀'


// 맵에 업데이트 하는 용도로 사용하는 정의.
#define MY_BULLET -50
#define ENEMY_BULLET -70

// 맵에서, 벽과 공간을 구분해놓기 위함.
#define WALL -11
#define BLANK -5


//비행기 크기의 최댓값.
#define PLANE_MAX_X 30
#define PLANE_MAX_Y 4


//총알의 종류.
#define BULLET_DEFAULT '*'               // 적군의 총알.
#define BULLET_SPECIAL '*'               // 플레이어의 총알.



#define PLAYER_BULLET_MAX 30               // 플레이어의 총알 갯수 제한
#define PLAYER_BULLET_DELAY 7               // 총알을 쏠 때의 시간 간격. 10 - 0.1초기본 : 7 
#define SHOOTING_BULLET_SPEED 2                //2~10 사이에서 설정하는것을 추천. 1로 설정 시 끊김 현상 발생(너무 빨리 총알이 날아가서)

#define PLAYER_MAX_ATTACKBLOCK 1         //모델을 직접 만들시 주의! 모델을 만들 때 사용한 ATTACKBLOCK의 개수를 정확히 세어 적자.






#define PLANE_MAX_ATTACKBLOCK 10
#define MAX_DISPLAYED_BULLET 100            //적군 총알이 화면에 표시되는 최대 한도, 30개를 초과할 경우 적군이 총알을 발사하지 않는다.

#define ENEMY_REGULAR 80                //좌우-이동타입
#define ENEMY_REVERSE 60                //상하-이동타입
#define ENEMY_MOVESPEED 20              //움직이는 속도 기본설정
#define ENEMY_NUM 50                    //등장하는 적의 수 최대
#define ENEMY_DEFAULT_HP 5              // 적들의 기본 체력

#define PLAYER -3						//플레이어의 ID.
#define ENEMY 2							//

#define PLAYER_COLOR 10 // 10 - 초록그린색
#define ENEMY_COLOR 12 // 12 - 빨간색
#define ENEMY_BULLET_COLOR 15 // 15 하얀색
#define PLAYER_BULLET_COLOR 14 // 6 노란색

#define REPLAY 0x59 // 게임 오버일 경우 Y키를 누르면 다시 시작된다.
#define GAME_QUIT 0x4E // 게임오버일 때 N키를 누르면 콘솔이 종료된다.

#pragma comment(lib, "winmm.lib")			// PlaySound()를 사용하기 위함.

int count = 0;                              // 메인에 있는 반복문의 반복 횟수를 세어 적절한 코드를 작성하기 위함.
int player_onBullet = 0;                    // player_onBullet은 플레이어가 총을 쏠수 있는 상태인지 아닌지를 검사하기 위하여 만든 전역변수로, 일정 카운트가 지나면 플레이어가 총을 쏠 수 있게 된다.
int map[MAX_Y][MAX_X + 1];					// 적 비행기와 플레이어의 위치를 저장하여 총알을 맞았는지 아닌지 판단하기 위하여 만듦.
int lev;									// 시간이 지나면 지날수록 레벨이 높아지는데, 3레벨까지 만들었음. 레벨이 높아질수록 어렵게 만들 생각임. 죽어도 1레벨에서 다시 시작이 아닌 죽은 해당 레벨에서 시작한다.
int score = 0;								// 적을 처치할때마다 score가 1점씩 오름. 죽거나 게임을 끝냈을 경우 화면에 자신의 score가 나옴 다시시작할 시 score는 초기화된다.,
int displayed_enemy = 0;					// 적 수를 변수로 만들어 적 비행기가 몇 대 현재 화면에 나와있는지 표시해주기 위해 만들었다. 이 displayed_enemy는 '남아 있는 적의 수'를 의미한다. 제한시간을 넘어 다음 레벨로 넘어갈 때 이 변수를 검사하여 남아있는 적의 수가 1대라도 있으면 게임오버이다.
int levelTimeLimit[6]; // 레벨 당 시간제한을 설정한다. 1라운드부터 5라운드까지 만들 예정이기 때문임.
int _time = 0;           //시간제한을 두기 위해 시간을 측정하기 위한 변수를 만듦.
int clearrr = 0;		//플레이어가 모두 클리어 했는지 여부

typedef struct _Bullet {
	char type;	// 총알의 타입으로, 이것을 수정하면 적이 쏘는 총알의 형태를 바꿀 수 있다.
	int x, y;	// 총알의 x,y좌표를 저장한다.
	int speed;	// 총알이 날아가는 속도를 의미한다.
	int isSpawned;	// 총알이 발사 되었는지 여부를 검사할 때 이용되는 변수이다.
	int dir;		// 총알이 나아가는 방향을 의미한다.
	int owner;		// 총알의 주인으로, PLAYER와 ENEMY로 나뉜다.
} Bullet;


typedef struct _Plane {
	int id;			// Plane의 고유번호. '내' 비행기는 기본 번호가 -3이다. 음수라는 것에 의의가 있는데, 적들은 고유번호가 0 이상이다. 이렇게 하여 얻을 수 있는 이익이 있다.
	int model[PLANE_MAX_Y][PLANE_MAX_X];		// 비행기의 모습, 형태 2차원 배열이다.
	int x, y;									// 비행기의 x,y좌표
	int max_x;									// 비행기에서 오른쪽 가장 끝 좌표
	int max_y;									// 비행기에서 가장 아래쪽 좌표
	int attack_x[PLANE_MAX_ATTACKBLOCK];		// 비행기 모델에서의 SHOTBLOCK 좌표
	int attack_y[PLANE_MAX_ATTACKBLOCK];		// ''
	int maxShotBlock;							// 최대 SHOTBLOCK, 즉 총을 쏠 수 있도록 만들 블럭의 갯수
	int bulletSelector;							// 총알 발사 순서. SHOTBLOCK이 1개일때는 의미가 없지만, 2개 이상일 경우 일정한 순서대로 총알이 발사된다.
	int isDead;									// 죽음 여부
	int isDisplayed; // //화면에 표시 되었는지 아닌지를 표시

					 // 적 비행기를 위한 변수
	int type; // 플레이어에게는 해당X, 적들 비행기의 이동특성 설정
	int dir; // 적들이 움직이는 방향.
	int bulletdelay; // 총알을 쏘는 속도.
	int movespeed; // 적이 움직이는 속도.
	int bulletspeed; // 적이 쏘는 총알의 속도. 2 - 가장 빠름
	int bulletdir; // 쏘는 총알의 방향
	int hp;			// 비행기의 체력
} Plane;



Plane enemy[ENEMY_NUM];			// define에서 설정된 대로 enemy 구조체를 만듦. ENEMY_NUM은 최대 적 수를 의미함.
Plane Me;
Bullet myBullet[PLAYER_BULLET_MAX];	// define에서 설정된 대로 myBullet 구조체를 만듦. 내가 쏠 수 있는 총알을 의미함.
Bullet enemyBullet[MAX_DISPLAYED_BULLET]; // // define에서 설정된 대로 enemyBullet 구조체를 만듦. 적들이 쏠 수 있는 총알을 의미함.


/*
void playMCI(char * a)//mp3 재생
{
	mciOpen.lpstrElementName = a; // 파일 경로
	mciOpen.lpstrDeviceType = "mpegvideo";

	mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&mciOpen );

	dwID = mciOpen.wDeviceID;

	mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&m_mciPlayParms);// play & repeat
}
void playMCI_noRepeat(char * a)//mp3재생 - 반복x
{
	mciOpen.lpstrElementName = a; // 파일 경로 입력
	mciOpen.lpstrDeviceType = "mpegvideo";

	mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&mciOpen);

	dwID = mciOpen.wDeviceID;

	mciSendCommand(dwID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&m_mciPlayParms);// play
}
void stopMCI()//mp3 재생 정지
{
	mciSendCommandW(dwID, MCI_CLOSE, 0, NULL); // stop
}


*/


void gotoxy(int x, int y) // 콘솔의 x,y좌표로 커서를 이동
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}



int checkBlocked(Plane *p, int key)			// 비행기가 벽에 닿았는지 안닿았는지 그 유무를 판단해주는 함수
{
	if (key == UP)          // 화살표 위쪽 방향키를 눌렀을 때
	{
		if (p->y < 3 + 1 + 2)  // 총알을 발사했을 때 게임 화면을 구성하는 벽이 사라지지 않게 하기 위해 비행기의 이동 가능 범위를 조금 뒤로 미뤄 적절히 설정하였다.
			return 1;


	}
	else if (key == DOWN) {			//화살표 아래쪽 방향키를 눌렀을 때

		if (p->y + p->max_y >= MAX_Y - 1)	//비행기가 아래쪽 벽에 닿으면
			return 1;						// 1을 반환한다.

	}
	else if (key == LEFT) {			//화살표 왼쪽 방향키를 눌렀을 때

		if (p->x < 2 + 1)			// 비행기가 왼쪽 벽에 닿으면
			return 1;				// 1을 반환.


	}
	else if (key == RIGHT) {		//화살표 오른쪽 방향키를 눌렀을 때

		if (p->x + p->max_x >= MAX_X - 2 - 1) // 비행기가 오른쪽 벽에 닿으면
			return 1;				// 1을 반환
	}



	return 0;					// 위 조건을 모두 만족하지 않을 경우 벽에 부딪히지 않은 것으로 간주, 0을 반환한다.
}
void displayBullet(Bullet *b)    // Bullet 단일 Struct가 움직이는 것을 출력하는 함수임.
{
	gotoxy(b->x, b->y);			// Bullet을 출력하기위해 콘솔 커서를 Bullet의 위치로 이동함.
	if (b->owner == PLAYER)		// 총알을 쏘는 것이 PLAYER라면
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), PLAYER_BULLET_COLOR); // 색을 PLAYER_BULLET_COLOR로 바꾼다.
	else if (b->owner == ENEMY) // 총알을 쏘는 것이 ENEMY라면
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ENEMY_BULLET_COLOR);	// 색을 ENEMY_BULLET_COLOR로 바꾼다.
	printf("%c", b->type);		// 총알을 출력한다. b->type은 총알의 종류를 의미하는데, 기본설정은 '*'이다.


}
void initCursor()	// 커서를 보이지 않게 하기 위한 설정.
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}
void resizeConsole()	// 콘솔의 크기를 조정.
{
	char chTemp[50];
	sprintf(chTemp, "Mode con cols=%d lines=%d", MAX_X, MAX_Y);
	system(chTemp);
}

void clearGame()			//게임 3레벨 클리어 시 나오는 마지막 클리어 화면.
{
	resizeConsole();

	gotoxy(20, 1);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("■■■■■■■■■■■■■");
	gotoxy(14, 2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("■■■■■■■■■■■■■■■■■■■");
	gotoxy(14, 3);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("■■■■■■■■■■■■■■■■■■■");
	gotoxy(14, 4);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("■■■■■■■■■■■■■■■■■■■");
	gotoxy(14, 5);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("■■■■■■■■■■■■■■■■■■■");
	gotoxy(18, 5);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("■■■■");
	gotoxy(32, 5);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("■■");
	gotoxy(42, 5);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("■■■");
	gotoxy(8, 6);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■");
	gotoxy(18, 6);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("■");
	gotoxy(42, 6);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("■");
	gotoxy(48, 6);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("■");
	gotoxy(36, 6);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("■");
	gotoxy(30, 6);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("■");





	gotoxy(8, 7);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■");
	gotoxy(48, 7);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("■");
	gotoxy(42, 7);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("■");

	gotoxy(36, 7);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("■");
	gotoxy(30, 7);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("■");
	gotoxy(18, 7);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("■");
	gotoxy(8, 8);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■");
	gotoxy(42, 8);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("■■■");

	gotoxy(36, 8);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("■");
	gotoxy(18, 8);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("■■■");
	gotoxy(30, 8);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("■");
	gotoxy(6, 9);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■");
	gotoxy(42, 9);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("■");
	gotoxy(46, 9);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("■■");
	gotoxy(36, 9);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("■");
	gotoxy(30, 9);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("■");
	gotoxy(18, 9);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("■");
	gotoxy(6, 10);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■");
	gotoxy(48, 10);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("■");
	gotoxy(42, 10);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("■");
	gotoxy(30, 10);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("■");

	gotoxy(36, 10);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("■");

	gotoxy(18, 10);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("■");


	gotoxy(6, 11);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■");
	gotoxy(32, 11);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("■■");
	gotoxy(42, 11);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("■");
	gotoxy(48, 11);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("■");
	gotoxy(18, 11);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("■");
	gotoxy(6, 12);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■");

	gotoxy(6, 13);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■");
	gotoxy(6, 14);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■");
	gotoxy(6, 15);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■");
	gotoxy(6, 16);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■");
	gotoxy(28, 16);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("!!WINNER!!");
	gotoxy(6, 17);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■");
	gotoxy(28, 17);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("!!WINNER!!");
	gotoxy(6, 18);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■");
	gotoxy(28, 18);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("!!WINNER!!");

	gotoxy(6, 19);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■");
	gotoxy(28, 19);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("!!WINNER!!");
	gotoxy(8, 20);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■");
	gotoxy(8, 21);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■");
	gotoxy(8, 22);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■");
	gotoxy(14, 23);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("■■■■■■■■■■■■■■■■■■■");
	gotoxy(14, 24);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("■■■■■■■■■■■■■■■■■■■");
	gotoxy(14, 25);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("■■■■■■■■■■■■■■■■■■■");
	gotoxy(14, 26);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("■■■■■■■■■■■■■■■■■■■");
	gotoxy(14, 27);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("■■■■■■■■■■■■■■■■■■■");
	gotoxy(24, 28);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("■■■■■■■■■");
	gotoxy(24, 29);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("■■■■■■■■■");
	gotoxy(24, 30);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("■■■■■■■■■");
	gotoxy(24, 31);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("■■■■■■■■■");
	gotoxy(24, 32);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("■■■■■■■■■");
	gotoxy(24, 33);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("■■■■■■■■■");
	gotoxy(24, 34);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("■■■■■■■■■");
	gotoxy(24, 35);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("■■■■■■■■■");
	gotoxy(24, 36);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("■■■■■■■■■");
	gotoxy(22, 37);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("●■■■↗  ↖■■■●");
	gotoxy(20, 38);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("●●●●●      ●●●●●");
	gotoxy(20, 39);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("●●●●          ●●●●");
	gotoxy(22, 40);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("●●              ●●");
}



void displayStart()		// 시작 화면.
{
	char ch;			// 문자 하나를 받아 아무 키를 입력하였을 경우 두번째 화면으로 가기 위해 이 변수를 만듦.
	while (1)
	{


		gotoxy(4, 1);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);		//첫번째 화면 꾸미기 - ㅔ임 이름
		printf("®®®®®®®\n    ®®®®®®®®\n    ®®®      ®®®\n    ®®®       ®®®\n    ®®®      ®®®\n    ®®®     ®®®\n    ®®®    ®®®\n    ®®®®®®®®\n    ®®®®®®®®\n    ®®®    ®®®\n    ®®®     ®®®\n    ®®®      ®®®\n    ®®®       ®®®\n");

		gotoxy(25, 8);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
		printf("ººº");
		gotoxy(23, 9);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
		printf("ººººº");
		gotoxy(22, 10);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
		printf("ºº    ºº");
		gotoxy(22, 11);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
		printf("ºº    ºº");
		gotoxy(23, 12);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
		printf("ºººººº");
		gotoxy(25, 13);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
		printf("ººº ºº");

		gotoxy(37, 7);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		printf("ººº");
		gotoxy(37, 8);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		printf("ººº");
		gotoxy(37, 9);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		printf("ººº");
		gotoxy(37, 10);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		printf("        ");
		gotoxy(37, 11);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		printf("ººº");
		gotoxy(37, 12);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		printf("ººº");
		gotoxy(37, 13);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		printf("ººº");

		gotoxy(48, 5);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		printf("ººº");
		gotoxy(48, 6);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		printf("ººº");
		gotoxy(44, 7);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		printf("ººººººº");
		gotoxy(44, 8);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		printf("ººººººº");
		gotoxy(44, 9);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		printf("ººººººº");
		gotoxy(48, 10);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		printf("ººº");
		gotoxy(48, 11);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		printf("ººº");
		gotoxy(48, 12);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		printf("ººº");
		gotoxy(48, 13);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		printf("ººº");


		gotoxy(60, 7);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
		printf("ººº");
		gotoxy(60, 8);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
		printf("ººº");
		gotoxy(60, 9);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
		printf("ººº");
		gotoxy(60, 10);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
		printf("        ");
		gotoxy(60, 11);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
		printf("ººº");
		gotoxy(60, 12);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
		printf("ººº");
		gotoxy(60, 13);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
		printf("ººº");




		gotoxy(MAX_X / 2 - 1, 17);		//첫번째 화면 꾸미기 - 비행기
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		printf("▲");
		gotoxy(MAX_X / 2 - 2, 18);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		printf("▲▲");
		gotoxy(MAX_X / 2 - 3, 19);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		printf("▲▲▲");
		gotoxy(MAX_X / 2 - 4, 20);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		printf("▲▲▲▲");
		gotoxy(MAX_X / 2 - 19, 21);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		printf("━━━━━━━◀■■■■■■■■■■▶━━━━━━━");
		gotoxy(MAX_X / 2 - 28, 22);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		printf("↙■■■■■■■■■■↓↓↓↓↓↓■■■■■■■■■■↘");
		gotoxy(MAX_X / 2 - 30, 23);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		printf("↙■■■■■■■■■■■↓↓↓↓↓↓■■■■■■■■■■■↘");
		gotoxy(MAX_X / 2 - 32, 24);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
		printf("↙■■■■■■■■■■■■↓↓↓↓↓↓■■■■■■■■■■■■↘");
		gotoxy(MAX_X / 2 - 30, 25);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		printf("↖■■■■■■■■■■■↓↓↓↓↓↓■■■■■■■■■■■↗");
		gotoxy(MAX_X / 2 - 4, 26);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		printf("■■■■");
		gotoxy(MAX_X / 2 - 4, 27);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		printf("■■■■");
		gotoxy(MAX_X / 2 - 4, 28);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		printf("■■■■");
		gotoxy(MAX_X / 2 - 4, 29);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		printf("■■■■");
		gotoxy(MAX_X / 2 - 4, 30);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		printf("■■■■");
		gotoxy(MAX_X / 2 - 14, 31);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		printf("↙■■■■■■■■■■■■↘");
		gotoxy(MAX_X / 2 - 16, 32);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		printf("↙■■■■■■■■■■■■■■↘");
		gotoxy(MAX_X / 2 - 18, 33);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		printf("↙■■■■■■■■■■■■■■■■↘");
		gotoxy(MAX_X / 2 - 16, 34);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		printf("↖■■■■■■■■■■■■■■↗");
		gotoxy(MAX_X / 2 - 14, 35);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		printf("↖■■■■■■■■■■■■↗");


		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
		gotoxy(MAX_X / 2 - 15, 40);
		printf("시작하려면 아무 키나 누르세요!");
		Sleep(300);

		if (_kbhit())			//아무 키나 누르면 시작한다.
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
	system("cls");	//화면을 비움
}
void displaySecond()			//첫번째 화면에서 아무키나 누른 후 나오는 두번째 화면
{
	char ch;		//문자를 입력받기 위한 문자 변수
	while (1)		//설명서 -
	{


		gotoxy(18, 7);
		printf("┌            <설명서>            ┓ ");
		gotoxy(18, 8);
		printf("│                                │");
		gotoxy(18, 9);
		printf("│    ↑: 제트기 위로이동         │");
		gotoxy(18, 10);
		printf("│    ↓: 제트기 아래로이동       │");
		gotoxy(18, 11);
		printf("│    ←: 제트기 왼쪽으로이동     │");
		gotoxy(18, 12);
		printf("│    →: 제트기 오른쪽으로이동   │");
		gotoxy(18, 13);
		printf("│       z키   :   총쏘기         │");
		gotoxy(18, 14);
		printf("│                                │");
		gotoxy(18, 15);
		printf("└────────────────────────────────┘");


		gotoxy(24, 25);
		printf("┌    TIP    ┓ ");
		gotoxy(24, 26);
		printf("│           │");
		gotoxy(24, 27);
		printf("│코드를수정 │");
		gotoxy(24, 28);
		printf("│하면 기분이│");
		gotoxy(24, 29);
		printf("│  너무좋아 │");
		gotoxy(24, 30);
		printf("└───────────┘");








		gotoxy(20, 35);
		printf("!!!!!!눌르면 게임시작!!!!!!");
		fflush(stdin);
		Sleep(300);
		while (1)
			if (_kbhit())		// 다시시작 시 해당 화면으로 넘어가지 않고 바로 비행기 화면으로 가는 오류를 해결하기 위해 만듦.
			{
				ch = _getch();
				break;
			}
		gotoxy(20, 35);
		printf("                                      ");
		Sleep(300);

		if (_kbhit())		//입력을 받아 시작.
		{
			ch = _getch();
			break;
		}
	}
	system("cls");
}
void printBound()	//맵의 경계 설정 및 map 2차원 배열의 초기화를 담당하는 함수
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
				printf("⊙");		//2바이트
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
void displayLevel(int level)			// Level을 출력하여 보여주는 함수.
{
	gotoxy(0, 0);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("Level : %d", level);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
}
void displayEnemyNum(int num)			//남은 적 수를 보여주는 출력을 담당하는 함수.
{
	gotoxy(20, 0);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("남은 적 : %d", num);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);

}
void displayTimer(int dest, int sec)	// '제한 시간'을 보여주는 출력을 담당하는 함수.
{
	sec = dest - sec;
	int min;
	min = sec / 60;
	sec = sec % 60;
	gotoxy(20, 1);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("제한시간 : %02d분 %02d초 남음", min, sec);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
}
void displayScore(int sc)	// 점수롤 보여주는 출력을 담당하는 함수.
{
	gotoxy(0, 1);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("Score : %d", sc);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
}
void clearReadBuffer_2() {
	fseek(stdin, 0, SEEK_END);
}
void displayEndScreen(int score)	//게임오버화면 함수
{


	system("cls");			//콘솔창 비우기
	clearReadBuffer_2();

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);	//게임오버화면 색 - 밝은 빨강, - FAIL 문자
	gotoxy(5, 3);
	printf("※※※※※※※\n     ※※※※※※※\n     ※※※※※※※\n     ※※※\n     ※※※\n     ※※※\n     ※※※※※※※\n     ※※※※※※※\n     ※※※※※※※\n     ※※※\n     ※※※\n     ※※※\n     ※※※\n");
	gotoxy(29, 3);
	printf("※\n");
	gotoxy(28, 4);
	printf("※※\n");
	gotoxy(27, 5);
	printf("※※※\n");
	gotoxy(26, 6);
	printf("※※※※\n");
	gotoxy(25, 7);
	printf("※※  ※※\n");
	gotoxy(24, 8);
	printf("※※    ※※\n");
	gotoxy(23, 9);
	printf("※※※※※※※\n");
	gotoxy(22, 10);
	printf("※※※※※※※※\n");
	gotoxy(21, 11);
	printf("※※※      ※※※\n");
	gotoxy(20, 12);
	printf("※※※        ※※※\n");
	gotoxy(19, 13);
	printf("※※※          ※※※\n");
	gotoxy(18, 14);
	printf("※※※            ※※※\n");
	gotoxy(17, 15);
	printf("※※※              ※※※\n");
	gotoxy(44, 3);
	printf("※※※※※\n");
	gotoxy(44, 4);
	printf("※※※※※\n");
	gotoxy(44, 5);
	printf("※※※※※\n");
	gotoxy(46, 6);
	printf("※※※\n");
	gotoxy(46, 7);
	printf("※※※\n");
	gotoxy(46, 8);
	printf("※※※\n");
	gotoxy(46, 9);
	printf("※※※\n");
	gotoxy(46, 10);
	printf("※※※\n");
	gotoxy(46, 11);
	printf("※※※\n");
	gotoxy(46, 12);
	printf("※※※\n");
	gotoxy(44, 13);
	printf("※※※※※\n");
	gotoxy(44, 14);
	printf("※※※※※\n");
	gotoxy(44, 15);
	printf("※※※※※\n");
	gotoxy(55, 3);
	printf("※※※\n");
	gotoxy(55, 4);
	printf("※※※\n");
	gotoxy(55, 5);
	printf("※※※\n");
	gotoxy(55, 6);
	printf("※※※\n");
	gotoxy(55, 7);
	printf("※※※\n");
	gotoxy(55, 8);
	printf("※※※\n");
	gotoxy(55, 9);
	printf("※※※\n");
	gotoxy(55, 10);
	printf("※※※\n");
	gotoxy(55, 11);
	printf("※※※\n");
	gotoxy(55, 12);
	printf("※※※\n");
	gotoxy(55, 13);
	printf("※※※※※※※\n");
	gotoxy(55, 14);
	printf("※※※※※※※\n");
	gotoxy(55, 15);
	printf("※※※※※※※\n");


	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);		//하얀색
	gotoxy(MAX_X / 2 - 10, MAX_Y / 2);									//게임오버 화면에서의 출력화면. Y/N은 따로 main함수에서 받는다.
	printf("최종 점수 : %d", score);
	gotoxy(MAX_X / 2 - 10, MAX_Y / 2 + 10);
	printf("(가장 앞글자만 인식합니다.)");
	gotoxy(MAX_X / 2 - 10, MAX_Y / 2 + 20);
	printf("다시 하시겠습니까? (Y/N) : ");


}
void shootBullet(Bullet * b, Plane * p, int angle)	//총알을 쏠 때 실행하는 함수.
{


	p->bulletSelector = p->bulletSelector%p->maxShotBlock;	//bulletSelector가 얼마나 올라갔던 0~maxShotBlock 사이에서 남아있도록 도와준다.



	b->isSpawned = 1;										//총알이 소환되었음을 설정

	b->x = p->x + p->attack_x[p->bulletSelector];			//총알의 좌표를 우선적으로 attack_x[bulleteSelector],  attack_y[bulleteSelector]로 지정.
	b->y = p->y + p->attack_y[p->bulletSelector];

	if (angle == 0)
		b->y = p->y + p->attack_y[p->bulletSelector] - 1;	//총알이 출발할 좌표. SHOTBLOCK에서 1칸 위에서 발사.


	if (angle == 180)
		b->y = p->y + p->attack_y[p->bulletSelector] + 1;	//총알이 출발할 좌표. SHOTBLOCK에서 1칸 아래에서 발사.

	if (angle == 90)
		b->x = p->x + p->attack_x[p->bulletSelector] + 2;	//총알이 출발할 좌표. SHOTBLOCK에서 2칸 오른쪽에서 발사.

	if (angle == 270)
		b->x = p->x + p->attack_x[p->bulletSelector] - 2;	//총알이 출발할 좌표. SHOTBLOCK에서 2칸 왼쪽에서 발사.


	p->bulletSelector++;	// bulletSelector의 값을 변경하여 다른 SHOTBLOCK에서 출력하기 위함임.

	if (p->bulletSelector >= p->maxShotBlock)	// maxShotBlock의 갯수가 최대이기 때문에 bulletSelector가 그 이상이 되어버리면 에러가 발생한다. 그러므로 maxShotBlock 안에서 bulletSelector 변수가 변해야 한다.
	{
		p->bulletSelector = p->bulletSelector - p->maxShotBlock; // 함수의 특성 상 위 if조건을 만족할 경우는 p->bulletSelector = p->maxShotBlock일 경우이므로 이 둘을 빼주면 0이 되는데 이로 다시 bulletSelector를 설정한다.
	}	//사실 이 if문은 위에서 이미 Selector를 잡아주고 있기 때문에 쓰이지 않는다. 하지만 오류가 날 경우를 대비하여 남겨놓고 있다.

	if (p->id == PLAYER)		//p가 플레이어일 경우
	{

		//PlaySound(TEXT("gun2.wav"), NULL, SND_FILENAME | SND_ASYNC); // 플레이어가 총 쏠 경우 효과음(총소리) 내기
	}


	displayBullet(b);	//총알을 화면에 나타나게 함

}
void deleteEntity(Plane *p) // 해석 그대로 p라는 비행기를 화면에서 지워주는 역할을 한다. 하지만 적 비행기가 플레이어의 비행기가 충돌했는지 안했는지 검사해 주는 함수이기도 하다.
{
	int i, j;
	for (i = 0; i<p->max_y; i++)		//p의 비행기 최대 y좌표 - p->max_y
	{
		for (j = 0; j<p->max_x; j++)	//p의 비행기 최대 x좌표 - p->max_x
		{
			gotoxy(p->x + j, p->y + i);	//콘솔 상에서의 비행기의 해당 gotoxy로 이동함.
			if (p->model[i][j] == BLOCK || p->model[i][j] == SHOTBLOCK || p->model[i][j] == R_SHOTBLOCK || p->model[i][j] == RIGHT_SHOTBLOCK || p->model[i][j] == LEFT_SHOTBLOCK)	// 모델에 빈 공간이 아닐 경우
			{
				if (p->id == PLAYER)	//만약 플레이어라면(Move에서 알다시피, 이 deleteEntity는 대개 비행기가 움직일 때 쓰인다. 즉, PLAYER가 움직일 때 p는 플레이어가 되고, ENEMY가 움직일 때 p는 ENEMY가 된다.)
				{
					if (map[p->y + i][p->x + j] >= 0)	// 만약 플레이어의 비행기 좌표에 적의 비행기가 걸려있을 경우
					{
						Me.isDead = 1;					//플레이어는 죽은 것으로 처리
						Me.isDisplayed = 0;				//표시되지 않도록 함
					}
				}
				else {					//만약 플레이어가 아닐경우, 즉 적일경우
					if (map[p->y + i][p->x + j] == PLAYER)	// 해당 적의 비행기 좌표에 플레이어의 비행기가 걸려있을 경우
					{
						Me.isDead = 1;					// 플레이어는 죽은 것으로 처리
						Me.isDisplayed = 0;				//표시되지 않도록 함
					}
				}
				map[p->y + i][p->x + j] = BLANK;		//맵상에서도 해당 좌표를 BLANK로 함. 즉 정말로 map상에서도, 실제 화면상에서도 없어진다.
				map[p->y + i][p->x + j + 1] = BLANK;	//map에서 블록을 2바이트로 설정하였기 때문에 이런 방식으로 저장을 하였었는데, 좌표를 BLANK로 채워 넣을 때에도 이를 처리해야함.
				printf("  ");		//화면 상에서 해당 좌표를 비움.
			}
		}
	}
}
void displayPlane(Plane * p)	//비행기를 화면에 표시해주는 함수. 또한 맵상에 비행기의 위치를 저장시켜주는 함수이기도 하다.
{
	int i, j;


	if (p->id == PLAYER)	//p가 플레이어의 비행기라면
	{

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), PLAYER_COLOR);	//PLAYER_COLOR에 해당하는 색으로 비행기 색을 설정하고
	}
	else {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ENEMY_COLOR);	//ENEMY_COLOR에 해당하는 색으로 비행기 색을 설정한다.
	}

	for (i = 0; i<PLANE_MAX_Y; i++)		//이 반복문은 비행기 모델의 블럭구성을 하나하나 검사하여 특정 명령을 실행하기 위함이다.
	{
		for (j = 0; j<PLANE_MAX_X; j++)
		{
			gotoxy(p->x + j, p->y + i);		//블럭이 위치할 map의 특정 좌표로 이동

			if (p->model[i][j] == BLOCK)	//비행기 모델 상 BLOCK이 위치해야 할 좌표인 경우
			{
				printf("■");				//BLOCK을 위치시킴.
				map[p->y + i][p->x + j] = p->id;		//p 비행기의 고유번호를 맵에 저장시킴
				map[p->y + i][p->x + j + 1] = p->id;	//p 비행기의 고유번호를 맵에 저장시킴, 하나의 블럭은 2바이트를 차지하기 때문에 map[p->y + i][p->x + j + 1]도 고유번호를 저장시켜야 한다.
			}
			else if (p->model[i][j] == SHOTBLOCK) {		//비행기 모델 상 SHOTBLOCK이 위치해야 할 좌표인 경우
				printf("▲");				//SHOTBLOCK을 위치시킴
				map[p->y + i][p->x + j] = p->id;		//p 비행기의 고유번호를 맵에 저장시킴
				map[p->y + i][p->x + j + 1] = p->id;	//p 비행기의 고유번호를 맵에 저장시킴, 하나의 블럭은 2바이트를 차지하기 때문에 map[p->y + i][p->x + j + 1]도 고유번호를 저장시켜야 한다.
			}
			else if (p->model[i][j] == R_SHOTBLOCK) {	//비행기 모델 상 R_SHOTBLOCK이 위치해야 할 좌표인 경우
				printf("▼");				//R_SHOTBLOCK을 위치시킴
				map[p->y + i][p->x + j] = p->id;		//p 비행기의 고유번호를 맵에 저장시킴
				map[p->y + i][p->x + j + 1] = p->id;	//p 비행기의 고유번호를 맵에 저장시킴, 하나의 블럭은 2바이트를 차지하기 때문에 map[p->y + i][p->x + j + 1]도 고유번호를 저장시켜야 한다.
			}
			else if (p->model[i][j] == RIGHT_SHOTBLOCK) {	//비행기 모델 상 RIGHT_SHOTBLOCK이 위치해야 할 좌표인 경우
				printf("▶");				//RIGHT_SHOTBLOCK을 위치시킴
				map[p->y + i][p->x + j] = p->id;		//p 비행기의 고유번호를 맵에 저장시킴
				map[p->y + i][p->x + j + 1] = p->id;	//p 비행기의 고유번호를 맵에 저장시킴, 하나의 블럭은 2바이트를 차지하기 때문에 map[p->y + i][p->x + j + 1]도 고유번호를 저장시켜야 한다.
			}
			else if (p->model[i][j] == LEFT_SHOTBLOCK) {	//비행기 모델 상 LEFT_SHOTBLOCK이 위치해야 할 좌표인 경우
				printf("◀");				//LEFT_SHOTBLOCK을 위치시킴
				map[p->y + i][p->x + j] = p->id;		//p 비행기의 고유번호를 맵에 저장시킴
				map[p->y + i][p->x + j + 1] = p->id;	//p 비행기의 고유번호를 맵에 저장시킴, 하나의 블럭은 2바이트를 차지하기 때문에 map[p->y + i][p->x + j + 1]도 고유번호를 저장시켜야 한다.
			}
		}
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);	//색 원래대로 돌리기

	p->isDisplayed = 1;		//비행기가 화면에 나타나도록 함.
}
void Move(Plane *p, int key)				//플레이어나 적 비행기를 이동시키는 함수 UP, RIGHT, LEFT, DOWN 등의 key를 받아 key에 따라 움직이도록 한다.
{
	switch (key)							//switch문 사용 - UP일 경우, - DOWN일 경우, - RIGHT일 경우, -LEFT일 경우
	{

	case UP:
		if (checkBlocked(p, UP) == FALSE)		//위쪽 벽에 닿을 위험이 없다면
		{
			deleteEntity(p);					//잠시 비행기를 지우고(안보이게 하고)
			p->y -= 1;							//위쪽으로 1칸 이동
		}
		break;
	case DOWN:
		if (checkBlocked(p, DOWN) == FALSE)		// 아래쪽 벽에 닿을 위험이 없다면
		{
			deleteEntity(p);					//잠시 비행기를 지우고(안보이게 하고)
			p->y += 1;							//아래쪽으로 1칸 이동
		}
		break;
	case LEFT:
		if (checkBlocked(p, LEFT) == FALSE)		// 왼쪽 벽에 닿을 위험이 없다면
		{
			deleteEntity(p);					//잠시 비행기를 지우고(안보이게 하고)
			p->x -= 1;							//왼쪽으로 1칸 이동
		}
		break;
	case RIGHT:
		if (checkBlocked(p, RIGHT) == FALSE)	// 오른쪽 벽에 닿을 위험이 없다면
		{
			deleteEntity(p);					//잠시 비행기를 지우고(안보이게 하고)
			p->x += 1;							// 오른쪽으로 1칸 이동
		}
		break;

	}


	displayPlane(p);	//다시 비행기를 나타낸다
}
void PlayerControl(Plane *p)			//플레이어가 어떠한 키를 눌렀는지 판단하여 움직이도록 도와주는 함수
{

	if (p->id == PLAYER && p->isDead == 0)		// 비행기의 고유번호가 Player의 고유번호이고 그 비행기가 죽지 않았다면
	{

		if (GetAsyncKeyState(VK_LEFT)) {		// 왼쪽 키를 누르면

			Move(p, LEFT);						// 왼쪽으로 움직인다

		}
		else if (GetAsyncKeyState(VK_RIGHT)) {	// 오른쪽 키를 누르면

			Move(p, RIGHT);						// 오른쪽으로 움직인다

		}

		if (GetAsyncKeyState(VK_UP)) {			// 위쪽 키를 누르면
			Move(p, UP);						// 위쪽으로 움직인다

		}
		else if (GetAsyncKeyState(VK_DOWN)) {	// 아래쪽 키를 누르면

			Move(p, DOWN);						// 아래쪽으로 움직인다

		}


	}



}
void eraseBullet(Bullet * b) // 총알을 지우는 함수
{
	gotoxy(b->x, b->y);		//총알의 위치로 커서를 옮겨
	printf(" ");			// 지운다
	map[b->y][b->x] = BLANK;	// map 상에서도 아무것도 없는 상태로 만든다.

}
void moveBullet(Bullet * b, int dir) // 총알을 움직이는 함수
{
	int id;							//고유번호 저장용 변수 생성
	eraseBullet(b);  // 위치 재설정을 위해 총알을 잠시 화면에서 지운다

	if (dir == 0)					//총알의 각이 0도일때
	{
		b->y = b->y - 1;  // 총알의 좌표를 위쪽으로 이동시킴



		if (map[b->y][b->x] >= 0) // 적들의 비행기의 id를 그 비행기의 좌표 상 위치에 저장하였다. 적들의 ID 이외 다른 나머지 Map 구성은 모두 음수로 하였기 때문에 이러한 조건을 사용할 수 있었다.
		{
			id = map[b->y][b->x];			// map상의 적의 위치는 그 적의 id로 저장되어 있다. 그러므로 이를 받는다.
			enemy[id].hp = enemy[id].hp - 1;   // 한 발 맞았을 경우 적의 체력을 1 깎는다.
			if (enemy[id].hp <= 0)              // 적의 체력이 0 이하일경우
			{
				score++;               //점수 1점 획득.
				displayScore(score);	//점수 업데이트
				enemy[id].isDead = 1; // 적의 죽음을 알림.
				enemy[id].isDisplayed = 0;	// 더이상 화면이 표시되지 않도록 설정해줌
				deleteEntity(&enemy[id]);	// 화면에서 지움.
				displayed_enemy--;			//남아있는 적 수에서 id고유번호의 비행기를 지움
			}
			b->isSpawned = 0;				//총알이 표시되지 않도록 설정해줌
			eraseBullet(b);					//총알을 지움
			return;							//함수 종료


		}

		if (b->y < 3 + 1)					// 0도의 조건이므로 총알이 벽 밖으로 튀어나가면 안되기 때문에 이를 막기위한 조건. 만약 위쪽 벽 위에 총알이 있으면
		{

			b->isSpawned = 0;				// 총알이 표시되지 않도록 설정
			eraseBullet(b);					//총알을 지움
			return;							//함수 종료

		}
	}

	if (dir == 180)	// 위와 동일한 구조이나 적들에게만 해당됨. 180도로 총알을 발사할 수 있는 비행기는 적들 뿐이다. 아래 90도, 270도도 마찬가지다.
	{

		b->y = b->y + 1;	// 총알의 좌표를 아래쪽으로 이동시킴

		if (map[b->y][b->x] == Me.id)	//map에서 총알이 위치한 좌표에 있는 것이 PLAYER일 경우
		{
			Me.isDead = 1;				// PLAYER가 죽음
			Me.isDisplayed = 0;			// 더이상 화면에 표시되지 않도록 설정
			deleteEntity(&Me);			// PLAYER를 화면에서 지움
			b->isSpawned = 0;			// 총알이 표시되지 않도록 설정
			eraseBullet(b);				//총알을 지움
			return;						//함수 종료
		}
		if (b->y >= MAX_Y - 2)			// 총알이 바닥 벽에 닿을 듯 한 경우
		{
			b->isSpawned = 0;			//총알이 표시되지 않도록 설정
			eraseBullet(b);				//총알을 지움
			return;
		}
	}

	if (dir == 90)						//즉 오른쪽으로 발사할 경우
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
		if (b->x >= MAX_X - 3)		//총알이 맵의 오른쪽 벽을 뚫고 나갈 것 같은 경우
		{
			b->isSpawned = 0;
			eraseBullet(b);

			return;
		}
	}

	if (dir == 270)							// 즉 왼쪽으로 발사할 경우
	{

		b->x = b->x - 1;
		if (map[b->y][b->x] == Me.id)		//해당 총알이 플레이어에게 닿았을 경우
		{
			Me.isDead = 1;					//죽음
			Me.isDisplayed = 0;				//플레이어를 화면에서 표시되지 않도록 설정
			deleteEntity(&Me);				//비행기를 지운다
			b->isSpawned = 0;				//총알이 표시되지 않도록 설정
			eraseBullet(b);
			return;
		}


		if (b->x <= 3)			//총알이 맵의 왼쪽 벽을 뚫고 나갈 것 같은 경우
		{
			b->isSpawned = 0;	//총알이 표시되지 않도록 설정
			eraseBullet(b);		//총알을 지운다

			return;
		}
	}

	displayBullet(b);		//총알을 화면에 나타낸다
}
void autoPlaneMaxPatch(Plane * p)   //비행기를 직접 만들 때 자동으로 비행기 가장 오른쪽과 가장 밑쪽의 좌표를 계산하여 저장하는 함수이다.
{
	int maxX = 0, maxY = 0;			// 가로 최댓값, 세로 최댓값을 저장해 줄 변수 생성.
	int i, j;
	for (i = 0; i<PLANE_MAX_Y; i++)	// 최대로 설정할 수 있는 비행기 크기로 블럭이 하나하나 찾음.
	{
		for (j = 0; j<PLANE_MAX_X; j++)
		{
			if (p->model[i][j] == BLOCK || p->model[i][j] == SHOTBLOCK || p->model[i][j] == R_SHOTBLOCK || p->model[i][j] == RIGHT_SHOTBLOCK || p->model[i][j] == LEFT_SHOTBLOCK)	//빈 공간이 아닌 어떠한 블럭이라도 있다면
			{
				if (j > maxX)
				{
					maxX = j;         //가장 오른쪽 부분의 X좌표를 maxX에 저장
				}

				if (i > maxY)
				{
					maxY = i;         //가장 아래쪽 부분의 Y좌표를 maxY에 저장
				}
			}
		}
	}


	p->max_x = maxX + 1;      // 비행기의 오른쪽 끝이 블럭, 즉 2바이트이므로 + 1을 붙여주어 오른쪽 벽에 붙었을 때 벽이 훼손되는 상황을 막음.
	p->max_y = maxY + 1;      // maxY는 0부터 시작하는 좌표 상 위치이기 때문에 아래쪽 벽에 닿지 않게 하기 위해서는 비행기의 세로 '길이'를 저장해야 하므로 +1를 붙여준다.

}

void enemyControl(Plane *p)		//적이 벽에 부딪혔을 때 이동방향을 재설정함.
{
	if (p->id != PLAYER && p->isDisplayed == 1)		// 고유 ID가 플레이어가 아니고 화면에 나타나 있다면
	{
		if (p->type == ENEMY_REGULAR) // 적의 type이 가로로 발사하는 타입인 경우 LEFT-RIGHT
		{
			if (checkBlocked(p, p->dir) == 0)	//
			{
				return;
			}
			else {
				p->dir = p->dir % 2 + 1;	//RIGHT이면 LEFT로, LEFT이면 RIGHT로
			}
		}

		if (p->type == ENEMY_REVERSE)		//적의 type이 세로로 발사하는 타입인경우 UP-DOWN
		{
			if (checkBlocked(p, p->dir) == 0)	//벽에 부딪히지 않았다면
			{
				return;			// 현 상태 유지하고 리턴
			}
			else {
				p->dir = p->dir % 2 + 3; // UP이면 DOWN으로, DOWN이면 UP으로
			}
		}
	}
}
void planeShotBlockSet(Plane * p)		//비행기 모델에서 SHOTBLOCK을 찾아 그 블럭에서 총알이 나올 수 있도록 설정해주는 함수
{
	int i, j, k;

	for (k = 0; k<p->maxShotBlock; )      //k를 반복문으로 설정한 것은 공격할수 있는 SHOTBLOCK의 번호(k)마다 x,y의 값을 지정해 주어야 하기 때문..
	{

		for (i = 0; i<PLANE_MAX_Y; i++)            // i는 비행기 모델 2차원 배열에서 y(세로)를 의미함.
		{
			for (j = 0; j<PLANE_MAX_X; j++)         // j는 비행기 모델 2차원 배열에서 x(가로)를 의미함.
			{
				if ((p->id == PLAYER && p->model[i][j] == SHOTBLOCK) || (p->id != PLAYER && p->model[i][j] == R_SHOTBLOCK) || (p->id != PLAYER && p->model[i][j] == RIGHT_SHOTBLOCK) || (p->id != PLAYER && p->model[i][j] == LEFT_SHOTBLOCK) || (p->id != PLAYER && p->model[i][j] == SHOTBLOCK))     // 비행기 모델 2차원 배열 중 SHOTBLOCK을 찾아 공격 가능하도록 자동설정해준다.
				{

					p->attack_x[k] = j + 1;         // 공격 x,y는 총알이 발사 될 수 있는 블럭의 위치정보를 저장한다.
					p->attack_y[k] = i;
					k++;                     // k++는 지정해준 maxShotBlock개의 ShotBlock을 찾을 시 빠져나오게 도와준다.
				}
			}
		}
	}
}
void clearPlane(Plane * p)	//비행기 모델 안쪽을 모두 비워 '초기화' 하는 함수. 완전히 빈 상태.
{
	int i, j;
	for (i = 0; i<PLANE_MAX_Y; i++)	//반복문 사용, 해당 비행기 모델에 있는 '모든' 것을 다 비도록 만듦.
	{
		for (j = 0; j<PLANE_MAX_X; j++)
		{
			p->model[i][j] = EMPTY;
		}
	}
}
void enemyConfigure(int id, int _x, int _y, int delay, int _mspeed, int _bspeed, int direction, int hp)
{
	enemy[id].x = _x;			// 적의 x좌표
	enemy[id].y = _y;			//적의 y좌표
	enemy[id].bulletdelay = delay;	// 적의 총알 딜레이(총알을 '쏘는' 속도)
	enemy[id].movespeed = _mspeed;	// 적이 움직이는 속도
	enemy[id].bulletspeed = _bspeed;	// 적의 총알 속도(총알이 '날아가는' 속도)
	autoPlaneMaxPatch(&enemy[id]);		//해당 적 비행기의 최대 y좌표, 최대 x좌표를 구해 저장하는 함수 실행.
	planeShotBlockSet(&enemy[id]);		// ShotBlock을 설정하여 적도 총알을 발사할 수 있게 함.
	enemy[id].dir = direction;			// 적이 움직이는 방향. UP, DOWN, RIGHT, LEFT가 있다.
	enemy[id].hp = hp;					// 적의 체력.
	enemy[id].isDead = 0;				// 죽지 않음을 설정.
}
void enemySpawnAsCount(int count) // 내가 원하는 특정 시간에 적이 등장하도록 도와주는 함수. 적비행기의 화면 출연 여부, 그 비행기의 초기 좌표나 적 비행기의 모양, 총알을 쏘는 속도를 조정하는 등 여러가지 재설정을 한다.
{


	if (lev == 1) // 1단계 시간 = 15초 즉 count로 환산 시 15 * 200 count
	{

		if (count == 200)		//레벨이 1이며 현 카운트가 200일 경우
		{
			enemy[1].isDisplayed = 1;	//적을 보이도록 함.
			enemyConfigure(1, MAX_X / 2 + 10, MAX_Y / 3, 20, 10, 10, RIGHT, 3);		//적 기본설정을 바꿈.

			displayed_enemy++;				//남은 적수에 해당 적을 추가함.
		}



		if (count == 300)	// 위와 동일한 구조, count == 300일 경우
		{
			enemy[2].isDisplayed = 1;	// 위와 동일
			enemyConfigure(2, MAX_X / 2 - 16, MAX_Y / 3, 20, 10, 10, LEFT, 3);

			displayed_enemy++;
		}

		if (count == 500)		//...위와 동일한 구조
		{
			enemy[3].isDisplayed = 1;		//...
			enemyConfigure(3, MAX_X / 2 + 5, MAX_Y / 4, 20, 10, 9, LEFT, 5);

			displayed_enemy++;
		}

		if (count == 600)		//위와 동일한 구조
		{
			enemy[4].isDisplayed = 1;
			enemyConfigure(4, MAX_X / 2 - 5, MAX_Y / 4, 20, 8, 10, RIGHT, 5);

			displayed_enemy++;		//...
		}
		if (count == 800)		//1레벨 보스 비행기, 위 구조와 동일하나 조금 다름
		{
			enemy[5].isDisplayed = 1;	//보이도록 설정.
			clearPlane(&enemy[5]);		//적 비행기의 기본 모델을 지움.
			enemy[5].model[0][0] = BLOCK;	// 적의 모델을 만듬.
			enemy[5].model[0][4] = BLOCK;
			enemy[5].model[1][0] = BLOCK;
			enemy[5].model[1][2] = BLOCK;
			enemy[5].model[1][4] = BLOCK;
			enemy[5].model[2][0] = R_SHOTBLOCK;
			enemy[5].model[2][2] = R_SHOTBLOCK;
			enemy[5].model[2][4] = R_SHOTBLOCK;
			enemy[5].maxShotBlock = 3;		// 해당 적 비행기가 사용할 수 있는 ShotBlock의 갯수를 적음. R_SHOTBLOCK이 3개 있으므로 3을 적는다.
			enemyConfigure(5, MAX_X / 2, MAX_Y / 6, 20, 10, 10, LEFT, 50);	//...

			displayed_enemy++;		//...
		}

	}

	if (lev == 2)			//레벨이 2가 되었을 경우
	{
		if (count == 50)		//레벨이 2이며 count가 50일 경우
		{
			enemy[6].isDisplayed = 1;		//적을 보이게 한다.
			enemyConfigure(6, MAX_X / 2 + 27, MAX_Y / 6, 15, 7, 4, LEFT, 5); // 적의 기본 설정을 재설정.

			displayed_enemy++;		// 남아있는 적의 수에 해당 비행기를 추가.
		}
		if (count == 50)				//위와 동일한 구조
		{
			enemy[7].isDisplayed = 1;
			enemyConfigure(7, MAX_X / 2 - 27, MAX_Y / 6, 15, 7, 4, RIGHT, 5);

			displayed_enemy++;
		}
		if (count == 150)			//위와 동일한 구조
		{
			enemy[8].isDisplayed = 1;
			enemyConfigure(8, MAX_X / 2 + 22, MAX_Y / 5, 15, 7, 4, LEFT, 7);

			displayed_enemy++;
		}
		if (count == 150)			//위와 동일한 구조
		{
			enemy[9].isDisplayed = 1;
			enemyConfigure(9, MAX_X / 2 - 22, MAX_Y / 5, 15, 7, 4, RIGHT, 7);

			displayed_enemy++;
		}
		if (count == 500)			//위 레벨 1 보스 비행기와 동일한 구조
		{
			clearPlane(&enemy[10]);
			enemy[10].model[0][0] = BLOCK;
			enemy[10].model[1][0] = RIGHT_SHOTBLOCK;
			enemy[10].model[2][0] = BLOCK;
			enemy[10].maxShotBlock = 1;
			enemy[10].isDisplayed = 1;


			enemy[10].type = ENEMY_REVERSE;			//특이사항 : 이 비행기는 총알을 오른쪽으로 발사하므로 type과 bulletdir를 설정.
			enemy[10].bulletdir = 90;				// 기본 = 180 - 아래쪽, 90 - 오른쪽  270 - 왼쪽

			enemyConfigure(10, 2, MAX_Y / 6, 35, 6, 6, DOWN, 20);

			displayed_enemy++;
		}


		if (count == 500)					//위와 동일한 구조.
		{
			clearPlane(&enemy[11]);
			enemy[11].model[0][0] = BLOCK;
			enemy[11].model[1][0] = LEFT_SHOTBLOCK;
			enemy[11].model[2][0] = BLOCK;
			enemy[11].maxShotBlock = 1;
			enemy[11].isDisplayed = 1;


			enemy[11].type = ENEMY_REVERSE;
			enemy[11].bulletdir = 270;				// 이번에는 왼쪽으로 총알을 발사하는 비행기.

			enemyConfigure(11, MAX_X - 4, MAX_Y / 6, 35, 6, 6, DOWN, 20);

			displayed_enemy++;
		}

		if (count == 1300)						//동일한 구조
		{
			enemy[12].isDisplayed = 1;			//화면에 보여준다. 2레벨의 보스 비행기.
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
	if (lev == 3)			//레벨이 3일 경우
	{
		if (count == 100)	// 레벨이 3이고, count가 100이면
		{
			clearPlane(&enemy[13]);		// 비행기의 기본 모델을 지운다.
			enemy[13].model[0][0] = BLOCK;
			enemy[13].model[1][0] = RIGHT_SHOTBLOCK;
			enemy[13].model[2][0] = BLOCK;
			enemy[13].maxShotBlock = 1;
			enemy[13].isDisplayed = 1;


			enemy[13].type = ENEMY_REVERSE;
			enemy[13].bulletdir = 90;		//오른쪽으로 총알을 발사하는 설정.

			enemyConfigure(13, 2, MAX_Y / 6, 35, 6, 6, DOWN, 5);

			displayed_enemy++;
		}

		if (count == 100)			//이하 모두 동일한 구조
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

	displayEnemyNum(displayed_enemy);		//남은 적 수를 업데이트하여 보여준다.
}


// MAINNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN
int main()
{

	lev = 1;					//처음 레벨은 1로 함. 물론 설정 가능! 
	levelTimeLimit[1] = 15;    // 1라운드 시간제한. 단위는 (초)
	levelTimeLimit[2] = 25;    // 2라운드 시간제한. 단위는 (초)
	levelTimeLimit[3] = 30;    // 3라운드.. 이하동일


	int PLAYER_CAN_SHOT = 0;		//플레이어가 Z나 X키를 눌렀을 경우 1이 되는 함수.
	int i, j;						// 반복문 사용을 위한 변수
	char cha;						//게임오버 화면에서 문자를 입력받을 변수
	int ReplayOrQuit;				// 게임오버 화면에서, 재시작할 것인지 나갈 것인지 판정하여 반복문을 빠져나가게 해주는 변수.



									//-----------------------------------------------------





	while (1)
	{
		player_onBullet = 0;                    // player_onBullet은 플레이어가 총을 쏠수 있는 상태인지 아닌지를 검사하기 위하여 만든 전역변수이다. (일정 간격마다 총을 쏠 수 있게 해준다)
		score = 0;								//점수는 0점으로
		displayed_enemy = 0;					//현재 표시된 적을 0명으로
		count = 0;								// 현재 count(시간)을 0으로
		clearPlane(&Me);						// Me의 비행기 모델을 비운다.
		Me.id = PLAYER;       // 플레이어의 비행기 id는 1로 지정.
		Me.isDead = 0;			// 플레이어가 죽지 않음 - 0, 죽음 - 1
		Me.isDisplayed = 1;		// 플레이어를 화면 상에 나타낼 수 있게 해주는 변수. 1 - 표시 0 - 비표시

		for (i = 0; i < ENEMY_NUM; i++) //적 비행기의 기본값을 지정한다. 특정 비행기의 설정을 다시 하기 위해서는 enemySpawnAsCount 함수를 이용한다.
		{
			clearPlane(&enemy[i]); //적 비행기 모델을 비운다.
			enemy[i].id = i;		//고유번호 설정
			enemy[i].type = ENEMY_REGULAR;		// 위-아래 이동 적인지, 왼-오른쪽 이동 적인지 알려준다. ENEMY_REGULAR - 왼-오른쪽 ENEMY_REVERSE - 위-아래
			enemy[i].dir = LEFT;				// 적이 움직일 방향
			enemy[i].isDisplayed = 0;			//적을 화면에 표시 X
			enemy[i].model[0][0] = BLOCK;	//적의 기본 모델
			enemy[i].model[0][2] = BLOCK;
			enemy[i].model[0][4] = BLOCK;
			enemy[i].model[1][0] = R_SHOTBLOCK;
			enemy[i].model[1][4] = R_SHOTBLOCK;
			enemy[i].maxShotBlock = 2;				//model 상 ShotBlock의 갯수
			enemy[i].bulletdelay = 100;				//총알을 쏠 때의 딜레이.
			enemy[i].movespeed = ENEMY_MOVESPEED;	// ENEMY_MOVESPEED의 속도로 움직임
			enemy[i].bulletspeed = 5;			//기본 총알속도 설정
			enemy[i].isDead = 0;				//죽음 여부
			enemy[i].hp = ENEMY_DEFAULT_HP;		//적의 기본 체력 설정
			enemy[i].bulletdir = 180;


			autoPlaneMaxPatch(&enemy[i]);
			planeShotBlockSet(&enemy[i]);
		}




		// 주의 - 이차원 배열에서 첫번째는 y값(세로), 두번째는 x값(가로)이다. 그러나, 블럭 하나 당 2바이트를 차지하므로 블럭을 놓을 때 y는 1칸 당 1을 뛰는 반면 x는 한칸 당 2칸을 뛴다.
		// 참고: SHOTBLOCK의 갯수가 n일 경우 "#define PLAYER_MAX_ATTACKBLOCK n" 으로 수정해 준다. 무조건!!!


		//-------------------------------------------------------------- 모델링 시작

		// SHOTBLOCK - 총알을 쏠 수 있는 블럭. ▲ 모양
		// BLOCK - 비행기를 구성하는 블럭. ■ 모양
		// R_SHOTBLOCK - 플레이어 측면에서는 멋있게 꾸며주는 용도, 적에게 있어서는 총알을 쏘아 플레이어를 맞출 수 있는 블럭이다. ▼ 모양
		// 그 이외에도 LEFT_SHOTBLOCK, RIGHT_SHOTBLOCK 등이 있다.





		Me.model[0][0] = SHOTBLOCK;
		Me.model[1][0] = BLOCK;
		Me.model[2][0] = R_SHOTBLOCK;











		//--------------------------------------------------------------- 모델링 끝


		Me.maxShotBlock = PLAYER_MAX_ATTACKBLOCK;	//아래 planeShotBlockSet 함수를 도와주는 변수.
		planeShotBlockSet(&Me);					//총알을 쏠 수 있게 설정해줌.







		Me.x = MAX_X / 2;
		Me.y = MAX_Y - 10;
		autoPlaneMaxPatch(&Me);                           //  모델링이 가능한데 모델 전체의 가로, 세로 길이는 자동으로 계산해줘야 한다고 생각해서 만들었다. 이것을 이용하여 어떠한 크기로 모델링을 하더라도 벽에 부딫혔을때 뚫고 나가는 버그를 막았다.

		for (i = 0; i < PLAYER_BULLET_MAX; i++)		// 플레이어의 총알에 대한 기본 설정
		{
			myBullet[i].type = BULLET_SPECIAL;		// BULLET_SPECIAL - '*'
			myBullet[i].isSpawned = 0;
			myBullet[i].speed = SHOOTING_BULLET_SPEED;  // 총알의 속도는 SHOOTING_BULLET_SPEED가 클수록 느리다.
			myBullet[i].dir = 0;						// 총알이 쏘아지는 각
			myBullet[i].owner = PLAYER;				//총알의 주인, 플레이어
		}

		for (i = 0; i < MAX_DISPLAYED_BULLET; i++)	// 적의 총알에 대한 기본 설정
		{
			enemyBullet[i].type = BULLET_DEFAULT;	// BULLET_DEFAULT - '*'
			enemyBullet[i].isSpawned = 0;			//위와 동일
			enemyBullet[i].speed = 5;
			enemyBullet[i].dir = 180;
			enemyBullet[i].owner = ENEMY;			//총알의 주인, 적
		}
		//PlaySound(NULL, NULL, NULL);
		initCursor();						// 커서가 안보이도록
		resizeConsole();					//콘솔의 사이즈 설정



		//playMCI("vapor.wav");						//vapor.wav 음악 재생
		displayStart();						//첫번쨰 화면
		displaySecond();					//두번째 화면


		//stopMCI();							//음악 종료
		printBound();						//맵 테두리 생성
		displayLevel(lev);					//레벨 나타냄
		displayPlane(&Me);					// 플레이어 비행기 표시
		score = 0;							// 점수 = 0

		//playMCI("main.wav");

		while (1)
		{
			enemySpawnAsCount(count);
			if ((GetAsyncKeyState(SHOTKEY) & SHOTKEY_CHECK) || (GetAsyncKeyState(SHOTKEY2) & SHOTKEY_CHECK)) // Z키 또는 X키를 눌렀을 경우
			{
				PLAYER_CAN_SHOT = 1;			// 플레이어가 총을 쏘기를 원한다는 것을 변수의 값을 바꿈으로써 알려줌.
			}

			if (Me.isDisplayed = 0 && Me.isDead == 1) // 플레이어가 죽었을 경우
			{

				break;							// 반복문을 빠져나가 게임오버 화면을 띄움.

			}


			if (count % 3 == 0)			//플레이어의 이동 속도. 빠르면 빠를수록 부드럽게, 하지만 빨리 움직인다. 그래서 너무 빠르지도, 딱딱하지도 않은 3으로 설정.
			{
				PlayerControl(&Me);		// 플레이어의 이동을 관리해주는 함수 실행
			}

			if (player_onBullet && PLAYER_CAN_SHOT)		// 플레이어가 Z키 또는 X키를 누르고 있고(PLAYER_CAN_SHOT), 일정 시간이 지나 총알을 발사할 수 있는 경우(player_onBullet)
			{
				for (i = 0; i < PLAYER_BULLET_MAX; i++)		//플레이어의 모든 총알을 검사
				{
					if (myBullet[i].isSpawned == 0)		//총알들 중에 발사되지 않은 총알이 있다면
					{
						PLAYER_CAN_SHOT = 0;		//원래대로 바꾼다
						player_onBullet = 0;		//원래대로 바꾼다
						shootBullet(&myBullet[i], &Me, myBullet[i].dir);		//그 총알을 쏜다
						break;	// 반복문을 빠져나온다
					}

				}
			}

			if (count % (PLAYER_BULLET_DELAY - PLAYER_MAX_ATTACKBLOCK) == 0) // 플레이어가 총을 쏠 수 있는 딜레이. 이 시간이 지나면 플레이어는 총을 쏠 수 있으며, Z 또는 X 키를 누르면 총알이 발사된다.
			{
				player_onBullet = 1;		//총을 쏠 수 있도록 설정
			}


			for (i = 0; i < PLAYER_BULLET_MAX; i++)		//발사된 총알에 대한 반복문
			{
				if (myBullet[i].isSpawned == 1)			//총알이 발사된 상태로 화면에서 움직여야 할 경우
				{
					if (count%myBullet[i].speed == 0)	// 총알별 특정 속도에 따라 맞추어
					{
						moveBullet(&myBullet[i], myBullet[i].dir);	//총알을 움직인다
					}
				}
			}


			for (i = 0; i < MAX_DISPLAYED_BULLET; i++)	//적_발사된 총알에 대한 반복문
			{
				if (enemyBullet[i].isSpawned == 1)		//위와 같다.
				{
					if (count%enemyBullet[i].speed == 0)	//총알별 특정 속도에 따라 맞추어
					{
						moveBullet(&enemyBullet[i], enemyBullet[i].dir);	//총알을 움직인다
					}
				}
			}



			for (i = 0; i < ENEMY_NUM; i++)		//적들 중
			{
				if (enemy[i].isDisplayed == 1 && count % enemy[i].bulletdelay == 0)		// 특정 적이 화면에서 소환되어져 있고 해당 적이 총알을 쏠 타이밍이 오면
				{
					for (j = 0; j < MAX_DISPLAYED_BULLET; j++)		//적들의 총알들 중
					{

						if (enemyBullet[j].isSpawned == 0)			//발사되지 않은 총알을
						{
							enemyBullet[j].speed = enemy[i].bulletspeed;
							enemyBullet[j].dir = enemy[i].bulletdir;	//적의 설정에 맞추어
							shootBullet(&enemyBullet[j], &enemy[i], enemyBullet[j].dir);	//총알을 발사한다.

							break;
						}
					}
				}
			}


			for (i = 0; i < ENEMY_NUM; i++)		//적들이 움직이도록 도와주는 반복문
			{
				if (enemy[i].isDisplayed == 1)
				{

					if (count % enemy[i].movespeed == 0) // 적들이 움직이는 속도, 즉 특정 카운트가 되면 움직임.
					{

						enemyControl(&enemy[i]);		// 적들의 방향 설정. 벽에 부딪힐 것 같은 경우 반대 방향으로 전환해주는 함수
						Move(&enemy[i], enemy[i].dir);	// 비행기를 움직이도록 도와주는 함수 실행
					}
				}
			}
			Sleep(5);	// 1000 - 1초이므로 5 - 1/200초
			count++;	//카운트를 센다
			if (count / 200 == levelTimeLimit[lev])		// count가 Sleep(5)마다 +1되므로 count / 200은 1초가 지날때마다 1이 올라감. 이를 레벨 별 제한 시간과 비교
			{
				if (displayed_enemy != 0)			// 남은 적의 수가 0이 아니면
				{
					break;							//게임오버화면으로 간다.
				}
				lev++;								//0이면 레벨이 올라간다.

				if (lev > 3)						//레벨 3 초과 시
				{
					clearrr = 1;					//클리어 시 변수 설정
					break;							//반복문을 깨고 나옴
				}

				displayLevel(lev);					//레벨을 업데이트한다.
				count = 0;							// count를 다시 0으로 하여 레벨이 올라간 상태로 처음부터 시작 한다.
			}

			if (count % 200 == 0)					// 1초마다
			{
				displayTimer(levelTimeLimit[lev], count / 200);	//제한시간을 업데이트한다.
			}

			if (Me.isDead == 1)	//총알이나 적에게 맞아 죽었다면
			{
				break;		//반복문을 빠져나온다
			}

		}


		Sleep(500);	//0.5초

		system("cls");	//콘솔창 비우기

		//stopMCI();	//배경음악 멈춤


		if (clearrr == 1)		//게임을 클리어 했을 시
		{
			clearGame();		//치킨그림 보여주기
			Sleep(1000000);		//1000초동안 치킨그림을 보여줌
			return 0;			//게임 종료
		}



		//playMCI("last.wav"); // 다른 배경음악 재생 - 게임오버화면



		displayEndScreen(score);	//게임오버 화면 함수


		while (1)
		{
			cha = getchar();		//문자 입력받기
			if (cha == 'N')			// N을 입력받았을 경우(+엔터)
			{
				//stopMCI();			//노래 끄기
				ReplayOrQuit = 0;	//게임을 종료할 수 있도록 변수 설정
				break;				//반복문을 나온다
			}
			else if (cha == 'Y') {	//Y를 입력받았을 경우(+엔터)
				//stopMCI();			//노래 끄기
				ReplayOrQuit = 1;	//리플레이 할 수 있도록 변수 설정
				break;
			}
			else {
				ReplayOrQuit = 2;	//둘 중 아무런 문자도 아닐 경우 무의미한 수로 설정
				gotoxy(MAX_X / 2 - 10, MAX_Y / 2 + 2);
				printf("다시 입력해 주십시오.                                             ");	// 다시 입력하라는 메시지가 뜸
				Sleep(1000);		//1초를 기다림
				displayEndScreen(score);	//다시 같은 화면을 띄움
			}


		}

		if (ReplayOrQuit == 0)	//게임종료할 수 있도록 변수를 설정했다면
		{
			break;		//나가기
		}
		if (ReplayOrQuit == 1)		// 다시 시작하기로 설정했다면
		{
			continue;			//다시 반복문의 처음으로
		}

	}
	return 0;
}





