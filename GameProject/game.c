#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>


struct player {
	struct item {
		int food;
		int water;
		int map;
		int book;
		int radio;
		int gas_mask;
		int ax;
		int knife;
		int gun;
		int ammo;
		int flash;
		int lock;
		int first_aid_kit;
		int pesticide;
		int card;
		int chess;
	};
	struct Char {
		int dad[6];
		int mom[6];
		int son[6];
		int dau[6];
		int dog;
	};
};

int day = 0, explo, exploTime=0, exploExit=0, exploMap, exploday, beforeExplo;
int before = 0; // 이전 이벤트와 겹치는 지 확인해주는 변수
int event[3] = { 0 }; // 진엔딩 이벤트용 변수
int eventTurn = 0; // 진엔딩 이벤트 진행 변수
int eventCancel = 0; // 진엔딩 이벤트에서 문 안열 경우 다른 진엔딩 이벤트에 참여할 수 있게끔
int badevent = 10;
int goodevent = 10;
int normalevnet = 10;
struct player player;
// 0.스프	1.물		2.지도	3.책		
// 4.라디오	5.방독면	6.도끼	7.칼	
// 8.총	9.탄약	10.손전등	11.자물쇠	
// 12.구급약	13.카드	14.체스	15. 살충제
// 
// 0. (배고픔, 굶주림)  1.(충분함, 목마름, 탈수)   2.(정상, 미침, 착란) 
// 3. (정상?, 지침)   4. (건강함, 다침, 고통)  5. (정상, 질병)
// https://papago.naver.net/website?locale=ko&source=en&target=ko&url=https%3A%2F%2F60seconds.fandom.com%2Fwiki%2FEvents_(60_Seconds!)%23Feline_Domination

// 해야할 것
// 
// 2. 탐사 = explo 받은 후 random주고 --해서 탐사 표현
// 3. 탐사 후 갔다 온 곳 스크립트 표현하기
// 
// . badEvent - 1번째 강도이벤트에서 아무것도 없이 막을 시 이벤트 수정하기
// 지도가 있으면 탐사 기간 하루 줄여주는?
// 자물쇠는 얻으면 2으로 주고 한 번씩 강도에게서 버틸 때 마다 --하는 식으로
// 
//
// 탐사 나가면 다음날 아침에 탐사 스크립트 띄우기


void script();
void earlyEvent();
void badEvent();
void normalEvent();
void goodEvent();
void militaryEvent();
void agentEvent();
void twinEvent();
void mainControl();
void mainStatus();
void dad_status();
void mom_status();
void son_status();
void dau_status();
void itemStatus();
void exploration();
int randomSystem(int num);

int main() {
	char var;// yes or no 변수
	srand(time(NULL));
	printf("60 Seconds!\n");
	printf("게임을 시작하려면 y, 종료하려면 n를 입력해주세요\n- ");

	// 게임 시작 입력문
	while (1) {
		scanf("%c", &var);
		if (var == 'y' || var == 'Y') {
			system("cls");
			printf("새 게임을 시작합니다.\n\n");
			Sleep(1000);
			system("cls");
			break;
		}
		else if (var == 'n' || var == 'N') {
			system("cls");
			printf("게임을 종료합니다.\n\n");
			return 0;
		}
		else {
			system("cls");
			printf("잘못 누르셨습니다. \n");
			printf("게임을 시작하려면 y, 종료하려면 n를 입력해주세요\n- ");
		}
	}

	// 게임 메인 진행
	while (day < 50) {
		// 새 게임일 때
		if (day == 0) {
			day++;
			player.food = 4;
			player.water = 4;
			player.radio = 0;
			player.book = 0;
			player.gas_mask = 0;
			player.ax = 0;
			player.knife = 0;
			player.gun = 0;
			player.ammo = 0;
			player.flash = 0;
			player.lock = 0;
			player.first_aid_kit = 0;
			player.pesticide = 0;
			player.card = 0;
			player.chess = 0;

			player.dad[0] = 2; player.dad[1] = 2;
			player.dad[2] = 0; player.dad[3] = 0; player.dad[4] = 0; player.dad[5] = 0;
			player.mom[0] = 2; player.mom[1] = 2;
			player.mom[2] = 0; player.mom[3] = 0; player.mom[4] = 0; player.mom[5] = 0;
			player.son[0] = 2; player.son[1] = 2;
			player.son[2] = 0; player.son[3] = 0; player.son[4] = 0; player.son[5] = 0;
			player.dau[0] = 2; player.dau[1] = 2;
			player.dau[2] = 0; player.dau[3] = 0; player.dau[4] = 0; player.dau[5] = 0;

			script();
			// 현재 물량 출력문
			printf("======\n");
			printf("1. 식량: %d\n", player.food);
			printf("2. 물: %d\n", player.water);
			printf("3. 지도: %d\n", player.map);
			printf("4. 책: %d\n", player.book);
			printf("5. 라디오: %d\n", player.radio);
			printf("6. 방독면: %d\n", player.gas_mask);
			printf("7. 도끼: %d\n", player.ax);
			printf("8. 칼: %d\n", player.knife);
			printf("9. 총: %d\n", player.gun);
			printf("10. 탄약: %d\n", player.ammo);
			printf("11. 손전등: %d\n", player.flash);
			printf("12. 자물쇠: %d\n", player.lock);
			printf("13. 구급약: %d\n", player.first_aid_kit);
			printf("14. 살충제: %d\n", player.pesticide);
			printf("15. 카드: %d\n", player.card);
			printf("16. 체스: %d\n", player.chess);
			printf("======\n");
			Sleep(4000);
			system("cls");
		}

		// 아무 진엔딩 미참여 + 50 일차 도달시
		else if (day == 50) {
			// 50일차 도달 전용 이벤트 함수
			printf("게임 종료");
			return 0;
		}

		mainStatus();
		// 상태 확인 후 이벤트 넘어갈 지 확인
		// 이벤트 표현 → 함수 받기 (각 n차 별 이벤트 만들기)

		itemStatus();
		printf("\n");
		
		printf("오늘의 이야기: ");
		mainControl();
		printf("\n-----------------------------------------\n\n");

		// 탐사 이벤트 문
		exploration();
		
		

		printf("시간이 벌써 저녁을 향해 달려가고 있다.\n다음 날을 위해 잠을 잘까 (y or n)\n- ");

		// 다음 회차로 갈까?
		while (1) {

			scanf(" %c", &var);
			if (var == 'y' || var == 'Y') {
				system("cls");
				printf("잠이 오진 않으나, 다음 날을 위하여 억지로라도 잠을 청해봅니다.\n");
				if (day == 9) {
					printf("바깥 상황을 보니 내일부터 탐사를 갈 수 있을 것 같다는 생각도 든다.\n");
					Sleep(2000);
				}
				if (day == 24) {
					printf("내일부턴 지겨운 벙커 냄새 대신 바깥의 선선하고 상쾌한 황무지 냄새를 폐에 반겨줄 때일 것 같다.\n");
					Sleep(2000);
				}
				printf("로딩중.");
				Sleep(300);
				printf(".");
				Sleep(300);
				printf(".");
				Sleep(300);
				printf(".");
				Sleep(300);
				printf(".");
				system("cls");
				break;
			}
			else if (var == 'n' || var == 'N') {
				system("cls");
				printf("오늘을 정리하고자 잠시 잠을 뒤로 한다.\n");
				printf("(오늘 한 거 요약해서 보여주는 함수)\n");
				printf("다음 날을 위해 잠을 잘까 (y or n))\n- ");
			}
			else {
				system("cls");
				printf("\n잘못 누르셨습니다. \n");
				printf("다음 날을 위해 잠을 잘까 (y or n)\n- ");
			}
		}
		day++;
	}
}

int randomSystem(int num) {
	int random = rand() % num;
	return random;
}

void script() {

	printf("평화로운 주말을 지내며 TV를 보던 당신은 실제상황이라는 빨간색 자막을 보면서\n");

	printf("동시에 수차례의 날카로운 미사일 소리와 함께 귀가 아플 정도의 사이렌을 듣게 되었습니다.\n");

	printf("그 난리법통 속에서 [실제상황] 이라는 단어는 머리에 각인되었고,  \n");

	printf("곧 머리 위로 당신의 집 크기만한 미사일이 떨어짐을 예상하게 되었습니다.\n");

	printf("전부터 준비한 지하벙커에 뭐라도 챙겨야 겠다는 생각에\n");

	printf("눈 앞에 보이는, 가까운 것 몇개가 눈에 띄었습니다. \n\n\n");

	printf("어떤 것들을 챙기시겠습니까? (최대 4개)\n");

	printf("=========================\n");
	printf("1. 추가 음식 (식량과 물)\t2. 지도와 책\t3. 라디오\n");
	printf("4. 방독면\t5. 도끼와 칼\t6. 총과 탄약\n");
	printf("7. 손전등과 자물쇠\t8. 구급약과 살충제\t9. 카드·체스\n");
	printf("=========================\n- ");

	int i = 0, s[4] = { 0 };
	// 중복 아이템 눌렸을 경우 열외 처리
again:
	while (i < 4) {
		s[i] = 0;
		i++;
	}i = 0;

	while (i < 4) {
		scanf(" %d", &s[i]);
		i++;
	}
	i = 0;

	// 입력 검사문
	for (i = 0; i < 4; i++) {
		for (int j = i + 1; j < 4; j++) {
			if (s[i] == s[j]) {
				printf("\n중복 입력하셨습니다. 다시 입력해주세요\n- ");
				goto again;
			}
		}
		if (s[i] > 9) {
			printf("\n잘못 입력하셨습니다. 다시 입력해주세요\n- ");
			goto again;
		}
	}i = 0;

	while (i < 4) {
		switch (s[i]) {
		case 1:
			player.food += 2; // 식량, 물
			player.water += 2;
			break;
		case 2:
			player.map += 1; // 지도와 책
			player.book += 1;
			break;
		case 3:
			player.radio += 1; // 라디오
			break;
		case 4:
			player.gas_mask += 1; // 방독면
			break;
		case 5:
			player.ax += 1; // 도끼, 칼
			player.knife += 1;
			break;
		case 6:
			player.gun += 1; // 총 탄약
			player.ammo += 1;
			break;
		case 7:
			player.lock += 2; // 손전등, 자물쇠
			player.flash += 1;
			break;
		case 8:
			player.first_aid_kit += 1; // 구급약, 살충제
			player.pesticide += 1;
			break;
		case 9:
			player.card += 1; // 카드 체스
			player.chess += 1;
			break;
		}
		i++;
	}

	system("cls");
	printf("그렇게 서두른 당신은 겨우 아내와 아들, 딸을 벙커로 대피시키고\n");

	printf("허겁지겁 고른 물건들을 집어들어, 벙커로 몸을 던져 벙커의 해치를 닫음으로써 대피에 성공했습니다.\n");

	printf("하지만 벙커에 있던 방사능 탐지기가 울부짓듯 울렸고\n");

	printf("기나긴 나날을 이 좁고 외로운 장소에서 지내야 한다는 생각에 눈 앞이 캄캄해집니다....\n");

}

void exploration() {
	int random = rand() % 15;

	if (day <= 3) {
		printf("지금 벙커 밖을 나간다는 생각을 한다는 것 자체가 미친 것이다.\n");
		return;
	}

	// 탐사 종료시
	if (exploExit == 1) {
		exploExit =0;
		beforeExplo = explo;

		switch (explo) {
			case 1:
				printf("드디어 아빠가 %d만에 길고 험난했던 탐사를 마치고 돌아왔다\n", exploday);
				player.dad[3] = -5;
				break;
			case 2:
				printf("드디어 엄마가 %d만에 길고 험난했던 탐사를 마치고 돌아왔다\n", exploday);
				player.mom[3] = -5;
				break;
			case 3:
				printf("드디어 아들이 %d만에 길고 험난했던 탐사를 마치고 돌아왔다\n", exploday);
				player.son[3] = -5;
				break;
			case 4:
				printf("드디어 딸이 %d만에 길고 험난했던 탐사를 마치고 돌아왔다\n", exploday);
				player.dau[3] = -5;
				break;
			}
		// 탐사 갔다온 장소에 대한 멘트
		switch (random) {
			case 0:
				printf("학교 방문\n");
				break;
			case 1:
				printf("공사장 방문\n");
				break;
			case 2:
				printf("주택가 방문\n");
				break;
			case 3:
				printf("병원 방문\n");
				break;
			case 4:
				printf("마트 방문\n");
				break;
			case 5:
				printf("식당가 방문\n");
				break;
			case 6:
				printf("지하철 방문\n");
				break;
			case 7:
				printf("도서관 방문\n");
				break;
			case 8:
				printf("아파트 방문\n");
				break;
			case 9:
				printf("미지정 장소 방문\n");
				break;
			}

		// 지도 지참으로 인한 아이템 확률 업
		// 기본 식량, 물 1개씩은 쥐어줄까?
		if (exploMap==1) {
			switch (random) {
			case 0: // 지도, 책, 라디오, 손전등, 카드
				printf("학교\n");
				break;
			case 1: // 식량, 물, 도끼, 자물쇠
				printf("공사장 이었던 곳\n");
				break;
			case 2: // 식량, 물, 총, 살충제, 카드
				printf("주택가\n");
				break;
			case 3: // 구급약, 손전등, 칼, 살충제
				printf("병원\n");
				break;
			case 4: // 식량, 물, 대량의 식량 or 물
				printf("마트\n");
				break;
			case 5: //식량, 물, 대량의 식량 or 물
				printf("식당가\n");
				break;
			case 6: // 방독면, 손전등, 구급약
				printf("지하철\n");
				break;
			case 7: // 지도, 책, 자물쇠, 체스
				printf("도서관\n");
				break;
			case 8: // 식량, 물, 체스
				printf("아파트\n");
				break;
			case 9: // 총, 탄약, 칼, 도끼, 자물쇠 中 1, 
				printf("무기고\n");
				break;
			case 10: // 식량, 물, 
				printf("카페\n");
				break;
			case 11:
				printf("미지정 장소\n");
				break;
			case 12:
				printf("미지정 장소\n");
				break;
			case 13:
				printf("미지정 장소\n");
				break;
			case 14:
				printf("미지정 장소\n");
				break;
			}

		}
		// 지도 미지참으로 인한 아이템 확률 다운
		else {
			switch (random) {
			case 0:
				printf("학교\n");
				break;
			case 1:
				printf("공사장 이었던 곳\n");
				break;
			case 2:
				printf("주택가\n");
				break;
			case 3:
				printf("병원\n");
				break;
			case 4:
				printf("마트\n");
				break;
			case 5:
				printf("식당가\n");
				break;
			case 6:
				printf("지하철\n");
				break;
			case 7:
				printf("도서관\n");
				break;
			case 8:
				printf("아파트\n");
				break;
			case 9:
				printf("미지정 장소\n");
				break;
			case 10:
				printf("미지정 장소\n");
				break;
			case 11:
				printf("미지정 장소\n");
				break;
			case 12:
				printf("미지정 장소\n");
				break;
			case 13:
				printf("미지정 장소\n");
				break;
			case 14:
				printf("미지정 장소\n");
				break;
			}
		}
		printf("오늘은 탐사를 다녀와서 가족 모두 정리할 것들이 많다.\n");
		explo = 0;
		return;
	}
	
	// 탐사 질문
	if (exploTime == 0) {
		if ( day >= 4 || day < 10 ) {
			// 10일차 전까지의 전용 이벤트
			printf("낙진이 봄비처럼 내리는 지금과 같은 환경에서 탐사를 나간다는 생각은 너무 무모하지만\n");
			printf("그 누가 핵폭발 이후의 장경을 볼 수 있을까? 라는 생각에 흥미로워진다.\n");
			printf("1. 아빠\t"); printf("2. 엄마\t"); printf("3. 아들\t"); printf("4. 딸\t"); printf("5. 나가지 않는다.\n");
			

			while (1) {
				printf("내일은 탐사를 누가 나갈까?\n- ");
				scanf("%d", &explo);
				if (explo == 1) {
					if (player.dad[2] < 0 || player.dad[3] < 0 || player.dad[4] < 0 || player.dad[5] < 0) {
						printf("현재 상태의 아빠를 탐사로 내보내는 것은 죽으라는 뜻이다.\n");
					}
					else {
						printf("\n아빠가 듬직함과 가장의 입장을 앞세우며 탐사에 나서기로 했다. \n");
						break;
					}
				}
				else if (explo == 2) {
					if (player.mom[2] < 0 || player.mom[3] < 0 || player.mom[4] < 0 || player.mom[5] < 0) {
						printf("현재 상태의 엄마를 탐사로 내보내는 것은 죽으라는 뜻이다.\n");
					}
					else {
						printf("엄마가 세심하고 책임감을 앞세우며 탐사에 나서기로 했다. \n");
						break;
					}
				}
				else if (explo == 3) {
					if (player.son[2] < 0 || player.son[3] < 0 || player.son[4] < 0 || player.son[5] < 0) {
						printf("현재 상태의 아들을 탐사로 내보내는 것은 죽으라는 뜻이다.\n");
					}
					else {
						printf("아들이 자신감과 열정을 불태우며 탐사에 나서기로 했다. \n");
						break;
					}
				}
				else if (explo == 4) {
					if (player.dau[2] < 0 || player.dau[3] < 0 || player.dau[4] < 0 || player.dau[5] < 0) {
						printf("현재 상태의 딸을 탐사로 내보내는 것은 죽으라는 뜻이다.\n");
					}
					else {
						printf("딸이 패기와 모험감을 앞세우며 탐사에 나서기로 했다. \n");
						break;
					}
				}
				else if (explo == 5) {
					printf("굳이 위험과 고난을 무릎쓰고 탐사를 나서야 할까?\n\n");
					explo = 0;
					break;
				}
				else {
					printf("\n잘못 입력하셨습니다.\n");
				}
			}

		}
		else if (day >= 10 || day <= 24) {
			printf("낙진도 그쳤고, 핵폭발의 여파가 곳곳에 남아있지만, 벙커를 나가 기지개를 펴기 좋은 날씨이다.\n");
			// 캐릭터 배열 앞자리에다 explo 넣어서 탐사 구현하기
			printf("1. 아빠\t"); printf("2. 엄마\t"); printf("3. 아들\t"); printf("4. 딸\t"); printf("5. 나가지 않는다.\n- ");


			while (1) {
				printf("내일은 탐사를 누가 나갈까?\n- ");
				scanf("%d", &explo);
				if (explo == 1) {
					if (player.dad[2] < 0 || player.dad[3] < 0 || player.dad[4] < 0 || player.dad[5] < 0) {
						printf("현재 상태의 아빠를 탐사로 내보내는 것은 죽으라는 뜻이다.\n");
					}
					else {
						printf("\n아빠가 듬직함과 가장의 입장을 앞세우며 탐사에 나서기로 했다. \n");
						break;
					}
				}
				else if (explo == 2) {
					if (player.mom[2] < 0 || player.mom[3] < 0 || player.mom[4] < 0 || player.mom[5] < 0) {
						printf("현재 상태의 엄마를 탐사로 내보내는 것은 죽으라는 뜻이다.\n");
					}
					else {
						printf("엄마가 세심하고 책임감을 앞세우며 탐사에 나서기로 했다. \n");
						break;
					}
				}
				else if (explo == 3) {
					if (player.son[2] < 0 || player.son[3] < 0 || player.son[4] < 0 || player.son[5] < 0) {
						printf("현재 상태의 아들을 탐사로 내보내는 것은 죽으라는 뜻이다.\n");
					}
					else {
						printf("아들이 자신감과 열정을 불태우며 탐사에 나서기로 했다. \n");
						break;
					}
				}
				else if (explo == 4) {
					if (player.dau[2] < 0 || player.dau[3] < 0 || player.dau[4] < 0 || player.dau[5] < 0) {
						printf("현재 상태의 딸을 탐사로 내보내는 것은 죽으라는 뜻이다.\n");
					}
					else {
						printf("딸이 패기와 모험감을 앞세우며 탐사에 나서기로 했다. \n");
						break;
					}
				}
				else if (explo == 5) {
					printf("굳이 위험과 고난을 무릎쓰고 탐사를 나서야 할까?\n\n");
					explo = 0;
					break;
				}
				else {
					printf("\n잘못 입력하셨습니다.\n");
				}
			}
		}
		else {
			printf("오늘같은 화창한 날씨를 보니, 내일은 해골이 나뒹구며, \n강도를 피해다니며 물건을 주어다닐 좋은 탐사가 될 것이다.\n");
			printf("1. 아빠\t"); printf("2. 엄마\t"); printf("3. 아들\t"); printf("4. 딸\t"); printf("5. 나가지 않는다.\n- ");
			while (1) {
				printf("내일은 탐사를 누가 나갈까?\n- ");
				scanf("%d", &explo);
				if (explo == 1) {
					if (player.dad[2] < 0 || player.dad[3] < 0 || player.dad[4] < 0 || player.dad[5] < 0) {
						printf("현재 상태의 아빠를 탐사로 내보내는 것은 죽으라는 뜻이다.\n");
					}
					else {
						printf("\n아빠가 듬직함과 가장의 입장을 앞세우며 탐사에 나서기로 했다. \n");
						break;
					}
				}
				else if (explo == 2) {
					if (player.mom[2] < 0 || player.mom[3] < 0 || player.mom[4] < 0 || player.mom[5] < 0) {
						printf("현재 상태의 엄마를 탐사로 내보내는 것은 죽으라는 뜻이다.\n");
					}
					else {
						printf("엄마가 세심하고 책임감을 앞세우며 탐사에 나서기로 했다. \n");
						break;
					}
				}
				else if (explo == 3) {
					if (player.son[2] < 0 || player.son[3] < 0 || player.son[4] < 0 || player.son[5] < 0) {
						printf("현재 상태의 아들을 탐사로 내보내는 것은 죽으라는 뜻이다.\n");
					}
					else {
						printf("아들이 자신감과 열정을 불태우며 탐사에 나서기로 했다. \n");
						break;
					}
				}
				else if (explo == 4) {
					if (player.dau[2] < 0 || player.dau[3] < 0 || player.dau[4] < 0 || player.dau[5] < 0) {
						printf("현재 상태의 딸을 탐사로 내보내는 것은 죽으라는 뜻이다.\n");
					}
					else {
						printf("딸이 패기와 모험감을 앞세우며 탐사에 나서기로 했다. \n");
						break;
					}
				}
				else if (explo == 5) {
					printf("굳이 위험과 고난을 무릎쓰고 탐사를 나서야 할까?\n\n");
					explo = 0;
					break;
				}
				else {
					printf("\n잘못 입력하셨습니다.\n");
				}
			}
		}

		// 탐사 보낼 시의 지도가 있는지 
		// 있으면 템겟확률 ↑, 없음 ↓
		if (explo) {
			if (player.map >= 1) {
				printf("(지도를 보유하고 있어, 탐사 후 아이템 습득 확률이 높아집니다.)\n");
				exploMap = 1;
			}
			else {
				printf("(지도를 보유하고 있지 않아, 탐사 후 아이템 습득 확률이 낮아집니다.)\n");
				exploMap = 0;
			}
		}
		

		// 랜덤 탐사 기간
		exploTime = rand() % 3;
		switch (exploTime) {
		case 0:
			exploTime = 3;
			exploday = 3;
			break;
		case 1:
			exploTime = 4;
			exploday = 4;
			break;
		case 2:
			exploTime = 5;
			exploday = 5;
			break;
		}

	}
	else {
		printf("지금은 ");
		switch (explo) {
		case 1:
			printf("아빠가 탐사에 나가있어 굳이 나갈 필요는 없을 것 같다.\n");
			break;
		case 2:
			printf("엄마가 탐사에 나가있어 굳이 나갈 필요는 없을 것 같다.\n");
			break;
		case 3:
			printf("아들이 탐사에 나가있어 굳이 나갈 필요는 없을 것 같다.\n");
			break;
		case 4:
			printf("딸이 탐사에 나가있어 굳이 나갈 필요는 없을 것 같다.\n");
			break;
		}
		if (exploTime == 1) {
			exploExit = 1;
		 }
		exploTime--;
	}
	printf("\n");
}

void mainStatus() {
	int i = 0;
	// DAY 출력하는 거랑 캐릭터 상태 출력하는 거랑 합칠까?
	printf("\t\t*********\n");
	printf("\t\t* Day %d *\n", day);
	printf("\t\t*********\n\n\n\n");

	printf("[가족의 상태]\n");
	// 가족들 상태 출력하는 걸 각각 함수 만든 다음에 switch (explo) {case1: (아빠 뺀 나머지 가족함수)}
	switch (explo)
	{
	case 0:
		printf("\n―――――――――――\n");
		dad_status();
		mom_status();
		son_status();
		dau_status();
		break;
	case 1:
		printf("아빠: 탐사");
		printf("\n―――――――――――\n");
		mom_status();
		son_status();
		dau_status();
		break;
	case 2:
		dad_status();
		printf("엄마: 탐사");
		printf("\n―――――――――――\n");
		son_status();
		dau_status();
		break;
	case 3:
		dad_status();
		mom_status();
		printf("아들: 탐사");
		printf("\n―――――――――――\n");
		dau_status();
		break;
	case 4:
		dad_status();
		mom_status();
		son_status();
		printf("딸: 탐사");
		printf("\n―――――――――――\n");
		break;
	}
	printf("\n");
}

void itemStatus() {
	printf("보유 물량\n========================\n");
	printf("식량: %d개   ", player.food);
	printf("물: %d개   ", player.water);
	printf("지도: %d개   ", player.map);
	printf("책: %d개   ", player.book);
	printf("라디오: %d개\n", player.radio);
	printf("방독면: %d개   ", player.gas_mask);
	printf("도끼: %d개   ", player.ax);
	printf("칼: %d개   ", player.knife);
	printf("총: %d개   ", player.gun);
	printf("탄약: %d개\n", player.ammo);
	printf("손전등: %d개   ", player.flash);
	printf("자물쇠: %d개   ", player.lock);
	printf("구급약: %d개   ", player.first_aid_kit);
	printf("카드: %d개   ", player.card);
	printf("체스: %d개    ", player.chess);
	printf("살충제: %d개", player.pesticide);
	printf("\n========================\n");
}

void dad_status() {
	printf("아빠: ");
	if (player.dad[0] > 0 && player.dad[1] > 0) {
		printf("충분함. ");
	}
	else {
		if (player.dad[0] == 0) {
			printf("배고픔. ");
		}
		else if (player.dad[0] = -2) {
			printf("굶주림. ");
		}
		if (player.dad[1] == 0) {
			printf("목마름. ");
		}
		else if (player.dad[1] == -1) {
			printf("탈수 ");
		}
	}

	if (player.dad[2] == -1) {
		printf("미침 ");
	}
	else if (player.dad[2] == -2) {
		printf("착란 ");
	}


	if (player.dad[3] <0) {
		printf("지침 ");
	}

	if (player.dad[4] == -1) {
		printf("다침. ");
	}
	else if (player.dad[4] == -2) {
		printf("고통. ");
	}

	if (player.dad[5] == -1) {
		printf("질병. ");
	}
	printf("\n―――――――――――\n");
}
void mom_status() {
	printf("엄마: ");
	if (player.mom[0] > 0 && player.mom[1] > 0) {
		printf("충분함. ");
	}
	else {
		if (player.mom[0] == 0) {
			printf("배고픔. ");
		}
		else if (player.mom[0] = -2) {
			printf("굶주림. ");
		}
		if (player.mom[1] == 0) {
			printf("목마름. ");
		}
		else if (player.mom[1] == -1) {
			printf("탈수 ");
		}
	}
	 

	if (player.mom[2] == -1) {
		printf("미침 ");
	}
	else if (player.mom[2] == -2) {
		printf("착란 ");
	}

	if (player.mom[3] <0) {
		printf("지침 ");
	}

	if (player.mom[4] == -1) {
		printf("다침. ");
	}
	else if (player.mom[4] == -2) {
		printf("고통. ");
	}

	if (player.mom[5] == -1) {
		printf("질병.");
	}
	printf("\n―――――――――――\n");
}
void son_status() {
	printf("아들: ");
	if (player.son[0] > 0 && player.son[1] > 0) {
		printf("충분함. ");
	}
	else {
		if (player.son[0] == 0) {
			printf("배고픔. ");
		}
		else if (player.son[0] = -2) {
			printf("굶주림. ");
		}
		if (player.son[1] == 0) {
			printf("목마름. ");
		}
		else if (player.son[1] == -1) {
			printf("탈수 ");
		}
	}

	if (player.son[2] == -1) {
		printf("미침 ");
	}
	else if (player.son[2] == -2) {
		printf("착란 ");
	}

	if (player.son[3] <0) {
		printf("지침 ");
	}

	if (player.mom[4] == -1) {
		printf("다침. ");
	}
	else if (player.son[4] == -2) {
		printf("고통. ");
	}

	if (player.son[5] == -1) {
		printf("질병. ");
	}
	printf("\n―――――――――――\n");
}
void dau_status() {
	printf("딸: ");
	if (player.dau[0] > 0 && player.dau[1] > 0) {
		printf("충분함. ");
	}
	else {
		if (player.dau[0] == 0) {
			printf("배고픔. ");
		}
		else if (player.dau[0] = -2) {
			printf("굶주림. ");
		}
		if (player.dau[1] == 0) {
			printf("목마름. ");
		}
		else if (player.dau[1] == -1) {
			printf("탈수 ");
		}
	}

	if (player.dau[2] == -1) {
		printf("미침 ");
	}
	else if (player.dau[2] == -2) {
		printf("착란 ");
	}

	 if (player.dau[3] < 0) {
		printf("지침 ");
	}

	if (player.dau[4] == -1) {
		printf("다침 .");
	}
	else if (player.dau[4] == -2) {
		printf("고통. ");
	}

	if (player.dau[5] == -1) {
		printf("질병. ");
	}
	printf("\n―――――――――――\n");
}

void mainControl() {
	int random = 0;
	//printf("input mainControl\nrandom = %d\n", random);
	//진엔딩 이벤트용
	
	if (day < 4) {
		printf("바깥 세상은 아직도 활활 불타고 있다.\n");
		earlyEvent();
		return;
	}

	if (random == 0) {
		// 처음 진엔딩 이벤트 들어가면
		if (event[0] == 0 && event[1] == 0 && event[2] == 0) {
			int random = randomSystem(3);
			switch (random) {
			case 0:
				printf("첫 군부대엔딩 이벤트 진입: \n");
				militaryEvent();
				event[0]++;
				break;
			case 1:
				printf("첫 요원엔딩 이벤트 진입: \n");
				agentEvent();
				event[1]++;
				break;
			case 2:
				printf("첫 쌍둥이엔딩 이벤트 진입: \n");
				twinEvent();
				event[2]++;
				break;
			}
		}

		// 아니라면 eventCancel 여부에 따라 진엔딩 이벤트 실행
		else {
			if (eventCancel != 0) {
				int random2 = randomSystem(2);
				printf("\neventCancel: %d\nrandom2: %d\n", eventCancel, random2);
				eventTurn = 0;
				if (eventCancel == 1) {
					event[0] = 0;
					if (random2 == 0) {
						event[1] = 1;
						printf("군부대 엔딩 진행 실패, 다음 진엔딩: 요원\n");
						agentEvent();
					}
					else if (random2 == 1) {
						event[2] = 1;
						printf("군부대 엔딩 진행 실패, 다음 진엔딩: 쌍둥이\n");
						twinEvent();
					}
				}

				else if (eventCancel == 2) {
					event[1] = 0;
					if (random2 == 0) {
						event[0] = 1;
						printf("요원 엔딩 진행 실패, 다음 진엔딩: 군부대\n");
						militaryEvent();
					}
					else if (random2 == 1) {
						event[2] = 1;
						printf("요원 엔딩 진행 실패, 다음 진엔딩: 쌍둥이\n");
						twinEvent();
						
					}
				}

				else if (eventCancel == 3) {
					event[2] = 0;
					if (random2 == 0) {
						event[0] = 1;
						printf("쌍둥이 엔딩 진행 실패, 다음 진엔딩: 군부대\n");
						militaryEvent();
					}
					else if (random2 == 1) {
						event[1] = 1;
						printf("쌍둥이 엔딩 진행 실패, 다음 진엔딩: 요원\n");
						agentEvent();
					}
				}
			}

			else  {
				if (event[0] == 1) {
					printf("군부대엔딩 이벤트 진입: \n");
					militaryEvent();
				}
				else if (event[1] == 1) {
					printf("요원엔딩 이벤트 진입: \n");
					agentEvent();
				}
				else if (event[2] == 1) {
					printf("쌍둥이엔딩 이벤트 진입: \n");
					twinEvent();
				}
			}
		}
	}
	//배드 이벤트용
	else if (random == 1) {
		badEvent();
	}

	//노말 이벤트용
	else if (random == 2) {
		normalEvent();
	}

	//굳 이벤트용
	else if (random == 3) {
		goodEvent();
	}
	
}

void earlyEvent() {
	// 4일차 미만일 때 진행될 스크립트
	// 이전 날 진행된 이벤트는 중복으로 뜨지 않게끔
	// 
	// 1. 불이 벙커 쪽으로 번지는 거 확인?
	// 2. 아무 일 없이 지루한 날 (이거 뜰 확률 2배로)
	// 3. 벙커 구석진 곳에서 무언가를 발견 ()
	// 4. 급하게 피하느라 부상 (냅둬도 ok or 부상으로 연계)
	// 5. 

	int random = rand() % 8;
	// 무운 이벤트
	if (random >= 0 && random <= 5) {
		previous:
		printf("역시 벙커에서 지내는 건 익숙지 않았고, 침묵으로만 몇 시간을 떼워버렸다.\n");
		return;
	}
	else {
		// 불이 벙커 쪽으로 번지는 이벤트
		if (random == 6) {
			int i = 0;
			if (before == 1) {
				before = 0;
				goto previous;
			}

			printf("우리는 벙커의 온도가 서서히 오르는 것을 느꼈고, 이내 타는 냄새 마저 맡기 시작했다.\n");
			printf("벙커 문의 창문으로 밖을 보니 이미 우린 불에 휩싸인 것이다!\n");
			printf("1. 물로 불을 소화한다. \n2. 벙커의 내구도를 믿으며 버틴다.\n");
			while (1) {
				printf("어떻게 해야 할까?\n- ");
				scanf(" %d", &i);
				if (i == 1) {
					if (player.water == 0) {
						printf("\n→ 물이 부족하다.\n");
					}
					else {
						printf("\n→ 물 2개를 이용해 벙커 주변의 불을 껐다.\n");
						printf("만약 끄지 않았다면 우린 통구이가 되었을 것이다.\n");
						player.water -= 2;
						before = 1;
						break;
					}
				}
				else if (i == 2) {
					int random2 = rand() % 6;
					int random3 = rand() % 4;
					if (random2 == 0) {
						printf("\n→ 화재로는 다치지 않았지만 연기가 마셔버린 탓에");
						if (random3 == 0) {
							player.dad[4]--;
							printf("아빠가 다쳤다.\n");
						}
						else if (random == 1) {
							player.mom[4]--;
							printf("엄마가 다쳤다.\n");
						}
						else if (random == 2) {
							player.son[4]--;
							printf("아들이 다쳤다.\n");
						}
						else if (random == 3) {
							player.dau[4]--;
							printf("딸이 다쳤다.\n");
						}
						before = 1;
						break;
					}
					else {
						printf("\n→ 이정도면 이미 대형 화재지만 핵폭발을 버틴 벙커이니 상관 없을 것이다.\n");
						before = 1;
						break;
					}
				}

				else {
					printf("\n잘못 누르셨습니다.\n");
				}
				
			}
		}

		// 정리 이벤트
		else if (random == 7) {
			char c;
			if (before == 2) {
				before = 0;
				goto previous;
			}
			printf("전에는 몰랐으나, 벙커 안쪽 침대 구석진 곳에 무언가가 있는 것을 발견했다.\n");
			while (1) {
				printf("확인해볼까? (y or n)\n- ");
				scanf(" %c", &c);
				if (c == 'y' || c == 'Y') {
					if (player.food < player.water) {
						printf("\n→ 그곳에는 토마토 스프 1개가 굴러다니고 있었다.\n");
						printf("정리의 중요함을 다시 깨닫게 되었다.\n");
						player.food++;
						before = 2;
						break;
					}
					else {
						printf("\n→ 그곳에는 물병 1개가 굴러다니고 있었다.\n");
						printf("정리의 중요함을 다시 깨닫게 되었다.\n");
						player.water++;
						before = 2;
						break;
					}
				}
				else if (c == 'n' || c == 'N') {
					printf("\n→ 오랫동안 미사용된 벙커를 방치해 생긴 먼지덩어리 뿐이었다.\n");
					before = 2;
					break;
				}
				else {
					printf("\n잘못 누르셨습니다.\n");
				}
			}
		}
	}
	

}

void badEvent() {
	int random = rand() % 10;
	int i = 0;

	// 이벤트 중복발생 방지문
	while (1) {
		printf("random=%d, badevent=%d\n", random, badevent);
		if (badevent == random) {
			random = rand() % 10;
		}
		else {
			break;
		}
	}
	
	printf("[bad event]\n");

	// 강도 침입이벤트
	if (random == 0) {
		printf("bad 1. 강도 이벤트\n");
		printf("강도들이 침입을 하려고 벙커의 문을 부수려고 한다. 어떻게든 막아야 한다!\n");
		printf("---------------------------\n");
		printf("1. 자물쇠로 벙커를 잠근다.\n");
		printf("2. 총으로 위협한다.\n");
		printf("3. 도끼로 위협한다.\n");
		printf("4. 칼로 위협한다.\n");
		printf("5. 아무것도 없이 버텨본다.\n");
		if (player.dog == 1) {
			printf("6. 강아지와 함께 막는다.\n");
		}
		printf("----------------------------\n");
		while (1) {
			printf("어떤 것들로 막을까?\n- ");
			scanf(" %d", &i);
			if (i == 1) {
				if (player.lock == 0) {
					printf("\n→ 자물쇠가 부족하다.\n");
				}
				else {
					printf("\n→ 자물쇠로 문을 잠근 다음 어떻게든 침입해보려는 강도를 도발하며 안전하게 지냈다.\n");
					player.lock--;
					break;
				}
			}
			else if (i == 2) {
				if (player.gun == 0) {
					printf("\n→ 총이 부족하다.\n");
				}
				else {
					printf("\n→ 총만큼 든든하고 멋진 친구는 없을 것이다. 강도에게 보여주자 줄행랑을 쳤다.\n");
					break;
				}
			}
			else if (i == 3) {
				if (player.ax == 0) {
					printf("\n→ 도끼가 부족하다.\n");
				}
				else {
					printf("\n→ 좁은 벙커 문으로 들어오다가는 도끼가 용서하지 않을 것이다. 강도는 하던것을 멈추고 달아났다.\n");
					break;
				}
			}
			else if (i == 4) {
				if (player.knife == 0) {
					printf("\n→ 칼이 부족하다.\n");
				}
				else {
					printf("\n→ 좁은 문으로 들어오다가는 모두 회가 될 것이다.\n");
					break;
				}
			}
			else if (i == 5) {
				if (player.food < 2) {
					player.food = 0;
				}
				else {
					player.food -= 2;
				}
				if (player.water < 2) {
					player.water = 0;
				}
				else {
					player.water -= 2;
				}
				printf("강도를 막지 못했다. 작은 몸다툼이 있었지만 인원수 차이로 당하기만 했다.\n");
				printf("썩은 이빨이 보이게끔 웃으면서 식량, 물을 뺏어갔고, ");
				int random2 = randomSystem(4);
				switch (random2) {
				case 0:
					printf("라디오를 부셨다.\n");
					player.radio--;
					break;
				case 1:
					printf("손전등을 부셨다.\n");
					player.flash--;
					break;
				case 2:
					printf("지도를 찢었다.\n");
					player.map--;
					break;
				case 3:
					printf("살충제를 가져갔다.\n");
					player.pesticide--;
					break;
				}
				break;
			}
			else {
				printf("잘못 누르셨습니다.");
			}
		}
		badevent = 0;
	}
	else if (random == 1) {
		printf("미구현 이벤트 (random =1)\n");
		badevent = 1;
	}
	else if (random == 2) {
		printf("미구현 이벤트 (random =2)\n");
		badevent = 2;
	}
	else if (random == 3) {
		printf("미구현 이벤트 (random = 3)\n");
		badevent = 3;

	}
	else if (random == 4) {
		printf("미구현 이벤트 (random = 4)\n");
		badevent = 4;
	}
	else if (random == 5) {
		printf("미구현 이벤트 (random = 5)\n");
		badevent = 5;
	}
	else if (random == 6) {
		printf("미구현 이벤트 (random = 6\n");
		badevent = 6;
	}
	else if (random == 7) {
		printf("미구현 이벤트 (random = 7)\n");
		badevent = 7;
	}
	else if (random == 8) {
		printf("미구현 이벤트 (random = 8)\n");
		badevent = 8;
	}
}

void normalEvent() {
	int i = 0, randomNum;
	char c;
	int random = rand() % 10;

	// 이벤트 중복발생 방지문
	while (1) {
		printf("random=%d, normalevent=%d\n", random, normalevnet);
		if (normalevnet == random) {
			random = rand() % 10;
		}
		else {
			break;
		}
	}

	// 지친 가족을 위한 이벤트
	if (random == 0) {
		printf("가족들이 쥐죽은 듯이 조용하다. 뭔가 조치를 취해야 할 것 같다.\n");
		printf("1. 라디오를 이용해본다.\n2. 아무것도 하지 않는다.\n");
		while (1) {
			printf("어떤 것을 해야 할까?\n- ");
			scanf(" %d", &i);
			if (i == 1) {
				if (player.radio == 0) {
					printf("\n→ 라디오가 없다.\n");
				}
				else {
					printf("\n→ 가족들은 라디오로 주파수를 찾다가 음악을 듣게 되었고, 머리가 조금 맑아지는 기분이 들었다.\n");
					randomNum = randomSystem(6);
					if (random == 1) {
						player.radio -= 1;
						printf("+ 라디오를 부적절하게 사용한 거 같다. 라디오가 고장났다\n");
					}
					break;
				}
			}
			else if (i == 2) {
				int random = rand() % 6;
				if (random == 0) {
					int random2 = randomSystem(4);
					printf("과묵 속에서 마음앓이를 하다가 결국");
					if (random2 == 0) {
						player.dad[2] -= 1;
						printf("아빠가 마음을 다잡지 못해 미쳐버렸다.\n");
					}
					else if (random2 == 1) {
						player.mom[2] -= 1;
						printf("엄마가 마음을 다잡지 못해 미쳐버렸다.\n");
					}
					else if (random2 == 1) {
						player.son[2] -= 1;
						printf("아들이 마음을 다잡지 못해 미쳐버렸다.\n");
					}
					else if (random2 == 1) {
						player.dau[2] -= 1;
						printf("딸이 마음을 다잡지 못해 미쳐버렸다.\n");
					}
					break;
				}
				else{
					printf("\n→ 이 조용하고 쓸쓸한 분위기를 굳이 깨야할까?라는 기분이 든다.\n");
					break;
				}
			}
			
			else {
				printf("\n잘못 누르셨습니다.\n");
			}
		}
		normalevnet = 0;
	}

	// 광대 이벤트
	else if (random == 1) {
		printf("1. 광대 이벤트\n");
		printf("부유한 자에게 물자를 빼앗아 가난한 자들에게 나누어준다는 녹색옷의 사람들이 벙커를 찾아왔다.\n");
		while (1) {
			printf("열어줄까? (y or n)\n- ");
			scanf(" %c", &c);
			if (c == 'y' || c == 'Y') {
				if (player.food > 3 && player.water > 3) {
					printf("물자를 나누어 주기엔 우리 가족은 너무 많다며 오히려 식량과 물을 1개씩 뺐어갔다.\n");
					player.food--; player.water--;
					break;
				}
				else {
					printf("그들은 말 그대로 식량과 물 1개씩 기부해주고 떠나버렸다.\n");
					player.food++; player.water++;
					break;
				}
			}
			else if (c == 'n' || c == 'N') {
				printf("역시 수상한 사람이 방문할 필요는 없는 거 같다\n");
				break;
			}
			else {
				printf("잘못 누르셨습니다.");
			}
		}
		normalevnet = 1;

	}

	// 빈곤한 생존자 이벤트
	else if (random == 2) {
		printf("빈곤한 생존자들이 물자를 달라고 요구해왔다.\n");
		printf("1. 식량 2개\n2. 물 2개\n3. 구급약\n4. 주지 않는다.\n");
		while (1) {
			printf("뭘 줄까?\n- ");
			scanf(" %d", &i);
			if (i == 1) {
				if (player.food < 2) {
					printf("식량이 부족해서 주지 못할 것 같다.\n");
				}
				else {
					player.food -= 2;
					printf("식량 2개를 줬다.\n");
					player.dad[2]++;
					player.mom[2]++;
					player.son[2]++;
					player.dau[2]++;
					printf("가난한 자를 도와주었다는 생각에 모두의 정신력이 강화되었다.\n");
					break;
				}
			}
			else if (i == 2) {
				if (player.water < 2) {
					printf("물이 부족해서 주지 못할 것 같다.");
				}
				else {
					player.water -= 2;
					player.dad[2]++;
					player.mom[2]++;
					player.son[2]++;
					player.dau[2]++;
					printf("믈 2개를 줬다.\n");
					printf("가난한 자를 도와주었다는 생각에 모두의 정신력이 강화되었다.\n");
					break;
				}
			}
			else if (i == 3) {
				if (player.first_aid_kit < 1) {
					printf("구급약이 부족해서 주지 못할 것 같다.\n");
				}
				else {
					player.first_aid_kit--;
					player.dad[2]++;
					player.mom[2]++;
					player.son[2]++;
					player.dau[2]++;
					printf("구급약을 줬다.\n");
					printf("가난한 자를 도와주었다는 생각에 모두의 정신력이 강화되었다.\n");
					break;
				}
			}
			else if (i == 4) {
				int random = rand() % 11;
				if (random = 0) {
					player.food = 0; player.water = 0;
					printf("빈곤한 생존자들이 쳐들어와 물자를 싹다 털어갔다.\n");
					break;
				}
				else {
					printf("빈곤한 생존자들은 어쩔 수 없이 다시 길을 걸어갔다\n");
					break;
				}
			}
			else {
				printf("잘못 입력하셨습니다.\n");
			}
		}
		normalevnet = 2;
	}

	// 샤워 이벤트
	else if (random == 3) {
		printf("벙커에서 생활하다 보니 샤워를 못한 지 오래다. 그나마 냄새를 없앨 수 있는 건 총알 속 화약인 것 같다.\n");
		while (1) {
			printf("샤워를 할까? (y or n)\n- ");
			scanf(" %c", &c);
			if (c == 'y' || c == 'Y') {
				printf("확실히 샤워는 청결과 직결되있는 문제이다.\n");
				printf("샤워를 하고 휴식을 취하니 질병이 나았다.\n");
				player.dad[5]++;
				player.mom[5]++;
				player.son[5]++;
				player.dau[5]++;
			}
			else if (c == 'n' || c == 'N') {
				int random = rand() % 4;
				if (random == 0) {
					random = rand() % 4;
					switch (random) {
					case 0:
						player.dad[5] -= 1;
						printf("샤워를 하지 못해 아빠가 질병에 걸렸다.\n");
						break;
					case 1:
						player.mom[5] -= 1;
						printf("샤워를 하지 못해 엄마가 질병에 걸렸다.\n");
						break;
					case 2:
						player.son[5] -= 1;
						printf("샤워를 하지 못해 아들이 질병에 걸렸다.\n");
						break;
					case 3:
						player.dau[5] -= 1;
						printf("샤워를 하지 못해 딸이 질병에 걸렸다.\n");
						break;
					}

				}
				else {
					printf("이런 고난 속에서 샤워는 참을 수 있어야 한다.\n");
				}
				break;
			}
			else {
				printf("잘못 누르셨습니다.");
			}
		}
		normalevnet = 3;
	}

	// 탄약상 방문 이벤트
	else if (random == 4) {
		printf("밖에서 탄약상이 방문해왔다. 물물거래를 하자고 했다.\n");
		printf("1. 체커\n2. 탄약.\n3. 아무것도 주지 않는다.\n");
		while (1) {
			printf("어떤것을 줘야할까?\n- ");
			scanf(" %d", &i);
			if (i == 1) {
				if (player.chess == 0) {
					printf("체커가 부족해 주지 못할 것 같다.\n");
				}
				else {
					printf("체커를 줬다.\n고맙다며 대가로 식량과 물을 1개씩 주었다.");
					player.food++;
					player.water++;
					break;
				}
			}
			else if (i == 2) {
				if (player.ammo == 0) {
					printf("탄이 없는 것을 미리 확인했는데도 거짓말을 하냐면서 동시에 연막탄을 터뜨렸다..\n");
					printf("연막이 거치고 나니 식량 2개와 물 1개가 없어졌다.\n");
					player.food -= 2;
					player.water--;
					break;
				}
				else {
					printf("무기는 많으나 부족한 탄약을 채워주었다고 큰 고마움을 표시했다.\n고맙다며 대가로 ");
					if (player.ax == 0 && player.knife == 1) {
						printf("칼은 있는 것 같다며 도끼를 건네주었다.\n");
					}
					else if (player.knife == 0 && player.ax == 1) {
						printf("도끼는 있는 것 같다며 칼을 건네주었다.");
					}
					else {
						int random = rand() % 2;
						if (random == 0) {
							printf("도끼를 건네주었다.\n");
							player.ax++;
						}
						else if (random == 1) {
							printf("칼을 건네주었다.\n");
							player.knife++;
						}
					}
					break;
				}
			}
			else if (i == 3) {
				printf("끝내주는 무기고 판매원과 거래를 하지 못해 아쉬웠다.\n");
				break;
			}
			else {
				printf("잘못 누르셨습니다.");
			}
		}
		normalevnet = 4;
	}

	// 거미 발견 이벤트
	else if (random == 5) {
		printf("가족이 벙커에서 생활하던 도중 거미를 발견했다.\n");
		printf("1. 살충제로 처리한다.\n2. 책으로 잡는다\n3. 구급약을 사용한다.\n4. 맨 손으로 잡아본다.\n");
		while (1) {
			printf("어떻게 해야할까?\n- ");
			scanf(" %d", &i);
			if (i == 1) {
				if (player.pesticide == 0) {
					printf("\n→ 살충제가 부족합니다\n");
				}
				else {
					printf("\n→ 살충제를 사용해 거미를 잡았다.\n");
					printf("살충제를 소비했습니다.\n");
					player.pesticide--;
					break;
				}
			}
			else if (i == 2) {
				if (player.book == 0) {
					printf("\n→ 책이 부족합니다.\n");
				}
				else {
					printf("\n→ 곤충들을 잡는데는 책 만한게 없다!\n");
					printf("거미들이 있던 벙커 구석진 곳에서 ");
					int random = rand() % 2;
					if (random == 0) {
						printf("식량을 발견했다.\n");
						player.food++;
					}
					else if (random == 1) {
						printf("물을 발견했다\n");
						player.water++;
					}
					break;
				}
			}
			else if (i == 3) {
				if (player.first_aid_kit == 0) {
					printf("\n→ 구급약이 부족합니다.\n");
				}
				else {
					printf("\n→ 우리는 오랜 시간을 벙커에서 지내다 보니 환상이라 생각했고, \n");
					printf("구급약 속 향정신성 약을 사용해보니 거미는 사라져있었다.\n");
					player.first_aid_kit--;
					break;
				}
			}
			else if (i == 4) {
				printf("\n→ 거미를 안잡는 것 보다 더 심각한 건 없다고 생각한다. 맨 손으로 억지로 잡아보려다가\n");
				printf("거미에게 물렸고, ");
				int random2 = rand() % 4;
				switch (random2) {
				case 0:
					player.dad[5] -= 1;
					printf("아빠가 질병에 걸렸다.\n");
					break;
				case 1:
					player.mom[5] -= 1;
					printf("엄마가 질병에 걸렸다.\n");
					break;
				case 2:
					player.son[5] -= 1;
					printf("아들이 질병에 걸렸다.\n");
					break;
				case 3:
					player.dau[5] -= 1;
					printf("딸이 질병에 걸렸다.\n");
					break;
				}
				break;
			}
			else {
				printf("\n잘못 누르셨습니다.\n");
			}
		}
		normalevnet = 5;
	}

	// 낮선 사람 - 카지노 딜러 (씨발 게임 땜에 개길어)
	else if (random == 6) {
	int num1, num2, n = 1;
	printf("바깥에서 낮선 누군가가 문을 두들겼다.\n");
	while (1) {
		printf("열어볼까? (y or n)\n- ");
		scanf(" %c", &c);
		if (c == 'y' || c == 'Y') {
			printf("문을 열어보니 깔끔한 검은 색 양복을 입은 낮선 남자가 우두커니 서있었다\n");
			printf("그는 카지노 딜러였고 게임을 하자고 권했다. 게임은 간단했다.\n");
			printf("4면 주사위를 통해 더 큰 숫자가 이기는 게임이다.\n");
			printf("순수하게 게임만 하는 것은 재미없기에, 식량 또는 물을 걸기로 하였다.\n ");
			printf("서로의 숫자가 같을 때 까지, 또는 서로의 식량, 물이 없을 때 까지 게임을 진행한다.\n");
			while (1) {
				printf("게임을 하시겠습니까? (y or n)\n- ");
				scanf(" %c", &c);
				if (c == 'y' || c == 'Y') {
					while (1) {
						printf("식량 또는 물 중 어떤 것을 걸겠습니까?\n- ");
						scanf(" %d", &i);
						if (i == 1) {
							if (player.food == 0) {
								printf("\n→ 걸 수 있는 식량이 없다.\n");
								continue;
							}
							else {
								break;
							}

						}
						else if (i == 2) {
							if (player.water == 0) {
								printf("\n→ 걸 수 있는 식량이 없다.\n");
								continue;
							}
							else {
								break;
							}
						}
						else {
							printf("\n잘못 입력하셨습니다.\n");
							continue;
						}
						system("cls");
						printf("게임을 시작합니다.\n");

					game:
						if (player.food == 0 || player.water == 0) {
							printf("이런! 게임에 열중하다 보니 ");
							if (i == 1) {
								printf("우리의 식량이 다 떨어졌다.\n");
								printf("남자는 웃으면서 아깝다는 말과 함께 벙커를 떠났다.\n");
								break;
							}
							else if (i == 2) {
								printf("우리의 물이 다 떨어졌다.\n");
								printf("남자는 웃으면서 아깝다는 말과 함께 벙커를 떠났다.\n");
								break;
							}
						}
						printf("게임 %d번째\n", n);
						num1 = randomSystem(4) + 1;
						num2 = randomSystem(4) + 1;
						printf("우리의 숫자: %d\n", num1);
						printf("남자의 숫자: %d\n", num2);
						if (num1 > num2) {
							printf("우리가 이겼다!\n");
							printf("남자는 웃으면서 아깝다는 표정으로 ");
							if (i == 1) {
								player.food++;
								printf("식량 1개를 줬다.\n");
							}
							else if (i == 2) {
								player.water++;
								printf("물 1개를 줬다.\n");
							}
							goto game;
						}
						else if (num1 < num2) {
							printf("우리가 졌다.\n");
							printf("남자는 웃으면서 담담한 표정으로 ");
							if (i == 1) {
								player.food--;
								printf("식량 1개를 받아갔다.\n");
							}
							else if (i == 2) {
								player.water--;
								printf("물 1개를 받아갔다.\n");
							}
							goto game;
						}
					}
					break;
				}

				else if (c == 'n' || c == 'N') {
					printf("\n→ 우리 가족은 도박은 일절 피하는 입장이었고, 낮선 남자는 아쉽다며 떠났다.\n");
					break;
				}
				else {
					printf("\n잘못 누르셨습니다.\n");
				}
			}
			break;
		}
		else if (c == 'n' || c == 'N') {
			printf("\n→ 역시 수상한 사람이 방문할 필요는 없는 거 같다\n");
			break;
		}
		else {
			printf("잘못 누르셨습니다.");
		}
	}
	normalevnet = 6;
	}

	// 
	else if (random == 7) {
		printf("미구현 이벤트 (random = 7)");
		normalevnet = 7;
	}
	else if (random == 8) {
		printf("미구현 이벤트 (random = 8)");
		normalevnet = 8;
	}
	else if (random == 9) {
		printf("미구현 이벤트 (random = 9)");
		normalevnet = 9;
	}
}

void goodEvent() {
	// 여기에 댕댕이랑 냥냥이 이벤트
	int i, rock = 0;
	char c;
	int random = rand() % 10;

	while (1) {
		printf("random=%d, goodevent=%d\n", random, goodevent);
		if (goodevent == random) {
			random = rand() % 10;
		}
		else {
			break;
		}
	}

	// 자유의 이름
	if (random == 0) {
		printf("자유의 이름으로 문을 열라는 미치광이가 벙커 앞에서 소리쳤다.\n");
		while (1) {
			printf("열어줄까? (y or n)\n- ");
			scanf(" %c", &c);
			if (c == 'y' || c == 'Y') {
				printf("미치광이의 생김새는 이미 낙진으로 인해 많은 질병을 앓아온 듯 했다.\n");
				printf("하지만 문을 열어준 우리에게 신뢰감을 표시하며");
				if (player.ax == 0 && player.knife == 0 && player.gun == 0) {
					int random = rand() % 3;
					if (random == 0) {
						printf("무기인 도끼를 주었다.\n");
						player.ax++;
					}
					else if (random == 1) {
						printf("무기인 칼을 건네주었다.\n");
						player.knife++;
					}
					else {
						printf("무기인 총을 건네주었다.\n");
						player.gun++;
					}
				}
				else {
					printf("식량 2개와 물 1개를 건네주었다.\n");
					player.food += 2;
					player.water += 1;
				}
			}
			else if (c == 'n' || c == 'N') {
				printf("역시 수상한 사람이 방문할 필요는 없는 거 같다\n");
				break;
			}
			else {
				printf("잘못 누르셨습니다.");
			}
		}
		goodevent = 0;
	}

	// 노숙자 - 돌 판매
	else if (random == 1) {
		if (rock == 0) {
			printf("노숙자들이 갑자기 벙커를 방문에 돌을 팔러 왔다고 전했다. 갑작스런 돌 방문 판매는 처음인 것 같다.\n");
			while (1) {
				printf("돌을 구매할까? (y or n)\n- ");
				scanf(" %c", &c);
				if (c == 'y' || c == 'Y') {
					printf("무료인 돌을 거절하기엔 아깝다.\n돌을 구매했다.");
					rock++;
					break;
				}
				else if (c == 'n' || c == 'N') {
					printf("돌을 파는 미치광이들을 대면할 필요는 없다.\n");
					break;
				}
				else {
					printf("잘못 누르셨습니다.");
				}
			}
		}
		else if (rock == 1 && player.water == 0) {
			printf("전에 돌을 판매했던 노숙자가 찾아와 돌을 갖고 있는 사람들에게는 축복이 다가왔다고 전했다.\n");
			printf("위대한 돌 만세! (물 3개를 받았습니다.)\n");
			player.water = 3;
		}
		goodevent = 1;
	}

	else if (random == 2) {
		printf("미구현 이벤트 (random = 2)");
		goodevent = 2;
	}
	else if (random == 3) {
		printf("미구현 이벤트 (random = 3)");
		goodevent = 3;
	}
	else if (random == 4) {
		printf("미구현 이벤트 (random = 4)");
		goodevent = 4;
	}
	else if (random == 5) {
		printf("미구현 이벤트 (random = 5)");
		goodevent =5 ;
	}
	else if (random == 6) {
		printf("미구현 이벤트 (random = 6)");
		goodevent = 6;
	}
	else if (random == 7) {
		printf("미구현 이벤트 (random = 7)");
		goodevent =7 ;
	}
	else if (random == 8) {
		printf("미구현 이벤트 (random = 8)");
		goodevent =8 ;
	}
	else if (random == 9) {
		printf("미구현 이벤트 (random = 9)");
		goodevent = 9;
	}
}

// 모든 이벤트에 no 할 경우 구현하기
void militaryEvent() {
	// 라디오가 있을 때만
	int i = 0;
	char c;
	if (eventTurn == 0) {
		printf("라디오의 주파수를 만지던 도중 군부대의 주파수를 찾게 되었고 생존자는 접선지로 나오라고 했다.\n");
		while (1) {
			printf("나갈까? (y or n)\n- ");
			scanf(" %c", &c);
			if (c == 'y' || c == 'Y') {
				printf("\n→ 말 그대로 군복과 장비를 차고 있는 군 부대를 접했고, 추후 통제가 있을 거라고 전했다.\n");
				eventTurn++;
				break;
			}
			else if (c == 'n' || c == 'N') {
				printf("\n→ 이 세상에서 누구라도 맘먹으면 군부대라고 속일 수 있을 것이다.\n");
				eventCancel = 1;
				break;
			}
			else {
				printf("\n잘못 누르셨습니다.\n");
			}
		}
	}

	else if (eventTurn == 1) {
		
		printf("군부대가 라디오를 통해 전에 만난 생존자는 거주 위치 근처에 일종 표식을 남기라고 했다.\n");
		printf("----------\n");
		printf("1. 지도\n");
		printf("2. 카드\n");
		printf("3. 손전등\n");
		printf("4. 어떻게든 표식을 남긴다.\n");
		printf("----------\n");
		while (1) {
			printf("어떤 것으로 표식을 남길까?\n- ");
			scanf(" %d", &i);
			if (i == 1) {
				if (player.map == 0) {
					printf("\n→ 지도가 없어 이 작업은 할 수 없을 것 같다.\n");
				}
				else {
					player.map = 0;
					printf("\n→ 지도로 표시했다.\n");
					break;
				}
			}
			else if (i == 2) {
				if (player.card == 0) {
					printf("\n→ 카드가 없어 이 작업은 할 수 없을 것 같다.\n");
				}
				else {
					player.card = 0;
					printf("\n→ 카드로 표시했다.\n");
					break;
				}

			}
			else if (i == 3) {
				if (player.flash == 0) {
					printf("\n→ 손전등이 없어 이 작업은 할 수 없을 것 같다.\n");
				}
				else {
					player.flash--;
					printf("\n→ 손전등로 표시했다.\n");
					break;
				}

			}
			else if (i == 4) {
				if (player.food > 0) {
					if (player.food < 2) {
						printf("\n→ 남아있는 식량을 전부 써서 SOS를 그렸다.\n");
						break;
					}
					else {
						printf("\n→ 어떻게든 표식을 남기기 위해 식량 2개를 써서 SOS를 그렸다\n");
						player.food -= 2;
						break;
					}

				}
			}
			else {
				printf("\n잘못 입력하셨습니다.\n");
			}
		}
		eventTurn++;
	}
	else if (eventTurn == 2) {

		printf("군인이 생존자를 구조하기 위해서는 생존자들의 도움 또한 필요하다고 했다.\n");
		printf("----------\n");
		printf("1. 도끼를 들고 헬기 착륙장 건설을 위해 나무를 벤다 (도끼 확률적 소모)\n");
		printf("2. 방독면을 쓰고 인근 주유소에서 휘발유를 가져온다. \n");
		printf("3. 위험 요소를 없애기 위해 총기를 버린다.\n");
		printf("----------\n");
		while (1) {
			printf("어떤 작업을 할까?\n- ");
			scanf(" %d", &i);
			if (i == 1) {
				if (player.ax == 0) {
					printf("\n→ 도끼가 없어 이 작업은 할 수 없을 것 같다.\n");
				}
				else {
					// 25%확률로 파킨
					int random = rand() % 4;
					if (random == 0) {
						player.ax = 0;
						printf("\n→ 도끼로 작업했다.\n");
						printf("+ 그리고 작업 하던 도중 도끼가 부서졌다.");
						break;
					}
					else {
						printf("\n→ 도끼로 작업했다.\n");
						break;
					}
				}
			}
			else if (i == 2) {
				if (player.gas_mask == 0) {
					printf("\n→ 방독면이 없어 이 작업은 할 수 없을 것 같다.\n");
				}
				else {
					printf("\n→ 방독면으로 휘발유를 챙겨놨다.\n");
					break;
				}
			}
			else if (i == 3) {
				if (player.gun == 0) {
					printf("\n→ 애초에 총도 없다는 것을 간절하게 표현했다.\n");
					break;
				}
				else {
					printf("\n→ 총을 버려 군부대에게 신뢰감을 표시했다.\n");
					player.gun = 0;
					break;
				}

			}
			else {
				printf("\n잘못 입력하셨습니다.\n");
			}

		}
		eventTurn++;
	}

	// 이거 explo 따로 작업?하기
	else if (eventTurn == 3) {
		printf("군의 요청으로 생존자들 중 한 명과 접촉을 원했다.\n ");
		printf("―――――――――\n");
		printf("1. 아빠\n");
		printf("2. 엄마\n");
		printf("3. 아들\n");
		printf("4. 딸\n");
		printf("―――――――――\n");
		while (1) {
			printf("누굴 보낼까?\n- ");
			scanf(" %d", &i);
			if (i == 1) {
				printf("\n→ 아빠가 나가기로 했다.\n");
				printf("+ 통제를 받던 도중 강도 무리의 습격으로 인해 군부대와 아빠가 다쳤다\n");
				player.dad[4]--;
				break;
			}
			if (i == 2) {
				printf("\n→ 엄마가 나가기로 했다.\n");
				printf("+ 통제를 받던 도중 강도 무리의 습격으로 인해 군부대와 엄마가 다쳤다\n");
				player.mom[4]--;
				break;
			}
			if (i == 3) {
				printf("\n→ 아들이 나가기로 했다.\n");
				printf("+ 통제를 받던 도중 강도 무리의 습격으로 인해 군부대와 아들이 다쳤다\n");
				player.son[4]--;
				break;
			}
			if (i == 4) {
				printf("\n→ 딸이 나가기로 했다.\n");
				printf("+ 통제를 받던 도중 강도 무리의 습격으로 인해 군부대와 딸이 다쳤다\n");
				player.dau[4]--;
				break;
			}
			else {
				printf("\n잘못 입력하셨습니다.\n");
			}
		}
		eventTurn++;
	}
	else if (eventTurn == 4) {
		//게임 엔딩
		printf("밖에서 간절하게 두드린다. 하지만 시끄럽고 많은 인원에 무슨 상황인지 알 수 없다. \n");
		printf("―――――――――――――――\n");
		printf("1. 밖을 열어서 확인해본다.\n");
		printf("2. 위험하니 열지 않는다.\n");
		printf("―――――――――――――――\n");
		while (1) {
			printf("열어볼까?\n- ");
			scanf(" %d", &i);
			if (i == 1) {
				printf("게임 종료, ");
				printf("군부대 엔딩 완료");
				exit(0);
			}
			else if (i == 2) {
				printf("\n→ 위험한 건 일절 제거해야 한다.\n");
				eventCancel = 1;

				break;
			}
			else {
				printf("\n[잘못 입력하셨습니다.]\n");
			}
		}

	}
}

void agentEvent() {
	int i = 0;
	char c;
	if (eventTurn == 0) {
		printf("샤리코프를 자세히 보니 목걸이에는 특정 주소가 적혀있었다.\n");

		while (1) {
			printf("가볼까? (y or n)\n- ");
			scanf(" %c", &c);
			if (c == 'y' || c == 'Y') {
				printf("\n→ 주소로 찾아가는 도중에 요원들이 나타나 샤리코프를 찾고있었다며 데리고 가버렸다.\n");
				printf("하지만 샤리코프는 며칠 뒤에 쥐도 새도 모르게 다시 방공호로 돌아온다.\n");
				eventTurn++;
				break;
			}
			else if (c == 'n' || c == 'N') {
				printf("\n→ 이미 핵폭발이 일어난 시점에 그곳에 가도 별 의미 없을 것이다. \n");
				eventCancel = 2;
				break;
			}
			else {
				printf("잘못 누르셨습니다.");
			}
		}
	}
	else if (eventTurn == 1) {
		printf("샤리코프가 가지고 놀고 있는 튀어나온 전선을 조사하면 방공호를 도청 중이던 요원들을 발견했다.\n");
		while (1) {
			printf("쫒아낼까? (y or n)\n- ");
			scanf(" %c", &c);
			if (c == 'y' || c == 'Y') {
				printf("무슨 일이 있어도 남의 벙커를 도청하면 나쁜 일이다.\n");
				eventTurn++;
				break;
			}
			else if (c == 'n' || c == 'N') {
				printf("이렇게 따분한 벙커를 도청해봤자 아무런 이득도 없을 것이다.");
				break;
			}
			else {
				printf("잘못 누르셨습니다.");
			}
		}
	}
	else if (eventTurn == 2) {
		printf("저번에 도청 중이던 요원이 이번엔 정식적으로 문을 두들겼다. 무슨 용무인지는 잘 모르겠다.\n");
		while (1) {
			printf("열어줄까? (y or n)\n- ");
			scanf(" %c", &c);
			if (c == 'y' || c == 'Y') {
				printf("열어주게 되면 자신들이 정부의 요원들이며 샤리코프가 소련의 스파이일 가능성이 있어\n 도청 중이었다는 말과 함께 자신들을 도우면 좋은 곳으로 데려가주겠다고 하고 돌아간다.\n");
				eventTurn++;
				break;
			}
			else if (c == 'n' || c == 'N') {
				printf("도청한 사람들을 방문할 필요는 없는 거 같다\n");
				break;
			}
			else {
				printf("잘못 누르셨습니다.");
			}
		}
	}
	else if (eventTurn == 3) {
		// 요원의 지시에 따라 탐사하는 이벤트
		printf("요원들이 자신들 대신 어느 지역을 조사해 달라고 요구하며 가족 한명을 보낼 수 있다.\n");
		while (1) {
			printf("누굴 보내줄까?\n- ");
			printf("1. 아빠\n2. 엄마\n3. 아들\n4. 딸");
			scanf(" %d", &explo);
			if (explo == 1) {
				printf("아빠가 요원의 요청에 답하기로 했다.\n");
				break;
			}
			else if (explo == 2) {
				printf("엄마가 요원의 요청에 답하기로 했다.\n");
				break;
			}
			else if (explo == 3) {
				printf("아들이 요원의 요청에 답하기로 했다.\n");
				break;
			}
			else if (explo == 4) {
				printf("딸이 요원의 요청에 답하기로 했다.\n");
				break;
			}
			else {
				printf("잘못 누르셨습니다.");
			}
		}
		eventTurn++;
	}
	else if (eventTurn == 4) {
		printf("요원들이 지금까지의노고를 치하하며 다른 곳에서 임무 중인 요원들에게 보낼 물자를 요구한다\n");
		printf("1. 식량 4개\n2. 물 4개\n3. 주지 않는다.\n");
		while (1) {
			printf("뭘 줄까?\n- ");
			scanf(" %d", &i);
			if (i == 1) {
				if (player.food < 4) {
					printf("식량이 부족해서 주지 못할 것 같다.\n");
				}
				else {
					player.food -= 4;
					printf("식량 4개를 줬다.\n");
					eventTurn++;
					break;
				}
			}
			else if (i == 2) {
				if (player.water < 4) {
					printf("물이 부족해서 주지 못할 것 같다.");
				}
				else {
					player.water -= 4;
					printf("물 4개를 줬다.\n");
					eventTurn++;
					break;
				}
			}
			else if (i == 3) {
				printf("지금은 부족해서 주지 못할 것 같다.");
				break;
			}
		}
	}
	else if (eventTurn == 5) {
		printf("바깥에서 웅성대는 소리가 났다. 노크 소리와 함께 밖을 바라봤으나, \n");
		printf("아무도 없었고, 미심쩍기만 했다.\n");
		printf("1. 연다\n2.열지 않는다.\n");
		while (1) {
			printf("밖을 열어 누가 왔는지 확인할까?\n- ");
			scanf(" %d", &i);
			if (i == 1) {
				printf("게임 종료\n");
				return 0;
			}
			else if (i == 2) {
				printf("혀 차는 소리와 함께 무전기를 통해 철수한다는 소리를 듣게 되었다.\n");
				eventCancel = 2;
				eventTurn = 0;
				break;
			}
			else {
				printf("잘못 입력하셨습니다.\n");
			}
		}
	}
}

void twinEvent() {
	int n = 0, i = 0;
	char c;
	if (eventTurn == 0) {
		//  공중 전화로 전화가 걸려와 가족 중 한 명이 받아야 함
		printf("부서진 줄만 알았던 공중전화해서 전화가 걸려왔다.\n");
		while (1) {
			printf("받으러 가볼까? (y or n)\n- ");
			scanf(" %c", &c);
			if (c == 'y' || c == 'Y') {
				printf("----------------------\n");
				printf("1. 아빠\n2. 엄마\n3. 아들\n4. 딸\n");
				printf("----------------------\n");
				while (1) {
					printf("누가 가지?\n- ");
					scanf(" %d", &i);
					if (i == 1) {
						printf("\n→ 아빠가 전화를 받으러 갔다.\n");
						break;
					}
					else if (i == 2) {
						printf("\n→ 엄마가 전화를 받으러 갔다.\n");
						break;
					}
					else if (i == 3) {
						printf("\n→ 아들이 전화를 받으러 갔다.\n");
						break;
					}
					else if (i == 4) {
						printf("\n→ 딸이 전화를 받으러 갔다.\n");
						break;
					}
					else {
						printf("\n잘못 입력하셨습니다.\n");
					}
				}
				printf("이에 한 여성이 전화를 받았고 자신이 구호단체에서 활동한다고 했고, 곧 접촉이 있을 거라고 했다.\n");
				printf("이런 멸망한 세상 속에서 저런 사람들이 있을까? 라고 생각하면서 벙커로 다시 돌아왔다.\n");
				eventTurn++;
				break;
			}
			else if (c == 'n' || c == 'N') {
				printf("\n→ 핵폭발 방사선으로 인해 고장났을 것이 뻔하다.\n");
				eventCancel = 3;
				break;
			}
			else {
				printf("잘못 누르셨습니다.");
			}
		}
	}
	else if (eventTurn == 1) {
		// 만약 n 했을 때 스토리 진행은 어케 할까?
		printf("밖이 시끌시끌해서 바라보니 강도가 어느 금발의 남성을 납치하고 있는 모습을 보았다.\n");
		while (1) {
			printf("도와줄까? (y or n)\n- ");
			scanf(" %c", &c);
			if (c == 'y' || c == 'Y') {
				// 6.도끼	7.칼	8.총
				printf("도와주기 위해선 적어도 위협될 무기가 필요할 것 같다.\n");
				printf("1. 도끼\n2. 칼\n3. 총\n4. 맨몸\n");
				while (1) {
					printf("어떤 무기를 들고 갈까?\n- ");

					scanf(" %d", &i);

					if (i == 1) {
						if (player.ax == 1) {
							printf("→ 도끼를 이용해 납치된 남성을 도와줬다.\n");
							break;
						}
						else {
							printf("→ 도끼가 없다.\n");
						}
					}
					else if (i == 2) {
						if (player.knife == 1) {
							printf("→ 칼을 이용해 납치된 남성을 도와줬다.\n");
							break;
						}
						else {
							printf("→ 칼이 없다.\n");
						}
					}
					else if (i == 3) {
						if (player.gun == 1) {
							printf("→ 총을 이용해 납치된 남성을 도와줬다.\n");
							break;
						}
						else {
							printf("→ 총이 없다.\n");
						}
					}
					else if (i == 4) {
						printf("----------------------\n");
						printf("1. 아빠\n2. 엄마\n3. 아들\n4.딸\n");
						printf("----------------------\n");
						while (1) {
							printf("누가 도와줄까?\n- ");
							scanf(" %d", &i);
							if (i == 1) {
								printf("→ 아빠가 도우러 갔다.\n");
								int random = rand() % 3;
								if (random == 0) {
									player.dad[4]--;
									printf("도와주던 도중 다쳤다.");
								}
								break;
							}
							else if (i == 2) {
								printf("→ 엄마가 도우러 갔다.\n");
								int random = rand() % 3;
								if (random == 0) {
									player.mom[4]--;
									printf("도와주던 도중 다쳤다.");
								}
								break;
								
							}
							else if (i == 3) {
								printf("→ 아들이 도우러 갔다.\n");
								int random = rand() % 3;
								if (random == 0) {
									player.son[4]--;
									printf("도와주던 도중 다쳤다.");
								}
								break;
							}
							else if (i == 4) {
								printf("→ 딸이 도우러 갔다.\n");
								int random = rand() % 3;
								if (random == 0) {
									player.dau[4]--;
									printf("도와주던 도중 다쳤다.");
								}
								break;
							}
							else {
								printf("잘못 입력하셨습니다.\n");
							}
						}
						break;
					}
					else {
						printf("\n잘못 입력하셨습니다\n");
					}
				}
				printf("금발의 남성은 핵폭발로 인해 다른 여러 고통받는 사람들을 돕고 있다고 했다.\n");
				printf("공중전화를 받은 가족, 즉 당신들에게 갈려다가 아버지, 강도의 두목에게 납치당했다고 했고,\n");
				printf("덕분에 큰 도움을 받았다고 전했다.\n");
				eventTurn++;
				break;
			}
			else if (c == 'n' || c == 'N') {
				printf("저 많은 강도 무리에게 갔다가는 나도 납치 될지도 모른다. \n");
				eventCancel = 3;
				break;
			}
			else {
				printf("\n잘못 누르셨습니다.\n");
			}
		}
	}
	else if (eventTurn == 2) {
		// 생존자를 위해 식량 하나 기부
		printf("저번에 도와준 남성의 여동생인 사람이 찾아와 강도에게 습격을 당했고, 겨우 가족의 벙커로 찾아왔다.\n");
		printf("몇일을 쫒겨 아무 것도 먹지도, 마시지도 못했다고 한다. \n");
		printf("1. 음식 \n2. 물\n3. 아무것도 주지 않는다.\n(기부 시 항목 -1)");
		while (1) {
			printf("어떤것을 줘야할까?\n-");
			scanf(" %d", &i);
			if (i == 1) {
				if (player.food == 0) {
					printf("음식이 부족해 주지 못할 것 같다.\n");
				}
				else {
					printf("음식을 줬다.\n");
					player.food--;
					eventTurn++;
					break;
				}
			}
			else if (i == 2) {
				if (player.water == 0) {
					printf("물이 부족해 주지 못할 것 같다.\n");
				}
				else {
					printf("물을 줬다.\n");
					player.water--;
					eventTurn++;
					break;
				}
			}
			else if (i == 3) {
				printf("주고 싶지만 우리 가족도 부족하다고 하여 미안함을 표현했다.\n");
				printf("하지만 쫒기는 강도에게 피할 곳을 준 것 만으로도 고맙다고 했다.\n");
				eventTurn++;
				break;
			}
			else {
				printf("잘못 누르셨습니다.");
			}
		}
	}
	else if (n == 3) {
		// 아이들을 위한 이벤트
		// 이전 이벤트에서 식량 or 물 소모 시 혜택을

		/*
		체커 이벤트(체커 소모)
		서바이벌 가이드 이벤트(서바이벌 가이드 소모)
		카드 이벤트(카드 소모)
		안전 장소 공사에 돕기 (맨손, 확률적 다침 or 질병)
		*/
		printf("이번엔 금발 남매가 모두 찾아와 저번에 목숨을 살려줘서 고맙다고 전했다.\n");

		//전 이벤트에서 도와줬을 시
		if (i == 1 || i == 2) {
			printf("동시에 도움만 받을 수 없다 하여 ");
			if (i == 1) {
				printf("전에 받은 식량을 2배로 건네 주었다.\n");
				player.food += 2;
			}
			else if (i == 2) {
				printf("전에 받은 물을 2배로 건네 주었다.\n");
				player.water += 2;
			}
		}
		printf("오늘은 구호단체에서 활동 중이다가 단체 속 아이들을 위하여 황랑한 세상 속 놀잇거리를 찾고자 나왔다고 한다.\n");
		printf("1. 체커\n2. 지도\n3.카드\n4. 베이스 캠프 공사에 돕기 (맨몸)\n");
		while (1) {
			printf("어떤 요청에 답할까?\n-");
			scanf(" %d", &i);
			if (i == 1) {
				printf("아쉽지만 체커를 기부했다.\n");
				player.chess--;
			}
			else if (i == 2) {
				printf("아쉽지만 책를 소모했다.\n");
				player.book--;
			}
			else if (i == 3) {
				printf("아쉽지만 카드를 소모했다.\n");
				player.card--;
			}
			else if (i == 4) {
				printf("줄게 없다고 했으나 몸으로 할 수 있는게 없냐고 물었다.\n");
				printf("이에 쌍둥이는 아직은 초기 단계이지만 베이스 캠프를 짓고 있다고 했다.\n");
				printf("그래서 가족 모두 약 3시간 정도를 공사하는데 보탰다.\n");
				printf("공사를 하느라 물 1개와 식량 2개를 썼다.");
				player.food -= 2;
				player.water--;
			}

			else {
				printf("잘못 입력하셨습니다.\n");
			}
			printf("자신이 구호단체 총괄 쌍둥이라고 했고, 곧 접촉이 있을 거라고 했다.\n");
			eventTurn++;
			break;
		}
	}
	else if (n == 4) {
		// 대규모 캠프 공사에 도움 이벤트
		/*
		지도 이벤트
		도끼 이벤트 (확률적 소모)
		구급약 이벤트 (100% 확률구급상자 소모)
		*/
		printf("마지막으로 저번에 얘기했던 대로 강도가 난무하는 세상에서 사람들을 지킬\n");
		printf("베이스 캠프를 만들려고 한다.\n");
		printf("1. 지도\n2. 도끼\n3. 구급약");
		while (1) {
			printf("어떤것을 줘야할까?\n-");
			scanf(" %d", &i);
			if (i == 1) {
				if (player.map == 0) {
					printf("지도가 부족해 주지 못할 것 같다.\n");
				}
				else {
					printf("지도를 줬다.\n");
					player.map--;
					eventTurn++;
					break;
				}
			}
			else if (i == 2) {
				if (player.ax == 0) {
					printf("도끼가 부족해 주지 못할 것 같다.\n");
				}
				else {
					printf("도끼를 사용했다.\n");
					player.ax--;
					eventTurn++;
					break;
				}
			}
			else if (i == 3) {
				if (player.first_aid_kit == 0) {
					printf("구급약이 부족해 주지 못할 것 같다.\n");
				}
				else {
					printf("구급약을 사용했다.\n");
					player.first_aid_kit--;
					eventTurn++;
					break;
				}
			}
			else {
				printf("잘못 누르셨습니다.");
			}
		}

	}
	else if (n == 5) {
		printf("누군가가 문을 두들겼다.\n");
		while (1) {
			printf("열까? (y or n)\n-");
			scanf(" %c", &c);
			if (c == 'y' || c == 'Y') {
				printf("게임 종료");
				return 0;
			}
			else if (c == 'n' || c == 'N') {
				printf("위험하다.\n");
				eventCancel = 3;
				break;
			}
			else {
				printf("잘못 누르셨습니다.");
			}
		}
	}
}