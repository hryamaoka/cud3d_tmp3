# `src/core/game_cleanup.c` 詳細解説

## 概要
ゲーム終了時のメモリ解放処理を担当します。「パースエラー」「初期化エラー」「正常終了（ESCキー）」等、いかなる場合でも安全にリソースを解放し、メモリリークを防ぎます。

## 依存関係
*   `libft.h`: `free` 関数。
*   `mlx.h`: `mlx_destroy_image`, `mlx_destroy_window`, `mlx_destroy_display` など。

## 関数詳細

### 1. `free_split`
#### プロトタイプ
`void free_split(char **split)`

#### 戻り値
なし

#### 解説
`ft_split` で確保されたダブルポインタ（文字列の配列）を解放します。
各文字列 `split[i]` を解放した後、配列そのもの `split` を解放します。

### 2. `free_tex_paths` (static)
#### プロトタイプ
`static void free_tex_paths(t_game *game)`

#### 戻り値
なし

#### 解説
パース時に確保されたテクスチャのパス文字列 (`game->tex.no` 等) を解放します。これらは `strdup` 等で確保されているため、`free` が必要です。

### 3. `free_images` (static)
#### プロトタイプ
`static void free_images(t_game *game)`

#### 戻り値
なし

#### 解説
MiniLibX で生成された画像を破棄します。
*   壁テクスチャ (4枚)
*   ドアテクスチャ
*   スプライトテクスチャ (2フレーム分)
*   描画用バッファ (`game->img.img`)
それぞれ `mlx_destroy_image` を呼び出してGPUメモリ/Xサーバー側のリソースを解放します。

### 4. `free_all`
#### プロトタイプ
`void free_all(t_game *game)`

#### 戻り値
なし

#### 解説
ゲームのリソース解放のメイン関数です。上記ヘルパー関数を呼び出し、さらに以下の解放を行います。
1.  **文字列解放**: `free_tex_paths`。
2.  **マップ配列**: `game->map.grid`。
3.  **動的配列**: `z_buffer`, `sprites`。
4.  **MLXリソース**: `free_images` で画像を破棄し、ウィンドウ、ディスプレイを閉じた後、最後に `mlx` 本体を `free` します。

## コード行別解説 (`free_all`)

| 行番号 | コード | 詳細解説 |
| :--- | :--- | :--- |
| 45 | `free_tex_paths(game);` | テクスチャのパス文字列を解放します。 |
| 46-47 | `free_split(game->map.grid);` | マップの2次元配列を解放します。 |
| 50, 52 | `free(game->z_buffer);` ... | Zバッファやスプライト配列を解放します。 |
| 53-60 | `if (game->mlx) ...` | **MLXリソースの解放**<br>MLX関連は `mlx` ポインタが存在する場合のみ行います。画像を破棄し、ウィンドウを破壊し、ディスプレイ接続を切断し、最後にポインタ自体を解放する順序が重要です。 |
