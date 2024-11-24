#include <algorithm> 
#include <graphics.h> // ʹ��EasyXͼ�ο�
#include <windows.h>
#include <mmsystem.h> // ���ڲ�������
#include <string>
#include <vector>
#include <fstream> 
#include <sstream>
#include <iostream>
#pragma comment(lib, "winmm.lib") // ���� winmm ��

// ���ڳߴ�
const int WINDOW_WIDTH = 1300;
const int WINDOW_HEIGHT = 800;

// ����ҳ������
enum MenuPage {
	MENU1, MENU2, LEVEL_SELECT, SETTINGS, DIFFICULTY,
	HOW_TO_PLAY, LEADERBOARD, SHOP, ABOUT_TEAM,
	CROSSING_STORY, LEVEL1_STORY, LEVEL1_MAP,
	LEVEL2_STORY, LEVEL2_MAP, LEVEL3_STORY, LEVEL3_MAP,
	VICTORY_SCREEN, // ��� VICTORY_SCREEN
	FAIL, GOODEND, BADEND1, BADEND2, PAUSE,
	FINAL_THANKS_TANGCHAO, // �������������Ƴ�������
	FINAL_THANKS_GT       // ���������ĸ���GT
};

// ��������Ľṹ��
struct GroundBlock {
	int left, top, right, bottom; // �������ĸ��߽�����
};

// ����ؿ�1�ĵ����
std::vector<GroundBlock> level1GroundBlocks = {
	{50, 740, 367, 740},
	{368, 660, 486, 660},
	{488, 740, 608, 740},
	{610, 619, 728, 619},
	{729, 740, 929, 740},
	{930, 660, 1088, 660},
	{1089, 621, 1249, 621},
	{930, 540, 1047, 540},
	{1089, 462, 1249, 462},
	{1010, 380, 1048, 380},
	{130, 340, 1009, 340},
	{229, 120, 387, 120},
};

// ����ؿ�2�ĵ����
std::vector<GroundBlock> level2GroundBlocks = {
	{50, 740, 328, 740},
	{330, 777, 448, 777},
	{449, 742, 529, 742},
	{530, 777, 650, 777},
	{648, 742, 730, 742},
	{731, 778, 850, 778},
	{850, 743, 930, 743},
	{933, 704, 970, 704},
	{972, 663, 1169, 663},
	{250, 541, 1091, 541},
	{331, 300, 891, 300},
	{168, 261, 249, 261},
	{328, 182, 449, 182},
	{530, 143, 689, 143},
	{770, 102, 930, 102},
	{968, 101, 1000, 101},
	{1051, 101, 1091, 101},
	{1171, 101, 1249, 101},
	{393, 262, 433, 302},
	{593, 262, 633, 302},
	{818, 262, 858, 302},
};

// ����ؿ�3�ĵ����
std::vector<GroundBlock> level3GroundBlocks = {
	{50, 740, 250, 740},
	{250, 777, 332, 777},
	{333, 741, 449, 741},
	{451, 779, 530, 779},
	{531, 741, 609, 741},
	{610, 777, 689, 777},
	{690, 741, 969, 741},
	{971, 700, 1008, 700},
	{1091, 661, 1209, 661},
	{1012, 541, 1131, 541},
	{1009, 778, 1090, 778},
	{770, 541, 930, 541},
	{610, 501, 729, 501},
	{410, 441, 570, 441},
	{610, 380, 729, 380},
	{770, 320, 889, 320},
	{889, 241, 1007, 241},
	{330, 180, 809, 180},
	{168, 179, 248, 179},
	{849, 60, 889, 60},
	{891, 100, 1002, 100},
	{1049, 140, 1249, 140},
};

// ����ǽ�ڿ�Ľṹ��
struct WallBlock {
	int left, top, right, bottom; // ǽ�ڵ����ұ߽�����±߽�
};

// ����ؿ�1��ǽ�ڿ�
std::vector<WallBlock> level1WallBlocks = {
	{50, 419, 50, 740},
	{369, 660, 369, 740},
	{486, 660, 486, 740},
	{610, 620, 610, 740},
	{729, 620, 729, 740},
	{930, 661, 930, 740},
	{1090, 625, 1090, 660},
	{930, 540, 930, 580},
	{1050, 540, 1050, 580},
	{1090, 463, 1090, 499},
	{1250, 21, 1250, 779},
	{1050, 381, 1050, 419},
	{1009, 340, 1009, 381},
	{130, 20, 130, 340},
	{230, 120, 230, 277},
	{270, 160, 270, 280},
	{388, 21, 388, 120},
	{468, 21, 468, 159},
};

// ����ؿ�2��ǽ�ڿ�
std::vector<WallBlock> level2WallBlocks = {
	{50, 20, 50, 778},
	{332, 742, 329, 777},
	{449, 742, 449, 778},
	{529, 742, 528, 777},
	{650, 742, 649, 777},
	{729, 744, 730, 779},
	{849, 744, 850, 776},
	{933, 703, 932, 740},
	{972, 663, 971, 702},
	{1173, 103, 1172, 663},
	{1249, 23, 1249, 100},
	{1090, 543, 1090, 580},
	{248, 263, 248, 539},
	{168, 261, 168, 581},
	{329, 303, 329, 459},
	{609, 341, 609, 460},
	{890, 302, 890, 339},
	{329, 188, 329, 218},
	{449, 188, 449, 218},
	{529, 147, 529, 178},
	{689, 147, 689, 177},
	{771, 102, 771, 138},
	{930, 103, 930, 139},
	{971, 101, 971, 139},
	{1010, 102, 1010, 139},
	{1051, 102, 1051, 138},
	{1090, 102, 1090, 138},
	{393, 262, 433, 302},
	{593, 262, 633, 302},
	{818, 262, 858, 302},
};

// ����ؿ�3��ǽ�ڿ�
std::vector<WallBlock> level3WallBlocks = {
	{49, 20, 50, 779},
	{248, 746, 249, 778},
	{332, 746, 332, 778},
	{449, 748, 448, 777},
	{530, 746, 529, 777},
	{608, 747, 609, 776},
	{691, 747, 690, 778},
	{970, 707, 970, 739},
	{1009, 708, 1009, 776},
	{1090, 668, 1090, 777},
	{1210, 181, 1209, 661},
	{1130, 548, 1131, 579},
	{1012, 547, 1012, 579},
	{929, 548, 930, 580},
	{769, 547, 770, 580},
	{729, 509, 730, 539},
	{610, 507, 610, 539},
	{568, 450, 570, 480},
	{410, 481, 409, 620},
	{409, 220, 409, 441},
	{329, 188, 330, 619},
	{250, 189, 250, 618},
	{168, 189, 169, 618},
	{610, 386, 610, 420},
	{729, 386, 729, 420},
	{770, 327, 770, 359},
	{889, 329, 889, 359},
	{890, 250, 890, 280},
	{1009, 246, 1010, 281},
	{808, 188, 809, 220},
	{849, 68, 849, 101},
	{887, 66, 889, 98},
	{889, 100, 890, 140},
	{1003, 106, 1003, 141},
	{1050, 146, 1050, 180},
	{1249, 20, 1249, 140},
};

// �����컨���Ľṹ��
struct CeilingBlock {
	int left, top, right, bottom; // �컨������ұ߽�����±߽�
};

// ����ؿ�1���컨���
std::vector<CeilingBlock> level1CeilingBlocks = {
	{931, 580, 1050, 580},
	{1091, 498, 1249, 498},
	{51, 419, 1048, 419},
	{229, 278, 269, 278},
	{269, 160, 467, 160},
	{51, 20, 1249, 20},
};


// ����ؿ�2���컨���
std::vector<CeilingBlock> level2CeilingBlocks = {
	{169, 581, 1090, 581},
	{329, 460, 610, 460},
	{610, 340, 889, 340},
	{330, 221, 450, 221},
	{530, 180, 690, 180},
	{771, 141, 930, 141},
	{972, 140, 1010, 140},
	{1052, 141, 1091, 141},
	{50, 20, 1249, 20},
};

// ����ؿ�3���컨���
std::vector<CeilingBlock> level3CeilingBlocks = {
	{169, 619, 249, 619},
	{330, 620, 410, 623},
	{410, 481, 569, 481},
	{611, 540, 730, 541},
	{771, 581, 928, 582},
	{1012, 580, 1131, 581},
	{611, 421, 730, 421},
	{771, 360, 889, 361},
	{890, 280, 1009, 281},
	{410, 220, 809, 221},
	{851, 100, 888, 100},
	{891, 141, 1001, 141},
	{1050, 182, 1210, 183},
	{48, 20, 1248, 20},
};


// ��������Ľṹ��
struct TrapBlock {
	int left, top, right, bottom; // ��������ұ߽�����±߽�
};

// ����ؿ�1�ĵش�
std::vector<TrapBlock> level1TrapBlocks = {
	{486, 700, 526, 740},
	{526, 700, 566, 740},
	{566, 700, 606, 740},
	{730, 700, 770, 740},
};

// ����ؿ�2�ĵش�
std::vector<TrapBlock> level2TrapBlocks = {
	{331, 742, 448, 776},
	{531, 743, 648, 777},
	{731, 743, 848, 777},
	{449, 263, 527, 300},
	{689, 261, 769, 299},
};

// ����ؿ�3�ĵش�
std::vector<TrapBlock> level3TrapBlocks = {
	{251, 746, 332, 778},
	{450, 745, 531, 777},
	{609, 745, 689, 778},
	{1010, 740, 1089, 780},
	{168, 140, 250, 179},
};

// ���屦��Ľṹ��
struct TreasureBlock {
	int left, top, right, bottom; // ��������ұ߽�����±߽�
	bool isclose = true;
};

//����ؿ�1�ı���
std::vector<TreasureBlock> level1TreasureBlocks =
{

};

//����ؿ�2�ı���
std::vector<TreasureBlock> level2TreasureBlocks =
{
	{393, 262, 433, 302},
	{593, 262, 633, 302},
	{818, 262, 858, 302},
};

//����ؿ�3�ı���
std::vector<TreasureBlock> level3TreasureBlocks =
{

};

//����ظ�����Ľṹ��
struct HealBlock {
	int left, top, right, bottom; // ����ı߽�
	int healAmount;              // ÿ֡�ָ�������ֵ
};

//����ؿ�1�Ļظ�����
std::vector<HealBlock> level1HealBlocks =
{

};


//����ؿ�3�Ļظ�����
std::vector<HealBlock> level2HealBlocks =
{

};

//����ؿ�3�Ļظ�����
std::vector<HealBlock> level3HealBlocks =
{
	{729, 687, 768, 732, 10},
};


//���崫�ͷ���Ľṹ��
struct TeleportBlock {
	int x1, y1, x2, y2;           // ��һ����������A��
	int targetX1, targetY1, targetX2, targetY2; // �ڶ�����������B��
};

//����ؿ�1�Ĵ��ͷ���
std::vector<TeleportBlock> level1TeleportBlocks = {

};

//����ؿ�2�Ĵ��ͷ���
std::vector<TeleportBlock> level2TeleportBlocks = {

};

//����ؿ�3�Ĵ��ͷ���
std::vector<TeleportBlock> level3TeleportBlocks = {
	{902, 28, 958, 99,
	256, 552, 320, 610},  // A �� B ��ͨ
};

// ����ͨ�ط���Ľṹ��
struct VictoryDoor {
	int left, top, right, bottom; // ͨ�ط�������ұ߽�����±߽�
};

VictoryDoor level1VictoryDoor = { 310, 22, 385, 121 };
VictoryDoor level2VictoryDoor = { 1186, 30, 1234, 97 };
VictoryDoor level3VictoryDoor = { 1185, 68, 1229, 134 };

class Player {
private:
	IMAGE rightImage; // �������ͼƬ
	IMAGE leftImage;  // �������ͼƬ
	int HP = 100;     // ��ҵ�ǰ����ֵ
	int maxHP = 100;  // ����������ֵ
	int x, y;         // ���λ������
	bool facingRight; // ��ҷ���trueΪ�ң�falseΪ��
	bool isJumping = false; // �Ƿ�����Ծ��
	bool doubleJumpAvailable = true; // �Ƿ���Խ��ж�����
	int vy = 0; // ��ֱ�ٶ�
	const int jumpPower = -15; // ��Ծ�ĳ�ʼ�ٶ�
	const int gravity = 1;     // �������ٶ�
	int jumpCooldown = 0;      // ��Ծ��ȴ��ʱ��
	int trapdamage = 10;       // ������˺�
	int treasures = 0;         // ��һ�ñ��������
	int healCooldown = 0; // �ظ���ȴʱ��
	int teleportCooldown = 0; // ������ȴ��ʱ������ʼΪ 0 ��ʾ���Դ���
	const int maxTeleportCooldown = 100; // ��ȴʱ�䣨��λ��֡��

public:
	// ���캯������ʼ�����λ�úͷ���
	Player(int startX, int startY) : x(startX), y(startY), facingRight(true) {}

	// �����������ֵ���������������ֵ
	void setHP(int hp) {
		HP = hp;
		maxHP = hp; // �����������ֵ
	}

	// ��ȡ�������ֵ��������ʾ��
	int getHP() const {
		return HP;
	}

	// �ָ�����ֵ�����ܳ������ֵ
	void heal(int amount) {
		HP = min(HP + amount, maxHP);
	}

	// �������ͼƬ��Դ
	void loadResources() {
		loadimage(&rightImage, L"ͼƬ��Դ/����.png"); // ���ء����ơ�ͼƬ
		loadimage(&leftImage, L"ͼƬ��Դ/����.png");  // ���ء����ơ�ͼƬ
	}

	// �������
	void draw() {
		if (facingRight) {
			putimage(x, y, &rightImage); // ��������ͼƬ
		}
		else {
			putimage(x, y, &leftImage); // ��������ͼƬ
		}
		// ���ƻ�ɫ�� HP ��������Ļ���Ͻ�
		if (HP >= 0) {
			settextcolor(YELLOW);          // ����������ɫΪ��ɫ
			setbkmode(TRANSPARENT);        // ���ñ���ģʽΪ͸��
			settextstyle(50, 0, L"΢���ź�"); // ��������Ϊ΢���źڣ���СΪ50

			wchar_t hpText[20];
			swprintf(hpText, 20, L"HP: %d / %d", HP, maxHP); // ת�� HP ��ֵΪ�ı�
			outtextxy(850, 40, hpText); // ����Ļ���Ͻ���ʾ HP ����
		}
	}

	// ����λ�õĺ���
	void resetPosition() {
		HP = maxHP; // �ָ����������ֵ
		x = 80;     // Ĭ�ϵ� x ����
		y = 700 - 51; // Ĭ�ϵ� y ����
		isJumping = false; // ������Ծ״̬
		doubleJumpAvailable = true; // ���ö�����
		vy = 0; // ���ô�ֱ�ٶ�
	}

	// �������Ƿ�����ͨ����
	bool checkVictory(const VictoryDoor& door) {
		return x + rightImage.getwidth() > door.left &&
			x < door.right &&
			y + rightImage.getheight() > door.top &&
			y < door.bottom;
	}

	// ��ȡ��һ�ñ��������
	int getTreasure() const {
		return treasures;
	}

	void resetTrapDamage(int damage)
	{
		trapdamage = damage;
	}

	// �������λ�ã�����ǽ�ڡ��컨�塢���塢����ͻظ�����ļ�⣩
	void update(const std::vector<GroundBlock>& groundBlocks, const std::vector<WallBlock>& wallBlocks,
		const std::vector<CeilingBlock>& ceilingBlocks, const std::vector<TrapBlock>& trapBlocks,
		std::vector<TreasureBlock>* treasureBlocks, const std::vector<HealBlock>& healBlocks,
		const std::vector<TeleportBlock>& teleportBlocks) {

		int originalX = x; // ��¼����ǰ��X����

		// �����ƶ�
		if (GetAsyncKeyState('A') & 0x8000) {
			x -= 5; // ����
			facingRight = false; // �ı䷽��Ϊ��
		}
		if (GetAsyncKeyState('D') & 0x8000) {
			x += 5; // ����
			facingRight = true; // �ı䷽��Ϊ��
		}

		// ���ǽ����ײ
		for (const auto& wall : wallBlocks) {
			if (x + rightImage.getwidth() > wall.left && x < wall.right &&
				y + rightImage.getheight() > wall.top && y < wall.bottom) {
				// ���������ײ���ָ���֮ǰ��λ��
				x = originalX;
				doubleJumpAvailable = true; // ����ǽ��ʱ���ö�����
				break;
			}
		}

		// ����컨����ײ��������ҽӴ����컨���ײ�����ʱ
		for (const auto& ceiling : ceilingBlocks) {
			int ceilingCollisionBuffer = 5; // ����߶�
			if (vy < 0 && x + rightImage.getwidth() > ceiling.left && x < ceiling.right &&
				y < ceiling.bottom && y + rightImage.getheight() >= ceiling.bottom - ceilingCollisionBuffer) {
				y = ceiling.bottom; // �����ͣ���컨���·�
				vy = 0;             // ֹͣ�����ƶ�
				break;
			}
		}

		// ���ش���ײ
		static int timecount = 0; // ��������˺���CD
		bool iscontactTrap = false; // ��¼�Ƿ�������Ӵ�
		for (const auto& trap : trapBlocks) {
			if (x + rightImage.getwidth() > trap.left && x < trap.right &&
				y + rightImage.getheight() > trap.top && y < trap.bottom) {
				if (timecount == 0) { // ���CDΪ�����Ѫ������CD
					HP -= trapdamage;
					timecount = 10;
				}
				else {
					timecount--;
				}
				iscontactTrap = true;
				break;
			}
		}
		if (!iscontactTrap) timecount = 0;

		// ��鱦�佻��
		if (GetAsyncKeyState('E') & 0x8000) {
			for (auto& treasure : *treasureBlocks) {
				if (x + rightImage.getwidth() + 6 > treasure.left && x < treasure.right + 6 &&
					y + rightImage.getheight() - 6 < treasure.bottom && treasure.isclose) {
					treasures++;
					treasure.isclose = false;
				}
			}
		}

		//���ظ�����
		for (const auto& healBlock : healBlocks) {
			if (x + rightImage.getwidth() > healBlock.left && x < healBlock.right &&
				y + rightImage.getheight() > healBlock.top && y < healBlock.bottom) {
				if (healCooldown == 0) { // ֻ����ȴʱ��Ϊ 0 ʱ������ظ�
					heal(healBlock.healAmount); // ���� heal �����ָ�����ֵ
					healCooldown = 10;         // ������ȴʱ��Ϊ 10 ֡
				}
				else {
					healCooldown--;
				}
				break;
			}
		}

		//��֡������ȴʱ��
		if (teleportCooldown > 0) {
			teleportCooldown--; // ��ȴ��ʱ�ݼ�
		}

		//��鴫�ͷ�����ײ
		for (const auto& teleport : teleportBlocks) {
			// �������� A ���򣬴��͵� B ���򣬲�����ȴ����
			if (teleportCooldown == 0 &&
				x + rightImage.getwidth() > teleport.x1 && x < teleport.x2 &&
				y + rightImage.getheight() > teleport.y1 && y < teleport.y2) {
				x = (teleport.targetX1 + teleport.targetX2) / 2; // ���͵� B ������λ��
				y = (teleport.targetY1 + teleport.targetY2) / 2;
				teleportCooldown = maxTeleportCooldown; // ������ȴʱ��
				break;
			}

			// �������� B ���򣬴��͵� A ���򣬲�����ȴ����
			if (teleportCooldown == 0 &&
				x + rightImage.getwidth() > teleport.targetX1 && x < teleport.targetX2 &&
				y + rightImage.getheight() > teleport.targetY1 && y < teleport.targetY2) {
				x = (teleport.x1 + teleport.x2) / 2; // ���͵� A ������λ��
				y = (teleport.y1 + teleport.y2) / 2;
				teleportCooldown = maxTeleportCooldown; // ������ȴʱ��
				break;
			}
		}

		// ��Ծ�Ͷ�����
		if (GetAsyncKeyState('W') & 0x8000) {
			jump();
		}

		// Ӧ����������Ծ
		applyGravity(groundBlocks);

		// ������Ծ��ȴ
		if (jumpCooldown > 0) {
			jumpCooldown--; // ��ȴʱ��ݼ�
		}
	}

private:
	// ������Ծ
	void jump() {
		if (!isJumping) { // ������Ծ
			isJumping = true;
			vy = jumpPower; // ������Ծ��
			doubleJumpAvailable = true; // ���ö�����
			jumpCooldown = 20;          // ������Ծ��ȴʱ�䣨����20֡��
		}
		else if (doubleJumpAvailable && jumpCooldown == 0) { // ����������û����ȴ
			vy = jumpPower;         // ������Ծ��
			doubleJumpAvailable = false; // ���ö�����
		}
	}

	// Ӧ������
	void applyGravity(const std::vector<GroundBlock>& groundBlocks) {
		const int groundCollisionBuffer = 5; // ����߶�

		// ����ҵ���
		y += vy;
		vy += gravity;

		// ����Ƿ��������ײ������һЩ����
		for (const auto& block : groundBlocks) {
			if (x + rightImage.getwidth() > block.left && x < block.right &&
				y + rightImage.getheight() >= block.top - groundCollisionBuffer &&
				y < block.bottom) {
				y = block.top - rightImage.getheight(); // �����ͣ�ڵ�����
				vy = 0;              // ���ô�ֱ�ٶ�
				isJumping = false;   // ������Ծ״̬
				doubleJumpAvailable = true; // �ָ�������
				break;
			}
		}
	}
};



// ��ť�࣬����ť������͵�����
class Button {
private:
	RECT area; // ��ť�����þ��α�ʾ

public:
	// ���캯������ʼ����ť��λ�úͳߴ�
	Button(int left, int top, int right, int bottom) {
		area = { left, top, right, bottom };
	}

	// �жϰ�ť�Ƿ񱻵��
	bool isClicked(int x, int y) const {
		return PtInRect(&area, POINT{ x, y });
	}
};

// ҳ���࣬����ҳ��ļ��ء����ƺ͵���¼�
class Page {
protected:
	IMAGE backgroundImage; // ����ͼ��
	std::vector<Button> buttons; // �洢ҳ���ϵİ�ť

public:
	// ����ҳ����Դ
	virtual void loadResources(const std::wstring& imagePath) {
		loadimage(&backgroundImage, imagePath.c_str());
	}

	// ����ҳ��
	virtual void draw() {
		putimage((WINDOW_WIDTH - backgroundImage.getwidth()) / 2, (WINDOW_HEIGHT - backgroundImage.getheight()) / 2, &backgroundImage);
	}

	// �������¼������麯������������ʵ��
	virtual void handleClick(int x, int y, MenuPage& currentPage) = 0;
};

// ���˵�ҳ����
class MainMenuPage : public Page {
public:
	MainMenuPage() {
		// ��ʼ����ť����
		buttons.push_back(Button(908, 565, 1127, 610)); // ��ҳ��ť
		buttons.push_back(Button(564, 274, 733, 318));  // �ؿ�ѡ��ť
		buttons.push_back(Button(564, 358, 733, 402));  // ���ð�ť
		buttons.push_back(Button(564, 455, 733, 498));  // �Ѷ�ѡ��ť
		buttons.push_back(Button(564, 543, 733, 587));  // �˳���Ϸ��ť
	}

	// �������¼�
	void handleClick(int x, int y, MenuPage& currentPage) override {
		if (buttons[0].isClicked(x, y)) {
			currentPage = MENU2; // �л������˵�2
		}
		else if (buttons[1].isClicked(x, y)) {
			currentPage = LEVEL_SELECT; // �л����ؿ�ѡ�����
		}
		else if (buttons[2].isClicked(x, y)) {
			currentPage = SETTINGS; // �л������ý���
		}
		else if (buttons[3].isClicked(x, y)) {
			currentPage = DIFFICULTY; // �л����ѶȽ���
		}
		else if (buttons[4].isClicked(x, y)) {
			closegraph(); // �ر�ͼ�δ��ڣ��˳���Ϸ
			exit(0);
		}
	}
};

// ����ҳ���࣬�̳�Page����
class Menu2Page : public Page {
public:
	Menu2Page() {
		buttons.push_back(Button(920, 562, 1024, 624)); // ���ذ�ť
		buttons.push_back(Button(552, 244, 748, 301));  // �淨��ť
		buttons.push_back(Button(552, 340, 748, 395));  // ���а�ť
		buttons.push_back(Button(552, 437, 748, 492));  // �̵갴ť
		buttons.push_back(Button(552, 530, 748, 590));  // �����ŶӰ�ť
	}

	void handleClick(int x, int y, MenuPage& currentPage) override {
		if (buttons[0].isClicked(x, y)) {
			currentPage = MENU1; // ���ص����˵�1
		}
		else if (buttons[1].isClicked(x, y)) {
			currentPage = HOW_TO_PLAY; // �����淨����
		}
		else if (buttons[2].isClicked(x, y)) {
			currentPage = LEADERBOARD; // �������а����
		}
		else if (buttons[3].isClicked(x, y)) {
			currentPage = SHOP; // �����̵����
		}
		else if (buttons[4].isClicked(x, y)) {
			currentPage = ABOUT_TEAM; // ��������Ŷӽ���
		}
	}
};

// �ؿ�ѡ��ҳ����
class LevelSelectPage : public Page {
public:
	LevelSelectPage() {
		buttons.push_back(Button(575, 146, 730, 187)); // ���ذ�ť
		buttons.push_back(Button(919, 405, 1073, 448)); // �����˵Ľ�֯����ť
		buttons.push_back(Button(919, 451, 1073, 495)); // ���������������ť
		buttons.push_back(Button(919, 497, 1073, 541)); // ���ǻ۵���ս����ť���ؿ�3��
	}

	void handleClick(int x, int y, MenuPage& currentPage) override {
		if (buttons[0].isClicked(x, y)) {
			currentPage = MENU1; // ���ص����˵�1
		}
		else if (buttons[1].isClicked(x, y)) {
			currentPage = CROSSING_STORY; // ���롰��Խ���顱ҳ��
		}
		else if (buttons[2].isClicked(x, y)) {
			currentPage = LEVEL2_STORY; // ����ؿ�2����ҳ��
		}
		else if (buttons[3].isClicked(x, y)) {
			currentPage = LEVEL3_STORY; // ����ؿ�3����ҳ��
		}
	}
};

// ����ѡ��ҳ����
class SettingsPage : public Page {
private:
	bool& isMusicOn;
public:
	SettingsPage(bool& musicOn) : isMusicOn(musicOn) {
		buttons.push_back(Button(534, 199, 711, 260)); // ���ذ�ť
		buttons.push_back(Button(813, 309, 1008, 378)); // ���ֿ��ذ�ť
	}

	void handleClick(int x, int y, MenuPage& currentPage) override {
		if (buttons[0].isClicked(x, y)) {
			currentPage = MENU1;
		}
		else if (buttons[1].isClicked(x, y)) {
			isMusicOn = !isMusicOn; // �л�����״̬
			if (isMusicOn) {
				PlaySound(L"������Դ/�˼���.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
			}
			else {
				PlaySound(NULL, NULL, 0);
			}
		}
	}
};

// ��Խ����ҳ����
class CrossingStoryPage : public Page {
public:
	CrossingStoryPage() {
		buttons.push_back(Button(926, 593, 1038, 653)); // ��һҳ��ť
	}

	void handleClick(int x, int y, MenuPage& currentPage) override {
		if (buttons[0].isClicked(x, y)) {
			currentPage = LEVEL1_STORY; // ���롰�ؿ�1���顱ҳ��
		}
	}
};

// �ؿ�1����ҳ����
class Level1StoryPage : public Page {
public:
	Level1StoryPage() {
		buttons.push_back(Button(904, 582, 1018, 643)); // ��һҳ��ť
	}

	void handleClick(int x, int y, MenuPage& currentPage) override {
		if (buttons[0].isClicked(x, y)) {
			currentPage = LEVEL1_MAP; // ���롰�ؿ�1��ͼ��ҳ��
		}
	}
};

// �ؿ�1��ͼҳ���ࣨ�޷��ذ�ť��
class Level1MapPage : public Page {
public:
	Level1MapPage() {
		// ��ҳ���޷��ذ�ť���ؿ�1��ͼ��Ψһ����Ǵӹؿ�1����
	}

	void handleClick(int x, int y, MenuPage& currentPage) override {
		// ��ҳ���޵���¼���Ӧ�������ڹؿ�1��ͼ
	}
};

// �ؿ�2����ҳ����
class Level2StoryPage : public Page {
public:
	Level2StoryPage() {
		buttons.push_back(Button(904, 582, 1018, 643)); // ��һҳ��ť
	}

	void handleClick(int x, int y, MenuPage& currentPage) override {
		if (buttons[0].isClicked(x, y)) {
			currentPage = LEVEL2_MAP; // ���롰�ؿ�2��ͼ��ҳ��
		}
	}
};

// �ؿ�3����ҳ����
class Level3StoryPage : public Page {
public:
	Level3StoryPage() {
		buttons.push_back(Button(904, 582, 1018, 643)); // ��һҳ��ť
	}

	void handleClick(int x, int y, MenuPage& currentPage) override {
		if (buttons[0].isClicked(x, y)) {
			currentPage = LEVEL3_MAP; // ���롰�ؿ�3��ͼ��ҳ��
		}
	}
};

// �ؿ�2��ͼҳ����
class Level2MapPage : public Page {
public:
	Level2MapPage() {
		// ��ҳ���޷��ذ�ť���ؿ�2��ͼ��Ψһ����Ǵӹؿ�2����
	}

	void handleClick(int x, int y, MenuPage& currentPage) override {
		// �޵���¼���Ӧ�������ڹؿ�2��ͼ
	}
};

// �ؿ�3��ͼҳ����
class Level3MapPage : public Page {
public:
	Level3MapPage() {
		// ��ҳ���޷��ذ�ť���ؿ�3��ͼ��Ψһ����Ǵӹؿ�3����
	}

	void handleClick(int x, int y, MenuPage& currentPage) override {
		// �޵���¼���Ӧ�������ڹؿ�3��ͼ
	}
};

// ͨ�ؽ�����
class VictoryPage : public Page {
private:
	MenuPage lastMapPage = MENU1; // ��ʼ��Ϊ MENU1������δ��ʼ���ľ���
	std::vector<IMAGE> imageV;
	Player& player;

public:
	// ���������ͼҳ��ķ���
	void setLastMapPage(MenuPage mapPage) { lastMapPage = mapPage; }

	VictoryPage(Player& player) :player(player) {
		// ��ʼ����ť����
		buttons.push_back(Button(245, 285, 414, 345)); // ���˵���ť
		buttons.push_back(Button(245, 378, 414, 436)); // �½�ѡ��ť
		buttons.push_back(Button(245, 460, 414, 528)); // ��һ�ذ�ť
	}

	// ����ͨ�ؽ������Դ
	void loadResourcesV(const std::wstring& imagePath) {
		Page::loadResources(imagePath); // ���û���ļ��ط���
		imageV.push_back(backgroundImage);
	}

	//����ͨ��ʱ��չʾ��ͬ��ͨ��ʤ������
	void drawV(DWORD& seconds)
	{
		int temp = seconds / 1000;
		if (0 <= temp && temp <= 15)
		{
			putimage((WINDOW_WIDTH - imageV[0].getwidth()) / 2, (WINDOW_HEIGHT - imageV[0].getheight()) / 2, &imageV[0]);
		}
		else if (15 < temp && temp <= 30)
		{
			putimage((WINDOW_WIDTH - imageV[1].getwidth()) / 2, (WINDOW_HEIGHT - imageV[1].getheight()) / 2, &imageV[1]);
		}
		else if (30 < seconds)
		{
			putimage((WINDOW_WIDTH - imageV[2].getwidth()) / 2, (WINDOW_HEIGHT - imageV[2].getheight()) / 2, &imageV[2]);
		}
	}

	// �������¼�
	void handleClick(int x, int y, MenuPage& currentPage) override {
		if (buttons[0].isClicked(x, y)) {
			currentPage = MENU1; // �������˵�
		}
		else if (buttons[1].isClicked(x, y)) {
			currentPage = LEVEL_SELECT; // ���ص��½�ѡ��
		}
		else if (buttons[2].isClicked(x, y)) {
			// ������һ���߼�
			switch (lastMapPage) {
			case LEVEL1_MAP:
				currentPage = LEVEL2_STORY; // ����ؿ�2����ҳ��
				break;
			case LEVEL2_MAP:
				currentPage = LEVEL3_STORY; // ����ؿ�3����ҳ��
				break;
			case LEVEL3_MAP:
			{
				int treasures = player.getTreasure();//��ȡ��ҵõ����������
				switch (treasures)
				{
				case 0://����һ�ñ��������Ϊ0ʱ�����������2
					currentPage = BADEND2;
					break;
				case 1://����һ�ñ��������Ϊ1����2ʱ�����������1
				case 2:
					currentPage = BADEND1;
					break;
				case 3://����һ�ñ��������Ϊ3��ȫ����ʱ�������ý��
					currentPage = GOODEND;
					break;
				}
			}
			break;
			default:
				// �����Ա�̣���������ֵ���������˵�
				currentPage = MENU1;
				break;
			}
		}
	}
};

// ʧ��ҳ��
class FailPage : public Page {
private:
	MenuPage lastMapPage = MENU1; // ��ʼ��Ϊ MENU1������δ��ʼ���ľ���

public:
	// ���������ͼҳ��ķ���
	void setLastMapPage(MenuPage mapPage) { lastMapPage = mapPage; }

	FailPage() { // ���캯��������Ҷ�������
		// ��ʼ����ť����
		buttons.push_back(Button(245, 285, 414, 345)); // ���˵���ť
		buttons.push_back(Button(245, 378, 414, 436)); // �½�ѡ��ť
		buttons.push_back(Button(245, 460, 414, 528)); // ���¿�ʼ
	}

	void handleClick(int x, int y, MenuPage& currentPage) override {
		if (buttons[0].isClicked(x, y)) {
			currentPage = MENU1; // �������˵�
		}
		else if (buttons[1].isClicked(x, y)) {
			currentPage = LEVEL_SELECT; // ���ص��½�ѡ��
		}
		else if (buttons[2].isClicked(x, y)) {
			// ������һ���߼�
			switch (lastMapPage) {
			case LEVEL1_MAP:
				currentPage = LEVEL1_MAP; // ����ؿ�2����ҳ��
				break;
			case LEVEL2_MAP:
				currentPage = LEVEL2_MAP; // ����ؿ�3����ҳ��
				break;
			case LEVEL3_MAP:
				// ����ǹؿ�3��Ĭ�Ͽ��Իص��ؿ�3����
				currentPage = LEVEL3_STORY;
				break;
			default:
				// �����Ա�̣���������ֵ���������˵�
				currentPage = MENU1;
				break;
			}
		}
	}
};

// �Ѷ�ѡ��ҳ��
class DifficultyPage : public Page {
private:
	Player& player; // ������Ҷ��������޸� HP ֵ

public:
	DifficultyPage(Player& p) : player(p) { // ���캯��������Ҷ�������
		buttons.push_back(Button(529, 202, 711, 260)); // ���ذ�ť
		buttons.push_back(Button(545, 290, 750, 350)); // ���°�ť
		buttons.push_back(Button(545, 381, 750, 445)); // ���Ű�ť
		buttons.push_back(Button(545, 473, 750, 535)); // ������ť
	}

	void handleClick(int x, int y, MenuPage& currentPage) override {
		if (buttons[0].isClicked(x, y)) {
			currentPage = MENU1; // ���ص����˵�1
		}
		if (buttons[1].isClicked(x, y)) { // �����Ѷ�
			player.setHP(100); // ������ҵ� HP Ϊ 100
		}
		if (buttons[2].isClicked(x, y)) { // �����Ѷ�
			player.setHP(50); // ������ҵ� HP Ϊ 50
		}
		if (buttons[3].isClicked(x, y)) { // �����Ѷ�
			player.setHP(20); // ������ҵ� HP Ϊ 20
		}
	}
};

// �淨����
class HowToPlayPage : public Page {
public:
	HowToPlayPage() {
		buttons.push_back(Button(515, 180, 790, 240)); // ���ذ�ť
	}

	void handleClick(int x, int y, MenuPage& currentPage) override {
		if (buttons[0].isClicked(x, y)) {
			currentPage = MENU2; // �������˵�2
		}
	}
};

// ���а����  
class LeaderboardPage : public Page {
private:
	std::vector<int> clearancetime{ 0,0,0 };//��¼�����ؿ���ͨ��ʱ�䣬��λΪ��
public:

	LeaderboardPage() {
		buttons.push_back(Button(515, 180, 790, 240)); // ���ذ�ť  
	}

	void handleClick(int x, int y, MenuPage& currentPage) override {
		if (buttons[0].isClicked(x, y)) {
			currentPage = MENU2; // �������˵�2  
		}
	}

	//��¼ͨ��ʱ��
	void recordclearancetime(DWORD& seconds, MenuPage& LEVEL)
	{
		int temp = seconds / 1000;
		switch (LEVEL)
		{
		case LEVEL1_MAP:
			clearancetime[0] = temp;
			break;
		case LEVEL2_MAP:
			clearancetime[1] = temp;
			break;
		case LEVEL3_MAP:
			clearancetime[2] = temp;
			break;
		}
	}

	//�����ļ��е����а���Ϣ
	void updateleaderboard()
	{
		std::vector<int>minimum = readleaderboard();
		for (int i = 0; i < minimum.size(); i++)
		{
			if (clearancetime[i] != 0 && minimum[i] != 0)
			{
				if (minimum[i] > clearancetime[i])
					minimum[i] = clearancetime[i];
			}
			else if (minimum[i] == 0)
				minimum[i] = clearancetime[i];;
		}
		std::ofstream ofile{ "leaderboard.txt", std::ios::out };
		if (!ofile)
		{
			std::cerr << "�����а��ļ�ʧ��" << std::endl;
			exit(1);
		}
		for (int i = 0; i < minimum.size(); i++)
			ofile << minimum[i] << std::endl;
		ofile.close();
	}

	//��ȡ�ļ��е����а���Ϣ
	std::vector<int> readleaderboard()const
	{
		std::vector<int>minimum(3, 0);
		std::ifstream ifile{ "leaderboard.txt", std::ios::in };
		if (!ifile)
		{
			std::cerr << "�����а��ļ�ʧ��" << std::endl;
			exit(1);
		}
		for (int i = 0; i < minimum.size(); i++)
			ifile >> minimum[i];
		ifile.close();
		return minimum;
	}

	//�������а�ĳɼ�
	void drawleader()
	{
		clearancetime = readleaderboard();
		for (int i = 0; i < 3; i++)
		{
			wchar_t num[4];
			setcolor(YELLOW);
			settextstyle(40, 0, L"����");
			setbkmode(TRANSPARENT);
			swprintf(num, 4, L"%d", clearancetime[i]);
			outtextxy(800, 280 + i * 80, num);
			outtextxy(900, 280 + i * 80, L"��");
		}

	}
};

// �̵����
class ShopPage : public Page {
private:
	Player& player;
public:
	ShopPage(Player& player) :player(player) {
		buttons.push_back(Button(246, 189, 468, 250)); // ���ذ�ť
		buttons.push_back(Button(246, 278, 522, 339)); // ���ذ�ť
	}

	void handleClick(int x, int y, MenuPage& currentPage) override {
		if (buttons[0].isClicked(x, y)) {
			currentPage = MENU2; // �������˵�2
		}
		if (buttons[1].isClicked(x, y))
		{
			static bool isinvincible = false;//���þ�̬������������¼����Ƿ������޵�ģʽ
			if (isinvincible)
			{
				player.resetTrapDamage(10);
				isinvincible = false;//����Ϊ���޵�״̬�����Ѷ�Ϊ����
			}
			else
			{
				player.resetTrapDamage(0);
				isinvincible = true;//����Ϊ�޵�״̬
			}

		}

	}
};

//�ý�ֽ���
class GoodEndPage : public Page {
public:
	GoodEndPage() {
		buttons.push_back(Button(708, 581, 853, 648)); // �������˵���ť
		buttons.push_back(Button(869, 581, 1023, 648)); // �ŶӸ��԰�ť
	}

	void handleClick(int x, int y, MenuPage& currentPage) override {
		if (buttons[0].isClicked(x, y)) {
			currentPage = MENU1; // �������˵�1
		}
		if (buttons[1].isClicked(x, y))
		{
			currentPage = FINAL_THANKS_TANGCHAO; // �л����Ƴ��������лҳ��
		}

	}
};

//�Ƴ�������������
class FinalThanksTangchaoPage : public Page {
public:
	FinalThanksTangchaoPage() {
		buttons.push_back(Button(878, 578, 1037, 642)); // "��һҳ"��ť
	}

	void handleClick(int x, int y, MenuPage& currentPage) override {
		if (buttons[0].isClicked(x, y)) {
			currentPage = FINAL_THANKS_GT; // �л���GT��лҳ��
		}
	}
};

//GT������
class FinalThanksGTPage : public Page {
public:
	FinalThanksGTPage() {
		buttons.push_back(Button(878, 578, 1037, 642)); // "�������˵�"��ť
	}

	void handleClick(int x, int y, MenuPage& currentPage) override {
		if (buttons[0].isClicked(x, y)) {
			currentPage = MENU1; // �������˵�
		}
	}
};

//����ֽ���
class BadEndPage : public Page {
public:
	BadEndPage() {
		buttons.push_back(Button(869, 581, 1023, 648)); // �������˵���ť
	}

	void handleClick(int x, int y, MenuPage& currentPage) override {
		if (buttons[0].isClicked(x, y)) {
			currentPage = MENU1;
		}
	}
};

// �����Ŷӽ���
class AboutTeamPage : public Page {
public:
	AboutTeamPage() {
		buttons.push_back(Button(733, 564, 1008, 624)); // ���ذ�ť
	}

	void handleClick(int x, int y, MenuPage& currentPage) override {
		if (buttons[0].isClicked(x, y)) {
			currentPage = MENU2; // �������˵�2
		}
	}
};

// �����Ŷӽ���
class PausePage : public Page {
private:
	MenuPage lastMapPage = MENU1; // ��ʼ��Ϊ MENU1������δ��ʼ���ľ���
	bool ispause = false;
	bool returngame = false;
	bool returnnogame = false;
public:
	PausePage() {
		buttons.push_back(Button(290, 368, 490, 425)); // �������˵�1
		buttons.push_back(Button(550, 368, 750, 425)); // ���ý��水ť
		buttons.push_back(Button(810, 368, 1010, 425)); // ������Ϸ
	}

	// ���������ͼҳ��ķ���
	void setLastMapPage(MenuPage mapPage) { lastMapPage = mapPage; }

	void handleClick(int x, int y, MenuPage& currentPage) override {
		if (buttons[0].isClicked(x, y)) {
			currentPage = MENU1; // �������˵�1
			ispause = false;
			returnnogame = true;
		}
		if (buttons[1].isClicked(x, y)) {
			currentPage = SETTINGS; // ���ý��水ť
			ispause = false;
			returnnogame = true;
		}
		if (buttons[2].isClicked(x, y)) {
			currentPage = lastMapPage; // ������Ϸ
			ispause = false;
			returngame = true;
		}
	}

	//�ж��Ƿ���ͣ��������ͣʱ�����ͣ����
	int isPause(MenuPage& currentPage)
	{
		if (!ispause)
		{
			if (GetAsyncKeyState(27) & 0x8000)
			{
				lastMapPage = currentPage;
				currentPage = PAUSE;
				ispause = true;
				returngame = false;
			}
			if (returngame)
			{
				currentPage = lastMapPage;
			}
		}
		//������ڴ�����ͣ״̬�򷵻�true
		if (ispause)
		{
			return 1;
		}
		else if (returngame)
		{
			returngame = false;
			return 0;
		}
		else if (returnnogame)
		{
			returnnogame = false;
			return 2;
		}
		return 0;
	}
};

// ��Ϸ����
class Game {
private:
	MenuPage currentPage; // ��ǰҳ��
	MainMenuPage mainMenu; // ���˵�ҳ��
	Menu2Page menu2; // ���˵�2
	LevelSelectPage levelSelect; // �ؿ�ѡ��ҳ��
	SettingsPage settings; // ����ҳ��
	DifficultyPage difficulty; // �Ѷ�ѡ��ҳ��
	HowToPlayPage howToPlay; // �淨����
	LeaderboardPage leaderboard; // ���а����
	ShopPage shop; // �̵����
	AboutTeamPage aboutTeam; // �����Ŷӽ���
	CrossingStoryPage crossingStory; // ��Խ����ҳ��
	Level1StoryPage level1Story; // �ؿ�1����ҳ��
	Level1MapPage level1Map; // �ؿ�1��ͼҳ��
	Level2StoryPage level2Story; // �ؿ�2����ҳ��
	Level2MapPage level2Map;     // �ؿ�2��ͼҳ��
	Level3StoryPage level3Story; // �ؿ�3����ҳ��
	Level3MapPage level3Map;     // �ؿ�3��ͼҳ��
	Player player;  // ��Ҷ���
	IMAGE backgroundImage; // ��ӱ���ͼ�����������ʤ������
	VictoryPage victoryPage; // ʤ������
	FailPage failPage; //ʧ��ҳ��
	IMAGE treasureclose;//����ر�
	IMAGE treasureopen;//�����
	GoodEndPage goodendPage;//�ý��ҳ��
	BadEndPage badend1Page;//�����ҳ��1
	BadEndPage badend2Page;//�����ҳ��2
	PausePage pausePage;//��ͣҳ��
	FinalThanksTangchaoPage finalThanksTangchaoPage; // �Ƴ��������л
	FinalThanksGTPage finalThanksGTPage;             // GT��л


public:
	Game() : currentPage(MENU1), player(80, 700 - 51), difficulty(player), settings(isMusicOn), shop(player), victoryPage(player) {} // ��ʼ����ǰҳ��Ϊ���˵�

	// ��������ҳ����Դ
	void loadResources() {
		mainMenu.loadResources(L"ͼƬ��Դ/���˵�1.png");
		menu2.loadResources(L"ͼƬ��Դ/���˵�2.png");
		levelSelect.loadResources(L"ͼƬ��Դ/�ؿ�ѡ�����.png");
		settings.loadResources(L"ͼƬ��Դ/���ý���.png");
		difficulty.loadResources(L"ͼƬ��Դ/�ѶȽ���.png");
		howToPlay.loadResources(L"ͼƬ��Դ/�淨����.png");
		leaderboard.loadResources(L"ͼƬ��Դ/���а����.png");
		shop.loadResources(L"ͼƬ��Դ/�̵����.png");
		aboutTeam.loadResources(L"ͼƬ��Դ/�����Ŷӽ���.png");
		crossingStory.loadResources(L"ͼƬ��Դ/��Խ����.png");
		level1Story.loadResources(L"ͼƬ��Դ/�ؿ�1����.png");
		level1Map.loadResources(L"ͼƬ��Դ/�ؿ�1��ͼ.jpg");
		level2Story.loadResources(L"ͼƬ��Դ/�ؿ�2����.png");
		level2Map.loadResources(L"ͼƬ��Դ/�ؿ�2��ͼ.png");
		level3Story.loadResources(L"ͼƬ��Դ/�ؿ�3����.png");
		level3Map.loadResources(L"ͼƬ��Դ/�ؿ�3��ͼ.jpg");
		player.loadResources(); // ���������Դ
		victoryPage.loadResourcesV(L"ͼƬ��Դ/ʤ������1.png"); // ����ʤ������ͼƬ
		victoryPage.loadResourcesV(L"ͼƬ��Դ/ʤ������2.png"); // ����ʤ������ͼƬ
		victoryPage.loadResourcesV(L"ͼƬ��Դ/ʤ������3.png"); // ����ʤ������ͼƬ
		failPage.loadResources(L"ͼƬ��Դ/ʧ�ܽ���1.png");
		loadimage(&treasureclose, L"ͼƬ��Դ/����ر�.png", 40, 40);
		loadimage(&treasureopen, L"ͼƬ��Դ/�����.png", 40, 40);
		goodendPage.loadResources(L"ͼƬ��Դ/�ý��1.png");
		badend1Page.loadResources(L"ͼƬ��Դ/�����1.png");
		badend2Page.loadResources(L"ͼƬ��Դ/�����2.png");
		pausePage.loadResources(L"ͼƬ��Դ/��ͣ����.png");
		finalThanksTangchaoPage.loadResources(L"ͼƬ��Դ/�������Ƴ�������.png");
		finalThanksGTPage.loadResources(L"ͼƬ��Դ/������GT.png");
	}

	bool isLevelMusicPlaying = false; // ��־λ���ж��Ƿ��ڲ��ŵ�ͼ����
	bool isMusicOn = true; // ȫ�ֱ�������¼���ֿ���״̬����ʼ״̬Ϊ����

	// ���ű�������
	void playBackgroundMusic(const std::wstring& musicFile) {
		if (isMusicOn) { // ֻ�������ֿ��ؿ���������²Ų�������
			PlaySound(musicFile.c_str(), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		}
		else {
			PlaySound(NULL, NULL, 0); // ֹͣ��������
		}
	}

	// ����ҳ�沥�Ų�ͬ������
	void updateBackgroundMusic() {
		if (currentPage == LEVEL1_MAP || currentPage == LEVEL2_MAP || currentPage == LEVEL3_MAP) {
			if (!isLevelMusicPlaying) {
				// �����ͼ�����ҵ�ͼ����δ����ʱ�����ŵ�ͼ����
				playBackgroundMusic(L"������Դ/��˵֮��.wav");
				isLevelMusicPlaying = true; // ��־λ��Ϊ��ͼ�������ڲ���
			}
		}
		else {
			if (isLevelMusicPlaying) {
				// �뿪��ͼ���棬�л�������ҳ��ʱ����Ĭ������
				playBackgroundMusic(L"������Դ/�˼���.wav");
				isLevelMusicPlaying = false; // ��־λ��Ϊ�ǵ�ͼ����
			}
			// ����ڷǵ�ͼ���棬���Ѿ������˼������֣������ٴβ���
		}
	}

	// ���Ƶ�ǰҳ��
	void drawCurrentPage() {
		switch (currentPage) {
		case MENU1:
			mainMenu.draw();
			break;
		case MENU2:
			menu2.draw();
			break;
		case LEVEL_SELECT:
			levelSelect.draw();
			break;
		case SETTINGS:
			settings.draw();
			break;
		case DIFFICULTY:
			difficulty.draw();
			break;
		case HOW_TO_PLAY:
			howToPlay.draw();
			break;
		case LEADERBOARD:
			leaderboard.draw();
			leaderboard.drawleader();
			break;
		case SHOP:
			shop.draw();
			break;
		case ABOUT_TEAM:
			aboutTeam.draw();
			break;
		case CROSSING_STORY:
			crossingStory.draw();
			break;
		case LEVEL1_STORY:
			level1Story.draw();
			break;
		case LEVEL1_MAP:
			level1Map.draw();
			break;
		case LEVEL2_STORY:
			level2Story.draw();
			break;
		case LEVEL2_MAP:
			level2Map.draw();
			break;
		case LEVEL3_STORY:
			level3Story.draw();
			break;
		case LEVEL3_MAP:
			level3Map.draw();
			break;
		case VICTORY_SCREEN: // ͨ�ؽ���
			victoryPage.drawV(seconds);
			break;
		case FAIL:
			failPage.draw();
			break;
		case GOODEND:
			goodendPage.draw();
			break;
		case BADEND1:
			badend1Page.draw();
			break;
		case BADEND2:
			badend2Page.draw();
			break;
		case PAUSE:
			pausePage.draw();
			break;
		case FINAL_THANKS_TANGCHAO:
			finalThanksTangchaoPage.draw();
			break;
		case FINAL_THANKS_GT:
			finalThanksGTPage.draw();
			break;
		}
	}

	// ����������¼�
	void handleMouseClick(int x, int y) {
		MenuPage previousPage = currentPage; // ���� previousPage �������洢��ǰҳ��

		switch (currentPage) {
		case MENU1:
			mainMenu.handleClick(x, y, currentPage);
			break;
		case MENU2:
			menu2.handleClick(x, y, currentPage);
			break;
		case LEVEL_SELECT:
			levelSelect.handleClick(x, y, currentPage);
			break;
		case SETTINGS:
			settings.handleClick(x, y, currentPage);
			break;
		case DIFFICULTY:
			difficulty.handleClick(x, y, currentPage);
			break;
		case HOW_TO_PLAY:
			howToPlay.handleClick(x, y, currentPage);
			break;
		case LEADERBOARD:
			leaderboard.handleClick(x, y, currentPage);
			break;
		case SHOP:
			shop.handleClick(x, y, currentPage);
			break;
		case ABOUT_TEAM:
			aboutTeam.handleClick(x, y, currentPage);
			break;
		case CROSSING_STORY:
			crossingStory.handleClick(x, y, currentPage);
			break;
		case LEVEL1_STORY:
			level1Story.handleClick(x, y, currentPage);
			break;
		case LEVEL1_MAP:
			level1Map.handleClick(x, y, currentPage);
			break;
		case LEVEL2_STORY:
			level2Story.handleClick(x, y, currentPage);
			break;
		case LEVEL2_MAP:
			level2Map.handleClick(x, y, currentPage);
			break;
		case LEVEL3_STORY:
			level3Story.handleClick(x, y, currentPage);
			break;
		case LEVEL3_MAP:
			level3Map.handleClick(x, y, currentPage);
			break;
		case VICTORY_SCREEN: // ʤ������
			victoryPage.handleClick(x, y, currentPage);
			break;
		case FAIL:
			failPage.handleClick(x, y, currentPage);
			break;
		case GOODEND:
			goodendPage.handleClick(x, y, currentPage);
			break;
		case BADEND1:
			badend1Page.handleClick(x, y, currentPage);
			break;
		case BADEND2:
			badend2Page.handleClick(x, y, currentPage);
			break;
		case PAUSE:
			pausePage.handleClick(x, y, currentPage);
			break;
		case FINAL_THANKS_TANGCHAO:
			finalThanksTangchaoPage.handleClick(x, y, currentPage);
			break;
		case FINAL_THANKS_GT:
			finalThanksGTPage.handleClick(x, y, currentPage);
			break;
		}

		if (currentPage != previousPage) {
			updateBackgroundMusic(); // ҳ���л�����±�������
		}
	}


	//�ؿ���ʼʱ��¼��ʼʱ��
	void timeRecordStart(bool& levelStarted, DWORD& startTime, MenuPage& currentPage)
	{
		if (!levelStarted && (currentPage == LEVEL1_MAP || currentPage == LEVEL2_MAP || currentPage == LEVEL3_MAP)) {
			startTime = GetTickCount(); // ��¼��ʼʱ��  
			levelStarted = true; // ���ùؿ��ѿ�ʼ��־  
		}
	}

	void calculateTimeElapsed(DWORD& seconds, DWORD& startTime, MenuPage& currentPage)
	{
		if (currentPage == LEVEL1_MAP || currentPage == LEVEL2_MAP || currentPage == LEVEL3_MAP)
		{
			// ���㲢��ʾʱ��  
			seconds = GetTickCount() - startTime; // ���㾭����ʱ��  
			int temp = seconds / 1000; // ת��Ϊ��  
			// ����Ļ����ʾ������ʱ��  
			std::wstring timeText = L"ʱ��: " + std::to_wstring(temp) + L"��";
			outtextxy(10, 10, timeText.c_str()); // ��ָ��λ�û���ʱ���ı�
		}
	}

	//���ؿ�ͨ����ʧ��ʱ��Ҫʵ���������λ�ú��л����ֵȹ��ܣ������������װ
	void levelFinish()
	{
		player.resetPosition(); // ͨ��ʱ�������λ��  
		playBackgroundMusic(L"������Դ/�˼���.wav"); // ȷ�������˼�������  
		levelStarted = false; // ���ùؿ���ʼ��־
		leaderboard.recordclearancetime(seconds, currentPage);
		leaderboard.updateleaderboard();
	}


	void inTheGame()
	{
		levelStarted = false; // ���ùؿ���ʼ��־
		player.resetPosition();
		timeRecordStart(levelStarted, startTime, currentPage);
		bool istimerecord = true;//��¼�Ƿ���ͣʱ�Ѿ���ȥ��ʱ��
		DWORD temptime = 0;//��¼��ͣʱ�Ѿ���ȥ��ʱ��
		while (true)
		{
			BeginBatchDraw(); // ˫���� 
			cleardevice();
			drawCurrentPage();
			//���Ʊ���
			int choice = pausePage.isPause(currentPage);//���ñ���choice������ͣ�жϷ���ֵ
			if (choice == 0)
			{
				if (istimerecord)
				{
					startTime = GetTickCount() - temptime;
					istimerecord = false;
				}
				for (auto& treasure : *currentTreasureBlocks)
				{
					if (treasure.isclose)
					{
						putimage(treasure.left, treasure.top, &treasureclose); // ���Ʊ���ر�
					}
					else
					{
						putimage(treasure.left, treasure.top, &treasureopen); // ���Ʊ��俪��
					}
				}
				// �ؿ���ʼʱ��¼ʱ��  
				timeRecordStart(levelStarted, startTime, currentPage);
				// ���㵱ǰ�ؿ��Ѿ�����ʱ�䲢չʾ
				calculateTimeElapsed(seconds, startTime, currentPage);
				// ���ºͻ������  
				player.update(*currentGroundBlocks, *currentWallBlocks, *currentCeilingBlocks,
					*currentTrapBlocks, currentTreasureBlocks, *currentHealBlocks, *currentTeleportBlocks);
				player.draw();


				//���������ֵС�ڵ���0ʱ���жϹؿ�ͨ��ʧ��
				if (player.getHP() <= 0)
				{
					failPage.setLastMapPage(currentPage); // ���õ�ǰ��ͼҳ��   
					currentVictoryDoor = nullptr; // ����ͨ���Ŷ���  
					currentPage = FAIL; // �л���ʤ������ 
					levelFinish();
					break;
				}
				/*�����ͨ��ʧ�ܵ��жϺ�����ͨ�ص��ж�Ψһ����������levelFinish()��λ�ò�ͬ��
					levelFinish()��λ�ò�ͬ�ᵼ�����а��Ƿ���¼ʱ��
				*/
				// ���ʤ������  
				if (player.checkVictory(*currentVictoryDoor)) {
					victoryPage.setLastMapPage(currentPage); // ���õ�ǰ��ͼҳ��   
					currentVictoryDoor = nullptr; // ����ͨ���Ŷ���
					levelFinish();
					currentPage = VICTORY_SCREEN; // �л���ʤ������
					break;
				}

				Sleep(5); // ����ˢ��Ƶ�� 
			}
			else if (choice == 1)
			{
				if (!istimerecord)
				{
					temptime = seconds;
					istimerecord = true;
				}
			}
			else if (choice == 2)
			{
				break;
			}

			// ����Ƿ�������¼�  
			if (MouseHit()) {
				MOUSEMSG msg = GetMouseMsg();
				if (msg.uMsg == WM_LBUTTONDOWN) {
					handleMouseClick(msg.x, msg.y);
					//std::cout << msg.x << "," << msg.y << std::endl;
				}
			}

			EndBatchDraw();
		}

	}

	//��Ϸ��ѭ��
	void run() {
		initgraph(WINDOW_WIDTH, WINDOW_HEIGHT); // ��ʼ��ͼ�δ���  
		loadResources(); // ������Դ  
		playBackgroundMusic(L"������Դ/�˼���.wav"); // ��ʼ����Ĭ������  

		while (true) {
			// ���ݵ�ǰҳ��ѡ���ͼ����顢ǽ�ڿ顢�컨����ͨ����  
			if (currentPage == LEVEL1_MAP) {
				currentGroundBlocks = &level1GroundBlocks;
				currentWallBlocks = &level1WallBlocks;
				currentCeilingBlocks = &level1CeilingBlocks;
				currentTrapBlocks = &level1TrapBlocks;
				currentVictoryDoor = &level1VictoryDoor;
				currentTreasureBlocks = &level1TreasureBlocks;
				currentHealBlocks = &level1HealBlocks;
				currentTeleportBlocks = &level1TeleportBlocks;
				inTheGame();
			}
			else if (currentPage == LEVEL2_MAP) {
				currentGroundBlocks = &level2GroundBlocks;
				currentWallBlocks = &level2WallBlocks;
				currentCeilingBlocks = &level2CeilingBlocks;
				currentTrapBlocks = &level2TrapBlocks;
				currentVictoryDoor = &level2VictoryDoor;
				currentTreasureBlocks = &level2TreasureBlocks;
				currentHealBlocks = &level2HealBlocks;
				currentTeleportBlocks = &level2TeleportBlocks;
				inTheGame();
			}
			else if (currentPage == LEVEL3_MAP) {
				currentGroundBlocks = &level3GroundBlocks;
				currentWallBlocks = &level3WallBlocks;
				currentCeilingBlocks = &level3CeilingBlocks;
				currentTrapBlocks = &level3TrapBlocks;
				currentVictoryDoor = &level3VictoryDoor;
				currentTreasureBlocks = &level3TreasureBlocks;
				currentHealBlocks = &level3HealBlocks; // ���عؿ�3�Ļظ�����
				currentTeleportBlocks = &level3TeleportBlocks; // ���عؿ�3�Ĵ�����
				inTheGame();
			}
			BeginBatchDraw(); // ˫����


			// ����Ƿ�������¼�  
			if (MouseHit()) {
				MOUSEMSG msg = GetMouseMsg();
				if (msg.uMsg == WM_LBUTTONDOWN) {
					handleMouseClick(msg.x, msg.y);
					std::cout << msg.x << "," << msg.y << std::endl;
				}
			}
			cleardevice(); // ����  
			drawCurrentPage(); // ���Ƶ�ǰҳ��  
			EndBatchDraw();
		}
		closegraph(); // �ر�ͼ�δ���  
		PlaySound(NULL, NULL, 0); // ֹͣ��������  
	}
private:
	// ��Ӽ�ʱ��صı���  
	DWORD startTime = 0; // �ؿ���ʼʱ��  
	DWORD seconds = 0;//��¼�ؿ�ʱ��
	bool levelStarted = false; // ��ǹؿ��Ƿ��Ѿ���ʼ  
	std::vector<GroundBlock>* currentGroundBlocks = nullptr;
	std::vector<WallBlock>* currentWallBlocks = nullptr;
	std::vector<CeilingBlock>* currentCeilingBlocks = nullptr;
	std::vector<TrapBlock>* currentTrapBlocks = nullptr;
	std::vector<TreasureBlock>* currentTreasureBlocks = nullptr;
	VictoryDoor* currentVictoryDoor = nullptr; // ��ǰ�ؿ���ͨ����  
	std::vector<HealBlock>* currentHealBlocks = nullptr; // ��ǰ�ؿ��� HealBlock
	std::vector<TeleportBlock>* currentTeleportBlocks = nullptr;
};

// ������
int main() {
	Game game;
	game.run();
	return 0;
}