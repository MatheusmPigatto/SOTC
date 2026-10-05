#include "common.h"

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/ios/graph/gs", iosDumpDMAStatus);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/ios/graph/gs", iosDumpVIF1Status);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/ios/graph/gs", iosDumpGIFStatus);

extern char D_40048060[];
extern char D_40048098[];
extern char D_400480D0[];
extern char D_40048100[];
extern char D_40048130[];
extern void (*D_40045A90)(u32);
extern void iosDumpDMAStatus(s32);
extern void iosDumpVIF1Status(void);
extern void iosDumpGIFStatus(void);
extern s32 LoaderSysPrintf(const char *, ...);

// VPU-STAT is COP2 control register $vi29, which C can only reach through asm
#define VU1_STAT(v) asm volatile("cfc2.ni %0, $vi29" : "=r"(v))

s32 iosSyncPath(s32 mode, u16 timeout)
{
    s32 count;
    s32 i;
    s32 stat;

    count = timeout ? timeout : 0x2000000;
    i = 0;
    if (mode == 0)
        goto sync;
    {
        s32 r0, r1, r2, r3, r4;
        VU1_STAT(stat);
        r0 = (*(volatile s32 *)0x10009000 >> 8) & 1;
        r1 = (*(volatile s32 *)0x1000A000 & 0x100) ? r0 | 2 : r0;
        r2 = (*(volatile s32 *)0x10003C00 & 0x1F000003) ? r1 | 4 : r1;
        r3 = (stat & 0x100) ? r2 | 8 : r2;
        r4 = (*(volatile s32 *)0x10003020 & 0xC00) ? r3 | 0x10 : r3;
        return r4;
    }
err1:
    iosDumpDMAStatus(0);
    iosDumpVIF1Status();
    iosDumpGIFStatus();
    LoaderSysPrintf(D_40048060);
    D_40045A90(*(volatile u32 *)0x10003C30);
    return -1;
err2:
    iosDumpDMAStatus(1);
    LoaderSysPrintf(D_40048098);
    return -1;
err3:
    iosDumpDMAStatus(0);
    iosDumpVIF1Status();
    iosDumpGIFStatus();
    LoaderSysPrintf(D_400480D0);
    D_40045A90(*(volatile u32 *)0x10003C30);
    return -1;
err4:
    iosDumpDMAStatus(0);
    iosDumpVIF1Status();
    LoaderSysPrintf(D_40048100);
    D_40045A90(*(volatile u32 *)0x10003C30);
    return -1;
err5:
    iosDumpDMAStatus(0);
    iosDumpDMAStatus(1);
    iosDumpVIF1Status();
    iosDumpGIFStatus();
    LoaderSysPrintf(D_40048130);
    D_40045A90(*(volatile u32 *)0x10003C30);
    return -1;
sync:
    if (*(volatile s32 *)0x10009000 & 0x100)
    {
        do
        {
            if (++i > count)
                goto err1;
        } while (*(volatile s32 *)0x10009000 & 0x100);
    }
    while (*(volatile s32 *)0x1000A000 & 0x100)
    {
        if (++i > count)
            goto err2;
    }
    while (*(volatile s32 *)0x10003C00 & 0x1F000003)
    {
        if (++i > count)
            goto err3;
    }
    VU1_STAT(stat);
    while (stat & 0x100)
    {
        if (++i > count)
            goto err4;
        VU1_STAT(stat);
    }
    while (*(volatile s32 *)0x10003020 & 0xC00)
    {
        if (++i > count)
            goto err5;
    }
    return 0;
}

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/ios/graph/gs", func_400268A8);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/ios/graph/gs", func_40026BE0);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/ios/graph/gs", iosGsResizeRootDC);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/ios/graph/gs", iosGsSetMode);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/ios/graph/gs", iosGsSetDrawContext);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/ios/graph/gs", iosCopyFrameBuffer);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/ios/graph/gs", getDispScreenWidth);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/ios/graph/gs", getDispScreenHeight);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/ios/graph/gs", getDrawScreenWidth);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/ios/graph/gs", getDrawScreenHeight);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/ios/graph/gs", getFrameBufferSize);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/ios/graph/gs", getFrameBufferSizeFBP);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/ios/graph/gs", getFrameBufferSizeTBP);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/ios/graph/gs", getDispBufferAddressTBP);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/ios/graph/gs", getDispBufferAddressFBP);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/ios/graph/gs", getDrawBufferAddressTBP);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/ios/graph/gs", getDrawBufferAddressFBP);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/ios/graph/gs", getZBufferAddressTBP);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/ios/graph/gs", getZBufferAddressFBP);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/ios/graph/gs", getTextureAreaAddressTBP);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/ios/graph/gs", getTextureAreaAddressFBP);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/ios/graph/gs", getScreenOffsetX);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/ios/graph/gs", getScreenOffsetY);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/ios/graph/gs", getAntiAlias);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/ios/graph/gs", getProgressiveMode);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/ios/graph/gs", iosResetGraph);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/ios/graph/gs", iosDmaSendPath1);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/ios/graph/gs", iosDmaSendPath2);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/ios/graph/gs", iosDmaSendPath3);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/ios/graph/gs", iosDmaSendSChainPath1);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/ios/graph/gs", iosDmaSendSChainPath2);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/ios/graph/gs", iosDmaSendSChainPath3);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/ios/graph/gs", iosResetPath);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/ios/graph/gs", iosSyncV);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/ios/graph/gs", iosGetField);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/ios/graph/gs", iosGsChangeMode);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/ios/graph/gs", iosSetBGColor);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/ios/graph/gs", iosGsResetCRTC);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/ios/graph/gs", iosSetSyncNoReturnFunc);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/ios/graph/gs", iosSetScreenEnv);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/ios/graph/gs", iosCheckDrawFinish);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/ios/graph/gs", iosGsInitDC);
