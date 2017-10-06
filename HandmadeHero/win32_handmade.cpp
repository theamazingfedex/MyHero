#include <windows.h>

LRESULT CALLBACK
MainWindowCallback(HWND Window,
                   UINT Message,
                   WPARAM WParam,
                   LPARAM LParam)
{
  LRESULT Result = 0;

  switch(Message)
  {
    case WM_SIZE:
    {
      OutputDebugStringA("WM_SIZE\n");
    } break;

    case WM_DESTROY:
    {
      OutputDebugStringA("WM_DESTROY4\n");
    } break;

    case WM_CLOSE:
    {
      OutputDebugStringA("WM_CLOSE\n");
    } break;

    case WM_ACTIVATEAPP:
    {
      OutputDebugStringA("WM_ACTIVATEAPP\n");
    } break;

    case WM_PAINT:
    {
      PAINTSTRUCT Paint;
      HDC DeviceContext = BeginPaint(Window, &Paint);
      INT X = Paint.rcPaint.left;
      INT Y = Paint.rcPaint.top;
      LONG Height = Paint.rcPaint.bottom - Paint.rcPaint.top;
      LONG Width = Paint.rcPaint.right - Paint.rcPaint.left;
      static DWORD Operation = WHITENESS;
      PatBlt(DeviceContext, X, Y, Width, Height, Operation);
      if(Operation == WHITENESS)
      {
        Operation = BLACKNESS;
      }
      else
      {
        Operation = WHITENESS;
      }
      EndPaint(Window, &Paint);
    } break;

    default:
    {
      //OutputDebugStringA("default\n");
      Result = DefWindowProc(Window, Message, WParam, LParam);
    } break;
  }
  return(Result);
}

int CALLBACK WinMain(
  HINSTANCE Instance,
  HINSTANCE PrevInstance,
  LPSTR CommandLine,
  int ShowCode
)
{
    WNDCLASS WindowClass = {};
    WindowClass.style = CS_OWNDC|CS_HREDRAW|CS_VREDRAW;
    WindowClass.lpfnWndProc = MainWindowCallback;
    WindowClass.hInstance = Instance;
    //WindowClass.hIcon = 0;
    WindowClass.lpszClassName = "HandmadeHeroWindowClass";
    
    if(RegisterClass(&WindowClass))
    {
      HWND WindowHandle = CreateWindowEx(
        0,
        WindowClass.lpszClassName,
        "Handmade Hero",
        WS_OVERLAPPEDWINDOW|WS_VISIBLE,
        CW_USEDEFAULT, // xPos
        CW_USEDEFAULT, // yPos
        CW_USEDEFAULT, // width
        CW_USEDEFAULT, // height
        0,
        0,
        Instance,
        0
      );
      if (WindowHandle)
      {
        for (;;)
        {
          MSG Message;
          BOOL MessageResult = GetMessage(&Message, 0, 0, 0);
          if (MessageResult > 0)
          {
            TranslateMessage(&Message);
            DispatchMessage(&Message);
          }
          else
          {
            break;
          }
        }
      }
      else
      {
        // TODO: Logging
      }
    }
    else
    {
      // TODO: Logging
    }
  return(0);
}
