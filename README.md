# my_corne_keymap

Daily-driver QMK keymap for `crkbd/rev1` on a Corne 3x6_3, optimized for Rust, Neovim, tmux, zsh, i3, and terminal-heavy Arch Linux use.

## Hardware Target

- Keyboard: `crkbd/rev1`
- Keymap: `my_keymap`
- Controller class: Pro Micro / ATmega32U4
- Bootloader reported by QMK: Caterina
- OLED: enabled
- RGB Light: disabled
- RGB Matrix: disabled

## Build

```sh
qmk lint -kb crkbd/rev1 -km my_keymap
qmk compile -kb crkbd/rev1 -km my_keymap
```

## Cheat Sheet

Open `CHEATSHEET.md` for a usage-focused guide covering thumbs, NAV, SYM, browser, i3, Neovim, tmux, and zsh.

## Flash

Do not flash until the diff and compile result have been reviewed.

```sh
qmk flash -kb crkbd/rev1 -km my_keymap
```

Flash each half separately when needed. `QK_BOOT` normally enters the bootloader for the active/master half. Flashing or recovering the other split half may require pressing that half's physical reset button.

## Base Layer

```text
┌────────┬───┬───┬───┬───┬───┐   ┌───┬───┬───┬───┬───┬───────────┐
│ Tab    │ Q │ W │ E │ R │ T │   │ Y │ U │ I │ O │ P │ Backspace │
├────────┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───────────┤
│ LShift │ A │ S │ D │ F │ G │   │ H │ J │ K │ L │ ; │ Quote     │
├────────┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───────────┤
│ LCtrl  │ Z │ X │ C │ V │ B │   │ N │ M │ , │ . │ / │ RCtrl     │
└────────┴───┴───┴───┴───┴───┘   └───┴───┴───┴───┴───┴───────────┘

              SYM  NAV/Esc Ent/Alt │  Spc/Alt NAV/Esc SYM
```

Thumb behavior:
- Outer `SYM` keys: momentary Symbol layer from either hand and part of tri-layer Adjust.
- `NAV/Esc`: tap for Escape, hold for Navigation layer and part of tri-layer Adjust. Mirrored on both hands.
- `Ent/Alt`: tap Enter, hold Left Alt.
- `Spc/Alt`: tap Space, hold Right Alt.

Tab, Quote, Shift, Ctrl, and alpha keys are deterministic. Ctrl lives on both outer pinkies. Esc is thumb-only on tap `NAV/Esc`. Alt lives as thumb holds on Enter and Space. SYM and NAV are mirrored for either hand.

## Symbol Layer

Hold either outer `SYM` thumb.

```text
┌───┬───┬───┬───┬───┬───┐   ┌───┬───┬───┬───┬───┬───┐
│ ` │ 1 │ 2 │ 3 │ 4 │ 5 │   │ 6 │ 7 │ 8 │ 9 │ 0 │ ~ │
├───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┤
│ | │ & │ - │ = │ < │ > │   │ ( │ ) │ [ │ ] │ { │ } │
├───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┤
│ ! │ _ │ : │ @ │ # │ $ │   │ % │ ^ │ * │ + │ ? │ \ │
└───┴───┴───┴───┴───┴───┘   └───┴───┴───┴───┴───┴───┘
```

Rust symbol examples:
- `::` = colon twice.
- `->` = roll `-` to `>`.
- `=>` = roll `=` to `>`.
- `<>` = roll `<` to `>`.
- `()`, `[]`, `{}` are adjacent pairs.
- `|` and `&` are adjacent for shell/logical operators; `_`, `?`, `:`, `-`, `=`, `<`, `>` are direct layer keys.

Example Rust snippets this layer is designed for:

```rust
fn parse<'a>(input: &'a str) -> Result<&'a str, Error>
```

```rust
match result {
    Ok(value) => value,
    Err(error) => return Err(error),
}
```

## Navigation Layer

Hold either `NAV/Esc` thumb.

```text
┌─────────┬─────┬─────┬─────┬─────┬─────┐   ┌─────┬─────┬─────┬─────┬─────┬─────────┐
│ Tab     │ WM1 │ WM2 │ WM3 │ WM4 │ WM5 │   │ WM6 │ WM7 │ WM8 │ WM9 │PrevT│ NextT   │
├─────────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────────┤
│ShiftTab │ GUI │ Alt │ Ctrl│Shift│ C-l │   │Left │Down │ Up  │Right│Home │ End     │
├─────────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────────┤
│ C-l     │ [d  │ ]d  │tmux[│Copy │Paste│   │A-b  │PgDn │PgUp │A-f  │Bspc │ Delete  │
└─────────┴─────┴─────┴─────┴─────┴─────┘   └─────┴─────┴─────┴─────┴─────┴─────────┘
```

Notes:
- Esc is thumb-only: tap the `NAV/Esc` thumb key. Holding that same key activates NAV.
- `PrevT` / `NextT` are browser/application previous and next tab: `Ctrl-Shift-Tab` and `Ctrl-Tab`.
- `ShiftTab` is plain `Shift-Tab` for reverse completion, browser forms, and UI focus movement.
- Arrow keys use true Vim H/J/K/L geometry on the right hand: H=Left, J=Down, K=Up, L=Right. NAV is held by the opposite hand to reduce right-hand fatigue.
- `C-l` clears terminal screens without assuming the shell prompt is empty.
- `[d` and `]d` are emitted as clean diagnostic sequences for Neovim.
- `tmux[` sends `Ctrl-S`, waits briefly, then sends `[`. This depends on tmux prefix `C-s`.
- Copy/Paste are `Ctrl-Shift-C` and `Ctrl-Shift-V` for terminal emulators.
- Word movement is `Alt-B` and `Alt-F`, matching readline/zsh behavior.

## Adjust Layer

Hold any `NAV/Esc + SYM` pair together. This uses QMK tri-layer support.

```text
┌────┬────┬────┬────┬────┬────┐   ┌────┬────┬────┬─────┬─────┬────────┐
│ F1 │ F2 │ F3 │ F4 │ F5 │ F6 │   │ F7 │ F8 │ F9 │ F10 │ F11 │ F12    │
├────┼────┼────┼────┼────┼────┤   ├────┼────┼────┼─────┼─────┼────────┤
│WM0 │Rep │ARep│ -- │ -- │ -- │   │Prev│Play│Next│Mute │Vol- │ Vol+   │
├────┼────┼────┼────┼────┼────┤   ├────┼────┼────┼─────┼─────┼────────┤
│BOOT│ -- │ -- │ -- │ -- │ -- │   │Bri-│Bri+│ -- │ --  │ --  │ --     │
└────┴────┴────┴────┴────┴────┘   └────┴────┴────┴─────┴─────┴────────┘
```

`QK_BOOT` is intentionally on a bottom corner and requires `NAV + SYM + bottom-corner key`. `WM0` is i3 workspace 10, moved here so NAV can keep direct browser previous/next tab keys.

## Caps Word

Caps Word is enabled, but there is no duplicate Caps Word key on Adjust.

- Press both Shift keys together to activate Caps Word.
- Idle timeout is 4000 ms.
- Use it for identifiers like `MAX_RETRY_COUNT`, `DATABASE_URL`, `RUST_LOG`, and `DEFAULT_TIMEOUT_SECONDS`.
- `COMMAND_ENABLE` is disabled so both-shifts activation does not conflict with QMK Command.

## Repeat Key

Repeat Key is enabled on Adjust for a one-week trial:

- `Rep`: `QK_REP`
- `ARep`: `QK_AREP`

If it is not used regularly after a week, disable `REPEAT_KEY_ENABLE` and replace these positions with `KC_NO`. Core layout, Caps Word, and OLED are higher priority.

## OLED

OLED is enabled with a minimal static display:

- Primary/secondary half indication.
- Current layer.
- Caps Word state.
- Active modifiers.

No animations, WPM pets, bitmap collections, or key logging are implemented.

## RGB

RGB Light and RGB Matrix are disabled for the ATmega32U4 build. This keeps firmware smaller and runtime behavior simpler. No RGB controls are placed on the keymap because they would be dead keys.

## tmux Requirement

The firmware assumes tmux prefix is `Ctrl-S`.

Recommended tmux snippet:

```tmux
unbind C-b
set -g prefix C-s
bind C-s send-prefix
set -s escape-time 0
```

## zsh Requirement

Disable terminal flow control in interactive shells so `Ctrl-S` does not send XOFF/freeze terminal output:

```sh
if [[ -o interactive ]]; then
    stty -ixon 2>/dev/null
fi
```

## i3 Mod1 To Mod4 Migration

The firmware centralizes workspace shortcuts in `keymap.c`:

```c
#define WM(kc) A(kc)
```

This matches i3 `Mod1`/Alt setups:

```i3
set $mod Mod1
```

If i3 is migrated to Super/Mod4:

```i3
set $mod Mod4
```

Then change only this firmware line:

```c
#define WM(kc) G(kc)
```

## Brightness Keys Under i3

The Adjust layer sends standard HID brightness keycodes `KC_BRID` and `KC_BRIU`. Some Linux/i3 setups handle these automatically through desktop services; minimal i3 sessions often do not.

If they do not work, bind the keysyms in i3, for example:

```i3
bindsym XF86MonBrightnessDown exec --no-startup-id brightnessctl set 5%-
bindsym XF86MonBrightnessUp exec --no-startup-id brightnessctl set +5%
```

## Neovim Mappings

Editor-specific actions belong in Neovim, not firmware. Recommended mappings:

```lua
vim.keymap.set("n", "<leader>w", "<cmd>write<cr>", { desc = "Write file" })
vim.keymap.set("n", "<leader>q", "<cmd>quit<cr>", { desc = "Quit window" })
vim.keymap.set("n", "[d", function() vim.diagnostic.jump({ count = -1, float = true }) end, { desc = "Previous diagnostic" })
vim.keymap.set("n", "]d", function() vim.diagnostic.jump({ count = 1, float = true }) end, { desc = "Next diagnostic" })
```

## Tapping-Term Notes

Current values are retained for future experimentation:

- `TAPPING_TERM = 180`
- `QUICK_TAP_TERM = 120`

There are no Base tap-hold keys in this layout, so these settings should not affect normal typing. Keep the layout deterministic unless a future change has a clear ergonomic payoff.

## Recovery

- Use `QK_BOOT` from `NAV + SYM + bottom-left corner` for the active/master half.
- If the other half does not enter bootloader, press its physical reset button and flash that side separately.
- Bootmagic is enabled. The keyboard also supports boot/reset behavior from the physical reset controls near the TRRS jack.

## Migration And Rollback

Before flashing, inspect the diff:

```sh
git diff -- keyboards/crkbd/keymaps/my_keymap
```

Rollback this keymap to the previous committed state if needed:

```sh
git restore --source=HEAD -- keyboards/crkbd/keymaps/my_keymap/config.h keyboards/crkbd/keymaps/my_keymap/keymap.c keyboards/crkbd/keymaps/my_keymap/README.md keyboards/crkbd/keymaps/my_keymap/rules.mk
```

If `.gitignore` is untracked and you want to remove only that new file:

```sh
rm keyboards/crkbd/keymaps/my_keymap/.gitignore
```

## Test Checklist

- Base: Tab, thumb Esc, Backspace, Space/Alt, Enter/Alt, Quote, both Shifts, left/right pinky Ctrl, mirrored NAV, and mirrored SYM.
- Rust symbols: `::`, `->`, `=>`, `<>`, `&`, `|`, `_`, `?`, `()`, `[]`, `{}`.
- Terminal: pinky `Ctrl-C`, `Ctrl-R`, `Ctrl-W`, `Ctrl-U`, `Ctrl-L`, thumb/layer `Alt-B`, `Alt-F`, terminal copy/paste.
- tmux: copy mode, terminal clear, no stuck Ctrl, no XOFF freeze with `stty -ixon`.
- Neovim: thumb Escape, `[d`, `]d`, H/J/K/L arrows, no firmware `:q` injection.
- i3: workspaces 1 through 9 on NAV, workspace 10 on Adjust, with current Mod1 behavior.
- Browser: plain Tab, Shift-Tab, previous tab, next tab, clipboard shortcuts, navigation keys.
- Adjust: any NAV/Esc + SYM pair, F1-F12, media, brightness, Caps Word, Repeat, Alternate Repeat, protected `QK_BOOT`.
