.thumb
.syntax unified

.global activate_task
activate_task:
  /* save kernel task state*/
  mrs ip, psr
  push {r4, r5, r6, r7, r8, r9, r10, r11, ip, lr}

  /* switch to process stack */
  msr psp, r0
  mov r0, #3
  msr control, r0

  /* load user task state */
  pop {r4, r5, r6, r7, r8, r9, r10, r11, lr}

  /* jump to user task */
  bx lr
