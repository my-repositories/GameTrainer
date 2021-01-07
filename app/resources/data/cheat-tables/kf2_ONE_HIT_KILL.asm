[ENABLE]

define(INJECT, KFGame.exe+57BEE)
registersymbol(INJECT)

alloc(newmem,2048)
label(returnhere)
label(originalcode)
label(exit)

newmem:
  {if is_player_flag = 0}
  {then mov [rdi],esi}
  {else js @F}
  cmp BYTE ptr [rdi-384+4c],1
  je @F
  mov [rdi],0
  jmp originalcode

@@:
  sub [rdi],eax

originalcode:
  mov eax,[rdi]
  mov [rsi],eax
  add rsp,20
  mov r14,0x00007FF7C0CA4BB0
  pop r14
  pop rdi
  pop rsi

exit:
  jmp returnhere

INJECT:
  jmp newmem

returnhere:

[DISABLE]
dealloc(newmem)

INJECT:
  sub [rdi],eax
  mov eax,[rdi]
  mov [rsi],eax
  add rsp,20
  pop r14
  pop rdi
  pop rsi
