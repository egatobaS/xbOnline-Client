#include "main.h"

unsigned int * BF4_addr_s_PatchID = 0;
Security * BF4_addr_s_Data = 0;

struct Vector3
{
	float x, y, z;
};

struct Vector2
{
	float x, y;
};

typedef struct Vector4
{
	float x, y, z, a;
	Vector4()
	{
		x = y = z = a = 0;
	}
	Vector4(float x, float y, float z, float a)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->a = a;
	}

} Vector4, *PVector4;

/*
TL-------------------TR
|					  |
|					  |
|					  |
BL-------------------BR
*/

struct MatrixCoords
{
	/*
	float TL_X;	//0x70
	float TL_Y;	//0x74
	float TL_Z;	//0x78
	*/
	Vector3 TL;

	/*
	float TR_X;	//0x7C
	float TR_Y;	//0x80
	float TR_Z;	//0x84
	*/
	Vector3 TR;

	/*
	float BR_X;	//0x88
	float BR_Y;	//0x8C
	float BR_Z;	//0x90
	*/
	Vector3 BR;

	/*
	float BL_X; //0x94
	float BL_Y; //0x98
	float BL_Z;	//0x9C
	*/
	Vector3 BL;
};

struct GAME_ADDRESSES_BF4
{
	int _0x89916E74; //0x89916E74
	int _0x1218;	 //0x1218    
	int _0x1288;	 //0x1288    
	int _0x12f8;	 //0x12f8    
	int _0x1448;	 //0x1448    
	int _0x14b8;	 //0x14b8    
	int _0x1528;	 //0x1528    
	int _0x700;		 //0x700     
	int _0x14;		 //0x14      
	int _0xA0;		 //0xA0      
	int _0x1000;	 //0x1000    
	int _0x58;		 //0x58      
	int _0x2A8;		 //0x2A8     
	int _0x8991B90C; //0x8991B90C
	int _0x88AA3798; //0x88AA3798
	int _0x88AA5E40; //0x88AA5E40
	int _0x88A9F9B8; //0x88A9F9B8
	int _0x8852B0A0; //0x8852B0A0
	int _0x88AA2C80; //0x88AA2C80
	int _0x88548C90; //0x88548C90
	int _0x88A94758; //0x88A94758
	int _0x886608C4; //0x886608C4
	int _0x887620c0; //0x887620c0
	int _0x88762008; //0x88762008
	int _0x88759DBC; //0x88759DBC
	int _0x48A94BE1; //0x48A94BE1
	int _0x8873E1E4; //0x8873E1E4
	int _0x484c5711; //0x484c5711
	int _0x88D0D6AC; //0x88D0D6AC
	int _0x3D6089A3; //0x3D6089A3
	int _0x616BF168; //0x616BF168
	int _0x906B0000; //0x906B0000
	int _0x60000000; //0x60000000
	int _0x8815DB54; //0x8815DB54
	int _0x89158D00; //0x89158D00
	int _0x885F4E54; //0x885F4E54
	int _0x885F4EEC; //0x885F4EEC
	int _0x885F410C; //0x885F410C
	int _0x885F4114; //0x885F4114
	int _0x885F4DB8; //0x885F4DB8
	int _0x885F4E1C; //0x885F4E1C
	int _0x88623830; //0x88623830
	int _0x88623838; //0x88623838
	int _0x886236EC; //0x886236EC
	int _0x88628E40; //0x88628E40
	int _0x497423f0; //0x497423f0
	int _0x4800004C; //0x4800004C
	int _0x48000034; //0x48000034
	int _0x480002FC; //0x480002FC
	int _0x409A0034; //0x409A0034
	int _0x1000038C; //0x1000038C
	int _0x41300000; //0x41300000
	int _0x4099004C; //0x4099004C
	int _0xD3350020; //0xD3350020
	int _0x92D50040; //0x92D50040
	int _0x419A0430; //0x419A0430
	int _0x409900D0; //0x409900D0
	int _0x11BFD9C3; //0x11BFD9C3
	int _0x915F0040; //0x915F0040
	int _0x11BED9C3; //0x11BED9C3
	int _0x7FE3FB78; //0x7FE3FB78
	int _0x8991B78C; //0x8991B78C
	int _0x150;		 //0x150     
	int _0x89916E78; //0x89916E78
	int _0x34;		 //0x34      
	int _0x18;		 //0x18      
	int _0x3644;	 //0x3644    
	int _0x2090;	 //0x2090    
	int _0x10;		 //0x10      
	int _0x89A39F28; //0x89A39F28
	int _0x5C;		 //0x5C      
	int _0x20;		 //0x20      
	int _0x89A10B10; //0x89A10B10
	int _0x89A39D48; //0x89A39D48
	int _0x89A39DE8; //0x89A39DE8
	int _0x89A38D38; //0x89A38D38
	int _0x880330E8; //0x880330E8
	int _0x897C150C; //0x897C150C
	int _0x897C1510; //0x897C1510
	int _0x88C06B54; //0x88C06B54
	int _0x89168184; //0x89168184
	int _0x88B59AEC; //0x88B59AEC
	int _0x88C0D9F4; //0x88C0D9F4
	int _0x88C0DA00; //0x88C0DA00
	int _0x48000040; //0x48000040
	int _0x419A0040; //0x419A0040
	int _0x419A0020; //0x419A0020
	int _0x7C8B2378; //0x7C8B2378
	int _0x39200001; //0x39200001
	int _0x988B0000; //0x988B0000
	int _0x39600000; //0x39600000
	int _0x882FB7B8; //0x882FB7B8
	int _0x88B9FD58; //0x88B9FD58
	int _0x88AD3A28; //0x88AD3A28
	int _0x88D0D6A8; //0x88D0D6A8
	int _0x88763360; //0x88763360
	int _0x88679E80; //0x88679E80
	int _0x88AA1FC8; //0x88AA1FC8
	int _0x8856A310; //0x8856A310
	int _0x915C00F0; //0x915C00F0
	int _0x4BFFFAD9; //0x4BFFFAD9
	int _0x913F00F0; //0x913F00F0

#if defined(DEVKIT)

	void SetAddress()
	{
		_0x89916E74 = 0x89916E74;
		_0x1218 = 0x1218;
		_0x1288 = 0x1288;
		_0x12f8 = 0x12f8;
		_0x1448 = 0x1448;
		_0x14b8 = 0x14b8;
		_0x1528 = 0x1528;
		_0x700 = 0x700;
		_0x14 = 0x14;
		_0xA0 = 0xA0;
		_0x1000 = 0x1000;
		_0x58 = 0x58;
		_0x2A8 = 0x2A8;
		_0x8991B90C = 0x8991B90C;
		_0x88AA3798 = 0x88AA3798;
		_0x88AA5E40 = 0x88AA5E40;
		_0x88A9F9B8 = 0x88A9F9B8;
		_0x8852B0A0 = 0x8852B0A0;
		_0x88AA2C80 = 0x88AA2C80;
		_0x88548C90 = 0x88548C90;
		_0x88A94758 = 0x88A94758;
		_0x886608C4 = 0x886608C4;
		_0x887620c0 = 0x887620c0;
		_0x88762008 = 0x88762008;
		_0x88759DBC = 0x88759DBC;
		_0x48A94BE1 = 0x48A94BE1;
		_0x8873E1E4 = 0x8873E1E4;
		_0x484c5711 = 0x484c5711;
		_0x88D0D6AC = 0x88D0D6AC;
		_0x3D6089A3 = 0x3D6089A3;
		_0x616BF168 = 0x616BF168;
		_0x906B0000 = 0x906B0000;
		_0x60000000 = 0x60000000;
		_0x8815DB54 = 0x8815DB54;
		_0x89158D00 = 0x89158D00;
		_0x885F4E54 = 0x885F4E54;
		_0x885F4EEC = 0x885F4EEC;
		_0x885F410C = 0x885F410C;
		_0x885F4114 = 0x885F4114;
		_0x885F4DB8 = 0x885F4DB8;
		_0x885F4E1C = 0x885F4E1C;
		_0x88623830 = 0x88623830;
		_0x88623838 = 0x88623838;
		_0x886236EC = 0x886236EC;
		_0x88628E40 = 0x88628E40;
		_0x497423f0 = 0x497423f0;
		_0x4800004C = 0x4800004C;
		_0x48000034 = 0x48000034;
		_0x480002FC = 0x480002FC;
		_0x409A0034 = 0x409A0034;
		_0x1000038C = 0x1000038C;
		_0x41300000 = 0x41300000;
		_0x4099004C = 0x4099004C;
		_0xD3350020 = 0xD3350020;
		_0x92D50040 = 0x92D50040;
		_0x419A0430 = 0x419A0430;
		_0x409900D0 = 0x409900D0;
		_0x11BFD9C3 = 0x11BFD9C3;
		_0x915F0040 = 0x915F0040;
		_0x11BED9C3 = 0x11BED9C3;
		_0x7FE3FB78 = 0x7FE3FB78;
		_0x8991B78C = 0x8991B78C;
		_0x150 = 0x150;
		_0x89916E78 = 0x89916E78;
		_0x34 = 0x34;
		_0x18 = 0x18;
		_0x3644 = 0x3644;
		_0x2090 = 0x2090;
		_0x10 = 0x10;
		_0x89A39F28 = 0x89A39F28;
		_0x5C = 0x5C;
		_0x20 = 0x20;
		_0x89A10B10 = 0x89A10B10;
		_0x89A39D48 = 0x89A39D48;
		_0x89A39DE8 = 0x89A39DE8;
		_0x89A38D38 = 0x89A38D38;
		_0x880330E8 = 0x880330E8;
		_0x897C150C = 0x897C150C;
		_0x897C1510 = 0x897C1510;
		_0x88C06B54 = 0x88C06B54;
		_0x89168184 = 0x89168184;
		_0x88B59AEC = 0x88B59AEC;
		_0x88C0D9F4 = 0x88C0D9F4;
		_0x88C0DA00 = 0x88C0DA00;
		_0x48000040 = 0x48000040;
		_0x419A0040 = 0x419A0040;
		_0x419A0020 = 0x419A0020;
		_0x7C8B2378 = 0x7C8B2378;
		_0x39200001 = 0x39200001;
		_0x988B0000 = 0x988B0000;
		_0x39600000 = 0x39600000;
		_0x882FB7B8 = 0x882FB7B8;
		_0x88B9FD58 = 0x88B9FD58;
		_0x88AD3A28 = 0x88AD3A28;
		_0x88D0D6A8 = 0x88D0D6A8;
		_0x88763360 = 0x88763360;
		_0x88679E80 = 0x88679E80;
		_0x88AA1FC8 = 0x88AA1FC8;
		_0x8856A310 = 0x8856A310;
		_0x915C00F0 = 0x915C00F0;
		_0x4BFFFAD9 = 0x4BFFFAD9;
		_0x913F00F0 = 0x913F00F0;
	}

#endif
};

struct GAME_ADDRESS_TRANSFER_BF4
{
	GAME_ADDRESSES_BF4* Addresses;

	void* drawText;
	void* setText;
	void* setAlignment;
	void* create;
	void* drawRect;
	void* SetKit;
	void* GetKit;
	void* ApplyPatches;
	void* SuperJumpPatchON;
	void* SuperJumpPatchOff;
	void* ResolveTextureByName;
	void* DrawTextureFromHandle;
	void* AddVector;
	void* GetDistance;
	void* VectorLength2D;
	void* GetFullAmmo;
	void* DrawRotatedShader;
	void* DrawLine;
	void* SendChatMessage;

};

GAME_ADDRESSES_BF4* Addresses;
GAME_ADDRESS_TRANSFER_BF4* ExternalFunctions;

void Real_drawText(int UIImmediateModeRenderer, int UITextObject, Vector4* rect, float scale)
{
	void(*drawText)(int, int, Vector4*, float) = (void(*)(int, int, Vector4*, float))Addresses->_0x88AA3798;
	drawText(UIImmediateModeRenderer, UITextObject, rect, scale);
}

void Real_setText(int UITextObject, const char* text, bool disableUpdateFromData)
{
	void(*setText)(int, const char*, bool) = (void(*)(int, const char*, bool))Addresses->_0x88AA5E40;
	setText(UITextObject, text, disableUpdateFromData);
}

void Real_setAlignment(int UITextObject, int halign, int valign)
{
	void(*setAlignment)(int, int, int) = (void(*)(int, int, int))Addresses->_0x88A9F9B8;
	setAlignment(UITextObject, halign, valign);
}

int Real_create(int UITextObject, const char* text, int style)
{
	int(*CreateText)(int, const char*, int) = (int(*)(int, const char*, int))Addresses->_0x8852B0A0;
	return CreateText(UITextObject, text, style);
}

void Real_drawRect(int _this, Vector4* Coords, Vector4* Color, long long unk)
{
	void(*DrawRect)(int, Vector4 *, Vector4*, long long) = (void(*)(int, Vector4*, Vector4*, long long))Addresses->_0x88AA2C80;
	DrawRect(_this, Coords, Color, unk);
}

int Real_SetKit(int r3, int r4, int r5)
{
	int(*SetKit)(int x, int y, int z) = (int(*)(int x, int y, int z))Addresses->_0x88548C90;
	return SetKit(r3, r4, r5);
}

int Real_GetKit(int r3, const char* r4, int r5)
{
	int(*GetKit)(int x, const char* y, int z) = (int(*)(int x, const char*, int z))Addresses->_0x88A94758;
	return GetKit(r3, r4, r5);
}

void Real_ApplyPatches()
{
	*(int*)(Addresses->_0x886608C4 + 0x0) = Addresses->_0x3D6089A3;
	*(int*)(Addresses->_0x886608C4 + 0x4) = Addresses->_0x616BF168;
	*(int*)(Addresses->_0x886608C4 + 0x8) = Addresses->_0x906B0000;
	*(int*)(Addresses->_0x886608C4 + 0xC) = Addresses->_0x60000000;
	*(int*)(Addresses->_0x886608C4 + 0x10) = Addresses->_0x60000000;
	*(int*)(Addresses->_0x886608C4 + 0x14) = Addresses->_0x60000000;
	*(int*)(Addresses->_0x886608C4 + 0x18) = Addresses->_0x60000000;

	*(int*)(Addresses->_0x887620c0) = Addresses->_0x60000000;
	*(int*)(Addresses->_0x88762008) = Addresses->_0x60000000;
	*(int*)(Addresses->_0x88759DBC) = Addresses->_0x60000000;

	long long va0 = Addresses->_0x48A94BE1;

	*(long long*)Addresses->_0x8873E1E4 = (va0 << 32) | Addresses->_0x60000000;

	long long va1 = Addresses->_0x484c5711;

	*(long long*)Addresses->_0x88D0D6AC = (va1 << 32) | Addresses->_0x60000000;
}

void Real_SuperJumpPatchON()
{
	*(int*)Addresses->_0x8815DB54 = Addresses->_0x497423f0;
	*(int*)Addresses->_0x89158D00 = Addresses->_0x4800004C;
	*(int*)Addresses->_0x885F4E54 = Addresses->_0x48000034;
	*(int*)Addresses->_0x885F4EEC = Addresses->_0x480002FC;
	*(int*)Addresses->_0x885F410C = Addresses->_0x60000000;
	*(int*)Addresses->_0x885F4114 = Addresses->_0x60000000;
	*(int*)Addresses->_0x885F4DB8 = Addresses->_0x60000000;
	*(int*)Addresses->_0x885F4E1C = Addresses->_0x60000000;

	*(int*)Addresses->_0x88623830 = Addresses->_0x60000000;
	*(int*)Addresses->_0x88623838 = Addresses->_0x60000000;
	*(int*)Addresses->_0x886236EC = Addresses->_0x60000000;
	*(int*)Addresses->_0x88628E40 = Addresses->_0x60000000;
}

void Real_SuperJumpPatchOff()
{
	*(int*)Addresses->_0x885F4E54 = Addresses->_0x409A0034;
	*(int*)Addresses->_0x885F4EEC = Addresses->_0x1000038C;
	*(int*)Addresses->_0x8815DB54 = Addresses->_0x41300000;
	*(int*)Addresses->_0x89158D00 = Addresses->_0x4099004C;
	*(int*)Addresses->_0x885F410C = Addresses->_0xD3350020;
	*(int*)Addresses->_0x885F4114 = Addresses->_0x92D50040;
	*(int*)Addresses->_0x885F4DB8 = Addresses->_0x419A0430;
	*(int*)Addresses->_0x885F4E1C = Addresses->_0x409900D0;

	*(int*)Addresses->_0x88623830 = Addresses->_0x11BFD9C3;
	*(int*)Addresses->_0x88623838 = Addresses->_0x915F0040;
	*(int*)Addresses->_0x886236EC = Addresses->_0x11BED9C3;
	*(int*)Addresses->_0x88628E40 = Addresses->_0x7FE3FB78;
}

int Real_ResolveTextureByName(int r3, const char* r4, int r5, int r6, int r7, int r8)
{
	int(*ResolveTextureByName)(int, const char*, int, int, int, int) = (int(*)(int, const char*, int, int, int, int))Addresses->_0x88679E80;
	return ResolveTextureByName(r3, r4, r5, r6, r7, r8);
}

void Real_DrawTextureFromHandle(int r3, int r4, int* r5, int* r6, int* r7, long long r8)
{
	void(*DrawTextureFromHandle)(int, int, int*, int*, int*, long long) = (void(*)(int, int, int*, int*, int*, long long))Addresses->_0x88AA1FC8;
	DrawTextureFromHandle(r3, r4, r5, r6, r7, r8);
}

void Real_AddVector(Vector3 From, Vector3 To, Vector3& Out)
{
	Out.x = From.x + To.x;
	Out.y = From.y + To.y;
	Out.z = From.z + To.z;
}

float Real_GetDistance(Vector3 c1, Vector3 c2)
{
	float dx = c2.x - c1.x;
	float dy = c2.y - c1.y;
	float dz = c2.z - c1.z;
	return sqrt((float)((dx * dx) + (dy * dy) + (dz * dz)));
}

float Real_VectorLength2D(Vector3* pV)
{
	return	sqrtf(pV->x * pV->x + pV->z * pV->z);
}

void Real_GetFullAmmo()
{
	//printf("GetFullAmmo\n");

	int CurSlot = *(int*)(Addresses->_0x8991B78C) + Addresses->_0x150;

	int Kit = Real_GetKit(CurSlot, "SelectedKit", 0);

	Real_SetKit(Kit, 1, 0);
}

void Real_DrawRotatedShader(float x, float y, float width, float height, float angle, Vector4* Color)
{
	MatrixCoords ShaderMatrix;

	Vector4 ImagePosition = Vector4(0.5f, 0.0f, 0.5f, 0.0f);
	Vector4 _color = Vector4(Color->x, Color->y, Color->z, Color->a);

	float f11 = x + width;
	float f10 = y + height;

	Vector2 Center = { (f11 + x) / 2, (y + f10) / 2 };

	ShaderMatrix.TL.x = Center.x + (x - Center.x)*cos(-angle) + (y - Center.y)*sin(-angle);
	ShaderMatrix.TL.y = Center.y - (x - Center.x)*sin(-angle) + (y - Center.y)*cos(-angle);
	ShaderMatrix.TL.z = 0;

	ShaderMatrix.TR.x = Center.x + (f11 - Center.x)*cos(-angle) + (y - Center.y)*sin(-angle);
	ShaderMatrix.TR.y = Center.y - (f11 - Center.x)*sin(-angle) + (y - Center.y)*cos(-angle);;
	ShaderMatrix.TR.z = 0;

	ShaderMatrix.BR.x = Center.x + (f11 - Center.x)*cos(-angle) + (f10 - Center.y)*sin(-angle);
	ShaderMatrix.BR.y = Center.y - (f11 - Center.x)*sin(-angle) + (f10 - Center.y)*cos(-angle);
	ShaderMatrix.BR.z = 0;

	ShaderMatrix.BL.x = Center.x + (x - Center.x)*cos(-angle) + (f10 - Center.y)*sin(-angle);
	ShaderMatrix.BL.y = Center.y - (x - Center.x)*sin(-angle) + (f10 - Center.y)*cos(-angle);
	ShaderMatrix.BL.z = 0;

	int TextureHandle = Real_ResolveTextureByName(0, "xhttps://eaassets-a.akamaihd.net/dice-commerce/battlefield4/topstory/prod/20170412-01/Easterfest_ConversionMissionv2_510x144.jpg", 1, 1, 0, 0);

	if (!TextureHandle)
		return;

	Real_DrawTextureFromHandle(*(int*)(Addresses->_0x8991B90C), *(int*)(TextureHandle), (int*)&ShaderMatrix, (int*)&_color, (int*)&ImagePosition, 0xA100000000);
}

void Real_DrawLine(float X1, float Y1, float X2, float Y2, float Width, Vector4* LineColor)
{
	float X, Y, L1, L2, H1;

	H1 = Y2 - Y1;
	L1 = X2 - X1;
	L2 = sqrt(L1 * L1 + H1 * H1);
	X = X1 + ((L1 - L2) / 2);
	Y = Y1 + (H1 / 2);

	Real_DrawRotatedShader(X, Y, L2, Width, (float)atan(H1 / L1), LineColor);
}

void Real_SendChatMessage(wchar_t *Message)
{
	int(*SendChat)(int chat, int ChannelID, int ReceiptMask, wchar_t*) = (int(*)(int, int ChannelID, int ReceiptMask, wchar_t*))Addresses->_0x8856A310;

	int ClientGameContext = *(int*)Addresses->_0x89916E78;
	int OnlineManager = *(int*)(ClientGameContext + Addresses->_0x34);
	int ClientPeer = *(int*)(OnlineManager + Addresses->_0x18);
	int Unk1 = *(int*)(ClientPeer + Addresses->_0x3644);

	if (Unk1 != 0)
	{
		int Unk2 = Unk1 - Addresses->_0x10;
		int Unk3 = *(int*)(Unk2 + Addresses->_0x2090);

		SendChat(Unk3, 0, ~0, Message);
	}
}


void BF4_SetupGameAddresses(ServerData_BF4* Server)
{
	if (BF4_addr_s_Data)
		delete BF4_addr_s_Data;

	BF4_addr_s_PatchID = new unsigned int[_byteswap_ulong(Server->Server_addr_s_XexAddrNum)];

	unsigned int *addr_s_PatchFile = new unsigned int[_byteswap_ulong(Server->Server_addr_s_XexAddrNum)];

	for (unsigned int i = 0; i < _byteswap_ulong(Server->Server_addr_s_XexAddrNum); i++) {

		addr_s_PatchFile[i] = Server->Server_addr_s[i];
		BF4_addr_s_PatchID[i] = Server->Server_addr_s_PatchID[i];
	}

	time_t t = 0;

	Sleep(100);

	time(&t);

	BF4_addr_s_Data = new Security(t, g_Session);
	BF4_addr_s_Data->ProcessAddressFile(addr_s_PatchFile, BF4_addr_s_PatchID, _byteswap_ulong(Server->Server_addr_s_XexAddrNum));

	delete[] addr_s_PatchFile;
}

bool BattleField4_BuildFunctions()
{
	BuildStartFunctions();

	if (ExternalFunctions)
		delete ExternalFunctions;

	ExternalFunctions = new GAME_ADDRESS_TRANSFER_BF4;

	if (Addresses)
		free(Addresses);

	Addresses = (GAME_ADDRESSES_BF4*)malloc(sizeof(GAME_ADDRESSES_BF4));

	memset(Addresses, 0, sizeof(GAME_ADDRESSES_BF4));

	for (int i = 0; i < 102; i++)
		((int*)(Addresses))[i] = GetAddress(BF4_addr_s_Data, BF4_addr_s_PatchID, i);

	ExternalFunctions->Addresses = Addresses;

	ExternalFunctions->drawText = (void*)ReverseInt((int)Real_drawText);
	ExternalFunctions->setText = (void*)ReverseInt((int)Real_setText);
	ExternalFunctions->setAlignment = (void*)ReverseInt((int)Real_setAlignment);
	ExternalFunctions->create = (void*)ReverseInt((int)Real_create);
	ExternalFunctions->drawRect = (void*)ReverseInt((int)Real_drawRect);
	ExternalFunctions->SetKit = (void*)ReverseInt((int)Real_SetKit);
	ExternalFunctions->GetKit = (void*)ReverseInt((int)Real_GetKit);
	ExternalFunctions->ApplyPatches = (void*)ReverseInt((int)Real_ApplyPatches);
	ExternalFunctions->SuperJumpPatchON = (void*)ReverseInt((int)Real_SuperJumpPatchON);
	ExternalFunctions->SuperJumpPatchOff = (void*)ReverseInt((int)Real_SuperJumpPatchOff);
	ExternalFunctions->ResolveTextureByName = (void*)ReverseInt((int)Real_ResolveTextureByName);
	ExternalFunctions->DrawTextureFromHandle = (void*)ReverseInt((int)Real_DrawTextureFromHandle);
	ExternalFunctions->AddVector = (void*)ReverseInt((int)Real_AddVector);
	ExternalFunctions->GetDistance = (void*)ReverseInt((int)Real_GetDistance);
	ExternalFunctions->VectorLength2D = (void*)ReverseInt((int)Real_VectorLength2D);
	ExternalFunctions->GetFullAmmo = (void*)ReverseInt((int)Real_GetFullAmmo);
	ExternalFunctions->DrawRotatedShader = (void*)ReverseInt((int)Real_DrawRotatedShader);
	ExternalFunctions->DrawLine = (void*)ReverseInt((int)Real_DrawLine);
	ExternalFunctions->SendChatMessage = (void*)ReverseInt((int)Real_SendChatMessage);

	HVGetVersionsPokeDWORD(0x800001000000BED0, (int)ReverseInt((int)ExternalFunctions));
	HVGetVersionsPokeDWORD(0x800001000000BED4, (int)ReverseInt((int)sizeof(GAME_ADDRESS_TRANSFER_BF4)));

	return true;
}