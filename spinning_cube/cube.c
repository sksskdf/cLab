#include <stdio.h>
#include <string.h>
#include <math.h>
#ifndef _WIN32
#include <unistd.h>
#else
#include <windows.h>
void usleep(__int64 usec) {
	HANDLE timer;
	LARGE_INTEGER ft;

	ft.QuadPart = -(10 * usec);

	timer = CreateWaitableTimer(NULL, TRUE, NULL);
	SetWaitableTimer(timer, &ft, 0, NULL, NULL, 0);
	WaitForSingleObject(timer, INFINITE);
	CloseHandle(timer);
}
#endif

float A, B, C;

float cubeWidth = 20;
int backgroundASCIICode = '.';
int width = 160, height = 44;
char buffer[160 * 44];
float zBuffer[160 * 44];
float horizontalOffset;
int distanceFromCam = 130;
float K1 = 40;

float incrementSpeed = 0.5;

float x, y, z;
float ooz;
int xp, yp;
int idx;

float calculateX(int i, int j, int k) {
	return 	j * sin(A) * sin(B) * cos(C) - k * cos(A) * sin(B) * cos(C) +
		j * cos(A) * sin(C) + k * sin(A) * sin(C) + i * cos(B) * cos(C);
}

float calculateY(int i, int j, int k) {
	return  j + cos(A) * cos(C) + k * sin(A) * cos(C) -
		j * sin(A) * sin(B) * sin(C) + k * cos(A) * sin(B) * sin(C) -
		i * cos(B) * sin(C);
}

float calculateZ(int i, int j, int k) {
	return k * cos(A) * cos(B) - j * sin(A) * cos(B) + i * sin(B);
}

void calculateForSurface(float cubeX, float cubeY, float cubeZ, int ch) {
	x = calculateX(cubeX, cubeY, cubeZ);
	y = calculateY(cubeX, cubeY, cubeZ);
	z = calculateZ(cubeX, cubeY, cubeZ) + distanceFromCam;

	// z값의 역수로 물체의 깊이 정보를 반영하는데 사용됨
	ooz = 0.8 / z;
	
	xp = (int)(width / 2 + horizontalOffset + K1 * ooz * x * 2);
	yp = (int)(height / 2 + K1 * ooz * y);

	idx = xp + yp * width;
	if (idx >= 0 && idx < width * height) {
		if (ooz > zBuffer[idx]) {
			zBuffer[idx] = ooz;
			buffer[idx] = ch;
		}
	}
}

int main() {
	// \x1b[2J 는 ANSI escape sequence로 터미널 화면을 지우는 명령어
	// \x1b는 ASCII 코드로 27번 (ESC)를 나타내며 ANSI escape sequence의 시작을 알림
	// [2J는 ESC에 이어오는 제어 문자 시퀀스, [2J는 화면 전체를 지우라는 의미
	printf("\x1b[2J");

	while (1) {
		// memset은 C에서 메모리 블록을 특정 값으로 초기화하는 데 사용
		// 주로 배열, 구조체 등의 메모리를 초기화할 때 사용됨
		// memset은 <string.h> 헤더 파일에 정의되어 있음
		// 	void *memset(void *ptr, int value, size_t num);
		// 		ptr: 초기화할 메모리의 시작 주소를 가리키는 포인터
		// 		value: 설정할 값, value는 int 타입이지만 unsigned char로 변환되어 메모리 블록의 각 바이트에 할당됨
		// 		num: 초기화할 바이트 수
		// 	반환값은 초기화된 메모리 블록의 시작 주소를 반환함
		memset(buffer, backgroundASCIICode, width * height);
		// float은 4바이트라서 *4 한 값으로 바이트 수를 초기화 해줘야 함.
		memset(zBuffer, 0, width * height * sizeof(float));
		cubeWidth = 22;
		horizontalOffset = -0.15 * cubeWidth;
		
		for (float cubeX = -cubeWidth; cubeX < cubeWidth; cubeX += incrementSpeed) {
			for (float cubeY = -cubeWidth; cubeY < cubeWidth; cubeY += incrementSpeed) {
				calculateForSurface(cubeX, cubeY, -cubeWidth, '@');
				calculateForSurface(cubeWidth, cubeY, cubeX, '$');
				calculateForSurface(-cubeWidth, cubeY, -cubeX, '~');
				calculateForSurface(-cubeX, cubeY, cubeWidth, '#');
				calculateForSurface(cubeX, -cubeWidth, -cubeY, ';');
				calculateForSurface(cubeX, cubeWidth, cubeY, '+');
			}
		}
		/*
		cubeWidth = 10;
		horizontalOffset = 1 * cubeWidth;
		for (float cubeX = -cubeWidth; cubeX < cubeWidth; cubeX += incrementSpeed) {
			for (float cubeY = -cubeWidth; cubeY < cubeWidth; cubeY += incrementSpeed) {
				calculateForSurface(cubeX, cubeY, -cubeWidth, '@');
				calculateForSurface(cubeWidth, cubeY , cubeX, '$');
				calculateForSurface(-cubeWidth, cubeY, -cubeX, '~');
				calculateForSurface(-cubeX, cubeY, cubeWidth, '#');
				calculateForSurface(cubeX, -cubeWidth, -cubeY, ';');
				calculateForSurface(cubeX, cubeWidth, cubeY, '+');
			}
		}
		cubeWidth = 5;
		horizontalOffset = 8 * cubeWidth;
		for (float cubeX = -cubeWidth; cubeX < cubeWidth; cubeX += incrementSpeed) {
			for (float cubeY = -cubeWidth; cubeY < cubeWidth; cubeY += incrementSpeed) {
				calculateForSurface(cubeX, cubeY, -cubeWidth, '@');
				calculateForSurface(cubeWidth, cubeY, cubeX, '$');
				calculateForSurface(-cubeWidth, cubeY, -cubeX, '~');
				calculateForSurface(-cubeX, cubeY, cubeWidth, '#');
				calculateForSurface(cubeX, -cubeWidth, -cubeY, ';');
				calculateForSurface(cubeX, cubeWidth, cubeY, '+');
			}
		}
		*/
		printf("\x1b[H");
		for (int k = 0; k < width * height; k++) {
			putchar(k % width ? buffer[k] : 10);
		}

		A += 0.04;
		B += 0.04;
//		C += 0.02;
		usleep(8000 * 2);
	}

	return 0;
}
