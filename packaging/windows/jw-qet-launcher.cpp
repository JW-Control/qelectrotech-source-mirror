/*
 * JW QET Windows launcher
 *
 * Native Windows GUI entry point used for the normal JW QET workflow.
 * It intentionally has no console window. The existing repository workflow
 * remains the single source of truth and is executed hidden with --detach.
 */

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <string>
#include <vector>

namespace {

constexpr wchar_t kWindowClass[] = L"JWQETLauncherWindow";
constexpr wchar_t kMutexName[] = L"Local\\JW-QET-Launcher";
constexpr UINT kWindowWidth = 470;
constexpr UINT kWindowHeight = 126;

std::wstring moduleDirectory()
{
    std::vector<wchar_t> buffer(32768, L'\0');
    const DWORD length = GetModuleFileNameW(nullptr, buffer.data(),
                                            static_cast<DWORD>(buffer.size()));
    if (length == 0 || length >= buffer.size())
        return {};

    std::wstring path(buffer.data(), length);
    const std::wstring::size_type slash = path.find_last_of(L"\\/");
    if (slash == std::wstring::npos)
        return {};

    path.resize(slash);
    return path;
}

bool pathExists(const std::wstring &path)
{
    const DWORD attributes = GetFileAttributesW(path.c_str());
    return attributes != INVALID_FILE_ATTRIBUTES;
}

bool ensureDirectory(const std::wstring &path)
{
    if (CreateDirectoryW(path.c_str(), nullptr))
        return true;

    return GetLastError() == ERROR_ALREADY_EXISTS;
}

std::wstring systemCmdPath()
{
    std::vector<wchar_t> buffer(MAX_PATH + 1, L'\0');
    const UINT length = GetSystemDirectoryW(buffer.data(),
                                             static_cast<UINT>(buffer.size()));
    if (length == 0 || length >= buffer.size())
        return {};

    std::wstring path(buffer.data(), length);
    path += L"\\cmd.exe";
    return path;
}

std::wstring windowsErrorMessage(DWORD code)
{
    wchar_t *message = nullptr;
    const DWORD flags = FORMAT_MESSAGE_ALLOCATE_BUFFER |
                        FORMAT_MESSAGE_FROM_SYSTEM |
                        FORMAT_MESSAGE_IGNORE_INSERTS;

    const DWORD length = FormatMessageW(
        flags,
        nullptr,
        code,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        reinterpret_cast<wchar_t *>(&message),
        0,
        nullptr);

    std::wstring result;
    if (length && message)
        result.assign(message, length);
    else
        result = L"Error de Windows " + std::to_wstring(code);

    if (message)
        LocalFree(message);

    while (!result.empty() &&
           (result.back() == L'\r' || result.back() == L'\n' ||
            result.back() == L' ')) {
        result.pop_back();
    }

    return result;
}

LRESULT CALLBACK launcherWindowProc(HWND hwnd, UINT message,
                                    WPARAM wParam, LPARAM lParam)
{
    switch (message) {
    case WM_CLOSE:
        // The update/build must finish atomically. Do not let an accidental
        // Alt+F4 leave Git or Ninja half-way through their work.
        MessageBeep(MB_ICONINFORMATION);
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProcW(hwnd, message, wParam, lParam);
    }
}

HWND createStatusWindow(HINSTANCE instance)
{
    WNDCLASSEXW wc{};
    wc.cbSize = sizeof(wc);
    wc.lpfnWndProc = launcherWindowProc;
    wc.hInstance = instance;
    wc.hCursor = LoadCursorW(nullptr, IDC_WAIT);
    wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
    wc.lpszClassName = kWindowClass;

    if (!RegisterClassExW(&wc) && GetLastError() != ERROR_CLASS_ALREADY_EXISTS)
        return nullptr;

    RECT workArea{};
    SystemParametersInfoW(SPI_GETWORKAREA, 0, &workArea, 0);
    const int x = workArea.left +
                  ((workArea.right - workArea.left) - static_cast<int>(kWindowWidth)) / 2;
    const int y = workArea.top +
                  ((workArea.bottom - workArea.top) - static_cast<int>(kWindowHeight)) / 2;

    HWND window = CreateWindowExW(
        WS_EX_TOOLWINDOW,
        kWindowClass,
        L"JW QET",
        WS_CAPTION | WS_POPUP | WS_VISIBLE,
        x,
        y,
        kWindowWidth,
        kWindowHeight,
        nullptr,
        nullptr,
        instance,
        nullptr);

    if (!window)
        return nullptr;

    HWND label = CreateWindowExW(
        0,
        L"STATIC",
        L"Preparando JW QET...\r\n"
        L"Se actualizara el repositorio y se compilara solo lo necesario.\r\n"
        L"QElectroTech se abrira automaticamente.",
        WS_CHILD | WS_VISIBLE | SS_CENTER,
        20,
        24,
        kWindowWidth - 40,
        70,
        window,
        nullptr,
        instance,
        nullptr);

    if (label)
        SendMessageW(label, WM_SETFONT,
                     reinterpret_cast<WPARAM>(GetStockObject(DEFAULT_GUI_FONT)), TRUE);

    ShowWindow(window, SW_SHOWNORMAL);
    UpdateWindow(window);
    return window;
}

void pumpWindowMessages()
{
    MSG message{};
    while (PeekMessageW(&message, nullptr, 0, 0, PM_REMOVE)) {
        TranslateMessage(&message);
        DispatchMessageW(&message);
    }
}

bool launchHiddenWorkflow(const std::wstring &repo,
                          const std::wstring &logPath,
                          DWORD &exitCode,
                          std::wstring &error)
{
    const std::wstring cmd = systemCmdPath();
    const std::wstring batch = repo + L"\\run-jw-qet-dev.bat";

    if (cmd.empty() || !pathExists(cmd)) {
        error = L"No se encontro cmd.exe del sistema.";
        return false;
    }

    if (!pathExists(batch)) {
        error = L"No se encontro el flujo del repositorio:\r\n" + batch;
        return false;
    }

    SECURITY_ATTRIBUTES security{};
    security.nLength = sizeof(security);
    security.bInheritHandle = TRUE;

    HANDLE log = CreateFileW(
        logPath.c_str(),
        GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
        &security,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        nullptr);

    if (log == INVALID_HANDLE_VALUE) {
        error = L"No se pudo crear el registro:\r\n" + logPath + L"\r\n\r\n" +
                windowsErrorMessage(GetLastError());
        return false;
    }

    HANDLE nullInput = CreateFileW(
        L"NUL",
        GENERIC_READ,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        &security,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        nullptr);

    STARTUPINFOW startup{};
    startup.cb = sizeof(startup);
    startup.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
    startup.wShowWindow = SW_HIDE;
    startup.hStdInput = (nullInput == INVALID_HANDLE_VALUE) ? nullptr : nullInput;
    startup.hStdOutput = log;
    startup.hStdError = log;

    PROCESS_INFORMATION process{};

    // /d disables AutoRun commands, /s gives deterministic quote handling,
    // and CREATE_NO_WINDOW guarantees there is no visible CMD during normal use.
    std::wstring commandLine = L"\"" + cmd +
        L"\" /d /s /c \"\"" + batch + L"\" --detach\"";
    std::vector<wchar_t> mutableCommand(commandLine.begin(), commandLine.end());
    mutableCommand.push_back(L'\0');

    const BOOL created = CreateProcessW(
        cmd.c_str(),
        mutableCommand.data(),
        nullptr,
        nullptr,
        TRUE,
        CREATE_NO_WINDOW,
        nullptr,
        repo.c_str(),
        &startup,
        &process);

    const DWORD createError = created ? ERROR_SUCCESS : GetLastError();

    if (nullInput != INVALID_HANDLE_VALUE)
        CloseHandle(nullInput);
    CloseHandle(log);

    if (!created) {
        error = L"No se pudo iniciar el flujo de JW QET.\r\n\r\n" +
                windowsErrorMessage(createError);
        return false;
    }

    CloseHandle(process.hThread);

    for (;;) {
        const DWORD waitResult = MsgWaitForMultipleObjects(
            1,
            &process.hProcess,
            FALSE,
            200,
            QS_ALLINPUT);

        if (waitResult == WAIT_OBJECT_0)
            break;

        if (waitResult == WAIT_OBJECT_0 + 1) {
            pumpWindowMessages();
            continue;
        }

        if (waitResult == WAIT_FAILED) {
            error = L"Fallo esperando al proceso de preparacion.\r\n\r\n" +
                    windowsErrorMessage(GetLastError());
            CloseHandle(process.hProcess);
            return false;
        }
    }

    if (!GetExitCodeProcess(process.hProcess, &exitCode)) {
        error = L"No se pudo obtener el resultado del proceso.\r\n\r\n" +
                windowsErrorMessage(GetLastError());
        CloseHandle(process.hProcess);
        return false;
    }

    CloseHandle(process.hProcess);
    return true;
}

} // namespace

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE, PWSTR, int)
{
    HANDLE mutex = CreateMutexW(nullptr, FALSE, kMutexName);
    if (!mutex) {
        MessageBoxW(nullptr,
                    L"No se pudo inicializar JW QET Launcher.",
                    L"JW QET",
                    MB_OK | MB_ICONERROR);
        return 1;
    }

    if (GetLastError() == ERROR_ALREADY_EXISTS) {
        MessageBoxW(nullptr,
                    L"JW QET ya se esta preparando en esta PC.\r\n"
                    L"Espera a que termine el proceso actual.",
                    L"JW QET",
                    MB_OK | MB_ICONINFORMATION);
        CloseHandle(mutex);
        return 0;
    }

    const std::wstring repo = moduleDirectory();
    if (repo.empty()) {
        MessageBoxW(nullptr,
                    L"No se pudo determinar la carpeta del repositorio.",
                    L"JW QET",
                    MB_OK | MB_ICONERROR);
        CloseHandle(mutex);
        return 1;
    }

    const std::wstring buildDir = repo + L"\\build";
    const std::wstring logDir = buildDir + L"\\logs";
    const std::wstring logPath = logDir + L"\\jw-qet-launcher.log";

    if (!ensureDirectory(buildDir) || !ensureDirectory(logDir)) {
        MessageBoxW(nullptr,
                    (L"No se pudo crear la carpeta de registros:\r\n" + logDir).c_str(),
                    L"JW QET",
                    MB_OK | MB_ICONERROR);
        CloseHandle(mutex);
        return 1;
    }

    HWND statusWindow = createStatusWindow(instance);

    DWORD exitCode = 1;
    std::wstring error;
    const bool started = launchHiddenWorkflow(repo, logPath, exitCode, error);

    if (statusWindow)
        DestroyWindow(statusWindow);
    pumpWindowMessages();

    if (!started || exitCode != 0) {
        std::wstring message;
        if (!error.empty())
            message = error + L"\r\n\r\n";
        else
            message = L"El flujo termino con codigo " + std::to_wstring(exitCode) + L".\r\n\r\n";

        message += L"Revisa el registro para ver el detalle:\r\n" + logPath;

        MessageBoxW(nullptr,
                    message.c_str(),
                    L"JW QET - No se pudo iniciar",
                    MB_OK | MB_ICONERROR);
        CloseHandle(mutex);
        return static_cast<int>(exitCode ? exitCode : 1);
    }

    CloseHandle(mutex);
    return 0;
}
