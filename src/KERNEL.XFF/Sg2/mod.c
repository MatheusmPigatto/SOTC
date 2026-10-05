#include "common.h"

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/Sg2/mod", func_40032AC0);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/Sg2/mod", func_40032C10);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/Sg2/mod", all_keyoff);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/Sg2/mod", all_soundoff);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/Sg2/mod", all_soundpause);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/Sg2/mod", all_soundmute);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/Sg2/mod", Sg2ModMidiout1);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/Sg2/mod", Sg2ModMidiout1Exclusive);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/Sg2/mod", Sg2ModMidiout);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/Sg2/mod", Sg2ModTickProc);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/Sg2/mod", Sg2ModOpenBgm);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/Sg2/mod", Sg2ModOpenSe);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/Sg2/mod", Sg2ModCheckSndOn);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/Sg2/mod", Sg2ModClose);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/Sg2/mod", Sg2ModSetParam);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/Sg2/mod", Sg2ModGetParam);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/Sg2/mod", Sg2ModSetOutputMode);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/Sg2/mod", Sg2ModInit);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/Sg2/mod", debug_mod_config);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/Sg2/mod", func_40034800);

typedef struct
{
    u8 b0, b1, b2;
    s8 b3;
    u16 h4, h6, h8;
    u8 bA, bB, bC, bD, bE, bF;
} Sg2Rgn;

typedef struct
{
    u8 b0, b1, b2, b3, b4, b5, b6;
} Sg2Prog;

typedef struct
{
    s32 x0, x4, x8, xC, x10, x14;
    s32 x18;
    s32 x1C, x20, x24, x28, x2C, x30, x34, x38;
    f32 f3C;
    s32 x40;
    s16 h44, h46;
    s32 x48, x4C, x50, x54, x58;
    u16 h5C, h5E, h60, h62;
    s32 x64;
    Sg2Prog *x68;
    Sg2Rgn *x6C;
} Sg2Ch;

typedef struct
{
    s32 x0, x4, x8;
    u32 xC;
    s32 x10, x14, x18;
    s32 pad1C[5];
    s32 x30, x34, x38, x3C, x40, x44;
    s32 pad48[3];
    s32 x54, x58;
    u16 *x5C;
    s32 pad60[(0x2B0 - 0x60) / 4];
    Sg2Ch ch[16];
} Sg2Work;

typedef struct
{
    char pad0[0x4C];
    s32 x4C;
    u8 *x50;
    char pad54[0x9B0 - 0x54];
} Sg2Bank;

extern s32 D_400F9048;
extern u8 *D_400F904C;
extern Sg2Work *D_400F9050;
extern Sg2Bank D_400F9058[];

s32 Sg2SlotFreeSearch();
s32 Sg2SlotSearchParamOlder1();
s32 Sg2SlotSearchTypeOlder();
s32 Sg2SlotFindSlotClassChSsaBaseNote();
void Sg2SlotSetBasicParam();
void Sg2SlotSetLfoPitchTbl();
void Sg2SlotSetBendRange();
s32 Sg2SlotSetBendValue();
void Sg2SlotSetLfoPitchSpeed();
void Sg2SlotSetLfoPitchDepth();
void Sg2SlotSetLfoVolSpeed();
void Sg2SlotSetLfoVolDepth();
void Sg2SlotSetDumperOn();
void Sg2SlotSetReverbOnBit();
void Sg2SlotSetReverbOffBit();
void Sg2SlotSetMasTune();
void Sg2SlotSetPitch();
void Sg2SlotSetMasPan();
void Sg2SlotSetBasePan();
void Sg2SlotSetPan();
void Sg2SlotSetVolPhase();
void Sg2SlotSetMasVol();
void Sg2SlotSetBaseVol();
void Sg2SlotSetVol();
s32 Sg2SlotSetSsa();
void Sg2SlotSetAdsr();
void Sg2SlotSetKeyOnBit();
void Sg2SlotSetPoltamentParam();
void Sg2SlotModKeyOff();

#define SLOT_BANK(s) ((s) < 0x18 ? 0 : 1)
#define SLOT_BIT(s) ((s) < 0x18 ? 1 << (s) : 1 << ((s) - 0x18))

void func_40034838(void)
{
    s32 out[48];
    s32 ch;
    Sg2Ch *p;

    ch = D_400F904C[0] & 0xF;
    p = &D_400F9050->ch[ch];
    if (D_400F904C[2] != 0)
    {
        p->x0 = D_400F9048;
        p->x1C = D_400F904C[1];
        p->x18 = D_400F904C[2];
        p->x40 = -1;
        if (D_400F9050->ch[ch].x38 == 0)
        {
            s32 cnt, flag, note, trans;
            s32 i, start, slot, grp, tone, pan, pan2, ar, sr, e0, e1, e2, e3;
            u64 vol;
            Sg2Prog *prog;
            Sg2Rgn *rgn;

            if (D_400F9050->x30 != 0)
                return;
            if (D_400F9050->x34 == 0 && D_400F9050->x38 == 0)
                return;
            if (p->x10 != 0)
                return;
            if (p->x14 == 0)
                return;
            if (p->x18 == 0)
                return;
            if (p->x20 == 0)
                return;
            prog = p->x68;
            if (prog == 0)
                return;
            rgn = p->x6C;
            if (rgn == 0)
                return;
            if (p->x2C != 0)
            {
                note = p->x1C + D_400F9050->x40;
                trans = D_400F9050->x40;
            }
            else
            {
                note = p->x1C;
                trans = 0;
            }
            if (prog->b6 - note > 0)
                return;
            flag = 0;
            if (prog->b0 == 0xFF)
            {
                cnt = note - prog->b6;
                start = cnt;
            }
            else
            {
                if (prog->b0 & 0x80)
                {
                    flag = 1;
                    cnt = prog->b0 - 0x80;
                }
                else
                {
                    cnt = prog->b0;
                }
                start = 0;
            }
            rgn += start;
            for (i = start; i <= cnt; i++, rgn++)
            {
                if ((note >= rgn->b0 && note <= rgn->b1) || prog->b0 == 0xFF)
                {
                    if (rgn->bD == 0xFF)
                        return;
                    grp = D_400F9050->x18;
                    slot = Sg2SlotFreeSearch(grp);
                    if (slot == -1)
                    {
                        slot = Sg2SlotSearchParamOlder1(grp, 1, D_400F9050->x4, ch);
                        if (slot == -1)
                        {
                            slot = Sg2SlotSearchTypeOlder(grp, 1);
                        }
                    }
                    Sg2SlotSetBasicParam(1, slot, D_400F9050->x4, D_400F9050->x0, ch, 0);
                    if ((rgn->bF & 0x40) == 0)
                    {
                        tone = rgn->bE;
                    }
                    else
                    {
                        tone = prog->b5;
                    }
                    if (D_400F9050->x54 > 0)
                    {
                        Sg2SlotSetLfoPitchTbl(slot, D_400F9050->x58 + D_400F9050->x5C[tone]);
                    }
                    if (rgn->bF & 0x10)
                    {
                        Sg2SlotSetBendRange(slot, prog->b4);
                    }
                    else
                    {
                        Sg2SlotSetBendRange(slot, rgn->bD);
                    }
                    Sg2SlotSetBendValue(slot, p->x34);
                    if ((rgn->bF & 0x20) || p->x4C + p->x50 != 0)
                    {
                        Sg2SlotSetLfoPitchSpeed(slot, p->x4C);
                        Sg2SlotSetLfoPitchDepth(slot, p->x50);
                    }
                    if (p->x54 + p->x58 != 0)
                    {
                        Sg2SlotSetLfoVolSpeed(slot, p->x54);
                        Sg2SlotSetLfoVolDepth(slot, p->x58);
                    }
                    if (p->x30 != 0)
                    {
                        Sg2SlotSetDumperOn(slot);
                    }
                    if (p->x24 == 0x7F || (rgn->bF & 0x80))
                    {
                        Sg2SlotSetReverbOnBit(SLOT_BANK(slot), SLOT_BIT(slot));
                    }
                    else
                    {
                        Sg2SlotSetReverbOffBit(SLOT_BANK(slot), SLOT_BIT(slot));
                    }
                    Sg2SlotSetMasTune(slot, D_400F9050->x44);
                    Sg2SlotSetPitch(slot, p->x1C, trans, rgn->b2, rgn->b3, p->x48);
                    Sg2SlotSetMasPan(slot, D_400F9050->x3C);
                    pan = p->xC;
                    if (pan > 0x7F)
                        pan = 0x7F;
                    if (pan <= 0)
                        pan = 1;
                    Sg2SlotSetBasePan(slot, pan);
                    pan2 = rgn->bC;
                    if (pan2 > 0x7F)
                        pan2 = 0x7F;
                    if (pan2 <= 0)
                        pan2 = 1;
                    Sg2SlotSetPan(slot, pan2);
                    Sg2SlotSetVolPhase(slot, p->h44, p->h46);
                    Sg2SlotSetMasVol(slot, D_400F9050->x34, D_400F9050->x38);
                    vol = p->x14;
                    vol *= p->x20;
                    vol *= p->x68->b1;
                    vol *= rgn->bB;
                    vol /= 0x1F417F;
                    Sg2SlotSetBaseVol(slot, (s32)vol);
                    if (D_400F9058[p->x0].x4C == 0)
                    {
                        vol = p->x18;
                    }
                    else
                    {
                        vol = D_400F9058[p->x0].x50[p->x18];
                    }
                    Sg2SlotSetVol(slot, (s32)vol);
                    vol = (rgn->h4 << D_400F9050->x8) + D_400F9050->xC;
                    Sg2SlotSetSsa(slot, (s32)vol);
                    ar = rgn->h6;
                    e0 = p->h5C;
                    if (e0 != 0)
                        ar = e0 | (ar & 0x80FF);
                    e1 = p->h5E;
                    if (e1 != 0)
                        ar = e1 | (ar & 0xFF0F);
                    sr = rgn->h8;
                    e2 = p->h60;
                    if (e2 != 0)
                        sr = e2 | (sr & 0x803F);
                    e3 = p->h62;
                    if (e3 != 0)
                        sr = e3 | (sr & 0xFFE0);
                    Sg2SlotSetAdsr(slot, ar, sr);
                    Sg2SlotSetKeyOnBit(SLOT_BANK(slot), SLOT_BIT(slot));
                    if (flag == 0)
                        return;
                }
            }
        }
        else
        {
            Sg2Work *w;
            s32 cnt, flag, note, trans, ssa;
            s32 i, start, slot, grp, tone, pan, pan2, ar, sr, e0, e1, e2, e3;
            u64 vol;
            Sg2Prog *prog;
            Sg2Rgn *rgn;

            w = D_400F9050;
            p = &w->ch[ch];
            if (w->x30 != 0)
                return;
            if (w->x34 == 0 && w->x38 == 0)
                return;
            if (p->x10 != 0)
                return;
            if (p->x14 == 0)
                return;
            if (p->x18 == 0)
                return;
            if (p->x20 == 0)
                return;
            prog = p->x68;
            if (prog == 0)
                return;
            rgn = p->x6C;
            if (rgn == 0)
                return;
            if (p->x2C != 0)
            {
                note = p->x1C + D_400F9050->x40;
                trans = D_400F9050->x40;
            }
            else
            {
                note = p->x1C;
                trans = 0;
            }
            if (prog->b6 - note > 0)
                return;
            flag = 0;
            if (prog->b0 == 0xFF)
            {
                cnt = note - prog->b6;
                start = cnt;
            }
            else
            {
                if (prog->b0 & 0x80)
                {
                    flag = 1;
                    cnt = prog->b0 - 0x80;
                }
                else
                {
                    cnt = prog->b0;
                }
                start = 0;
            }
            rgn += start;
            for (i = start; i <= cnt; i++, rgn++)
            {
                if ((note >= rgn->b0 && note <= rgn->b1) || prog->b0 == 0xFF)
                {
                    if (rgn->bD == 0xFF)
                        return;
                    vol = (rgn->h4 << D_400F9050->x8) + D_400F9050->xC;
                    ssa = (s32)vol;
                    if (Sg2SlotFindSlotClassChSsaBaseNote(out, D_400F9050->x4, ch, ssa, rgn->b2) > 0)
                    {
                        Sg2SlotSetPoltamentParam(out[0], p->x1C, p->f3C);
                        continue;
                    }
                    grp = D_400F9050->x18;
                    slot = Sg2SlotFreeSearch(grp);
                    if (slot == -1)
                    {
                        slot = Sg2SlotSearchParamOlder1(grp, 1, D_400F9050->x4, ch);
                        if (slot == -1)
                        {
                            slot = Sg2SlotSearchTypeOlder(grp, 1);
                        }
                    }
                    Sg2SlotSetBasicParam(1, slot, D_400F9050->x4, D_400F9050->x0, ch, 0);
                    if ((rgn->bF & 0x40) == 0)
                    {
                        tone = rgn->bE;
                    }
                    else
                    {
                        tone = prog->b5;
                    }
                    if (D_400F9050->x54 > 0)
                    {
                        Sg2SlotSetLfoPitchTbl(slot, D_400F9050->x58 + D_400F9050->x5C[tone]);
                    }
                    if (rgn->bF & 0x10)
                    {
                        Sg2SlotSetBendRange(slot, prog->b4);
                    }
                    else
                    {
                        Sg2SlotSetBendRange(slot, rgn->bD);
                    }
                    Sg2SlotSetBendValue(slot, p->x34);
                    if ((rgn->bF & 0x20) || p->x4C + p->x50 != 0)
                    {
                        Sg2SlotSetLfoPitchSpeed(slot, p->x4C);
                        Sg2SlotSetLfoPitchDepth(slot, p->x50);
                    }
                    if (p->x54 + p->x58 != 0)
                    {
                        Sg2SlotSetLfoVolSpeed(slot, p->x54);
                        Sg2SlotSetLfoVolDepth(slot, p->x58);
                    }
                    if (p->x30 != 0)
                    {
                        Sg2SlotSetDumperOn(slot);
                    }
                    if (p->x24 == 0x7F || (rgn->bF & 0x80))
                    {
                        Sg2SlotSetReverbOnBit(SLOT_BANK(slot), SLOT_BIT(slot));
                    }
                    else
                    {
                        Sg2SlotSetReverbOffBit(SLOT_BANK(slot), SLOT_BIT(slot));
                    }
                    Sg2SlotSetMasTune(slot, D_400F9050->x44);
                    Sg2SlotSetPitch(slot, p->x1C, trans, rgn->b2, rgn->b3, p->x48);
                    Sg2SlotSetMasPan(slot, D_400F9050->x3C);
                    pan = p->xC;
                    if (pan > 0x7F)
                        pan = 0x7F;
                    if (pan <= 0)
                        pan = 1;
                    Sg2SlotSetBasePan(slot, pan);
                    pan2 = rgn->bC;
                    if (pan2 > 0x7F)
                        pan2 = 0x7F;
                    if (pan2 <= 0)
                        pan2 = 1;
                    Sg2SlotSetPan(slot, pan2);
                    Sg2SlotSetVolPhase(slot, p->h44, p->h46);
                    Sg2SlotSetMasVol(slot, D_400F9050->x34, D_400F9050->x38);
                    vol = p->x14;
                    vol *= p->x20;
                    vol *= p->x68->b1;
                    vol *= rgn->bB;
                    vol /= 0x1F417F;
                    Sg2SlotSetBaseVol(slot, (s32)vol);
                    if (D_400F9058[p->x0].x4C == 0)
                    {
                        vol = p->x18;
                    }
                    else
                    {
                        vol = D_400F9058[p->x0].x50[p->x18];
                    }
                    Sg2SlotSetVol(slot, (s32)vol);
                    Sg2SlotSetSsa(slot, ssa);
                    ar = rgn->h6;
                    e0 = p->h5C;
                    if (e0 != 0)
                        ar = e0 | (ar & 0x80FF);
                    e1 = p->h5E;
                    if (e1 != 0)
                        ar = e1 | (ar & 0xFF0F);
                    sr = rgn->h8;
                    e2 = p->h60;
                    if (e2 != 0)
                        sr = e2 | (sr & 0x803F);
                    e3 = p->h62;
                    if (e3 != 0)
                        sr = e3 | (sr & 0xFFE0);
                    Sg2SlotSetAdsr(slot, ar, sr);
                    Sg2SlotSetKeyOnBit(SLOT_BANK(slot), SLOT_BIT(slot));
                    if (flag == 0)
                        return;
                }
            }
        }
    }
    else
    {
        Sg2SlotModKeyOff(D_400F9050->x4, D_400F904C[0] & 0xF, D_400F904C[1]);
    }
}

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/Sg2/mod", func_40035408);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/Sg2/mod", func_40035A50);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/Sg2/mod", func_40035A88);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/Sg2/mod", func_40035B28);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/Sg2/mod", func_40035BC8);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/Sg2/mod", func_40035C68);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/Sg2/mod", func_40035D10);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/Sg2/mod", func_40035D80);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/Sg2/mod", func_40035F80);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/Sg2/mod", func_40035FB8);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/Sg2/mod", func_40035FF0);

void func_40036028(void) {
}

void func_40036030(void) {
}

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/Sg2/mod", func_40036038);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/Sg2/mod", func_400360C0);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/Sg2/mod", func_400360F8);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/Sg2/mod", func_40036148);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/Sg2/mod", func_400361A0);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/Sg2/mod", func_400361F8);

void func_40036250(void) {
}

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/Sg2/mod", func_40036258);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/Sg2/mod", func_40036290);

void func_40036330(void) {
}

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/Sg2/mod", func_40036338);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/Sg2/mod", func_40036370);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/Sg2/mod", func_400363A8);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/Sg2/mod", func_40036450);

void func_400364E8(void) {
}

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/Sg2/mod", func_400364F0);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/Sg2/mod", func_40036528);

void func_400365B0(void) {
}

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/Sg2/mod", func_400365B8);

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/Sg2/mod", func_40036660);

void func_40036BE0(void) {
}

void func_40036BE8(void) {
}

void func_40036BF0(void) {
}

void func_40036BF8(void) {
}

INCLUDE_ASM("asm/KERNEL.XFF/nonmatchings/Sg2/mod", func_40036C00);

void func_40036CE0(void) {
}
