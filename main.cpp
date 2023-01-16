#include <iostream>
#include <Windows.h>
#include <vector>

namespace constants
{
	int X = 22;
	int Y = 22;
	int CD = 60;
}

void clear()
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });
}

std::vector < std::vector<char>> board_gen(std::vector <std::vector<std::string>> buf1)
{
	std::vector <std::string> buf(16);
	int buftempsize = 0;
	for (int i = 0; i < buf1.size(); i++)
	{
		for (int j = 0; j < buf1.size(); j++)
		{
			buf[buftempsize] = buf1[i][j];
			buftempsize += 1;
		}
	}

	std::vector < std::vector<char>> board(constants::X, std::vector <char>(constants::Y));
	int bufX = 0;
	int bufY = 0;
	for (int el = 0; el < buf.size(); el++)
	{
		for (int y = 0; y < 5; y++)
		{
			for (int x = 0; x < 5; x++)
			{
				for (int i = 0; i < buf[el].length(); i++)
				{
					if (buf[el][i] == 's')
					{
						if (buf[el][i] == '0')
						{
							if (buf[el].length() < 3)
							{
								board[bufY + 2][bufX + 2] = buf[el][0];
							}
							else
							{
								board[bufY + 2][bufX + 1] = buf[el][0];
								board[bufY + 2][bufX + 2] = buf[el][1];
								board[bufY + 2][bufX + 3] = buf[el][2];
							}
						}
						if (x == 0 or x == 4 or y == 0 or y == 4)
						{
							board[bufY + y][bufX + x] = '#';
						}
						else
						{
							board[bufY + y][bufX + x] = ' ';
						}
					}
					else
					{
						if (y == 0 or y == 4)
						{
							board[bufY + y][bufX + x] = ' ';
						}
						else if (x == 0 or x == 4)
						{
							board[bufY + y][bufX + x] = ' ';
						}
						else
						{
							board[bufY + y][bufX + x] = ' ';
						}
						if (buf[el][i] == '0')
						{
							continue;
							if (y == 0 or y == 4)
							{
								board[bufY + y][bufX + x] = ' ';
							}
							else if (x == 0 or x == 4)
							{
								board[bufY + y][bufX + x] = ' ';
							}
							else
							{
								board[bufY + y][bufX + x] = ' ';
							}
						}
						if (i == 1)
						{
							if (buf[el][i-1] == '0')
							{
								if (y == 0 or y == 4)
								{
									board[bufY + y][bufX + x] = ' ';
								}
								else if (x == 0 or x == 4)
								{
									board[bufY + y][bufX + x] = ' ';
								}
								else
								{
									board[bufY + y][bufX + x] = ' ';
								}
								continue;
							}
						}
						if (buf[el].length() < 3)
						{
							board[bufY + 2][bufX + 2] = buf[el][0];
						}
						else
						{
							board[bufY + 2][bufX + 1] = buf[el][0];
							board[bufY + 2][bufX + 2] = buf[el][1];
							board[bufY + 2][bufX + 3] = buf[el][2];
						}
					}
				}
			}
		}
		if (bufX == 15)
		{
			bufY += 5;
			bufX = 0;
		}
		else
		{
			bufX += 5;
		}
	}

	return board;
}

void render(std::vector <std::vector<std::string>> board)
{
	auto buf = board_gen(board);
	std::cout << "_____________________________________________"<<std::endl;
	for (int y = 0; y < buf.size()-2; y++)
	{
		std::string line = "|  ";
		for (int x = 0; x < buf[0].size()-1; x++)
		{
			line += buf[y][x];
			line += " ";
		}
		line += "|";
		std::cout << line;
		std::cout << '\n';
	}
	std::cout << "_____________________________________________" << std::endl;
}

std::vector <std::vector<std::string>> board_init()
{
	std::vector <std::vector<std::string>> board = { {"1 ","2 ","3 ","4 "}, {"5 ", "6 ", "7 ", "8 "}, {"9 ", "1 0 ", "1 1 ", "1 2 "}, {"1 3 ", "1 4 ", "1 5 ", "0 "}};

	return board;
}

struct selected
{
	int x;
	int y;
};

int main()
{
	srand(time(0));
	void* hWnd = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_FONT_INFOEX cfi{};
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 12;
	cfi.dwFontSize.Y = 20;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, L"Lucida");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

	COORD bufferSize = { constants::X * 2 + 3, constants::Y + 3 };
	SMALL_RECT windowSize = { 0, 0, constants::X * 2 + 1, constants::Y  };
	SetConsoleScreenBufferSize(hWnd, bufferSize);
	SetConsoleWindowInfo(hWnd, TRUE, &windowSize);

	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(hWnd, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(hWnd, &structCursorInfo);

	auto board = board_init();
	selected sel{0,0};
	board[sel.y][sel.x][board[sel.y][sel.x].length() - 1] = 's';
	int cd = 0;
	bool issel = false;

	while (true)
	{
		if (GetAsyncKeyState((unsigned short)'E'))
		{
			if (cd == 0)
			{
				issel = true;
				cd = constants::CD;
			}
		}
		if (GetAsyncKeyState((unsigned short)'W'))
		{
			if (cd == 0)
			{
				if (sel.y != 0)
				{
					if (issel)
					{
						if (board[sel.y - 1][sel.x] == "0 ")
						{
							std::string tmp = board[sel.y - 1][sel.x];
							board[sel.y - 1][sel.x] = board[sel.y][sel.x];
							board[sel.y][sel.x] = tmp;
							issel = false;
						}
					}
					board[sel.y][sel.x][board[sel.y][sel.x].length() - 1] = ' ';
					sel.y -= 1;
					board[sel.y][sel.x][board[sel.y][sel.x].length() - 1] = 's';
				}
				cd = constants::CD;
			}
		}
		if (GetAsyncKeyState((unsigned short)'A'))
		{
			if (cd == 0)
			{
				if (sel.x != 0)
				{
					if (issel)
					{
						if (board[sel.y][sel.x - 1] == "0 ")
						{
							std::string tmp = board[sel.y][sel.x - 1];
							board[sel.y][sel.x - 1] = board[sel.y][sel.x];
							board[sel.y][sel.x] = tmp;
							issel = false;
						}
					}
					board[sel.y][sel.x][board[sel.y][sel.x].length() - 1] = ' ';
					sel.x -= 1;
					board[sel.y][sel.x][board[sel.y][sel.x].length() - 1] = 's';
				}
				cd = constants::CD;
			}
		}
		if (GetAsyncKeyState((unsigned short)'S'))
		{
			if (cd == 0)
			{
				if (sel.y != 3)
				{
					if (issel)
					{
						if (board[sel.y + 1][sel.x] == "0 ")
						{
							std::string tmp = board[sel.y + 1][sel.x];
							board[sel.y + 1][sel.x] = board[sel.y][sel.x];
							board[sel.y][sel.x] = tmp;
							issel = false;
						}
					}
					board[sel.y][sel.x][board[sel.y][sel.x].length() - 1] = ' ';
					sel.y += 1;
					board[sel.y][sel.x][board[sel.y][sel.x].length() - 1] = 's';
				}
				cd = constants::CD;
			}
		}
		if (GetAsyncKeyState((unsigned short)'D'))
		{
			if (cd == 0)
			{
				if (sel.x != 3)
				{
					if (issel)
					{
						if (board[sel.y][sel.x+1] == "0 ")
						{
							std::string tmp = board[sel.y][sel.x + 1];
							board[sel.y][sel.x + 1] = board[sel.y][sel.x];
							board[sel.y][sel.x] = tmp;
							issel = false;
						}
					}
					board[sel.y][sel.x][board[sel.y][sel.x].length() - 1] = ' ';
					sel.x += 1;
					board[sel.y][sel.x][board[sel.y][sel.x].length() - 1] = 's';
				}
				cd = constants::CD;
			}
		}

		clear();
		render(board);

		if (cd != 0)
		{
			cd -= 1;
		}
	}

	return 0;
}