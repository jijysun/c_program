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
int before = 0; // ���� �̺�Ʈ�� ��ġ�� �� Ȯ�����ִ� ����
int event[3] = { 0 }; // ������ �̺�Ʈ�� ����
int eventTurn = 0; // ������ �̺�Ʈ ���� ����
int eventCancel = 0; // ������ �̺�Ʈ���� �� �ȿ� ��� �ٸ� ������ �̺�Ʈ�� ������ �� �ְԲ�
int badevent = 10;
int goodevent = 10;
int normalevnet = 10;
struct player player;
// 0.����	1.��		2.����	3.å		
// 4.����	5.�浶��	6.����	7.Į	
// 8.��	9.ź��	10.������	11.�ڹ���	
// 12.���޾�	13.ī��	14.ü��	15. ������
// 
// 0. (�����, ���ָ�)  1.(�����, �񸶸�, Ż��)   2.(����, ��ħ, ����) 
// 3. (����?, ��ħ)   4. (�ǰ���, ��ħ, ����)  5. (����, ����)
// https://papago.naver.net/website?locale=ko&source=en&target=ko&url=https%3A%2F%2F60seconds.fandom.com%2Fwiki%2FEvents_(60_Seconds!)%23Feline_Domination

// �ؾ��� ��
// 
// 2. Ž�� = explo ���� �� random�ְ� --�ؼ� Ž�� ǥ��
// 3. Ž�� �� ���� �� �� ��ũ��Ʈ ǥ���ϱ�
// 
// . badEvent - 1��° �����̺�Ʈ���� �ƹ��͵� ���� ���� �� �̺�Ʈ �����ϱ�
// ������ ������ Ž�� �Ⱓ �Ϸ� �ٿ��ִ�?
// �ڹ���� ������ 2���� �ְ� �� ���� �������Լ� ��ƿ �� ���� --�ϴ� ������
// 
//
// Ž�� ������ ������ ��ħ�� Ž�� ��ũ��Ʈ ����


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
	char var;// yes or no ����
	srand(time(NULL));
	printf("60 Seconds!\n");
	printf("������ �����Ϸ��� y, �����Ϸ��� n�� �Է����ּ���\n- ");

	// ���� ���� �Է¹�
	while (1) {
		scanf("%c", &var);
		if (var == 'y' || var == 'Y') {
			system("cls");
			printf("�� ������ �����մϴ�.\n\n");
			Sleep(1000);
			system("cls");
			break;
		}
		else if (var == 'n' || var == 'N') {
			system("cls");
			printf("������ �����մϴ�.\n\n");
			return 0;
		}
		else {
			system("cls");
			printf("�߸� �����̽��ϴ�. \n");
			printf("������ �����Ϸ��� y, �����Ϸ��� n�� �Է����ּ���\n- ");
		}
	}

	// ���� ���� ����
	while (day < 50) {
		// �� ������ ��
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
			// ���� ���� ��¹�
			printf("======\n");
			printf("1. �ķ�: %d\n", player.food);
			printf("2. ��: %d\n", player.water);
			printf("3. ����: %d\n", player.map);
			printf("4. å: %d\n", player.book);
			printf("5. ����: %d\n", player.radio);
			printf("6. �浶��: %d\n", player.gas_mask);
			printf("7. ����: %d\n", player.ax);
			printf("8. Į: %d\n", player.knife);
			printf("9. ��: %d\n", player.gun);
			printf("10. ź��: %d\n", player.ammo);
			printf("11. ������: %d\n", player.flash);
			printf("12. �ڹ���: %d\n", player.lock);
			printf("13. ���޾�: %d\n", player.first_aid_kit);
			printf("14. ������: %d\n", player.pesticide);
			printf("15. ī��: %d\n", player.card);
			printf("16. ü��: %d\n", player.chess);
			printf("======\n");
			Sleep(4000);
			system("cls");
		}

		// �ƹ� ������ ������ + 50 ���� ���޽�
		else if (day == 50) {
			// 50���� ���� ���� �̺�Ʈ �Լ�
			printf("���� ����");
			return 0;
		}

		mainStatus();
		// ���� Ȯ�� �� �̺�Ʈ �Ѿ �� Ȯ��
		// �̺�Ʈ ǥ�� �� �Լ� �ޱ� (�� n�� �� �̺�Ʈ �����)

		itemStatus();
		printf("\n");
		
		printf("������ �̾߱�: ");
		mainControl();
		printf("\n-----------------------------------------\n\n");

		// Ž�� �̺�Ʈ ��
		exploration();
		
		

		printf("�ð��� ���� ������ ���� �޷����� �ִ�.\n���� ���� ���� ���� �߱� (y or n)\n- ");

		// ���� ȸ���� ����?
		while (1) {

			scanf(" %c", &var);
			if (var == 'y' || var == 'Y') {
				system("cls");
				printf("���� ���� ������, ���� ���� ���Ͽ� �����ζ� ���� û�غ��ϴ�.\n");
				if (day == 9) {
					printf("�ٱ� ��Ȳ�� ���� ���Ϻ��� Ž�縦 �� �� ���� �� ���ٴ� ������ ���.\n");
					Sleep(2000);
				}
				if (day == 24) {
					printf("���Ϻ��� ���ܿ� ��Ŀ ���� ��� �ٱ��� �����ϰ� ������ Ȳ���� ������ �� �ݰ��� ���� �� ����.\n");
					Sleep(2000);
				}
				printf("�ε���.");
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
				printf("������ �����ϰ��� ��� ���� �ڷ� �Ѵ�.\n");
				printf("(���� �� �� ����ؼ� �����ִ� �Լ�)\n");
				printf("���� ���� ���� ���� �߱� (y or n))\n- ");
			}
			else {
				system("cls");
				printf("\n�߸� �����̽��ϴ�. \n");
				printf("���� ���� ���� ���� �߱� (y or n)\n- ");
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

	printf("��ȭ�ο� �ָ��� ������ TV�� ���� ����� ������Ȳ�̶�� ������ �ڸ��� ���鼭\n");

	printf("���ÿ� �������� ��ī�ο� �̻��� �Ҹ��� �Բ� �Ͱ� ���� ������ ���̷��� ��� �Ǿ����ϴ�.\n");

	printf("�� �������� �ӿ��� [������Ȳ] �̶�� �ܾ�� �Ӹ��� ���εǾ���,  \n");

	printf("�� �Ӹ� ���� ����� �� ũ�⸸�� �̻����� �������� �����ϰ� �Ǿ����ϴ�.\n");

	printf("������ �غ��� ���Ϻ�Ŀ�� ���� ì�ܾ� �ڴٴ� ������\n");

	printf("�� �տ� ���̴�, ����� �� ��� ���� ������ϴ�. \n\n\n");

	printf("� �͵��� ì��ðڽ��ϱ�? (�ִ� 4��)\n");

	printf("=========================\n");
	printf("1. �߰� ���� (�ķ��� ��)\t2. ������ å\t3. ����\n");
	printf("4. �浶��\t5. ������ Į\t6. �Ѱ� ź��\n");
	printf("7. ������� �ڹ���\t8. ���޾�� ������\t9. ī�塤ü��\n");
	printf("=========================\n- ");

	int i = 0, s[4] = { 0 };
	// �ߺ� ������ ������ ��� ���� ó��
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

	// �Է� �˻繮
	for (i = 0; i < 4; i++) {
		for (int j = i + 1; j < 4; j++) {
			if (s[i] == s[j]) {
				printf("\n�ߺ� �Է��ϼ̽��ϴ�. �ٽ� �Է����ּ���\n- ");
				goto again;
			}
		}
		if (s[i] > 9) {
			printf("\n�߸� �Է��ϼ̽��ϴ�. �ٽ� �Է����ּ���\n- ");
			goto again;
		}
	}i = 0;

	while (i < 4) {
		switch (s[i]) {
		case 1:
			player.food += 2; // �ķ�, ��
			player.water += 2;
			break;
		case 2:
			player.map += 1; // ������ å
			player.book += 1;
			break;
		case 3:
			player.radio += 1; // ����
			break;
		case 4:
			player.gas_mask += 1; // �浶��
			break;
		case 5:
			player.ax += 1; // ����, Į
			player.knife += 1;
			break;
		case 6:
			player.gun += 1; // �� ź��
			player.ammo += 1;
			break;
		case 7:
			player.lock += 2; // ������, �ڹ���
			player.flash += 1;
			break;
		case 8:
			player.first_aid_kit += 1; // ���޾�, ������
			player.pesticide += 1;
			break;
		case 9:
			player.card += 1; // ī�� ü��
			player.chess += 1;
			break;
		}
		i++;
	}

	system("cls");
	printf("�׷��� ���θ� ����� �ܿ� �Ƴ��� �Ƶ�, ���� ��Ŀ�� ���ǽ�Ű��\n");

	printf("������� �� ���ǵ��� ������, ��Ŀ�� ���� ���� ��Ŀ�� ��ġ�� �������ν� ���ǿ� �����߽��ϴ�.\n");

	printf("������ ��Ŀ�� �ִ� ���� Ž���Ⱑ ������� ��Ȱ�\n");

	printf("�⳪�� ������ �� ���� �ܷο� ��ҿ��� ������ �Ѵٴ� ������ �� ���� įį�����ϴ�....\n");

}

void exploration() {
	int random = rand() % 15;

	if (day <= 3) {
		printf("���� ��Ŀ ���� �����ٴ� ������ �Ѵٴ� �� ��ü�� ��ģ ���̴�.\n");
		return;
	}

	// Ž�� �����
	if (exploExit == 1) {
		exploExit =0;
		beforeExplo = explo;

		switch (explo) {
			case 1:
				printf("���� �ƺ��� %d���� ��� �賭�ߴ� Ž�縦 ��ġ�� ���ƿԴ�\n", exploday);
				player.dad[3] = -5;
				break;
			case 2:
				printf("���� ������ %d���� ��� �賭�ߴ� Ž�縦 ��ġ�� ���ƿԴ�\n", exploday);
				player.mom[3] = -5;
				break;
			case 3:
				printf("���� �Ƶ��� %d���� ��� �賭�ߴ� Ž�縦 ��ġ�� ���ƿԴ�\n", exploday);
				player.son[3] = -5;
				break;
			case 4:
				printf("���� ���� %d���� ��� �賭�ߴ� Ž�縦 ��ġ�� ���ƿԴ�\n", exploday);
				player.dau[3] = -5;
				break;
			}
		// Ž�� ���ٿ� ��ҿ� ���� ��Ʈ
		switch (random) {
			case 0:
				printf("�б� �湮\n");
				break;
			case 1:
				printf("������ �湮\n");
				break;
			case 2:
				printf("���ð� �湮\n");
				break;
			case 3:
				printf("���� �湮\n");
				break;
			case 4:
				printf("��Ʈ �湮\n");
				break;
			case 5:
				printf("�Ĵ簡 �湮\n");
				break;
			case 6:
				printf("����ö �湮\n");
				break;
			case 7:
				printf("������ �湮\n");
				break;
			case 8:
				printf("����Ʈ �湮\n");
				break;
			case 9:
				printf("������ ��� �湮\n");
				break;
			}

		// ���� �������� ���� ������ Ȯ�� ��
		// �⺻ �ķ�, �� 1������ ����ٱ�?
		if (exploMap==1) {
			switch (random) {
			case 0: // ����, å, ����, ������, ī��
				printf("�б�\n");
				break;
			case 1: // �ķ�, ��, ����, �ڹ���
				printf("������ �̾��� ��\n");
				break;
			case 2: // �ķ�, ��, ��, ������, ī��
				printf("���ð�\n");
				break;
			case 3: // ���޾�, ������, Į, ������
				printf("����\n");
				break;
			case 4: // �ķ�, ��, �뷮�� �ķ� or ��
				printf("��Ʈ\n");
				break;
			case 5: //�ķ�, ��, �뷮�� �ķ� or ��
				printf("�Ĵ簡\n");
				break;
			case 6: // �浶��, ������, ���޾�
				printf("����ö\n");
				break;
			case 7: // ����, å, �ڹ���, ü��
				printf("������\n");
				break;
			case 8: // �ķ�, ��, ü��
				printf("����Ʈ\n");
				break;
			case 9: // ��, ź��, Į, ����, �ڹ��� �� 1, 
				printf("�����\n");
				break;
			case 10: // �ķ�, ��, 
				printf("ī��\n");
				break;
			case 11:
				printf("������ ���\n");
				break;
			case 12:
				printf("������ ���\n");
				break;
			case 13:
				printf("������ ���\n");
				break;
			case 14:
				printf("������ ���\n");
				break;
			}

		}
		// ���� ���������� ���� ������ Ȯ�� �ٿ�
		else {
			switch (random) {
			case 0:
				printf("�б�\n");
				break;
			case 1:
				printf("������ �̾��� ��\n");
				break;
			case 2:
				printf("���ð�\n");
				break;
			case 3:
				printf("����\n");
				break;
			case 4:
				printf("��Ʈ\n");
				break;
			case 5:
				printf("�Ĵ簡\n");
				break;
			case 6:
				printf("����ö\n");
				break;
			case 7:
				printf("������\n");
				break;
			case 8:
				printf("����Ʈ\n");
				break;
			case 9:
				printf("������ ���\n");
				break;
			case 10:
				printf("������ ���\n");
				break;
			case 11:
				printf("������ ���\n");
				break;
			case 12:
				printf("������ ���\n");
				break;
			case 13:
				printf("������ ���\n");
				break;
			case 14:
				printf("������ ���\n");
				break;
			}
		}
		printf("������ Ž�縦 �ٳ�ͼ� ���� ��� ������ �͵��� ����.\n");
		explo = 0;
		return;
	}
	
	// Ž�� ����
	if (exploTime == 0) {
		if ( day >= 4 || day < 10 ) {
			// 10���� �������� ���� �̺�Ʈ
			printf("������ ����ó�� ������ ���ݰ� ���� ȯ�濡�� Ž�縦 �����ٴ� ������ �ʹ� ����������\n");
			printf("�� ���� ������ ������ ����� �� �� ������? ��� ������ ��̷ο�����.\n");
			printf("1. �ƺ�\t"); printf("2. ����\t"); printf("3. �Ƶ�\t"); printf("4. ��\t"); printf("5. ������ �ʴ´�.\n");
			

			while (1) {
				printf("������ Ž�縦 ���� ������?\n- ");
				scanf("%d", &explo);
				if (explo == 1) {
					if (player.dad[2] < 0 || player.dad[3] < 0 || player.dad[4] < 0 || player.dad[5] < 0) {
						printf("���� ������ �ƺ��� Ž��� �������� ���� ������� ���̴�.\n");
					}
					else {
						printf("\n�ƺ��� �����԰� ������ ������ �ռ���� Ž�翡 ������� �ߴ�. \n");
						break;
					}
				}
				else if (explo == 2) {
					if (player.mom[2] < 0 || player.mom[3] < 0 || player.mom[4] < 0 || player.mom[5] < 0) {
						printf("���� ������ ������ Ž��� �������� ���� ������� ���̴�.\n");
					}
					else {
						printf("������ �����ϰ� å�Ӱ��� �ռ���� Ž�翡 ������� �ߴ�. \n");
						break;
					}
				}
				else if (explo == 3) {
					if (player.son[2] < 0 || player.son[3] < 0 || player.son[4] < 0 || player.son[5] < 0) {
						printf("���� ������ �Ƶ��� Ž��� �������� ���� ������� ���̴�.\n");
					}
					else {
						printf("�Ƶ��� �ڽŰ��� ������ ���¿�� Ž�翡 ������� �ߴ�. \n");
						break;
					}
				}
				else if (explo == 4) {
					if (player.dau[2] < 0 || player.dau[3] < 0 || player.dau[4] < 0 || player.dau[5] < 0) {
						printf("���� ������ ���� Ž��� �������� ���� ������� ���̴�.\n");
					}
					else {
						printf("���� �б�� ���谨�� �ռ���� Ž�翡 ������� �ߴ�. \n");
						break;
					}
				}
				else if (explo == 5) {
					printf("���� ����� ���� �������� Ž�縦 ������ �ұ�?\n\n");
					explo = 0;
					break;
				}
				else {
					printf("\n�߸� �Է��ϼ̽��ϴ�.\n");
				}
			}

		}
		else if (day >= 10 || day <= 24) {
			printf("������ ���ư�, �������� ���İ� ������ ����������, ��Ŀ�� ���� �������� ��� ���� �����̴�.\n");
			// ĳ���� �迭 ���ڸ����� explo �־ Ž�� �����ϱ�
			printf("1. �ƺ�\t"); printf("2. ����\t"); printf("3. �Ƶ�\t"); printf("4. ��\t"); printf("5. ������ �ʴ´�.\n- ");


			while (1) {
				printf("������ Ž�縦 ���� ������?\n- ");
				scanf("%d", &explo);
				if (explo == 1) {
					if (player.dad[2] < 0 || player.dad[3] < 0 || player.dad[4] < 0 || player.dad[5] < 0) {
						printf("���� ������ �ƺ��� Ž��� �������� ���� ������� ���̴�.\n");
					}
					else {
						printf("\n�ƺ��� �����԰� ������ ������ �ռ���� Ž�翡 ������� �ߴ�. \n");
						break;
					}
				}
				else if (explo == 2) {
					if (player.mom[2] < 0 || player.mom[3] < 0 || player.mom[4] < 0 || player.mom[5] < 0) {
						printf("���� ������ ������ Ž��� �������� ���� ������� ���̴�.\n");
					}
					else {
						printf("������ �����ϰ� å�Ӱ��� �ռ���� Ž�翡 ������� �ߴ�. \n");
						break;
					}
				}
				else if (explo == 3) {
					if (player.son[2] < 0 || player.son[3] < 0 || player.son[4] < 0 || player.son[5] < 0) {
						printf("���� ������ �Ƶ��� Ž��� �������� ���� ������� ���̴�.\n");
					}
					else {
						printf("�Ƶ��� �ڽŰ��� ������ ���¿�� Ž�翡 ������� �ߴ�. \n");
						break;
					}
				}
				else if (explo == 4) {
					if (player.dau[2] < 0 || player.dau[3] < 0 || player.dau[4] < 0 || player.dau[5] < 0) {
						printf("���� ������ ���� Ž��� �������� ���� ������� ���̴�.\n");
					}
					else {
						printf("���� �б�� ���谨�� �ռ���� Ž�翡 ������� �ߴ�. \n");
						break;
					}
				}
				else if (explo == 5) {
					printf("���� ����� ���� �������� Ž�縦 ������ �ұ�?\n\n");
					explo = 0;
					break;
				}
				else {
					printf("\n�߸� �Է��ϼ̽��ϴ�.\n");
				}
			}
		}
		else {
			printf("���ð��� ȭâ�� ������ ����, ������ �ذ��� ���߱���, \n������ ���شٴϸ� ������ �־�ٴ� ���� Ž�簡 �� ���̴�.\n");
			printf("1. �ƺ�\t"); printf("2. ����\t"); printf("3. �Ƶ�\t"); printf("4. ��\t"); printf("5. ������ �ʴ´�.\n- ");
			while (1) {
				printf("������ Ž�縦 ���� ������?\n- ");
				scanf("%d", &explo);
				if (explo == 1) {
					if (player.dad[2] < 0 || player.dad[3] < 0 || player.dad[4] < 0 || player.dad[5] < 0) {
						printf("���� ������ �ƺ��� Ž��� �������� ���� ������� ���̴�.\n");
					}
					else {
						printf("\n�ƺ��� �����԰� ������ ������ �ռ���� Ž�翡 ������� �ߴ�. \n");
						break;
					}
				}
				else if (explo == 2) {
					if (player.mom[2] < 0 || player.mom[3] < 0 || player.mom[4] < 0 || player.mom[5] < 0) {
						printf("���� ������ ������ Ž��� �������� ���� ������� ���̴�.\n");
					}
					else {
						printf("������ �����ϰ� å�Ӱ��� �ռ���� Ž�翡 ������� �ߴ�. \n");
						break;
					}
				}
				else if (explo == 3) {
					if (player.son[2] < 0 || player.son[3] < 0 || player.son[4] < 0 || player.son[5] < 0) {
						printf("���� ������ �Ƶ��� Ž��� �������� ���� ������� ���̴�.\n");
					}
					else {
						printf("�Ƶ��� �ڽŰ��� ������ ���¿�� Ž�翡 ������� �ߴ�. \n");
						break;
					}
				}
				else if (explo == 4) {
					if (player.dau[2] < 0 || player.dau[3] < 0 || player.dau[4] < 0 || player.dau[5] < 0) {
						printf("���� ������ ���� Ž��� �������� ���� ������� ���̴�.\n");
					}
					else {
						printf("���� �б�� ���谨�� �ռ���� Ž�翡 ������� �ߴ�. \n");
						break;
					}
				}
				else if (explo == 5) {
					printf("���� ����� ���� �������� Ž�縦 ������ �ұ�?\n\n");
					explo = 0;
					break;
				}
				else {
					printf("\n�߸� �Է��ϼ̽��ϴ�.\n");
				}
			}
		}

		// Ž�� ���� ���� ������ �ִ��� 
		// ������ �۰�Ȯ�� ��, ���� ��
		if (explo) {
			if (player.map >= 1) {
				printf("(������ �����ϰ� �־�, Ž�� �� ������ ���� Ȯ���� �������ϴ�.)\n");
				exploMap = 1;
			}
			else {
				printf("(������ �����ϰ� ���� �ʾ�, Ž�� �� ������ ���� Ȯ���� �������ϴ�.)\n");
				exploMap = 0;
			}
		}
		

		// ���� Ž�� �Ⱓ
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
		printf("������ ");
		switch (explo) {
		case 1:
			printf("�ƺ��� Ž�翡 �����־� ���� ���� �ʿ�� ���� �� ����.\n");
			break;
		case 2:
			printf("������ Ž�翡 �����־� ���� ���� �ʿ�� ���� �� ����.\n");
			break;
		case 3:
			printf("�Ƶ��� Ž�翡 �����־� ���� ���� �ʿ�� ���� �� ����.\n");
			break;
		case 4:
			printf("���� Ž�翡 �����־� ���� ���� �ʿ�� ���� �� ����.\n");
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
	// DAY ����ϴ� �Ŷ� ĳ���� ���� ����ϴ� �Ŷ� ��ĥ��?
	printf("\t\t*********\n");
	printf("\t\t* Day %d *\n", day);
	printf("\t\t*********\n\n\n\n");

	printf("[������ ����]\n");
	// ������ ���� ����ϴ� �� ���� �Լ� ���� ������ switch (explo) {case1: (�ƺ� �� ������ �����Լ�)}
	switch (explo)
	{
	case 0:
		printf("\n����������������������\n");
		dad_status();
		mom_status();
		son_status();
		dau_status();
		break;
	case 1:
		printf("�ƺ�: Ž��");
		printf("\n����������������������\n");
		mom_status();
		son_status();
		dau_status();
		break;
	case 2:
		dad_status();
		printf("����: Ž��");
		printf("\n����������������������\n");
		son_status();
		dau_status();
		break;
	case 3:
		dad_status();
		mom_status();
		printf("�Ƶ�: Ž��");
		printf("\n����������������������\n");
		dau_status();
		break;
	case 4:
		dad_status();
		mom_status();
		son_status();
		printf("��: Ž��");
		printf("\n����������������������\n");
		break;
	}
	printf("\n");
}

void itemStatus() {
	printf("���� ����\n========================\n");
	printf("�ķ�: %d��   ", player.food);
	printf("��: %d��   ", player.water);
	printf("����: %d��   ", player.map);
	printf("å: %d��   ", player.book);
	printf("����: %d��\n", player.radio);
	printf("�浶��: %d��   ", player.gas_mask);
	printf("����: %d��   ", player.ax);
	printf("Į: %d��   ", player.knife);
	printf("��: %d��   ", player.gun);
	printf("ź��: %d��\n", player.ammo);
	printf("������: %d��   ", player.flash);
	printf("�ڹ���: %d��   ", player.lock);
	printf("���޾�: %d��   ", player.first_aid_kit);
	printf("ī��: %d��   ", player.card);
	printf("ü��: %d��    ", player.chess);
	printf("������: %d��", player.pesticide);
	printf("\n========================\n");
}

void dad_status() {
	printf("�ƺ�: ");
	if (player.dad[0] > 0 && player.dad[1] > 0) {
		printf("�����. ");
	}
	else {
		if (player.dad[0] == 0) {
			printf("�����. ");
		}
		else if (player.dad[0] = -2) {
			printf("���ָ�. ");
		}
		if (player.dad[1] == 0) {
			printf("�񸶸�. ");
		}
		else if (player.dad[1] == -1) {
			printf("Ż�� ");
		}
	}

	if (player.dad[2] == -1) {
		printf("��ħ ");
	}
	else if (player.dad[2] == -2) {
		printf("���� ");
	}


	if (player.dad[3] <0) {
		printf("��ħ ");
	}

	if (player.dad[4] == -1) {
		printf("��ħ. ");
	}
	else if (player.dad[4] == -2) {
		printf("����. ");
	}

	if (player.dad[5] == -1) {
		printf("����. ");
	}
	printf("\n����������������������\n");
}
void mom_status() {
	printf("����: ");
	if (player.mom[0] > 0 && player.mom[1] > 0) {
		printf("�����. ");
	}
	else {
		if (player.mom[0] == 0) {
			printf("�����. ");
		}
		else if (player.mom[0] = -2) {
			printf("���ָ�. ");
		}
		if (player.mom[1] == 0) {
			printf("�񸶸�. ");
		}
		else if (player.mom[1] == -1) {
			printf("Ż�� ");
		}
	}
	 

	if (player.mom[2] == -1) {
		printf("��ħ ");
	}
	else if (player.mom[2] == -2) {
		printf("���� ");
	}

	if (player.mom[3] <0) {
		printf("��ħ ");
	}

	if (player.mom[4] == -1) {
		printf("��ħ. ");
	}
	else if (player.mom[4] == -2) {
		printf("����. ");
	}

	if (player.mom[5] == -1) {
		printf("����.");
	}
	printf("\n����������������������\n");
}
void son_status() {
	printf("�Ƶ�: ");
	if (player.son[0] > 0 && player.son[1] > 0) {
		printf("�����. ");
	}
	else {
		if (player.son[0] == 0) {
			printf("�����. ");
		}
		else if (player.son[0] = -2) {
			printf("���ָ�. ");
		}
		if (player.son[1] == 0) {
			printf("�񸶸�. ");
		}
		else if (player.son[1] == -1) {
			printf("Ż�� ");
		}
	}

	if (player.son[2] == -1) {
		printf("��ħ ");
	}
	else if (player.son[2] == -2) {
		printf("���� ");
	}

	if (player.son[3] <0) {
		printf("��ħ ");
	}

	if (player.mom[4] == -1) {
		printf("��ħ. ");
	}
	else if (player.son[4] == -2) {
		printf("����. ");
	}

	if (player.son[5] == -1) {
		printf("����. ");
	}
	printf("\n����������������������\n");
}
void dau_status() {
	printf("��: ");
	if (player.dau[0] > 0 && player.dau[1] > 0) {
		printf("�����. ");
	}
	else {
		if (player.dau[0] == 0) {
			printf("�����. ");
		}
		else if (player.dau[0] = -2) {
			printf("���ָ�. ");
		}
		if (player.dau[1] == 0) {
			printf("�񸶸�. ");
		}
		else if (player.dau[1] == -1) {
			printf("Ż�� ");
		}
	}

	if (player.dau[2] == -1) {
		printf("��ħ ");
	}
	else if (player.dau[2] == -2) {
		printf("���� ");
	}

	 if (player.dau[3] < 0) {
		printf("��ħ ");
	}

	if (player.dau[4] == -1) {
		printf("��ħ .");
	}
	else if (player.dau[4] == -2) {
		printf("����. ");
	}

	if (player.dau[5] == -1) {
		printf("����. ");
	}
	printf("\n����������������������\n");
}

void mainControl() {
	int random = 0;
	//printf("input mainControl\nrandom = %d\n", random);
	//������ �̺�Ʈ��
	
	if (day < 4) {
		printf("�ٱ� ������ ������ ȰȰ ��Ÿ�� �ִ�.\n");
		earlyEvent();
		return;
	}

	if (random == 0) {
		// ó�� ������ �̺�Ʈ ����
		if (event[0] == 0 && event[1] == 0 && event[2] == 0) {
			int random = randomSystem(3);
			switch (random) {
			case 0:
				printf("ù ���δ뿣�� �̺�Ʈ ����: \n");
				militaryEvent();
				event[0]++;
				break;
			case 1:
				printf("ù ������� �̺�Ʈ ����: \n");
				agentEvent();
				event[1]++;
				break;
			case 2:
				printf("ù �ֵ��̿��� �̺�Ʈ ����: \n");
				twinEvent();
				event[2]++;
				break;
			}
		}

		// �ƴ϶�� eventCancel ���ο� ���� ������ �̺�Ʈ ����
		else {
			if (eventCancel != 0) {
				int random2 = randomSystem(2);
				printf("\neventCancel: %d\nrandom2: %d\n", eventCancel, random2);
				eventTurn = 0;
				if (eventCancel == 1) {
					event[0] = 0;
					if (random2 == 0) {
						event[1] = 1;
						printf("���δ� ���� ���� ����, ���� ������: ���\n");
						agentEvent();
					}
					else if (random2 == 1) {
						event[2] = 1;
						printf("���δ� ���� ���� ����, ���� ������: �ֵ���\n");
						twinEvent();
					}
				}

				else if (eventCancel == 2) {
					event[1] = 0;
					if (random2 == 0) {
						event[0] = 1;
						printf("��� ���� ���� ����, ���� ������: ���δ�\n");
						militaryEvent();
					}
					else if (random2 == 1) {
						event[2] = 1;
						printf("��� ���� ���� ����, ���� ������: �ֵ���\n");
						twinEvent();
						
					}
				}

				else if (eventCancel == 3) {
					event[2] = 0;
					if (random2 == 0) {
						event[0] = 1;
						printf("�ֵ��� ���� ���� ����, ���� ������: ���δ�\n");
						militaryEvent();
					}
					else if (random2 == 1) {
						event[1] = 1;
						printf("�ֵ��� ���� ���� ����, ���� ������: ���\n");
						agentEvent();
					}
				}
			}

			else  {
				if (event[0] == 1) {
					printf("���δ뿣�� �̺�Ʈ ����: \n");
					militaryEvent();
				}
				else if (event[1] == 1) {
					printf("������� �̺�Ʈ ����: \n");
					agentEvent();
				}
				else if (event[2] == 1) {
					printf("�ֵ��̿��� �̺�Ʈ ����: \n");
					twinEvent();
				}
			}
		}
	}
	//��� �̺�Ʈ��
	else if (random == 1) {
		badEvent();
	}

	//�븻 �̺�Ʈ��
	else if (random == 2) {
		normalEvent();
	}

	//�� �̺�Ʈ��
	else if (random == 3) {
		goodEvent();
	}
	
}

void earlyEvent() {
	// 4���� �̸��� �� ����� ��ũ��Ʈ
	// ���� �� ����� �̺�Ʈ�� �ߺ����� ���� �ʰԲ�
	// 
	// 1. ���� ��Ŀ ������ ������ �� Ȯ��?
	// 2. �ƹ� �� ���� ������ �� (�̰� �� Ȯ�� 2���)
	// 3. ��Ŀ ������ ������ ���𰡸� �߰� ()
	// 4. ���ϰ� ���ϴ��� �λ� (���ֵ� ok or �λ����� ����)
	// 5. 

	int random = rand() % 8;
	// ���� �̺�Ʈ
	if (random >= 0 && random <= 5) {
		previous:
		printf("���� ��Ŀ���� ������ �� �ͼ��� �ʾҰ�, ħ�����θ� �� �ð��� �������ȴ�.\n");
		return;
	}
	else {
		// ���� ��Ŀ ������ ������ �̺�Ʈ
		if (random == 6) {
			int i = 0;
			if (before == 1) {
				before = 0;
				goto previous;
			}

			printf("�츮�� ��Ŀ�� �µ��� ������ ������ ���� ������, �̳� Ÿ�� ���� ���� �ñ� �����ߴ�.\n");
			printf("��Ŀ ���� â������ ���� ���� �̹� �츰 �ҿ� �۽��� ���̴�!\n");
			printf("1. ���� ���� ��ȭ�Ѵ�. \n2. ��Ŀ�� �������� ������ ��ƾ��.\n");
			while (1) {
				printf("��� �ؾ� �ұ�?\n- ");
				scanf(" %d", &i);
				if (i == 1) {
					if (player.water == 0) {
						printf("\n�� ���� �����ϴ�.\n");
					}
					else {
						printf("\n�� �� 2���� �̿��� ��Ŀ �ֺ��� ���� ����.\n");
						printf("���� ���� �ʾҴٸ� �츰 �뱸�̰� �Ǿ��� ���̴�.\n");
						player.water -= 2;
						before = 1;
						break;
					}
				}
				else if (i == 2) {
					int random2 = rand() % 6;
					int random3 = rand() % 4;
					if (random2 == 0) {
						printf("\n�� ȭ��δ� ��ġ�� �ʾ����� ���Ⱑ ���Ź��� ſ��");
						if (random3 == 0) {
							player.dad[4]--;
							printf("�ƺ��� ���ƴ�.\n");
						}
						else if (random == 1) {
							player.mom[4]--;
							printf("������ ���ƴ�.\n");
						}
						else if (random == 2) {
							player.son[4]--;
							printf("�Ƶ��� ���ƴ�.\n");
						}
						else if (random == 3) {
							player.dau[4]--;
							printf("���� ���ƴ�.\n");
						}
						before = 1;
						break;
					}
					else {
						printf("\n�� �������� �̹� ���� ȭ������ �������� ��ƾ ��Ŀ�̴� ��� ���� ���̴�.\n");
						before = 1;
						break;
					}
				}

				else {
					printf("\n�߸� �����̽��ϴ�.\n");
				}
				
			}
		}

		// ���� �̺�Ʈ
		else if (random == 7) {
			char c;
			if (before == 2) {
				before = 0;
				goto previous;
			}
			printf("������ ��������, ��Ŀ ���� ħ�� ������ ���� ���𰡰� �ִ� ���� �߰��ߴ�.\n");
			while (1) {
				printf("Ȯ���غ���? (y or n)\n- ");
				scanf(" %c", &c);
				if (c == 'y' || c == 'Y') {
					if (player.food < player.water) {
						printf("\n�� �װ����� �丶�� ���� 1���� �����ٴϰ� �־���.\n");
						printf("������ �߿����� �ٽ� ���ݰ� �Ǿ���.\n");
						player.food++;
						before = 2;
						break;
					}
					else {
						printf("\n�� �װ����� ���� 1���� �����ٴϰ� �־���.\n");
						printf("������ �߿����� �ٽ� ���ݰ� �Ǿ���.\n");
						player.water++;
						before = 2;
						break;
					}
				}
				else if (c == 'n' || c == 'N') {
					printf("\n�� �������� �̻��� ��Ŀ�� ��ġ�� ���� ������� ���̾���.\n");
					before = 2;
					break;
				}
				else {
					printf("\n�߸� �����̽��ϴ�.\n");
				}
			}
		}
	}
	

}

void badEvent() {
	int random = rand() % 10;
	int i = 0;

	// �̺�Ʈ �ߺ��߻� ������
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

	// ���� ħ���̺�Ʈ
	if (random == 0) {
		printf("bad 1. ���� �̺�Ʈ\n");
		printf("�������� ħ���� �Ϸ��� ��Ŀ�� ���� �μ����� �Ѵ�. ��Ե� ���ƾ� �Ѵ�!\n");
		printf("---------------------------\n");
		printf("1. �ڹ���� ��Ŀ�� ��ٴ�.\n");
		printf("2. ������ �����Ѵ�.\n");
		printf("3. ������ �����Ѵ�.\n");
		printf("4. Į�� �����Ѵ�.\n");
		printf("5. �ƹ��͵� ���� ���ߺ���.\n");
		if (player.dog == 1) {
			printf("6. �������� �Բ� ���´�.\n");
		}
		printf("----------------------------\n");
		while (1) {
			printf("� �͵�� ������?\n- ");
			scanf(" %d", &i);
			if (i == 1) {
				if (player.lock == 0) {
					printf("\n�� �ڹ��谡 �����ϴ�.\n");
				}
				else {
					printf("\n�� �ڹ���� ���� ��� ���� ��Ե� ħ���غ����� ������ �����ϸ� �����ϰ� ���´�.\n");
					player.lock--;
					break;
				}
			}
			else if (i == 2) {
				if (player.gun == 0) {
					printf("\n�� ���� �����ϴ�.\n");
				}
				else {
					printf("\n�� �Ѹ�ŭ ����ϰ� ���� ģ���� ���� ���̴�. �������� �������� ������� �ƴ�.\n");
					break;
				}
			}
			else if (i == 3) {
				if (player.ax == 0) {
					printf("\n�� ������ �����ϴ�.\n");
				}
				else {
					printf("\n�� ���� ��Ŀ ������ �����ٰ��� ������ �뼭���� ���� ���̴�. ������ �ϴ����� ���߰� �޾Ƴ���.\n");
					break;
				}
			}
			else if (i == 4) {
				if (player.knife == 0) {
					printf("\n�� Į�� �����ϴ�.\n");
				}
				else {
					printf("\n�� ���� ������ �����ٰ��� ��� ȸ�� �� ���̴�.\n");
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
				printf("������ ���� ���ߴ�. ���� �������� �־����� �ο��� ���̷� ���ϱ⸸ �ߴ�.\n");
				printf("���� �̻��� ���̰Բ� �����鼭 �ķ�, ���� �����, ");
				int random2 = randomSystem(4);
				switch (random2) {
				case 0:
					printf("������ �μ̴�.\n");
					player.radio--;
					break;
				case 1:
					printf("�������� �μ̴�.\n");
					player.flash--;
					break;
				case 2:
					printf("������ ������.\n");
					player.map--;
					break;
				case 3:
					printf("�������� ��������.\n");
					player.pesticide--;
					break;
				}
				break;
			}
			else {
				printf("�߸� �����̽��ϴ�.");
			}
		}
		badevent = 0;
	}
	else if (random == 1) {
		printf("�̱��� �̺�Ʈ (random =1)\n");
		badevent = 1;
	}
	else if (random == 2) {
		printf("�̱��� �̺�Ʈ (random =2)\n");
		badevent = 2;
	}
	else if (random == 3) {
		printf("�̱��� �̺�Ʈ (random = 3)\n");
		badevent = 3;

	}
	else if (random == 4) {
		printf("�̱��� �̺�Ʈ (random = 4)\n");
		badevent = 4;
	}
	else if (random == 5) {
		printf("�̱��� �̺�Ʈ (random = 5)\n");
		badevent = 5;
	}
	else if (random == 6) {
		printf("�̱��� �̺�Ʈ (random = 6\n");
		badevent = 6;
	}
	else if (random == 7) {
		printf("�̱��� �̺�Ʈ (random = 7)\n");
		badevent = 7;
	}
	else if (random == 8) {
		printf("�̱��� �̺�Ʈ (random = 8)\n");
		badevent = 8;
	}
}

void normalEvent() {
	int i = 0, randomNum;
	char c;
	int random = rand() % 10;

	// �̺�Ʈ �ߺ��߻� ������
	while (1) {
		printf("random=%d, normalevent=%d\n", random, normalevnet);
		if (normalevnet == random) {
			random = rand() % 10;
		}
		else {
			break;
		}
	}

	// ��ģ ������ ���� �̺�Ʈ
	if (random == 0) {
		printf("�������� ������ ���� �����ϴ�. ���� ��ġ�� ���ؾ� �� �� ����.\n");
		printf("1. ������ �̿��غ���.\n2. �ƹ��͵� ���� �ʴ´�.\n");
		while (1) {
			printf("� ���� �ؾ� �ұ�?\n- ");
			scanf(" %d", &i);
			if (i == 1) {
				if (player.radio == 0) {
					printf("\n�� ������ ����.\n");
				}
				else {
					printf("\n�� �������� ������ ���ļ��� ã�ٰ� ������ ��� �Ǿ���, �Ӹ��� ���� �������� ����� �����.\n");
					randomNum = randomSystem(6);
					if (random == 1) {
						player.radio -= 1;
						printf("+ ������ �������ϰ� ����� �� ����. ������ ���峵��\n");
					}
					break;
				}
			}
			else if (i == 2) {
				int random = rand() % 6;
				if (random == 0) {
					int random2 = randomSystem(4);
					printf("���� �ӿ��� �������̸� �ϴٰ� �ᱹ");
					if (random2 == 0) {
						player.dad[2] -= 1;
						printf("�ƺ��� ������ ������ ���� ���Ĺ��ȴ�.\n");
					}
					else if (random2 == 1) {
						player.mom[2] -= 1;
						printf("������ ������ ������ ���� ���Ĺ��ȴ�.\n");
					}
					else if (random2 == 1) {
						player.son[2] -= 1;
						printf("�Ƶ��� ������ ������ ���� ���Ĺ��ȴ�.\n");
					}
					else if (random2 == 1) {
						player.dau[2] -= 1;
						printf("���� ������ ������ ���� ���Ĺ��ȴ�.\n");
					}
					break;
				}
				else{
					printf("\n�� �� �����ϰ� ������ �����⸦ ���� �����ұ�?��� ����� ���.\n");
					break;
				}
			}
			
			else {
				printf("\n�߸� �����̽��ϴ�.\n");
			}
		}
		normalevnet = 0;
	}

	// ���� �̺�Ʈ
	else if (random == 1) {
		printf("1. ���� �̺�Ʈ\n");
		printf("������ �ڿ��� ���ڸ� ���Ѿ� ������ �ڵ鿡�� �������شٴ� ������� ������� ��Ŀ�� ã�ƿԴ�.\n");
		while (1) {
			printf("�����ٱ�? (y or n)\n- ");
			scanf(" %c", &c);
			if (c == 'y' || c == 'Y') {
				if (player.food > 3 && player.water > 3) {
					printf("���ڸ� ������ �ֱ⿣ �츮 ������ �ʹ� ���ٸ� ������ �ķ��� ���� 1���� �����.\n");
					player.food--; player.water--;
					break;
				}
				else {
					printf("�׵��� �� �״�� �ķ��� �� 1���� ������ְ� �������ȴ�.\n");
					player.food++; player.water++;
					break;
				}
			}
			else if (c == 'n' || c == 'N') {
				printf("���� ������ ����� �湮�� �ʿ�� ���� �� ����\n");
				break;
			}
			else {
				printf("�߸� �����̽��ϴ�.");
			}
		}
		normalevnet = 1;

	}

	// ����� ������ �̺�Ʈ
	else if (random == 2) {
		printf("����� �����ڵ��� ���ڸ� �޶�� �䱸�ؿԴ�.\n");
		printf("1. �ķ� 2��\n2. �� 2��\n3. ���޾�\n4. ���� �ʴ´�.\n");
		while (1) {
			printf("�� �ٱ�?\n- ");
			scanf(" %d", &i);
			if (i == 1) {
				if (player.food < 2) {
					printf("�ķ��� �����ؼ� ���� ���� �� ����.\n");
				}
				else {
					player.food -= 2;
					printf("�ķ� 2���� ���.\n");
					player.dad[2]++;
					player.mom[2]++;
					player.son[2]++;
					player.dau[2]++;
					printf("������ �ڸ� �����־��ٴ� ������ ����� ���ŷ��� ��ȭ�Ǿ���.\n");
					break;
				}
			}
			else if (i == 2) {
				if (player.water < 2) {
					printf("���� �����ؼ� ���� ���� �� ����.");
				}
				else {
					player.water -= 2;
					player.dad[2]++;
					player.mom[2]++;
					player.son[2]++;
					player.dau[2]++;
					printf("�� 2���� ���.\n");
					printf("������ �ڸ� �����־��ٴ� ������ ����� ���ŷ��� ��ȭ�Ǿ���.\n");
					break;
				}
			}
			else if (i == 3) {
				if (player.first_aid_kit < 1) {
					printf("���޾��� �����ؼ� ���� ���� �� ����.\n");
				}
				else {
					player.first_aid_kit--;
					player.dad[2]++;
					player.mom[2]++;
					player.son[2]++;
					player.dau[2]++;
					printf("���޾��� ���.\n");
					printf("������ �ڸ� �����־��ٴ� ������ ����� ���ŷ��� ��ȭ�Ǿ���.\n");
					break;
				}
			}
			else if (i == 4) {
				int random = rand() % 11;
				if (random = 0) {
					player.food = 0; player.water = 0;
					printf("����� �����ڵ��� �ĵ��� ���ڸ� �ϴ� �о��.\n");
					break;
				}
				else {
					printf("����� �����ڵ��� ��¿ �� ���� �ٽ� ���� �ɾ��\n");
					break;
				}
			}
			else {
				printf("�߸� �Է��ϼ̽��ϴ�.\n");
			}
		}
		normalevnet = 2;
	}

	// ���� �̺�Ʈ
	else if (random == 3) {
		printf("��Ŀ���� ��Ȱ�ϴ� ���� ������ ���� �� ������. �׳��� ������ ���� �� �ִ� �� �Ѿ� �� ȭ���� �� ����.\n");
		while (1) {
			printf("������ �ұ�? (y or n)\n- ");
			scanf(" %c", &c);
			if (c == 'y' || c == 'Y') {
				printf("Ȯ���� ������ û��� ������ִ� �����̴�.\n");
				printf("������ �ϰ� �޽��� ���ϴ� ������ ���Ҵ�.\n");
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
						printf("������ ���� ���� �ƺ��� ������ �ɷȴ�.\n");
						break;
					case 1:
						player.mom[5] -= 1;
						printf("������ ���� ���� ������ ������ �ɷȴ�.\n");
						break;
					case 2:
						player.son[5] -= 1;
						printf("������ ���� ���� �Ƶ��� ������ �ɷȴ�.\n");
						break;
					case 3:
						player.dau[5] -= 1;
						printf("������ ���� ���� ���� ������ �ɷȴ�.\n");
						break;
					}

				}
				else {
					printf("�̷� �� �ӿ��� ������ ���� �� �־�� �Ѵ�.\n");
				}
				break;
			}
			else {
				printf("�߸� �����̽��ϴ�.");
			}
		}
		normalevnet = 3;
	}

	// ź��� �湮 �̺�Ʈ
	else if (random == 4) {
		printf("�ۿ��� ź����� �湮�ؿԴ�. �����ŷ��� ���ڰ� �ߴ�.\n");
		printf("1. üĿ\n2. ź��.\n3. �ƹ��͵� ���� �ʴ´�.\n");
		while (1) {
			printf("����� ����ұ�?\n- ");
			scanf(" %d", &i);
			if (i == 1) {
				if (player.chess == 0) {
					printf("üĿ�� ������ ���� ���� �� ����.\n");
				}
				else {
					printf("üĿ�� ���.\n���ٸ� �밡�� �ķ��� ���� 1���� �־���.");
					player.food++;
					player.water++;
					break;
				}
			}
			else if (i == 2) {
				if (player.ammo == 0) {
					printf("ź�� ���� ���� �̸� Ȯ���ߴµ��� �������� �ϳĸ鼭 ���ÿ� ����ź�� �Ͷ߷ȴ�..\n");
					printf("������ ��ġ�� ���� �ķ� 2���� �� 1���� ��������.\n");
					player.food -= 2;
					player.water--;
					break;
				}
				else {
					printf("����� ������ ������ ź���� ä���־��ٰ� ū ������ ǥ���ߴ�.\n���ٸ� �밡�� ");
					if (player.ax == 0 && player.knife == 1) {
						printf("Į�� �ִ� �� ���ٸ� ������ �ǳ��־���.\n");
					}
					else if (player.knife == 0 && player.ax == 1) {
						printf("������ �ִ� �� ���ٸ� Į�� �ǳ��־���.");
					}
					else {
						int random = rand() % 2;
						if (random == 0) {
							printf("������ �ǳ��־���.\n");
							player.ax++;
						}
						else if (random == 1) {
							printf("Į�� �ǳ��־���.\n");
							player.knife++;
						}
					}
					break;
				}
			}
			else if (i == 3) {
				printf("�����ִ� ����� �Ǹſ��� �ŷ��� ���� ���� �ƽ�����.\n");
				break;
			}
			else {
				printf("�߸� �����̽��ϴ�.");
			}
		}
		normalevnet = 4;
	}

	// �Ź� �߰� �̺�Ʈ
	else if (random == 5) {
		printf("������ ��Ŀ���� ��Ȱ�ϴ� ���� �Ź̸� �߰��ߴ�.\n");
		printf("1. �������� ó���Ѵ�.\n2. å���� ��´�\n3. ���޾��� ����Ѵ�.\n4. �� ������ ��ƺ���.\n");
		while (1) {
			printf("��� �ؾ��ұ�?\n- ");
			scanf(" %d", &i);
			if (i == 1) {
				if (player.pesticide == 0) {
					printf("\n�� �������� �����մϴ�\n");
				}
				else {
					printf("\n�� �������� ����� �Ź̸� ��Ҵ�.\n");
					printf("�������� �Һ��߽��ϴ�.\n");
					player.pesticide--;
					break;
				}
			}
			else if (i == 2) {
				if (player.book == 0) {
					printf("\n�� å�� �����մϴ�.\n");
				}
				else {
					printf("\n�� ������� ��µ��� å ���Ѱ� ����!\n");
					printf("�Ź̵��� �ִ� ��Ŀ ������ ������ ");
					int random = rand() % 2;
					if (random == 0) {
						printf("�ķ��� �߰��ߴ�.\n");
						player.food++;
					}
					else if (random == 1) {
						printf("���� �߰��ߴ�\n");
						player.water++;
					}
					break;
				}
			}
			else if (i == 3) {
				if (player.first_aid_kit == 0) {
					printf("\n�� ���޾��� �����մϴ�.\n");
				}
				else {
					printf("\n�� �츮�� ���� �ð��� ��Ŀ���� ������ ���� ȯ���̶� �����߰�, \n");
					printf("���޾� �� �����ż� ���� ����غ��� �Ź̴� ������־���.\n");
					player.first_aid_kit--;
					break;
				}
			}
			else if (i == 4) {
				printf("\n�� �Ź̸� ����� �� ���� �� �ɰ��� �� ���ٰ� �����Ѵ�. �� ������ ������ ��ƺ����ٰ�\n");
				printf("�Ź̿��� ���Ȱ�, ");
				int random2 = rand() % 4;
				switch (random2) {
				case 0:
					player.dad[5] -= 1;
					printf("�ƺ��� ������ �ɷȴ�.\n");
					break;
				case 1:
					player.mom[5] -= 1;
					printf("������ ������ �ɷȴ�.\n");
					break;
				case 2:
					player.son[5] -= 1;
					printf("�Ƶ��� ������ �ɷȴ�.\n");
					break;
				case 3:
					player.dau[5] -= 1;
					printf("���� ������ �ɷȴ�.\n");
					break;
				}
				break;
			}
			else {
				printf("\n�߸� �����̽��ϴ�.\n");
			}
		}
		normalevnet = 5;
	}

	// ���� ��� - ī���� ���� (���� ���� ���� �����)
	else if (random == 6) {
	int num1, num2, n = 1;
	printf("�ٱ����� ���� �������� ���� �ε���.\n");
	while (1) {
		printf("�����? (y or n)\n- ");
		scanf(" %c", &c);
		if (c == 'y' || c == 'Y') {
			printf("���� ����� ����� ���� �� �纹�� ���� ���� ���ڰ� ���Ŀ�� ���־���\n");
			printf("�״� ī���� �������� ������ ���ڰ� ���ߴ�. ������ �����ߴ�.\n");
			printf("4�� �ֻ����� ���� �� ū ���ڰ� �̱�� �����̴�.\n");
			printf("�����ϰ� ���Ӹ� �ϴ� ���� ��̾��⿡, �ķ� �Ǵ� ���� �ɱ�� �Ͽ���.\n ");
			printf("������ ���ڰ� ���� �� ����, �Ǵ� ������ �ķ�, ���� ���� �� ���� ������ �����Ѵ�.\n");
			while (1) {
				printf("������ �Ͻðڽ��ϱ�? (y or n)\n- ");
				scanf(" %c", &c);
				if (c == 'y' || c == 'Y') {
					while (1) {
						printf("�ķ� �Ǵ� �� �� � ���� �ɰڽ��ϱ�?\n- ");
						scanf(" %d", &i);
						if (i == 1) {
							if (player.food == 0) {
								printf("\n�� �� �� �ִ� �ķ��� ����.\n");
								continue;
							}
							else {
								break;
							}

						}
						else if (i == 2) {
							if (player.water == 0) {
								printf("\n�� �� �� �ִ� �ķ��� ����.\n");
								continue;
							}
							else {
								break;
							}
						}
						else {
							printf("\n�߸� �Է��ϼ̽��ϴ�.\n");
							continue;
						}
						system("cls");
						printf("������ �����մϴ�.\n");

					game:
						if (player.food == 0 || player.water == 0) {
							printf("�̷�! ���ӿ� �����ϴ� ���� ");
							if (i == 1) {
								printf("�츮�� �ķ��� �� ��������.\n");
								printf("���ڴ� �����鼭 �Ʊ��ٴ� ���� �Բ� ��Ŀ�� ������.\n");
								break;
							}
							else if (i == 2) {
								printf("�츮�� ���� �� ��������.\n");
								printf("���ڴ� �����鼭 �Ʊ��ٴ� ���� �Բ� ��Ŀ�� ������.\n");
								break;
							}
						}
						printf("���� %d��°\n", n);
						num1 = randomSystem(4) + 1;
						num2 = randomSystem(4) + 1;
						printf("�츮�� ����: %d\n", num1);
						printf("������ ����: %d\n", num2);
						if (num1 > num2) {
							printf("�츮�� �̰��!\n");
							printf("���ڴ� �����鼭 �Ʊ��ٴ� ǥ������ ");
							if (i == 1) {
								player.food++;
								printf("�ķ� 1���� ���.\n");
							}
							else if (i == 2) {
								player.water++;
								printf("�� 1���� ���.\n");
							}
							goto game;
						}
						else if (num1 < num2) {
							printf("�츮�� ����.\n");
							printf("���ڴ� �����鼭 ����� ǥ������ ");
							if (i == 1) {
								player.food--;
								printf("�ķ� 1���� �޾ư���.\n");
							}
							else if (i == 2) {
								player.water--;
								printf("�� 1���� �޾ư���.\n");
							}
							goto game;
						}
					}
					break;
				}

				else if (c == 'n' || c == 'N') {
					printf("\n�� �츮 ������ ������ ���� ���ϴ� �����̾���, ���� ���ڴ� �ƽ��ٸ� ������.\n");
					break;
				}
				else {
					printf("\n�߸� �����̽��ϴ�.\n");
				}
			}
			break;
		}
		else if (c == 'n' || c == 'N') {
			printf("\n�� ���� ������ ����� �湮�� �ʿ�� ���� �� ����\n");
			break;
		}
		else {
			printf("�߸� �����̽��ϴ�.");
		}
	}
	normalevnet = 6;
	}

	// 
	else if (random == 7) {
		printf("�̱��� �̺�Ʈ (random = 7)");
		normalevnet = 7;
	}
	else if (random == 8) {
		printf("�̱��� �̺�Ʈ (random = 8)");
		normalevnet = 8;
	}
	else if (random == 9) {
		printf("�̱��� �̺�Ʈ (random = 9)");
		normalevnet = 9;
	}
}

void goodEvent() {
	// ���⿡ ����̶� �ɳ��� �̺�Ʈ
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

	// ������ �̸�
	if (random == 0) {
		printf("������ �̸����� ���� ����� ��ġ���̰� ��Ŀ �տ��� �Ҹ��ƴ�.\n");
		while (1) {
			printf("�����ٱ�? (y or n)\n- ");
			scanf(" %c", &c);
			if (c == 'y' || c == 'Y') {
				printf("��ġ������ ������� �̹� �������� ���� ���� ������ �ξƿ� �� �ߴ�.\n");
				printf("������ ���� ������ �츮���� �ŷڰ��� ǥ���ϸ�");
				if (player.ax == 0 && player.knife == 0 && player.gun == 0) {
					int random = rand() % 3;
					if (random == 0) {
						printf("������ ������ �־���.\n");
						player.ax++;
					}
					else if (random == 1) {
						printf("������ Į�� �ǳ��־���.\n");
						player.knife++;
					}
					else {
						printf("������ ���� �ǳ��־���.\n");
						player.gun++;
					}
				}
				else {
					printf("�ķ� 2���� �� 1���� �ǳ��־���.\n");
					player.food += 2;
					player.water += 1;
				}
			}
			else if (c == 'n' || c == 'N') {
				printf("���� ������ ����� �湮�� �ʿ�� ���� �� ����\n");
				break;
			}
			else {
				printf("�߸� �����̽��ϴ�.");
			}
		}
		goodevent = 0;
	}

	// ����� - �� �Ǹ�
	else if (random == 1) {
		if (rock == 0) {
			printf("����ڵ��� ���ڱ� ��Ŀ�� �湮�� ���� �ȷ� �Դٰ� ���ߴ�. ���۽��� �� �湮 �ǸŴ� ó���� �� ����.\n");
			while (1) {
				printf("���� �����ұ�? (y or n)\n- ");
				scanf(" %c", &c);
				if (c == 'y' || c == 'Y') {
					printf("������ ���� �����ϱ⿣ �Ʊ���.\n���� �����ߴ�.");
					rock++;
					break;
				}
				else if (c == 'n' || c == 'N') {
					printf("���� �Ĵ� ��ġ���̵��� ����� �ʿ�� ����.\n");
					break;
				}
				else {
					printf("�߸� �����̽��ϴ�.");
				}
			}
		}
		else if (rock == 1 && player.water == 0) {
			printf("���� ���� �Ǹ��ߴ� ����ڰ� ã�ƿ� ���� ���� �ִ� ����鿡�Դ� �ູ�� �ٰ��Դٰ� ���ߴ�.\n");
			printf("������ �� ����! (�� 3���� �޾ҽ��ϴ�.)\n");
			player.water = 3;
		}
		goodevent = 1;
	}

	else if (random == 2) {
		printf("�̱��� �̺�Ʈ (random = 2)");
		goodevent = 2;
	}
	else if (random == 3) {
		printf("�̱��� �̺�Ʈ (random = 3)");
		goodevent = 3;
	}
	else if (random == 4) {
		printf("�̱��� �̺�Ʈ (random = 4)");
		goodevent = 4;
	}
	else if (random == 5) {
		printf("�̱��� �̺�Ʈ (random = 5)");
		goodevent =5 ;
	}
	else if (random == 6) {
		printf("�̱��� �̺�Ʈ (random = 6)");
		goodevent = 6;
	}
	else if (random == 7) {
		printf("�̱��� �̺�Ʈ (random = 7)");
		goodevent =7 ;
	}
	else if (random == 8) {
		printf("�̱��� �̺�Ʈ (random = 8)");
		goodevent =8 ;
	}
	else if (random == 9) {
		printf("�̱��� �̺�Ʈ (random = 9)");
		goodevent = 9;
	}
}

// ��� �̺�Ʈ�� no �� ��� �����ϱ�
void militaryEvent() {
	// ������ ���� ����
	int i = 0;
	char c;
	if (eventTurn == 0) {
		printf("������ ���ļ��� ������ ���� ���δ��� ���ļ��� ã�� �Ǿ��� �����ڴ� �������� ������� �ߴ�.\n");
		while (1) {
			printf("������? (y or n)\n- ");
			scanf(" %c", &c);
			if (c == 'y' || c == 'Y') {
				printf("\n�� �� �״�� ������ ��� ���� �ִ� �� �δ븦 ���߰�, ���� ������ ���� �Ŷ�� ���ߴ�.\n");
				eventTurn++;
				break;
			}
			else if (c == 'n' || c == 'N') {
				printf("\n�� �� ���󿡼� ������ �������� ���δ��� ���� �� ���� ���̴�.\n");
				eventCancel = 1;
				break;
			}
			else {
				printf("\n�߸� �����̽��ϴ�.\n");
			}
		}
	}

	else if (eventTurn == 1) {
		
		printf("���δ밡 ������ ���� ���� ���� �����ڴ� ���� ��ġ ��ó�� ���� ǥ���� ������ �ߴ�.\n");
		printf("----------\n");
		printf("1. ����\n");
		printf("2. ī��\n");
		printf("3. ������\n");
		printf("4. ��Ե� ǥ���� �����.\n");
		printf("----------\n");
		while (1) {
			printf("� ������ ǥ���� �����?\n- ");
			scanf(" %d", &i);
			if (i == 1) {
				if (player.map == 0) {
					printf("\n�� ������ ���� �� �۾��� �� �� ���� �� ����.\n");
				}
				else {
					player.map = 0;
					printf("\n�� ������ ǥ���ߴ�.\n");
					break;
				}
			}
			else if (i == 2) {
				if (player.card == 0) {
					printf("\n�� ī�尡 ���� �� �۾��� �� �� ���� �� ����.\n");
				}
				else {
					player.card = 0;
					printf("\n�� ī��� ǥ���ߴ�.\n");
					break;
				}

			}
			else if (i == 3) {
				if (player.flash == 0) {
					printf("\n�� �������� ���� �� �۾��� �� �� ���� �� ����.\n");
				}
				else {
					player.flash--;
					printf("\n�� ������� ǥ���ߴ�.\n");
					break;
				}

			}
			else if (i == 4) {
				if (player.food > 0) {
					if (player.food < 2) {
						printf("\n�� �����ִ� �ķ��� ���� �Ἥ SOS�� �׷ȴ�.\n");
						break;
					}
					else {
						printf("\n�� ��Ե� ǥ���� ����� ���� �ķ� 2���� �Ἥ SOS�� �׷ȴ�\n");
						player.food -= 2;
						break;
					}

				}
			}
			else {
				printf("\n�߸� �Է��ϼ̽��ϴ�.\n");
			}
		}
		eventTurn++;
	}
	else if (eventTurn == 2) {

		printf("������ �����ڸ� �����ϱ� ���ؼ��� �����ڵ��� ���� ���� �ʿ��ϴٰ� �ߴ�.\n");
		printf("----------\n");
		printf("1. ������ ��� ��� ������ �Ǽ��� ���� ������ ���� (���� Ȯ���� �Ҹ�)\n");
		printf("2. �浶���� ���� �α� �����ҿ��� �ֹ����� �����´�. \n");
		printf("3. ���� ��Ҹ� ���ֱ� ���� �ѱ⸦ ������.\n");
		printf("----------\n");
		while (1) {
			printf("� �۾��� �ұ�?\n- ");
			scanf(" %d", &i);
			if (i == 1) {
				if (player.ax == 0) {
					printf("\n�� ������ ���� �� �۾��� �� �� ���� �� ����.\n");
				}
				else {
					// 25%Ȯ���� ��Ų
					int random = rand() % 4;
					if (random == 0) {
						player.ax = 0;
						printf("\n�� ������ �۾��ߴ�.\n");
						printf("+ �׸��� �۾� �ϴ� ���� ������ �μ�����.");
						break;
					}
					else {
						printf("\n�� ������ �۾��ߴ�.\n");
						break;
					}
				}
			}
			else if (i == 2) {
				if (player.gas_mask == 0) {
					printf("\n�� �浶���� ���� �� �۾��� �� �� ���� �� ����.\n");
				}
				else {
					printf("\n�� �浶������ �ֹ����� ì�ܳ���.\n");
					break;
				}
			}
			else if (i == 3) {
				if (player.gun == 0) {
					printf("\n�� ���ʿ� �ѵ� ���ٴ� ���� �����ϰ� ǥ���ߴ�.\n");
					break;
				}
				else {
					printf("\n�� ���� ���� ���δ뿡�� �ŷڰ��� ǥ���ߴ�.\n");
					player.gun = 0;
					break;
				}

			}
			else {
				printf("\n�߸� �Է��ϼ̽��ϴ�.\n");
			}

		}
		eventTurn++;
	}

	// �̰� explo ���� �۾�?�ϱ�
	else if (eventTurn == 3) {
		printf("���� ��û���� �����ڵ� �� �� ��� ������ ���ߴ�.\n ");
		printf("������������������\n");
		printf("1. �ƺ�\n");
		printf("2. ����\n");
		printf("3. �Ƶ�\n");
		printf("4. ��\n");
		printf("������������������\n");
		while (1) {
			printf("���� ������?\n- ");
			scanf(" %d", &i);
			if (i == 1) {
				printf("\n�� �ƺ��� ������� �ߴ�.\n");
				printf("+ ������ �޴� ���� ���� ������ �������� ���� ���δ�� �ƺ��� ���ƴ�\n");
				player.dad[4]--;
				break;
			}
			if (i == 2) {
				printf("\n�� ������ ������� �ߴ�.\n");
				printf("+ ������ �޴� ���� ���� ������ �������� ���� ���δ�� ������ ���ƴ�\n");
				player.mom[4]--;
				break;
			}
			if (i == 3) {
				printf("\n�� �Ƶ��� ������� �ߴ�.\n");
				printf("+ ������ �޴� ���� ���� ������ �������� ���� ���δ�� �Ƶ��� ���ƴ�\n");
				player.son[4]--;
				break;
			}
			if (i == 4) {
				printf("\n�� ���� ������� �ߴ�.\n");
				printf("+ ������ �޴� ���� ���� ������ �������� ���� ���δ�� ���� ���ƴ�\n");
				player.dau[4]--;
				break;
			}
			else {
				printf("\n�߸� �Է��ϼ̽��ϴ�.\n");
			}
		}
		eventTurn++;
	}
	else if (eventTurn == 4) {
		//���� ����
		printf("�ۿ��� �����ϰ� �ε帰��. ������ �ò����� ���� �ο��� ���� ��Ȳ���� �� �� ����. \n");
		printf("������������������������������\n");
		printf("1. ���� ��� Ȯ���غ���.\n");
		printf("2. �����ϴ� ���� �ʴ´�.\n");
		printf("������������������������������\n");
		while (1) {
			printf("�����?\n- ");
			scanf(" %d", &i);
			if (i == 1) {
				printf("���� ����, ");
				printf("���δ� ���� �Ϸ�");
				exit(0);
			}
			else if (i == 2) {
				printf("\n�� ������ �� ���� �����ؾ� �Ѵ�.\n");
				eventCancel = 1;

				break;
			}
			else {
				printf("\n[�߸� �Է��ϼ̽��ϴ�.]\n");
			}
		}

	}
}

void agentEvent() {
	int i = 0;
	char c;
	if (eventTurn == 0) {
		printf("���������� �ڼ��� ���� ����̿��� Ư�� �ּҰ� �����־���.\n");

		while (1) {
			printf("������? (y or n)\n- ");
			scanf(" %c", &c);
			if (c == 'y' || c == 'Y') {
				printf("\n�� �ּҷ� ã�ư��� ���߿� ������� ��Ÿ�� ���������� ã���־��ٸ� ������ �����ȴ�.\n");
				printf("������ ���������� ��ĥ �ڿ� �㵵 ���� �𸣰� �ٽ� ���ȣ�� ���ƿ´�.\n");
				eventTurn++;
				break;
			}
			else if (c == 'n' || c == 'N') {
				printf("\n�� �̹� �������� �Ͼ ������ �װ��� ���� �� �ǹ� ���� ���̴�. \n");
				eventCancel = 2;
				break;
			}
			else {
				printf("�߸� �����̽��ϴ�.");
			}
		}
	}
	else if (eventTurn == 1) {
		printf("���������� ������ ��� �ִ� Ƣ��� ������ �����ϸ� ���ȣ�� ��û ���̴� ������� �߰��ߴ�.\n");
		while (1) {
			printf("�i�Ƴ���? (y or n)\n- ");
			scanf(" %c", &c);
			if (c == 'y' || c == 'Y') {
				printf("���� ���� �־ ���� ��Ŀ�� ��û�ϸ� ���� ���̴�.\n");
				eventTurn++;
				break;
			}
			else if (c == 'n' || c == 'N') {
				printf("�̷��� ������ ��Ŀ�� ��û�غ��� �ƹ��� �̵浵 ���� ���̴�.");
				break;
			}
			else {
				printf("�߸� �����̽��ϴ�.");
			}
		}
	}
	else if (eventTurn == 2) {
		printf("������ ��û ���̴� ����� �̹��� ���������� ���� �ε���. ���� �빫������ �� �𸣰ڴ�.\n");
		while (1) {
			printf("�����ٱ�? (y or n)\n- ");
			scanf(" %c", &c);
			if (c == 'y' || c == 'Y') {
				printf("�����ְ� �Ǹ� �ڽŵ��� ������ ������̸� ���������� �ҷ��� �������� ���ɼ��� �־�\n ��û ���̾��ٴ� ���� �Բ� �ڽŵ��� ����� ���� ������ �������ְڴٰ� �ϰ� ���ư���.\n");
				eventTurn++;
				break;
			}
			else if (c == 'n' || c == 'N') {
				printf("��û�� ������� �湮�� �ʿ�� ���� �� ����\n");
				break;
			}
			else {
				printf("�߸� �����̽��ϴ�.");
			}
		}
	}
	else if (eventTurn == 3) {
		// ����� ���ÿ� ���� Ž���ϴ� �̺�Ʈ
		printf("������� �ڽŵ� ��� ��� ������ ������ �޶�� �䱸�ϸ� ���� �Ѹ��� ���� �� �ִ�.\n");
		while (1) {
			printf("���� �����ٱ�?\n- ");
			printf("1. �ƺ�\n2. ����\n3. �Ƶ�\n4. ��");
			scanf(" %d", &explo);
			if (explo == 1) {
				printf("�ƺ��� ����� ��û�� ���ϱ�� �ߴ�.\n");
				break;
			}
			else if (explo == 2) {
				printf("������ ����� ��û�� ���ϱ�� �ߴ�.\n");
				break;
			}
			else if (explo == 3) {
				printf("�Ƶ��� ����� ��û�� ���ϱ�� �ߴ�.\n");
				break;
			}
			else if (explo == 4) {
				printf("���� ����� ��û�� ���ϱ�� �ߴ�.\n");
				break;
			}
			else {
				printf("�߸� �����̽��ϴ�.");
			}
		}
		eventTurn++;
	}
	else if (eventTurn == 4) {
		printf("������� ���ݱ����ǳ�� ġ���ϸ� �ٸ� ������ �ӹ� ���� ����鿡�� ���� ���ڸ� �䱸�Ѵ�\n");
		printf("1. �ķ� 4��\n2. �� 4��\n3. ���� �ʴ´�.\n");
		while (1) {
			printf("�� �ٱ�?\n- ");
			scanf(" %d", &i);
			if (i == 1) {
				if (player.food < 4) {
					printf("�ķ��� �����ؼ� ���� ���� �� ����.\n");
				}
				else {
					player.food -= 4;
					printf("�ķ� 4���� ���.\n");
					eventTurn++;
					break;
				}
			}
			else if (i == 2) {
				if (player.water < 4) {
					printf("���� �����ؼ� ���� ���� �� ����.");
				}
				else {
					player.water -= 4;
					printf("�� 4���� ���.\n");
					eventTurn++;
					break;
				}
			}
			else if (i == 3) {
				printf("������ �����ؼ� ���� ���� �� ����.");
				break;
			}
		}
	}
	else if (eventTurn == 5) {
		printf("�ٱ����� ������� �Ҹ��� ����. ��ũ �Ҹ��� �Բ� ���� �ٶ������, \n");
		printf("�ƹ��� ������, �̽�½�⸸ �ߴ�.\n");
		printf("1. ����\n2.���� �ʴ´�.\n");
		while (1) {
			printf("���� ���� ���� �Դ��� Ȯ���ұ�?\n- ");
			scanf(" %d", &i);
			if (i == 1) {
				printf("���� ����\n");
				return 0;
			}
			else if (i == 2) {
				printf("�� ���� �Ҹ��� �Բ� �����⸦ ���� ö���Ѵٴ� �Ҹ��� ��� �Ǿ���.\n");
				eventCancel = 2;
				eventTurn = 0;
				break;
			}
			else {
				printf("�߸� �Է��ϼ̽��ϴ�.\n");
			}
		}
	}
}

void twinEvent() {
	int n = 0, i = 0;
	char c;
	if (eventTurn == 0) {
		//  ���� ��ȭ�� ��ȭ�� �ɷ��� ���� �� �� ���� �޾ƾ� ��
		printf("�μ��� �ٸ� �˾Ҵ� ������ȭ�ؼ� ��ȭ�� �ɷ��Դ�.\n");
		while (1) {
			printf("������ ������? (y or n)\n- ");
			scanf(" %c", &c);
			if (c == 'y' || c == 'Y') {
				printf("----------------------\n");
				printf("1. �ƺ�\n2. ����\n3. �Ƶ�\n4. ��\n");
				printf("----------------------\n");
				while (1) {
					printf("���� ����?\n- ");
					scanf(" %d", &i);
					if (i == 1) {
						printf("\n�� �ƺ��� ��ȭ�� ������ ����.\n");
						break;
					}
					else if (i == 2) {
						printf("\n�� ������ ��ȭ�� ������ ����.\n");
						break;
					}
					else if (i == 3) {
						printf("\n�� �Ƶ��� ��ȭ�� ������ ����.\n");
						break;
					}
					else if (i == 4) {
						printf("\n�� ���� ��ȭ�� ������ ����.\n");
						break;
					}
					else {
						printf("\n�߸� �Է��ϼ̽��ϴ�.\n");
					}
				}
				printf("�̿� �� ������ ��ȭ�� �޾Ұ� �ڽ��� ��ȣ��ü���� Ȱ���Ѵٰ� �߰�, �� ������ ���� �Ŷ�� �ߴ�.\n");
				printf("�̷� ����� ���� �ӿ��� ���� ������� ������? ��� �����ϸ鼭 ��Ŀ�� �ٽ� ���ƿԴ�.\n");
				eventTurn++;
				break;
			}
			else if (c == 'n' || c == 'N') {
				printf("\n�� ������ ��缱���� ���� ���峵�� ���� ���ϴ�.\n");
				eventCancel = 3;
				break;
			}
			else {
				printf("�߸� �����̽��ϴ�.");
			}
		}
	}
	else if (eventTurn == 1) {
		// ���� n ���� �� ���丮 ������ ���� �ұ�?
		printf("���� �ò��ò��ؼ� �ٶ󺸴� ������ ��� �ݹ��� ������ ��ġ�ϰ� �ִ� ����� ���Ҵ�.\n");
		while (1) {
			printf("�����ٱ�? (y or n)\n- ");
			scanf(" %c", &c);
			if (c == 'y' || c == 'Y') {
				// 6.����	7.Į	8.��
				printf("�����ֱ� ���ؼ� ��� ������ ���Ⱑ �ʿ��� �� ����.\n");
				printf("1. ����\n2. Į\n3. ��\n4. �Ǹ�\n");
				while (1) {
					printf("� ���⸦ ��� ����?\n- ");

					scanf(" %d", &i);

					if (i == 1) {
						if (player.ax == 1) {
							printf("�� ������ �̿��� ��ġ�� ������ �������.\n");
							break;
						}
						else {
							printf("�� ������ ����.\n");
						}
					}
					else if (i == 2) {
						if (player.knife == 1) {
							printf("�� Į�� �̿��� ��ġ�� ������ �������.\n");
							break;
						}
						else {
							printf("�� Į�� ����.\n");
						}
					}
					else if (i == 3) {
						if (player.gun == 1) {
							printf("�� ���� �̿��� ��ġ�� ������ �������.\n");
							break;
						}
						else {
							printf("�� ���� ����.\n");
						}
					}
					else if (i == 4) {
						printf("----------------------\n");
						printf("1. �ƺ�\n2. ����\n3. �Ƶ�\n4.��\n");
						printf("----------------------\n");
						while (1) {
							printf("���� �����ٱ�?\n- ");
							scanf(" %d", &i);
							if (i == 1) {
								printf("�� �ƺ��� ���췯 ����.\n");
								int random = rand() % 3;
								if (random == 0) {
									player.dad[4]--;
									printf("�����ִ� ���� ���ƴ�.");
								}
								break;
							}
							else if (i == 2) {
								printf("�� ������ ���췯 ����.\n");
								int random = rand() % 3;
								if (random == 0) {
									player.mom[4]--;
									printf("�����ִ� ���� ���ƴ�.");
								}
								break;
								
							}
							else if (i == 3) {
								printf("�� �Ƶ��� ���췯 ����.\n");
								int random = rand() % 3;
								if (random == 0) {
									player.son[4]--;
									printf("�����ִ� ���� ���ƴ�.");
								}
								break;
							}
							else if (i == 4) {
								printf("�� ���� ���췯 ����.\n");
								int random = rand() % 3;
								if (random == 0) {
									player.dau[4]--;
									printf("�����ִ� ���� ���ƴ�.");
								}
								break;
							}
							else {
								printf("�߸� �Է��ϼ̽��ϴ�.\n");
							}
						}
						break;
					}
					else {
						printf("\n�߸� �Է��ϼ̽��ϴ�\n");
					}
				}
				printf("�ݹ��� ������ �����߷� ���� �ٸ� ���� ����޴� ������� ���� �ִٰ� �ߴ�.\n");
				printf("������ȭ�� ���� ����, �� ��ŵ鿡�� �����ٰ� �ƹ���, ������ �θ񿡰� ��ġ���ߴٰ� �߰�,\n");
				printf("���п� ū ������ �޾Ҵٰ� ���ߴ�.\n");
				eventTurn++;
				break;
			}
			else if (c == 'n' || c == 'N') {
				printf("�� ���� ���� �������� ���ٰ��� ���� ��ġ ������ �𸥴�. \n");
				eventCancel = 3;
				break;
			}
			else {
				printf("\n�߸� �����̽��ϴ�.\n");
			}
		}
	}
	else if (eventTurn == 2) {
		// �����ڸ� ���� �ķ� �ϳ� ���
		printf("������ ������ ������ �������� ����� ã�ƿ� �������� ������ ���߰�, �ܿ� ������ ��Ŀ�� ã�ƿԴ�.\n");
		printf("������ �i�� �ƹ� �͵� ������, �������� ���ߴٰ� �Ѵ�. \n");
		printf("1. ���� \n2. ��\n3. �ƹ��͵� ���� �ʴ´�.\n(��� �� �׸� -1)");
		while (1) {
			printf("����� ����ұ�?\n-");
			scanf(" %d", &i);
			if (i == 1) {
				if (player.food == 0) {
					printf("������ ������ ���� ���� �� ����.\n");
				}
				else {
					printf("������ ���.\n");
					player.food--;
					eventTurn++;
					break;
				}
			}
			else if (i == 2) {
				if (player.water == 0) {
					printf("���� ������ ���� ���� �� ����.\n");
				}
				else {
					printf("���� ���.\n");
					player.water--;
					eventTurn++;
					break;
				}
			}
			else if (i == 3) {
				printf("�ְ� ������ �츮 ������ �����ϴٰ� �Ͽ� �̾����� ǥ���ߴ�.\n");
				printf("������ �i��� �������� ���� ���� �� �� �����ε� ���ٰ� �ߴ�.\n");
				eventTurn++;
				break;
			}
			else {
				printf("�߸� �����̽��ϴ�.");
			}
		}
	}
	else if (n == 3) {
		// ���̵��� ���� �̺�Ʈ
		// ���� �̺�Ʈ���� �ķ� or �� �Ҹ� �� ������

		/*
		üĿ �̺�Ʈ(üĿ �Ҹ�)
		�����̹� ���̵� �̺�Ʈ(�����̹� ���̵� �Ҹ�)
		ī�� �̺�Ʈ(ī�� �Ҹ�)
		���� ��� ���翡 ���� (�Ǽ�, Ȯ���� ��ħ or ����)
		*/
		printf("�̹��� �ݹ� ���Ű� ��� ã�ƿ� ������ ����� ����༭ ���ٰ� ���ߴ�.\n");

		//�� �̺�Ʈ���� �������� ��
		if (i == 1 || i == 2) {
			printf("���ÿ� ���� ���� �� ���� �Ͽ� ");
			if (i == 1) {
				printf("���� ���� �ķ��� 2��� �ǳ� �־���.\n");
				player.food += 2;
			}
			else if (i == 2) {
				printf("���� ���� ���� 2��� �ǳ� �־���.\n");
				player.water += 2;
			}
		}
		printf("������ ��ȣ��ü���� Ȱ�� ���̴ٰ� ��ü �� ���̵��� ���Ͽ� Ȳ���� ���� �� ���հŸ��� ã���� ���Դٰ� �Ѵ�.\n");
		printf("1. üĿ\n2. ����\n3.ī��\n4. ���̽� ķ�� ���翡 ���� (�Ǹ�)\n");
		while (1) {
			printf("� ��û�� ���ұ�?\n-");
			scanf(" %d", &i);
			if (i == 1) {
				printf("�ƽ����� üĿ�� ����ߴ�.\n");
				player.chess--;
			}
			else if (i == 2) {
				printf("�ƽ����� å�� �Ҹ��ߴ�.\n");
				player.book--;
			}
			else if (i == 3) {
				printf("�ƽ����� ī�带 �Ҹ��ߴ�.\n");
				player.card--;
			}
			else if (i == 4) {
				printf("�ٰ� ���ٰ� ������ ������ �� �� �ִ°� ���İ� ������.\n");
				printf("�̿� �ֵ��̴� ������ �ʱ� �ܰ������� ���̽� ķ���� ���� �ִٰ� �ߴ�.\n");
				printf("�׷��� ���� ��� �� 3�ð� ������ �����ϴµ� ���ɴ�.\n");
				printf("���縦 �ϴ��� �� 1���� �ķ� 2���� ���.");
				player.food -= 2;
				player.water--;
			}

			else {
				printf("�߸� �Է��ϼ̽��ϴ�.\n");
			}
			printf("�ڽ��� ��ȣ��ü �Ѱ� �ֵ��̶�� �߰�, �� ������ ���� �Ŷ�� �ߴ�.\n");
			eventTurn++;
			break;
		}
	}
	else if (n == 4) {
		// ��Ը� ķ�� ���翡 ���� �̺�Ʈ
		/*
		���� �̺�Ʈ
		���� �̺�Ʈ (Ȯ���� �Ҹ�)
		���޾� �̺�Ʈ (100% Ȯ�����޻��� �Ҹ�)
		*/
		printf("���������� ������ ����ߴ� ��� ������ �����ϴ� ���󿡼� ������� ��ų\n");
		printf("���̽� ķ���� ������� �Ѵ�.\n");
		printf("1. ����\n2. ����\n3. ���޾�");
		while (1) {
			printf("����� ����ұ�?\n-");
			scanf(" %d", &i);
			if (i == 1) {
				if (player.map == 0) {
					printf("������ ������ ���� ���� �� ����.\n");
				}
				else {
					printf("������ ���.\n");
					player.map--;
					eventTurn++;
					break;
				}
			}
			else if (i == 2) {
				if (player.ax == 0) {
					printf("������ ������ ���� ���� �� ����.\n");
				}
				else {
					printf("������ ����ߴ�.\n");
					player.ax--;
					eventTurn++;
					break;
				}
			}
			else if (i == 3) {
				if (player.first_aid_kit == 0) {
					printf("���޾��� ������ ���� ���� �� ����.\n");
				}
				else {
					printf("���޾��� ����ߴ�.\n");
					player.first_aid_kit--;
					eventTurn++;
					break;
				}
			}
			else {
				printf("�߸� �����̽��ϴ�.");
			}
		}

	}
	else if (n == 5) {
		printf("�������� ���� �ε���.\n");
		while (1) {
			printf("����? (y or n)\n-");
			scanf(" %c", &c);
			if (c == 'y' || c == 'Y') {
				printf("���� ����");
				return 0;
			}
			else if (c == 'n' || c == 'N') {
				printf("�����ϴ�.\n");
				eventCancel = 3;
				break;
			}
			else {
				printf("�߸� �����̽��ϴ�.");
			}
		}
	}
}