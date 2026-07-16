# Corne Keymap Cheat Sheet

Path: `~/qmk_firmware/keyboards/crkbd/keymaps/my_keymap/CHEATSHEET.md`

## Base

```text
Tab     Q  W  E  R  T        Y  U  I  O  P  Backspace
LShift  A  S  D  F  G        H  J  K  L  ;  '
LCtrl   Z  X  C  V  B        N  M  ,  .  /  RCtrl

             SYM  NAV/Esc  Ent/Alt    Spc/Alt  NAV/Esc  SYM
```

## Thumbs

```text
Tap NAV/Esc       = Esc
Hold NAV/Esc      = NAV
Tap Ent/Alt       = Enter
Hold Ent/Alt      = Left Alt
Tap Spc/Alt       = Space
Hold Spc/Alt      = Right Alt
Hold either SYM   = SYM
Hold NAV + SYM    = ADJ
```

## Navigation

Hold either `NAV/Esc`.

```text
Tab       WM1  WM2  WM3  WM4  WM5      WM6   WM7   WM8   WM9   PrevTab  NextTab
ShiftTab  GUI  Alt  Ctrl Shift C-l      Left  Down  Up    Right Home     End
clear     [d   ]d   tmux[ Copy Paste    A-b   PgDn  PgUp  A-f   Bspc     Del
```

Common use:

```text
Esc                 = tap NAV/Esc
Tab                 = top-left key
Shift-Tab           = NAV + LShift-position
Browser prev tab    = NAV + P-position
Browser next tab    = NAV + Backspace-position
Arrows              = NAV + H/J/K/L
Ctrl-L              = NAV + G-position
clear + Enter       = NAV + bottom-left
Word left/right     = NAV + N-position / NAV + .-position
```

## Symbols

Hold either outer `SYM`.

```text
`  1  2  3  4  5        6  7  8  9  0  ~
|  &  -  =  <  >        (  )  [  ]  {  }
!  _  :  @  #  $        %  ^  *  +  ?  \
```

Rust and web patterns:

```text
::    colon twice
->    - then >
=>    = then >
<>    < then >
&&    & twice
||    | twice
()    adjacent pair
[]    adjacent pair
{}    adjacent pair
```

## Adjust

Hold any `NAV/Esc + SYM` pair.

```text
F1    F2   F3    F4  F5  F6      F7    F8    F9   F10  F11  F12
WM0   Rep  ARep   --  --  --      Prev  Play  Next Mute Vol- Vol+
BOOT  --   --     --  --  --      Bri-  Bri+  --   --   --   --
```

## i3

```text
Workspace 1-9       = NAV + Q..O positions
Workspace 10        = NAV + SYM + LShift-position
```

Firmware currently assumes i3 Mod1/Alt:

```c
#define WM(kc) A(kc)
```

If i3 moves to Super/Mod4, change it to:

```c
#define WM(kc) G(kc)
```

Suggested i3 binding to open this guide:

```i3
bindsym $mod+Shift+slash exec --no-startup-id alacritty -e nvim ~/qmk_firmware/keyboards/crkbd/keymaps/my_keymap/CHEATSHEET.md
```

## Neovim

Recommended command to open this guide:

```lua
vim.api.nvim_create_user_command("CorneHelp", function()
  vim.cmd("tabedit ~/qmk_firmware/keyboards/crkbd/keymaps/my_keymap/CHEATSHEET.md")
end, {})

vim.keymap.set("n", "<leader>?", "<cmd>CorneHelp<cr>", { desc = "Open Corne keymap guide" })
```

Useful keyboard actions in Neovim:

```text
Esc                 = tap NAV/Esc
Diagnostics prev    = NAV + S-position
Diagnostics next    = NAV + D-position
Arrows              = NAV + H/J/K/L
Page down/up        = NAV + J/K lower row positions
```

## Browser

```text
Tab                 = top-left key
Shift-Tab           = NAV + LShift-position
Previous tab        = NAV + P-position
Next tab            = NAV + Backspace-position
Address bar         = Ctrl + L, or NAV C-l if accepted by the focused app
Reload              = Ctrl + R
Hard reload         = Ctrl + Shift + R
DevTools            = F12 on ADJ
```

## tmux And zsh

Firmware assumes tmux prefix is `Ctrl-S`.

```text
clear + Enter       = NAV + bottom-left
tmux copy mode      = NAV + C-position
```

Disable terminal flow control so `Ctrl-S` does not freeze output:

```sh
stty -ixon
```
