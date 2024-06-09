section .data
    const1 dq 1.5
    const2 dq 3.0
    const3 dq 1.0
    const4 dq 2.5
    const5 dq 9.5
    const6 dq 5.0

section .text
global f1
f1:
    push ebp
    mov ebp, esp
    finit
    
    fld qword[const1]
    fld qword[const3]
    fld qword[ebp+8]
    faddp
    fdivp
    fld qword[const2]
    faddp
    
    leave
    ret

global f2
f2:
    push ebp
    mov ebp, esp
    finit
    
    fld qword[const4]
    fld qword[esp+8]
    fmulp
    fld qword[const5]
    fsubp
    
    leave
    ret
    
global f3
f3:
    push ebp
    mov ebp, esp
    finit
    
    fld qword[const6]
    fld qword[esp+8]
    fdivp
    
    leave
    ret