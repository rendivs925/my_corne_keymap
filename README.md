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
│ LAlt   │ Z │ X │ C │ V │ B │   │ N │ M │ , │ . │ / │ RShift    │
└────────┴───┴───┴───┴───┴───┘   └───┴───┴───┴───┴───┴───────────┘

              LCtrl   NAV   Space  │  Enter   SYM   GUI/Escape
```

Thumb behavior:
- `LCtrl`: dedicated Control.
- `NAV`: momentary Navigation layer and part of tri-layer Adjust.
- `Space`: dedicated Space.
- `Enter`: dedicated Enter.
- `SYM`: momentary Symbol layer and part of tri-layer Adjust.
- `GUI/Escape`: tap Escape, hold Left GUI/Super.

Space, Enter, Quote, Shift, and alpha keys are deterministic. There are no home-row mods.

## Symbol Layer

Hold the right `SYM` thumb.

```text
┌───┬───┬───┬───┬───┬───┐   ┌───┬───┬───┬───┬───┬───┐
│ ` │ 1 │ 2 │ 3 │ 4 │ 5 │   │ 6 │ 7 │ 8 │ 9 │ 0 │ ~ │
├───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┤
│ | │ : │ - │ = │ < │ > │   │ ( │ ) │ [ │ ] │ { │ } │
├───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┤
│ & │ _ │ ! │ @ │ # │ $ │   │ % │ ^ │ * │ + │ ? │ \ │
└───┴───┴───┴───┴───┴───┘   └───┴───┴───┴───┴───┴───┘
```

Rust symbol examples:
- `::` = colon twice.
- `->` = roll `-` to `>`.
- `=>` = roll `=` to `>`.
- `<>` = roll `<` to `>`.
- `()`, `[]`, `{}` are adjacent pairs.
- `&`, `|`, `_`, `?`, `:`, `-`, `=`, `<`, `>` are direct layer keys.

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

Hold the left `NAV` thumb.

```text
┌─────────┬─────┬─────┬─────┬─────┬─────┐   ┌─────┬─────┬─────┬─────┬─────┬─────────┐
│ PrevTab │ WM1 │ WM2 │ WM3 │ WM4 │ WM5 │   │ WM6 │ WM7 │ WM8 │ WM9 │ WM0 │ NextTab │
├─────────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────────┤
│ Reserved│ GUI │ Alt │ Ctrl│Shift│ C-l │   │Home │Left │Down │ Up  │Right│ End     │
├─────────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────────┤
│ C-l     │ [d  │ ]d  │tmux[│Copy │Paste│   │PgDn │A-b  │A-f  │PgUp │Bspc │ Delete  │
└─────────┴─────┴─────┴─────┴─────┴─────┘   └─────┴─────┴─────┴─────┴─────┴─────────┘
```

Notes:
- Arrow keys use H/J/K/L geometry on the right hand.
- `C-l` clears terminal screens without assuming the shell prompt is empty.
- `[d` and `]d` are emitted as clean diagnostic sequences for Neovim.
- `tmux[` sends `Ctrl-S`, waits briefly, then sends `[`. This depends on tmux prefix `C-s`.
- Copy/Paste are `Ctrl-Shift-C` and `Ctrl-Shift-V` for terminal emulators.
- Word movement is `Alt-B` and `Alt-F`, matching readline/zsh behavior.

## Adjust Layer

Hold `NAV + SYM` together. This uses QMK tri-layer support.

```text
┌────┬────┬────┬────┬────┬────┐   ┌────┬────┬────┬─────┬─────┬────────┐
│ F1 │ F2 │ F3 │ F4 │ F5 │ F6 │   │ F7 │ F8 │ F9 │ F10 │ F11 │ QK_BOOT│
├────┼────┼────┼────┼────┼────┤   ├────┼────┼────┼─────┼─────┼────────┤
│ -- │Caps│Rep │ARep│ -- │ -- │   │Prev│Play│Next│Mute │Vol- │ Vol+   │
├────┼────┼────┼────┼────┼────┤   ├────┼────┼────┼─────┼─────┼────────┤
│ -- │ -- │ -- │ -- │ -- │ -- │   │Bri-│Bri+│ -- │ --  │ --  │ --     │
└────┴────┴────┴────┴────┴────┘   └────┴────┴────┴─────┴─────┴────────┘
```

`QK_BOOT` is intentionally on a distant corner and requires `NAV + SYM + corner key`.

## Caps Word

Caps Word is enabled.

- Press both Shift keys together to activate Caps Word.
- Idle timeout is 4000 ms.
- Use it for identifiers like `MAX_RETRY_COUNT`, `DATABASE_URL`, `RUST_LOG`, and `DEFAULT_TIMEOUT_SECONDS`.
- `COMMAND_ENABLE` is disabled so both-shifts activation does not conflict with QMK Command.

## Repeat Key

Repeat Key is enabled on Adjust:

- `Rep`: `QK_REP`
- `ARep`: `QK_AREP`

If firmware headroom becomes tight in future versions, Repeat Key is the first optional feature to remove. Core layout, Caps Word, and OLED are higher priority.

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

## Tapping-Term Tuning

Starting values:

- `TAPPING_TERM = 180`
- `QUICK_TAP_TERM = 120`

Only `GUI/Escape` has per-key permissive hold. If Escape triggers Super accidentally, increase tapping term slightly or remove permissive hold for `GUI_ESC`.

## Recovery

- Use `QK_BOOT` from `NAV + SYM + top-right corner` for the active/master half.
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

- Base: Tab, Backspace, Space, Enter, Quote, both Shifts, thumb Ctrl, Alt, GUI/Escape.
- Rust symbols: `::`, `->`, `=>`, `<>`, `&`, `|`, `_`, `?`, `()`, `[]`, `{}`.
- Terminal: `Ctrl-C`, `Ctrl-R`, `Ctrl-W`, `Ctrl-U`, `Ctrl-L`, `Alt-B`, `Alt-F`, terminal copy/paste.
- tmux: prefix, send-prefix, copy mode, no stuck Ctrl, no XOFF freeze with `stty -ixon`.
- Neovim: Escape, `[d`, `]d`, H/J/K/L arrows, no firmware `:q` injection.
- i3: workspaces 1 through 10 with current Mod1 behavior.
- Browser: previous tab, next tab, clipboard shortcuts, navigation keys.
- Adjust: NAV + SYM, F1-F12, media, brightness, Caps Word, Repeat, protected `QK_BOOT`.
