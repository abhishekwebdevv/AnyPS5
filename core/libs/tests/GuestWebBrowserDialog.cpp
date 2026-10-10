#include "prx/libc/include/general/VabiMacros.hpp"
#include <cstdint>
#include <cstdlib>

extern "C" {
int APS5_VABI sceWebBrowserDialogInitialize(void);
int APS5_VABI sceWebBrowserDialogTerminate(void);
int APS5_VABI sceWebBrowserDialogOpen(const void* param);
int APS5_VABI sceWebBrowserDialogGetStatus(void);
int APS5_VABI sceWebBrowserDialogUpdateStatus(void);
int APS5_VABI sceWebBrowserDialogSetCookie(const void* param);
int APS5_VABI sceWebBrowserDialogOpenForPredeterminedContent(const void* param, const void* predetermined_content_param);
int APS5_VABI sceWebBrowserDialogResetCookie(const void* param);
}

namespace {

constexpr int COMMON_DIALOG_STATUS_NONE = 0;
constexpr int COMMON_DIALOG_STATUS_INITIALIZED = 1;
constexpr int COMMON_DIALOG_STATUS_FINISHED = 3;
constexpr int COMMON_DIALOG_ERROR_NOT_INITIALIZED = static_cast<int>(0x80B80003u);
constexpr int COMMON_DIALOG_ERROR_ARG_NULL = static_cast<int>(0x80B8000Du);

void Require(bool value) { if (!value) std::abort(); }

}

int main() {
    Require(sceWebBrowserDialogGetStatus() == COMMON_DIALOG_STATUS_NONE);
    std::uint8_t param[64] = {};
    std::uint8_t predeterminedContent[256] = {};
    Require(sceWebBrowserDialogSetCookie(param) == COMMON_DIALOG_ERROR_NOT_INITIALIZED);
    Require(sceWebBrowserDialogResetCookie(param) == COMMON_DIALOG_ERROR_NOT_INITIALIZED);
    Require(sceWebBrowserDialogOpenForPredeterminedContent(param, predeterminedContent) == COMMON_DIALOG_ERROR_NOT_INITIALIZED);
    Require(sceWebBrowserDialogInitialize() == 0);
    Require(sceWebBrowserDialogGetStatus() == COMMON_DIALOG_STATUS_INITIALIZED);
    Require(sceWebBrowserDialogSetCookie(nullptr) == COMMON_DIALOG_ERROR_ARG_NULL);
    Require(sceWebBrowserDialogResetCookie(nullptr) == COMMON_DIALOG_ERROR_ARG_NULL);
    Require(sceWebBrowserDialogOpenForPredeterminedContent(param, nullptr) == COMMON_DIALOG_ERROR_ARG_NULL);
    Require(sceWebBrowserDialogOpenForPredeterminedContent(nullptr, param) == COMMON_DIALOG_ERROR_ARG_NULL);
    Require(sceWebBrowserDialogSetCookie(param) == 0);
    Require(sceWebBrowserDialogGetStatus() == COMMON_DIALOG_STATUS_INITIALIZED);
    Require(sceWebBrowserDialogResetCookie(param) == 0);
    Require(sceWebBrowserDialogTerminate() == 0);
    Require(sceWebBrowserDialogGetStatus() == COMMON_DIALOG_STATUS_NONE);
    Require(sceWebBrowserDialogInitialize() == 0);
    Require(sceWebBrowserDialogOpen(param) == 0);
    Require(sceWebBrowserDialogGetStatus() == COMMON_DIALOG_STATUS_FINISHED);
    Require(sceWebBrowserDialogUpdateStatus() == COMMON_DIALOG_STATUS_FINISHED);
    Require(sceWebBrowserDialogSetCookie(param) == 0);
    Require(sceWebBrowserDialogResetCookie(param) == 0);
    Require(sceWebBrowserDialogOpenForPredeterminedContent(nullptr, nullptr) == COMMON_DIALOG_ERROR_ARG_NULL);
    Require(sceWebBrowserDialogOpenForPredeterminedContent(param, predeterminedContent) == 0);
    Require(sceWebBrowserDialogGetStatus() == COMMON_DIALOG_STATUS_FINISHED);
}
