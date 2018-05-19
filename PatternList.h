#pragma once

#ifdef listem

/*LocalPlayer 
a1 ? ? ? ? 85 c0 74 ? 8d 88 ? ? ? ? 8b 01 
mov eax, [03E3FF38] 
*/
#pragma region OBJ_AI_Base
/*Object Position
8b 81 ? ? ? ? ff 74 ? ? 89 46
mov eax,[ecx+000000FC]
*/

/*Gold
89 34 ? 8b 5c ? ? 8b 44 << find out what writes that shhhhhhit eax is offset 
offset eax
mov [ebx+eax],esi
*/

/*AI_MANAGER - ACTOR_COMMON
ff 90 ? ? ? ? 80 b8 98 01 00 00 ? 74 ? 8b 0d
call dword ptr [eax+00000244]
Caller to mov eax,[ecx+00001240] < ecx+ offset
*/
/*pCharData
74 ? 8b 0d ? ? ? ? 84 db
je
mov [esi+00000884],eax
mov eax,[esi+00000E48]  esi + offset 
*/

/*Health
8d 8b ? ? ? ? e8 ? ? ? ? 8b 07
8d 89 ? ? ? ? e8 ? ? ? ? 8b 4e
a1 ? ? ? ? 8b 1d ? ? ? ? 81 c3  that top function
call dword ptr [esi+000002E0]
lea ecx,[ebx+00000678]  ebx+offset
*/
/*NetWorkID
39 77 ? 74 ? 57
cmp [edi+6C],esi  6C OFFSET
je "League of Legends.AK::WriteBytesMem::Bytes"+79392 { ->League of Legends.AK::WriteBytesMem::Bytes+79392 }
push edi

*/
/*BuffManager
8b 85 ? ? ? ? 2b 85 ? ? ? ? c1 f8 ? 85 c0
8b 85 ? ? ? ? 47 2b 85
mov eax,[ebp+00001294]  end
sub eax,[ebp+00001290]  begin 
*/

/*SpellBook
75 ? e8 ? ? ? ? 8d 88 ? ? ? ? 8b 01
8d 88 ? ? ? ? 8b 01 8b 40 ? ff d0 84 c0 74 ? c6 07
8d 88 ? ? ? ? e8 ? ? ? ? 80 3f
lea ecx,[eax+00001BD0] eax+offset
pushed param set bp get param 1 = 83 ec ? 53 55 8b 6c ? ? 8d 44 ? ? 56 50
*/

/*SpellData sData

new 83 ec ? 53 55 56 8b 74 ? ? 8b e9 57 83 be 1c 01 00 00
11c

83 bd ?? ?? 00 00 ? 0f 84 ? ? ? ? 8b 5c
cmp dword ptr [ebp+0000011C],00 { 0 }
je 
mov ebx,[esp+4C]
test ebx,ebx

part 2 

e8 ? ? ? ? 84 c0 0f 84 ? ? ? ? 8b 44 ? ? 83 b8 1c 01 00 00
cmp dword ptr [eax+0000011C],00
*/
/*
GetSpell array
68 ? ? ? ? e8 ? ? ? ? 83 c4 ? 83 fe ? 77 ? 8b 84 ? ? ? ? ? 5f 5e c2 ? ? 8b 87 ? ? ? ? 5f 5e c2 ? ? cc cc cc cc cc cc 56
8b 84 ? ? ? ? ? 5f 5e c2 ? ? 8b 87 ? ? ? ? 5f 5e c2 ? ? cc cc cc cc cc cc 56
56 8b 74 ? ? 57 8b f9 85 f6 78 ? 83 fe ? 7c ? 68 ? ? ? ? e8 ? ? ? ? 83 c4 ? 83 fe ? 77 ? 8b 84 ? ? ? ? ? 5f 5e c2 ? ? 8b 87 ? ? ? ? 5f 5e c2 ? ? cc cc cc cc cc cc 56
68 ? ? ? ? e8 ? ? ? ? 83 c4 ? 83 fb ? 77
8b 87 ? ? ? ? 5f 5e c2 ? ? cc cc cc cc cc cc 56
ALE-BEF0AEF3
ALE-C00960B2

mov eax,[edi+esi*4+00000530] edi+esi*4+offset
mov eax,[edi+00000530]
*/

/*ActorCommonNavigasyon
0f 86 ? ? ? ? 8b 87 ? ? ? ? 8d b7
mov eax,[edi+000002BC] edi+offset
*/
/*r3dRendererInstance
a1 ? ? ? ? 85 c0 74 ? 80 78 44 ? 75 ? 8b 0d ? ? ? ? 8b 49 ? e8 ? ? ? ? e8 ? ? ? ? 85 c0 74 ? 8b 10 8b c8 ff 52 ? 8b 0d ? ? ? ? e8
mov eax,[03E643A0]
83 3d a0 43 e6 03 ? 53 8b d9
68 ? ? ? ? e8 ? ? ? ? 83 c4 ? 89 06 8b 0d ? ? ? ? e8 ? ? ? ? 5e

Width  = 8b 46 ? 89 86 ? ? ? ? 8b 46 ? c7 06

SCREEN_MATRIX

*/
/*Projectionmatrix

Projection = 8d 87 ? ? ? ? 6a ? 50 e8 ? ? ? ? 83 c4 ? 8b c7
lea eax,[edi+000000CC] edi + offset projection
https://my.mixtape.moe/mnotls.png looks like xd
*/

/*AI NavPath array

8b 88 ? ? ? ? 2b 88 ? ? ? ? b8 ? ? ? ? f7 e9
8b 8f ? ? ? ? 2b 8f ? ? ? ? 8b b7
mov ecx,[eax+000001C0] // end
sub ecx,[eax+000001BC] // begin
*/

/*Lolcursor

a1 ? ? ? ? 8b 40 ? 85 c0
80 b8 22 02 00 00 ? 0f 85 ? ? ? ? 6a ? 68 ? ? ? ? 8d 4c ? ? c7 44 24 40
mov eax,["League of Legends.g_LEngineDefaultPoolId"+14A8C] { [0A153800] } << ------
mov eax,[eax+14]

*/
/*undermouseobject

c7 05 94 1a de 02 ? ? ? ? e8 ? ? ? ? 83 c4 ? ff b4
80 bc 24 90 00 00 00 ? 0f 85 ? ? ? ? a1
mov ["League of Legends.g_LEngineDefaultPoolId"+C62A34],eax { [00000001] }
mov ["League of Legends.g_LEngineDefaultPoolId"+C629FC],00000000 { [00000000] } <<

*/
#pragma endregion



#endif