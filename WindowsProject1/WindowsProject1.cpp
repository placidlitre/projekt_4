#include <windows.h>
#include <iostream>
#include <objidl.h>
#include <gdiplus.h>
#include <string>
#include <vector>
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")
Point hakStart(600, 100);
Point hakEnd(600, 150);
#define ID_DOWN 2 
#define ID_UP 3
#define ID_RIGHT 4 
#define ID_LEFT 5 
#define ID_HOOK 6
#define ID_KWADRAT 7
#define ID_TROJKAT 8
#define ID_KOLO 9
int dopuszczanaMasa = 100000000;
class towar {

    
    
public: 
    int masa; 
    char ksztalt; 
    int xStart, yStart, width, height; 
    bool isHooked; 

    towar() {
        ksztalt = 'k';
        masa = 50000;
        xStart = 500;
        yStart = 500;
        width = 100;
        height = 100;
        isHooked = false; 
    }
    towar(char zadanyKsztalt) {
        ksztalt = zadanyKsztalt;
        masa = 50000;
        xStart = 700;
        yStart = 400;
        width = 100;
        height = 100;
        isHooked = false;  
    }

    void zmiana()
    {
        yStart+=10;
    }
    bool czySpelnia() {
        if ((ksztalt == 'k' || ksztalt == 'o' || ksztalt == 't') && masa < dopuszczanaMasa) {
            return true;
        }
        else return false;
    }
};
std::vector<towar> towary;

VOID OnPaint(HDC hdc)
{
    Graphics graphics(hdc);
    GraphicsPath path;

    PointF points[3] = {
              PointF(100, 50),   // wierzchołek górny
              PointF(50, 200),   // lewy dolny
              PointF(150, 200)   // prawy dolny
   };
    
    Pen      pen(Color(255, 255, 0, 0));
    graphics.DrawRectangle(&pen, 200, 100, 100, 1600); //pionowa czesc zurawia
    graphics.DrawRectangle(&pen, 200, 0, 1200, 100);
    graphics.DrawLine(&pen, hakStart, hakEnd);
    
    if (!towary.empty()) {
        for (towar &towar : towary) {
            switch (towar.ksztalt) {
            case 'k':
                graphics.DrawRectangle(&pen, towar.xStart, towar.yStart, towar.width, towar.height); 
                break;
            case 't':
                points[0] = PointF(towar.xStart, towar.yStart);
                points[1] = PointF(towar.xStart + towar.width, towar.yStart + towar.height);
                points[2] = PointF(towar.xStart - towar.width, towar.yStart + towar.height);
                graphics.DrawPolygon(&pen, points, 3);
                break;
            case 'o':
                graphics.DrawEllipse(&pen, towar.xStart, towar.yStart, towar.width, towar.height);
                break;
            default:
                break;
            }
        }
    }

}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow)
{
    HWND                hWnd;
    MSG                 msg;
    WNDCLASS            wndClass;
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR           gdiplusToken;

    // Initialize GDI+.
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    wndClass.style = CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc = WndProc;
    wndClass.cbClsExtra = 0;
    wndClass.cbWndExtra = 0;
    wndClass.hInstance = hInstance;
    wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndClass.lpszMenuName = NULL;
    wndClass.lpszClassName = TEXT("GettingStarted");

    RegisterClass(&wndClass);

   

    hWnd = CreateWindow(
        TEXT("GettingStarted"),   // window class name
        TEXT("Getting Started"),  // window caption
        WS_OVERLAPPEDWINDOW,      // window style
        CW_USEDEFAULT,            // initial x position
        CW_USEDEFAULT,            // initial y position
        CW_USEDEFAULT,            // initial x size
        CW_USEDEFAULT,            // initial y size
        NULL,                     // parent window handle
        NULL,                     // window menu handle
        hInstance,                // program instance handle
        NULL);                    // creation parameters
    HWND up = CreateWindow(
        L"BUTTON",  // Predefined class; Unicode assumed 
        L"UP",      // Button text 
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
        10,         // x position 
        100,         // y position 
        100,        // Button width
        100,        // Button height
        hWnd,     // Parent window
        (HMENU) ID_UP,       // No menu.
        (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
        NULL);      // Pointer not needed.
    HWND down = CreateWindow(
        L"BUTTON",  // Predefined class; Unicode assumed 
        L"DOWN",      // Button text 
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
        10,         // x position 
        200,         // y position 
        100,        // Button width
        100,        // Button height
        hWnd,     // Parent window
        (HMENU)ID_DOWN,       // No menu.
        (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
        NULL);      // Pointer not needed.
    HWND left = CreateWindow(
        L"BUTTON",  // Predefined class; Unicode assumed 
        L"LEFT",      // Button text 
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
        10,         // x position 
        300,         // y position 
        100,        // Button width
        100,        // Button height
        hWnd,     // Parent window
        (HMENU)ID_LEFT,       // No menu.
        (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
        NULL);      // Pointer not needed.
    HWND right= CreateWindow(
        L"BUTTON",  // Predefined class; Unicode assumed 
        L"RIGHT",      // Button text 
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
        10,         // x position 
        400,         // y position 
        100,        // Button width
        100,        // Button height
        hWnd,     // Parent window
        (HMENU)ID_RIGHT,       // No menu.
        (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
        NULL);      // Pointer not needed.
    HWND hook = CreateWindow(
        L"BUTTON",  // Predefined class; Unicode assumed 
        L"HOOK",      // Button text 
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
        10,         // x position 
        500,         // y position 
        100,        // Button width
        100,        // Button height
        hWnd,     // Parent window
        (HMENU)ID_HOOK,       // No menu.
        (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
        NULL);      // Pointer not needed.
    HWND kwadrat = CreateWindow(
        L"BUTTON",  // Predefined class; Unicode assumed 
        L"KWADRAT",      // Button text 
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
        10,         // x position 
        600,         // y position 
        100,        // Button width
        100,        // Button height
        hWnd,     // Parent window
        (HMENU)ID_KWADRAT,       // No menu.
        (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
        NULL);      // Pointer not needed.
    HWND trojkat = CreateWindow(
        L"BUTTON",  // Predefined class; Unicode assumed 
        L"TROJKAT",      // Button text 
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
        10,         // x position 
        700,         // y position 
        100,        // Button width
        100,        // Button height
        hWnd,     // Parent window
        (HMENU)ID_TROJKAT,       // No menu.
        (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
        NULL);      // Pointer not needed.
    HWND kolo = CreateWindow(
        L"BUTTON",  // Predefined class; Unicode assumed 
        L"KOLO",      // Button text 
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
        10,         // x position 
        800,         // y position 
        100,        // Button width
        100,        // Button height
        hWnd,     // Parent window
        (HMENU)ID_KOLO,       // No menu.
        (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
        NULL);      // Pointer not needed.
    ShowWindow(hWnd, iCmdShow);
    UpdateWindow(hWnd);

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    GdiplusShutdown(gdiplusToken);
    return msg.wParam;
}  // WinMain

LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
    WPARAM wParam, LPARAM lParam)
{
    HDC          hdc;
    PAINTSTRUCT  ps;

    switch (message)
    {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        OnPaint(hdc);
        EndPaint(hWnd, &ps);
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_COMMAND:
        if (LOWORD(wParam) == ID_DOWN) {
            hakEnd.Y += 10;   
            if (!towary.empty()) {

                for (towar& towar : towary) {
                    if (towar.isHooked && towar.czySpelnia())
                        towar.yStart += 10;
                }
            }
          // Move end of line 10px down
            InvalidateRect(hWnd, NULL, TRUE); // Request repaint
        }
        if (LOWORD(wParam) == ID_UP && hakEnd.Y >100) {
            hakEnd.Y -= 10;  
            if (!towary.empty()) {

            for (towar& towar : towary ) {
                if (towar.isHooked && towar.czySpelnia())
                  towar.yStart -=10;
            }
           }
            InvalidateRect(hWnd, NULL, TRUE); // Request repaint
        }if (LOWORD(wParam) == ID_RIGHT) {
            hakEnd.X += 10;  
            hakStart.X += 10;
            if (!towary.empty()) {

                for (towar& towar : towary) {
                    if (towar.isHooked && towar.czySpelnia())
                        towar.xStart += 10;
                }
            }
            InvalidateRect(hWnd, NULL, TRUE); // Request repaint
        }if (LOWORD(wParam) == ID_LEFT && hakStart.X > 350) {
            hakStart.X -= 10;
            hakEnd.X -= 10;
            if (!towary.empty()) {

                for (towar& towar : towary) {
                    if (towar.isHooked && towar.czySpelnia())
                        towar.xStart -= 10;
                }
            }
            InvalidateRect(hWnd, NULL, TRUE); // Request repaint
        }if (LOWORD(wParam) == ID_KWADRAT) {
            towary.push_back(towar('k')); 
            InvalidateRect(hWnd, NULL, TRUE); // Request repaint
        }if (LOWORD(wParam) == ID_TROJKAT) {
            towary.push_back(towar('t')); 
            InvalidateRect(hWnd, NULL, TRUE); // Request repaint
        }if (LOWORD(wParam) == ID_KOLO) {
            towary.push_back(towar('o')); 
            InvalidateRect(hWnd, NULL, TRUE); // Request repaint
        }
        if (LOWORD(wParam) == ID_HOOK ) {
            if (!towary.empty()) {
                for(towar& towar :towary){
                    if (hakStart.X >= towar.xStart && hakStart.X <= towar.xStart + towar.width && (towar.yStart) == hakEnd.Y) {
                        if (towar.isHooked) {
                            towar.isHooked = false;
                        }
                        else towar.isHooked = true;
                    }
                    else towar.isHooked = false; 
                }
           }
            InvalidateRect(hWnd, NULL, TRUE); // Request repaint
        }
        return 0;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
} // WndProc