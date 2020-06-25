/*******************************************************************************
*
*  (C) COPYRIGHT AUTHORS, 2019 - 2020
*
*  TITLE:       PLUGIN_DEF.H
*
*  VERSION:     1.02
*
*  DATE:        23 June 2020
*
*  Common header file for the plugin subsystem definitions.
*
* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
* ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
* TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
* PARTICULAR PURPOSE.
*
*******************************************************************************/

#pragma once

#define WOBJ_PLUGIN_SYSTEM_VERSION 18712

typedef PVOID(*PMEMALLOCROUTINE)(
    _In_ SIZE_T NumberOfBytes);

typedef BOOL(*PMEMFREEROUTINE)(
    _In_ PVOID Memory);

typedef BOOL(CALLBACK* pfnReadSystemMemoryEx)(
    _In_ ULONG_PTR Address,
    _Inout_ PVOID Buffer,
    _In_ ULONG BufferSize,
    _Out_opt_ PULONG NumberOfBytesRead);

typedef UCHAR(CALLBACK* pfnGetInstructionLength)(
    _In_ PVOID ptrCode,
    _Out_ PULONG ptrFlags);

typedef PVOID(*pfnGetSystemInfoEx)(
    _In_ ULONG SystemInformationClass,
    _Out_opt_ PULONG ReturnLength,
    _In_ PMEMALLOCROUTINE MemAllocRoutine,
    _In_ PMEMFREEROUTINE MemFreeRoutine);

typedef PVOID(*pfnFindModuleEntryByName)(
    _In_ PVOID pModulesList,
    _In_ LPCSTR ModuleName);

typedef ULONG(*pfnFindModuleEntryByAddress)(
    _In_ PVOID pModulesList,
    _In_ PVOID Address);

typedef BOOL(*pfnFindModuleNameByAddress)(
    _In_ PVOID pModulesList,
    _In_ PVOID Address,
    _Inout_	LPWSTR Buffer,
    _In_ DWORD ccBuffer);

typedef BOOL(*pfnGetWin32FileName)(
    _In_ LPWSTR FileName,
    _Inout_ LPWSTR Win32FileName,
    _In_ SIZE_T ccWin32FileName);

typedef INT(*pfnuiGetMaxOfTwoU64FromHex)(
    _In_ HWND ListView,
    _In_ LPARAM lParam1,
    _In_ LPARAM lParam2,
    _In_ LPARAM lParamSort,
    _In_ BOOL Inverse);

typedef INT(*pfnuiGetMaxCompareTwoFixedStrings)(
    _In_ HWND ListView,
    _In_ LPARAM lParam1,
    _In_ LPARAM lParam2,
    _In_ LPARAM lParamSort,
    _In_ BOOL Inverse);

typedef VOID(*pfnuiCopyTreeListSubItemValue)(
    _In_ HWND TreeList,
    _In_ UINT ValueIndex);

typedef VOID(*pfnuiCopyListViewSubItemValue)(
    _In_ HWND ListView,
    _In_ UINT ValueIndex);

typedef VOID(*pfnuiShowFileProperties)(
    _In_ HWND hwndDlg,
    _In_ LPWSTR lpFileName);

typedef UINT(*pfnuiGetDPIValue)(
    _In_opt_ HWND hWnd);

typedef struct _WINOBJEX_PARAM_BLOCK {
    HWND ParentWindow;
    HINSTANCE Instance;
    ULONG_PTR SystemRangeStart;
    HANDLE ObjectHandle; // used only by Context plugins
    RTL_OSVERSIONINFOW Version;

    //sys
    pfnReadSystemMemoryEx ReadSystemMemoryEx;
    pfnGetInstructionLength GetInstructionLength;
    pfnGetSystemInfoEx GetSystemInfoEx;
    pfnFindModuleEntryByName FindModuleEntryByName;
    pfnFindModuleEntryByAddress FindModuleEntryByAddress;
    pfnFindModuleNameByAddress FindModuleNameByAddress;
    pfnGetWin32FileName GetWin32FileName;

    //ui
    pfnuiGetMaxOfTwoU64FromHex uiGetMaxOfTwoU64FromHex;
    pfnuiGetMaxCompareTwoFixedStrings uiGetMaxCompareTwoFixedStrings;
    pfnuiCopyTreeListSubItemValue uiCopyTreeListSubItemValue;
    pfnuiCopyListViewSubItemValue uiCopyListViewSubItemValue;
    pfnuiShowFileProperties uiShowFileProperties;
    pfnuiGetDPIValue uiGetDPIValue;

} WINOBJEX_PARAM_BLOCK, * PWINOBJEX_PARAM_BLOCK;

typedef NTSTATUS(CALLBACK* pfnStartPlugin)(
    _In_ PWINOBJEX_PARAM_BLOCK ParamBlock);

typedef void(CALLBACK* pfnStopPlugin)(
    VOID);

typedef struct _WINOBJEX_PLUGIN WINOBJEX_PLUGIN;

typedef enum _WINOBJEX_PLUGIN_STATE {
    PluginInitialization = 0,
    PluginStopped = 1,
    PluginRunning = 2,
    PluginError = 3,
    MaxPluginState
} WINOBJEX_PLUGIN_STATE;

typedef enum _WINOBJEX_PLUGIN_TYPE {
    DefaultPlugin = 0, // General purpose plugin (shown in main menu under "Plugins")
    ContextPlugin = 1  // Object type specific plugin (shown in popup menu for specified object type)
} WINOBJEX_PLUGIN_TYPE;

typedef void(CALLBACK* pfnStateChangeCallback)(
    _In_ WINOBJEX_PLUGIN* PluginData,
    _In_ WINOBJEX_PLUGIN_STATE NewState,
    _Reserved_ PVOID Reserved);

//
// Object type indexes for known types, must be in compliance with WOBJ_OBJECT_TYPE values.
//

#define ObjectTypeDevice 0
#define ObjectTypeDriver 1
#define ObjectTypeSection 2
#define ObjectTypePort 3
#define ObjectTypeSymbolicLink 4
#define ObjectTypeKey 5
#define ObjectTypeEvent 6
#define ObjectTypeJob 7
#define ObjectTypeMutant 8
#define ObjectTypeKeyedEvent 9
#define ObjectTypeType 10
#define ObjectTypeDirectory 11
#define ObjectTypeWinstation 12
#define ObjectTypeCallback 13
#define ObjectTypeSemaphore 14
#define ObjectTypeWaitablePort 15
#define ObjectTypeTimer 16
#define ObjectTypeSession 17
#define ObjectTypeController 18
#define ObjectTypeProfile 19
#define ObjectTypeEventPair 20
#define ObjectTypeDesktop 21
#define ObjectTypeFile 22
#define ObjectTypeWMIGuid 23
#define ObjectTypeDebugObject 24
#define ObjectTypeIoCompletion 25
#define ObjectTypeProcess 26
#define ObjectTypeAdapter 27
#define ObjectTypeToken 28
#define ObjectTypeETWRegistration 29
#define ObjectTypeThread 30
#define ObjectTypeTmTx 31
#define ObjectTypeTmTm 32
#define ObjectTypeTmRm 33
#define ObjectTypeTmEn 34
#define ObjectTypePcwObject 35
#define ObjectTypeFltConnPort 36
#define ObjectTypeFltComnPort 37
#define ObjectTypePowerRequest 38
#define ObjectTypeETWConsumer 39
#define ObjectTypeTpWorkerFactory 40
#define ObjectTypeComposition 41
#define ObjectTypeIRTimer 42
#define ObjectTypeDxgkSharedResource 43
#define ObjectTypeDxgkSharedSwapChain 44
#define ObjectTypeDxgkSharedSyncObject 45
#define ObjectTypeDxgkCurrentDxgProcessObject 46
#define ObjectTypeDxgkCurrentDxgThreadObject 47
#define ObjectTypeDxgkDisplayManager 48
#define ObjectTypeDxgkSharedBundle 49
#define ObjectTypeDxgkSharedProtectedSession 50
#define ObjectTypeDxgkComposition 51
#define ObjectTypeDxgkSharedKeyedMutex 52
#define ObjectTypeMemoryPartition 53
#define ObjectTypeRegistryTransaction 54
#define ObjectTypeDmaAdapter 55
#define ObjectTypeDmaDomain 56
#define ObjectTypeUnknown 57

typedef struct _WINOBJEX_PLUGIN {
    BOOLEAN NeedAdmin;
    BOOLEAN NeedDriver;
    BOOLEAN SupportWine;
    ULONG SupportedObjectType; // Ignored if plugin Type is DefaultPlugin
    WINOBJEX_PLUGIN_TYPE Type;
    WINOBJEX_PLUGIN_STATE State;
    WORD MajorVersion;
    WORD MinorVersion;
    ULONG RequiredPluginSystemVersion;
    WCHAR Name[32];
    WCHAR Description[64];
    pfnStartPlugin StartPlugin;
    pfnStopPlugin StopPlugin;
    pfnStateChangeCallback StateChangeCallback;
} WINOBJEX_PLUGIN, * PWINOBJEX_PLUGIN;
