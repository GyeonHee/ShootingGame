#pragma once

#include <Windows.h>

// ������Ʈ���� �پ��ϰ� ����� ��ƿ��Ƽ �Լ� ����
namespace Utils
{
	// �� ���� ���� �ٲ� �� ����ϴ� �Լ�
	template<typename T>
	void Swap(T& a, T& b)
	{
		T temp;
		a = b;
		b = temp;
	}

	// �ܼ� ��� �ڵ� �������� �Լ�
	inline HANDLE GetConsoleHandle()
	{
		return GetStdHandle(STD_OUTPUT_HANDLE);
	}

	// �ܼ� Ŀ�� ��ġ �̵� �Լ�
	inline void SetCursorPosition(COORD coord)
	{
		static HANDLE handle = GetConsoleHandle();
		SetConsoleCursorPosition(handle, coord);
	}

	// �ܼ� �ؽ�Ʈ ���� ���� �Լ�
	inline void SetConsoleTextColor(WORD color)
	{
		static HANDLE handle = GetConsoleHandle();
		SetConsoleTextAttribute(handle, color);
	}
}