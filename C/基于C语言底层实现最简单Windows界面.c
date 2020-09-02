// 基于C语言底层实现最简单Windows界面
// 使用gcc编译windows程序时(这里指Windows API编程)需要加上-mwindows选项！！！

#include <Windows.h>  // 底层实现窗口的头文件

// 处理消息（窗口过程）
LRESULT CALLBACK HwxWindowProc(HWND hwnd,      //消息所属的窗口句柄
                               UINT uMsg,      //具体消息名称
                               WPARAM wParam,  //键盘附加消息
                               LPARAM lParam   //鼠标附加消息
);

// 程序入口函数
// WINAPI 代表__stdcall 参数的传递顺序：从右到左，依次入栈，并且在函数返回前，清空堆栈
int WINAPI WinMain(HINSTANCE hinstance,      //应用程序的实例句柄
                   HINSTANCE hprevinstance,  //上一个应用程序句柄
                   LPSTR lpcmdline,          // char* argv[]
                   int ncmdshow)             //显示命令
{
    // 1.设计窗口

    WNDCLASS wc;

    // 类的额外的内存
    wc.cbClsExtra = 0;

    // 窗口额外的内存
    wc.cbWndExtra = 0;

    // 设置背景
    // 这句话放到Dev里面一直报错，不过在VS里是正常的
    // 而且Dev默认Release，你只有调到debug才知道这里错了
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

    // 设置光标
    // 如果第一个参数为NULL，代表使用系统提供的光标
    wc.hCursor = LoadCursor(NULL, IDC_HAND);

    // 设置图标
    // 如果第一个参数为NULL，代表使用系统提供的图标
    wc.hIcon = LoadIcon(NULL, IDI_ERROR);

    // 应用程序实例句柄，传入winmain中的形参即可
    wc.hInstance = hinstance;

    // 回调函数（窗口过程）
    wc.lpfnWndProc = HwxWindowProc;

    // 指定窗口类名称
    wc.lpszClassName = TEXT("HwxWin");

    // 菜单名称
    wc.lpszMenuName = NULL;

    // 显示风格，0代表默认风格
    wc.style = 0;

    // 2.注册窗口

    RegisterClass(&wc);

    // 3.创建窗口

    HWND HwxHwnd;

    // 参数解释：
    // lpClassName      类名
    // lpWindowName     窗口的标题名称
    // dwStyle          风格，不懂就写WS_OVERLAPPEDWINDOW
    // x, y             显示坐标，默认CW_USEDEFAULT
    // nWidth, nHeight  宽高
    // hWndParent       父窗口，此处写NULL
    // hMenu            菜单，此处写NULL
    // hInstance        实例句柄
    // lpParam          附加值，此处写NULL
    HwxHwnd = CreateWindow(wc.lpszClassName, TEXT("C语言底层实现最简单界面"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
                           CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hinstance, NULL);

    // 4.显示和更新

    // (1)显示窗口
    // 第一个参数已在上一步得到
    // 第二个参数推荐SW_SHOWNORMAL
    ShowWindow(HwxHwnd, SW_SHOWNORMAL);

    // (2)更新窗口
    UpdateWindow(HwxHwnd);

    // 5.通过循环取消息

    // MSG定义：
    /*
    HWND        hwnd;       主窗口句柄
    UINT        message;    具体的消息名称
    WPARAM      wParam;     附加消息，通常是键盘消息
    LPARAM      lParam;     附加消息，鼠标消息（左右键）
    DWORD       time;       消息产生的时间
    POINT       pt;         附加消息 鼠标消息（坐标点的信息）
    */
    MSG hwxmsg;

    // 通过循环取消息
    while (1) {
        // GetMessage定义：
        /*
        _Out_ LPMSG lpMsg,          消息
        _In_opt_ HWND hWnd,         捕获窗口，填NULL代表捕获所有窗口
        _In_ UINT wMsgFilterMin,    最小和最大的过滤的消息
        _In_ UINT wMsgFilterMax     两者都为0代表捕获所有消息
        */
        if (GetMessage(&hwxmsg, NULL, 0, 0)) {
            //翻译消息，主要是组合键之类的
            TranslateMessage(&hwxmsg);

            //分发消息
            DispatchMessage(&hwxmsg);
        } else
            break;
    }

    // 6.处理消息（窗口过程）

    return 0;
}

// 处理消息（窗口过程）
LRESULT CALLBACK HwxWindowProc(HWND hwnd,      //消息所属的窗口句柄
                               UINT uMsg,      //具体消息名称
                               WPARAM wParam,  //键盘附加消息
                               LPARAM lParam)  //鼠标附加消息
{
    switch (uMsg) {
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_LBUTTONDOWN:  //鼠标左键点击
        {
            int xPos, yPos;
            char hwx[100] = {0};
            xPos = LOWORD(lParam);
            yPos = HIWORD(lParam);
            wsprintf(hwx, TEXT("你鼠标点击的坐标是(%d,%d)\n就这！就这！就这！"), xPos, yPos);
            MessageBox(hwnd, hwx, TEXT("就这？就这？就这？"), MB_OK);
            break;
        }
        case WM_PAINT: {
            PAINTSTRUCT hwxps;
            HDC hwxhdc;
            hwxhdc = BeginPaint(hwnd, &hwxps);
            TextOut(hwxhdc, 100, 100, TEXT("HELLO WORLD"), strlen("HELLO WORLD"));
            EndPaint(hwnd, &hwxps);
            break;
        }
    }

    // 返回值用默认处理方式
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
