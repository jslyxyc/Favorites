// ����C���Եײ�ʵ�����Windows����
// ʹ��gcc����windows����ʱ(����ָWindows API���)��Ҫ����-mwindowsѡ�����

#include <Windows.h>  // �ײ�ʵ�ִ��ڵ�ͷ�ļ�

// ������Ϣ�����ڹ��̣�
LRESULT CALLBACK HwxWindowProc(HWND hwnd,      //��Ϣ�����Ĵ��ھ��
                               UINT uMsg,      //������Ϣ����
                               WPARAM wParam,  //���̸�����Ϣ
                               LPARAM lParam   //��긽����Ϣ
);

// ������ں���
// WINAPI ����__stdcall �����Ĵ���˳�򣺴��ҵ���������ջ�������ں�������ǰ����ն�ջ
int WINAPI WinMain(HINSTANCE hinstance,      //Ӧ�ó����ʵ�����
                   HINSTANCE hprevinstance,  //��һ��Ӧ�ó�����
                   LPSTR lpcmdline,          // char* argv[]
                   int ncmdshow)             //��ʾ����
{
    // 1.��ƴ���

    WNDCLASS wc;

    // ��Ķ�����ڴ�
    wc.cbClsExtra = 0;

    // ���ڶ�����ڴ�
    wc.cbWndExtra = 0;

    // ���ñ���
    // ��仰�ŵ�Dev����һֱ����������VS����������
    // ����DevĬ��Release����ֻ�е���debug��֪���������
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

    // ���ù��
    // �����һ������ΪNULL������ʹ��ϵͳ�ṩ�Ĺ��
    wc.hCursor = LoadCursor(NULL, IDC_HAND);

    // ����ͼ��
    // �����һ������ΪNULL������ʹ��ϵͳ�ṩ��ͼ��
    wc.hIcon = LoadIcon(NULL, IDI_ERROR);

    // Ӧ�ó���ʵ�����������winmain�е��βμ���
    wc.hInstance = hinstance;

    // �ص����������ڹ��̣�
    wc.lpfnWndProc = HwxWindowProc;

    // ָ������������
    wc.lpszClassName = TEXT("HwxWin");

    // �˵�����
    wc.lpszMenuName = NULL;

    // ��ʾ���0����Ĭ�Ϸ��
    wc.style = 0;

    // 2.ע�ᴰ��

    RegisterClass(&wc);

    // 3.��������

    HWND HwxHwnd;

    // �������ͣ�
    // lpClassName      ����
    // lpWindowName     ���ڵı�������
    // dwStyle          ��񣬲�����дWS_OVERLAPPEDWINDOW
    // x, y             ��ʾ���꣬Ĭ��CW_USEDEFAULT
    // nWidth, nHeight  ���
    // hWndParent       �����ڣ��˴�дNULL
    // hMenu            �˵����˴�дNULL
    // hInstance        ʵ�����
    // lpParam          ����ֵ���˴�дNULL
    HwxHwnd = CreateWindow(wc.lpszClassName, TEXT("C���Եײ�ʵ����򵥽���"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
                           CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hinstance, NULL);

    // 4.��ʾ�͸���

    // (1)��ʾ����
    // ��һ������������һ���õ�
    // �ڶ��������Ƽ�SW_SHOWNORMAL
    ShowWindow(HwxHwnd, SW_SHOWNORMAL);

    // (2)���´���
    UpdateWindow(HwxHwnd);

    // 5.ͨ��ѭ��ȡ��Ϣ

    // MSG���壺
    /*
    HWND        hwnd;       �����ھ��
    UINT        message;    �������Ϣ����
    WPARAM      wParam;     ������Ϣ��ͨ���Ǽ�����Ϣ
    LPARAM      lParam;     ������Ϣ�������Ϣ�����Ҽ���
    DWORD       time;       ��Ϣ������ʱ��
    POINT       pt;         ������Ϣ �����Ϣ����������Ϣ��
    */
    MSG hwxmsg;

    // ͨ��ѭ��ȡ��Ϣ
    while (1) {
        // GetMessage���壺
        /*
        _Out_ LPMSG lpMsg,          ��Ϣ
        _In_opt_ HWND hWnd,         ���񴰿ڣ���NULL���������д���
        _In_ UINT wMsgFilterMin,    ��С�����Ĺ��˵���Ϣ
        _In_ UINT wMsgFilterMax     ���߶�Ϊ0������������Ϣ
        */
        if (GetMessage(&hwxmsg, NULL, 0, 0)) {
            //������Ϣ����Ҫ����ϼ�֮���
            TranslateMessage(&hwxmsg);

            //�ַ���Ϣ
            DispatchMessage(&hwxmsg);
        } else
            break;
    }

    // 6.������Ϣ�����ڹ��̣�

    return 0;
}

// ������Ϣ�����ڹ��̣�
LRESULT CALLBACK HwxWindowProc(HWND hwnd,      //��Ϣ�����Ĵ��ھ��
                               UINT uMsg,      //������Ϣ����
                               WPARAM wParam,  //���̸�����Ϣ
                               LPARAM lParam)  //��긽����Ϣ
{
    switch (uMsg) {
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_LBUTTONDOWN:  //���������
        {
            int xPos, yPos;
            char hwx[100] = {0};
            xPos = LOWORD(lParam);
            yPos = HIWORD(lParam);
            wsprintf(hwx, TEXT("���������������(%d,%d)\n���⣡���⣡���⣡"), xPos, yPos);
            MessageBox(hwnd, hwx, TEXT("���⣿���⣿���⣿"), MB_OK);
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

    // ����ֵ��Ĭ�ϴ���ʽ
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
