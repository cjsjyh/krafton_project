////////////////////////////////////////////////////////////////////////////////
// Filename: inputclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _INPUTCLASS_H_
#define _INPUTCLASS_H_



///////////////////////////////
// PRE-PROCESSING DIRECTIVES //
///////////////////////////////
#define DIRECTINPUT_VERSION 0x0800


/////////////
// LINKING //
/////////////



//////////////
// INCLUDES //
//////////////



////////////////////////////////////////////////////////////////////////////////
// Class name: InputClass
////////////////////////////////////////////////////////////////////////////////

class InputClass
{
public:
	InputClass();
	InputClass(const InputClass&);
	~InputClass();

	bool Initialize(HINSTANCE, HWND, int, int);
	void Shutdown();
	bool Frame();

	bool IsLMouseDown(); // ���� Ŭ��
	bool IsRMouseDown(); // ������ Ŭ��
	bool IsMMouseDown(); // �� Ŭ��

	bool IsEscapePressed();

	bool IsKeyPressed(int);
	static bool IsKeyPressed(int* arr, int key);

	void GetMouseLocation(int&, int&);
	void GetMouseOffset(int&, int&);
	void GetScreenSize(int&, int&);

	static bool IsWASDKeyPressed(int* arr);
	static bool MouseNotClicked(bool* mouseInput);
	static bool RightMouseClicked(bool* mouseInput);
	static bool LeftMouseClicked(bool* mouseInput);

	int keyInput[10];
	bool mouseInput[3];

private:
	bool ReadKeyboard();
	bool ReadMouse();

private:
	IDirectInput8* m_directInput;
	IDirectInputDevice8* m_keyboard;
	IDirectInputDevice8* m_mouse;

	unsigned char m_keyboardState[256];
	DIMOUSESTATE m_mouseState;
	POINT cursorPos;
	HWND hwnd;

	const int keyCode[KEY_NUM] = { DIK_W, DIK_A,DIK_S,DIK_D,DIK_SPACE, DIK_LSHIFT, DIK_RETURN };

	int m_screenWidth, m_screenHeight;
	int m_mouseX, m_mouseY;
};

#endif