# `src/core/window.c` 詳細解説

## 概要
MiniLibXを使用したウィンドウ作成、画像バッファ確保、イベントフックの設定を行います。

## コード詳細解説

| 行番号 | コード | 解説 |
| :--- | :--- | :--- |
| **3** | `int close_game(t_game *game)` | **終了処理**<br>ウィンドウの閉じるボタンやESCキー押下時に呼ばれます。リソースを解放して終了します。 |
| **10** | `int init_window(t_game *game)` | **ウィンドウ初期化関数**<br> |
| **14** | `  game->mlx = mlx_init();` | **MLX初期化**<br>MiniLibXライブラリを初期化し、接続識別子を取得します。 |
| **18-19** | `  screen_w = 1024; ...` | **画面解像度**<br>ウィンドウサイズを固定値（1024x768）で設定します。 |
| **21** | `  game->win = mlx_new_window(...)` | **ウィンドウ作成**<br>指定サイズとタイトルでウィンドウを開きます。 |
| **25** | `  game->img.img = mlx_new_image(...)` | **オフスクリーン画像**<br>描画用の裏画面（イメージバッファ）を作成します。ピクセル操作を高速に行うため、直接ウィンドウに描画せず、この画像に一度描画してからウィンドウに転送します。 |
| **26** | `  game->img.addr = mlx_get_data_addr(...)` | **アドレス取得**<br>画像のピクセルデータ配列へのポインタと、形式情報（bpp, line_length, endian）を取得します。これにより配列アクセス(`addr[i]`)での高速描画が可能になります。 |
| **31** | `  game->z_buffer = malloc(...)` | **Zバッファ確保**<br>画面幅分の深度バッファ配列を確保します。スプライト描画の前後判定に使用されます。 |
| **35-38** | `  mlx_hook(game->win, ...);` | **イベント登録**<br>`2` (KeyPress): キー入力自 → `key_press`<br>`6` (MotionNotify): マウス移動 → `mouse_handler`<br>`17` (DestroyNotify): 閉じるボタン → `close_game`<br>`mlx_loop_hook`: アイドル時（毎フレーム） → `render_frame` |
