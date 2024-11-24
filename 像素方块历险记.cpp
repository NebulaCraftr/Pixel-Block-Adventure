#include <algorithm> 
#include <graphics.h> // 使用EasyX图形库
#include <windows.h>
#include <mmsystem.h> // 用于播放声音
#include <string>
#include <vector>
#include <fstream> 
#include <sstream>
#include <iostream>
#pragma comment(lib, "winmm.lib") // 链接 winmm 库

// 窗口尺寸
const int WINDOW_WIDTH = 1300;
const int WINDOW_HEIGHT = 800;

// 定义页面类型
enum MenuPage {
	MENU1, MENU2, LEVEL_SELECT, SETTINGS, DIFFICULTY,
	HOW_TO_PLAY, LEADERBOARD, SHOP, ABOUT_TEAM,
	CROSSING_STORY, LEVEL1_STORY, LEVEL1_MAP,
	LEVEL2_STORY, LEVEL2_MAP, LEVEL3_STORY, LEVEL3_MAP,
	VICTORY_SCREEN, // 添加 VICTORY_SCREEN
	FAIL, GOODEND, BADEND1, BADEND2, PAUSE,
	FINAL_THANKS_TANGCHAO, // 新增：完结感言唐朝的宇宙
	FINAL_THANKS_GT       // 新增：完结的感言GT
};

// 定义地面块的结构体
struct GroundBlock {
	int left, top, right, bottom; // 地面块的四个边界坐标
};

// 定义关卡1的地面块
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

// 定义关卡2的地面块
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

// 定义关卡3的地面块
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

// 定义墙壁块的结构体
struct WallBlock {
	int left, top, right, bottom; // 墙壁的左右边界和上下边界
};

// 定义关卡1的墙壁块
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

// 定义关卡2的墙壁块
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

// 定义关卡3的墙壁块
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

// 定义天花板块的结构体
struct CeilingBlock {
	int left, top, right, bottom; // 天花板的左右边界和上下边界
};

// 定义关卡1的天花板块
std::vector<CeilingBlock> level1CeilingBlocks = {
	{931, 580, 1050, 580},
	{1091, 498, 1249, 498},
	{51, 419, 1048, 419},
	{229, 278, 269, 278},
	{269, 160, 467, 160},
	{51, 20, 1249, 20},
};


// 定义关卡2的天花板块
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

// 定义关卡3的天花板块
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


// 定义陷阱的结构体
struct TrapBlock {
	int left, top, right, bottom; // 陷阱的左右边界和上下边界
};

// 定义关卡1的地刺
std::vector<TrapBlock> level1TrapBlocks = {
	{486, 700, 526, 740},
	{526, 700, 566, 740},
	{566, 700, 606, 740},
	{730, 700, 770, 740},
};

// 定义关卡2的地刺
std::vector<TrapBlock> level2TrapBlocks = {
	{331, 742, 448, 776},
	{531, 743, 648, 777},
	{731, 743, 848, 777},
	{449, 263, 527, 300},
	{689, 261, 769, 299},
};

// 定义关卡3的地刺
std::vector<TrapBlock> level3TrapBlocks = {
	{251, 746, 332, 778},
	{450, 745, 531, 777},
	{609, 745, 689, 778},
	{1010, 740, 1089, 780},
	{168, 140, 250, 179},
};

// 定义宝箱的结构体
struct TreasureBlock {
	int left, top, right, bottom; // 陷阱的左右边界和上下边界
	bool isclose = true;
};

//定义关卡1的宝箱
std::vector<TreasureBlock> level1TreasureBlocks =
{

};

//定义关卡2的宝箱
std::vector<TreasureBlock> level2TreasureBlocks =
{
	{393, 262, 433, 302},
	{593, 262, 633, 302},
	{818, 262, 858, 302},
};

//定义关卡3的宝箱
std::vector<TreasureBlock> level3TreasureBlocks =
{

};

//定义回复方块的结构体
struct HealBlock {
	int left, top, right, bottom; // 方块的边界
	int healAmount;              // 每帧恢复的生命值
};

//定义关卡1的回复方块
std::vector<HealBlock> level1HealBlocks =
{

};


//定义关卡3的回复方块
std::vector<HealBlock> level2HealBlocks =
{

};

//定义关卡3的回复方块
std::vector<HealBlock> level3HealBlocks =
{
	{729, 687, 768, 732, 10},
};


//定义传送方块的结构体
struct TeleportBlock {
	int x1, y1, x2, y2;           // 第一个传送区域（A）
	int targetX1, targetY1, targetX2, targetY2; // 第二个传送区域（B）
};

//定义关卡1的传送方块
std::vector<TeleportBlock> level1TeleportBlocks = {

};

//定义关卡2的传送方块
std::vector<TeleportBlock> level2TeleportBlocks = {

};

//定义关卡3的传送方块
std::vector<TeleportBlock> level3TeleportBlocks = {
	{902, 28, 958, 99,
	256, 552, 320, 610},  // A 和 B 互通
};

// 定义通关方块的结构体
struct VictoryDoor {
	int left, top, right, bottom; // 通关方块的左右边界和上下边界
};

VictoryDoor level1VictoryDoor = { 310, 22, 385, 121 };
VictoryDoor level2VictoryDoor = { 1186, 30, 1234, 97 };
VictoryDoor level3VictoryDoor = { 1185, 68, 1229, 134 };

class Player {
private:
	IMAGE rightImage; // 玩家右移图片
	IMAGE leftImage;  // 玩家左移图片
	int HP = 100;     // 玩家当前生命值
	int maxHP = 100;  // 玩家最大生命值
	int x, y;         // 玩家位置坐标
	bool facingRight; // 玩家方向（true为右，false为左）
	bool isJumping = false; // 是否在跳跃中
	bool doubleJumpAvailable = true; // 是否可以进行二段跳
	int vy = 0; // 垂直速度
	const int jumpPower = -15; // 跳跃的初始速度
	const int gravity = 1;     // 重力加速度
	int jumpCooldown = 0;      // 跳跃冷却计时器
	int trapdamage = 10;       // 陷阱的伤害
	int treasures = 0;         // 玩家获得宝箱的数量
	int healCooldown = 0; // 回复冷却时间
	int teleportCooldown = 0; // 传送冷却计时器，初始为 0 表示可以传送
	const int maxTeleportCooldown = 100; // 冷却时间（单位：帧）

public:
	// 构造函数，初始化玩家位置和方向
	Player(int startX, int startY) : x(startX), y(startY), facingRight(true) {}

	// 设置玩家生命值，并更新最大生命值
	void setHP(int hp) {
		HP = hp;
		maxHP = hp; // 更新最大生命值
	}

	// 获取玩家生命值（用于显示）
	int getHP() const {
		return HP;
	}

	// 恢复生命值，不能超过最大值
	void heal(int amount) {
		HP = min(HP + amount, maxHP);
	}

	// 加载玩家图片资源
	void loadResources() {
		loadimage(&rightImage, L"图片资源/右移.png"); // 加载“右移”图片
		loadimage(&leftImage, L"图片资源/左移.png");  // 加载“左移”图片
	}

	// 绘制玩家
	void draw() {
		if (facingRight) {
			putimage(x, y, &rightImage); // 绘制右移图片
		}
		else {
			putimage(x, y, &leftImage); // 绘制左移图片
		}
		// 绘制黄色的 HP 数字在屏幕右上角
		if (HP >= 0) {
			settextcolor(YELLOW);          // 设置字体颜色为黄色
			setbkmode(TRANSPARENT);        // 设置背景模式为透明
			settextstyle(50, 0, L"微软雅黑"); // 设置字体为微软雅黑，大小为50

			wchar_t hpText[20];
			swprintf(hpText, 20, L"HP: %d / %d", HP, maxHP); // 转换 HP 数值为文本
			outtextxy(850, 40, hpText); // 在屏幕右上角显示 HP 数字
		}
	}

	// 重置位置的函数
	void resetPosition() {
		HP = maxHP; // 恢复到最大生命值
		x = 80;     // 默认的 x 坐标
		y = 700 - 51; // 默认的 y 坐标
		isJumping = false; // 重置跳跃状态
		doubleJumpAvailable = true; // 重置二段跳
		vy = 0; // 重置垂直速度
	}

	// 检查玩家是否触碰到通关门
	bool checkVictory(const VictoryDoor& door) {
		return x + rightImage.getwidth() > door.left &&
			x < door.right &&
			y + rightImage.getheight() > door.top &&
			y < door.bottom;
	}

	// 获取玩家获得宝箱的数量
	int getTreasure() const {
		return treasures;
	}

	void resetTrapDamage(int damage)
	{
		trapdamage = damage;
	}

	// 更新玩家位置（加入墙壁、天花板、陷阱、宝箱和回复方块的检测）
	void update(const std::vector<GroundBlock>& groundBlocks, const std::vector<WallBlock>& wallBlocks,
		const std::vector<CeilingBlock>& ceilingBlocks, const std::vector<TrapBlock>& trapBlocks,
		std::vector<TreasureBlock>* treasureBlocks, const std::vector<HealBlock>& healBlocks,
		const std::vector<TeleportBlock>& teleportBlocks) {

		int originalX = x; // 记录更新前的X坐标

		// 左右移动
		if (GetAsyncKeyState('A') & 0x8000) {
			x -= 5; // 左移
			facingRight = false; // 改变方向为左
		}
		if (GetAsyncKeyState('D') & 0x8000) {
			x += 5; // 右移
			facingRight = true; // 改变方向为右
		}

		// 检查墙壁碰撞
		for (const auto& wall : wallBlocks) {
			if (x + rightImage.getwidth() > wall.left && x < wall.right &&
				y + rightImage.getheight() > wall.top && y < wall.bottom) {
				// 如果发生碰撞，恢复到之前的位置
				x = originalX;
				doubleJumpAvailable = true; // 碰到墙壁时重置二段跳
				break;
			}
		}

		// 检查天花板碰撞，仅在玩家接触到天花板块底部区域时
		for (const auto& ceiling : ceilingBlocks) {
			int ceilingCollisionBuffer = 5; // 缓冲高度
			if (vy < 0 && x + rightImage.getwidth() > ceiling.left && x < ceiling.right &&
				y < ceiling.bottom && y + rightImage.getheight() >= ceiling.bottom - ceilingCollisionBuffer) {
				y = ceiling.bottom; // 将玩家停在天花板下方
				vy = 0;             // 停止向上移动
				break;
			}
		}

		// 检查地刺碰撞
		static int timecount = 0; // 陷阱造成伤害的CD
		bool iscontactTrap = false; // 记录是否与陷阱接触
		for (const auto& trap : trapBlocks) {
			if (x + rightImage.getwidth() > trap.left && x < trap.right &&
				y + rightImage.getheight() > trap.top && y < trap.bottom) {
				if (timecount == 0) { // 如果CD为零则扣血并重置CD
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

		// 检查宝箱交互
		if (GetAsyncKeyState('E') & 0x8000) {
			for (auto& treasure : *treasureBlocks) {
				if (x + rightImage.getwidth() + 6 > treasure.left && x < treasure.right + 6 &&
					y + rightImage.getheight() - 6 < treasure.bottom && treasure.isclose) {
					treasures++;
					treasure.isclose = false;
				}
			}
		}

		//检查回复方块
		for (const auto& healBlock : healBlocks) {
			if (x + rightImage.getwidth() > healBlock.left && x < healBlock.right &&
				y + rightImage.getheight() > healBlock.top && y < healBlock.bottom) {
				if (healCooldown == 0) { // 只有冷却时间为 0 时才允许回复
					heal(healBlock.healAmount); // 调用 heal 函数恢复生命值
					healCooldown = 10;         // 设置冷却时间为 10 帧
				}
				else {
					healCooldown--;
				}
				break;
			}
		}

		//逐帧减少冷却时间
		if (teleportCooldown > 0) {
			teleportCooldown--; // 冷却计时递减
		}

		//检查传送方块碰撞
		for (const auto& teleport : teleportBlocks) {
			// 如果玩家在 A 区域，传送到 B 区域，并且冷却结束
			if (teleportCooldown == 0 &&
				x + rightImage.getwidth() > teleport.x1 && x < teleport.x2 &&
				y + rightImage.getheight() > teleport.y1 && y < teleport.y2) {
				x = (teleport.targetX1 + teleport.targetX2) / 2; // 传送到 B 的中心位置
				y = (teleport.targetY1 + teleport.targetY2) / 2;
				teleportCooldown = maxTeleportCooldown; // 重置冷却时间
				break;
			}

			// 如果玩家在 B 区域，传送到 A 区域，并且冷却结束
			if (teleportCooldown == 0 &&
				x + rightImage.getwidth() > teleport.targetX1 && x < teleport.targetX2 &&
				y + rightImage.getheight() > teleport.targetY1 && y < teleport.targetY2) {
				x = (teleport.x1 + teleport.x2) / 2; // 传送到 A 的中心位置
				y = (teleport.y1 + teleport.y2) / 2;
				teleportCooldown = maxTeleportCooldown; // 重置冷却时间
				break;
			}
		}

		// 跳跃和二段跳
		if (GetAsyncKeyState('W') & 0x8000) {
			jump();
		}

		// 应用重力和跳跃
		applyGravity(groundBlocks);

		// 处理跳跃冷却
		if (jumpCooldown > 0) {
			jumpCooldown--; // 冷却时间递减
		}
	}

private:
	// 处理跳跃
	void jump() {
		if (!isJumping) { // 初次跳跃
			isJumping = true;
			vy = jumpPower; // 设置跳跃力
			doubleJumpAvailable = true; // 启用二段跳
			jumpCooldown = 20;          // 设置跳跃冷却时间（比如20帧）
		}
		else if (doubleJumpAvailable && jumpCooldown == 0) { // 二段跳，且没有冷却
			vy = jumpPower;         // 设置跳跃力
			doubleJumpAvailable = false; // 禁用二段跳
		}
	}

	// 应用重力
	void applyGravity(const std::vector<GroundBlock>& groundBlocks) {
		const int groundCollisionBuffer = 5; // 缓冲高度

		// 让玩家掉落
		y += vy;
		vy += gravity;

		// 检查是否与地面碰撞，允许一些缓冲
		for (const auto& block : groundBlocks) {
			if (x + rightImage.getwidth() > block.left && x < block.right &&
				y + rightImage.getheight() >= block.top - groundCollisionBuffer &&
				y < block.bottom) {
				y = block.top - rightImage.getheight(); // 将玩家停在地面上
				vy = 0;              // 重置垂直速度
				isJumping = false;   // 重置跳跃状态
				doubleJumpAvailable = true; // 恢复二段跳
				break;
			}
		}
	}
};



// 按钮类，管理按钮的区域和点击检测
class Button {
private:
	RECT area; // 按钮区域，用矩形表示

public:
	// 构造函数，初始化按钮的位置和尺寸
	Button(int left, int top, int right, int bottom) {
		area = { left, top, right, bottom };
	}

	// 判断按钮是否被点击
	bool isClicked(int x, int y) const {
		return PtInRect(&area, POINT{ x, y });
	}
};

// 页面类，管理页面的加载、绘制和点击事件
class Page {
protected:
	IMAGE backgroundImage; // 背景图像
	std::vector<Button> buttons; // 存储页面上的按钮

public:
	// 加载页面资源
	virtual void loadResources(const std::wstring& imagePath) {
		loadimage(&backgroundImage, imagePath.c_str());
	}

	// 绘制页面
	virtual void draw() {
		putimage((WINDOW_WIDTH - backgroundImage.getwidth()) / 2, (WINDOW_HEIGHT - backgroundImage.getheight()) / 2, &backgroundImage);
	}

	// 处理点击事件，纯虚函数，需由子类实现
	virtual void handleClick(int x, int y, MenuPage& currentPage) = 0;
};

// 主菜单页面类
class MainMenuPage : public Page {
public:
	MainMenuPage() {
		// 初始化按钮区域
		buttons.push_back(Button(908, 565, 1127, 610)); // 翻页按钮
		buttons.push_back(Button(564, 274, 733, 318));  // 关卡选择按钮
		buttons.push_back(Button(564, 358, 733, 402));  // 设置按钮
		buttons.push_back(Button(564, 455, 733, 498));  // 难度选择按钮
		buttons.push_back(Button(564, 543, 733, 587));  // 退出游戏按钮
	}

	// 处理点击事件
	void handleClick(int x, int y, MenuPage& currentPage) override {
		if (buttons[0].isClicked(x, y)) {
			currentPage = MENU2; // 切换到主菜单2
		}
		else if (buttons[1].isClicked(x, y)) {
			currentPage = LEVEL_SELECT; // 切换到关卡选择界面
		}
		else if (buttons[2].isClicked(x, y)) {
			currentPage = SETTINGS; // 切换到设置界面
		}
		else if (buttons[3].isClicked(x, y)) {
			currentPage = DIFFICULTY; // 切换到难度界面
		}
		else if (buttons[4].isClicked(x, y)) {
			closegraph(); // 关闭图形窗口，退出游戏
			exit(0);
		}
	}
};

// 其他页面类，继承Page基类
class Menu2Page : public Page {
public:
	Menu2Page() {
		buttons.push_back(Button(920, 562, 1024, 624)); // 返回按钮
		buttons.push_back(Button(552, 244, 748, 301));  // 玩法按钮
		buttons.push_back(Button(552, 340, 748, 395));  // 排行榜按钮
		buttons.push_back(Button(552, 437, 748, 492));  // 商店按钮
		buttons.push_back(Button(552, 530, 748, 590));  // 开发团队按钮
	}

	void handleClick(int x, int y, MenuPage& currentPage) override {
		if (buttons[0].isClicked(x, y)) {
			currentPage = MENU1; // 返回到主菜单1
		}
		else if (buttons[1].isClicked(x, y)) {
			currentPage = HOW_TO_PLAY; // 进入玩法界面
		}
		else if (buttons[2].isClicked(x, y)) {
			currentPage = LEADERBOARD; // 进入排行榜界面
		}
		else if (buttons[3].isClicked(x, y)) {
			currentPage = SHOP; // 进入商店界面
		}
		else if (buttons[4].isClicked(x, y)) {
			currentPage = ABOUT_TEAM; // 进入关于团队界面
		}
	}
};

// 关卡选择页面类
class LevelSelectPage : public Page {
public:
	LevelSelectPage() {
		buttons.push_back(Button(575, 146, 730, 187)); // 返回按钮
		buttons.push_back(Button(919, 405, 1073, 448)); // “命运的交织”按钮
		buttons.push_back(Button(919, 451, 1073, 495)); // “真理的试炼”按钮
		buttons.push_back(Button(919, 497, 1073, 541)); // “智慧的挑战”按钮（关卡3）
	}

	void handleClick(int x, int y, MenuPage& currentPage) override {
		if (buttons[0].isClicked(x, y)) {
			currentPage = MENU1; // 返回到主菜单1
		}
		else if (buttons[1].isClicked(x, y)) {
			currentPage = CROSSING_STORY; // 进入“穿越剧情”页面
		}
		else if (buttons[2].isClicked(x, y)) {
			currentPage = LEVEL2_STORY; // 进入关卡2剧情页面
		}
		else if (buttons[3].isClicked(x, y)) {
			currentPage = LEVEL3_STORY; // 进入关卡3剧情页面
		}
	}
};

// 设置选择页面类
class SettingsPage : public Page {
private:
	bool& isMusicOn;
public:
	SettingsPage(bool& musicOn) : isMusicOn(musicOn) {
		buttons.push_back(Button(534, 199, 711, 260)); // 返回按钮
		buttons.push_back(Button(813, 309, 1008, 378)); // 音乐开关按钮
	}

	void handleClick(int x, int y, MenuPage& currentPage) override {
		if (buttons[0].isClicked(x, y)) {
			currentPage = MENU1;
		}
		else if (buttons[1].isClicked(x, y)) {
			isMusicOn = !isMusicOn; // 切换音乐状态
			if (isMusicOn) {
				PlaySound(L"音乐资源/人间日.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
			}
			else {
				PlaySound(NULL, NULL, 0);
			}
		}
	}
};

// 穿越剧情页面类
class CrossingStoryPage : public Page {
public:
	CrossingStoryPage() {
		buttons.push_back(Button(926, 593, 1038, 653)); // 下一页按钮
	}

	void handleClick(int x, int y, MenuPage& currentPage) override {
		if (buttons[0].isClicked(x, y)) {
			currentPage = LEVEL1_STORY; // 进入“关卡1剧情”页面
		}
	}
};

// 关卡1剧情页面类
class Level1StoryPage : public Page {
public:
	Level1StoryPage() {
		buttons.push_back(Button(904, 582, 1018, 643)); // 下一页按钮
	}

	void handleClick(int x, int y, MenuPage& currentPage) override {
		if (buttons[0].isClicked(x, y)) {
			currentPage = LEVEL1_MAP; // 进入“关卡1地图”页面
		}
	}
};

// 关卡1地图页面类（无返回按钮）
class Level1MapPage : public Page {
public:
	Level1MapPage() {
		// 此页面无返回按钮，关卡1地图的唯一入口是从关卡1剧情
	}

	void handleClick(int x, int y, MenuPage& currentPage) override {
		// 此页面无点击事件响应，保持在关卡1地图
	}
};

// 关卡2剧情页面类
class Level2StoryPage : public Page {
public:
	Level2StoryPage() {
		buttons.push_back(Button(904, 582, 1018, 643)); // 下一页按钮
	}

	void handleClick(int x, int y, MenuPage& currentPage) override {
		if (buttons[0].isClicked(x, y)) {
			currentPage = LEVEL2_MAP; // 进入“关卡2地图”页面
		}
	}
};

// 关卡3剧情页面类
class Level3StoryPage : public Page {
public:
	Level3StoryPage() {
		buttons.push_back(Button(904, 582, 1018, 643)); // 下一页按钮
	}

	void handleClick(int x, int y, MenuPage& currentPage) override {
		if (buttons[0].isClicked(x, y)) {
			currentPage = LEVEL3_MAP; // 进入“关卡3地图”页面
		}
	}
};

// 关卡2地图页面类
class Level2MapPage : public Page {
public:
	Level2MapPage() {
		// 此页面无返回按钮，关卡2地图的唯一入口是从关卡2剧情
	}

	void handleClick(int x, int y, MenuPage& currentPage) override {
		// 无点击事件响应，保持在关卡2地图
	}
};

// 关卡3地图页面类
class Level3MapPage : public Page {
public:
	Level3MapPage() {
		// 此页面无返回按钮，关卡3地图的唯一入口是从关卡3剧情
	}

	void handleClick(int x, int y, MenuPage& currentPage) override {
		// 无点击事件响应，保持在关卡3地图
	}
};

// 通关界面类
class VictoryPage : public Page {
private:
	MenuPage lastMapPage = MENU1; // 初始化为 MENU1，避免未初始化的警告
	std::vector<IMAGE> imageV;
	Player& player;

public:
	// 设置最近地图页面的方法
	void setLastMapPage(MenuPage mapPage) { lastMapPage = mapPage; }

	VictoryPage(Player& player) :player(player) {
		// 初始化按钮区域
		buttons.push_back(Button(245, 285, 414, 345)); // 主菜单按钮
		buttons.push_back(Button(245, 378, 414, 436)); // 章节选择按钮
		buttons.push_back(Button(245, 460, 414, 528)); // 下一关按钮
	}

	// 加载通关界面的资源
	void loadResourcesV(const std::wstring& imagePath) {
		Page::loadResources(imagePath); // 调用基类的加载方法
		imageV.push_back(backgroundImage);
	}

	//根据通关时间展示不同的通关胜利界面
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

	// 处理点击事件
	void handleClick(int x, int y, MenuPage& currentPage) override {
		if (buttons[0].isClicked(x, y)) {
			currentPage = MENU1; // 返回主菜单
		}
		else if (buttons[1].isClicked(x, y)) {
			currentPage = LEVEL_SELECT; // 返回到章节选择
		}
		else if (buttons[2].isClicked(x, y)) {
			// 进入下一关逻辑
			switch (lastMapPage) {
			case LEVEL1_MAP:
				currentPage = LEVEL2_STORY; // 进入关卡2剧情页面
				break;
			case LEVEL2_MAP:
				currentPage = LEVEL3_STORY; // 进入关卡3剧情页面
				break;
			case LEVEL3_MAP:
			{
				int treasures = player.getTreasure();//获取玩家得到宝箱的数量
				switch (treasures)
				{
				case 0://当玩家获得宝箱的数量为0时，触发坏结局2
					currentPage = BADEND2;
					break;
				case 1://当玩家获得宝箱的数量为1或者2时，触发坏结局1
				case 2:
					currentPage = BADEND1;
					break;
				case 3://当玩家获得宝箱的数量为3（全部）时，触发好结局
					currentPage = GOODEND;
					break;
				}
			}
			break;
			default:
				// 防御性编程：如果意外的值，返回主菜单
				currentPage = MENU1;
				break;
			}
		}
	}
};

// 失败页面
class FailPage : public Page {
private:
	MenuPage lastMapPage = MENU1; // 初始化为 MENU1，避免未初始化的警告

public:
	// 设置最近地图页面的方法
	void setLastMapPage(MenuPage mapPage) { lastMapPage = mapPage; }

	FailPage() { // 构造函数接收玩家对象引用
		// 初始化按钮区域
		buttons.push_back(Button(245, 285, 414, 345)); // 主菜单按钮
		buttons.push_back(Button(245, 378, 414, 436)); // 章节选择按钮
		buttons.push_back(Button(245, 460, 414, 528)); // 重新开始
	}

	void handleClick(int x, int y, MenuPage& currentPage) override {
		if (buttons[0].isClicked(x, y)) {
			currentPage = MENU1; // 返回主菜单
		}
		else if (buttons[1].isClicked(x, y)) {
			currentPage = LEVEL_SELECT; // 返回到章节选择
		}
		else if (buttons[2].isClicked(x, y)) {
			// 进入下一关逻辑
			switch (lastMapPage) {
			case LEVEL1_MAP:
				currentPage = LEVEL1_MAP; // 进入关卡2剧情页面
				break;
			case LEVEL2_MAP:
				currentPage = LEVEL2_MAP; // 进入关卡3剧情页面
				break;
			case LEVEL3_MAP:
				// 如果是关卡3，默认可以回到关卡3剧情
				currentPage = LEVEL3_STORY;
				break;
			default:
				// 防御性编程：如果意外的值，返回主菜单
				currentPage = MENU1;
				break;
			}
		}
	}
};

// 难度选择页面
class DifficultyPage : public Page {
private:
	Player& player; // 引用玩家对象，用于修改 HP 值

public:
	DifficultyPage(Player& p) : player(p) { // 构造函数接收玩家对象引用
		buttons.push_back(Button(529, 202, 711, 260)); // 返回按钮
		buttons.push_back(Button(545, 290, 750, 350)); // 萌新按钮
		buttons.push_back(Button(545, 381, 750, 445)); // 入门按钮
		buttons.push_back(Button(545, 473, 750, 535)); // 熟练按钮
	}

	void handleClick(int x, int y, MenuPage& currentPage) override {
		if (buttons[0].isClicked(x, y)) {
			currentPage = MENU1; // 返回到主菜单1
		}
		if (buttons[1].isClicked(x, y)) { // 萌新难度
			player.setHP(100); // 设置玩家的 HP 为 100
		}
		if (buttons[2].isClicked(x, y)) { // 入门难度
			player.setHP(50); // 设置玩家的 HP 为 50
		}
		if (buttons[3].isClicked(x, y)) { // 熟练难度
			player.setHP(20); // 设置玩家的 HP 为 20
		}
	}
};

// 玩法界面
class HowToPlayPage : public Page {
public:
	HowToPlayPage() {
		buttons.push_back(Button(515, 180, 790, 240)); // 返回按钮
	}

	void handleClick(int x, int y, MenuPage& currentPage) override {
		if (buttons[0].isClicked(x, y)) {
			currentPage = MENU2; // 返回主菜单2
		}
	}
};

// 排行榜界面  
class LeaderboardPage : public Page {
private:
	std::vector<int> clearancetime{ 0,0,0 };//记录三个关卡的通关时间，单位为秒
public:

	LeaderboardPage() {
		buttons.push_back(Button(515, 180, 790, 240)); // 返回按钮  
	}

	void handleClick(int x, int y, MenuPage& currentPage) override {
		if (buttons[0].isClicked(x, y)) {
			currentPage = MENU2; // 返回主菜单2  
		}
	}

	//记录通关时间
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

	//更新文件中的排行榜信息
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
			std::cerr << "打开排行榜文件失败" << std::endl;
			exit(1);
		}
		for (int i = 0; i < minimum.size(); i++)
			ofile << minimum[i] << std::endl;
		ofile.close();
	}

	//获取文件中的排行榜信息
	std::vector<int> readleaderboard()const
	{
		std::vector<int>minimum(3, 0);
		std::ifstream ifile{ "leaderboard.txt", std::ios::in };
		if (!ifile)
		{
			std::cerr << "打开排行榜文件失败" << std::endl;
			exit(1);
		}
		for (int i = 0; i < minimum.size(); i++)
			ifile >> minimum[i];
		ifile.close();
		return minimum;
	}

	//绘制排行榜的成绩
	void drawleader()
	{
		clearancetime = readleaderboard();
		for (int i = 0; i < 3; i++)
		{
			wchar_t num[4];
			setcolor(YELLOW);
			settextstyle(40, 0, L"宋体");
			setbkmode(TRANSPARENT);
			swprintf(num, 4, L"%d", clearancetime[i]);
			outtextxy(800, 280 + i * 80, num);
			outtextxy(900, 280 + i * 80, L"秒");
		}

	}
};

// 商店界面
class ShopPage : public Page {
private:
	Player& player;
public:
	ShopPage(Player& player) :player(player) {
		buttons.push_back(Button(246, 189, 468, 250)); // 返回按钮
		buttons.push_back(Button(246, 278, 522, 339)); // 返回按钮
	}

	void handleClick(int x, int y, MenuPage& currentPage) override {
		if (buttons[0].isClicked(x, y)) {
			currentPage = MENU2; // 返回主菜单2
		}
		if (buttons[1].isClicked(x, y))
		{
			static bool isinvincible = false;//设置静态布尔变量来记录玩家是否开启了无敌模式
			if (isinvincible)
			{
				player.resetTrapDamage(10);
				isinvincible = false;//重置为不无敌状态并且难度为萌新
			}
			else
			{
				player.resetTrapDamage(0);
				isinvincible = true;//重置为无敌状态
			}

		}

	}
};

//好结局界面
class GoodEndPage : public Page {
public:
	GoodEndPage() {
		buttons.push_back(Button(708, 581, 853, 648)); // 返回主菜单按钮
		buttons.push_back(Button(869, 581, 1023, 648)); // 团队感言按钮
	}

	void handleClick(int x, int y, MenuPage& currentPage) override {
		if (buttons[0].isClicked(x, y)) {
			currentPage = MENU1; // 返回主菜单1
		}
		if (buttons[1].isClicked(x, y))
		{
			currentPage = FINAL_THANKS_TANGCHAO; // 切换到唐朝的宇宙感谢页面
		}

	}
};

//唐朝的宇宙完结感言
class FinalThanksTangchaoPage : public Page {
public:
	FinalThanksTangchaoPage() {
		buttons.push_back(Button(878, 578, 1037, 642)); // "下一页"按钮
	}

	void handleClick(int x, int y, MenuPage& currentPage) override {
		if (buttons[0].isClicked(x, y)) {
			currentPage = FINAL_THANKS_GT; // 切换到GT感谢页面
		}
	}
};

//GT完结感言
class FinalThanksGTPage : public Page {
public:
	FinalThanksGTPage() {
		buttons.push_back(Button(878, 578, 1037, 642)); // "返回主菜单"按钮
	}

	void handleClick(int x, int y, MenuPage& currentPage) override {
		if (buttons[0].isClicked(x, y)) {
			currentPage = MENU1; // 返回主菜单
		}
	}
};

//坏结局界面
class BadEndPage : public Page {
public:
	BadEndPage() {
		buttons.push_back(Button(869, 581, 1023, 648)); // 返回主菜单按钮
	}

	void handleClick(int x, int y, MenuPage& currentPage) override {
		if (buttons[0].isClicked(x, y)) {
			currentPage = MENU1;
		}
	}
};

// 关于团队界面
class AboutTeamPage : public Page {
public:
	AboutTeamPage() {
		buttons.push_back(Button(733, 564, 1008, 624)); // 返回按钮
	}

	void handleClick(int x, int y, MenuPage& currentPage) override {
		if (buttons[0].isClicked(x, y)) {
			currentPage = MENU2; // 返回主菜单2
		}
	}
};

// 关于团队界面
class PausePage : public Page {
private:
	MenuPage lastMapPage = MENU1; // 初始化为 MENU1，避免未初始化的警告
	bool ispause = false;
	bool returngame = false;
	bool returnnogame = false;
public:
	PausePage() {
		buttons.push_back(Button(290, 368, 490, 425)); // 返回主菜单1
		buttons.push_back(Button(550, 368, 750, 425)); // 设置界面按钮
		buttons.push_back(Button(810, 368, 1010, 425)); // 返回游戏
	}

	// 设置最近地图页面的方法
	void setLastMapPage(MenuPage mapPage) { lastMapPage = mapPage; }

	void handleClick(int x, int y, MenuPage& currentPage) override {
		if (buttons[0].isClicked(x, y)) {
			currentPage = MENU1; // 返回主菜单1
			ispause = false;
			returnnogame = true;
		}
		if (buttons[1].isClicked(x, y)) {
			currentPage = SETTINGS; // 设置界面按钮
			ispause = false;
			returnnogame = true;
		}
		if (buttons[2].isClicked(x, y)) {
			currentPage = lastMapPage; // 返回游戏
			ispause = false;
			returngame = true;
		}
	}

	//判断是否暂停，并在暂停时输出暂停界面
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
		//如果现在处于暂停状态则返回true
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

// 游戏主类
class Game {
private:
	MenuPage currentPage; // 当前页面
	MainMenuPage mainMenu; // 主菜单页面
	Menu2Page menu2; // 主菜单2
	LevelSelectPage levelSelect; // 关卡选择页面
	SettingsPage settings; // 设置页面
	DifficultyPage difficulty; // 难度选择页面
	HowToPlayPage howToPlay; // 玩法界面
	LeaderboardPage leaderboard; // 排行榜界面
	ShopPage shop; // 商店界面
	AboutTeamPage aboutTeam; // 关于团队界面
	CrossingStoryPage crossingStory; // 穿越剧情页面
	Level1StoryPage level1Story; // 关卡1剧情页面
	Level1MapPage level1Map; // 关卡1地图页面
	Level2StoryPage level2Story; // 关卡2剧情页面
	Level2MapPage level2Map;     // 关卡2地图页面
	Level3StoryPage level3Story; // 关卡3剧情页面
	Level3MapPage level3Map;     // 关卡3地图页面
	Player player;  // 玩家对象
	IMAGE backgroundImage; // 添加背景图像变量，用于胜利界面
	VictoryPage victoryPage; // 胜利界面
	FailPage failPage; //失败页面
	IMAGE treasureclose;//宝箱关闭
	IMAGE treasureopen;//宝箱打开
	GoodEndPage goodendPage;//好结局页面
	BadEndPage badend1Page;//坏结局页面1
	BadEndPage badend2Page;//坏结局页面2
	PausePage pausePage;//暂停页面
	FinalThanksTangchaoPage finalThanksTangchaoPage; // 唐朝的宇宙感谢
	FinalThanksGTPage finalThanksGTPage;             // GT感谢


public:
	Game() : currentPage(MENU1), player(80, 700 - 51), difficulty(player), settings(isMusicOn), shop(player), victoryPage(player) {} // 初始化当前页面为主菜单

	// 加载所有页面资源
	void loadResources() {
		mainMenu.loadResources(L"图片资源/主菜单1.png");
		menu2.loadResources(L"图片资源/主菜单2.png");
		levelSelect.loadResources(L"图片资源/关卡选择界面.png");
		settings.loadResources(L"图片资源/设置界面.png");
		difficulty.loadResources(L"图片资源/难度界面.png");
		howToPlay.loadResources(L"图片资源/玩法界面.png");
		leaderboard.loadResources(L"图片资源/排行榜界面.png");
		shop.loadResources(L"图片资源/商店界面.png");
		aboutTeam.loadResources(L"图片资源/开发团队界面.png");
		crossingStory.loadResources(L"图片资源/穿越剧情.png");
		level1Story.loadResources(L"图片资源/关卡1剧情.png");
		level1Map.loadResources(L"图片资源/关卡1地图.jpg");
		level2Story.loadResources(L"图片资源/关卡2剧情.png");
		level2Map.loadResources(L"图片资源/关卡2地图.png");
		level3Story.loadResources(L"图片资源/关卡3剧情.png");
		level3Map.loadResources(L"图片资源/关卡3地图.jpg");
		player.loadResources(); // 加载玩家资源
		victoryPage.loadResourcesV(L"图片资源/胜利界面1.png"); // 加载胜利界面图片
		victoryPage.loadResourcesV(L"图片资源/胜利界面2.png"); // 加载胜利界面图片
		victoryPage.loadResourcesV(L"图片资源/胜利界面3.png"); // 加载胜利界面图片
		failPage.loadResources(L"图片资源/失败界面1.png");
		loadimage(&treasureclose, L"图片资源/宝箱关闭.png", 40, 40);
		loadimage(&treasureopen, L"图片资源/宝箱打开.png", 40, 40);
		goodendPage.loadResources(L"图片资源/好结局1.png");
		badend1Page.loadResources(L"图片资源/坏结局1.png");
		badend2Page.loadResources(L"图片资源/坏结局2.png");
		pausePage.loadResources(L"图片资源/暂停界面.png");
		finalThanksTangchaoPage.loadResources(L"图片资源/完结感言唐朝的宇宙.png");
		finalThanksGTPage.loadResources(L"图片资源/完结感言GT.png");
	}

	bool isLevelMusicPlaying = false; // 标志位，判断是否在播放地图音乐
	bool isMusicOn = true; // 全局变量，记录音乐开关状态，初始状态为开启

	// 播放背景音乐
	void playBackgroundMusic(const std::wstring& musicFile) {
		if (isMusicOn) { // 只有在音乐开关开启的情况下才播放音乐
			PlaySound(musicFile.c_str(), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		}
		else {
			PlaySound(NULL, NULL, 0); // 停止播放音乐
		}
	}

	// 根据页面播放不同的音乐
	void updateBackgroundMusic() {
		if (currentPage == LEVEL1_MAP || currentPage == LEVEL2_MAP || currentPage == LEVEL3_MAP) {
			if (!isLevelMusicPlaying) {
				// 进入地图界面且地图音乐未播放时，播放地图音乐
				playBackgroundMusic(L"音乐资源/传说之下.wav");
				isLevelMusicPlaying = true; // 标志位设为地图音乐正在播放
			}
		}
		else {
			if (isLevelMusicPlaying) {
				// 离开地图界面，切换回其他页面时播放默认音乐
				playBackgroundMusic(L"音乐资源/人间日.wav");
				isLevelMusicPlaying = false; // 标志位设为非地图音乐
			}
			// 如果在非地图界面，且已经播放人间日音乐，无需再次播放
		}
	}

	// 绘制当前页面
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
		case VICTORY_SCREEN: // 通关界面
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

	// 处理鼠标点击事件
	void handleMouseClick(int x, int y) {
		MenuPage previousPage = currentPage; // 定义 previousPage 变量，存储当前页面

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
		case VICTORY_SCREEN: // 胜利界面
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
			updateBackgroundMusic(); // 页面切换后更新背景音乐
		}
	}


	//关卡开始时记录开始时间
	void timeRecordStart(bool& levelStarted, DWORD& startTime, MenuPage& currentPage)
	{
		if (!levelStarted && (currentPage == LEVEL1_MAP || currentPage == LEVEL2_MAP || currentPage == LEVEL3_MAP)) {
			startTime = GetTickCount(); // 记录开始时间  
			levelStarted = true; // 设置关卡已开始标志  
		}
	}

	void calculateTimeElapsed(DWORD& seconds, DWORD& startTime, MenuPage& currentPage)
	{
		if (currentPage == LEVEL1_MAP || currentPage == LEVEL2_MAP || currentPage == LEVEL3_MAP)
		{
			// 计算并显示时间  
			seconds = GetTickCount() - startTime; // 计算经过的时间  
			int temp = seconds / 1000; // 转换为秒  
			// 在屏幕上显示经过的时间  
			std::wstring timeText = L"时间: " + std::to_wstring(temp) + L"秒";
			outtextxy(10, 10, timeText.c_str()); // 在指定位置绘制时间文本
		}
	}

	//当关卡通过或失败时需要实现重置玩家位置和切换音乐等功能，用这个方法封装
	void levelFinish()
	{
		player.resetPosition(); // 通关时重置玩家位置  
		playBackgroundMusic(L"音乐资源/人间日.wav"); // 确保播放人间日音乐  
		levelStarted = false; // 重置关卡开始标志
		leaderboard.recordclearancetime(seconds, currentPage);
		leaderboard.updateleaderboard();
	}


	void inTheGame()
	{
		levelStarted = false; // 重置关卡开始标志
		player.resetPosition();
		timeRecordStart(levelStarted, startTime, currentPage);
		bool istimerecord = true;//记录是否暂停时已经过去的时间
		DWORD temptime = 0;//记录暂停时已经过去的时间
		while (true)
		{
			BeginBatchDraw(); // 双缓存 
			cleardevice();
			drawCurrentPage();
			//绘制宝箱
			int choice = pausePage.isPause(currentPage);//设置变量choice储存暂停判断返回值
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
						putimage(treasure.left, treasure.top, &treasureclose); // 绘制宝箱关闭
					}
					else
					{
						putimage(treasure.left, treasure.top, &treasureopen); // 绘制宝箱开启
					}
				}
				// 关卡开始时记录时间  
				timeRecordStart(levelStarted, startTime, currentPage);
				// 计算当前关卡已经过的时间并展示
				calculateTimeElapsed(seconds, startTime, currentPage);
				// 更新和绘制玩家  
				player.update(*currentGroundBlocks, *currentWallBlocks, *currentCeilingBlocks,
					*currentTrapBlocks, currentTreasureBlocks, *currentHealBlocks, *currentTeleportBlocks);
				player.draw();


				//当玩家生命值小于等于0时，判断关卡通关失败
				if (player.getHP() <= 0)
				{
					failPage.setLastMapPage(currentPage); // 设置当前地图页面   
					currentVictoryDoor = nullptr; // 重置通关门对象  
					currentPage = FAIL; // 切换到胜利界面 
					levelFinish();
					break;
				}
				/*上面的通关失败的判断和下面通关的判断唯一的区别在于levelFinish()的位置不同，
					levelFinish()的位置不同会导致排行榜是否会记录时间
				*/
				// 检查胜利条件  
				if (player.checkVictory(*currentVictoryDoor)) {
					victoryPage.setLastMapPage(currentPage); // 设置当前地图页面   
					currentVictoryDoor = nullptr; // 重置通关门对象
					levelFinish();
					currentPage = VICTORY_SCREEN; // 切换到胜利界面
					break;
				}

				Sleep(5); // 控制刷新频率 
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

			// 检查是否有鼠标事件  
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

	//游戏主循环
	void run() {
		initgraph(WINDOW_WIDTH, WINDOW_HEIGHT); // 初始化图形窗口  
		loadResources(); // 加载资源  
		playBackgroundMusic(L"音乐资源/人间日.wav"); // 初始播放默认音乐  

		while (true) {
			// 根据当前页面选择地图地面块、墙壁块、天花板块和通关门  
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
				currentHealBlocks = &level3HealBlocks; // 加载关卡3的回复方块
				currentTeleportBlocks = &level3TeleportBlocks; // 加载关卡3的传送门
				inTheGame();
			}
			BeginBatchDraw(); // 双缓存


			// 检查是否有鼠标事件  
			if (MouseHit()) {
				MOUSEMSG msg = GetMouseMsg();
				if (msg.uMsg == WM_LBUTTONDOWN) {
					handleMouseClick(msg.x, msg.y);
					std::cout << msg.x << "," << msg.y << std::endl;
				}
			}
			cleardevice(); // 清屏  
			drawCurrentPage(); // 绘制当前页面  
			EndBatchDraw();
		}
		closegraph(); // 关闭图形窗口  
		PlaySound(NULL, NULL, 0); // 停止播放音乐  
	}
private:
	// 添加计时相关的变量  
	DWORD startTime = 0; // 关卡开始时间  
	DWORD seconds = 0;//记录关卡时间
	bool levelStarted = false; // 标记关卡是否已经开始  
	std::vector<GroundBlock>* currentGroundBlocks = nullptr;
	std::vector<WallBlock>* currentWallBlocks = nullptr;
	std::vector<CeilingBlock>* currentCeilingBlocks = nullptr;
	std::vector<TrapBlock>* currentTrapBlocks = nullptr;
	std::vector<TreasureBlock>* currentTreasureBlocks = nullptr;
	VictoryDoor* currentVictoryDoor = nullptr; // 当前关卡的通关门  
	std::vector<HealBlock>* currentHealBlocks = nullptr; // 当前关卡的 HealBlock
	std::vector<TeleportBlock>* currentTeleportBlocks = nullptr;
};

// 主函数
int main() {
	Game game;
	game.run();
	return 0;
}