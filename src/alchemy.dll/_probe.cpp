// alchemy.dll matching probe -- 8 representatives across the size-16 veins.
// Verifies the claim/decoration mechanics before scaling with automation.
extern "C" {

// sub_6201610: xor eax,eax; ret 4  (return 0, 1 arg)
int __stdcall probe_6201610(int a) { return 0; }

// sub_6202740: mov eax,0x190; ret 4  (return constant)
int __stdcall probe_6202740(int a) { return 0x190; }

// sub_6202700: mov eax,[esp+4]; mov eax,[eax+0xc]; ret 4  (direct getter)
int __stdcall probe_6202700(void* p) { return *(int*)((char*)p + 0xc); }

// sub_6203400: increment getter at +8
int __stdcall probe_6203400(void* p) { return ++*(int*)((char*)p + 8); }

// sub_62026F0: setter [eax+8]=ecx; xor eax; ret 8
int __stdcall probe_62026F0(void* p, int v) { *(int*)((char*)p + 8) = v; return 0; }

// sub_6202690: thiscall chained getter -> fastcall model
int __fastcall probe_6202690(void* self) { return *(int*)(*(char**)((char*)self + 0x84) + 0x14); }

// sub_62026A0: getter+shr eax,0x1f (sign bit)
unsigned __stdcall probe_62026A0(void* p) { return *(unsigned*)((char*)p + 8) >> 0x1f; }

// sub_6203220: or eax,-1; ret 8  (return -1, 2 args)
int __stdcall probe_6203220(int a, int b) { return -1; }

}
