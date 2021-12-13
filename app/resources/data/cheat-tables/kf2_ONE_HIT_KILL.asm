[ENABLE]

define(INJECT, KFGame.exe+57BEE)
registersymbol(INJECT)

alloc(newmem,2048)
label(returnhere)
label(originalcode)
label(kill)

newmem:
  cmp word ptr [rdi-384+170],1
  je kill
  sub [rdi],eax
  jmp originalcode

kill:
  mov [rdi],0

originalcode:
  mov eax,[rdi]
  mov [rsi],eax
  add rsp,20
  pop r14
  pop rdi
  pop rsi
  jmp returnhere

INJECT:
  jmp newmem

returnhere:

[DISABLE]
unregistersymbol(INJECT)
dealloc(newmem)

INJECT:
  sub [rdi],eax
  mov eax,[rdi]
  mov [rsi],eax
  add rsp,20
  pop r14
  pop rdi
  pop rsi
