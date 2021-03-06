/*
 * ATrap.c
 * Looks up by trap pumber the name of a Macintosh trap
 * Alternately dumps a list of all trap names and numbers
 * Written by Dan Allen 10/30/88
 * Name lookup added 2/1/89
 *
 * Fixed bug Ricky Zhang 7/5/2020
*/

#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include <string.h>

typedef struct trap {
	const char *name;
	uint16_t num;
} trap;

static trap list[] = {
	"Open", 0xA000, "Close", 0xA001,
	"Read", 0xA002, "Write", 0xA003,
	"Control", 0xA004, "Status", 0xA005,
	"KillIO", 0xA006, "GetVolinfo", 0xA007,
	"Create", 0xA008, "Delete", 0xA009,
	"0penRF", 0xA00A, "Rename", 0xA00B,
	"GetFileinfo", 0xA00C, "SetFinfo", 0xA00D,
	"UnmountVol", 0xA00E, "MountVol", 0xA00F,
	"Allocate", 0xA010, "GetEOF", 0xA011,
	"SetEOF", 0xA012, "FlushVol", 0xA013,
	"GetVol", 0xA014, "SetVol", 0xA015,
	"InitQueue", 0xA016, "Eject", 0xA017,
	"GetFPos", 0xA018, "InitZone", 0xA019,
	"GetZone", 0xA01A, "SetZone", 0xA01B,
	"FreeMem", 0xA01C, "MaxMem", 0xA01D,
	"NewPtr", 0xA01E, "DisposePtr", 0xA01F,
	"SetPtrSize", 0xA020, "GetPtrSize", 0xA021,
	"NewHandle", 0xA022, "DisposeHandle", 0xA023,
	"SetHandleSize", 0xA024, "GetHandleSize", 0xA025,
	"HandleZone", 0xA026, "ReallocHandle", 0xA027,
	"RecoverHandle", 0xA028, "HLock", 0xA029,
	"HUnlock", 0xA02A, "EmptyHandle", 0xA02B,
	"InitApplZone", 0xA02C, "SetApplLimit", 0xA02D,
	"BlockMove", 0xA02E, "PostEvent", 0xA02F,
	"OSEventAvail", 0xA030, "GetOSEvent", 0xA031,
	"FlushEvents", 0xA032, "VInstall", 0xA033,
	"VRemove", 0xA034, "0ffLine", 0xA035,
	"MoreMasters", 0xA036, "ReadParam", 0xA037,
	"WriteParam", 0xA038, "ReadDateTime", 0xA039,
	"SetDateTime", 0xA03A, "Delay", 0xA03B,
	"CmpString", 0xA03C, "Drvrinstall", 0xA03D,
	"DrvrRemove", 0xA03E, "InitUtil", 0xA03F,
	"ResrvMem", 0xA040, "SetFilLock", 0xA041,
	"RstFilLock", 0xA042, "SetFilType", 0xA043,
	"SetFPos", 0xA044, "FlushFile", 0xA045,
	"GetTrapAddress", 0xA046, "SetTrapAddress", 0xA047,
	"PtrZone", 0xA048, "HPurge", 0xA049,
	"HNoPurge", 0xA04A, "SetGrowZone", 0xA04B,
	"CompactMem", 0xA04C, "PurgeMem", 0xA04D,
	"AddDrive", 0xA04E, "RDrvrinstall", 0xA04F,
	"RelString", 0xA050, "ReadXPRam", 0xA051,
	"WriteXPRam", 0xA052, "ClkNoMem", 0xA053,
	"UprString", 0xA054, "StripAddress", 0xA055,
	"LwrString", 0xA056, "SetAppBase", 0xA057,
	"InsTime", 0xA058, "RmvTime", 0xA059,
	"PrimeTime", 0xA05A, "PowerOff", 0xA05B,
	"** Free **", 0xA05C, "SwapMMUMode", 0xA05D,
	"NMinstall", 0xA05E, "NMRemove", 0xA05F,
	"HFSDispatch", 0xA060, "MaxBlock", 0xA061,
	"PurgeSpace", 0xA062, "MaxApplZone", 0xA063,
	"MoveHHi", 0xA064, "StackSpace", 0xA065,
	"NewEmptyHandle", 0xA066, "HSetRBit", 0xA067,
	"HClrRBit", 0xA068, "HGetState", 0xA069,
	"HSetState", 0xA06A, "TestManager", 0xA06B,
	"InitFS", 0xA06C, "InitEvents", 0xA06D,
	"SlotManager", 0xA06E, "SlotVInstall", 0xA06F,
	"SlotVRemove", 0xA070, "AttachVBL", 0xA071,
	"DoVBLTask", 0xA072, "0SReserved", 0xA073,
	"** Free **", 0xA074, "Sintinstall", 0xA075,
	"SintRemove", 0xA076, "CountADBs", 0xA077,
	"GetindADB", 0xA078, "GetADBinfo", 0xA079,
	"SetADBinfo", 0xA07A, "ADBReinit", 0xA07B,
	"ADBOp", 0xA07C, "GetDefaultStartup", 0xA07D,
	"SetDefaultStartup", 0xA07E, "InternalWait", 0xA07F,
	"GetVideoDefault", 0xA080, "SetVideoDefault", 0xA081,
	"DTinstall", 0xA082, "SetOSDefault", 0xA083,
	"GetOSDefault", 0xA084, "PmgrOp", 0xA085,
	"SetIOPMsginfo", 0xA086, "IOPMsgAccess", 0xA087,
	"IOPMoveData", 0xA088, "SCSIAtomic", 0xA089,
	"Sleep", 0xA08A, "CommMgr", 0xA08B,
	"** Free **", 0xA08C, "**Free **", 0xA08D,
	"** Free**", 0xA08E, "** Free **", 0xA08F,
	"SysEnvirons", 0xA090, "SndDisposeChannel", 0xA801,
	"SndAddModifier", 0xA802, "SndDoCommand", 0xA803,
	"SndDoimmediate", 0xA804, "SndPlay", 0xA805,
	"SndControl", 0xA806, "SndNewChannel", 0xA807,
	"InitProcMenu", 0xA808, "GetCVariant", 0xA809,
	"GetWVariant", 0xA80A, "PopUpMenuSelect", 0xA80B,
	"RGetResource", 0xA80C, "CountlResources", 0xA80D,
	"Get1IxResource", 0xA80E, "GetlixType", 0xA80F,
	"UniquelID", 0xA810, "TESelView", 0xA811,
	"TEPinScroll", 0xA812, "TEAutoView", 0xA813,
	"SetFractEnable", 0xA814, "SCSIDispatch", 0xA815,
	"Pack8", 0xA816, "CopyMask", 0xA817,
	"FixATan2", 0xA818, "XMunger", 0xA819,
	"GetZone", 0xA81A, "SetZone", 0xA81B,
	"Count1Types", 0xA81C, "MaxMem", 0xA81D,
	"NewPtr", 0xA81E, "Get1Resource", 0xA81F,
	"Get1NamedResource", 0xA820, "MaxSizeRsrc", 0xA821,
	"NwHandle", 0xA822, "DsposeHandle", 0xA823,
	"SetHandleSize", 0xA824, "GetHandleSize", 0xA825,
	"InsMenuitem", 0xA826, "HideDitem", 0xA827,
	"ShowDitem", 0xA828, "HLock", 0xA829,
	"HUnLock", 0xA82A, "Pack9", 0xA82B,
	"Packl0", 0xA82C, "Packll", 0xA82D,
	"Packl2", 0xA82E, "Packl3", 0xA82F,
	"Packl4", 0xA830, "Packl5", 0xA831,
	"FlushEvents", 0xA832, "ScrnBitMap", 0xA833,
	"SetFScaleDisable", 0xA834, "FontMetrics", 0xA835,
	"GetMaskTable", 0xA836, "MeasureText", 0xA837,
	"CalcMask", 0xA838, "SeedFill", 0xA839,
	"ZoomWindow", 0xA83A, "TrackBox", 0xA83B,
	"TEGet0ffset", 0xA83C, "TEDispatch", 0xA83D,
	"TEStylNew", 0xA83E, "Long2Fix", 0xA83F,
	"Fix2Long", 0xA840, "Fix2Frac", 0xA841,
	"Frac2Fix", 0xA842, "Fix2X", 0xA843,
	"X2Fix", 0xA844, "Frac2X", 0xA845,
	"X2Frac", 0xA846, "FracCos", 0xA847,
	"FracSin", 0xA848, "FracSqrt", 0xA849,
	"FracMul", 0xA84A, "FracDiv", 0xA84B,
	"CompactMem", 0xA84C, "FixDiv", 0xA84D,
	"GetitemCmd", 0xA84E, "SetitemCmd", 0xA84F,
	"InitCursor", 0xA850, "SetCursor", 0xA851,
	"HideCursor", 0xA852, "ShowCursor", 0xA853,
	"UprString", 0xA854, "ShieldCursor", 0xA855,
	"0bscureCursor", 0xA856, "SetEntry", 0xA857,
	"BitAnd", 0xA858, "BitXor", 0xA859,
	"BitNot", 0xA85A, "BitOr", 0xA85B,
	"BitShift", 0xA85C, "BitTst", 0xA85D,
	"BitSet", 0xA85E, "BitClr", 0xA85F,
	"WaitNextEvent", 0xA860, "Random", 0xA861,
	"ForeColor", 0xA862, "BackColor", 0xA863,
	"ColorBit", 0xA864, "GetPixel", 0xA865,
	"StuffHex", 0xA866, "LongMul", 0xA867,
	"FixMul", 0xA868, "FixRatio", 0xA869,
	"HiWord", 0xA86A, "LoWord", 0xA86B,
	"FixRound", 0xA86C, "InitPort", 0xA86D,
	"InitGraf", 0xA86E, "OpenPort", 0xA86F,
	"LocalToGlobal", 0xA870, "GlobalToLocal", 0xA871,
	"GrafDevice", 0xA872, "SetPort", 0xA873,
	"GetPort", 0xA874, "SetPBits", 0xA875,
	"PortSize", 0xA876, "MovePortTo", 0xA877,
	"Set0rigin", 0xA878, "SetClip", 0xA879,
	"GetClip", 0xA87A, "ClipRect", 0xA87B,
	"BackPat", 0xA87C, "ClosePort", 0xA87D,
	"AddPt", 0xA87E, "SubPt", 0xA87F,
	"SetPt", 0xA880, "EqualPt", 0xA881,
	"StdText", 0xA882, "DrawChar", 0xA883,
	"DrawString", 0xA884, "DrawText", 0xA885,
	"TextWidth", 0xA886, "TextFont", 0xA887,
	"TextFace", 0xA888, "TextMode", 0xA889,
	"TextSize", 0xA88A, "GetFontinfo", 0xA88B,
	"StringWidth", 0xA88C, "CharWidth", 0xA88D,
	"SpaceExtra", 0xA88E, "OSDispatch", 0xA88F,
	"StdLine", 0xA890, "LineTo", 0xA891,
	"Line", 0xA892, "MoveTo", 0xA893,
	"Move", 0xA894, "ShutDown", 0xA895,
	"HidePen", 0xA896, "ShowPen", 0xA897,
	"GetPenState", 0xA898, "SetPenState", 0xA899,
	"GetPen", 0xA89A, "PenSize", 0xA89B,
	"PenMode", 0xA89C, "PenPat", 0xA89D,
	"PenNormal", 0xA89E, "Unimplemented", 0xA89F,
	"StdRect", 0xA8A0, "FrameRect", 0xA8A1,
	"PaintRect", 0xA8A2, "EraseRect", 0xA8A3,
	"InverRect", 0xA8A4, "FillRect", 0xA8A5,
	"EqualRect", 0xA8A6, "SetRect", 0xA8A7,
	"OffSetRect", 0xA8A8, "InsetRect", 0xA8A9,
	"SectRect", 0xA8AA, "UnionRect", 0xA8AB,
	"Pt2Rect", 0xA8AC, "PtinRect", 0xA8AD,
	"EmptyRect", 0xA8AE, "StdRRect", 0xA8AF,
	"FrameRoundRect", 0xA8B0, "PaintRoundRect", 0xA8B1,
	"EraseRoundRect", 0xA8B2, "InvertRoundRect", 0xA8B3,
	"FillRoundRect", 0xA8B4, "ScriptUtil", 0xA8B5,
	"Std0val", 0xA8B6, "FrameOval", 0xA8B7,
	"Paint0val", 0xA8B8, "EraseOval", 0xA8B9,
	"InvertOval", 0xA8BA, "FillOval", 0xA8BB,
	"SlopeFromAngle", 0xA8BC, "StdArc", 0xA8BD,
	"FrameArc", 0xA8BE, "PaintArc", 0xA8BF,
	"EraseArc", 0xA8C0, "InvertArc", 0xA8C1,
	"FillArc", 0xA8C2, "PtToAngle", 0xA8C3,
	"AngleFromSlope", 0xA8C4, "StdPoly", 0xA8C5,
	"FramePoly", 0xA8C6, "PaintPoly", 0xA8C7,
	"ErasePoly", 0xA8C8, "InvertPoly", 0xA8C9,
	"FillPoly", 0xA8CA, "OpenPoly", 0xA8CB,
	"ClosePoly", 0xA8CC, "KillPoly", 0xA8CD,
	"OffsetPoly", 0xA8CE, "PackBits", 0xA8CF,
	"UnpackBits", 0xA8D0, "StdRgn", 0xA8D1,
	"FrameRgn", 0xA8D2, "PaintRgn", 0xA8D3,
	"EraseRgn", 0xA8D4, "InvertRgn", 0xA8D5,
	"FillRgn", 0xA8D6, "BitMapRgn", 0xA8D7,
	"NewRgn", 0xA8D8, "DisposeRgn", 0xA8D9,
	"0penRgn", 0xA8DA, "CloseRgn", 0xA8DB,
	"CopyRgn", 0xA8DC, "S.etEmptyRgn", 0xA8DD,
	"SetRectRgn", 0xA8DE, "RectRgn", 0xA8DF,
	"OffsetRgn", 0xA8E0, "InsetRgn", 0xA8E1,
	"EmptyRgn", 0xA8E2, "EqualRgn", 0xA8E3,
	"SectRgn", 0xA8E4, "UnionRgn", 0xA8E5,
	"DiffRgn", 0xA8E6, "XorRgn", 0xA8E7,
	"PtinRgn", 0xA8E8, "RectinRgn", 0xA8E9,
	"SetStdProcs", 0xA8EA, "StdBits", 0xA8EB,
	"CopyBits", 0xA8EC, "StdTxMeas", 0xA8ED,
	"StdGetPic", 0xA8EE, "ScrollRect", 0xA8EF,
	"StdPutPic", 0xA8F0, "StdComment", 0xA8F1,
	"PicComment", 0xA8F2, "OpenPicture", 0xA8F3,
	"ClosePicture", 0xA8F4, "KillPictu.re", 0xA8F5,
	"DrawPicture", 0xA8F6, "** Free **", 0xA8F7,
	"ScalePt", 0xA8F8, "MapPt", 0xA8F9,
	"MapRect", 0xA8FA, "MapRgn", 0xA8FB,
	"MapPoly", 0xA8FC, "PrGlue", 0xA8FD,
	"InitFonts", 0xA8FE, "GetFontName", 0xA8FF,
	"GetFNum", 0xA900, "FMSwapFont", 0xA901,
	"RealFont", 0xA902, "SetFontLock", 0xA903,
	"DrawGrowicon", 0xA904, "DragGrayRgn", 0xA905,
	"NewString", 0xA906, "SetString", 0xA907,
	"ShowHide", 0xA908, "CalcVis", 0xA909,
	"CalcVBehind", 0xA90A, "ClipAbove", 0xA90B,
	"Paint0ne", 0xA90C, "PaintBehind", 0xA90D,
	"SaveOld", 0xA90E, "DrawNew", 0xA90F,
	"GetWMgrPort", 0xA910, "CheckUpdate", 0xA911,
	"InitWindows", 0xA912, "NewWindow", 0xA913,
	"DisposeWindow", 0xA914, "ShowWindow", 0xA915,
	"HideWindow", 0xA916, "GetWRefCon", 0xA917,
	"SetWRefCon", 0xA918, "GetWTitle", 0xA919,
	"SetWTitle", 0xA91A, "MoveWindow", 0xA91B,
	"HiliteWindow", 0xA91C, "SizeWindow", 0xA91D,
	"TrackGoAway", 0xA91E, "SelectWindow", 0xA91F,
	"BringToFront", 0xA920, "SendBehind", 0xA921,
	"BeginUpdate", 0xA922, "EndUpdate", 0xA923,
	"FrontWindow", 0xA924, "DragWindow", 0xA925,
	"DragTheRgn", 0xA926, "InvalRgn", 0xA927,
	"InvalRect", 0xA928, "ValidRgn", 0xA929,
	"ValidRect", 0xA92A, "GrowWindow", 0xA92B,
	"FindWindow", 0xA92C, "CloseWindow", 0xA92D,
	"SetWindowPic", 0xA92E, "GetWindowPic", 0xA92F,
	"InitMenus", 0xA930, "NewMenu", 0xA931,
	"DisposeMenu", 0xA932, "AppendMenu", 0xA933,
	"ClearMenuBar", 0xA934, "InsertMenu", 0xA935,
	"DeleteMenu", 0xA936, "DrawMenuBar", 0xA937,
	"HiliteMenu", 0xA938, "Enableitem", 0xA939,
	"Disableitem", 0xA93A, "GetMenuBar", 0xA93B,
	"SetMenuBar", 0xA93C, "MenuSelect", 0xA93D,
	"MenuKey", 0xA93E, "Getitmicon", 0xA93F,
	"Setitmicon", 0xA940, "GetitmStyle", 0xA941,
	"SetitmStyle", 0xA942, "GetitemMark", 0xA943,
	"SetitemMark", 0xA944, "Checkitem", 0xA945,
	"Getitem", 0xA946, "Setitem", 0xA947,
	"CalcMenuSize", 0xA948, "GetMHandle", 0xA949,
	"SetMenuFlash", 0xA94A, "Ploticon", 0xA94B,
	"FlashMenuBar", 0xA94C, "AddResMenu", 0xA94D,
	"PinRect", 0xA94E, "DeltaPoint", 0xA94F,
	"CountMitems", 0xA950, "InsertResMenu", 0xA951,
	"DelMenuitem", 0xA952, "UpdtControl", 0xA953,
	"NewControl", 0xA954, "DisposeControl", 0xA955,
	"KillControls", 0xA956, "ShowControl", 0xA957,
	"HideControl", 0xA958, "MoveControl", 0xA959,
	"GetCRefCoi:", 0xA95A, "SetCRefCon", 0xA95B,
	"SizeControl", 0xA95C, "HiliteControl", 0xA95D,
	"GetCTitle", 0xA95E, "SetCTitle", 0xA95F,
	"GetCtlValue", 0xA960, "GetMinCtl", 0xA961,
	"GetMaxCtl", 0xA962, "SetCtlValue", 0xA963,
	"SetMinCtl", 0xA964, "SetMaxCtl", 0xA965,
	"TestControl", 0xA966, "DragControl", 0xA967,
	"TrackControl", 0xA968, "DrawControls", 0xA969,
	"GetCtlAction", 0xA96A, "SetCtlAction", 0xA96B,
	"FindControl", 0xA96C, "Draw1Control", 0xA96D,
	"Dequeue", 0xA96E, "Enqueue", 0xA96F,
	"GetNextEvent", 0xA970, "EventAvail", 0xA971,
	"GetMouse", 0xA972, "Stilldown", 0xA973,
	"Button", 0xA974, "TickCount", 0xA975,
	"GetKeys", 0xA976, "WaitMouseUp", 0xA977,
	"UpdtDialog", 0xA978, "CouldDialog", 0xA979,
	"FreeDialog", 0xA97A, "InitDialogs", 0xA97B,
	"GetNewDialog", 0xA97C, "NewDialog", 0xA97D,
	"SelIText", 0xA97E, "IsDialogEvent", 0xA97F,
	"DialogSelect", 0xA980, "DrawDialog", 0xA981,
	"CloseDialog", 0xA982, "DisposeDialog", 0xA983,
	"FindDitem", 0xA984, "Alert", 0xA985,
	"StopAlert", 0xA986, "NoteAlert", 0xA987,
	"CautionAlert", 0xA988, "CouldAlert", 0xA989,
	"FreeAlert", 0xA98A, "ParamText", 0xA98B,
	"ErrorSound", 0xA98C, "GetDitem", 0xA98D,
	"SetDitem", 0xA98E, "SetIText", 0xA98F,
	"GetIText", 0xA990, "ModalDialog", 0xA991,
	"DetachResource", 0xA992, "SetResPurge", 0xA993,
	"CurResFile", 0xA994, "InitResources", 0xA995,
	"RsrcZoneinit", 0xA996, "0penResFile", 0xA997,
	"UseResFile", 0xA998, "UpdateResFile", 0xA999,
	"CloseResFile", 0xA99A, "SetResLoad", 0xA99B,
	"CountResources", 0xA99C, "GetindResource", 0xA99D,
	"CountTypes", 0xA99E, "GetindType", 0xA99F,
	"GetResource", 0xA9A0, "GetNamedResource", 0xA9A1,
	"LoadResource", 0xA9A2, "ReleaseResource", 0xA9A3,
	"HomeResFile", 0xA9A4, "SizeRsrc", 0xA9A5,
	"GetResAttrs", 0xA9A6, "SetResAttrs", 0xA9A7,
	"GetResinfo", 0xA9A8, "SetResinfo", 0xA9A9,
	"ChangedResource", 0xA9AA, "AddResource", 0xA9AB,
	"AddReference", 0xA9AC, "RmveResource", 0xA9AD,
	"RmveReference", 0xA9AE, "ResError", 0xA9AF,
	"WriteResource", 0xA9B0, "CreateResFile", 0xA9B1,
	"SystemEvent", 0xA9B2, "SystemClick", 0xA9B3,
	"SystemTask", 0xA9B4, "SystemMenu", 0xA9B5,
	"OpenDeskAcc", 0xA9B6, "CloseDeskAcc", 0xA9B7,
	"GetPattern", 0xA9B8, "GetCursor", 0xA9B9,
	"GetString", 0xA9BA, "Geticon", 0xA9BB,
	"GetPicture", 0xA9BC, "GetNewWindow", 0xA9BD,
	"GetNewControl", 0xA9BE, "GetRMenu", 0xA9BF,
	"GetNewMBar", 0xA9C0, "UniqueID", 0xA9C1,
	"SysEdit", 0xA9C2, "KeyTrans", 0xA9C3,
	"0penRFPerm", 0xA9C4, "RsrcMapEntry", 0xA9C5,
	"Secs2Date", 0xA9C6, "Date2Secs", 0xA9C7,
	"SysBeep", 0xA9C8, "SysError", 0xA9C9,
	"Puticon", 0xA9CA, "TEGetText", 0xA9CB,
	"TEinit", 0xA9CC, "TEDispose", 0xA9CD,
	"TextBox", 0xA9CE, "TESetText", 0xA9CF,
	"TECalText", 0xA9D0, "TESetSelect", 0xA9D1,
	"TENew", 0xA9D2, "TEUpdate", 0xA9D3,
	"TEClick", 0xA9D4, "TECopy", 0xA9D5,
	"TECut", 0xA9D6, "TEDelete", 0xA9D7,
	"TEActivate", 0xA9D8, "TEDeactivate", 0xA9D9,
	"TEidle", 0xA9DA, "TEPaste", 0xA9DB,
	"TEKey", 0xA9DC, "TEScroll", 0xA9DD,
	"TEinsert", 0xA9DE, "TESetJust", 0xA9DF,
	"Munger", 0xA9E0, "HandToHand", 0xA9E1,
	"PtrToXHand", 0xA9E2, "PtrToHand", 0xA9E3,
	"HandAndHand", 0xA9E4, "InitPack", 0xA9E5,
	"InitA11Packs", 0xA9E6, "Pack0", 0xA9E7,
	"Packl", 0xA9E8, "Pack2", 0xA9E9,
	"Pack3", 0xA9EA, "Pack4", 0xA9EB,
	"Pack5", 0xA9EC, "Pack6", 0xA9ED,
	"Pack7", 0xA9EE, "PtrAndHand", 0xA9EF,
	"LoadSeg", 0xA9F0, "UnloadSeg", 0xA9F1,
	"Launch", 0xA9F2, "Chain", 0xA9F3,
	"ExitToShell", 0xA9F4, "GetAppParms", 0xA9F5,
	"GetResFileAttrs", 0xA9F6, "SetResFileAttrs", 0xA9F7,
	"MethodDispatch", 0xA9F8, "InfoScrap", 0xA9F9,
	"UnloadScrap", 0xA9FA, "LoadScrap", 0xA9FB,
	"ZeroScrap", 0xA9FC, "GetScrap", 0xA9FD,
	"PutScrap", 0xA9FE, "Debugger", 0xA9FF,
	"OpenCPort", 0xAA00, "InitCPort", 0xAA01,
	"CloseCPort", 0xAA02, "NewPixMap", 0xAA03,
	"DisposePixMap", 0xAA04, "CopyPixMap", 0xAA05,
	"SetCPortPix", 0xAA06, "NewPixPat", 0xAA07,
	"DisposePixPat", 0xAA08, "CopyPixPat", 0xAA09,
	"PenPixPat", 0xAA0A, "BackPixPat", 0xAA0B,
	"GetPixPat", 0xAA0C, "MakeRGBPat", 0xAA0D,
	"FillCRect", 0xAA0E, "FillCOval", 0xAA0F,
	"FillCRoundRect", 0xAA10, "FillCArc", 0xAA11,
	"FillCRgn", 0xAA12, "FillCPoly", 0xAA13,
	"RGBForeColor", 0xAA14, "RGBBackColor", 0xAA15,
	"SetCPixel", 0xAA16, "GetCPixel", 0xAA17,
	"GetCTable", 0xAA18, "GetForeColor", 0xAA19,
	"GetBackColor", 0xAA1A, "GetCCursor", 0xAA1B,
	"SetCCursor", 0xAA1C, "AllocCursor", 0xAA1D,
	"GetCicon", 0xAA1E, "PlotCicon", 0xAA1F,
	"OpenCPicture", 0xAA20, "0pColor", 0xAA21,
	"HiliteColor", 0xAA22, "CharExtra", 0xAA23,
	"DisposeCTable", 0xAA24, "DisposeCicon", 0xAA25,
	"DisposeCCursor", 0xAA26, "GetMaxDevice", 0xAA27,
	"GetCTSeed", 0xAA28, "GetDeviceList", 0xAA29,
	"GetMainDevice", 0xAA2A, "GetNextDevice", 0xAA2B,
	"TestDeviceAttribute", 0xAA2C, "SetDeviceAttribute", 0xAA2D,
	"InitGDevice", 0xAA2E, "NewGDevice", 0xAA2F,
	"DisposeGDevice", 0xAA30, "SetGDevice", 0xAA31,
	"GetGDevice", 0xAA32, "Color2Index", 0xAA33,
	"Index2Color", 0xAA34, "InvertColor", 0xAA35,
	"RealColor", 0xAA36, "GetSubTable", 0xAA37,
	"UpdatePixMap", 0xAA38, "MakeITable", 0xAA39,
	"AddSearch", 0xAA3A, "AddComp", 0xAA3B,
	"SetClientID", 0xAA3C, "ProtectEntry", 0xAA3D,
	"ReserveEntry", 0xAA3E, "SetEntries", 0xAA3F,
	"QDError", 0xAA40, "SetWinColor", 0xAA41,
	"GetAuxWin", 0xAA42, "SetCtlColor", 0xAA43,
	"GetAuxCtl", 0xAA44, "NewCWindow", 0xAA45,
	"GetNewCWindow", 0xAA46, "SetDeskCPat", 0xAA47,
	"GetCWMgrPort", 0xAA48, "SaveEntries", 0xAA49,
	"RestoreEntries", 0xAA4A, "NewCDialog", 0xAA4B,
	"DelSearch", 0xAA4C, "DelComp", 0xAA4D,
	"SetStdCProcs", 0xAA4E, "CalcCMask", 0xAA4F,
	"SeedCFill", 0xAA50, "** Free **", 0xAA51,
	"**Free **", 0xAA52, "** Free **", 0xAA53,
	"** Free **", 0xAA54, "**Free **", 0xAA55,
	"** Free **", 0xAA56, "** Free **", 0xAA57,
	"** Free **", 0xAA58, "** Free **", 0xAA59,
	"** Free **", 0xAA5A, "**Free ** ", 0xAA5B,
	"** Free **", 0xAA5C, "** Free **", 0xAA5D,
	"**Free **", 0xAA5E, "** Free **", 0xAA5F,
	"DelMCEntries", 0xAA60, "GetMCinfo", 0xAA61,
	"SetMCinfo", 0xAA62, "DispMCinfo", 0xAA63,
	"GetMCEntry", 0xAA64, "SetMCEntries", 0xAA65,
	"MenuChoice", 0xAA66, "* * Free **", 0xAA67,
	"** Free **", 0xAA68, "** Free **", 0xAA69,
	"** Free **", 0xAA6A, "** Free **", 0xAA6B,
	"** Free **", 0xAA6C, "* * Free **", 0xAA6D,
	"** Free **", 0xAA6E, "** Free **", 0xAA6F,
	"** Free **", 0xAA70, "** Free **", 0xAA71,
	"** Free **", 0xAA72, "** Free **", 0xAA73,
	"** Free **", 0xAA74, "** Free **", 0xAA75,
	"** Free **", 0xAA76, "** Free **", 0xAA77,
	"** Free **", 0xAA78, "** Free **", 0xAA79,
	"** Free **", 0xAA7A, "** Free **", 0xAA7B,
	"** Free **", 0xAA7C, "** Free **", 0xAA7D,
	"** Free **", 0xAA7E, "** Free **", 0xAA7F,
	"** Free **", 0xAA80, "** Free **", 0xAA81,
	"** Free **", 0xAA82, "** Free **", 0xAA83,
	"** Free **", 0xAA84, "** Free **", 0xAA85,
	"** Free **", 0xAA86, "** Free **", 0xAA87,
	"* * Free **", 0xAA88, "** Free **", 0xAA89,
	"** Free **", 0xAA8A, "**Free **", 0xAA8B,
	"** Free **", 0xAA8C, "** Free **", 0xAA8D,
	"**Free **", 0xAA8E, "** Free **", 0xAA8F,
	"InitPalettes", 0xAA90, "NewPalette", 0xAA91,
	"GetNewPalette", 0xAA92, "DisposePalette", 0xAA93,
	"ActivatePalette", 0xAA94, "SetPalette", 0xAA95,
	"GetPalette", 0xAA96, "PmForeColor", 0xAA97,
	"PmBackColor", 0xAA98, "AnimateEntry", 0xAA99,
	"AnimatePalette", 0xAA9A, "GetEntryColor", 0xAA9B,
	"SetEntryColor", 0xAA9C, "GetEntryUsage", 0xAA9D,
	"GetEntryUsage", 0xAA9E, "CTab2Palette", 0xAA9F,
	"Palette2CTab", 0xAAA0, "CopyPalette", 0xAAA1
} ;


int main(int argc,char *argv[])
{
	uint16_t i, n;
	trap *p;
	if (argc == 2 && sscanf(argv[1],"%hX",&i) == 1)
	{
        printf("Get input A-Trap number: %4X\n", i);
		if (i > 0xA800 && i <= 0xAAA1) {
            uint16_t offset = i - 0xA801;
            uint16_t index = offset + 0x91;
			printf("%4X %s\n",list[index].num,list[index].name);
        } else if (i >= 0xA000 && i <= 0xA090) {
            uint16_t index = i - 0xA000;
			printf("%4X %s\n",list[index].num,list[index].name);
        } else {
            printf("Invalid A-Trap number.\n");
        }
		return 0;
	}


	i = sizeof(list)/sizeof(trap);

	if (argc == 2 && isalpha(argv[1][0])) {
		for (p = &list[0]; i--; p++)
			if (strstr(p->name,argv[1]))
				printf("%X\t%s\n",p->num,p->name);
	} else {
		for (p = &list[0]; i--; p++)
			printf("%X\t%s\n",p->num,p->name);
	}
	return 0;

}
